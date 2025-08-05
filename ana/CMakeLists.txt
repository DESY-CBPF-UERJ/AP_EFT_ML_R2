set(ANALYSIS "AP_EFT_ML_R2")

target_sources(RunAnalysis PRIVATE ${ANALYSIS}/ana/BTagEffMap.cpp ${ANALYSIS}/ana/TestWgt.cpp ${ANALYSIS}/ana/Zrecoil.cpp ${ANALYSIS}/ana/CompareEff.cpp ${ANALYSIS}/ana/Sonnenschein.cpp ${ANALYSIS}/ana/SgnStudy.cpp ${ANALYSIS}/ana/Test.cpp)
