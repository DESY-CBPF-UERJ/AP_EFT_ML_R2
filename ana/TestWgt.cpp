#include "HEPHero.h"

//-------------------------------------------------------------------------------------------------
// Description:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace TestWgt{

    //int variable1Name;   [example]
}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPHero::SetupTestWgt() {

    //======SETUP CUTFLOW==========================================================================
    _cutFlow.insert(pair<string,double>("01_Leptons", 0) );
    _cutFlow.insert(pair<string,double>("02_LeadingLepPt", 0) );
    _cutFlow.insert(pair<string,double>("03_Jets", 0) );
    _cutFlow.insert(pair<string,double>("04_MET", 0) );
    _cutFlow.insert(pair<string,double>("05_MET_Filters", 0) );
    _cutFlow.insert(pair<string,double>("06_HEM_Filter", 0) );
    _cutFlow.insert(pair<string,double>("07_Selected", 0) );
    

    //======SETUP HISTOGRAMS=======================================================================
    //makeHist( "histogram1DName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    //sys_regions = { 0, 1, 2 }; [example] // Choose regions as defined in RegionID. Empty vector means that all events will be used.
    //makeSysHist( "histogram1DSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeSysHist( "histogram2DSysName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP OUTPUT BRANCHES==================================================================
    //_outputTree->Branch("variable1NameInTheTree", &TestWgt::variable1Name );  [example]

    //======SETUP INFORMATION IN OUTPUT HDF5 FILE==================================================
    HDF_insert( "prefiring_wgt", &prefiring_wgt );
    HDF_insert( "pileup_wgt", &pileup_wgt );
    HDF_insert( "electron_wgt", &electron_wgt );
    HDF_insert( "muon_wgt", &muon_wgt );
    HDF_insert( "jet_puid_wgt", &jet_puid_wgt );
    HDF_insert( "btag_wgt", &btag_wgt );
    //HDF_insert( "trigger_wgt", &trigger_wgt );
    //HDF_insert( "top_pt_wgt", &top_pt_wgt );

    HDF_insert( "Nelectrons", &Nelectrons );
    HDF_insert( "Nmuons", &Nmuons );
    HDF_insert( "Nbjets", &Nbjets );
    HDF_insert( "Njets_below50", &Njets_below50 );
    //HDF_insert( "PV_npvs", &PV_npvs );
    HDF_insert( "PV_npvsGood", &PV_npvsGood );
    HDF_insert( "MET_pt", &MET_pt );
    

    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPHero::TestWgtRegion() {

    LeptonSelection();

    if( !(Nleptons >= 2) ) return false;
    _cutFlow.at("01_Leptons") += evtWeight;

    Get_Leptonic_Info(true, false);

    if( !(LeadingLep_pt > LEADING_LEP_PT_CUT) ) return false;
    _cutFlow.at("02_LeadingLepPt") += evtWeight;

    JetSelection();

    if( !((Njets >= 2) && (Nbjets >= 1)) ) return false;
    _cutFlow.at("03_Jets") += evtWeight;
    
    METCorrection();

    if( !(MET_pt > MET_CUT) ) return false;
    _cutFlow.at("04_MET") += evtWeight;

    if( !METFilters() ) return false;
    _cutFlow.at("05_MET_Filters") += evtWeight;

    HEMissue();

    if( !HEM_filter ) return false;
    _cutFlow.at("06_HEM_Filter") += evtWeight;

    bool GoodEvent = lumi_certificate.GoodLumiSection( _datasetName, run, luminosityBlock );
    if( !GoodEvent ) return false;                                      
    
    if( !Trigger() ) return false;                                              
    _cutFlow.at("07_Selected") += evtWeight;


    Weight_corrections();

    //cout << jet_puid_wgt << " " << jet_puid_wgt_2 << " " << endl;

    return true;
}


//-------------------------------------------------------------------------------------------------
// Write your analysis code here
//-------------------------------------------------------------------------------------------------
void HEPHero::TestWgtSelection() {













    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //TestWgt::variable1Name = 100;      [Example]

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
void HEPHero::TestWgtSystematic() {

    //FillSystematic( "histogram1DSysName", var, evtWeight );  [Example]
    //FillSystematic( "histogram2DSysName", var1, var2, evtWeight );  [Example]
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPHero::FinishTestWgt() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
