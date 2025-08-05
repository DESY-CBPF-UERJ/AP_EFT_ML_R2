#--------------------------------------------------------------------------------------------------
# Dataset files
#--------------------------------------------------------------------------------------------------
selection = "Test"
analysis = "AP_EFT_ML_R2"
treeName = "Events"
LumiWeights = 1

analysis_parameters = {
# JET
"JET_ETA_CUT                ": 2.4,
"JET_PT_CUT                 ": 30,      # GeV
"JET_ID_WP                  ": 6,       # 0-loose, 2-tight, 6-tightlepveto
"JET_PUID_WP                ": 7,       # 0-fail, 1-loose, 3-medium, 7-tight (tight is the only correct WP in v9)
"JET_BTAG_WP                ": 4,       # DeepJet: 0-loose, 1-medium, 2-tight; DeepCSV: 3-loose, 4-medium, 5-tight; [Set up the efficiency maps as well]
"JET_LEP_DR_ISO_CUT         ": 0.4,
# ELECTRON
"ELECTRON_GAP_LOWER_CUT     ": 1.444,   # Lower absolute limit of barrel-endcap gap
"ELECTRON_GAP_UPPER_CUT     ": 1.566,   # Upper absolute limit of barrel-endcap gap
"ELECTRON_ETA_CUT           ": 2.5,
"ELECTRON_PT_CUT            ": 20,      # GeV
"ELECTRON_ID_WP             ": 4,       # 0-veto, 1-loose, 2-medium, 3-tight, 4-WP90iso, 5-WP80iso
# MUON
"MUON_ETA_CUT               ": 2.4,
"MUON_PT_CUT                ": 20,      # GeV
"MUON_ID_WP                 ": 1,       # 0-loose, 1-medium, 2-tight
"MUON_ISO_WP                ": 3,       # 0-none, 1-loose/looseID, 2-loose/mediumID, 3-tight/mediumID
# EVENT
"LEADING_LEP_PT_CUT         ": 25.,      # GeV
"LEPLEP_MASS_CUT            ": 20.,      # GeV
"MET_CUT                    ": 40.,      # GeV
"LEPLEP_DM_CUT              ": 15.,      # GeV    
}

corrections = {  # 0-don't apply, 1-apply
"PILEUP_WGT                 ": 1,
"MET_XY_CORR                ": 0,
"JER_CORR                   ": 1,
"MUON_ROC_CORR              ": 1,
"PREFIRING_WGT              ": 1,
"ELECTRON_ID_WGT            ": 1,
"MUON_ID_WGT                ": 1,
"JET_PUID_WGT               ": 1,
"BTAG_WGT                   ": 1,    
}

lateral_systematics = { 
"CV":          [0,  1, [], []],   # [sys_source, sys_universe, processes_ID (empty -> all), subsources]
#"JER":         [28,  2, [], []],
#"UncMET":      [29,  2, [], []],
#"Recoil":      [30,  6, ["02"], []],
#"JES":         [41,  2, [], ["Total"]],
}

vertical_systematics = {
}


#--------------------------------------------------------------------------------------------------
# Jobs setup
#--------------------------------------------------------------------------------------------------
NumMaxEvents = -1
NumFilesPerJob_Data = 2  
NumFilesPerJob_Signal = 10
NumFilesPerJob_Bkg = 5


#--------------------------------------------------------------------------------------------------
# Dataset files
#--------------------------------------------------------------------------------------------------
periods = [
#"0_16",
#"1_16",
"0_17",
#"0_18",
]

datasets = [
"Data_Lep",
#"Data_MET",
"Signal",
"DY",
"TTFullLep",
"TTSemiLep",
"ST",
"VZ",
"ResidualSM"
]


#--------------------------------------------------------------------------------------------------
# Metadata
#--------------------------------------------------------------------------------------------------
metadata = {
"pileup_0_16                ": analysis+"/Metadata/POG/LUM/2016preVFP_UL/puWeights.json.gz",
"pileup_1_16                ": analysis+"/Metadata/POG/LUM/2016postVFP_UL/puWeights.json.gz",
"pileup_0_17                ": analysis+"/Metadata/POG/LUM/2017_UL/puWeights.json.gz",
"pileup_0_18                ": analysis+"/Metadata/POG/LUM/2018_UL/puWeights.json.gz",
"met_xy_0_16                ": analysis+"/Metadata/POG/JME/2016preVFP_UL/met.json.gz",
"met_xy_1_16                ": analysis+"/Metadata/POG/JME/2016postVFP_UL/met.json.gz",
"met_xy_0_17                ": analysis+"/Metadata/POG/JME/2017_UL/met.json.gz",
"met_xy_0_18                ": analysis+"/Metadata/POG/JME/2018_UL/met.json.gz",
"electron_0_16              ": analysis+"/Metadata/POG/EGM/2016preVFP_UL/electron.json.gz",
"electron_1_16              ": analysis+"/Metadata/POG/EGM/2016postVFP_UL/electron.json.gz",
"electron_0_17              ": analysis+"/Metadata/POG/EGM/2017_UL/electron.json.gz",
"electron_0_18              ": analysis+"/Metadata/POG/EGM/2018_UL/electron.json.gz",
"muon_0_16                  ": analysis+"/Metadata/POG/MUO/2016preVFP_UL/muon_Z.json.gz",
"muon_1_16                  ": analysis+"/Metadata/POG/MUO/2016postVFP_UL/muon_Z.json.gz",
"muon_0_17                  ": analysis+"/Metadata/POG/MUO/2017_UL/muon_Z.json.gz",
"muon_0_18                  ": analysis+"/Metadata/POG/MUO/2018_UL/muon_Z.json.gz",
"btag_SF_0_16               ": analysis+"/Metadata/POG/BTV/2016preVFP_UL/btagging.json.gz",
"btag_SF_1_16               ": analysis+"/Metadata/POG/BTV/2016postVFP_UL/btagging.json.gz",
"btag_SF_0_17               ": analysis+"/Metadata/POG/BTV/2017_UL/btagging.json.gz",
"btag_SF_0_18               ": analysis+"/Metadata/POG/BTV/2018_UL/btagging.json.gz",
"btag_eff_0_16              ": analysis+"/Metadata/btag_eff/DeepCSVMedium/2016preVFP.json",
"btag_eff_1_16              ": analysis+"/Metadata/btag_eff/DeepCSVMedium/2016postVFP.json",
"btag_eff_0_17              ": analysis+"/Metadata/btag_eff/DeepCSVMedium/2017.json",
"btag_eff_0_18              ": analysis+"/Metadata/btag_eff/DeepCSVMedium/2018.json",
"jet_puID_0_16              ": analysis+"/Metadata/POG/JME/2016preVFP_UL/jmar.json.gz",
"jet_puID_1_16              ": analysis+"/Metadata/POG/JME/2016postVFP_UL/jmar.json.gz",
"jet_puID_0_17              ": analysis+"/Metadata/POG/JME/2017_UL/jmar.json.gz",
"jet_puID_0_18              ": analysis+"/Metadata/POG/JME/2018_UL/jmar.json.gz",
"jet_veto_0_16              ": analysis+"/Metadata/POG/JME/2016preVFP_UL/jetvetomaps.json.gz",
"jet_veto_1_16              ": analysis+"/Metadata/POG/JME/2016postVFP_UL/jetvetomaps.json.gz",
"jet_veto_0_17              ": analysis+"/Metadata/POG/JME/2017_UL/jetvetomaps.json.gz",
"jet_veto_0_18              ": analysis+"/Metadata/POG/JME/2018_UL/jetvetomaps.json.gz",
"jerc_0_16                  ": analysis+"/Metadata/POG/JME/2016preVFP_UL/jet_jerc.json.gz",
"jerc_1_16                  ": analysis+"/Metadata/POG/JME/2016postVFP_UL/jet_jerc.json.gz",
"jerc_0_17                  ": analysis+"/Metadata/POG/JME/2017_UL/jet_jerc.json.gz",
"jerc_0_18                  ": analysis+"/Metadata/POG/JME/2018_UL/jet_jerc.json.gz",
"jer_smear_X_XX             ": analysis+"/Metadata/POG/JME/jer_smear.json.gz",
"mu_RoccoR_0_16             ": analysis+"/Metadata/mu_Rochester/RoccoR2016aUL.txt",
"mu_RoccoR_1_16             ": analysis+"/Metadata/mu_Rochester/RoccoR2016bUL.txt",
"mu_RoccoR_0_17             ": analysis+"/Metadata/mu_Rochester/RoccoR2017UL.txt",
"mu_RoccoR_0_18             ": analysis+"/Metadata/mu_Rochester/RoccoR2018UL.txt",
"ttbar_PDF_X_XX             ": analysis+"/Metadata/ttbar_reco/ttbar_pdfs_run2.json",
"ttbar_Res_X_XX             ": analysis+"/Metadata/ttbar_reco/ttbar_resolutions_run2.json",
"lumi_certificate_X_16      ": analysis+"/Metadata/certificates/Cert_271036-284044_13TeV_Legacy2016_Collisions16.json",
"lumi_certificate_X_17      ": analysis+"/Metadata/certificates/Cert_294927-306462_13TeV_UL2017_Collisions17.json",
"lumi_certificate_X_18      ": analysis+"/Metadata/certificates/Cert_314472-325175_13TeV_Legacy2018_Collisions18.json",    
}


#--------------------------------------------------------------------------------------------------
# Plots
#--------------------------------------------------------------------------------------------------
Get_Image_in_EPS = 0
Get_Image_in_PNG = 1
Get_Image_in_PDF = 1


"""
X -> Implement METXYCorr_Met_MetPhi using old approach
X -> Implement METXYCorr_Met_MetPhi using correctionlib
X -> Implement METCorrectionFromJER, ...
X -> Implement muon_roc_corr
X -> JERvariation()
X -> Check if I added the DATA samples updated
-> Remove codes associated with 3 and 4 leptons
-> Add jet maps corrections
-> Probably I must replace the trigger SFs by a central one
-> Check if I have the b-tagging eff maps for medium and compare both algorithm
-> Probably I must change the LepLep selection criteria for one compatible with a ttbar analysis
-> Muon raw pt should be used to get trigger eff. SFs (probably is wrong in the previous analysis)
"""
