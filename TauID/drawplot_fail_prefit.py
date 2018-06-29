#!/usr/bin/python
import ROOT
from ROOT import TObject, TStyle, THStack, TPad, TFile, TH1, TH1D, TCanvas, TROOT, TLegend, TLatex, TKey, TString, TAttFill, TGraphAsymmErrors
import tdrStyle
import libPyROOT
from array import array

tdrStyle.setTDRStyle()
ROOT.gStyle.SetErrorX(0.5)

fileDir = "./postfit/"

MCfileList = ["DYJ", "DYB", "VV", "W", "TT", "QCD", "DYS"]
MClabel = ["Z(ll)Jets", "Z(ll)", "VV", "WJets", "TTJets", "QCD", "Z(#tau#tau)"]

histList = ["visMass", "mtTauMu", "ptTauHad"]
histLabel = ["M_{#tau#tau}^{vis} [GeV]", "M_{T}(#tau_{#mu}) [GeV]", "p_{T}(#tau_{h}) [GeV]"]
histRange = [[0,200],[0,40],[20,200]]

label1 = ROOT.TLatex(0.17,0.86, "CMS Preliminary")
label2 = ROOT.TLatex(0.21,0.96, "#sqrt{s} = 13 TeV, Lumi = 35.9 fb^{-1}")
label3 = ROOT.TLatex(0.55,0.86, "failOS prefit")
label1.SetNDC()
label2.SetNDC()
label2.SetTextSize(0.04)
label3.SetNDC()
label3.SetTextSize(0.04)

Colors = [9, 8, 7, 6, 5, 4, 2]

for k,keyHist in enumerate(histList):

    fData = ROOT.TFile(fileDir + "ztt_" + keyHist +"_shapes.root")

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

    data = fData.Get("fail_prefit/data_obs")
    data.Sumw2()
    data.SetStats(0)

    data.SetLineColor(1)
    data.SetLineWidth(2)
    data.SetMarkerStyle(20)
    data.SetMarkerColor(1)
    data.GetYaxis().SetTitle("#Events");
    data.GetYaxis().SetTitleOffset(1.);
    data.GetYaxis().SetTitleSize(0.06);
    data.GetYaxis().SetLabelSize(0.05);
    data.GetXaxis().SetRangeUser(histRange[k][0],histRange[k][1])

    if "pt" in keyHist:
        pad1.SetLogy()
        data.GetYaxis().SetRangeUser((data.GetMinimum())*0.001, data.GetMaximum()*15.0)

    else:
        data.GetYaxis().SetRangeUser(0, data.GetMaximum()*1.4)

    legend = ROOT.TLegend(0.77,0.6,0.99,0.99);
    legend.SetFillColor(0);
    legend.SetTextSize(0.04);
    legend.AddEntry(data,"Data","epl");

    ratio = data.Clone()
    hSumMC = ROOT.THStack("", "") # used to compare the data and MC sum in plots

    for i,histKey in enumerate(MCfileList):

        iMC = fData.Get("fail_prefit/" + histKey)
        iMC.SetStats(0)
        iMC.Sumw2()

        iMC.SetFillStyle(1001)
        iMC.SetFillColor(Colors[i])
        iMC.SetLineColor(Colors[i])

        hSumMC.Add(iMC)
        legend.AddEntry(iMC, MClabel[i], "f")

    hSyst = hSumMC.GetStack().Last().Clone()
    nBins = hSyst.GetNbinsX()

    for ibin in range(nBins):
        if ratio.GetBinContent(ibin+1) == 0 or hSyst.GetBinContent(ibin+1) == 0:
            continue
        statUnc = ratio.GetBinError(ibin+1)/ratio.GetBinContent(ibin+1)
        ratio.SetBinContent(ibin+1,ratio.GetBinContent(ibin+1)/hSyst.GetBinContent(ibin+1))
        ratio.SetBinError(ibin+1,statUnc)

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
    ratio.GetXaxis().SetTitle(histLabel[k])
    ratio.GetXaxis().SetRangeUser(histRange[k][0],histRange[k][1])
    ratio.GetXaxis().SetTitleSize(0.11);
    ratio.GetXaxis().SetLabelSize(0.11);

    xCoor = array('d')
    yCoor = array('d')
    xErr = array('d')
    yErr = array('d')

    for ibin in range(nBins):
        xCoor.append(hSyst.GetBinCenter(ibin+1))
        yCoor.append(1.0)
        xErr.append(hSyst.GetBinWidth(ibin+1)/2.0)

        if hSyst.GetBinContent(ibin+1) == 0:
            yErr.append(0)
            continue

        yErr.append(hSyst.GetBinError(ibin+1)/hSyst.GetBinContent(ibin+1))


    grSyst = ROOT.TGraphAsymmErrors(nBins, xCoor, yCoor, xErr, xErr, yErr, yErr)

    grSyst.SetFillColor(12)
    grSyst.SetLineColor(12)
    grSyst.SetFillStyle(3013)

    legend.AddEntry(grSyst,"Syst Unc","f")

    pad1.cd()
    data.Draw("EP")
    hSumMC.Draw("HIST same")
    data.DrawCopy("e same")
    ROOT.gPad.RedrawAxis()
    legend.Draw("same")
    label1.Draw("same")
    label2.Draw("same")
    label3.Draw("same")

    pad2.cd()
    ratio.Draw("EP")
    grSyst.Draw("2")
    canvas.SaveAs("controlPlots/" + keyHist + "_fail_prefit.pdf")
