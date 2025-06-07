analysis = "AP_EFT_ML_R2"
nano_version = 'v9'
path_0_16 = analysis+'/Datasets/Files/signal_16/dti_0/'+nano_version+'/'
path_1_16 = analysis+'/Datasets/Files/signal_16/dti_1/'+nano_version+'/'
path_0_17 = analysis+'/Datasets/Files/signal_17/dti_0/'+nano_version+'/'
path_0_18 = analysis+'/Datasets/Files/signal_18/dti_0/'+nano_version+'/'

#--------------------------------------------------------------------------------------------------
# ID digits:
# 1st-2nd = 16(2016),17(2017),18(2018)                              # Year
# 3th-4th = 00(Data),01(MC-signal),02-13(MC-bkg),99(private sample) # Group
# 5th-6th = 00(none),...                                            # Bkg -> Process
# 5th-6th = 00(none),11(250_30),12(250_40),55(1250_100)             # Signal -> Signal point
# 5th-6th = 00(none),01(A),02(B),03(C)                              # Data -> Era
# 7th     = 0,1,2,...                                               # Data taking interval (DTI)

# 2016 DTIs = 0(with "HIPM"/"APV")("pre-VFP"), 1(without "HIPM"/"APV")("pos-VFP")
#--------------------------------------------------------------------------------------------------


periods = ["0_16", "1_16", "0_17", "0_18"]
paths = [path_0_16, path_1_16, path_0_17, path_0_18]

for period,path in zip(periods,paths):
    
    dti = period[0]
    year = period[-2:]
        
    Signal = [
        ["Signal_TTto2L2Nu_MTT-0to700_"+period]     + [year+'0100'+dti, path+"Signal_TTto2L2Nu_MTT-0to700.txt"],
        ["Signal_TTto2L2Nu_MTT-700to900_"+period]   + [year+'0101'+dti, path+"Signal_TTto2L2Nu_MTT-700to900.txt"],
        ["Signal_TTto2L2Nu_MTT-900toInf_"+period]   + [year+'0102'+dti, path+"Signal_TTto2L2Nu_MTT-900toInf.txt"],
    ]


    if period == "0_16":
        Signal_0_16 = Signal
    elif period == "1_16":
        Signal_1_16 = Signal
    elif period == "0_17":
        Signal_0_17 = Signal
    elif period == "0_18":
        Signal_0_18 = Signal
