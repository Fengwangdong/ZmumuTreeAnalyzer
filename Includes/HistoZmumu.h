#ifndef _HistoZmumu_h_
#define _HistoZmumu_h_

#include "TH1.h"
#include <iostream>
#include <vector>
#include <string>
#include "TArray.h"
using namespace std;

class HistoZmumu{

    public:

        vector<TH1D*> histColl;

        TH1D* newTH1D(string, string, string, int, double*);
        TH1D* newTH1D(string, string, string, int, double, double);
        TH1D* newTH1D(string, string, string, vector<double>&);

        HistoZmumu();
        ~HistoZmumu();
        TH1D* Mu1Pt_ZSkim;
        TH1D* Mu2Pt_ZSkim;
        TH1D* Mu1Eta_ZSkim;
        TH1D* Mu2Eta_ZSkim;
        TH1D* invMass_ZSkim;
        TH1D* dRMu1Mu2_ZSkim;
        TH1D* dPhiMu1Mu2_ZSkim;
        TH1D* Mu1Mu2Pt_ZSkim;
        TH1D* Mu1Mu2Eta_ZSkim;
        TH1D* MetPt_ZSkim;
};

#endif
