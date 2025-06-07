set(ANALYSIS "AP_EFT_ML_R2")

target_sources(RunAnalysis PRIVATE ${ANALYSIS}/src/HEPHeroB.cpp ${ANALYSIS}/src/HEPRoutines.cpp ${ANALYSIS}/src/HEPWeights.cpp ${ANALYSIS}/src/HEPVerticalSystematics.cpp ${ANALYSIS}/src/EXPTools.cpp ${ANALYSIS}/src/ANATools.cpp ${ANALYSIS}/src/spin_correlation.cpp ${ANALYSIS}/src/RoccoR.cc ${ANALYSIS}/src/correction.cc ${ANALYSIS}/src/formula_ast.cc)
