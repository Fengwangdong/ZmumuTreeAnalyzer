#define Zmumu_cxx
#include "Zmumu.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <sys/time.h>
#include <iomanip>
using namespace std;

void Zmumu::Loop()
{
   TString outputfileName = createOutputFileName();
   TFile* outputFile = new TFile(outputfileName, "RECREATE");

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   //Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   struct timeval t0;
   gettimeofday(&t0, 0);
   int mess_every_n =  std::min(1000000LL, nentries/10);

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;

      if (jentry % mess_every_n == 0 && jentry > 0){
          timeval t1;
          gettimeofday(&t1, 0);
          double dt = (t1.tv_sec - t0.tv_sec) + 1.e-6*(t1.tv_usec - t0.tv_usec);
          dt *= double(nentries  - jentry) / mess_every_n;
          int dt_s = int(dt + 0.5);
          int dt_h = int(dt_s) / 3600; 
          dt_s -= dt_h * 3600;
          int dt_m = dt_s / 60;
          dt_s -= dt_m *60;
          cout << TString::Format("%4.1f%%", (100. * jentry) / nentries)
              << "\t" << std::setw(11) << jentry << " / " << nentries
              << "\t " << std::setw(4) << int(dt / mess_every_n * 1.e6 + 0.5) << " us/event"
              << "\t Remaining time for this dataset loop: " 
              << std::setw(2) << dt_h << " h "
              << std::setw(2) << dt_m << " min "
              << std::setw(2) << dt_s << " s"
              << "\r" << std::flush;
          t0 = t1;
      }

      nb = fChain->GetEntry(jentry);   
      nbytes += nb;
     
      if(isData){
        Mu1Pt_ZSkim->Fill(Mu1Pt);
        Mu2Pt_ZSkim->Fill(Mu2Pt);
        Mu1Eta_ZSkim->Fill(Mu1Eta);
        Mu2Eta_ZSkim->Fill(Mu2Eta);
        Mu1Mu2Pt_ZSkim->Fill(Mu1Mu2Pt);
        Mu1Mu2Eta_ZSkim->Fill(Mu1Mu2Eta);
        invMass_ZSkim->Fill(invMass);
        dRMu1Mu2_ZSkim->Fill(dRMu1Mu2);
        dPhiMu1Mu2_ZSkim->Fill(dPhiMu1Mu2);
        MetPt_ZSkim->Fill(MetPt);
      }

      else{
        if (SFsWeight == 0) SFsWeight = 1.0;
        Mu1Pt_ZSkim->Fill(Mu1Pt, EventWeight*SFsWeight);
        Mu2Pt_ZSkim->Fill(Mu2Pt, EventWeight*SFsWeight);
        Mu1Eta_ZSkim->Fill(Mu1Eta, EventWeight*SFsWeight);
        Mu2Eta_ZSkim->Fill(Mu2Eta, EventWeight*SFsWeight);
        Mu1Mu2Pt_ZSkim->Fill(Mu1Mu2Pt, EventWeight*SFsWeight);
        Mu1Mu2Eta_ZSkim->Fill(Mu1Mu2Eta, EventWeight*SFsWeight);
        invMass_ZSkim->Fill(invMass, EventWeight*SFsWeight);
        dRMu1Mu2_ZSkim->Fill(dRMu1Mu2, EventWeight*SFsWeight);
        dPhiMu1Mu2_ZSkim->Fill(dPhiMu1Mu2, EventWeight*SFsWeight);
        MetPt_ZSkim->Fill(MetPt, EventWeight*SFsWeight);
      }
   }

   outputFile->cd();

   int numberofhist = histColl.size();
   for(int i=0; i<numberofhist; i++){
       if (!isData) histColl[i]->Scale(lumiScale/summedWeights);
       histColl[i]->Write();
   }

   for(int j=0; j<numberofhist; j++){
       delete histColl[j];
   }

   outputFile->Write();
   outputFile->Close();
}
