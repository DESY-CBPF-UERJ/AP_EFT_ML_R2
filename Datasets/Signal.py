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
paths["0_16"] = analysis+'/Datasets/Files/signal_16/dti_0/'+nano_version+'/'
paths["1_16"] = analysis+'/Datasets/Files/signal_16/dti_1/'+nano_version+'/'
paths["0_17"] = analysis+'/Datasets/Files/signal_17/dti_0/'+nano_version+'/'
paths["0_18"] = analysis+'/Datasets/Files/signal_18/dti_0/'+nano_version+'/'


s_ds_info = { # [DatasetName, Production ID, PROC_XSEC[pb], XSEC_UNC[pb], XSEC_Accuracy]
"Signal": [
    ["Signal_TTto2L2Nu_MTT-0to700",     '10',       88.51,              0.,                'unknown'],
    ["Signal_TTto2L2Nu_MTT-700to900",   '10',       88.51,              0.,                'unknown'],
    ["Signal_TTto2L2Nu_MTT-900toInf",   '10',       88.51,              0.,                'unknown'],
],
}


#----------------------------------------------------------------------------------------
# [DO NOT TOUCH THIS PART]
#----------------------------------------------------------------------------------------
s_ds = {}
for period in paths.keys():
    
    dti = period[0]
    year = period[-2:]

    for key in s_ds_info.keys():
        s_ds[key+"_"+period] = []
        for ds in s_ds_info[key]:
            list_temp = []
            list_temp.append(ds[0]+"_"+period)
            list_temp.append(ds[1]+year+dti)
            list_temp.append(paths[period]+ds[0]+".txt")
            list_temp.append(ds[2])
            list_temp.append(ds[3])
            s_ds[key+"_"+period].append(list_temp)

