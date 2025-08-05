#include "HEPHero.h"

//-------------------------------------------------------------------------------------------------
// Description:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace Sonnenschein{

    int Ntops;
    int Nbquarks;
    int Nleptons;
    int Nneutrinos;
    float mtt;
    float neutrino_E;
    float antineutrino_E;
    int Nnu_positive;
    int Nnu_negative;

    float lbbar_mass;
    float alb_mass;
    float drMin_b;
    float drMin_bbar;
    float drMin_l;
    float drMin_al;
    float ratio_l_E;
    float ratio_al_E;
    float ratio_b_E;
    float ratio_bbar_E;
    float ratio_l_pt;
    float ratio_al_pt;
    float ratio_b_pt;
    float ratio_bbar_pt;
    float diff_l_eta;
    float diff_al_eta;
    float diff_b_eta;
    float diff_bbar_eta;
    float diff_l_phi;
    float diff_al_phi;
    float diff_b_phi;
    float diff_bbar_phi;

    float lbbar_MET_mt;
    float alb_MET_mt;
    float ratio_MET_pt;
    float diff_MET_phi;

    float reco_l_pt;
    float reco_b_pt;
    float reco_MET_pt;
    
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
    _cutFlow.insert(pair<string,double>("07_Jet_Match", 0) );
    _cutFlow.insert(pair<string,double>("08_Lep_Match", 0) );


    //======SETUP HISTOGRAMS=======================================================================
    makeHist( "ttbar_mass", 140, 300., 1000., "mtt [GeV]", "events" ); 
    makeHist( "mtt", 140, 300., 1000., "mtt [GeV]", "events" );
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    //sys_regions = { 0, 1, 2 }; [example] // Choose regions as defined in RegionID. Empty vector means that all events will be used.
    //makeSysHist( "histogram1DSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeSysHist( "histogram2DSysName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP OUTPUT BRANCHES==================================================================
    //_outputTree->Branch("variable1NameInTheTree", &Sonnenschein::variable1Name );  [example]

    //======SETUP INFORMATION IN OUTPUT HDF5 FILE==================================================
    HDF_insert("Ntops", &Sonnenschein::Ntops );
    HDF_insert("Nbquarks", &Sonnenschein::Nbquarks );
    HDF_insert("Nleptons", &Sonnenschein::Nleptons );
    HDF_insert("Nneutrinos", &Sonnenschein::Nneutrinos );
    HDF_insert("mtt", &Sonnenschein::mtt );
    HDF_insert("ttbar_reco", &ttbar_reco );
    HDF_insert("ttbar_score", &ttbar_score );
    HDF_insert("ttbar_mass", &ttbar_mass );
    HDF_insert("ttbar_reco_v2", &ttbar_reco_v2 );
    HDF_insert("ttbar_score_v2", &ttbar_score_v2 );
    HDF_insert("ttbar_mass_v2", &ttbar_mass_v2 );
    HDF_insert("neutrino_E", &Sonnenschein::neutrino_E );
    HDF_insert("antineutrino_E", &Sonnenschein::antineutrino_E );
    //HDF_insert("Nnu_positive", &Sonnenschein::Nnu_positive );
    //HDF_insert("Nnu_negative", &Sonnenschein::Nnu_negative );

    HDF_insert("lbbar_mass", &Sonnenschein::lbbar_mass );
    HDF_insert("alb_mass", &Sonnenschein::alb_mass );
    HDF_insert("drMin_b", &Sonnenschein::drMin_b );
    HDF_insert("drMin_bbar", &Sonnenschein::drMin_bbar );
    HDF_insert("drMin_l", &Sonnenschein::drMin_l );
    HDF_insert("drMin_al", &Sonnenschein::drMin_al );
    HDF_insert("ratio_l_E", &Sonnenschein::ratio_l_E );
    HDF_insert("ratio_al_E", &Sonnenschein::ratio_al_E );
    HDF_insert("ratio_b_E", &Sonnenschein::ratio_b_E );
    HDF_insert("ratio_bbar_E", &Sonnenschein::ratio_bbar_E );
    HDF_insert("ratio_l_pt", &Sonnenschein::ratio_l_pt );
    HDF_insert("ratio_al_pt", &Sonnenschein::ratio_al_pt );
    HDF_insert("ratio_b_pt", &Sonnenschein::ratio_b_pt );
    HDF_insert("ratio_bbar_pt", &Sonnenschein::ratio_bbar_pt );
    HDF_insert("diff_l_eta", &Sonnenschein::diff_l_eta );
    HDF_insert("diff_al_eta", &Sonnenschein::diff_al_eta );
    HDF_insert("diff_b_eta", &Sonnenschein::diff_b_eta );
    HDF_insert("diff_bbar_eta", &Sonnenschein::diff_bbar_eta );
    HDF_insert("diff_l_phi", &Sonnenschein::diff_l_phi );
    HDF_insert("diff_al_phi", &Sonnenschein::diff_al_phi );
    HDF_insert("diff_b_phi", &Sonnenschein::diff_b_phi );
    HDF_insert("diff_bbar_phi", &Sonnenschein::diff_bbar_phi );

    HDF_insert("lbbar_MET_mt", &Sonnenschein::lbbar_MET_mt );
    HDF_insert("alb_MET_mt", &Sonnenschein::alb_MET_mt );
    HDF_insert("ratio_MET_pt", &Sonnenschein::ratio_MET_pt );
    HDF_insert("diff_MET_phi", &Sonnenschein::diff_MET_phi );

    HDF_insert("reco_l_pt", &Sonnenschein::reco_l_pt );
    HDF_insert("reco_b_pt", &Sonnenschein::reco_b_pt );
    HDF_insert("reco_MET_pt", &Sonnenschein::reco_MET_pt );


    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPHero::SonnenscheinRegion() {

    
    vector<int> tops;
    vector<int> bquarks;
    vector<int> leptons;
    vector<int> neutrinos;
    for( unsigned int ipart = 0; ipart < nGenPart; ++ipart ) {
        if( (abs(GenPart_pdgId[ipart]) == 6) && (abs(GenPart_pdgId[GenPart_genPartIdxMother[ipart]]) != 6) ){
            tops.push_back(ipart);
        }
        else if( (abs(GenPart_pdgId[ipart]) == 5) && (abs(GenPart_pdgId[GenPart_genPartIdxMother[ipart]]) != 5) ){
            bquarks.push_back(ipart);
        }
        else if( ((abs(GenPart_pdgId[ipart]) == 11) || (abs(GenPart_pdgId[ipart]) == 13)) && (abs(GenPart_pdgId[GenPart_genPartIdxMother[ipart]]) == 24) ){
            leptons.push_back(ipart);
        }
        else if( ((abs(GenPart_pdgId[ipart]) == 12) || (abs(GenPart_pdgId[ipart]) == 14)) && (abs(GenPart_pdgId[GenPart_genPartIdxMother[ipart]]) == 24) ){
            neutrinos.push_back(ipart);
        }
    }
    Sonnenschein::Ntops = tops.size();
    Sonnenschein::Nbquarks = bquarks.size();
    Sonnenschein::Nleptons = leptons.size();
    Sonnenschein::Nneutrinos = neutrinos.size();

    //-------------------------------------------------------------------------
    // (2 electrons, 2 muons, or 1 electron and 1 muon) and 2 neutrinos
    //-------------------------------------------------------------------------
    if( !(Sonnenschein::Nleptons == 2) || !(Sonnenschein::Nneutrinos == 2) || !(Sonnenschein::Nbquarks == 2) ) return false;
    _cutFlow.at("00_2Leps") += 1;

    int prod_tops_sign = GenPart_pdgId[tops[0]]*GenPart_pdgId[tops[1]];
    int prod_leps_sign = GenPart_pdgId[leptons[0]]*GenPart_pdgId[leptons[1]];
    int prod_nus_sign = GenPart_pdgId[neutrinos[0]]*GenPart_pdgId[neutrinos[1]];
    int prod_bs_sign = GenPart_pdgId[bquarks[0]]*GenPart_pdgId[bquarks[1]];

    //-------------------------------------------------------------------------
    // 2 OS leptons and 2 OS tops
    //-------------------------------------------------------------------------
    if( !((prod_tops_sign < 0) && (prod_leps_sign < 0) && (prod_nus_sign < 0) && (prod_bs_sign < 0)) ) return false;
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

    if( !((RecoLepID > 0) && (RecoLepID < 2000)) ) return false;
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

    
    //-------------------------------------------------------------------------
    // Neutrino energies
    //-------------------------------------------------------------------------
    Sonnenschein::Nnu_positive = 0;
    Sonnenschein::Nnu_negative = 0;
    TLorentzVector neutrino;
    TLorentzVector antineutrino;
    for( unsigned int inu = 0; inu < neutrinos.size(); ++inu ) {
        unsigned int ipart = neutrinos.at(inu);
        if( GenPart_pdgId[ipart] > 0 ){
            Sonnenschein::Nnu_positive += 1;
            neutrino.SetPtEtaPhiM(GenPart_pt[ipart], GenPart_eta[ipart], GenPart_phi[ipart], GenPart_mass[ipart]); 
            Sonnenschein::neutrino_E = neutrino.E();
        }else{
            Sonnenschein::Nnu_negative += 1;
            antineutrino.SetPtEtaPhiM(GenPart_pt[ipart], GenPart_eta[ipart], GenPart_phi[ipart], GenPart_mass[ipart]); 
            Sonnenschein::antineutrino_E = antineutrino.E();
        };
    }

    
    //-------------------------------------------------------------------------
    // b*al and bbar*l masses
    //-------------------------------------------------------------------------
    int l_id;
    int al_id;
    for( unsigned int ilep = 0; ilep < leptons.size(); ++ilep ) {
        unsigned int ipart = leptons.at(ilep);
        if( GenPart_pdgId[ipart] > 0 ){
            l_id = ipart;
        }else{
            al_id = ipart;
        }
    }

    int b_id;
    int bbar_id;
    for( unsigned int ib = 0; ib < bquarks.size(); ++ib ) {
        unsigned int ipart = bquarks.at(ib);
        if( GenPart_pdgId[ipart] > 0 ){
            b_id = ipart;
        }else{
            bbar_id = ipart;
        }
    }

    TLorentzVector l_TLV;
    TLorentzVector al_TLV;
    TLorentzVector b_TLV;
    TLorentzVector bbar_TLV;
    l_TLV.SetPtEtaPhiM(GenPart_pt[l_id], GenPart_eta[l_id], GenPart_phi[l_id], GenPart_mass[l_id]);
    al_TLV.SetPtEtaPhiM(GenPart_pt[al_id], GenPart_eta[al_id], GenPart_phi[al_id], GenPart_mass[al_id]);
    b_TLV.SetPtEtaPhiM(GenPart_pt[b_id], GenPart_eta[b_id], GenPart_phi[b_id], GenPart_mass[b_id]);
    bbar_TLV.SetPtEtaPhiM(GenPart_pt[bbar_id], GenPart_eta[bbar_id], GenPart_phi[bbar_id], GenPart_mass[bbar_id]);

    TLorentzVector lbbar_TLV = l_TLV + bbar_TLV;
    TLorentzVector alb_TLV = al_TLV + b_TLV;;
    Sonnenschein::lbbar_mass = lbbar_TLV.M();
    Sonnenschein::alb_mass = alb_TLV.M();

    TLorentzVector MET_TLV = neutrino + antineutrino;
    Sonnenschein::lbbar_MET_mt = sqrt( 2*lbbar_TLV.Pt()*MET_TLV.Pt()*(1 - cos(MET_TLV.DeltaPhi(lbbar_TLV))) ) ;
    Sonnenschein::alb_MET_mt = sqrt( 2*alb_TLV.Pt()*MET_TLV.Pt()*(1 - cos(MET_TLV.DeltaPhi(alb_TLV))) ) ;
    

    //-------------------------------------------------------------------------
    // Reco-true matches
    //-------------------------------------------------------------------------
    int JetID_b = -1;
    int JetID_bbar = -1;
    Sonnenschein::drMin_b = 99999.;
    Sonnenschein::drMin_bbar = 99999.;
    for( unsigned int iseljet = 0; iseljet < selectedJet.size(); ++iseljet ) {
        int ijet = selectedJet.at(iseljet);

        double deta_b = fabs(GenPart_eta[b_id] - Jet_eta[ijet]);
        double dphi_b = fabs(GenPart_phi[b_id] - Jet_phi[ijet]);
        if( dphi_b > M_PI ) dphi_b = 2*M_PI - dphi_b;
        double dr_b = sqrt( deta_b*deta_b + dphi_b*dphi_b );
        if( dr_b < Sonnenschein::drMin_b ){
            Sonnenschein::drMin_b = dr_b;
            JetID_b = ijet;
        }
        
        double deta_bbar = fabs(GenPart_eta[bbar_id] - Jet_eta[ijet]);
        double dphi_bbar = fabs(GenPart_phi[bbar_id] - Jet_phi[ijet]);
        if( dphi_bbar > M_PI ) dphi_bbar = 2*M_PI - dphi_bbar;
        double dr_bbar = sqrt( deta_bbar*deta_bbar + dphi_bbar*dphi_bbar );
        if( dr_bbar < Sonnenschein::drMin_bbar ){
            Sonnenschein::drMin_bbar = dr_bbar;
            JetID_bbar = ijet;
        }
    }
    if( (Sonnenschein::drMin_b > 1) || (Sonnenschein::drMin_bbar > 1) || (JetID_b == JetID_bbar) ) return false;
    _cutFlow.at("07_Jet_Match") += 1;
    
    
    int LepID_l = -1;
    int LepID_al = -1;
    Sonnenschein::drMin_l = 99999.;
    Sonnenschein::drMin_al = 99999.;
    if( (GenPart_pdgId[l_id] == 11) && (GenPart_pdgId[al_id] == -11) ){
        for( unsigned int isellep = 0; isellep < selectedEle.size(); ++isellep ) {
            int ilep = selectedEle.at(isellep);
    
            double deta_l = fabs(GenPart_eta[l_id] - Electron_eta[ilep]);
            double dphi_l = fabs(GenPart_phi[l_id] - Electron_phi[ilep]);
            if( dphi_l > M_PI ) dphi_l = 2*M_PI - dphi_l;
            double dr_l = sqrt( deta_l*deta_l + dphi_l*dphi_l );
            if( dr_l < Sonnenschein::drMin_l ){
                Sonnenschein::drMin_l = dr_l;
                LepID_l = ilep;
            }
            
            double deta_al = fabs(GenPart_eta[al_id] - Electron_eta[ilep]);
            double dphi_al = fabs(GenPart_phi[al_id] - Electron_phi[ilep]);
            if( dphi_al > M_PI ) dphi_al = 2*M_PI - dphi_al;
            double dr_al = sqrt( deta_al*deta_al + dphi_al*dphi_al );
            if( dr_al < Sonnenschein::drMin_al ){
                Sonnenschein::drMin_al = dr_al;
                LepID_al = ilep;
            }
        }
    }
    else if( (GenPart_pdgId[l_id] == 13) && (GenPart_pdgId[al_id] == -13) ){
        for( unsigned int isellep = 0; isellep < selectedMu.size(); ++isellep ) {
            int ilep = selectedMu.at(isellep);
    
            double deta_l = fabs(GenPart_eta[l_id] - Muon_eta[ilep]);
            double dphi_l = fabs(GenPart_phi[l_id] - Muon_phi[ilep]);
            if( dphi_l > M_PI ) dphi_l = 2*M_PI - dphi_l;
            double dr_l = sqrt( deta_l*deta_l + dphi_l*dphi_l );
            if( dr_l < Sonnenschein::drMin_l ){
                Sonnenschein::drMin_l = dr_l;
                LepID_l = ilep;
            }
            
            double deta_al = fabs(GenPart_eta[al_id] - Muon_eta[ilep]);
            double dphi_al = fabs(GenPart_phi[al_id] - Muon_phi[ilep]);
            if( dphi_al > M_PI ) dphi_al = 2*M_PI - dphi_al;
            double dr_al = sqrt( deta_al*deta_al + dphi_al*dphi_al );
            if( dr_al < Sonnenschein::drMin_al ){
                Sonnenschein::drMin_al = dr_al;
                LepID_al = ilep;
            }
        }
    }
    else if( (GenPart_pdgId[l_id] == 11) && (GenPart_pdgId[al_id] == -13) ){
        for( unsigned int isellep = 0; isellep < selectedEle.size(); ++isellep ) {
            int ilep = selectedEle.at(isellep);
    
            double deta_l = fabs(GenPart_eta[l_id] - Electron_eta[ilep]);
            double dphi_l = fabs(GenPart_phi[l_id] - Electron_phi[ilep]);
            if( dphi_l > M_PI ) dphi_l = 2*M_PI - dphi_l;
            double dr_l = sqrt( deta_l*deta_l + dphi_l*dphi_l );
            if( dr_l < Sonnenschein::drMin_l ){
                Sonnenschein::drMin_l = dr_l;
                LepID_l = ilep;
            }
        }

        for( unsigned int isellep = 0; isellep < selectedMu.size(); ++isellep ) {
            int ilep = selectedMu.at(isellep);
            
            double deta_al = fabs(GenPart_eta[al_id] - Muon_eta[ilep]);
            double dphi_al = fabs(GenPart_phi[al_id] - Muon_phi[ilep]);
            if( dphi_al > M_PI ) dphi_al = 2*M_PI - dphi_al;
            double dr_al = sqrt( deta_al*deta_al + dphi_al*dphi_al );
            if( dr_al < Sonnenschein::drMin_al ){
                Sonnenschein::drMin_al = dr_al;
                LepID_al = ilep;
            }
        }
    }
    else if( (GenPart_pdgId[l_id] == 13) && (GenPart_pdgId[al_id] == -11) ){
        for( unsigned int isellep = 0; isellep < selectedMu.size(); ++isellep ) {
            int ilep = selectedMu.at(isellep);
    
            double deta_l = fabs(GenPart_eta[l_id] - Muon_eta[ilep]);
            double dphi_l = fabs(GenPart_phi[l_id] - Muon_phi[ilep]);
            if( dphi_l > M_PI ) dphi_l = 2*M_PI - dphi_l;
            double dr_l = sqrt( deta_l*deta_l + dphi_l*dphi_l );
            if( dr_l < Sonnenschein::drMin_l ){
                Sonnenschein::drMin_l = dr_l;
                LepID_l = ilep;
            }
        }

        for( unsigned int isellep = 0; isellep < selectedEle.size(); ++isellep ) {
            int ilep = selectedEle.at(isellep);
            
            double deta_al = fabs(GenPart_eta[al_id] - Electron_eta[ilep]);
            double dphi_al = fabs(GenPart_phi[al_id] - Electron_phi[ilep]);
            if( dphi_al > M_PI ) dphi_al = 2*M_PI - dphi_al;
            double dr_al = sqrt( deta_al*deta_al + dphi_al*dphi_al );
            if( dr_al < Sonnenschein::drMin_al ){
                Sonnenschein::drMin_al = dr_al;
                LepID_al = ilep;
            }
        }
    }
    if( (Sonnenschein::drMin_l > 0.05) || (Sonnenschein::drMin_al > 0.05) || ((abs(GenPart_pdgId[l_id]) == abs(GenPart_pdgId[al_id])) && (LepID_l == LepID_al)) ) return false;
    _cutFlow.at("08_Lep_Match") += 1;


    //-------------------------------------------------------------------------
    // Resolutions
    //-------------------------------------------------------------------------

    // Jets
    TLorentzVector Jet_b_TLV;
    Jet_b_TLV.SetPtEtaPhiM(Jet_pt[JetID_b], Jet_eta[JetID_b], Jet_phi[JetID_b], Jet_mass[JetID_b]);
    Sonnenschein::ratio_b_E = b_TLV.E()/Jet_b_TLV.E();
    Sonnenschein::ratio_b_pt = b_TLV.Pt()/Jet_b_TLV.Pt();
    TLorentzVector Jet_bbar_TLV;
    Jet_bbar_TLV.SetPtEtaPhiM(Jet_pt[JetID_bbar], Jet_eta[JetID_bbar], Jet_phi[JetID_bbar], Jet_mass[JetID_bbar]);
    Sonnenschein::ratio_bbar_E = bbar_TLV.E()/Jet_bbar_TLV.E();
    Sonnenschein::ratio_bbar_pt = bbar_TLV.Pt()/Jet_bbar_TLV.Pt();
    
    Sonnenschein::diff_b_eta = abs(GenPart_eta[b_id] - Jet_eta[JetID_b]);
    Sonnenschein::diff_bbar_eta = abs(GenPart_eta[bbar_id] - Jet_eta[JetID_bbar]);
    
    Sonnenschein::diff_b_phi = abs(GenPart_phi[b_id] - Jet_phi[JetID_b]);
    Sonnenschein::diff_bbar_phi = abs(GenPart_phi[bbar_id] - Jet_phi[JetID_bbar]);

    // Leptons
    TLorentzVector Lep_l_TLV;
    TLorentzVector Lep_al_TLV;
    if( (GenPart_pdgId[l_id] == 11) && (GenPart_pdgId[al_id] == -11) ){
        Lep_l_TLV.SetPtEtaPhiM(Electron_pt[LepID_l], Electron_eta[LepID_l], Electron_phi[LepID_l], Electron_mass[LepID_l]);
        Sonnenschein::ratio_l_E = l_TLV.E()/Lep_l_TLV.E();
        Sonnenschein::ratio_l_pt = l_TLV.Pt()/Lep_l_TLV.Pt();
        Lep_al_TLV.SetPtEtaPhiM(Electron_pt[LepID_al], Electron_eta[LepID_al], Electron_phi[LepID_al], Electron_mass[LepID_al]);
        Sonnenschein::ratio_al_E = al_TLV.E()/Lep_al_TLV.E();
        Sonnenschein::ratio_al_pt = al_TLV.Pt()/Lep_al_TLV.Pt();
        
        Sonnenschein::diff_l_eta = abs(GenPart_eta[l_id] - Electron_eta[LepID_l]);
        Sonnenschein::diff_al_eta = abs(GenPart_eta[al_id] - Electron_eta[LepID_al]);
        
        Sonnenschein::diff_l_phi = abs(GenPart_phi[l_id] - Electron_phi[LepID_l]);
        Sonnenschein::diff_al_phi = abs(GenPart_phi[al_id] - Electron_phi[LepID_al]);
    }else if( (GenPart_pdgId[l_id] == 13) && (GenPart_pdgId[al_id] == -13) ){
        Lep_l_TLV.SetPtEtaPhiM(Muon_pt[LepID_l], Muon_eta[LepID_l], Muon_phi[LepID_l], Muon_mass[LepID_l]);
        Sonnenschein::ratio_l_E = l_TLV.E()/Lep_l_TLV.E();
        Sonnenschein::ratio_l_pt = l_TLV.Pt()/Lep_l_TLV.Pt();
        Lep_al_TLV.SetPtEtaPhiM(Muon_pt[LepID_al], Muon_eta[LepID_al], Muon_phi[LepID_al], Muon_mass[LepID_al]);
        Sonnenschein::ratio_al_E = al_TLV.E()/Lep_al_TLV.E();
        Sonnenschein::ratio_al_pt = al_TLV.Pt()/Lep_al_TLV.Pt();
        
        Sonnenschein::diff_l_eta = abs(GenPart_eta[l_id] - Muon_eta[LepID_l]);
        Sonnenschein::diff_al_eta = abs(GenPart_eta[al_id] - Muon_eta[LepID_al]);
        
        Sonnenschein::diff_l_phi = abs(GenPart_phi[l_id] - Muon_phi[LepID_l]);
        Sonnenschein::diff_al_phi = abs(GenPart_phi[al_id] - Muon_phi[LepID_al]);
    }else if( (GenPart_pdgId[l_id] == 11) && (GenPart_pdgId[al_id] == -13) ){
        Lep_l_TLV.SetPtEtaPhiM(Electron_pt[LepID_l], Electron_eta[LepID_l], Electron_phi[LepID_l], Electron_mass[LepID_l]);
        Sonnenschein::ratio_l_E = l_TLV.E()/Lep_l_TLV.E();
        Sonnenschein::ratio_l_pt = l_TLV.Pt()/Lep_l_TLV.Pt();
        Lep_al_TLV.SetPtEtaPhiM(Muon_pt[LepID_al], Muon_eta[LepID_al], Muon_phi[LepID_al], Muon_mass[LepID_al]);
        Sonnenschein::ratio_al_E = al_TLV.E()/Lep_al_TLV.E();
        Sonnenschein::ratio_al_pt = al_TLV.Pt()/Lep_al_TLV.Pt();
        
        Sonnenschein::diff_l_eta = abs(GenPart_eta[l_id] - Electron_eta[LepID_l]);
        Sonnenschein::diff_al_eta = abs(GenPart_eta[al_id] - Muon_eta[LepID_al]);
        
        Sonnenschein::diff_l_phi = abs(GenPart_phi[l_id] - Electron_phi[LepID_l]);
        Sonnenschein::diff_al_phi = abs(GenPart_phi[al_id] - Muon_phi[LepID_al]);
    }else if( (GenPart_pdgId[l_id] == 13) && (GenPart_pdgId[al_id] == -11) ){
        Lep_l_TLV.SetPtEtaPhiM(Muon_pt[LepID_l], Muon_eta[LepID_l], Muon_phi[LepID_l], Muon_mass[LepID_l]);
        Sonnenschein::ratio_l_E = l_TLV.E()/Lep_l_TLV.E();
        Sonnenschein::ratio_l_pt = l_TLV.Pt()/Lep_l_TLV.Pt();
        Lep_al_TLV.SetPtEtaPhiM(Electron_pt[LepID_al], Electron_eta[LepID_al], Electron_phi[LepID_al], Electron_mass[LepID_al]);
        Sonnenschein::ratio_al_E = al_TLV.E()/Lep_al_TLV.E();
        Sonnenschein::ratio_al_pt = al_TLV.Pt()/Lep_al_TLV.Pt();
        
        Sonnenschein::diff_l_eta = abs(GenPart_eta[l_id] - Muon_eta[LepID_l]);
        Sonnenschein::diff_al_eta = abs(GenPart_eta[al_id] - Electron_eta[LepID_al]);
        
        Sonnenschein::diff_l_phi = abs(GenPart_phi[l_id] - Muon_phi[LepID_l]);
        Sonnenschein::diff_al_phi = abs(GenPart_phi[al_id] - Electron_phi[LepID_al]);
    }

    // MET   
    Sonnenschein::ratio_MET_pt = MET_TLV.Pt()/MET_pt;
    Sonnenschein::diff_MET_phi = abs(MET_TLV.Phi() - MET_phi);
    if( Sonnenschein::diff_MET_phi > M_PI ) Sonnenschein::diff_MET_phi = 2*M_PI - Sonnenschein::diff_MET_phi;

    // Pt
    Sonnenschein::reco_b_pt = Jet_b_TLV.Pt();
    Sonnenschein::reco_l_pt = Lep_l_TLV.Pt();
    Sonnenschein::reco_MET_pt = MET_pt;

    _histograms1D.at("ttbar_mass").Fill( ttbar_mass, evtWeight );
    _histograms1D.at("mtt").Fill( Sonnenschein::mtt, evtWeight );

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
