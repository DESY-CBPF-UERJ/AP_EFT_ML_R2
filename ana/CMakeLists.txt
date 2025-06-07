set(ANALYSIS "AP_EFT_ML_R2")

target_sources(RunAnalysis PRIVATE ${ANALYSIS}/ana/Sonnenschein.cpp ${ANALYSIS}/ana/SgnStudy.cpp ${ANALYSIS}/ana/Test.cpp)
