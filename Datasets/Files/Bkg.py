#==================================================================================================
# Campaigns setup  (key = version_period)
#==================================================================================================
campaigns = {}
campaigns["9_0_16"] = "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11"
campaigns["9_1_16"] = "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17"
campaigns["9_0_17"] = "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9"
campaigns["9_0_18"] = "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1"


#==================================================================================================
# Datasets setup
#==================================================================================================
datasets = [
["DYJetsToLL_PtZ-0To50",        "/DYJetsToLL_LHEFilterPtZ-0To50_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/"],
["DYJetsToLL_PtZ-50To100",      "/DYJetsToLL_LHEFilterPtZ-50To100_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/"],
["DYJetsToLL_PtZ-100To250",     "/DYJetsToLL_LHEFilterPtZ-100To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/"],
["DYJetsToLL_PtZ-250To400",     "/DYJetsToLL_LHEFilterPtZ-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/"],
["DYJetsToLL_PtZ-400To650",     "/DYJetsToLL_LHEFilterPtZ-400To650_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/"],
["DYJetsToLL_PtZ-650ToInf",     "/DYJetsToLL_LHEFilterPtZ-650ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/"],
["DYJetsToLL_Pt-Inclusive",     "/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/"],
["DYJetsToLL_Pt-0To3",          "/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/"],
["DYJetsToLL_PtZ-3To50",        "/DYJetsToLL_LHEFilterPtZ-0To50_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/"],
["TTTo2L2Nu",                   "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/"],
["TTToSemiLeptonic",            "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/"],
["ST_tW_antitop",               "/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/"],
["ST_tW_top",                   "/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/"],
["ST_t-channel_top",            "/ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/"],
["ST_t-channel_antitop",        "/ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/"],
["ST_s-channel",                "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/"],
["WZ",                          "/WZ_TuneCP5_13TeV-pythia8/"],
["WZTo3LNu",                    "/WZTo3LNu_mllmin4p0_TuneCP5_13TeV-powheg-pythia8/"],
["WZTo2Q2L",                    "/WZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/"],
["ZZ",                          "/ZZ_TuneCP5_13TeV-pythia8/"],
["ZZTo4L",                      "/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/"],
["ZZTo2L2Nu",                   "/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/"],
["ZZTo2Q2L",                    "/ZZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/"],
["WW",                          "/WW_TuneCP5_13TeV-pythia8/"],
["WWTo2L2Nu",                   "/WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/"],
["ZZZ",                         "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/"],
["WZZ",                         "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/"],
["WWZ",                         "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/"],
["WWW",                         "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/"],
["TTWW",                        "/TTWW_TuneCP5_13TeV-madgraph-pythia8/"],
["TTWZ",                        "/TTWZ_TuneCP5_13TeV-madgraph-pythia8/"],
["TTZZ",                        "/TTZZ_TuneCP5_13TeV-madgraph-pythia8/"],
["TWZToLL_thad_Wlept",          "/TWZToLL_thad_Wlept_5f_DR_TuneCP5_13TeV-amcatnlo-pythia8/"],
["TWZToLL_tlept_Whad",          "/TWZToLL_tlept_Whad_5f_DR_TuneCP5_13TeV-amcatnlo-pythia8/"],
["TWZToLL_tlept_Wlept",         "/TWZToLL_tlept_Wlept_5f_DR_TuneCP5_13TeV-amcatnlo-pythia8/"],
["TTWJetsToLNu",                "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/"],
["TTWJetsToQQ",                 "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/"],
["TTZToQQ",                     "/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/"],
["TTZToLL",                     "/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/"],
["TTZToNuNu",                   "/TTZToNuNu_TuneCP5_13TeV-amcatnlo-pythia8/"],
["tZq_ll",                      "/tZq_ll_4f_ckm_NLO_TuneCP5_erdON_13TeV-amcatnlo-pythia8/"],
]
