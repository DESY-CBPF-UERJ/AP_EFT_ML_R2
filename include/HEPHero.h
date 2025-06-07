#ifndef HEPHERO_H
#define HEPHERO_H

#include "HEPBase.h"
#include "CMS.h"
#include "ML.h"
#include "RoccoR.h"
#include "correction.h"


using namespace std;

class HEPHero : public HEPBase {
    public:
        static HEPHero* GetInstance( char* configFileName );
        ~HEPHero() {}
        
        bool Init();
        void RunEventLoop( int nEventsMax = -1);
        void FinishRun();
    
    private:
        static HEPHero* _instance;

        bool RunRoutines();
        void PreRoutines();
        
        HEPHero() {}
        HEPHero( char* configFileName );

        void Weight_corrections();
        void VerticalSysSizes();
        void VerticalSys();
        void FillControlVariables( string key, string value);
        bool MC_processing();
        void SetupAna();
        bool AnaRegion();
        void AnaSelection();
        void AnaSystematic();
        void FinishAna();


        void SetupTest();
        bool TestRegion();
        void TestSelection();
        void TestSystematic();
        void FinishTest();
        void SetupSgnStudy();
        bool SgnStudyRegion();
        void SgnStudySelection();
        void SgnStudySystematic();
        void FinishSgnStudy();
        void SetupSonnenschein();
        bool SonnenscheinRegion();
        void SonnenscheinSelection();
        void SonnenscheinSystematic();
        void FinishSonnenschein();
        // INSERT YOUR SELECTION HERE



    //=============================================================================================
    // ANALYSIS SETUP
    //=============================================================================================

        //-------------------------------------------------------------------------------
        // Functions
        //-------------------------------------------------------------------------------

        //----ANALYSIS-----------------------------------------------
        void METCorrection();
        void Get_ttbar_Variables();
        void LeptonSelection();
        void Get_LeadingAndTrailing_Lepton_Variables();
        void Get_ThirdAndFourth_Lepton_Variables();
        void Get_Leptonic_Info( bool get12 = true, bool get34 = true);
        void Get_LepLep_Variables( bool get12 = true, bool get34 = true);
        void Jet_lep_overlap( float deltaR_cut );
        void JetSelection();
        bool Trigger();

        //----EXPERIMENT---------------------------------------------
        void JERvariation();
        bool PileupJet( int iJet );
        void HEMissue();
        bool METFilters();
        bool Jet_GenJet_match( int ijet, float deltaR_cut );
        bool ElectronID( int iobj, int WP );
        bool MuonID( int iobj, int WP );
        bool MuonISO( int iobj, int WP );
        bool JetBTAG( int iobj, int WP );

        //----TOP SPIN CORRELATION-----------------------------------
        int index_with_key(const std::vector<std::pair<std::string, float>> &vec, std::string inq);
        const std::vector<std::pair<std::string, float>>& compute_spin_correlation(float pTop_pt, float pTop_eta, float pTop_phi, float pTop_m, float aTop_pt, float aTop_eta, float aTop_phi, float aTop_m, float pLep_pt, float pLep_eta, float pLep_phi, float pLep_m, float aLep_pt, float aLep_eta, float aLep_phi, float aLep_m);

        //----WEIGHTS------------------------------------------------
        float GetPileupWeight( float Pileup_nTrueInt, string sysType );



        //-------------------------------------------------------------------------------
        // Variables
        //-------------------------------------------------------------------------------

        //----TOP SPIN CORRELATION-----------------------------------
        std::vector<std::pair<std::string, float>> spin_corr;

        //----TTBAR--------------------------------------------------
        float MT2LL;
        int ttbar_reco;
        float ttbar_mass;
        float ttbar_score;
        int ttbar_reco_v2;
        float ttbar_mass_v2;
        float ttbar_score_v2;

        //----SELECTION----------------------------------------------
        float JET_ETA_CUT;
        float JET_PT_CUT;
        int   JET_ID_WP;
        int   JET_PUID_WP;
        int   JET_BTAG_WP;
        float JET_LEP_DR_ISO_CUT;

        float ELECTRON_GAP_LOWER_CUT;
        float ELECTRON_GAP_UPPER_CUT;
        float ELECTRON_ETA_CUT;
        float ELECTRON_PT_CUT;
        int   ELECTRON_ID_WP;

        float MUON_ETA_CUT;
        float MUON_PT_CUT;
        int   MUON_ID_WP;
        int   MUON_ISO_WP;

        float LEADING_LEP_PT_CUT;
        float LEPLEP_PT_CUT;
        float MET_CUT;
        float LEPLEP_DR_CUT;
        float LEPLEP_DM_CUT;
        float MET_LEPLEP_DPHI_CUT;
        float MET_LEPLEP_MT_CUT;

        //----TRIGGERS-----------------------------------------------
        bool HLT_SingleEle;
        bool HLT_DoubleEle;
        bool HLT_SingleMu;
        bool HLT_DoubleMu;
        bool HLT_EleMu;
        bool HLT_MET;
        bool HLT_LEP;

        //----JETS---------------------------------------------------
        vector<int> selectedJet;
        vector<bool> Jet_LepOverlap;
        int Nbjets;
        int Nbjets30;
        int Njets;
        int Njets30;
        int Njets_forward;
        int Njets30_forward;
        int Njets_ISR;
        int NPUjets;
        float HT;
        float HT30;
        float MHT;
        float MHT30;
        float MDT;
        float Jet_abseta_max;
        float LeadingJet_pt;
        float SubLeadingJet_pt;
        float ThirdLeadingJet_pt;
        float FourthLeadingJet_pt;

        //----LEPTONS------------------------------------------------
        vector<int> selectedEle;
        vector<int> selectedMu;
        int Nleptons;
        int Nelectrons;
        int Nmuons;
        int RecoLepID;  // 11 - reco electron event, 13- reco muon event
        int IdxLeadingLep;
        int IdxTrailingLep;
        int IdxThirdLep;
        int IdxFourthLep;
        TLorentzVector lep_1;
        TLorentzVector lep_2;
        TLorentzVector lep_3;
        TLorentzVector lep_4;
        float LeadingLep_pt;
        float LeadingLep_eta;
        float TrailingLep_pt;
        float TrailingLep_eta;
        Float_t Muon_raw_pt[50];

        //----LEPLEP & MET-------------------------------------------
        TLorentzVector LepLep;
        float LepLep_mass;
        float LepLep_pt;
        float LepLep_deltaR;
        float LepLep_phi;
        float LepLep_eta;
        float LepLep_deltaM;
        float MET_LepLep_deltaPhi;
        float MET_LepLep_Mt;
        float MET_LepLep_deltaPt;

        //----EXTRA LEPTONS INFO-------------------------------------
        float Lep3Lep4_deltaM;
        float Lep3Lep4_M;
        float Lep3Lep4_pt;
        float Lep3Lep4_phi;
        float Lep3Lep4_deltaR;
        float LepLep_Lep3_M;
        float LepLep_Lep3_deltaR;
        float LepLep_Lep3_deltaPhi;
        float LepLep_Lep3_deltaPt;
        float MET_Lep3_deltaPhi;
        float MET_Lep3_Mt;
        float Lep3_pt;
        float Lep4_pt;
        float Min_dilep_deltaR;

        //----MET----------------------------------------------------
        float MET_RAW_pt;
        float MET_RAW_phi;
        float MET_Unc_pt;
        float MET_Unc_phi;
        float MET_JES_pt;
        float MET_JES_phi;
        float MET_XY_pt;
        float MET_XY_phi;
        float MET_RECOIL_pt;
        float MET_RECOIL_phi;
        float MET_JER_pt;
        float MET_JER_phi;
        float MET_Emu_pt;
        float MET_Emu_phi;
        float MET_sig;
        float Ux;
        float Uy;
        float U1;
        float U2;

        //----HEM----------------------------------------------------
        bool HEM_issue_ele;
        bool HEM_issue_jet;
        bool HEM_issue_ele_v2;
        bool HEM_issue_jet_v2;
        bool HEM_issue_met;
        bool HEM_filter;

        //----CONSTANTS----------------------------------------------
        const float Z_pdg_mass = 91.1876; //GeV
        const float Muon_pdg_mass = 0.105658; //GeV
        const float Electron_pdg_mass = 0.000510999; //GeV

        //----VERTICAL SYSTEMATICS-----------------------------------



        //-------------------------------------------------------------------------------
        // Metadata
        //-------------------------------------------------------------------------------

        //----PILEUP---------------------------------------
        bool    apply_pileup_wgt;
        double  pileup_wgt;
        string  pileup_file;
        shared_ptr<correction::Correction const> pileup_corr;

        //----JERC---------------------------------------------------
        bool apply_jer_corr;
        string jerc_file;
        string jer_smear_file;
        shared_ptr<correction::Correction const> jet_JER_SF_corr;
        shared_ptr<correction::Correction const> jet_JER_PtRes_corr;
        shared_ptr<correction::Correction const> jet_JER_smear_corr;
        shared_ptr<correction::Correction const> jet_JES_Unc;
        //shared_ptr<correction::Correction const> jet_JES_L1;
        //shared_ptr<correction::Correction const> jet_JES_L2;
        //shared_ptr<correction::Correction const> jet_JES_L3;
        //shared_ptr<correction::Correction const> jet_JES_Res;
        //shared_ptr<correction::Correction const> jet_JES_L1L2L3Res;
        TLorentzVector METCorrectionFromJER;
        TLorentzVector METCorrectionFromJES;

        //----MET XY-------------------------------------------------
        bool apply_met_xy_corr;
        string  met_xy_file;
        shared_ptr<correction::Correction const> met_xy_pt_corr;
        shared_ptr<correction::Correction const> met_xy_phi_corr;

        //----MET RECOIL---------------------------------------------
        bool apply_met_recoil_corr = false;

        //----MUON ROCHESTER-----------------------------------------
        bool apply_muon_roc_corr;
        Rochester_Corrector muon_roc_corr;
        string muon_roc_file;

    
    //=============================================================================================
    // INPUT TREE SETUP - NANOAOD
    //=============================================================================================
    private:

        UInt_t    run;
        UInt_t    luminosityBlock;
        ULong64_t event;

        Float_t btagWeight_CSVV2;
        Float_t btagWeight_DeepCSVB;

        UInt_t  nCorrT1METJet;              //[100] 28   6
        Float_t CorrT1METJet_area[100];
        Float_t CorrT1METJet_eta[100];
        Float_t CorrT1METJet_muonSubtrFactor[100];
        Float_t CorrT1METJet_phi[100];
        Float_t CorrT1METJet_rawPt[100];
        /*
        Float_t CaloMET_phi;
        Float_t CaloMET_pt;
        Float_t CaloMET_sumEt;
        Float_t ChsMET_phi;
        Float_t ChsMET_pt;
        Float_t ChsMET_sumEt;
        Float_t DeepMETResolutionTune_phi;
        Float_t DeepMETResolutionTune_pt;
        Float_t DeepMETResponseTune_phi;
        Float_t DeepMETResponseTune_pt;
        */

        UInt_t  nElectron;                  //[50]  9    2
        Float_t Electron_deltaEtaSC[50];
        Float_t Electron_dr03EcalRecHitSumEt[50];
        Float_t Electron_dr03HcalDepth1TowerSumEt[50];
        Float_t Electron_dr03TkSumPt[50];
        Float_t Electron_dr03TkSumPtHEEP[50];
        Float_t Electron_dxy[50];
        Float_t Electron_dxyErr[50];
        Float_t Electron_dz[50];
        Float_t Electron_dzErr[50];
        Float_t Electron_eInvMinusPInv[50];
        Float_t Electron_energyErr[50];
        Float_t Electron_eta[50];
        Float_t Electron_hoe[50];
        Float_t Electron_ip3d[50];
        Float_t Electron_jetPtRelv2[50];
        Float_t Electron_jetRelIso[50];
        Float_t Electron_mass[50];
        Float_t Electron_miniPFRelIso_all[50];
        Float_t Electron_miniPFRelIso_chg[50];
        Float_t Electron_mvaFall17V1Iso[50];
        Float_t Electron_mvaFall17V1noIso[50];
        Float_t Electron_mvaFall17V2Iso[50];
        Float_t Electron_mvaFall17V2noIso[50];
        Float_t Electron_pfRelIso03_all[50];
        Float_t Electron_pfRelIso03_chg[50];
        Float_t Electron_phi[50];
        Float_t Electron_pt[50];
        Float_t Electron_r9[50];
        Float_t Electron_scEtOverPt[50];
        Float_t Electron_sieie[50];
        Float_t Electron_sip3d[50];
        Float_t Electron_mvaTTH[50];
        Int_t   Electron_charge[50];
        Int_t   Electron_cutBased[50];
        Int_t   Electron_cutBased_Fall17_V1[50];
        Int_t   Electron_jetIdx[50];
        Int_t   Electron_pdgId[50];
        Int_t   Electron_photonIdx[50];
        Int_t   Electron_tightCharge[50];
        Int_t   Electron_vidNestedWPBitmap[50];
        Int_t   Electron_vidNestedWPBitmapHEEP[50];
        Bool_t  Electron_convVeto[50];
        Bool_t  Electron_cutBased_HEEP[50];
        Bool_t  Electron_isPFcand[50];
        UChar_t Electron_jetNDauCharged[50];
        UChar_t Electron_lostHits[50];
        Bool_t  Electron_mvaFall17V1Iso_WP80[50];
        Bool_t  Electron_mvaFall17V1Iso_WP90[50];
        Bool_t  Electron_mvaFall17V1Iso_WPL[50];
        Bool_t  Electron_mvaFall17V1noIso_WP80[50];
        Bool_t  Electron_mvaFall17V1noIso_WP90[50];
        Bool_t  Electron_mvaFall17V1noIso_WPL[50];
        Bool_t  Electron_mvaFall17V2Iso_WP80[50];
        Bool_t  Electron_mvaFall17V2Iso_WP90[50];
        Bool_t  Electron_mvaFall17V2Iso_WPL[50];
        Bool_t  Electron_mvaFall17V2noIso_WP80[50];
        Bool_t  Electron_mvaFall17V2noIso_WP90[50];
        Bool_t  Electron_mvaFall17V2noIso_WPL[50];
        UChar_t Electron_seedGain[50];
        Int_t   Electron_genPartIdx[50];
        UChar_t Electron_genPartFlav[50];


        UInt_t  nGenJet;                    //[100] 23   3
        Float_t GenJet_eta[100];
        Float_t GenJet_mass[100];
        Float_t GenJet_phi[100];
        Float_t GenJet_pt[100];
        Int_t   GenJet_partonFlavour[100];
        UChar_t GenJet_hadronFlavour[100];

        UInt_t  nGenPart;                   //[500] 143  34
        Float_t GenPart_eta[500];
        Float_t GenPart_mass[500];
        Float_t GenPart_phi[500];
        Float_t GenPart_pt[500];
        Int_t   GenPart_genPartIdxMother[500];
        Int_t   GenPart_pdgId[500];
        Int_t   GenPart_status[500];
        Int_t   GenPart_statusFlags[500];

        Float_t Generator_binvar;
        Float_t Generator_scalePDF;
        Float_t Generator_weight;
        Float_t Generator_x1;
        Float_t Generator_x2;
        Float_t Generator_xpdf1;
        Float_t Generator_xpdf2;
        Int_t   Generator_id1;
        Int_t   Generator_id2;

        Float_t GenVtx_x;
        Float_t GenVtx_y;
        Float_t GenVtx_z;

        Float_t genWeight;
        Float_t LHEWeight_originalXWGTUP;
        UInt_t  nLHEPdfWeight;              //[500] 101  68
        Float_t LHEPdfWeight[500];
        UInt_t  nLHEReweightingWeight;      //[125]  125  125
        Float_t LHEReweightingWeight[354];
        UInt_t  nLHEScaleWeight;            //[50]  9    0
        Float_t LHEScaleWeight[50];
        UInt_t  nPSWeight;                  //[50]  4    0
        Float_t PSWeight[50];

        UInt_t  nIsoTrack;                  //[50]  6    1
        Float_t IsoTrack_dxy[50];
        Float_t IsoTrack_dz[50];
        Float_t IsoTrack_eta[50];
        Float_t IsoTrack_pfRelIso03_all[50];
        Float_t IsoTrack_pfRelIso03_chg[50];
        Float_t IsoTrack_phi[50];
        Float_t IsoTrack_pt[50];
        Float_t IsoTrack_miniPFRelIso_all[50];
        Float_t IsoTrack_miniPFRelIso_chg[50];
        Int_t   IsoTrack_fromPV[50];
        Int_t   IsoTrack_pdgId[50];
        Bool_t  IsoTrack_isHighPurityTrack[50];
        Bool_t  IsoTrack_isPFcand[50];
        Bool_t  IsoTrack_isFromLostTrack[50];

        UInt_t  nJet;                       //[100] 24   3
        Float_t Jet_area[100];
        Float_t Jet_btagCSVV2[100];
        Float_t Jet_btagDeepB[100];
        Float_t Jet_btagDeepCvB[100];
        Float_t Jet_btagDeepCvL[100];
        Float_t Jet_btagDeepFlavB[100];
        Float_t Jet_btagDeepFlavCvB[100];
        Float_t Jet_btagDeepFlavCvL[100];
        Float_t Jet_btagDeepFlavQG[100];
        Float_t Jet_chEmEF[100];
        Float_t Jet_chFPV0EF[100];
        Float_t Jet_chFPV1EF[100];
        Float_t Jet_chFPV2EF[100];
        Float_t Jet_chFPV3EF[100];
        Float_t Jet_chHEF[100];
        Float_t Jet_eta[100];
        Float_t Jet_mass[100];
        Float_t Jet_muEF[100];
        Float_t Jet_muonSubtrFactor[100];
        Float_t Jet_neEmEF[100];
        Float_t Jet_neHEF[100];
        Float_t Jet_phi[100];
        Float_t Jet_pt[100];
        Float_t Jet_puIdDisc[100];
        Float_t Jet_qgl[100];
        Float_t Jet_rawFactor[100];
        Float_t Jet_bRegCorr[100];
        Float_t Jet_bRegRes[100];
        Float_t Jet_cRegCorr[100];
        Float_t Jet_cRegRes[100];
        Int_t   Jet_electronIdx1[100];
        Int_t   Jet_electronIdx2[100];
        Int_t   Jet_jetId[100];
        Int_t   Jet_muonIdx1[100];
        Int_t   Jet_muonIdx2[100];
        Int_t   Jet_nConstituents[100];
        Int_t   Jet_nElectrons[100];
        Int_t   Jet_nMuons[100];
        Int_t   Jet_puId[100];
        Int_t   Jet_genJetIdx[100];
        Int_t   Jet_hadronFlavour[100];
        Int_t   Jet_partonFlavour[100];

        UInt_t  nFatJet;                    //[50]  7    3
        Float_t FatJet_eta[50];
        Float_t FatJet_phi[50];
        Float_t FatJet_pt[50];
        Float_t FatJet_mass[50];
        Float_t FatJet_deepTagMD_ZHbbvsQCD[50];
        Float_t FatJet_deepTagMD_ZbbvsQCD[50];
        Float_t FatJet_deepTagMD_HbbvsQCD[50];
        Float_t FatJet_deepTag_H[50];
        Float_t FatJet_deepTag_ZvsQCD[50];
        Float_t FatJet_deepTagMD_bbvsLight[50];
        //Float_t FatJet_btagDDBvL[50];

        Float_t LHE_HT;
        Float_t LHE_Vpt;
        UChar_t LHE_Njets;
        /*
        Float_t LHE_HTIncoming;
        Float_t LHE_AlphaS;
        UChar_t LHE_Nb;
        UChar_t LHE_Nc;
        UChar_t LHE_Nuds;
        UChar_t LHE_Nglu;
        UChar_t LHE_NpNLO;
        UChar_t LHE_NpLO;
        UInt_t  nLHEPart;                   //[50]  8    3
        Float_t LHEPart_pt[50];
        Float_t LHEPart_eta[50];
        Float_t LHEPart_phi[50];
        Float_t LHEPart_mass[50];
        Float_t LHEPart_incomingpz[50];
        Int_t   LHEPart_pdgId[50];
        Int_t   LHEPart_status[50];
        Int_t   LHEPart_spin[50];
        */

        Float_t GenMET_phi;
        Float_t GenMET_pt;
        Float_t MET_MetUnclustEnUpDeltaX;
        Float_t MET_MetUnclustEnUpDeltaY;
        Float_t MET_covXX;
        Float_t MET_covXY;
        Float_t MET_covYY;
        Float_t MET_phi;
        Float_t MET_pt;
        Float_t MET_significance;
        Float_t MET_sumEt;
        Float_t MET_sumPtUnclustered;


        UInt_t  nMuon;                      //[50]  8    1
        Float_t Muon_dxy[50];
        Float_t Muon_dxyErr[50];
        Float_t Muon_dxybs[50];
        Float_t Muon_dz[50];
        Float_t Muon_dzErr[50];
        Float_t Muon_eta[50];
        Float_t Muon_ip3d[50];
        Float_t Muon_jetPtRelv2[50];
        Float_t Muon_jetRelIso[50];
        Float_t Muon_mass[50];
        Float_t Muon_miniPFRelIso_all[50];
        Float_t Muon_miniPFRelIso_chg[50];
        Float_t Muon_pfRelIso03_all[50];
        Float_t Muon_pfRelIso03_chg[50];
        Float_t Muon_pfRelIso04_all[50];
        Float_t Muon_phi[50];
        Float_t Muon_pt[50];
        Float_t Muon_ptErr[50];
        Float_t Muon_segmentComp[50];
        Float_t Muon_sip3d[50];
        Float_t Muon_softMva[50];
        Float_t Muon_tkRelIso[50];
        Float_t Muon_tunepRelPt[50];
        Float_t Muon_mvaLowPt[50];
        Float_t Muon_mvaTTH[50];
        Int_t   Muon_charge[50];
        Int_t   Muon_jetIdx[50];
        Int_t   Muon_nStations[50];
        Int_t   Muon_nTrackerLayers[50];
        Int_t   Muon_pdgId[50];
        Int_t   Muon_tightCharge[50];
        Int_t   Muon_fsrPhotonIdx[50];
        UChar_t Muon_highPtId[50];
        Bool_t  Muon_highPurity[50];
        Bool_t  Muon_inTimeMuon[50];
        Bool_t  Muon_isGlobal[50];
        Bool_t  Muon_isPFcand[50];
        Bool_t  Muon_isTracker[50];
        UChar_t Muon_jetNDauCharged[50];
        Bool_t  Muon_looseId[50];
        Bool_t  Muon_mediumId[50];
        Bool_t  Muon_mediumPromptId[50];
        UChar_t Muon_miniIsoId[50];
        UChar_t Muon_multiIsoId[50];
        UChar_t Muon_mvaId[50];
        UChar_t Muon_mvaLowPtId[50];
        UChar_t Muon_pfIsoId[50];
        UChar_t Muon_puppiIsoId[50];
        Bool_t  Muon_softId[50];
        Bool_t  Muon_softMvaId[50];
        Bool_t  Muon_tightId[50];
        UChar_t Muon_tkIsoId[50];
        Bool_t  Muon_triggerIdLoose[50];
        Int_t   Muon_genPartIdx[50];
        UChar_t Muon_genPartFlav[50];


        Float_t Pileup_nTrueInt;
        Float_t Pileup_pudensity;
        Float_t Pileup_gpudensity;
        Int_t   Pileup_nPU;
        Int_t   Pileup_sumEOOT;
        Int_t   Pileup_sumLOOT;

        Float_t fixedGridRhoFastjetAll;
        /*
        Float_t fixedGridRhoFastjetCentral;
        Float_t fixedGridRhoFastjetCentralCalo;
        Float_t fixedGridRhoFastjetCentralChargedPileUp;
        Float_t fixedGridRhoFastjetCentralNeutral;
        */

        /*
        UInt_t  nGenDressedLepton;          //[50]  4    0
        Float_t GenDressedLepton_eta[50];
        Float_t GenDressedLepton_mass[50];
        Float_t GenDressedLepton_phi[50];
        Float_t GenDressedLepton_pt[50];
        Int_t   GenDressedLepton_pdgId[50];
        Bool_t  GenDressedLepton_hasTauAnc[50];
        */

        /*
        UInt_t  nSoftActivityJet;           //[50]  6    0
        Float_t SoftActivityJet_eta[50];
        Float_t SoftActivityJet_phi[50];
        Float_t SoftActivityJet_pt[50];
        Float_t SoftActivityJetHT;
        Float_t SoftActivityJetHT10;
        Float_t SoftActivityJetHT2;
        Float_t SoftActivityJetHT5;
        Int_t   SoftActivityJetNjets10;
        Int_t   SoftActivityJetNjets2;
        Int_t   SoftActivityJetNjets5;
        */

        /*
        UInt_t  nSubJet;                    //[100] 10   2
        Float_t SubJet_btagCSVV2[100];
        Float_t SubJet_btagDeepB[100];
        Float_t SubJet_eta[100];
        Float_t SubJet_mass[100];
        Float_t SubJet_n2b1[100];
        Float_t SubJet_n3b1[100];
        Float_t SubJet_phi[100];
        Float_t SubJet_pt[100];
        Float_t SubJet_rawFactor[100];
        Float_t SubJet_tau1[100];
        Float_t SubJet_tau2[100];
        Float_t SubJet_tau3[100];
        Float_t SubJet_tau4[100];
        */

        /*
        UInt_t  nTau;                       //[50]  7    1
        Float_t Tau_chargedIso[50];
        Float_t Tau_dxy[50];
        Float_t Tau_dz[50];
        Float_t Tau_eta[50];
        Float_t Tau_leadTkDeltaEta[50];
        Float_t Tau_leadTkDeltaPhi[50];
        Float_t Tau_leadTkPtOverTauPt[50];
        Float_t Tau_mass[50];
        Float_t Tau_neutralIso[50];
        Float_t Tau_phi[50];
        Float_t Tau_photonsOutsideSignalCone[50];
        Float_t Tau_pt[50];
        Float_t Tau_puCorr[50];
        Float_t Tau_rawAntiEle[50];
        Float_t Tau_rawAntiEle2018[50];
        Float_t Tau_rawDeepTau2017v2p1VSe[50];
        Float_t Tau_rawDeepTau2017v2p1VSjet[50];
        Float_t Tau_rawDeepTau2017v2p1VSmu[50];
        Float_t Tau_rawIso[50];
        Float_t Tau_rawIsodR03[50];
        Float_t Tau_rawMVAnewDM2017v2[50];
        Float_t Tau_rawMVAoldDM[50];
        Float_t Tau_rawMVAoldDM2017v1[50];
        Float_t Tau_rawMVAoldDM2017v2[50];
        Float_t Tau_rawMVAoldDMdR032017v2[50];
        Int_t   Tau_charge[50];
        Int_t   Tau_decayMode[50];
        Int_t   Tau_jetIdx[50];
        Int_t   Tau_rawAntiEleCat[50];
        Int_t   Tau_rawAntiEleCat2018[50];
        UChar_t Tau_idAntiEle[50];
        UChar_t Tau_idAntiEle2018[50];
        Bool_t  Tau_idAntiEleDeadECal[50];
        UChar_t Tau_idAntiMu[50];
        Bool_t  Tau_idDecayMode[50];
        Bool_t  Tau_idDecayModeNewDMs[50];
        UChar_t Tau_idDeepTau2017v2p1VSe[50];
        UChar_t Tau_idDeepTau2017v2p1VSjet[50];
        UChar_t Tau_idDeepTau2017v2p1VSmu[50];
        UChar_t Tau_idMVAnewDM2017v2[50];
        UChar_t Tau_idMVAoldDM[50];
        UChar_t Tau_idMVAoldDM2017v1[50];
        UChar_t Tau_idMVAoldDM2017v2[50];
        UChar_t Tau_idMVAoldDMdR032017v2[50];
        */

        /*
        UInt_t  nTrigObj;                   //[100] 43   10
        Float_t TrigObj_pt[100];
        Float_t TrigObj_eta[100];
        Float_t TrigObj_phi[100];
        Float_t TrigObj_l1pt[100];
        Float_t TrigObj_l1pt_2[100];
        Float_t TrigObj_l2pt[100];
        Int_t   TrigObj_id[100];
        Int_t   TrigObj_l1iso[100];
        Int_t   TrigObj_l1charge[100];
        Int_t   TrigObj_filterBits[100];
        */


        //UInt_t  nOtherPV;                   //[50]  3    0
        //Float_t OtherPV_z[50];
        Float_t PV_ndof;
        Float_t PV_x;
        Float_t PV_y;
        Float_t PV_z;
        Float_t PV_chi2;
        Float_t PV_score;
        Int_t   PV_npvs;
        Int_t   PV_npvsGood;



        /*
        Int_t   FatJet_genJetAK8Idx[];
        Int_t   FatJet_hadronFlavour[];
        UChar_t FatJet_nBHadrons[];
        UChar_t FatJet_nCHadrons[];
        Int_t   GenJetAK8_partonFlavour[];
        UChar_t GenJetAK8_hadronFlavour[];
        Float_t GenVtx_t0;
        Int_t   Photon_genPartIdx[];
        UChar_t Photon_genPartFlav[];
        Int_t   SubJet_hadronFlavour[];
        UChar_t SubJet_nBHadrons[];
        UChar_t SubJet_nCHadrons[];
        */

        UInt_t  nSV;                        //[100] 13   4
        Float_t SV_dlen[100];
        Float_t SV_dlenSig[100];
        Float_t SV_dxy[100];
        Float_t SV_dxySig[100];
        Float_t SV_pAngle[100];
        Float_t SV_chi2[100];
        Float_t SV_eta[100];
        Float_t SV_mass[100];
        Float_t SV_ndof[100];
        Float_t SV_phi[100];
        Float_t SV_pt[100];
        Float_t SV_x[100];
        Float_t SV_y[100];
        Float_t SV_z[100];
        UChar_t SV_ntracks[100];

        Bool_t  Flag_HBHENoiseFilter;
        Bool_t  Flag_HBHENoiseIsoFilter;
        Bool_t  Flag_CSCTightHaloFilter;
        Bool_t  Flag_CSCTightHaloTrkMuUnvetoFilter;
        Bool_t  Flag_CSCTightHalo2015Filter;
        Bool_t  Flag_globalTightHalo2016Filter;
        Bool_t  Flag_globalSuperTightHalo2016Filter;
        Bool_t  Flag_HcalStripHaloFilter;
        Bool_t  Flag_hcalLaserEventFilter;
        Bool_t  Flag_EcalDeadCellTriggerPrimitiveFilter;
        Bool_t  Flag_EcalDeadCellBoundaryEnergyFilter;
        Bool_t  Flag_ecalBadCalibFilter;
        Bool_t  Flag_goodVertices;
        Bool_t  Flag_eeBadScFilter;
        Bool_t  Flag_ecalLaserCorrFilter;
        Bool_t  Flag_trkPOGFilters;
        Bool_t  Flag_chargedHadronTrackResolutionFilter;
        Bool_t  Flag_muonBadTrackFilter;
        Bool_t  Flag_BadChargedCandidateFilter;
        Bool_t  Flag_BadPFMuonFilter;
        Bool_t  Flag_BadPFMuonDzFilter;
        Bool_t  Flag_BadChargedCandidateSummer16Filter;
        Bool_t  Flag_BadPFMuonSummer16Filter;
        Bool_t  Flag_METFilters;

        Float_t  L1PreFiringWeight_Dn;
        Float_t  L1PreFiringWeight_Nom;
        Float_t  L1PreFiringWeight_Up;

        // Triggers used in 2016
        Bool_t  HLT_Ele27_WPTight_Gsf;
        Bool_t  HLT_Ele115_CaloIdVT_GsfTrkIdT;
        Bool_t  HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
        //Bool_t  HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL;
        Bool_t  HLT_IsoMu24;
        Bool_t  HLT_IsoTkMu24;
        Bool_t  HLT_Mu50;
        Bool_t  HLT_TkMu50;
        Bool_t  HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
        Bool_t  HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
        Bool_t  HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
        Bool_t  HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
        //Bool_t  HLT_Mu30_TkMu11;
        Bool_t  HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
        Bool_t  HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
        Bool_t  HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
        Bool_t  HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
        Bool_t  HLT_PFMET300;
        Bool_t  HLT_MET200;
        Bool_t  HLT_PFHT300_PFMET110;
        Bool_t  HLT_PFMET170_HBHECleaned;
        Bool_t  HLT_PFMET120_PFMHT120_IDTight;
        Bool_t  HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;
        Bool_t  HLT_Photon175;
        Bool_t  HLT_DoubleEle33_CaloIdL_GsfTrkIdVL;

        // Triggers added in 2017
        Bool_t  HLT_Ele35_WPTight_Gsf;
        Bool_t  HLT_IsoMu27;
        Bool_t  HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
        Bool_t  HLT_DoubleEle33_CaloIdL_MW;
        Bool_t  HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;
        Bool_t  HLT_PFMET200_HBHECleaned;
        Bool_t  HLT_PFMET200_HBHE_BeamHaloCleaned;
        Bool_t  HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned;
        Bool_t  HLT_PFMET120_PFMHT120_IDTight_PFHT60;
        Bool_t  HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60;
        Bool_t  HLT_PFHT500_PFMET100_PFMHT100_IDTight;
        Bool_t  HLT_PFHT700_PFMET85_PFMHT85_IDTight;
        Bool_t  HLT_PFHT800_PFMET75_PFMHT75_IDTight;
        Bool_t  HLT_Photon200;

        // Triggers added in 2018
        Bool_t  HLT_Ele32_WPTight_Gsf;
        Bool_t  HLT_DoubleEle25_CaloIdL_MW;
        Bool_t  HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
        Bool_t  HLT_OldMu100;
        Bool_t  HLT_TkMu100;
        
};

#endif
