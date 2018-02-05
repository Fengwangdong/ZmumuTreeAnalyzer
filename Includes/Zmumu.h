//////////////////////////////////////////////////////////
// This class is used for reading reduced tree 
// from Mu1Mu2Analyzer
// original author: Fengwangdong Zhang
//////////////////////////////////////////////////////////

#ifndef Zmumu_h
#define Zmumu_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "HistoZmumu.h"
#include <TString.h>
#include <iostream>
#include <string>
#include <sstream>
// Header file for the classes stored in the TTree if any.

class Zmumu : public HistoZmumu {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        Mu1Pt;
   Double_t        Mu2Pt;
   Double_t        Mu1Eta;
   Double_t        Mu2Eta;
   Double_t        Mu1Mu2Pt;
   Double_t        Mu1Mu2Eta;
   Double_t        invMass;
   Double_t        dRMu1Mu2;
   Double_t        dPhiMu1Mu2;
   Double_t        MetPt;
   Float_t         EventWeight;
   Float_t         SFsWeight;
   Double_t        puWeightVal;

   // List of branches
   TBranch        *b_Mu1Pt;   //!
   TBranch        *b_Mu2Pt;   //!
   TBranch        *b_Mu1Eta;   //!
   TBranch        *b_Mu2Eta;   //!
   TBranch        *b_Mu1Mu2Pt;   //!
   TBranch        *b_Mu1Mu2Eta;   //!
   TBranch        *b_invMass;   //!
   TBranch        *b_dRMu1Mu2;   //!
   TBranch        *b_dPhiMu1Mu2;   //!
   TBranch        *b_MetPt;   //!
   TBranch        *b_EventWeight;   //!
   TBranch        *b_SFsWeight;   //!
   TBranch        *b_puWeightVal;   //!

   TString fileName;
   float lumiScale;
   float summedWeights; // these two factors contribute to the MC normalization

   Zmumu(TString fileName_, float lumiScale_, float summedWeights_ = 1.0);
   string createOutputFileName();
   virtual ~Zmumu();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   bool isData;
};

#endif

#ifdef Zmumu_cxx
Zmumu::Zmumu(TString fileName_, float lumiScale_, float summedWeights_) : HistoZmumu() 
{
    fileName = fileName_;
    lumiScale = lumiScale_;
    summedWeights = summedWeights_;

    TChain *chain = new TChain("", "");
    TString treePath = fileName + ".root/Mu1Mu2Analyzer/Mu1Mu2Tree";
    chain->Add(treePath);
    fChain = chain;
    Init();
    isData = ((fileName.Index("Data") >= 0) || (fileName.Index("data") >= 0));
}

string Zmumu::createOutputFileName()
{
    ostringstream outputName;
    fileName.ReplaceAll("Tree/","");
    outputName << "Histogram/";
    outputName << fileName;
    outputName << "_histogram";
    outputName << ".root";
    return outputName.str();
}

Zmumu::~Zmumu()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Zmumu::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Zmumu::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Zmumu::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   
   Mu1Pt = -999.;
   Mu2Pt = -999.;
   Mu1Eta = -999.;
   Mu2Eta = -999.;
   Mu1Mu2Pt = -999.;
   Mu1Mu2Eta = -999.;
   invMass = -999.;
   dRMu1Mu2 = -999.;
   dPhiMu1Mu2 = -999.;
   MetPt = -999.;
   EventWeight = 1;
   SFsWeight = 1;
   puWeightVal = 1;

   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Mu1Pt", &Mu1Pt, &b_Mu1Pt);
   fChain->SetBranchAddress("Mu2Pt", &Mu2Pt, &b_Mu2Pt);
   fChain->SetBranchAddress("Mu1Eta", &Mu1Eta, &b_Mu1Eta);
   fChain->SetBranchAddress("Mu2Eta", &Mu2Eta, &b_Mu2Eta);
   fChain->SetBranchAddress("Mu1Mu2Pt", &Mu1Mu2Pt, &b_Mu1Mu2Pt);
   fChain->SetBranchAddress("Mu1Mu2Eta", &Mu1Mu2Eta, &b_Mu1Mu2Eta);
   fChain->SetBranchAddress("invMass", &invMass, &b_invMass);
   fChain->SetBranchAddress("dRMu1Mu2", &dRMu1Mu2, &b_dRMu1Mu2);
   fChain->SetBranchAddress("dPhiMu1Mu2", &dPhiMu1Mu2, &b_dPhiMu1Mu2);
   fChain->SetBranchAddress("MetPt", &MetPt, &b_MetPt);
   fChain->SetBranchAddress("EventWeight", &EventWeight, &b_EventWeight);
   fChain->SetBranchAddress("SFsWeight", &SFsWeight, &b_SFsWeight);
   fChain->SetBranchAddress("puWeightVal", &puWeightVal, &b_puWeightVal);
   Notify();
}

Bool_t Zmumu::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Zmumu::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Zmumu::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Zmumu_cxx
