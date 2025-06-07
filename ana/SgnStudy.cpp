#include "HEPHero.h"

//-------------------------------------------------------------------------------------------------
// Description:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace SgnStudy{

    int Ntops;
    int Nleptons;
    float mtt;
    float chel;

    float test1Weight;
    float test2Weight;
    float test3Weight;
    vector<float> eftWeights;

}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPHero::SetupSgnStudy() {

    //======SETUP CUTFLOW==========================================================================
    _cutFlow.insert(pair<string,double>("0_2Leps", 0) );
    _cutFlow.insert(pair<string,double>("1_2OSpairs", 0) );

    //======SETUP HISTOGRAMS=======================================================================
    //makeHist( "histogram1DName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    //sys_regions = { 0, 1, 2 }; [example] // Choose regions as defined in RegionID. Empty vector means that all events will be used.
    //makeSysHist( "histogram1DSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeSysHist( "histogram2DSysName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP OUTPUT BRANCHES==================================================================
    //_outputTree->Branch("variable1NameInTheTree", &SgnStudy::variable1Name );  [example]

    //======SETUP INFORMATION IN OUTPUT HDF5 FILE==================================================
    HDF_insert("genWeight", &genWeight );
    HDF_insert("Ntops", &SgnStudy::Ntops );
    HDF_insert("Nleptons", &SgnStudy::Nleptons );
    HDF_insert("mtt", &SgnStudy::mtt );
    HDF_insert("chel", &SgnStudy::chel );
    HDF_insert("nLHEReweightingWeight", &nLHEReweightingWeight );

    HDF_insert("test1Weight", &SgnStudy::test1Weight );
    HDF_insert("test2Weight", &SgnStudy::test2Weight );
    HDF_insert("test3Weight", &SgnStudy::test3Weight );
    HDF_insert("eftWeights", &SgnStudy::eftWeights );


    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPHero::SgnStudyRegion() {

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
void HEPHero::SgnStudySelection() {

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
    SgnStudy::Ntops = tops.size();
    SgnStudy::Nleptons = leptons.size();

    //-------------------------------------------------------------------------
    // 2 electrons, 2 muons, or 1 electron and 1 muon
    //-------------------------------------------------------------------------
    if( !(SgnStudy::Nleptons == 2) ) return;
    _cutFlow.at("0_2Leps") += 1;

    int prod_tops_sign = GenPart_pdgId[tops[0]]*GenPart_pdgId[tops[1]];
    int prod_leps_sign = GenPart_pdgId[leptons[0]]*GenPart_pdgId[leptons[1]];

    //-------------------------------------------------------------------------
    // 2 OS leptons and 2 OS tops
    //-------------------------------------------------------------------------
    if( !((prod_tops_sign < 0) && (prod_leps_sign < 0)) ) return;
    _cutFlow.at("1_2OSpairs") += 1;


    SgnStudy::mtt = 0;
    if( tops.size() == 2 ){
        TLorentzVector top1;
        TLorentzVector top2;
        top1.SetPtEtaPhiM(GenPart_pt[tops[0]], GenPart_eta[tops[0]], GenPart_phi[tops[0]], GenPart_mass[tops[0]]);
        top2.SetPtEtaPhiM(GenPart_pt[tops[1]], GenPart_eta[tops[1]], GenPart_phi[tops[1]], GenPart_mass[tops[1]]);

        TLorentzVector tt = top1 + top2;
        SgnStudy::mtt = tt.M();
    }

    float pTop_pt, pTop_eta, pTop_phi, pTop_m;
    float aTop_pt, aTop_eta, aTop_phi, aTop_m;
    float pLep_pt, pLep_eta, pLep_phi, pLep_m;
    float aLep_pt, aLep_eta, aLep_phi, aLep_m;
    if( GenPart_pdgId[tops[0]] > 0 ){
        pTop_pt = GenPart_pt[tops[0]]; pTop_eta = GenPart_eta[tops[0]]; pTop_phi = GenPart_phi[tops[0]]; pTop_m = GenPart_mass[tops[0]];
        aTop_pt = GenPart_pt[tops[1]]; aTop_eta = GenPart_eta[tops[1]]; aTop_phi = GenPart_phi[tops[1]]; aTop_m = GenPart_mass[tops[1]];
    }else{
        pTop_pt = GenPart_pt[tops[1]]; pTop_eta = GenPart_eta[tops[1]]; pTop_phi = GenPart_phi[tops[1]]; pTop_m = GenPart_mass[tops[1]];
        aTop_pt = GenPart_pt[tops[0]]; aTop_eta = GenPart_eta[tops[0]]; aTop_phi = GenPart_phi[tops[0]]; aTop_m = GenPart_mass[tops[0]];
    }
    if( GenPart_pdgId[leptons[0]] > 0 ){
        pLep_pt = GenPart_pt[leptons[0]]; pLep_eta = GenPart_eta[leptons[0]]; pLep_phi = GenPart_phi[leptons[0]]; pLep_m = GenPart_mass[leptons[0]];
        aLep_pt = GenPart_pt[leptons[1]]; aLep_eta = GenPart_eta[leptons[1]]; aLep_phi = GenPart_phi[leptons[1]]; aLep_m = GenPart_mass[leptons[1]];
    }else{
        pLep_pt = GenPart_pt[leptons[1]]; pLep_eta = GenPart_eta[leptons[1]]; pLep_phi = GenPart_phi[leptons[1]]; pLep_m = GenPart_mass[leptons[1]];
        aLep_pt = GenPart_pt[leptons[0]]; aLep_eta = GenPart_eta[leptons[0]]; aLep_phi = GenPart_phi[leptons[0]]; aLep_m = GenPart_mass[leptons[0]];
    }

    spin_corr = compute_spin_correlation(pTop_pt, pTop_eta, pTop_phi, pTop_m,
                                         aTop_pt, aTop_eta, aTop_phi, aTop_m,
                                         pLep_pt, pLep_eta, pLep_phi, pLep_m,
                                         aLep_pt, aLep_eta, aLep_phi, aLep_m);
    static const int icHel = index_with_key(spin_corr, "cHel");
    SgnStudy::chel = spin_corr[icHel].second;


    SgnStudy::test1Weight = 0;
    SgnStudy::test2Weight = 0;
    SgnStudy::test3Weight = 0;
    if( nLHEReweightingWeight == 354 ){
        SgnStudy::test1Weight = LHEReweightingWeight[152]; //EFTrwgt152
        SgnStudy::test2Weight = LHEReweightingWeight[27]; //EFTrwgt27
        SgnStudy::test3Weight = LHEReweightingWeight[103]; //EFTrwgt103
    }

    vector<int> basis_idx = {200, 201, 202, 203, 204, 207, 208, 209, 210, 211, 217, 218, 219, 220, 223, 224, 225, 226, 227, 233, 234, 235, 238, 239, 240, 241, 242, 248, 249, 252, 253, 254, 255, 256, 262, 265, 266, 267, 268, 269, 298, 299, 300, 301, 302, 308, 309, 310, 311, 317, 318, 319, 325, 326, 332};

    SgnStudy::eftWeights.clear();
    for( unsigned int iwgt = 0; iwgt < basis_idx.size(); ++iwgt ) {
        SgnStudy::eftWeights.push_back(LHEReweightingWeight[basis_idx[iwgt]]);
    }



    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //SgnStudy::variable1Name = 100;      [Example]

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
void HEPHero::SgnStudySystematic() {

    //FillSystematic( "histogram1DSysName", var, evtWeight );  [Example]
    //FillSystematic( "histogram2DSysName", var1, var2, evtWeight );  [Example]
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPHero::FinishSgnStudy() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
