#include "HEPHero.h"

//-------------------------------------------------------------------------------------------------
// Pre-Routines Setup
//-------------------------------------------------------------------------------------------------
void HEPHero::PreRoutines() {
    
    //=============================================================================================
    // CMS SETUP
    //=============================================================================================

    //----OUTPUT INFO------------------------------------------------------------------------------
    _outputTree->Branch( "evtWeight", &evtWeight );
    HDF_insert( "evtWeight", &evtWeight );

    size_t pos_HT = _datasetName.find("_HT-");
    size_t pos_Pt = _datasetName.find("_Pt-");
    size_t pos_PtZ = _datasetName.find("_PtZ-");
    size_t pos_NJets = _datasetName.find("_NJets-");
    if( (pos_HT != string::npos) || (pos_Pt != string::npos) || (pos_PtZ != string::npos) || (pos_NJets != string::npos) ){
        _outputTree->Branch( "LHE_HT", &LHE_HT );
        _outputTree->Branch( "LHE_Vpt", &LHE_Vpt );
        //_outputTree->Branch( "LHE_Njets", &LHE_Njets );
        HDF_insert( "LHE_HT", &LHE_HT );
        HDF_insert( "LHE_Vpt", &LHE_Vpt );
        //HDF_insert( "LHE_Njets", &LHE_Njets );
    }

    //=============================================================================================
    // METADATA SETUP
    //=============================================================================================

    //----PILEUP-------------------------------------------------------------------------
    if( apply_pileup_wgt ){
        auto pileup_set = correction::CorrectionSet::from_file(pileup_file.c_str());
        string SetName = "Collisions" + dataset_year +"_UltraLegacy_goldenJSON";
        pileup_corr = pileup_set->at(SetName.c_str());
    }

    //----ELECTRON ID------------------------------------------------------------------------------
    if( apply_electron_wgt ){
        auto electron_set = correction::CorrectionSet::from_file(electron_file.c_str());
        electron_ID_corr = electron_set->at("UL-Electron-ID-SF");
    }

    //----MUON ID----------------------------------------------------------------------------------
    if( apply_muon_wgt ){
        auto muon_set = correction::CorrectionSet::from_file(muon_file.c_str());
        
        muon_RECO_corr = muon_set->at("NUM_TrackerMuons_DEN_genTracks");

        string MuID_WP;
        if( MUON_ID_WP == 0 ){
            MuID_WP = "NUM_LooseID_DEN_TrackerMuons";
        }else if( MUON_ID_WP == 1 ){
            MuID_WP = "NUM_MediumID_DEN_TrackerMuons";
        }else if( MUON_ID_WP == 2 ){
            MuID_WP = "NUM_TightID_DEN_TrackerMuons";
        }
        muon_ID_corr = muon_set->at(MuID_WP);

        string MuISO_WP;
        if( MUON_ISO_WP == 0 ){
            MuISO_WP = "NUM_LooseRelIso_DEN_LooseID"; // dumb value, not used
        }else if( MUON_ISO_WP == 1 ){
            MuISO_WP = "NUM_LooseRelIso_DEN_LooseID";
        }else if( MUON_ISO_WP == 2 ){
            MuISO_WP = "NUM_LooseRelIso_DEN_MediumID";
        }else if( MUON_ISO_WP == 3 ){
            MuISO_WP = "NUM_TightRelIso_DEN_MediumID";
        }
        muon_ISO_corr = muon_set->at(MuISO_WP);
    }

    //----JET PU ID--------------------------------------------------------------------------------
    if( apply_jet_puid_wgt ){
        auto jet_puid_set = correction::CorrectionSet::from_file(jet_puid_file.c_str());
        jet_PUID_corr = jet_puid_set->at("PUJetID_eff");
    }

    //----B TAGGING--------------------------------------------------------------------------------
    if( apply_btag_wgt ){

        string dsName = _datasetName.substr(0,_datasetName.length()-5);

        string dsNameDY = dsName.substr(0,10);
        if( dsNameDY == "DYJetsToLL" ) dsName = "DYJetsToLL";

        btag_eff.readFile(btag_eff_file);
        if( dataset_group != "Data" ) btag_eff.calib(dsName, "TTTo2L2Nu");

        // Choose btag algo
        // https://btv-wiki.docs.cern.ch/ScaleFactors/
        std::string btagAlgorithmMujets;
        std::string btagAlgorithmIncl;
        std::string btagAlgorithmComb;

        if (JET_BTAG_WP >= 0 and JET_BTAG_WP <= 2) {
            btagAlgorithmMujets = "deepJet_mujets";
            btagAlgorithmIncl = "deepJet_incl";
            btagAlgorithmComb = "deepJet_comb";
        }
        else if (JET_BTAG_WP >= 3 and JET_BTAG_WP <= 5) {
            btagAlgorithmMujets = "deepCSV_mujets";
            btagAlgorithmIncl = "deepCSV_incl";
            btagAlgorithmComb = "deepCSV_comb";
        }

        auto btag_set = correction::CorrectionSet::from_file(btag_SF_file.c_str());
        btag_bc_corr = btag_set->at(btagAlgorithmMujets.c_str());
        btag_udsg_corr = btag_set->at(btagAlgorithmIncl.c_str());
    }

    //----MET XY-------------------------------------------------------------------------
    if( apply_met_xy_corr ){
        auto met_xy_set = correction::CorrectionSet::from_file(met_xy_file.c_str());
        string SetName_pt;
        string SetName_phi;
        if( dataset_group == "Data" ){
            SetName_pt = "pt_metphicorr_pfmet_data";
            SetName_phi = "phi_metphicorr_pfmet_data";
        }else{
            SetName_pt = "pt_metphicorr_pfmet_mc";
            SetName_phi = "phi_metphicorr_pfmet_mc";
        }
        met_xy_pt_corr = met_xy_set->at(SetName_pt.c_str());
        met_xy_phi_corr = met_xy_set->at(SetName_phi.c_str());
    }


    //----JERC-------------------------------------------------------------------------------------
    if( apply_jer_corr || (_sysName_lateral == "JES") ){
        auto jet_jerc_set = correction::CorrectionSet::from_file(jerc_file.c_str());
        auto jet_jer_smear_set = correction::CorrectionSet::from_file(jer_smear_file.c_str());
        string jer_SF_corr_name;
        string jer_PtRes_corr_name;
        string jes_Unc_name;
        if( dataset_year == "16" ){
            if( dataset_dti == 0 ){
                jer_SF_corr_name = "Summer20UL16APV_JRV3_MC_ScaleFactor_AK4PFchs";
                jer_PtRes_corr_name = "Summer20UL16APV_JRV3_MC_PtResolution_AK4PFchs";
                jes_Unc_name = "Summer19UL16APV_V7_MC_Total_AK4PFchs";
                //if( _sysName_lateral == "JES" ) jes_Unc_name = "Summer19UL16APV_V7_MC_"+_SysSubSource+"_AK4PFchs";
            }else{
                jer_SF_corr_name = "Summer20UL16_JRV3_MC_ScaleFactor_AK4PFchs";
                jer_PtRes_corr_name = "Summer20UL16_JRV3_MC_PtResolution_AK4PFchs";
                jes_Unc_name = "Summer19UL16_V7_MC_Total_AK4PFchs";
                //if( _sysName_lateral == "JES" ) jes_Unc_name = "Summer19UL16_V7_MC_"+_SysSubSource+"_AK4PFchs";
            }
        }else if( dataset_year == "17" ){
            jer_SF_corr_name = "Summer19UL17_JRV2_MC_ScaleFactor_AK4PFchs";
            jer_PtRes_corr_name = "Summer19UL17_JRV2_MC_PtResolution_AK4PFchs";
            jes_Unc_name = "Summer19UL17_V5_MC_Total_AK4PFchs";
            //if( _sysName_lateral == "JES" ) jes_Unc_name = "Summer19UL17_V5_MC_"+_SysSubSource+"_AK4PFchs";
        }else if( dataset_year == "18" ){
            jer_SF_corr_name = "Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs";
            jer_PtRes_corr_name = "Summer19UL18_JRV2_MC_PtResolution_AK4PFchs";
            jes_Unc_name = "Summer19UL18_V5_MC_Total_AK4PFchs";
            //if( _sysName_lateral == "JES" ) jes_Unc_name = "Summer19UL18_V5_MC_"+_SysSubSource+"_AK4PFchs";
        }

        if( apply_jer_corr ){
            jet_JER_SF_corr = jet_jerc_set->at(jer_SF_corr_name);
            jet_JER_PtRes_corr = jet_jerc_set->at(jer_PtRes_corr_name);
            jet_JER_smear_corr = jet_jer_smear_set->at("JERSmear");
        }

        if( _sysName_lateral == "JES" ){
            jet_JES_Unc = jet_jerc_set->at(jes_Unc_name);
        }
    }


    //----MUON ROCHESTER-----------------------------------------------------------------
    if( apply_muon_roc_corr ){
        muon_roc_corr.Initialize(muon_roc_file);
    }

    //----TTBAR--------------------------------------------------------------------------
    if( ttbar_pdf_file.size() > 0 && ttbar_resolution_file.size() > 0 ){
        ttbarReco.addPDF(ttbar_pdf_file);
        ttbarReco.addResolution(ttbar_resolution_file);
    }

    //----LUMI CERTIFICATE-------------------------------------------------------------------------
    lumi_certificate.ReadFile(certificate_file);

}


//-------------------------------------------------------------------------------------------------
// On fly Routines Setup [run before genWeight count]
//-------------------------------------------------------------------------------------------------
bool HEPHero::RunRoutines() {
    
    //======SUM THE GENERATOR WEIGHTS=================================================
    if( dataset_group != "Data" ){
        SumGenWeights_original += genWeight;
        SumGenWeights += genWeight;
    }


    //======MC SAMPLES PROCESSING=====================================================
    if( !MC_processing() ) return false;


    //======START EVENT WEIGHT========================================================
    evtWeight = 1.;
    if( dataset_group != "Data" ) evtWeight = genWeight;

    
    return true;
}


//-------------------------------------------------------------------------------------------------
// MCsamples processing
//-------------------------------------------------------------------------------------------------
bool HEPHero::MC_processing(){

    bool pass_cut = true;
    string dsName = _datasetName.substr(0,_datasetName.length()-5);



    return pass_cut;
}

    
