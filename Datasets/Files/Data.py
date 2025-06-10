#==================================================================================================
# Eras setup  (key = year)
#==================================================================================================
eras = {}
eras["16"] = ['B-ver1_HIPM', 'B-ver2_HIPM', 'C-HIPM', 'D-HIPM', 'E-HIPM', 'F-HIPM', 'F', 'G', 'H']
eras["17"] = ['B', 'C', 'D', 'E', 'F']
eras["18"] = ['A', 'B', 'C', 'D']


#==================================================================================================
# Campaigns setup  (key = version_year_era)
#==================================================================================================
campaigns = {}
for era in set(sum(eras.values(), [])):
    campaigns["9_16_"+era] = "Run2016"+era+"_UL2016_MiniAODv2_NanoAODv9"
    campaigns["9_17_"+era] = "Run2017"+era+"_UL2017_MiniAODv2_NanoAODv9"
    campaigns["9_18_"+era] = "Run2018"+era+"_UL2018_MiniAODv2_NanoAODv9_GT36"


#==================================================================================================
# Datasets setup  (key = year)
#==================================================================================================
datasets = {}
datasets["16"] = [
["Data_EleMu",          "/MuonEG/"],
["Data_DoubleMu",       "/DoubleMuon/"],
["Data_DoubleEle",      "/DoubleEG/"],
["Data_SingleMu",       "/SingleMuon/"],
["Data_SingleEle",      "/SingleElectron/"],
["Data_MET",            "/MET/"],
]

datasets["17"] = datasets["16"].copy()

datasets["18"] = [
["Data_EleMu",          "/MuonEG/"],
["Data_DoubleMu",       "/DoubleMuon/"],
["Data_SingleMu",       "/SingleMuon/"],
["Data_Ele",            "/EGamma/"],
["Data_MET",            "/MET/"],
]
