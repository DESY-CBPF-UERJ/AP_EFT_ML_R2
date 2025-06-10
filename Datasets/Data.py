analysis = "AP_EFT_ML_R2"
nano_version = 'v9'

#--------------------------------------------------------------------------------------------------
# Production ID:
# 00-09(Data), 10-19(MC-signal), 20-98(MC-bkg), 99(private sample)
#
# Data taking interval (DTI):
# 2016 DTIs = 0(with "HIPM"/"APV")("pre-VFP"), 1(without "HIPM"/"APV")("pos-VFP")
#--------------------------------------------------------------------------------------------------

paths = {}
paths["0_16"] = analysis+'/Datasets/Files/data_16/'+nano_version+'/'
paths["1_16"] = analysis+'/Datasets/Files/data_16/'+nano_version+'/'
paths["0_17"] = analysis+'/Datasets/Files/data_17/'+nano_version+'/'
paths["0_18"] = analysis+'/Datasets/Files/data_18/'+nano_version+'/'


eras = {}
eras["0_16"] = ['B-ver1_HIPM', 'B-ver2_HIPM', 'C-HIPM', 'D-HIPM', 'E-HIPM', 'F-HIPM']
eras["1_16"] = ['F', 'G', 'H']
eras["0_17"] = ['B', 'C', 'D', 'E', 'F']
eras["0_18"] = ['A', 'B', 'C', 'D']


# https://twiki.cern.ch/twiki/bin/view/CMS/TWikiLUM
# https://twiki.cern.ch/twiki/bin/view/CMS/LumiRecommendationsRun2#SummaryTable
lumis = {} # [Luminosity[pb-1], Unc_total[%], Unc_uncorr[%], Unc_fullcorr[%]], Unc_fc1718[%]
lumis["tags"] = ["Luminosity", "Unc_total", "uncorr", "fullcorr", "fc1718"]
lumis["0_16"] = [19521.2283,    1.2,  1.0,  0.6,  0.0]
lumis["1_16"] = [16812.1517,    1.2,  1.0,  0.6,  0.0]
lumis["0_17"] = [41479.6805,    2.3,  2.0,  0.9,  0.6]
lumis["0_18"] = [59832.4753,    2.5,  1.5,  2.0,  0.2]


d_ds_info = {}
d_ds_info["0_16"] = { # [DatasetName, Production ID]
"Data_Lep": [
    ["Data_EleMu",          '00'],
    ["Data_DoubleMu",       '00'],
    ["Data_DoubleEle",      '00'],
    ["Data_SingleMu",       '00'],
    ["Data_SingleEle",      '00'],
],
"Data_MET": [
    ["Data_MET",            '01'],
],
}
d_ds_info["1_16"] = d_ds_info["0_16"].copy()
d_ds_info["0_17"] = d_ds_info["0_16"].copy()
d_ds_info["0_18"] = { # [DatasetName, Production ID]
"Data_Lep": [
    ["Data_EleMu",          '00'],
    ["Data_DoubleMu",       '00'],
    ["Data_SingleMu",       '00'],
    ["Data_Ele",            '00'],
],
"Data_MET": [
    ["Data_MET",            '01'],
],
}


#----------------------------------------------------------------------------------------
# [DO NOT TOUCH THIS PART]
#----------------------------------------------------------------------------------------
d_ds = {}
for period in paths.keys():

    dti = period[0]
    year = period[-2:]

    for key in d_ds_info[period].keys():
        d_ds[key+"_"+period] = []
        for ds in d_ds_info[period][key]:
            for era in eras[period]:
                list_temp = []
                list_temp.append(ds[0]+"_"+era+"_"+period)
                list_temp.append(ds[1]+year+dti)
                list_temp.append(paths[period]+ds[0]+"_"+era+".txt")
                list_temp.append(None)
                list_temp.append(None)
                d_ds[key+"_"+period].append(list_temp)

