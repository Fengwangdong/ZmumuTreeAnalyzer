#!/usr/bin/python
import ROOT
from ROOT import TStyle, THStack, TPad, TFile, TH1, TH1D, TCanvas, TROOT, TLegend, TLatex, TKey, TString, TAttFill
import tdrStyle

tdrStyle.setTDRStyle()
ROOT.gStyle.SetErrorX(0.5)

fileDir = "Histogram/"

MCfileList = ["SingleTop", "VVTo2L2Nu", "WZTo3LNu", "ZZTo2L2Q", "ZZTo4L", "wjets", "ttbar", "zjets"]
MClabel = ["Single Top", "VV2L2Nu", "WZ3LNu", "ZZ2L2Q", "ZZ4L", "WJets", "t#bar{t}Jets", "Z(#mu#mu)Jets"]

histList = ["Mu1Pt", "Mu2Pt", "Mu1Mu2Pt", "Mu1Eta", "Mu2Eta", "Mu1Mu2Eta","invMass","MetPt","dRMu1Mu2","dPhiMu1Mu2"]

label1 = ROOT.TLatex(0.17,0.86, "CMS Preliminary")
label2 = ROOT.TLatex(0.22,0.96, "#sqrt{s} = 13 TeV,    Lumi = 35.9 fb^{-1}")
label1.SetNDC()
label2.SetNDC()
label2.SetTextSize(0.04)

Colors = [9, 8, 7, 6, 5, 4, 3, 2]

fData = ROOT.TFile(fileDir + "DataSMu_histogram.root")
fMC = []

for fileKey in MCfileList:
    ftemp = ROOT.TFile(fileDir + fileKey + "_histogram.root")
    fMC.append(ftemp)

print "***strange action****"
for itest in histList:
    fMC[7].Get(itest) # if the last sample's histograms are not visited here, they will appear as same as the data histograms, which is very strange?
print "***strange action finished!****"

for histKey in histList:

    # ===========  prepare the canvas for comparison  ===============
    canvas = ROOT.TCanvas("yield","dataVSMC",900,1200)
    canvas.cd()
    pad1 = ROOT.TPad("plot1","plot1",0.05,0.33,0.95,0.97)
    pad2 = ROOT.TPad("plot2","plot2",0.05,0.02,0.95,0.35)
    pad1.SetTopMargin(0.05)
    pad1.SetBottomMargin(0)
    pad2.SetTopMargin(0.05)
    pad2.SetBottomMargin(0.3)
    pad2.SetGridy()
    pad2.SetTicks()

    pad1.SetFillColor(0)
    pad1.SetFillStyle(4000)
    pad1.SetFrameFillStyle(0)
    pad2.SetFillColor(0)
    pad2.SetFillStyle(4000)
    pad2.SetFrameFillStyle(0)
    pad1.Draw()
    pad2.Draw()

    # ==============================================================

    data = fData.Get(histKey)
    data.Sumw2()
    data.SetStats(0)

    data.SetLineColor(1)
    data.SetLineWidth(2)
    data.SetMarkerStyle(20)
    data.SetMarkerColor(1)
    data.GetYaxis().SetTitleOffset(1.);
    data.GetYaxis().SetTitleSize(0.06);
    data.GetYaxis().SetLabelSize(0.05);


    if histKey.find("Pt")!=-1 or histKey.find("pt")!=-1 or histKey.find("invMass")!=-1:
       pad1.SetLogy()
       data.GetYaxis().SetRangeUser((data.GetMinimum())*0.001, data.GetMaximum()*15.0)

    if histKey.find("Eta")!=-1:
       data.GetYaxis().SetRangeUser((data.GetMinimum())*0.001, data.GetMaximum()*1.2)

    if histKey.find("dPhi")!=-1:
       pad1.SetLogy()
       data.GetYaxis().SetRangeUser(data.GetMinimum()*0.001, data.GetMaximum()*15.0)

    if histKey.find("dR")!=-1:
       pad1.SetLogy()
       data.GetYaxis().SetRangeUser(1, data.GetMaximum()*100.0)


    legend = ROOT.TLegend(0.77,0.6,0.99,0.99);
    legend.SetFillColor(0);
    legend.SetTextSize(0.04);
    legend.AddEntry(data,"Data","ep");

    hSumMC = ROOT.THStack(histKey, histKey) # used to compare the data and MC sum in plots
    ratio = data.Clone()

    for i,index in enumerate(fMC):
        iMC = index.Get(histKey)
        iMC.SetStats(0)
        iMC.Sumw2()

        iMC.SetFillStyle(1001)
        iMC.SetFillColor(Colors[i])
        iMC.SetLineColor(Colors[i])

        hSumMC.Add(iMC)
        legend.AddEntry(iMC, MClabel[i], "f")


    ratio.Divide(hSumMC.GetStack().Last().Clone())
    ratio.SetLineColor(1)
    ratio.SetLineWidth(1)
    ratio.SetMarkerStyle(20)
    ratio.SetMarkerColor(1)

    ratio.GetYaxis().SetRangeUser(0.5, 1.5);
    ratio.GetYaxis().SetNdivisions(5,2,0);
    ratio.GetYaxis().SetTitle("Data/MC");
    ratio.GetYaxis().SetTitleSize(0.12);
    ratio.GetYaxis().SetTitleOffset(0.5);
    ratio.GetYaxis().SetLabelSize(0.11);
    ratio.GetXaxis().SetTitleSize(0.11);
    ratio.GetXaxis().SetLabelSize(0.11);

    pad1.cd()
    data.Draw("EP")
    hSumMC.Draw("HIST same")
    data.DrawCopy("e same")
    legend.Draw("same")
    label1.Draw("same")
    label2.Draw("same")

    pad2.cd()
    ratio.Draw("EP")
    canvas.SaveAs("plots/"+histKey+"_Yield.pdf")
    canvas.SaveAs("plots/"+histKey+"_Yield.png")

