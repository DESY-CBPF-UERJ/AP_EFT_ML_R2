#include "HEPHero.h"

//-------------------------------------------------------------------------------------------------
// Description:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace Sonnenschein{

    int Ntops;
    int Nleptons;
    float mtt;
}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPHero::SetupSonnenschein() {

    //======SETUP CUTFLOW==========================================================================
    _cutFlow.insert(pair<string,double>("00_2Leps", 0) );
    _cutFlow.insert(pair<string,double>("01_2OSpairs", 0) );
    _cutFlow.insert(pair<string,double>("02_TwoLepOS", 0) );
    _cutFlow.insert(pair<string,double>("03_MET_Filters", 0) );
    _cutFlow.insert(pair<string,double>("04_HEM_Filter", 0) );
    _cutFlow.insert(pair<string,double>("05_Jets", 0) );
    _cutFlow.insert(pair<string,double>("06_MET", 0) );


    //======SETUP HISTOGRAMS=======================================================================
    //makeHist( "histogram1DName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    //sys_regions = { 0, 1, 2 }; [example] // Choose regions as defined in RegionID. Empty vector means that all events will be used.
    //makeSysHist( "histogram1DSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeSysHist( "histogram2DSysName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP OUTPUT BRANCHES==================================================================
    //_outputTree->Branch("variable1NameInTheTree", &Sonnenschein::variable1Name );  [example]

    //======SETUP INFORMATION IN OUTPUT HDF5 FILE==================================================
    HDF_insert("Ntops", &Sonnenschein::Ntops );
    HDF_insert("Nleptons", &Sonnenschein::Nleptons );
    HDF_insert("mtt", &Sonnenschein::mtt );
    HDF_insert("ttbar_reco", &ttbar_reco );
    HDF_insert("ttbar_score", &ttbar_score );
    HDF_insert("ttbar_mass", &ttbar_mass );
    HDF_insert("ttbar_reco_v2", &ttbar_reco_v2 );
    HDF_insert("ttbar_score_v2", &ttbar_score_v2 );
    HDF_insert("ttbar_mass_v2", &ttbar_mass_v2 );


    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPHero::SonnenscheinRegion() {

    vector<int> tops;
    vector<int> leptons;
    for( unsigned int ipart = 0; ipart < nGenPart; ++ipart ) {
        if( (abs(GenPart_pdgId[ipart]) == 6) && (abs(GenPart_pdgId[GenPart_genPartIdxMother[ipart]]) != 6) ){
            tops.push_back(ipart);
        }
        if( ((abs(GenPart_pdgId[ipart]) == 11) || (abs(GenPart_pdgId[ipart]) == 13)) && (abs(GenPart_pdgId[GenPart_genPartIdxMother[ipart]]) == 24) ){
            leptons.push_back(ipart);
        }
    }
    Sonnenschein::Ntops = tops.size();
    Sonnenschein::Nleptons = leptons.size();

    //-------------------------------------------------------------------------
    // 2 electrons, 2 muons, or 1 electron and 1 muon
    //-------------------------------------------------------------------------
    if( !(Sonnenschein::Nleptons == 2) ) return false;
    _cutFlow.at("00_2Leps") += 1;

    int prod_tops_sign = GenPart_pdgId[tops[0]]*GenPart_pdgId[tops[1]];
    int prod_leps_sign = GenPart_pdgId[leptons[0]]*GenPart_pdgId[leptons[1]];

    //-------------------------------------------------------------------------
    // 2 OS leptons and 2 OS tops
    //-------------------------------------------------------------------------
    if( !((prod_tops_sign < 0) && (prod_leps_sign < 0)) ) return false;
    _cutFlow.at("01_2OSpairs") += 1;


    Sonnenschein::mtt = 0;
    if( tops.size() == 2 ){
        TLorentzVector top1;
        TLorentzVector top2;
        top1.SetPtEtaPhiM(GenPart_pt[tops[0]], GenPart_eta[tops[0]], GenPart_phi[tops[0]], GenPart_mass[tops[0]]);
        top2.SetPtEtaPhiM(GenPart_pt[tops[1]], GenPart_eta[tops[1]], GenPart_phi[tops[1]], GenPart_mass[tops[1]]);

        TLorentzVector tt = top1 + top2;
        Sonnenschein::mtt = tt.M();
    }

    LeptonSelection();

    if( !(RecoLepID < 2000) ) return false;
    _cutFlow.at("02_TwoLepOS") += 1;

    JetSelection();
    METCorrection();

    if( !METFilters() ) return false;
    _cutFlow.at("03_MET_Filters") += 1;

    HEMissue();

    if( !HEM_filter ) return false;
    _cutFlow.at("04_HEM_Filter") += 1;

    if( !((Njets >= 2) && (Nbjets >= 1)) ) return false;
    _cutFlow.at("05_Jets") += 1;

    if( !(MET_pt > 30) ) return false;
    _cutFlow.at("06_MET") += 1;

    Get_Leptonic_Info(true, false);

    Get_ttbar_Variables();

    return true;
}


//-------------------------------------------------------------------------------------------------
// Write your analysis code here
//-------------------------------------------------------------------------------------------------
void HEPHero::SonnenscheinSelection() {











    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //Sonnenschein::variable1Name = 100;      [Example]

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
void HEPHero::SonnenscheinSystematic() {

    //FillSystematic( "histogram1DSysName", var, evtWeight );  [Example]
    //FillSystematic( "histogram2DSysName", var1, var2, evtWeight );  [Example]
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPHero::FinishSonnenschein() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
