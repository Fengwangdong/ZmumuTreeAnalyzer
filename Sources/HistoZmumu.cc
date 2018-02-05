#include <TH1D.h>
#include "HistoZmumu.h"
#include <TString.h>
#include <TAxis.h>
#define PI 3.14159265359
using namespace std;

TH1D* HistoZmumu::newTH1D(string name, string title, string xTitle, int nBins, double *xBins){
    TH1D* hist = new TH1D(name.c_str(), title.c_str(), nBins, xBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH1D* HistoZmumu::newTH1D(string name, string title, string xTitle, vector<double>& xBinsVect)
{
    int nBins = xBinsVect.size()-1;
    double *xBins = new double[xBinsVect.size()];
    std::copy(xBinsVect.begin(), xBinsVect.end(), xBins);
    TH1D* hist = new TH1D(name.c_str(), title.c_str(), nBins, xBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    delete [] xBins;
    histColl.push_back(hist);
    return hist;
}

TH1D* HistoZmumu::newTH1D(string name, string title, string xTitle, int nBins, double xLow, double xUp){
    TH1D* hist = new TH1D(name.c_str(), title.c_str(), nBins, xLow, xUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    hist->SetOption("HIST");
    histColl.push_back(hist);
    return hist;
}

HistoZmumu::HistoZmumu(){

    double Mu1PtBin [] = {25, 29, 33, 37, 41, 45, 49, 53, 57, 61, 65, 69, 73, 77, 81, 85, 89, 93, 97, 101, 105, 110, 115, 120, 126, 133, 141, 150, 160, 171, 183, 196, 210, 225, 241, 258, 276, 300};
    double Mu2PtBin [] = {10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66, 70, 75, 80, 86, 92, 99, 107, 116, 126, 137, 149, 162, 176, 200};
    double Mu1Mu2PtBin [] = {0, 5, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66, 70, 75, 80, 86, 92, 99, 107, 116, 126, 137, 149, 162, 176, 200};
    double MetPtBin [] = {0, 4, 8, 12, 16, 20, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61, 65, 69, 73, 77, 81, 85, 89, 93, 97, 101, 105, 110, 115, 120, 126, 133, 141, 150, 160, 171, 183, 196, 210, 225, 241, 258, 276, 300};

    int NBinsMu1Pt = sizeof(Mu1PtBin)/sizeof(Mu1PtBin[0])-1;
    int NBinsMu2Pt = sizeof(Mu2PtBin)/sizeof(Mu2PtBin[0])-1;
    int NBinsMu1Mu2Pt = sizeof(Mu1Mu2PtBin)/sizeof(Mu1Mu2PtBin[0])-1;
    int NBinsMetPt = sizeof(MetPtBin)/sizeof(MetPtBin[0])-1;

    Mu1Pt_ZSkim = newTH1D("Mu1Pt", "Mu1Pt", "p_{T}(#mu_{1})[GeV]", NBinsMu1Pt, Mu1PtBin);
    Mu2Pt_ZSkim = newTH1D("Mu2Pt", "Mu2Pt", "p_{T}(#mu_{2})[GeV]", NBinsMu2Pt, Mu2PtBin);

    Mu1Eta_ZSkim = newTH1D("Mu1Eta", "Mu1Eta", "#eta(#mu_{1})", 40, -2.5, 2.5);
    Mu2Eta_ZSkim = newTH1D("Mu2Eta", "Mu2Eta", "#eta(#mu_{2})", 40, -2.5, 2.5);

    Mu1Mu2Pt_ZSkim = newTH1D("Mu1Mu2Pt", "Mu1Mu2Pt", "p_{T}(#mu_{1}#mu_{2})[GeV]", NBinsMu1Mu2Pt, Mu1Mu2PtBin);
    Mu1Mu2Eta_ZSkim = newTH1D("Mu1Mu2Eta", "Mu1Mu2Eta", "#eta(#mu_{1}#mu_{2})", 40, -2.5, 2.5);
    invMass_ZSkim = newTH1D("invMass", "invMass", "M(#mu_{1}#mu_{2})[GeV]", 30, 60., 120.);

    dRMu1Mu2_ZSkim = newTH1D("dRMu1Mu2", "dRMu1Mu2", "#Delta R(#mu_{1}#mu_{2})", 50, 0, 5.0);
    dPhiMu1Mu2_ZSkim = newTH1D("dPhiMu1Mu2", "dPhiMu1Mu2", "#Delta#phi(#mu_{1}#mu_{2})[Rad]", 50, 0, PI);

    MetPt_ZSkim = newTH1D("MetPt", "MetPt", "#slash{E}_{T}[GeV]", NBinsMetPt, MetPtBin);
}

HistoZmumu::~HistoZmumu()
{}
