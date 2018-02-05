#include "Zmumu.h"
#include "lumiana.h"

int main()
{
    double lumi = 35.9; // fb-1
    float summedWeights = 0;

    //------------------------- data histograms production -------------------
    lumiana DataLumi("Tree/DataSMu");
    summedWeights = DataLumi.Loop();
    Zmumu DataHist("Tree/DataSMu", 1, 1);
    DataHist.Loop();

    //------------------------- zjets histograms production -------------------
    lumiana DYLumi("Tree/zjets");
    summedWeights = DYLumi.Loop();
    Zmumu DYHist("Tree/zjets", lumi*5765.4*1000., summedWeights);
    DYHist.Loop();

    //------------------------- ttjets histograms production -------------------
    lumiana TTLumi("Tree/ttbar");
    summedWeights = TTLumi.Loop();
    Zmumu TTHist("Tree/ttbar", lumi*831.76*1000., summedWeights);
    TTHist.Loop();

    //------------------------- wjets histograms production -------------------
    lumiana WJetsLumi("Tree/wjets");
    summedWeights = WJetsLumi.Loop();
    Zmumu WJetsHist("Tree/wjets", lumi*61526.7*1000., summedWeights);
    WJetsHist.Loop();

    //------------------------- VVTo2L2Nu histograms production -------------------
    lumiana VVTo2L2NuLumi("Tree/VVTo2L2Nu");
    summedWeights = VVTo2L2NuLumi.Loop();
    Zmumu VVTo2L2NuHist("Tree/VVTo2L2Nu", lumi*11.95*1000., summedWeights);
    VVTo2L2NuHist.Loop();

    //------------------------- WZTo3LNu histograms production -------------------
    lumiana WZTo3LNuLumi("Tree/WZTo3LNu");
    summedWeights = WZTo3LNuLumi.Loop();
    Zmumu WZTo3LNuHist("Tree/WZTo3LNu", lumi*5.26*1000., summedWeights);
    WZTo3LNuHist.Loop();

    //------------------------- ZZTo2L2Q histograms production -------------------
    lumiana ZZTo2L2QLumi("Tree/ZZTo2L2Q");
    summedWeights = ZZTo2L2QLumi.Loop();
    Zmumu ZZTo2L2QHist("Tree/ZZTo2L2Q", lumi*3.22*1000., summedWeights);
    ZZTo2L2QHist.Loop();

    //------------------------- ZZTo4L histograms production -------------------
    lumiana ZZTo4LLumi("Tree/ZZTo4L");
    summedWeights = ZZTo4LLumi.Loop();
    Zmumu ZZTo4LHist("Tree/ZZTo4L", lumi*1.212*1000., summedWeights);
    ZZTo4LHist.Loop();

    //------------------------- St_sch_4l histograms production -------------------
    lumiana St_sch_4lLumi("Tree/St_sch_4l");
    summedWeights = St_sch_4lLumi.Loop();
    Zmumu St_sch_4lHist("Tree/St_sch_4l", lumi*3.36*1000., summedWeights);
    St_sch_4lHist.Loop();

    //------------------------- St_tch_inc_top histograms production -------------------
    lumiana St_tch_inc_topLumi("Tree/St_tch_inc_top");
    summedWeights = St_tch_inc_topLumi.Loop();
    Zmumu St_tch_inc_topHist("Tree/St_tch_inc_top", lumi*44.33*1000., summedWeights);
    St_tch_inc_topHist.Loop();

    //------------------------- St_tch_inc_antitop histograms production -------------------
    lumiana St_tch_inc_antitopLumi("Tree/St_tch_inc_antitop");
    summedWeights = St_tch_inc_antitopLumi.Loop();
    Zmumu St_tch_inc_antitopHist("Tree/St_tch_inc_antitop", lumi*26.38*1000., summedWeights);
    St_tch_inc_antitopHist.Loop();

    //------------------------- St_tW_inc_top histograms production -------------------
    lumiana St_tW_inc_topLumi("Tree/St_tW_inc_top");
    summedWeights = St_tW_inc_topLumi.Loop();
    Zmumu St_tW_inc_topHist("Tree/St_tW_inc_top", lumi*35.85*1000., summedWeights);
    St_tW_inc_topHist.Loop();

    //------------------------- St_tW_inc_antitop histograms production -------------------
    lumiana St_tW_inc_antitopLumi("Tree/St_tW_inc_antitop");
    summedWeights = St_tW_inc_antitopLumi.Loop();
    Zmumu St_tW_inc_antitopHist("Tree/St_tW_inc_antitop", lumi*35.85*1000., summedWeights);
    St_tW_inc_antitopHist.Loop();

    return 0;
}
