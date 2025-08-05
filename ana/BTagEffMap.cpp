#include "HEPHero.h"

//-------------------------------------------------------------------------------------------------
// Description: Maximum of 60000000 entries
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace BTagEffMap{

    int Jet_jetId;
    int Jet_hadronFlavour;
    float Jet_JES_pt;
    float Jet_pt;
    float Jet_eta;
    float Jet_btagDeepB;
    float Jet_btagDeepFlavB;
}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPHero::SetupBTagEffMap() {

    //======SETUP CUTFLOW==========================================================================
    

    //======SETUP HISTOGRAMS=======================================================================
    //makeHist( "histogram1DName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    //sys_regions = { 0, 1, 2 }; [example] // Choose regions as defined in RegionID. Empty vector means that all events will be used.
    //makeSysHist( "histogram1DSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeSysHist( "histogram2DSysName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP OUTPUT BRANCHES==================================================================
    //_outputTree->Branch("variable1NameInTheTree", &BTagEffMap::variable1Name );  [example]

    //======SETUP INFORMATION IN OUTPUT HDF5 FILE==================================================
    //HDF_insert("EventPosition", &_EventPosition );
    //HDF_insert("Jet_jetId", &BTagEffMap::Jet_jetId);
    HDF_insert("Jet_hadronFlavour", &BTagEffMap::Jet_hadronFlavour);
    HDF_insert("Jet_pt", &BTagEffMap::Jet_pt);
    //HDF_insert("Jet_JES_pt", &BTagEffMap::Jet_JES_pt);
    HDF_insert("Jet_eta", &BTagEffMap::Jet_eta);
    HDF_insert("Jet_btagDeepB", &BTagEffMap::Jet_btagDeepB);
    HDF_insert("Jet_btagDeepFlavB", &BTagEffMap::Jet_btagDeepFlavB);

    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPHero::BTagEffMapRegion() {

    

    return true;
}


//-------------------------------------------------------------------------------------------------
// Write your analysis code here
//-------------------------------------------------------------------------------------------------
void HEPHero::BTagEffMapSelection() {




    for (unsigned int ijet = 0; ijet < nJet; ++ijet) {
        if (
            Jet_pt[ijet] > JET_PT_CUT
            && Jet_jetId[ijet] >= JET_ID_WP
            && abs(Jet_eta[ijet]) < JET_ETA_CUT
        ) {
            //BTagEffMap::Jet_jetId = Jet_jetId[ijet];
            BTagEffMap::Jet_hadronFlavour = Jet_hadronFlavour[ijet];
            //BTagEffMap::Jet_JES_pt = Jet_JES_pt[ijet];
            BTagEffMap::Jet_pt = Jet_pt[ijet];
            BTagEffMap::Jet_eta = Jet_eta[ijet];
            BTagEffMap::Jet_btagDeepB = Jet_btagDeepB[ijet]; // DeepCSV
            BTagEffMap::Jet_btagDeepFlavB = Jet_btagDeepFlavB[ijet]; // DeepJet
            HDF_fill();
        }
    }








    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //BTagEffMap::variable1Name = 100;      [Example]

    //======FILL THE HISTOGRAMS====================================================================
    //_histograms1D.at("histogram1DName").Fill( var, evtWeight );               [Example]
    //_histograms2D.at("histogram2DName").Fill( var1, var2, evtWeight );        [Example]

    //======FILL THE OUTPUT TREE===================================================================
    //_outputTree->Fill();

    //======FILL THE OUTPUT HDF5 INFO===============================================================
    

    return;
}


//-------------------------------------------------------------------------------------------------
// Produce systematic histograms
//-------------------------------------------------------------------------------------------------
void HEPHero::BTagEffMapSystematic() {

    //FillSystematic( "histogram1DSysName", var, evtWeight );  [Example]
    //FillSystematic( "histogram2DSysName", var1, var2, evtWeight );  [Example]
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPHero::FinishBTagEffMap() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
