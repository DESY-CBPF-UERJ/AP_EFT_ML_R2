#include "HEPHero.h"

//-------------------------------------------------------------------------------------------------
// Description:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace CompareEff{

    //int variable1Name;   [example]
}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPHero::SetupCompareEff() {

    //======SETUP CUTFLOW==========================================================================
    _cutFlow.insert(pair<string,double>("02_TwoLepOS", 0) );
    _cutFlow.insert(pair<string,double>("03_MET_Filters", 0) );
    _cutFlow.insert(pair<string,double>("04_HEM_Filter", 0) );
    _cutFlow.insert(pair<string,double>("05_Jets", 0) );
    _cutFlow.insert(pair<string,double>("06_MET", 0) );

    //======SETUP HISTOGRAMS=======================================================================
    makeHist( "ttbar_mass", 190, 50., 1000., "mtt [GeV]", "events" );
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    //sys_regions = { 0, 1, 2 }; [example] // Choose regions as defined in RegionID. Empty vector means that all events will be used.
    //makeSysHist( "histogram1DSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeSysHist( "histogram2DSysName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP OUTPUT BRANCHES==================================================================
    //_outputTree->Branch("variable1NameInTheTree", &CompareEff::variable1Name );  [example]

    //======SETUP INFORMATION IN OUTPUT HDF5 FILE==================================================
    HDF_insert("ttbar_reco", &ttbar_reco );
    HDF_insert("ttbar_reco_v2", &ttbar_reco_v2 );
    HDF_insert("ttbar_mass", &ttbar_mass );

    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPHero::CompareEffRegion() {

    LeptonSelection();

    if( !((RecoLepID > 0) && (RecoLepID < 2000)) ) return false;
    _cutFlow.at("02_TwoLepOS") += evtWeight;

    JetSelection();
    METCorrection();

    if( !METFilters() ) return false;
    _cutFlow.at("03_MET_Filters") += evtWeight;

    HEMissue();

    if( !HEM_filter ) return false;
    _cutFlow.at("04_HEM_Filter") += evtWeight;

    if( !((Njets >= 2) && (Nbjets >= 1)) ) return false;
    _cutFlow.at("05_Jets") += evtWeight;

    if( !(MET_pt > 30) ) return false;
    _cutFlow.at("06_MET") += evtWeight;

    Get_Leptonic_Info(true, false);

    Get_ttbar_Variables();

    _histograms1D.at("ttbar_mass").Fill( ttbar_mass, evtWeight );

    //-------------------------------------------------------------------------
    // Cut description
    //-------------------------------------------------------------------------
    //if( !(CutCondition) ) return false;           [Example]
    //_cutFlow.at("CutName") += evtWeight;          [Example]

    return true;
}


//-------------------------------------------------------------------------------------------------
// Write your analysis code here
//-------------------------------------------------------------------------------------------------
void HEPHero::CompareEffSelection() {













    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //CompareEff::variable1Name = 100;      [Example]

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
void HEPHero::CompareEffSystematic() {

    //FillSystematic( "histogram1DSysName", var, evtWeight );  [Example]
    //FillSystematic( "histogram2DSysName", var1, var2, evtWeight );  [Example]
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPHero::FinishCompareEff() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
