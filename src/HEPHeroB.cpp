#include "HEPHero.h"


//-------------------------------------------------------------------------------------------------
// FILL CONTROL VARIABLES WITH INPUT FILE LINES
//-------------------------------------------------------------------------------------------------
void HEPHero::FillControlVariables( string key, string value){

    //----CORRECTIONS------------------------------------------------------------------------------
    if( key == "PILEUP_WGT"                 )   apply_pileup_wgt = ( atoi(value.c_str()) == 1 );
    if( key == "MET_XY_CORR"                )   apply_met_xy_corr = ( atoi(value.c_str()) == 1 );
    if( key == "JER_CORR"                   )   apply_jer_corr = ( atoi(value.c_str()) == 1 );
    if( key == "MUON_ROC_CORR"              )   apply_muon_roc_corr = ( atoi(value.c_str()) == 1 );

    //----METADATA FILES---------------------------------------------------------------------------
    if( key == "pileup"                     )   pileup_file = value;
    if( key == "met_xy"                     )   met_xy_file = value;
    if( key == "jerc"                       )   jerc_file = value;
    if( key == "jer_smear"                  )   jer_smear_file = value;
    if( key == "mu_RoccoR"                  )   muon_roc_file = value;

    //----SELECTION--------------------------------------------------------------------------------
    if( key == "JET_ETA_CUT"                )   JET_ETA_CUT = atof(value.c_str());
    if( key == "JET_PT_CUT"                 )   JET_PT_CUT = atof(value.c_str());
    if( key == "JET_ID_WP"                  )   JET_ID_WP = atoi(value.c_str());
    if( key == "JET_PUID_WP"                )   JET_PUID_WP = atoi(value.c_str());
    if( key == "JET_BTAG_WP"                )   JET_BTAG_WP = atoi(value.c_str());
    if( key == "JET_LEP_DR_ISO_CUT"         )   JET_LEP_DR_ISO_CUT = atof(value.c_str());

    if( key == "ELECTRON_GAP_LOWER_CUT"     )   ELECTRON_GAP_LOWER_CUT = atof(value.c_str());
    if( key == "ELECTRON_GAP_UPPER_CUT"     )   ELECTRON_GAP_UPPER_CUT = atof(value.c_str());
    if( key == "ELECTRON_ETA_CUT"           )   ELECTRON_ETA_CUT = atof(value.c_str());
    if( key == "ELECTRON_PT_CUT"            )   ELECTRON_PT_CUT = atof(value.c_str());
    if( key == "ELECTRON_ID_WP"             )   ELECTRON_ID_WP = atoi(value.c_str());

    if( key == "MUON_ETA_CUT"               )   MUON_ETA_CUT = atof(value.c_str());
    if( key == "MUON_PT_CUT"                )   MUON_PT_CUT = atof(value.c_str());
    if( key == "MUON_ID_WP"                 )   MUON_ID_WP = atoi(value.c_str());
    if( key == "MUON_ISO_WP"                )   MUON_ISO_WP = atoi(value.c_str());

    if( key == "LEADING_LEP_PT_CUT"         )   LEADING_LEP_PT_CUT = atof(value.c_str());
    if( key == "LEPLEP_PT_CUT"              )   LEPLEP_PT_CUT = atof(value.c_str());
    if( key == "MET_CUT"                    )   MET_CUT = atof(value.c_str());
    if( key == "LEPLEP_DR_CUT"              )   LEPLEP_DR_CUT = atof(value.c_str());
    if( key == "LEPLEP_DM_CUT"              )   LEPLEP_DM_CUT = atof(value.c_str());
    if( key == "MET_LEPLEP_DPHI_CUT"        )   MET_LEPLEP_DPHI_CUT = atof(value.c_str());
    if( key == "MET_LEPLEP_MT_CUT"          )   MET_LEPLEP_MT_CUT = atof(value.c_str());

}


//-------------------------------------------------------------------------------------------------
// Init
//-------------------------------------------------------------------------------------------------
bool HEPHero::Init() {
    
    //======SET HISTOGRAMS STYLE===================================================================
    setStyle(1.0,true,0.15);

    if( _ANALYSIS != "GEN" ){
        //======SET THE BRANCH ADDRESSES===========================================================
        _inputTree->SetBranchAddress("run", &run );
        _inputTree->SetBranchAddress("luminosityBlock", &luminosityBlock );
        _inputTree->SetBranchAddress("event", &event );

        /*
        _inputTree->SetBranchAddress("nFatJet", &nFatJet );
        _inputTree->SetBranchAddress("nFsrPhoton", &nFsrPhoton );
        _inputTree->SetBranchAddress("nGenJetAK8", &nGenJetAK8 );

        _inputTree->SetBranchAddress("nSubGenJetAK8", &nSubGenJetAK8 );
        _inputTree->SetBranchAddress("nGenVisTau", &nGenVisTau );
        _inputTree->SetBranchAddress("nLHEPdfWeight", &nLHEPdfWeight );
        _inputTree->SetBranchAddress("nLHEReweightingWeight", &nLHEReweightingWeight );
        _inputTree->SetBranchAddress("nLHEScaleWeight", &nLHEScaleWeight );
        _inputTree->SetBranchAddress("nPSWeight", &nPSWeight );
        _inputTree->SetBranchAddress("nIsoTrack", &nIsoTrack );
        _inputTree->SetBranchAddress("nLHEPart", &nLHEPart );
        _inputTree->SetBranchAddress("nPhoton", &nPhoton );
        _inputTree->SetBranchAddress("nGenDressedLepton", &nGenDressedLepton );
        _inputTree->SetBranchAddress("nGenIsolatedPhoton", &nGenIsolatedPhoton );
        _inputTree->SetBranchAddress("nSoftActivityJet", &nSoftActivityJet );
        _inputTree->SetBranchAddress("nSubJet", &nSubJet );
        _inputTree->SetBranchAddress("nTau", &nTau );
        _inputTree->SetBranchAddress("nTrigObj", &nTrigObj );
        _inputTree->SetBranchAddress("nOtherPV", &nOtherPV );
        _inputTree->SetBranchAddress("nSV", &nSV );
    */

        _inputTree->SetBranchAddress("fixedGridRhoFastjetAll", &fixedGridRhoFastjetAll );

        //-----------------------------------------------------------------------------------------
        _inputTree->SetBranchAddress("nElectron", &nElectron );
        _inputTree->SetBranchAddress("Electron_pt", &Electron_pt );
        _inputTree->SetBranchAddress("Electron_eta", &Electron_eta );
        _inputTree->SetBranchAddress("Electron_phi", &Electron_phi );
        _inputTree->SetBranchAddress("Electron_charge", &Electron_charge );
        _inputTree->SetBranchAddress("Electron_mass", &Electron_mass );
        _inputTree->SetBranchAddress("Electron_pdgId", &Electron_pdgId );
        _inputTree->SetBranchAddress("Electron_miniPFRelIso_all", &Electron_miniPFRelIso_all );
        _inputTree->SetBranchAddress("Electron_miniPFRelIso_chg", &Electron_miniPFRelIso_chg );
        _inputTree->SetBranchAddress("Electron_jetRelIso", &Electron_jetRelIso );
        _inputTree->SetBranchAddress("Electron_jetIdx", &Electron_jetIdx );
        _inputTree->SetBranchAddress("Electron_isPFcand", &Electron_isPFcand );
        _inputTree->SetBranchAddress("Electron_dxy", &Electron_dxy );
        _inputTree->SetBranchAddress("Electron_dxyErr", &Electron_dxyErr );
        _inputTree->SetBranchAddress("Electron_dz", &Electron_dz );
        _inputTree->SetBranchAddress("Electron_dzErr", &Electron_dzErr );
        _inputTree->SetBranchAddress("Electron_deltaEtaSC", &Electron_deltaEtaSC );

        _inputTree->SetBranchAddress("Electron_cutBased", &Electron_cutBased );
        _inputTree->SetBranchAddress("Electron_cutBased_HEEP", &Electron_cutBased_HEEP );
        //_inputTree->SetBranchAddress("Electron_cutBased_Fall17_V1", &Electron_cutBased_Fall17_V1 );
        //_inputTree->SetBranchAddress("Electron_mvaFall17V1Iso", &Electron_mvaFall17V1Iso );
        //_inputTree->SetBranchAddress("Electron_mvaFall17V1noIso", &Electron_mvaFall17V1noIso );
        _inputTree->SetBranchAddress("Electron_mvaFall17V2Iso", &Electron_mvaFall17V2Iso );
        _inputTree->SetBranchAddress("Electron_mvaFall17V2noIso", &Electron_mvaFall17V2noIso );
        _inputTree->SetBranchAddress("Electron_pfRelIso03_all", &Electron_pfRelIso03_all );
        _inputTree->SetBranchAddress("Electron_pfRelIso03_chg", &Electron_pfRelIso03_chg );
        _inputTree->SetBranchAddress("Electron_mvaFall17V2Iso_WP80", &Electron_mvaFall17V2Iso_WP80 );
        _inputTree->SetBranchAddress("Electron_mvaFall17V2Iso_WP90", &Electron_mvaFall17V2Iso_WP90 );
        _inputTree->SetBranchAddress("Electron_mvaFall17V2Iso_WPL", &Electron_mvaFall17V2Iso_WPL );
        _inputTree->SetBranchAddress("Electron_mvaFall17V2noIso_WP80", &Electron_mvaFall17V2noIso_WP80 );
        _inputTree->SetBranchAddress("Electron_mvaFall17V2noIso_WP90", &Electron_mvaFall17V2noIso_WP90 );


        //-----------------------------------------------------------------------------------------
        _inputTree->SetBranchAddress("nMuon", &nMuon );
        _inputTree->SetBranchAddress("Muon_pt", &Muon_pt );
        _inputTree->SetBranchAddress("Muon_eta", &Muon_eta );
        _inputTree->SetBranchAddress("Muon_phi", &Muon_phi );
        _inputTree->SetBranchAddress("Muon_charge", &Muon_charge );
        _inputTree->SetBranchAddress("Muon_mass", &Muon_mass );
        _inputTree->SetBranchAddress("Muon_pdgId", &Muon_pdgId );
        _inputTree->SetBranchAddress("Muon_miniPFRelIso_all", &Muon_miniPFRelIso_all );
        _inputTree->SetBranchAddress("Muon_miniPFRelIso_chg", &Muon_miniPFRelIso_chg );
        _inputTree->SetBranchAddress("Muon_jetRelIso", &Muon_jetRelIso );
        _inputTree->SetBranchAddress("Muon_jetIdx", &Muon_jetIdx );
        _inputTree->SetBranchAddress("Muon_isPFcand", &Muon_isPFcand );
        _inputTree->SetBranchAddress("Muon_isGlobal", &Muon_isGlobal );
        _inputTree->SetBranchAddress("Muon_isTracker", &Muon_isTracker );
        _inputTree->SetBranchAddress("Muon_dxy", &Muon_dxy );
        _inputTree->SetBranchAddress("Muon_dxyErr", &Muon_dxyErr );
        _inputTree->SetBranchAddress("Muon_dz", &Muon_dz );
        _inputTree->SetBranchAddress("Muon_dzErr", &Muon_dzErr );
        _inputTree->SetBranchAddress("Muon_nTrackerLayers", &Muon_nTrackerLayers );

        _inputTree->SetBranchAddress("Muon_looseId", &Muon_looseId );
        _inputTree->SetBranchAddress("Muon_mediumId", &Muon_mediumId );
        _inputTree->SetBranchAddress("Muon_tightId", &Muon_tightId );
        _inputTree->SetBranchAddress("Muon_multiIsoId", &Muon_multiIsoId );
        _inputTree->SetBranchAddress("Muon_softId", &Muon_softId );
        _inputTree->SetBranchAddress("Muon_tkIsoId", &Muon_tkIsoId );
        _inputTree->SetBranchAddress("Muon_tkRelIso", &Muon_tkRelIso );
        _inputTree->SetBranchAddress("Muon_pfRelIso04_all", &Muon_pfRelIso04_all );
        _inputTree->SetBranchAddress("Muon_pfRelIso03_all", &Muon_pfRelIso03_all );
        _inputTree->SetBranchAddress("Muon_pfRelIso03_chg", &Muon_pfRelIso03_chg );
        _inputTree->SetBranchAddress("Muon_pfIsoId", &Muon_pfIsoId );
        _inputTree->SetBranchAddress("Muon_highPtId", &Muon_highPtId );


        //-----------------------------------------------------------------------------------------
        /*
        _inputTree->SetBranchAddress("nTau", &nTau );                       //[50]  7    1
        _inputTree->SetBranchAddress("Tau_chargedIso", &Tau_chargedIso );
        _inputTree->SetBranchAddress("Tau_dxy", &Tau_dxy );
        _inputTree->SetBranchAddress("Tau_dz", &Tau_dz );
        _inputTree->SetBranchAddress("Tau_eta", &Tau_eta );
        _inputTree->SetBranchAddress("Tau_leadTkDeltaEta", &Tau_leadTkDeltaEta );
        _inputTree->SetBranchAddress("Tau_leadTkDeltaPhi", &Tau_leadTkDeltaPhi );
        _inputTree->SetBranchAddress("Tau_leadTkPtOverTauPt", &Tau_leadTkPtOverTauPt );
        _inputTree->SetBranchAddress("Tau_mass", &Tau_mass );
        _inputTree->SetBranchAddress("Tau_neutralIso", &Tau_neutralIso );
        _inputTree->SetBranchAddress("Tau_phi", &Tau_phi );
        _inputTree->SetBranchAddress("Tau_pt", &Tau_pt );
        _inputTree->SetBranchAddress("Tau_puCorr", &Tau_puCorr );
        _inputTree->SetBranchAddress("Tau_charge", &Tau_charge );
        _inputTree->SetBranchAddress("Tau_decayMode", &Tau_decayMode );
        _inputTree->SetBranchAddress("Tau_jetIdx", &Tau_jetIdx );
        _inputTree->SetBranchAddress("Tau_idAntiEle", &Tau_idAntiEle );
        _inputTree->SetBranchAddress("Tau_idAntiEle2018", &Tau_idAntiEle2018 );
        _inputTree->SetBranchAddress("Tau_idAntiEleDeadECal", &Tau_idAntiEleDeadECal );
        _inputTree->SetBranchAddress("Tau_idAntiMu", &Tau_idAntiMu );
        _inputTree->SetBranchAddress("Tau_idDecayMode", &Tau_idDecayMode );
        _inputTree->SetBranchAddress("Tau_idDecayModeNewDMs", &Tau_idDecayModeNewDMs );
        _inputTree->SetBranchAddress("Tau_idDeepTau2017v2p1VSe", &Tau_idDeepTau2017v2p1VSe );
        _inputTree->SetBranchAddress("Tau_idDeepTau2017v2p1VSjet", &Tau_idDeepTau2017v2p1VSjet );
        _inputTree->SetBranchAddress("Tau_idDeepTau2017v2p1VSmu", &Tau_idDeepTau2017v2p1VSmu );
        _inputTree->SetBranchAddress("Tau_idMVAnewDM2017v2", &Tau_idMVAnewDM2017v2 );
        */

        //-----------------------------------------------------------------------------------------
        _inputTree->SetBranchAddress("nCorrT1METJet", &nCorrT1METJet );
        _inputTree->SetBranchAddress("CorrT1METJet_area", &CorrT1METJet_area );
        _inputTree->SetBranchAddress("CorrT1METJet_eta", &CorrT1METJet_eta );
        _inputTree->SetBranchAddress("CorrT1METJet_muonSubtrFactor", &CorrT1METJet_muonSubtrFactor );
        _inputTree->SetBranchAddress("CorrT1METJet_phi", &CorrT1METJet_phi );
        _inputTree->SetBranchAddress("CorrT1METJet_rawPt", &CorrT1METJet_rawPt );

        _inputTree->SetBranchAddress("nJet", &nJet );
        _inputTree->SetBranchAddress("Jet_pt", &Jet_pt );
        _inputTree->SetBranchAddress("Jet_eta", &Jet_eta );
        _inputTree->SetBranchAddress("Jet_phi", &Jet_phi );
        _inputTree->SetBranchAddress("Jet_area", &Jet_area );
        _inputTree->SetBranchAddress("Jet_mass", &Jet_mass );
        _inputTree->SetBranchAddress("Jet_jetId", &Jet_jetId );
        _inputTree->SetBranchAddress("Jet_chEmEF", &Jet_chEmEF );
        _inputTree->SetBranchAddress("Jet_chHEF", &Jet_chHEF );
        _inputTree->SetBranchAddress("Jet_neEmEF", &Jet_neEmEF );
        _inputTree->SetBranchAddress("Jet_neHEF", &Jet_neHEF );
        _inputTree->SetBranchAddress("Jet_btagDeepB", &Jet_btagDeepB );
        _inputTree->SetBranchAddress("Jet_btagDeepFlavB", &Jet_btagDeepFlavB );
        _inputTree->SetBranchAddress("Jet_puIdDisc", &Jet_puIdDisc );
        _inputTree->SetBranchAddress("Jet_puId", &Jet_puId );
        _inputTree->SetBranchAddress("Jet_qgl", &Jet_qgl );
        _inputTree->SetBranchAddress("Jet_nConstituents", &Jet_nConstituents );
        _inputTree->SetBranchAddress("Jet_nElectrons", &Jet_nElectrons );
        _inputTree->SetBranchAddress("Jet_nMuons", &Jet_nMuons );
        _inputTree->SetBranchAddress("Jet_rawFactor", &Jet_rawFactor );
        _inputTree->SetBranchAddress("Jet_muonSubtrFactor", &Jet_muonSubtrFactor );

        _inputTree->SetBranchAddress("nFatJet", &nFatJet );
        _inputTree->SetBranchAddress("FatJet_eta", &FatJet_eta );
        _inputTree->SetBranchAddress("FatJet_phi", &FatJet_phi );
        _inputTree->SetBranchAddress("FatJet_pt", &FatJet_pt );
        _inputTree->SetBranchAddress("FatJet_mass", &FatJet_mass );
        _inputTree->SetBranchAddress("FatJet_deepTagMD_ZHbbvsQCD", &FatJet_deepTagMD_ZHbbvsQCD );
        _inputTree->SetBranchAddress("FatJet_deepTagMD_ZbbvsQCD", &FatJet_deepTagMD_ZbbvsQCD );
        _inputTree->SetBranchAddress("FatJet_deepTagMD_HbbvsQCD", &FatJet_deepTagMD_HbbvsQCD );
        _inputTree->SetBranchAddress("FatJet_deepTag_H", &FatJet_deepTag_H );
        _inputTree->SetBranchAddress("FatJet_deepTag_ZvsQCD", &FatJet_deepTag_ZvsQCD );
        _inputTree->SetBranchAddress("FatJet_deepTagMD_bbvsLight", &FatJet_deepTagMD_bbvsLight );
        //_inputTree->SetBranchAddress("FatJet_btagDDBvL", &FatJet_btagDDBvL );

        //-----------------------------------------------------------------------------------------
        _inputTree->SetBranchAddress("MET_phi", &MET_phi );
        _inputTree->SetBranchAddress("MET_pt", &MET_pt );
        _inputTree->SetBranchAddress("MET_MetUnclustEnUpDeltaX", &MET_MetUnclustEnUpDeltaX );
        _inputTree->SetBranchAddress("MET_MetUnclustEnUpDeltaY", &MET_MetUnclustEnUpDeltaY );
        _inputTree->SetBranchAddress("MET_covXX", &MET_covXX );
        _inputTree->SetBranchAddress("MET_covXY", &MET_covXY );
        _inputTree->SetBranchAddress("MET_covYY", &MET_covYY );
        _inputTree->SetBranchAddress("MET_significance", &MET_significance );


        //-----------------------------------------------------------------------------------------
        _inputTree->SetBranchAddress("PV_ndof", &PV_ndof );
        _inputTree->SetBranchAddress("PV_x", &PV_x );
        _inputTree->SetBranchAddress("PV_y", &PV_y );
        _inputTree->SetBranchAddress("PV_z", &PV_z );
        _inputTree->SetBranchAddress("PV_chi2", &PV_chi2 );
        _inputTree->SetBranchAddress("PV_score", &PV_score );
        _inputTree->SetBranchAddress("PV_npvs", &PV_npvs );
        _inputTree->SetBranchAddress("PV_npvsGood", &PV_npvsGood );


        //-----------------------------------------------------------------------------------------
        _inputTree->SetBranchAddress("nSV", &nSV );
        _inputTree->SetBranchAddress("SV_dlen", &SV_dlen );
        _inputTree->SetBranchAddress("SV_dlenSig", &SV_dlenSig );
        _inputTree->SetBranchAddress("SV_dxy", &SV_dxy );
        _inputTree->SetBranchAddress("SV_dxySig", &SV_dxySig );
        _inputTree->SetBranchAddress("SV_pAngle", &SV_pAngle );
        _inputTree->SetBranchAddress("SV_chi2", &SV_chi2 );
        _inputTree->SetBranchAddress("SV_eta", &SV_eta );
        _inputTree->SetBranchAddress("SV_mass", &SV_mass );
        _inputTree->SetBranchAddress("SV_ndof", &SV_ndof );
        _inputTree->SetBranchAddress("SV_phi", &SV_phi );
        _inputTree->SetBranchAddress("SV_pt", &SV_pt );
        _inputTree->SetBranchAddress("SV_x", &SV_x );
        _inputTree->SetBranchAddress("SV_y", &SV_y );
        _inputTree->SetBranchAddress("SV_z", &SV_z );
        //_inputTree->SetBranchAddress("SV_ntracks", &SV_ntracks ); // not found in data 2016


        //-----------------------------------------------------------------------------------------
        _inputTree->SetBranchAddress("nIsoTrack", &nIsoTrack );
        _inputTree->SetBranchAddress("IsoTrack_dxy", &IsoTrack_dxy );
        _inputTree->SetBranchAddress("IsoTrack_dz", &IsoTrack_dz );
        _inputTree->SetBranchAddress("IsoTrack_eta", &IsoTrack_eta );
        _inputTree->SetBranchAddress("IsoTrack_pfRelIso03_all", &IsoTrack_pfRelIso03_all );
        _inputTree->SetBranchAddress("IsoTrack_pfRelIso03_chg", &IsoTrack_pfRelIso03_chg );
        _inputTree->SetBranchAddress("IsoTrack_phi", &IsoTrack_phi );
        _inputTree->SetBranchAddress("IsoTrack_pt", &IsoTrack_pt );
        _inputTree->SetBranchAddress("IsoTrack_miniPFRelIso_all", &IsoTrack_miniPFRelIso_all );
        _inputTree->SetBranchAddress("IsoTrack_miniPFRelIso_chg", &IsoTrack_miniPFRelIso_chg );
        _inputTree->SetBranchAddress("IsoTrack_fromPV", &IsoTrack_fromPV );
        _inputTree->SetBranchAddress("IsoTrack_pdgId", &IsoTrack_pdgId );
        _inputTree->SetBranchAddress("IsoTrack_isHighPurityTrack", &IsoTrack_isHighPurityTrack );
        _inputTree->SetBranchAddress("IsoTrack_isPFcand", &IsoTrack_isPFcand );
        _inputTree->SetBranchAddress("IsoTrack_isFromLostTrack", &IsoTrack_isFromLostTrack );


        //-----------------------------------------------------------------------------------------
        _inputTree->SetBranchAddress("Flag_goodVertices", &Flag_goodVertices );
        _inputTree->SetBranchAddress("Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter );
        _inputTree->SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter );
        _inputTree->SetBranchAddress("Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter );
        _inputTree->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter );
        _inputTree->SetBranchAddress("Flag_BadPFMuonFilter", &Flag_BadPFMuonFilter );
        _inputTree->SetBranchAddress("Flag_BadPFMuonDzFilter", &Flag_BadPFMuonDzFilter );
        _inputTree->SetBranchAddress("Flag_ecalBadCalibFilter", &Flag_ecalBadCalibFilter );
        _inputTree->SetBranchAddress("Flag_eeBadScFilter", &Flag_eeBadScFilter );


        //-----------------------------------------------------------------------------------------
        if( dataset_year == "16" ){
            _inputTree->SetBranchAddress("HLT_Ele27_WPTight_Gsf", &HLT_Ele27_WPTight_Gsf );
            _inputTree->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT", &HLT_Ele115_CaloIdVT_GsfTrkIdT );
            _inputTree->SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ );
            //_inputTree->SetBranchAddress("HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL", &HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL );
            _inputTree->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24 );
            _inputTree->SetBranchAddress("HLT_IsoTkMu24", &HLT_IsoTkMu24 );
            _inputTree->SetBranchAddress("HLT_Mu50", &HLT_Mu50 );
            _inputTree->SetBranchAddress("HLT_TkMu50", &HLT_TkMu50 );
            //_inputTree->SetBranchAddress("HLT_Mu30_TkMu11", &HLT_Mu30_TkMu11 );
            _inputTree->SetBranchAddress("HLT_PFMET300", &HLT_PFMET300 );
            _inputTree->SetBranchAddress("HLT_MET200", &HLT_MET200 );
            _inputTree->SetBranchAddress("HLT_PFHT300_PFMET110", &HLT_PFHT300_PFMET110 );
            _inputTree->SetBranchAddress("HLT_PFMET170_HBHECleaned", &HLT_PFMET170_HBHECleaned );
            _inputTree->SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight", &HLT_PFMET120_PFMHT120_IDTight );
            _inputTree->SetBranchAddress("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight", &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight );
            _inputTree->SetBranchAddress("HLT_Photon175", &HLT_Photon175 );
            _inputTree->SetBranchAddress("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL", &HLT_DoubleEle33_CaloIdL_GsfTrkIdVL );

            //if( (dataset_group == "Data") && (dataset_era == "H") ){
            _inputTree->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ );
            _inputTree->SetBranchAddress("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ );
            _inputTree->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ );
            _inputTree->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ );
            //}else{
            _inputTree->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL );
            _inputTree->SetBranchAddress("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL );
            _inputTree->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL );
            _inputTree->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL );
            //}
        }else if( dataset_year == "17" ){
            _inputTree->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ );
            _inputTree->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ );
            _inputTree->SetBranchAddress("HLT_Ele35_WPTight_Gsf", &HLT_Ele35_WPTight_Gsf );
            _inputTree->SetBranchAddress("HLT_IsoMu27", &HLT_IsoMu27 );
            _inputTree->SetBranchAddress("HLT_Mu50", &HLT_Mu50 );
            _inputTree->SetBranchAddress("HLT_OldMu100", &HLT_OldMu100 );
            _inputTree->SetBranchAddress("HLT_TkMu100", &HLT_TkMu100 );
            _inputTree->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT", &HLT_Ele115_CaloIdVT_GsfTrkIdT );
            _inputTree->SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL );
            _inputTree->SetBranchAddress("HLT_DoubleEle33_CaloIdL_MW", &HLT_DoubleEle33_CaloIdL_MW );
            _inputTree->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 );
            _inputTree->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 );
            _inputTree->SetBranchAddress("HLT_PFMET200_HBHECleaned", &HLT_PFMET200_HBHECleaned );
            _inputTree->SetBranchAddress("HLT_PFMET200_HBHE_BeamHaloCleaned", &HLT_PFMET200_HBHE_BeamHaloCleaned );
            _inputTree->SetBranchAddress("HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned", &HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned );
            _inputTree->SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight", &HLT_PFMET120_PFMHT120_IDTight );
            _inputTree->SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight_PFHT60", &HLT_PFMET120_PFMHT120_IDTight_PFHT60 );
            _inputTree->SetBranchAddress("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight", &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight );
            _inputTree->SetBranchAddress("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60", &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60 );
            _inputTree->SetBranchAddress("HLT_PFHT500_PFMET100_PFMHT100_IDTight", &HLT_PFHT500_PFMET100_PFMHT100_IDTight );
            _inputTree->SetBranchAddress("HLT_PFHT700_PFMET85_PFMHT85_IDTight", &HLT_PFHT700_PFMET85_PFMHT85_IDTight );
            _inputTree->SetBranchAddress("HLT_PFHT800_PFMET75_PFMHT75_IDTight", &HLT_PFHT800_PFMET75_PFMHT75_IDTight );
            _inputTree->SetBranchAddress("HLT_Photon200", &HLT_Photon200 );
        }else if( dataset_year == "18" ){
            _inputTree->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ );
            _inputTree->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL );
            _inputTree->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24 );
            _inputTree->SetBranchAddress("HLT_Mu50", &HLT_Mu50 );
            _inputTree->SetBranchAddress("HLT_OldMu100", &HLT_OldMu100 );
            _inputTree->SetBranchAddress("HLT_TkMu100", &HLT_TkMu100 );
            _inputTree->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf );
            _inputTree->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT", &HLT_Ele115_CaloIdVT_GsfTrkIdT );
            _inputTree->SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL );
            _inputTree->SetBranchAddress("HLT_DoubleEle25_CaloIdL_MW", &HLT_DoubleEle25_CaloIdL_MW );
            _inputTree->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 );
            _inputTree->SetBranchAddress("HLT_PFMET200_HBHECleaned", &HLT_PFMET200_HBHECleaned );
            _inputTree->SetBranchAddress("HLT_PFMET200_HBHE_BeamHaloCleaned", &HLT_PFMET200_HBHE_BeamHaloCleaned );
            _inputTree->SetBranchAddress("HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned", &HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned );
            _inputTree->SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight", &HLT_PFMET120_PFMHT120_IDTight );
            _inputTree->SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight_PFHT60", &HLT_PFMET120_PFMHT120_IDTight_PFHT60 );
            _inputTree->SetBranchAddress("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight", &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight );
            _inputTree->SetBranchAddress("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60", &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60 );
            _inputTree->SetBranchAddress("HLT_PFHT500_PFMET100_PFMHT100_IDTight", &HLT_PFHT500_PFMET100_PFMHT100_IDTight );
            _inputTree->SetBranchAddress("HLT_PFHT700_PFMET85_PFMHT85_IDTight", &HLT_PFHT700_PFMET85_PFMHT85_IDTight );
            _inputTree->SetBranchAddress("HLT_PFHT800_PFMET75_PFMHT75_IDTight", &HLT_PFHT800_PFMET75_PFMHT75_IDTight );
        }
        

        
        //-----------------------------------------------------------------------------------------
        if( dataset_group != "Data" ) {
            _inputTree->SetBranchAddress("genWeight", &genWeight );

            _inputTree->SetBranchAddress("Electron_genPartIdx", &Electron_genPartIdx );
            _inputTree->SetBranchAddress("Muon_genPartIdx", &Muon_genPartIdx );
            _inputTree->SetBranchAddress("Jet_genJetIdx", &Jet_genJetIdx );
            _inputTree->SetBranchAddress("Jet_hadronFlavour", &Jet_hadronFlavour );

            _inputTree->SetBranchAddress("Pileup_nTrueInt", &Pileup_nTrueInt );
            _inputTree->SetBranchAddress("Pileup_nPU", &Pileup_nPU );

            _inputTree->SetBranchAddress("nGenJet", &nGenJet );
            _inputTree->SetBranchAddress("GenJet_eta", &GenJet_eta );
            _inputTree->SetBranchAddress("GenJet_phi", &GenJet_phi );
            _inputTree->SetBranchAddress("GenJet_pt", &GenJet_pt );
            _inputTree->SetBranchAddress("GenJet_partonFlavour", &GenJet_partonFlavour );

            _inputTree->SetBranchAddress("GenMET_phi", &GenMET_phi );
            _inputTree->SetBranchAddress("GenMET_pt", &GenMET_pt );

            _inputTree->SetBranchAddress("nGenPart", &nGenPart );
            _inputTree->SetBranchAddress("GenPart_eta", &GenPart_eta );
            _inputTree->SetBranchAddress("GenPart_mass", &GenPart_mass );
            _inputTree->SetBranchAddress("GenPart_phi", &GenPart_phi );
            _inputTree->SetBranchAddress("GenPart_pt", &GenPart_pt );
            _inputTree->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother );
            _inputTree->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId );
            _inputTree->SetBranchAddress("GenPart_status", &GenPart_status );
            _inputTree->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags );

            _inputTree->SetBranchAddress("LHEWeight_originalXWGTUP", &LHEWeight_originalXWGTUP );
            _inputTree->SetBranchAddress("nLHEPdfWeight", &nLHEPdfWeight );
            _inputTree->SetBranchAddress("LHEPdfWeight", &LHEPdfWeight );
            _inputTree->SetBranchAddress("nLHEScaleWeight", &nLHEScaleWeight );
            _inputTree->SetBranchAddress("LHEScaleWeight", &LHEScaleWeight );
            _inputTree->SetBranchAddress("nPSWeight", &nPSWeight );
            _inputTree->SetBranchAddress("PSWeight", &PSWeight );
            _inputTree->SetBranchAddress("nLHEReweightingWeight", &nLHEReweightingWeight );
            _inputTree->SetBranchAddress("LHEReweightingWeight", &LHEReweightingWeight );

            _inputTree->SetBranchAddress("LHE_HT", &LHE_HT );
            _inputTree->SetBranchAddress("LHE_Vpt", &LHE_Vpt );
            _inputTree->SetBranchAddress("LHE_Njets", &LHE_Njets );

            _inputTree->SetBranchAddress("L1PreFiringWeight_Dn", &L1PreFiringWeight_Dn );
            _inputTree->SetBranchAddress("L1PreFiringWeight_Nom", &L1PreFiringWeight_Nom );
            _inputTree->SetBranchAddress("L1PreFiringWeight_Up", &L1PreFiringWeight_Up );
            
        }

    }

    return true;
}


//-------------------------------------------------------------------------------------------------
// ANAFILES' ROUTINES
//-------------------------------------------------------------------------------------------------
void HEPHero::SetupAna(){
    if( false );
    else if( _SELECTION == "Test" ) SetupTest();
    else if( _SELECTION == "SgnStudy" ) SetupSgnStudy();
    else if( _SELECTION == "Sonnenschein" ) SetupSonnenschein();
    // SETUP YOUR SELECTION HERE
    else {
      cout << "Unknown selection requested. Exiting. " << endl;
      return;
    }
}

bool HEPHero::AnaRegion(){
    bool Selected = true;
    if( _SELECTION == "Test" && !TestRegion() ) Selected = false;
    if( _SELECTION == "SgnStudy" && !SgnStudyRegion() ) Selected = false;
    if( _SELECTION == "Sonnenschein" && !SonnenscheinRegion() ) Selected = false;
    // SET THE REGION OF YOUR SELECTION HERE

    return Selected;
}

void HEPHero::AnaSelection(){
    if( _SELECTION == "Test" ) TestSelection();
    if( _SELECTION == "SgnStudy" ) SgnStudySelection();
    if( _SELECTION == "Sonnenschein" ) SonnenscheinSelection();
    // CALL YOUR SELECTION HERE
}

void HEPHero::AnaSystematic(){
    if( _SELECTION == "Test" ) TestSystematic();
    if( _SELECTION == "SgnStudy" ) SgnStudySystematic();
    if( _SELECTION == "Sonnenschein" ) SonnenscheinSystematic();
    // PRODUCE THE SYSTEMATIC OF YOUR SELECTION HERE
}

void HEPHero::FinishAna(){
    if( _SELECTION == "Test" ) FinishTest();
    if( _SELECTION == "SgnStudy" ) FinishSgnStudy();
    if( _SELECTION == "Sonnenschein" ) FinishSonnenschein();
    // FINISH YOUR SELECTION HERE
}
   




