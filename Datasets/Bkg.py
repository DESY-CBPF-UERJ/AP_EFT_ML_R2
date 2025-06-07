analysis = "AP_EFT_ML_R2"
nano_version = 'v9'
path_0_16 = analysis+'/Datasets/Files/bkg_16/dti_0/'+nano_version+'/'
path_1_16 = analysis+'/Datasets/Files/bkg_16/dti_1/'+nano_version+'/'
path_0_17 = analysis+'/Datasets/Files/bkg_17/dti_0/'+nano_version+'/'
path_0_18 = analysis+'/Datasets/Files/bkg_18/dti_0/'+nano_version+'/'

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
    
    DYPt0To50 = [
        ["DYJetsToLL_Pt-0To3_"+period]               + [year+'0201'+dti, path+"DYJetsToLL_Pt-Inclusive.txt"],
        ["DYJetsToLL_PtZ-3To50_"+period]             + [year+'0201'+dti, path+"DYJetsToLL_PtZ-0To50.txt"],
        ##["DYJetsToLL_PtZ-0To50_"+period]             + [year+'0201'+dti, path+"DYJetsToLL_PtZ-0To50.txt"],
        ##["DYJetsToLL_Pt-Inclusive_"+period]          + [year+'0201'+dti, path+"DYJetsToLL_Pt-Inclusive.txt"],
    ]

    DYPt50ToInf = [
        ["DYJetsToLL_PtZ-50To100_"+period]           + [year+'0202'+dti, path+"DYJetsToLL_PtZ-50To100.txt"],
        ["DYJetsToLL_PtZ-100To250_"+period]          + [year+'0203'+dti, path+"DYJetsToLL_PtZ-100To250.txt"],
        ["DYJetsToLL_PtZ-250To400_"+period]          + [year+'0204'+dti, path+"DYJetsToLL_PtZ-250To400.txt"],
        ["DYJetsToLL_PtZ-400To650_"+period]          + [year+'0205'+dti, path+"DYJetsToLL_PtZ-400To650.txt"],
        ["DYJetsToLL_PtZ-650ToInf_"+period]          + [year+'0206'+dti, path+"DYJetsToLL_PtZ-650ToInf.txt"],
        ##["DYJetsToLL_Pt-50To100_"+period]            + [year+'0202'+dti, path+"DYJetsToLL_Pt-50To100.txt"],
        ##["DYJetsToLL_Pt-100To250_"+period]           + [year+'0203'+dti, path+"DYJetsToLL_Pt-100To250.txt"],
        ##["DYJetsToLL_Pt-250To400_"+period]           + [year+'0204'+dti, path+"DYJetsToLL_Pt-250To400.txt"],
        ##["DYJetsToLL_Pt-400To650_"+period]           + [year+'0205'+dti, path+"DYJetsToLL_Pt-400To650.txt"],
        ##["DYJetsToLL_Pt-650ToInf_"+period]           + [year+'0206'+dti, path+"DYJetsToLL_Pt-650ToInf.txt"],
        ##["DYJetsToLL_HT-Inclusive_"+period]          + [year+'0207'+dti, path+"DYJetsToLL_HT-Inclusive.txt"],
        ##["DYJetsToLL_HT-70to100_"+period]            + [year+'0208'+dti, path+"DYJetsToLL_HT-70to100.txt"],
        ##["DYJetsToLL_HT-100to200_"+period]           + [year+'0209'+dti, path+"DYJetsToLL_HT-100to200.txt"],
        ##["DYJetsToLL_HT-200to400_"+period]           + [year+'0210'+dti, path+"DYJetsToLL_HT-200to400.txt"],
        ##["DYJetsToLL_HT-400to600_"+period]           + [year+'0211'+dti, path+"DYJetsToLL_HT-400to600.txt"],
        ##["DYJetsToLL_HT-600to800_"+period]           + [year+'0212'+dti, path+"DYJetsToLL_HT-600to800.txt"],
        ##["DYJetsToLL_HT-800to1200_"+period]          + [year+'0213'+dti, path+"DYJetsToLL_HT-800to1200.txt"],
        ##["DYJetsToLL_HT-1200to2500_"+period]         + [year+'0214'+dti, path+"DYJetsToLL_HT-1200to2500.txt"],
        ##["DYJetsToLL_HT-2500toInf_"+period]          + [year+'0215'+dti, path+"DYJetsToLL_HT-2500toInf.txt"],
    ]

    TTFullLep = [
        ["TTTo2L2Nu_"+period]                        + [year+'0300'+dti, path+"TTTo2L2Nu.txt"],
    ]

    TTSemiLep = [
        ["TTToSemiLeptonic_"+period]                 + [year+'0301'+dti, path+"TTToSemiLeptonic.txt"],
    ]

    ST = [
        ["ST_tW_top_"+period]                        + [year+'0400'+dti, path+"ST_tW_top.txt"],
        ["ST_tW_antitop_"+period]                    + [year+'0401'+dti, path+"ST_tW_antitop.txt"],
        ["ST_t-channel_top_"+period]                 + [year+'0402'+dti, path+"ST_t-channel_top.txt"],
        ["ST_t-channel_antitop_"+period]             + [year+'0403'+dti, path+"ST_t-channel_antitop.txt"],
        ["ST_s-channel_"+period]                     + [year+'0404'+dti, path+"ST_s-channel.txt"],
    ]

    VZ = [
        ["ZZTo2L2Nu_"+period]                        + [year+'0501'+dti, path+"ZZTo2L2Nu.txt"],
        ["ZZTo4L_"+period]                           + [year+'0502'+dti, path+"ZZTo4L.txt"],
        ["WZTo3LNu_"+period]                         + [year+'0512'+dti, path+"WZTo3LNu.txt"],
        #["ggToZZTo2e2mu_"+period]                    + [year+'0503'+dti, path+"ggToZZTo2e2mu.txt"],
        #["ggToZZTo2e2nu_"+period]                    + [year+'0504'+dti, path+"ggToZZTo2e2nu.txt"],
        #["ggToZZTo2e2tau_"+period]                   + [year+'0505'+dti, path+"ggToZZTo2e2tau.txt"],
        #["ggToZZTo2mu2nu_"+period]                   + [year+'0506'+dti, path+"ggToZZTo2mu2nu.txt"],
        #["ggToZZTo2mu2tau_"+period]                  + [year+'0507'+dti, path+"ggToZZTo2mu2tau.txt"],
        #["ggToZZTo4e_"+period]                       + [year+'0508'+dti, path+"ggToZZTo4e.txt"],
        #["ggToZZTo4mu_"+period]                      + [year+'0509'+dti, path+"ggToZZTo4mu.txt"],
        #["ggToZZTo4tau_"+period]                     + [year+'0510'+dti, path+"ggToZZTo4tau.txt"],
    ]

    ResidualSM = [
        #["ZZ_Inclusive_"+period]                     + [year+'0500'+dti, path+"ZZ.txt"],
        #["ZZ_Others_"+period]                        + [year+'0500'+dti, path+"ZZ.txt"],
        ["ZZTo2Q2L_"+period]                         + [year+'0504'+dti, path+"ZZTo2Q2L.txt"],
        #["WZ_Inclusive_"+period]                     + [year+'0510'+dti, path+"WZ.txt"],
        #["WZ_Others_"+period]                        + [year+'0510'+dti, path+"WZ.txt"],
        ["WZTo2Q2L_"+period]                         + [year+'0513'+dti, path+"WZTo2Q2L.txt"],
        #["WW_"+period]                               + [year+'0520'+dti, path+"WW.txt"],
        ["WWTo2L2Nu_"+period]                        + [year+'0521'+dti, path+"WWTo2L2Nu.txt"],
        ["ZZZ_"+period]                              + [year+'0600'+dti, path+"ZZZ.txt"],
        ["WZZ_"+period]                              + [year+'0601'+dti, path+"WZZ.txt"],
        ["WWZ_"+period]                              + [year+'0602'+dti, path+"WWZ.txt"],
        ["WWW_"+period]                              + [year+'0603'+dti, path+"WWW.txt"],
        ["TTWZ_"+period]                             + [year+'0700'+dti, path+"TTWZ.txt"],
        ["TTZZ_"+period]                             + [year+'0701'+dti, path+"TTZZ.txt"],
        ["TTWW_"+period]                             + [year+'0702'+dti, path+"TTWW.txt"],
        #["TWZToLL_thad_Wlept_"+period]               + [year+'0800'+dti, path+"TWZToLL_thad_Wlept.txt"],
        #["TWZToLL_tlept_Whad_"+period]               + [year+'0801'+dti, path+"TWZToLL_tlept_Whad.txt"],
        #["TWZToLL_tlept_Wlept_"+period]              + [year+'0802'+dti, path+"TWZToLL_tlept_Wlept.txt"],
        ["TTWJetsToLNu_"+period]                     + [year+'1000'+dti, path+"TTWJetsToLNu.txt"],
        ["TTWJetsToQQ_"+period]                      + [year+'1001'+dti, path+"TTWJetsToQQ.txt"],
        ["TTZToQQ_"+period]                          + [year+'1002'+dti, path+"TTZToQQ.txt"],
        ["TTZToNuNu_"+period]                        + [year+'1003'+dti, path+"TTZToNuNu.txt"],
        ["TTZToLL_"+period]                          + [year+'1004'+dti, path+"TTZToLL.txt"],
        ["tZq_ll_"+period]                           + [year+'1100'+dti, path+"tZq_ll.txt"],
        #["ttH_HToZZ_"+period]                        + [year+'1300'+dti, path+"ttH_HToZZ.txt"],
        #["ttHTobb_"+period]                          + [year+'1301'+dti, path+"ttHTobb.txt"],
        #["ttHToTauTau_"+period]                      + [year+'1302'+dti, path+"ttHToTauTau.txt"],
        #["GluGluHToWWTo2L2Nu_"+period]               + [year+'1400'+dti, path+"GluGluHToWWTo2L2Nu.txt"],
        #["GluGluHToZZTo4L_"+period]                  + [year+'1401'+dti, path+"GluGluHToZZTo4L.txt"],
        #["WplusH_HToZZTo4L_"+period]                 + [year+'1500'+dti, path+"WplusH_HToZZTo4L.txt"],
        #["WminusH_HToZZTo4L_"+period]                + [year+'1501'+dti, path+"WminusH_HToZZTo4L.txt"],
        #["ZH_HToBB_ZToLL_"+period]                   + [year+'1600'+dti, path+"ZH_HToBB_ZToLL.txt"],
        #["ZH_HToZZ_"+period]                         + [year+'1601'+dti, path+"ZH_HToZZ.txt"],
        #["QCD_Mu_Pt-15To20_"+period]                 + [year+'1800'+dti, path+"QCD_Mu_Pt-15To20.txt"],
        #["QCD_Mu_Pt-20To30_"+period]                 + [year+'1801'+dti, path+"QCD_Mu_Pt-20To30.txt"],
        #["QCD_Mu_Pt-30To50_"+period]                 + [year+'1802'+dti, path+"QCD_Mu_Pt-30To50.txt"],
        #["QCD_Mu_Pt-50To80_"+period]                 + [year+'1803'+dti, path+"QCD_Mu_Pt-50To80.txt"],
        #["QCD_Mu_Pt-80To120_"+period]                + [year+'1804'+dti, path+"QCD_Mu_Pt-80To120.txt"],
        #["QCD_Mu_Pt-120To170_"+period]               + [year+'1805'+dti, path+"QCD_Mu_Pt-120To170.txt"],
        #["QCD_Mu_Pt-170To300_"+period]               + [year+'1806'+dti, path+"QCD_Mu_Pt-170To300.txt"],
        #["QCD_Mu_Pt-300To470_"+period]               + [year+'1807'+dti, path+"QCD_Mu_Pt-300To470.txt"],
        #["QCD_Mu_Pt-470To600_"+period]               + [year+'1808'+dti, path+"QCD_Mu_Pt-470To600.txt"],
        #["QCD_Mu_Pt-600To800_"+period]               + [year+'1809'+dti, path+"QCD_Mu_Pt-600To800.txt"],
        #["QCD_Mu_Pt-800To1000_"+period]              + [year+'1810'+dti, path+"QCD_Mu_Pt-800To1000.txt"],
        #["QCD_Mu_Pt-1000ToInf_"+period]              + [year+'1811'+dti, path+"QCD_Mu_Pt-1000ToInf.txt"],
        #["WJetsToLNu_"+period]                       + [year+'1900'+dti, path+"WJetsToLNu.txt"],
        #["WGToLNuG_"+period]                         + [year+'1901'+dti, path+"WGToLNuG.txt"],
    ]

    
    if period == "0_16":
        ResidualSM_0_16 = ResidualSM
        VZ_0_16 = VZ
        ST_0_16 = ST
        TTSemiLep_0_16 = TTSemiLep
        TTFullLep_0_16 = TTFullLep
        DYPt0To50_0_16 = DYPt0To50
        DYPt50ToInf_0_16 = DYPt50ToInf
    elif period == "1_16":
        ResidualSM_1_16 = ResidualSM
        VZ_1_16 = VZ
        ST_1_16 = ST
        TTSemiLep_1_16 = TTSemiLep
        TTFullLep_1_16 = TTFullLep
        DYPt0To50_1_16 = DYPt0To50
        DYPt50ToInf_1_16 = DYPt50ToInf
    elif period == "0_17":
        ResidualSM_0_17 = ResidualSM
        VZ_0_17 = VZ
        ST_0_17 = ST
        TTSemiLep_0_17 = TTSemiLep
        TTFullLep_0_17 = TTFullLep
        DYPt0To50_0_17 = DYPt0To50
        DYPt50ToInf_0_17 = DYPt50ToInf
    elif period == "0_18":
        ResidualSM_0_18 = ResidualSM
        VZ_0_18 = VZ
        ST_0_18 = ST
        TTSemiLep_0_18 = TTSemiLep
        TTFullLep_0_18 = TTFullLep
        DYPt0To50_0_18 = DYPt0To50
        DYPt50ToInf_0_18 = DYPt50ToInf

