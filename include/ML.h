#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <stdlib.h>
#include <TStyle.h>
#include <TH2D.h>
#include <TLegend.h>
#include <TColor.h>
#include <math.h>
#include <THnSparse.h>
#include <map>
#include <string>
#include <vector>
#include <random>
#include "THnSparse.h"
#include "TF1.h"
#include "TSystem.h"
#include "TLorentzVector.h"
#include "TGraphAsymmErrors.h"
#include <iomanip>
#include <sys/stat.h>
#include <time.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidcsv.h"
#include <torch/torch.h>
#include <torch/script.h>

using namespace std;

//-------------------------------------------------------------------------
// NN Model (Torch)
//-------------------------------------------------------------------------
class NN_Torch {
    private:
        torch::jit::script::Module NN_model;
    public:
        void readFile( string model_file ){
            NN_model = torch::jit::load(model_file.c_str());
            torch::NoGradGuard no_grad; // ensures that autograd is off
            NN_model.eval();
        }
        
        float predict( vector<float> mlp_input, bool binary=true  ){
            std::vector<torch::jit::IValue> inputs;
            inputs.push_back(torch::tensor(mlp_input));
            at::Tensor result = NN_model.forward(inputs).toTensor();
            float prediction = result[0].item<float>();
            
            if( binary ){ 
                return 1-prediction;
            }else{
                return prediction;
            }
        }
};

