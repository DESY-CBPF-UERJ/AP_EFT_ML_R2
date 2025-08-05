#include "HEPHero.h"


//-------------------------------------------------------------------------------------------------
// Weight corrections
//-------------------------------------------------------------------------------------------------
void HEPHero::Weight_corrections(){

    pileup_wgt = 1.;
    prefiring_wgt = 1.;
    electron_wgt = 1.;
    muon_wgt = 1.;
    btag_wgt = 1.;

    if(dataset_group != "Data"){

        if( apply_pileup_wgt ){
            pileup_wgt = GetPileupWeight(Pileup_nTrueInt, "nominal");
            evtWeight *= pileup_wgt;
        }

        if( apply_prefiring_wgt ){
            prefiring_wgt = GetPrefiringWeight("cv");
            evtWeight *= prefiring_wgt;
        }
        
        if( apply_electron_wgt ){
            electron_wgt = GetElectronWeight("cv");
            evtWeight *= electron_wgt;
        }
        
        if( apply_muon_wgt ){
            muon_wgt = GetMuonWeight("cv");
            evtWeight *= muon_wgt;
        }
        
        if( apply_jet_puid_wgt ){
            jet_puid_wgt = GetJetPUIDWeight("cv");
            evtWeight *= jet_puid_wgt;
        }
        
        if( apply_btag_wgt ){
            btag_wgt = GetBTagWeight("cv");
            evtWeight *= btag_wgt;
        }

    }
}


//-------------------------------------------------------------------------------------------------
// Pileup Correction
// Return weight associated to the pileup effect
//-------------------------------------------------------------------------------------------------
float HEPHero::GetPileupWeight( float Pileup_nTrueInt, string sysType ){

    double pileup_weight = 1.;
    pileup_weight = pileup_corr->evaluate({Pileup_nTrueInt, sysType});

    return pileup_weight;
}


//---------------------------------------------------------------------------------------------
// Prefiring Correction
// Return prefiring scale factor
//---------------------------------------------------------------------------------------------
float HEPHero::GetPrefiringWeight( string sysID ){

    double prefiring_weight = 1.;
    if( (dataset_group != "Data") && (dataset_year != "18") ){
        if( sysID == "cv" ){
            prefiring_weight = L1PreFiringWeight_Nom;
        }else if( sysID == "down" ){
            prefiring_weight = L1PreFiringWeight_Dn;
        }else if( sysID == "up" ){
            prefiring_weight = L1PreFiringWeight_Up;
        }
    }

    return prefiring_weight;
}


//---------------------------------------------------------------------------------------------
// Electron ID Correction
// Return weight associated to the identification of the two electrons
//---------------------------------------------------------------------------------------------
float HEPHero::GetElectronWeight( string sysID ){

    float LeptonID_wgt = 1.;
    if( dataset_group != "Data" ){

        string year;
        if( dataset_year == "16" ){
            if( dataset_dti == 0 ){
                year = "2016preVFP";
            }else{
                year = "2016postVFP";
            }
        }else if( dataset_year == "17" ){
            year = "2017";
        }else if( dataset_year == "18" ){
            year = "2018";
        }

        string EleID_WP;
        if( ELECTRON_ID_WP == 0 ){
            EleID_WP = "Veto";
        }else if( ELECTRON_ID_WP == 1 ){
            EleID_WP = "Loose";
        }else if( ELECTRON_ID_WP == 2 ){
            EleID_WP = "Medium";
        }else if( ELECTRON_ID_WP == 3 ){
            EleID_WP = "Tight";
        }else if( ELECTRON_ID_WP == 4 ){
            EleID_WP = "wp90iso";
        }else if( ELECTRON_ID_WP == 5 ){
            EleID_WP = "wp80iso";
        }

        for( unsigned int iele = 0; iele < nElectron; ++iele ) {
            if( Electron_pt[iele] <= 10 ) continue;
            //if( Electron_pt[iele] >= 500 ) continue;

            float ele_pt = Electron_pt[iele];
            float ele_etaSC = Electron_eta[iele] + Electron_deltaEtaSC[iele];

            float RECO_SF;
            if( sysID == "cv" ){
                if( ele_pt <= 20     ) RECO_SF = electron_ID_corr->evaluate({year, "sf", "RecoBelow20", ele_etaSC, ele_pt});
                else if( ele_pt > 20 ) RECO_SF = electron_ID_corr->evaluate({year, "sf", "RecoAbove20", ele_etaSC, ele_pt});
            }else if( sysID == "down" ){
                if( ele_pt <= 20     ) RECO_SF = electron_ID_corr->evaluate({year, "sfdown", "RecoBelow20", ele_etaSC, ele_pt});
                else if( ele_pt > 20 ) RECO_SF = electron_ID_corr->evaluate({year, "sfdown", "RecoAbove20", ele_etaSC, ele_pt});
            }else if( sysID == "up" ){
                if( ele_pt <= 20     ) RECO_SF = electron_ID_corr->evaluate({year, "sfup", "RecoBelow20", ele_etaSC, ele_pt});
                else if( ele_pt > 20 ) RECO_SF = electron_ID_corr->evaluate({year, "sfup", "RecoAbove20", ele_etaSC, ele_pt});
            }
            LeptonID_wgt *= RECO_SF;

            if( !ElectronID( iele, ELECTRON_ID_WP ) ) continue;

            float ID_SF;
            if( sysID == "cv" ){
                ID_SF = electron_ID_corr->evaluate({year, "sf", EleID_WP, ele_etaSC, ele_pt});
            }else if( sysID == "down" ){
                ID_SF = electron_ID_corr->evaluate({year, "sfdown", EleID_WP, ele_etaSC, ele_pt});
            }else if( sysID == "up" ){
                ID_SF = electron_ID_corr->evaluate({year, "sfup", EleID_WP, ele_etaSC, ele_pt});
            }
            LeptonID_wgt *= ID_SF;
        }
    }

    return LeptonID_wgt;
}


//---------------------------------------------------------------------------------------------
// Muon ID Correction
// Return weight associated to the identification of the muons
//---------------------------------------------------------------------------------------------
float HEPHero::GetMuonWeight( string sysID ){

    float LeptonID_wgt = 1.;
    if( dataset_group != "Data" ){

        for( unsigned int imu = 0; imu < nMuon; ++imu ) {
            if( Muon_pt[imu] <= 15 ) continue;
            if( abs(Muon_eta[imu]) >= 2.4 ) continue;

            float mu_pt = Muon_pt[imu];
            float mu_abseta = abs(Muon_eta[imu]);
            
            float RECO_SF;
            if( mu_pt > 40 ){
                if( sysID == "cv" ){
                    RECO_SF = muon_RECO_corr->evaluate({mu_abseta, mu_pt, "nominal"});
                }else if( sysID == "down" ){
                    RECO_SF = muon_RECO_corr->evaluate({mu_abseta, mu_pt, "systdown"});
                }else if( sysID == "up" ){
                    RECO_SF = muon_RECO_corr->evaluate({mu_abseta, mu_pt, "systup"});
                }
                LeptonID_wgt *= RECO_SF;
            }

            if( !MuonID( imu, MUON_ID_WP ) ) continue;

            float ID_SF;
            if( sysID == "cv" ){
                ID_SF = muon_ID_corr->evaluate({mu_abseta, mu_pt, "nominal"});
            }else if( sysID == "down" ){
                ID_SF = muon_ID_corr->evaluate({mu_abseta, mu_pt, "systdown"});
            }else if( sysID == "up" ){
                ID_SF = muon_ID_corr->evaluate({mu_abseta, mu_pt, "systup"});
            }
            LeptonID_wgt *= ID_SF;

            if( !MuonISO( imu, MUON_ISO_WP ) ) continue;

            float ISO_SF;
            if( sysID == "cv" ){
                ISO_SF = muon_ISO_corr->evaluate({mu_abseta, mu_pt, "nominal"});
            }else if( sysID == "down" ){
                ISO_SF = muon_ISO_corr->evaluate({mu_abseta, mu_pt, "systdown"});
            }else if( sysID == "up" ){
                ISO_SF = muon_ISO_corr->evaluate({mu_abseta, mu_pt, "systup"});
            }
            if( MUON_ISO_WP > 0 ) LeptonID_wgt *= ISO_SF;
        }
    }

    return LeptonID_wgt;
}


//---------------------------------------------------------------------------------------------
// Jet puID Correction
// Return weight associated to the jet pileup ID selection
// Jet pileup ID identify jets that are NOT pileup
// https://twiki.cern.ch/twiki/bin/view/CMS/PileupJetIDUL#Data_MC_Efficiency_Scale_Factors
// https://twiki.cern.ch/twiki/bin/view/CMS/PileupJetID#Efficiencies_and_data_MC_scale_f
//---------------------------------------------------------------------------------------------
float HEPHero::GetJetPUIDWeight( string sysID ){

    double puid_weight = 1.;
    if( dataset_group != "Data" ){

        string WP;
        if( JET_PUID_WP == 1 ){
            WP = "L";
        }else if( JET_PUID_WP == 3 ){
            WP = "M";
        }else if( JET_PUID_WP == 7 ){
            WP = "T";
        }

        double P_MC = 1;
        double P_DATA = 1;
        
        for( unsigned int ijet = 0; ijet < nJet; ++ijet ) {
            if( abs(Jet_eta[ijet]) >= 5.0 ) continue;
            if( Jet_pt[ijet] < 20 ) continue;
            if( Jet_pt[ijet] >= 50 ) continue;
            //if( !Jet_GenJet_match(ijet, 0.4) ) continue;
            if( Jet_genJetIdx[ijet] < 0 ) continue;

            //-------------------------------------------------------------------
            float jet_pt = Jet_pt[ijet];
            float jet_eta = Jet_eta[ijet];

            double eff = jet_PUID_corr->evaluate({jet_eta, jet_pt, "MCEff", WP});

            double SF;
            if( sysID == "cv" ){
                SF = jet_PUID_corr->evaluate({jet_eta, jet_pt, "nom", WP});
            }else if( sysID == "down" ){
                SF = jet_PUID_corr->evaluate({jet_eta, jet_pt, "down", WP});
            }else if( sysID == "up" ){
                SF = jet_PUID_corr->evaluate({jet_eta, jet_pt, "up", WP});
            }
            //-------------------------------------------------------------------

            if( Jet_puId[ijet] >= JET_PUID_WP ){
                P_MC *= eff;
                P_DATA *= eff*SF;
            }else{
                P_MC *= 1-eff;
                P_DATA *= 1-eff*SF;
            }
            
            //if( Jet_puId[ijet] < JET_PUID_WP ) continue;
            //if( JET_PUID_WP > 0 ) puid_weight *= SF;  // old implementation
            
        }
        
        if( P_MC > 0 ){    // new implementation
            puid_weight = P_DATA/P_MC;
        }
        
    }

    return puid_weight;
}

//---------------------------------------------------------------------------------------------
// BTagging Correction
// Return weight associated to the btagging selection
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagSFMethods
//---------------------------------------------------------------------------------------------
float HEPHero::GetBTagWeight( string sysID, string sysFlavor, string sysType ){

    double btag_weight = 1.;
    if( dataset_group != "Data" ){

        string WP;
        if(      (JET_BTAG_WP == 0) || (JET_BTAG_WP == 3) ) WP = "L";
        else if( (JET_BTAG_WP == 1) || (JET_BTAG_WP == 4) ) WP = "M";
        else if( (JET_BTAG_WP == 2) || (JET_BTAG_WP == 5) ) WP = "T";

        double P_MC = 1;
        double P_DATA = 1;
        //for( unsigned int ijet = 0; ijet < nJet; ++ijet ) {
            //if( Jet_pt[ijet] <= 20 ) continue;
            //if( abs(Jet_eta[ijet]) >= 2.4 ) continue;
        for( unsigned int iselJet = 0; iselJet < selectedJet.size(); ++iselJet ) {
            int ijet = selectedJet[iselJet];

            std::string Jet_flavour_str;
            if (Jet_hadronFlavour[ijet] == 5) {         // B
                Jet_flavour_str = "b";
            } else if (Jet_hadronFlavour[ijet] == 4) {  // C
                Jet_flavour_str = "c";
            } else if (Jet_hadronFlavour[ijet] == 0) {  // UDSG
                Jet_flavour_str = "udsg";
            }

            double eff = btag_eff.getEfficiency( Jet_flavour_str, Jet_eta[ijet], Jet_pt[ijet] );

            double SF;

            if( (Jet_flavour_str == "b") || (Jet_flavour_str == "c") ){
                if( (sysID == "cv") || (sysFlavor == "light") ){
                    SF = btag_bc_corr->evaluate({"central", WP, Jet_hadronFlavour[ijet], abs(Jet_eta[ijet]), Jet_pt[ijet]});
                }else if( (sysID == "down") && (sysType == "uncorrelated") ){
                    SF = btag_bc_corr->evaluate({"down_uncorrelated", WP, Jet_hadronFlavour[ijet], abs(Jet_eta[ijet]), Jet_pt[ijet]});
                }else if( (sysID == "down") && (sysType == "correlated") ){
                    SF = btag_bc_corr->evaluate({"down_correlated", WP, Jet_hadronFlavour[ijet], abs(Jet_eta[ijet]), Jet_pt[ijet]});
                }else if( (sysID == "up") && (sysType == "uncorrelated") ){
                    SF = btag_bc_corr->evaluate({"up_uncorrelated", WP, Jet_hadronFlavour[ijet], abs(Jet_eta[ijet]), Jet_pt[ijet]});
                }else if( (sysID == "up") && (sysType == "correlated") ){
                    SF = btag_bc_corr->evaluate({"up_correlated", WP, Jet_hadronFlavour[ijet], abs(Jet_eta[ijet]), Jet_pt[ijet]});
                }
            }else if( Jet_flavour_str == "udsg" ){
                if( (sysID == "cv") || (sysFlavor == "bc") ){
                    SF = btag_udsg_corr->evaluate({"central", WP, Jet_hadronFlavour[ijet], abs(Jet_eta[ijet]), Jet_pt[ijet]});
                }else if( (sysID == "down") && (sysType == "uncorrelated") ){
                    SF = btag_udsg_corr->evaluate({"down_uncorrelated", WP, Jet_hadronFlavour[ijet], abs(Jet_eta[ijet]), Jet_pt[ijet]});
                }else if( (sysID == "down") && (sysType == "correlated") ){
                    SF = btag_udsg_corr->evaluate({"down_correlated", WP, Jet_hadronFlavour[ijet], abs(Jet_eta[ijet]), Jet_pt[ijet]});
                }else if( (sysID == "up") && (sysType == "uncorrelated") ){
                    SF = btag_udsg_corr->evaluate({"up_uncorrelated", WP, Jet_hadronFlavour[ijet], abs(Jet_eta[ijet]), Jet_pt[ijet]});
                }else if( (sysID == "up") && (sysType == "correlated") ){
                    SF = btag_udsg_corr->evaluate({"up_correlated", WP, Jet_hadronFlavour[ijet], abs(Jet_eta[ijet]), Jet_pt[ijet]});
                }
            }

            if( JetBTAG( ijet, JET_BTAG_WP ) ){
                P_MC *= eff;
                P_DATA *= eff*SF;
            }else{
                P_MC *= 1-eff;
                P_DATA *= 1-eff*SF;
            }
        }
        if( P_MC > 0 ){
            btag_weight = P_DATA/P_MC;
        }else{
            btag_weight = 1.;
        }
    }

    return btag_weight;
}
























