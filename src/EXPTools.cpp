#include "HEPHero.h"


//---------------------------------------------------------------------------------------------
// JER correction
//---------------------------------------------------------------------------------------------
void HEPHero::JERvariation(){

    if( apply_jer_corr && (dataset_group != "Data") ){

        //string sys_var = "nominal";
        string sys_var = "nom";
        if( (_sysName_lateral == "JER") && (_Universe == 0) ) sys_var = "down";
        if( (_sysName_lateral == "JER") && (_Universe == 1) ) sys_var = "up";

        METCorrectionFromJER.SetXYZT(0.,0.,0.,0.);
        for( unsigned int ijet = 0; ijet < nJet; ++ijet ) {
            TLorentzVector JetLV_before;
            JetLV_before.SetPtEtaPhiM(Jet_pt[ijet],Jet_eta[ijet],Jet_phi[ijet],Jet_mass[ijet]);

            float jet_pt = Jet_pt[ijet];
            float jet_eta = Jet_eta[ijet];
            float genjet_pt = GenJet_pt[Jet_genJetIdx[ijet]];
            float jet_pt_nomuon = Jet_pt[ijet]*(1-Jet_muonSubtrFactor[ijet]);
            float jet_EmEF = Jet_neEmEF[ijet] + Jet_chEmEF[ijet];

            double jer_PtRes = jet_JER_PtRes_corr->evaluate({jet_eta, jet_pt, fixedGridRhoFastjetAll});
            double jer_SF = jet_JER_SF_corr->evaluate({jet_eta, sys_var});
            double jer_factor = jet_JER_smear_corr->evaluate({jet_pt, jet_eta, genjet_pt, fixedGridRhoFastjetAll, _EventPosition, jer_PtRes, jer_SF});

            Jet_pt[ijet] = Jet_pt[ijet]*jer_factor;
            Jet_mass[ijet] = Jet_mass[ijet]*jer_factor;

            // Cut according to MissingETRun2Corrections Twiki
            if( jet_pt_nomuon <= 15 ) continue;
            if( jet_EmEF >= 0.9 ) continue;

            TLorentzVector JetLV_after;
            JetLV_after.SetPtEtaPhiM(Jet_pt[ijet],Jet_eta[ijet],Jet_phi[ijet],Jet_mass[ijet]);

            METCorrectionFromJER -= JetLV_after - JetLV_before;
        }
    }
}


//-------------------------------------------------------------------------------------------------
// Return boolean informing if the reco jet is a pileup jet or not
//-------------------------------------------------------------------------------------------------
bool HEPHero::PileupJet( int iJet ){
    bool isPileup = true;
    bool isSignal = false;

    for( unsigned int igenJet = 0; igenJet < nGenJet; ++igenJet ) {
        float DEta = fabs( GenJet_eta[igenJet] - Jet_eta[iJet] );
        float DPhi = fabs( GenJet_phi[igenJet] - Jet_phi[iJet] );
        if( DPhi > M_PI ) DPhi = 2*M_PI - DPhi;
        float DR = sqrt( DEta*DEta + DPhi*DPhi );
        if( DR < 0.4 ) isSignal = true;
    }
    if( isSignal ) isPileup = false;

    return isPileup;
}


//-------------------------------------------------------------------------------------------------
// HEM issue in 2018
// https://twiki.cern.ch/twiki/bin/view/CMS/SUSRecommendationsRun2Legacy#HEM_issue_in_2018
//-------------------------------------------------------------------------------------------------
void HEPHero::HEMissue(){

    HEM_issue_ele = false;
    HEM_issue_jet = false;
    HEM_issue_ele_v2 = false;
    HEM_issue_jet_v2 = false;
    HEM_issue_met = false;
    HEM_filter = true;

    for( unsigned int iselele = 0; iselele < selectedEle.size(); ++iselele ) {
        int iele = selectedEle.at(iselele);
        float eta = Electron_eta[iele];
        float phi = Electron_phi[iele];
        if( (eta > -3.0) && (eta < -1.3) && (phi > -1.57) && (phi < -0.87) ) HEM_issue_ele_v2 = true;
    }


    for( unsigned int iseljet = 0; iseljet < selectedJet.size(); ++iseljet ) {
        int ijet = selectedJet.at(iseljet);
        float eta = Jet_eta[ijet];
        float phi = Jet_phi[ijet];
        if( (eta > -3.0) && (eta < -1.3) && (phi > -1.57) && (phi < -0.87) ) HEM_issue_jet_v2 = true;
    }




    for( unsigned int iele = 0; iele < nElectron; ++iele ) {
        float eta = Electron_eta[iele];
        float phi = Electron_phi[iele];
        if( (eta > -3.0) && (eta < -1.3) && (phi > -1.57) && (phi < -0.87) ) HEM_issue_ele = true;
    }

    for( unsigned int ijet = 0; ijet < nJet; ++ijet ) {
        float eta = Jet_eta[ijet];
        float phi = Jet_phi[ijet];
        float pt = Jet_pt[ijet];
        if( (pt > 20) && (eta > -3.0) && (eta < -1.3) && (phi > -1.57) && (phi < -0.87) ) HEM_issue_jet = true;
    }


    if( (MET_phi > -1.57) && (MET_phi < -0.87) ) HEM_issue_met = true;


    if( (dataset_year == "18") && (HEM_issue_ele || HEM_issue_jet) ) HEM_filter = false;

}


//-------------------------------------------------------------------------------------------------
// MET  Filters
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#UL_data
//-------------------------------------------------------------------------------------------------
bool HEPHero::METFilters(){

    string dsName = _datasetName.substr(0,_datasetName.length()-5);
    string dsNameSignal = dsName.substr(0,15);


    bool filtered = false;
    bool filters;
    //if( (dataset_year == "18") && (dsNameSignal == "Signal_1000_600") ){
    //    filters =   Flag_goodVertices &&
    //                Flag_globalSuperTightHalo2016Filter &&
    //                Flag_HBHENoiseFilter &&
    //                Flag_HBHENoiseIsoFilter &&
    //                Flag_EcalDeadCellTriggerPrimitiveFilter &&
    //                Flag_BadPFMuonFilter &&
    //                Flag_eeBadScFilter;
    //}else{
    filters =   Flag_goodVertices &&
                Flag_globalSuperTightHalo2016Filter &&
                Flag_HBHENoiseFilter &&
                Flag_HBHENoiseIsoFilter &&
                Flag_EcalDeadCellTriggerPrimitiveFilter &&
                Flag_BadPFMuonFilter &&
                Flag_BadPFMuonDzFilter &&
                Flag_eeBadScFilter;


    if( dataset_year == "16" ){
        if( filters ) filtered = true;
    }else if( (dataset_year == "17") || (dataset_year == "18") ){
        if(filters && Flag_ecalBadCalibFilter) filtered = true;
    }else{
        std::cout << "Something is Wrong !!!" << std::endl;
        std::cout << "The dataset name does not have the year [16,17,18] or dataset is from another year" << std::endl;
    }

    return filtered ;
}


//-------------------------------------------------------------------------------------------------
// Jet BTAG
//-------------------------------------------------------------------------------------------------
bool HEPHero::JetBTAG( int iobj, int WP ){

    bool obj_selected = false;
    float BTAG_CUT;

    // DeepJet
    if( dataset_year == "16"){
        if( dataset_dti == 0 ){
            if(      WP == 0 ) BTAG_CUT = 0.0508;   // loose
            else if( WP == 1 ) BTAG_CUT = 0.2598;   // medium
            else if( WP == 2 ) BTAG_CUT = 0.6502;   // tight
        }else{
            if(      WP == 0 ) BTAG_CUT = 0.0480;   // loose
            else if( WP == 1 ) BTAG_CUT = 0.2489;   // medium
            else if( WP == 2 ) BTAG_CUT = 0.6377;   // tight
        }
    }else if( dataset_year == "17" ){
        if(      WP == 0 ) BTAG_CUT = 0.0532;   // loose
        else if( WP == 1 ) BTAG_CUT = 0.3040;   // medium
        else if( WP == 2 ) BTAG_CUT = 0.7476;   // tight
    }else if( dataset_year == "18" ){
        if(      WP == 0 ) BTAG_CUT = 0.0490;   // loose
        else if( WP == 1 ) BTAG_CUT = 0.2783;   // medium
        else if( WP == 2 ) BTAG_CUT = 0.7100;   // tight
    }

    // DeepCSV
    if( dataset_year == "16" ){
        if( dataset_dti == 0 ){
            if(      WP == 3 ) BTAG_CUT = 0.2027;   // loose
            else if( WP == 4 ) BTAG_CUT = 0.6001;   // medium
            else if( WP == 5 ) BTAG_CUT = 0.8819;   // tight
        }else{
            if(      WP == 3 ) BTAG_CUT = 0.1918;   // loose
            else if( WP == 4 ) BTAG_CUT = 0.5847;   // medium
            else if( WP == 5 ) BTAG_CUT = 0.8767;   // tight
        }
    }else if( dataset_year == "17" ){
        if(      WP == 3 ) BTAG_CUT = 0.1355;   // loose
        else if( WP == 4 ) BTAG_CUT = 0.4506;   // medium
        else if( WP == 5 ) BTAG_CUT = 0.7738;   // tight
    }else if( dataset_year == "18" ){
        if(      WP == 3 ) BTAG_CUT = 0.1208;   // loose
        else if( WP == 4 ) BTAG_CUT = 0.4168;   // medium
        else if( WP == 5 ) BTAG_CUT = 0.7665;   // tight
    }

    if(      WP >= 0 and WP <=2 ) obj_selected = (Jet_btagDeepFlavB[iobj] > BTAG_CUT);    // DeepJet
    else if( WP >= 3 and WP <=5 ) obj_selected = (Jet_btagDeepB[iobj] > BTAG_CUT);        // DeepCSV

    return obj_selected;
}


//-------------------------------------------------------------------------------------------------
// Jet GenJet match
//-------------------------------------------------------------------------------------------------
bool HEPHero::Jet_GenJet_match( int ijet, float deltaR_cut ){

    bool match = false;
    double drMin = 10000;

    for( unsigned int igenJet = 0; igenJet < nGenJet; ++igenJet ) {
        double deta = fabs(GenJet_eta[igenJet] - Jet_eta[ijet]);
        double dphi = fabs(GenJet_phi[igenJet] - Jet_phi[ijet]);
        if( dphi > M_PI ) dphi = 2*M_PI - dphi;
        double dr = sqrt( deta*deta + dphi*dphi );
        if( dr < drMin ) drMin = dr;
    }

    if( drMin < deltaR_cut ) match = true;

    return match;
}


//-------------------------------------------------------------------------------------------------
// Electron ID
//-------------------------------------------------------------------------------------------------
bool HEPHero::ElectronID( int iobj, int WP ){

    bool obj_selected = false;

    if(      WP == 0 ) obj_selected = (Electron_cutBased[iobj] >= 1);
    else if( WP == 1 ) obj_selected = (Electron_cutBased[iobj] >= 2);
    else if( WP == 2 ) obj_selected = (Electron_cutBased[iobj] >= 3);
    else if( WP == 3 ) obj_selected = (Electron_cutBased[iobj] >= 4);
    else if( WP == 4 ) obj_selected = Electron_mvaFall17V2Iso_WP90[iobj];
    else if( WP == 5 ) obj_selected = Electron_mvaFall17V2Iso_WP80[iobj];

    return obj_selected;
}


//-------------------------------------------------------------------------------------------------
// Muon ID
//-------------------------------------------------------------------------------------------------
bool HEPHero::MuonID( int iobj, int WP ){

    bool obj_selected = false;

    if(      WP == 0 ) obj_selected = Muon_looseId[iobj];
    else if( WP == 1 ) obj_selected = Muon_mediumId[iobj];
    else if( WP == 2 ) obj_selected = Muon_tightId[iobj];

    return obj_selected;
}


//-------------------------------------------------------------------------------------------------
// Muon ISO
//-------------------------------------------------------------------------------------------------
bool HEPHero::MuonISO( int iobj, int WP ){

    bool obj_selected = false;

    if(      WP == 0 ) obj_selected = true;
    else if( WP == 1 ) obj_selected = (Muon_pfIsoId[iobj] >= 2);
    else if( WP == 2 ) obj_selected = (Muon_pfIsoId[iobj] >= 2);
    else if( WP == 3 ) obj_selected = (Muon_pfIsoId[iobj] >= 4);

    return obj_selected;
}
