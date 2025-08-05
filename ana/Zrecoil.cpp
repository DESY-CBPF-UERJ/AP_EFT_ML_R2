#include "HEPHero.h"

//-------------------------------------------------------------------------------------------------
// Description:
//-------------------------------------------------------------------------------------------------
// It is necessary to uncomment the line below and comment the previous one in ANATools.cpp in
// order to deactivate JER from DY.
// if( apply_jer_corr && (dataset_group != "Data") && !(dsNameDY == "DYJetsToLL") ){ 
// 
// Comment all part of pileup special treatement for DY in CMSTools.cpp
// if( (dsNameDY == "DYJetsToLL") && (sysType != "nominal") ){

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace Zrecoil{

    float u1;
    float u2;
    
    float pileup_ratio_down;
    float pileup_ratio_up;
}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPHero::SetupZrecoil() {

    //======SETUP CUTFLOW==========================================================================
    _cutFlow.insert(pair<string,double>("00_TwoLepOS", 0) );
    _cutFlow.insert(pair<string,double>("01_MET", 0) );
    _cutFlow.insert(pair<string,double>("02_LeadingLep_Pt", 0) );
    _cutFlow.insert(pair<string,double>("03_LepLep_DM", 0) );
    _cutFlow.insert(pair<string,double>("04_LepLep_Pt", 0) );
    _cutFlow.insert(pair<string,double>("05_Selected", 0) );
    _cutFlow.insert(pair<string,double>("06_Corrected", 0) );

    //======SETUP HISTOGRAMS=======================================================================
    //makeHist( "histogram1DName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    //sys_regions = { 0, 1, 2 }; [example] // Choose regions as defined in RegionID. Empty vector means that all events will be used.
    //makeSysHist( "histogram1DSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeSysHist( "histogram2DSysName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP OUTPUT BRANCHES==================================================================
    //_outputTree->Branch("variable1NameInTheTree", &Zrecoil::variable1Name );  [example]

    //======SETUP INFORMATION IN OUTPUT HDF5 FILE==================================================
    //HDF_insert( "RecoLepID", &RecoLepID );
    HDF_insert( "LepLep_pt", &LepLep_pt );
    HDF_insert( "LepLep_deltaM", &LepLep_deltaM );
    //HDF_insert( "MET_JES_pt", &MET_JES_pt );
    //HDF_insert( "MET_JES_phi", &MET_JES_phi );
    HDF_insert( "MET_pt", &MET_pt );
    //HDF_insert( "MET_phi", &MET_phi );
    HDF_insert( "Nbjets", &Nbjets );
    //HDF_insert( "Njets", &Njets );
    HDF_insert( "Njets_ISR", &Njets_ISR );
    
    HDF_insert( "pileup_ratio_down", &Zrecoil::pileup_ratio_down );
    HDF_insert( "pileup_ratio_up", &Zrecoil::pileup_ratio_up );
    
    //HDF_insert( "LepLep_deltaR", &LepLep_deltaR );
    //HDF_insert( "LeadingLep_pt", &LeadingLep_pt );
    HDF_insert( "u1", &Zrecoil::u1 );
    HDF_insert( "u2", &Zrecoil::u2 );
    
    //HDF_insert( "Lep3Lep4_M", &Lep3Lep4_M );
    //HDF_insert( "Lep3Lep4_pt", &Lep3Lep4_pt );
    //HDF_insert( "Lep3Lep4_phi", &Lep3Lep4_phi );
    

    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPHero::ZrecoilRegion() {
    
    // Lateral Syst variation
    //_sysName_lateral = "JES";
    //_Universe = 0;
    //aplly cut in MET
    //remove pileup weight
    
    LeptonSelection();
    
    //if( !(((RecoLepID > 0) && (RecoLepID < 100)) || (RecoLepID > 40000)) ) return false;           // Has two reconstructed leptons with opposite signal
    if( !((RecoLepID > 0) && (RecoLepID < 100)) ) return false;
    _cutFlow.at("00_TwoLepOS") += evtWeight;
    
    JetSelection();
    
    //if( !(MET_pt <= MET_CUT) ) return false;                                     // MET <= CUT
    _cutFlow.at("01_MET") += evtWeight;
    
    METCorrection();
    
    Get_Leptonic_Info(true, false);
    
    if( !(LeadingLep_pt > LEADING_LEP_PT_CUT) ) return false;                   // Leading lepton pt > CUT
    _cutFlow.at("02_LeadingLep_Pt") += evtWeight; 
    
    Get_LepLep_Variables(true, true);
    
    //if( !(LepLep_deltaM < LEPLEP_DM_CUT) ) return false;                        // Difference between Z boson mass and the inv. mass of two leptons < CUT
    _cutFlow.at("03_LepLep_DM") += evtWeight; 
    
    //if( !(LepLep_pt > LEPLEP_PT_CUT) ) return false;                            // Two leptons system pt > CUT
    _cutFlow.at("04_LepLep_Pt") += evtWeight;
    
     
    bool GoodEvent = lumi_certificate.GoodLumiSection( _datasetName, run, luminosityBlock );
    if( !GoodEvent ) return false;                                              // Select only certified data events
    
    if( !METFilters() ) return false;                                           // Selected by MET filters

    HEMissue();

    if( !HEM_filter ) return false;                                           // Selected by HEM filter
    
    if( !Trigger() ) return false;                                              // Selected by triggers
    _cutFlow.at("05_Selected") += evtWeight;
    
    Weight_corrections();
    _cutFlow.at("06_Corrected") += evtWeight;

    return true;
}


//-------------------------------------------------------------------------------------------------
// Write your analysis code here
//-------------------------------------------------------------------------------------------------
void HEPHero::ZrecoilSelection() {



    float ux = -( MET_pt*cos(MET_phi) + LepLep_pt*cos(LepLep_phi) );
    float uy = -( MET_pt*sin(MET_phi) + LepLep_pt*sin(LepLep_phi) );
    
    Zrecoil::u1 = ux*cos(LepLep_phi) + uy*sin(LepLep_phi);
    Zrecoil::u2 = -ux*sin(LepLep_phi) + uy*cos(LepLep_phi);
    


    double pileup_wgt_down = GetPileupWeight(Pileup_nTrueInt, "down");
    double pileup_wgt_up = GetPileupWeight(Pileup_nTrueInt, "up");
    
    Zrecoil::pileup_ratio_down = pileup_wgt_down/pileup_wgt;
    Zrecoil::pileup_ratio_up = pileup_wgt_up/pileup_wgt;


    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //Zrecoil::variable1Name = 100;      [Example]

    //======FILL THE HISTOGRAMS====================================================================
    //_histograms1D.at("histogram1DName").Fill( var, evtWeight );               [Example]
    //_histograms2D.at("histogram2DName").Fill( var1, var2, evtWeight );        [Example]

    //======FILL THE OUTPUT TREE===================================================================
    //_outputTree->Fill();

    //======FILL THE OUTPUT HDF5 INFO===============================================================
    HDF_fill();

    return;
}


//-------------------------------------------------------------------------------------------------
// Produce systematic histograms
//-------------------------------------------------------------------------------------------------
void HEPHero::ZrecoilSystematic() {

    //FillSystematic( "histogram1DSysName", var, evtWeight );  [Example]
    //FillSystematic( "histogram2DSysName", var1, var2, evtWeight );  [Example]
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPHero::FinishZrecoil() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
