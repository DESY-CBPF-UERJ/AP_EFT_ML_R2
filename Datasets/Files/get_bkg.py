import os
import sys
import argparse


#======SETUP=======================================================================================
parser = argparse.ArgumentParser()
parser.add_argument("-v", "--version")
parser.add_argument("-p", "--period")
args = parser.parse_args()

dataset_code = args.period+"_"+args.version

datasets_available = ["0_16_9", "1_16_9", "0_17_9", "0_18_9", "0_22_12", "1_22_12", "0_23_12", "1_23_12"]

if dataset_code not in datasets_available:
    print("There is no dataset for")
    print("NanoAOD version = v"+args.version)
    print("Year = 20"+args.period[-2:])
    print("DTI = "+args.period[0])
    print("Type a period and a version present in the list below in which the elements are formed as period_version.")
    print(datasets_available)
    sys.exit()


if args.version == "9":
    if args.period == "0_16":
        campaign = "RunIISummer20UL16NanoAODAPVv9-106X_mcRun2_asymptotic_preVFP_v11"
    elif args.period == "1_16":
        campaign = "RunIISummer20UL16NanoAODv9-106X_mcRun2_asymptotic_v17"
    elif args.period == "0_17":
        campaign = "RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9"
    elif args.period == "0_18":
        campaign = "RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1"

if args.version == "12":
    if args.period == "0_22":
        campaign = "Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5"
    elif args.period == "1_22":
        campaign = "Run3Summer22EENanoAODv12-130X_mcRun3_2022_realistic_postEE_v6"
    elif args.period == "0_23":
        campaign = "Run3Summer23NanoAODv12-130X_mcRun3_2023_realistic_v14"
    elif args.period == "1_23":
        campaign = "Run3Summer23BPixNanoAODv12-130X_mcRun3_2023_realistic_postBPix_v2"


basedir = "bkg_"+args.period[-2:]+"/dti_"+args.period[0]+"/v"+args.version+"/"
if os.path.isdir(basedir) is False:
    os.makedirs(basedir)


datasets = [
["DYJetsToLL_PtZ-0To50",        "/DYJetsToLL_LHEFilterPtZ-0To50_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
["DYJetsToLL_PtZ-50To100",      "/DYJetsToLL_LHEFilterPtZ-50To100_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
["DYJetsToLL_PtZ-100To250",     "/DYJetsToLL_LHEFilterPtZ-100To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
["DYJetsToLL_PtZ-250To400",     "/DYJetsToLL_LHEFilterPtZ-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
["DYJetsToLL_PtZ-400To650",     "/DYJetsToLL_LHEFilterPtZ-400To650_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
["DYJetsToLL_PtZ-650ToInf",     "/DYJetsToLL_LHEFilterPtZ-650ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
["DYJetsToLL_Pt-Inclusive",     "/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["DYJetsToLL_Pt-50To100",       "/DYJetsToLL_Pt-50To100_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["DYJetsToLL_Pt-100To250",      "/DYJetsToLL_Pt-100To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["DYJetsToLL_Pt-250To400",      "/DYJetsToLL_Pt-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["DYJetsToLL_Pt-400To650",      "/DYJetsToLL_Pt-400To650_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["DYJetsToLL_Pt-650ToInf",      "/DYJetsToLL_Pt-650ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["DYJetsToLL_M-10to50",         "/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/" + campaign],
#["DYJetsToLL_HT-Inclusive",     "/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/" + campaign],
#["DYJetsToLL_HT-70to100",       "/DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/" + campaign],
#["DYJetsToLL_HT-100to200",      "/DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/" + campaign],
#["DYJetsToLL_HT-200to400",      "/DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/" + campaign],
#["DYJetsToLL_HT-400to600",      "/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/" + campaign],
#["DYJetsToLL_HT-600to800",      "/DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/" + campaign],
#["DYJetsToLL_HT-800to1200",     "/DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/" + campaign],
#["DYJetsToLL_HT-1200to2500",    "/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/" + campaign],
#["DYJetsToLL_HT-2500toInf",     "/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/" + campaign],
["TTTo2L2Nu",                   "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/" + campaign],
["TTToSemiLeptonic",            "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/" + campaign],
["ST_tW_antitop",               "/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/" + campaign],
["ST_tW_top",                   "/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/" + campaign],
["ST_t-channel_top",            "/ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/" + campaign],
["ST_t-channel_antitop",        "/ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/" + campaign],
["ST_s-channel",                "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/" + campaign],
["WZ",                          "/WZ_TuneCP5_13TeV-pythia8/" + campaign],
["WZTo3LNu",                    "/WZTo3LNu_mllmin4p0_TuneCP5_13TeV-powheg-pythia8/" + campaign],
["WZTo2Q2L",                    "/WZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
["ZZ",                          "/ZZ_TuneCP5_13TeV-pythia8/" + campaign],
["ZZTo4L",                      "/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/" + campaign],
["ZZTo2L2Nu",                   "/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/" + campaign],
["ZZTo2Q2L",                    "/ZZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
["WW",                          "/WW_TuneCP5_13TeV-pythia8/" + campaign],
["WWTo2L2Nu",                   "/WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/" + campaign],
["ZZZ",                         "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/" + campaign],
["WZZ",                         "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/" + campaign],
["WWZ",                         "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/" + campaign],
["WWW",                         "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/" + campaign],
["TTWW",                        "/TTWW_TuneCP5_13TeV-madgraph-pythia8/" + campaign],
["TTWZ",                        "/TTWZ_TuneCP5_13TeV-madgraph-pythia8/" + campaign],
["TTZZ",                        "/TTZZ_TuneCP5_13TeV-madgraph-pythia8/" + campaign],
["TWZToLL_thad_Wlept",          "/TWZToLL_thad_Wlept_5f_DR_TuneCP5_13TeV-amcatnlo-pythia8/" + campaign],
["TWZToLL_tlept_Whad",          "/TWZToLL_tlept_Whad_5f_DR_TuneCP5_13TeV-amcatnlo-pythia8/" + campaign],
["TWZToLL_tlept_Wlept",         "/TWZToLL_tlept_Wlept_5f_DR_TuneCP5_13TeV-amcatnlo-pythia8/" + campaign],
["TTWJetsToLNu",                "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/" + campaign],
["TTWJetsToQQ",                 "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/" + campaign],
["TTZToQQ",                     "/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/" + campaign],
["TTZToLL",                     "/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/" + campaign],
["TTZToNuNu",                   "/TTZToNuNu_TuneCP5_13TeV-amcatnlo-pythia8/" + campaign],
["tZq_ll",                      "/tZq_ll_4f_ckm_NLO_TuneCP5_erdON_13TeV-amcatnlo-pythia8/" + campaign],
#["ttH_HToZZ",                   "/ttH_HToZZ_4LFilter_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/" + campaign],
#["ttHTobb",                     "/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/" + campaign],
#["ttHToTauTau",                 "/ttHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/" + campaign],
#["GluGluHToWWTo2L2Nu",          "/GluGluHToWWTo2L2Nu_M125_TuneCP5_13TeV_powheg2_JHUGenV714_pythia8/" + campaign],
#["GluGluHToZZTo2L2Q",           "/GluGluHToZZTo2L2Q_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/" + campaign],
#["GluGluHToZZTo4L",             "/GluGluHToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/" + campaign],
#["WplusH_HToZZTo2L2X",          "/WplusH_HToZZTo2L2X_M125_TuneCP5_13TeV_powheg2-minlo-HWJ_JHUGenV7011_pythia8/" + campaign],
#["WplusH_HToZZTo4L",            "/WplusH_HToZZTo4L_M125_TuneCP5_13TeV_powheg2-minlo-HWJ_JHUGenV7011_pythia8/" + campaign],
#["WminusH_HToZZTo2L2X",         "/WminusH_HToZZTo2L2X_M125_TuneCP5_13TeV_powheg2-minlo-HWJ_JHUGenV7011_pythia8/" + campaign],
#["WminusH_HToZZTo4L",           "/WminusH_HToZZTo4L_M125_TuneCP5_13TeV_powheg2-minlo-HWJ_JHUGenV7011_pythia8/" + campaign],
#["ZH_HToBB_ZToLL",              "/ZH_HToBB_ZToLL_M-125_TuneCP5_13TeV-powheg-pythia8/" + campaign],
#["ZH_HToZZ",                    "/ZH_HToZZ_4LFilter_M125_TuneCP5_13TeV_powheg2-minlo-HZJ_JHUGenV7011_pythia8/" + campaign],
#["QCD_Mu_Pt-15To20",            "/QCD_Pt-15To20_MuEnrichedPt5_TuneCP5_13TeV-pythia8/" + campaign],
#["QCD_Mu_Pt-20To30",            "/QCD_Pt-20To30_MuEnrichedPt5_TuneCP5_13TeV-pythia8/" + campaign],
#["QCD_Mu_Pt-30To50",            "/QCD_Pt-30To50_MuEnrichedPt5_TuneCP5_13TeV-pythia8/" + campaign],
#["QCD_Mu_Pt-50To80",            "/QCD_Pt-50To80_MuEnrichedPt5_TuneCP5_13TeV-pythia8/" + campaign],
#["QCD_Mu_Pt-80To120",           "/QCD_Pt-80To120_MuEnrichedPt5_TuneCP5_13TeV-pythia8/" + campaign],
#["QCD_Mu_Pt-120To170",          "/QCD_Pt-120To170_MuEnrichedPt5_TuneCP5_13TeV-pythia8/" + campaign],
#["QCD_Mu_Pt-170To300",          "/QCD_Pt-170To300_MuEnrichedPt5_TuneCP5_13TeV-pythia8/" + campaign],
#["QCD_Mu_Pt-300To470",          "/QCD_Pt-300To470_MuEnrichedPt5_TuneCP5_13TeV-pythia8/" + campaign],
#["QCD_Mu_Pt-470To600",          "/QCD_Pt-470To600_MuEnrichedPt5_TuneCP5_13TeV-pythia8/" + campaign],
#["QCD_Mu_Pt-600To800",          "/QCD_Pt-600To800_MuEnrichedPt5_TuneCP5_13TeV-pythia8/" + campaign],
#["QCD_Mu_Pt-800To1000",         "/QCD_Pt-800To1000_MuEnrichedPt5_TuneCP5_13TeV-pythia8/" + campaign],
#["QCD_Mu_Pt-1000ToInf",         "/QCD_Pt-1000_MuEnrichedPt5_TuneCP5_13TeV-pythia8/" + campaign],
#["tZq_ll",                      "/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/" + campaign],
##["WJetsToLNu",                  "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/" + campaign],
#["WGToLNuG",                    "/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/" + campaign],
#["TTToHadronic",                "/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/" + campaign],
#["QCD_Pt_15to30",               "/QCD_Pt_15to30_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_30to50",               "/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_50to80",               "/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_80to120",              "/QCD_Pt_80to120_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_120to170",             "/QCD_Pt_120to170_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_170to300",             "/QCD_Pt_170to300_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_300to470",             "/QCD_Pt_300to470_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_470to600",             "/QCD_Pt_470to600_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_600to800",             "/QCD_Pt_600to800_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_800to1000",            "/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_1000to1400",           "/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_1400to1800",           "/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_1800to2400",           "/QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_2400to3200",           "/QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8/" + campaign],
#["QCD_Pt_3200toInf",            "/QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8/" + campaign],
#["ZH_HToBB_ZToNuNu",            "/ZH_HToBB_ZToNuNu_M-125_TuneCP5_13TeV-powheg-pythia8/" + campaign],
#["ZZTo2Q2Nu",                   "/ZZTo2Q2Nu_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["QCD_B_HT100to200",            "/QCD_HT100to200_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/" + campaign],
#["QCD_B_HT200to300",            "/QCD_HT200to300_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/" + campaign],
#["QCD_B_HT300to500",            "/QCD_HT300to500_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/" + campaign],
#["QCD_B_HT500to700",            "/QCD_HT500to700_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/" + campaign],
#["QCD_B_HT700to1000",           "/QCD_HT700to1000_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/" + campaign],
#["QCD_B_HT1000to1500",          "/QCD_HT1000to1500_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/" + campaign],
#["QCD_B_HT1500to2000",          "/QCD_HT1500to2000_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/" + campaign],
#["QCD_B_HT2000toInf",           "/QCD_HT2000toInf_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/" + campaign],
#["WJetsToLNu_Pt-Inclusive",     "/WJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["WJetsToLNu_Pt-100To250",      "/WJetsToLNu_Pt-100To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["WJetsToLNu_Pt-250To400",      "/WJetsToLNu_Pt-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["WJetsToLNu_Pt-400To600",      "/WJetsToLNu_Pt-400To600_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["WJetsToLNu_Pt-600ToInf",      "/WJetsToLNu_Pt-600ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["WJetsToLNu_0J",               "/WJetsToLNu_0J_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["WJetsToLNu_1J",               "/WJetsToLNu_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["WJetsToLNu_2J",               "/WJetsToLNu_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["WHJet_HToBB_WToLNu",          "/WHJet_HToBB_WToLNu_M-125_TuneCP5_SMEFTsim_topU3l_13TeV-madgraphMLM-pythia8/" + campaign],
#["QCD_HT50to100",   "/QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraph-pythia8/" + campaign],
#["QCD_HT100to200",   "/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraph-pythia8/" + campaign],
#["QCD_HT200to300",   "/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraph-pythia8/" + campaign],
#["QCD_HT300to500",   "/QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraph-pythia8/" + campaign],
#["QCD_HT500to700",   "/QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraph-pythia8/" + campaign],
#["QCD_HT700to1000",   "/QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraph-pythia8/" + campaign],
#["QCD_HT1000to1500",   "/QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraph-pythia8/" + campaign],
#["QCD_HT1500to2000",   "/QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraph-pythia8/" + campaign],
#["QCD_HT2000toInf",   "/QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraph-pythia8/" + campaign],
#["Z1JetsToNuNu_PtZ-50To150",   "/Z1JetsToNuNu_M-50_LHEFilterPtZ-50To150_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["Z1JetsToNuNu_PtZ-150To250",   "/Z1JetsToNuNu_M-50_LHEFilterPtZ-150To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["Z1JetsToNuNu_PtZ-250To400",   "/Z1JetsToNuNu_M-50_LHEFilterPtZ-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["Z1JetsToNuNu_PtZ-400ToInf",   "/Z1JetsToNuNu_M-50_LHEFilterPtZ-400ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["Z2JetsToNuNu_PtZ-50To150",   "/Z2JetsToNuNu_M-50_LHEFilterPtZ-50To150_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["Z2JetsToNuNu_PtZ-150To250",   "/Z2JetsToNuNu_M-50_LHEFilterPtZ-150To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["Z2JetsToNuNu_PtZ-250To400",   "/Z2JetsToNuNu_M-50_LHEFilterPtZ-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["Z2JetsToNuNu_PtZ-400ToInf",   "/Z2JetsToNuNu_M-50_LHEFilterPtZ-400ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/" + campaign],
#["ggToZZTo2e2mu",               "/GluGluToContinToZZTo2e2mu_TuneCP5_13TeV-mcfm701-pythia8/" + campaign],
#["ggToZZTo2e2nu",               "/GluGluToContinToZZTo2e2nu_TuneCP5_13TeV-mcfm701-pythia8/" + campaign],
#["ggToZZTo2e2tau",              "/GluGluToContinToZZTo2e2tau_TuneCP5_13TeV-mcfm701-pythia8/" + campaign],
#["ggToZZTo2mu2nu",              "/GluGluToContinToZZTo2mu2nu_TuneCP5_13TeV-mcfm701-pythia8/" + campaign],
#["ggToZZTo2mu2tau",             "/GluGluToContinToZZTo2mu2tau_TuneCP5_13TeV-mcfm701-pythia8/" + campaign],
#["ggToZZTo4e",                  "/GluGluToContinToZZTo4e_TuneCP5_13TeV-mcfm701-pythia8/" + campaign],
#["ggToZZTo4mu",                 "/GluGluToContinToZZTo4mu_TuneCP5_13TeV-mcfm701-pythia8/" + campaign],
#["ggToZZTo4tau",                "/GluGluToContinToZZTo4tau_TuneCP5_13TeV-mcfm701-pythia8/" + campaign],
]

for i in range(len(datasets)):
    file_name = basedir + datasets[i][0] + ".txt"

    # Main dataset
    for k in range(9):
        ds_name = datasets[i][1] + "-v" + str(k+1) + "/NANOAODSIM"
        if k == 0:
            command = "dasgoclient --limit 0 --query 'dataset dataset=" + ds_name + "' > " + "temp.txt"
        else:
            command = "dasgoclient --limit 0 --query 'dataset dataset=" + ds_name + "' >> " + "temp.txt"
        os.system(command)
    has_dataset = False
    k_lines = []
    with open("temp.txt", "r") as file:
        for line in file:
            has_dataset = True
            k_lines.append(line[0:-1])
    os.system("rm temp.txt")
    if has_dataset:
        k_value = 9
        for dataset_name in reversed(k_lines):
            command = "dasgoclient --limit 0 --query 'file dataset=" + dataset_name + "' > " + file_name
            os.system(command)
            NumLines = sum(1 for line in open(file_name))
            if NumLines > 0:
                print(dataset_name)
                break
            k_value = k_value - 1
    else:
        open(file_name, 'a').close()
        print(datasets[i][1] + " is not available!")

    # Extension
    ds_name = datasets[i][1] + "_ext*-v" + str(k_value) + "/NANOAODSIM"
    command = "dasgoclient --limit 0 --query 'dataset dataset=" + ds_name + "' > " + "temp.txt"
    os.system(command)
    has_dataset = False
    ext_lines = []
    with open("temp.txt", "r") as file:
        for line in file:
            has_dataset = True
            ext_lines.append(line[0:-1])
    os.system("rm temp.txt")
    if has_dataset:
        for dataset_name in ext_lines:
            command = "dasgoclient --limit 0 --query 'file dataset=" + dataset_name + "' >> " + file_name
            os.system(command)
            print(dataset_name)
