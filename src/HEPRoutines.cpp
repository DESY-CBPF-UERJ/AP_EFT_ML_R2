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

    
