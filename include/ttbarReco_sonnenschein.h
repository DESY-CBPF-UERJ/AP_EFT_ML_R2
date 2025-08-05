#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <TMath.h>
#include <Math/Polynomial.h>
#include <TLorentzVector.h>
#include <complex>
#include <TRandom3.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

using namespace std;


//-------------------------------------------------------------------------
// Top-Antitop reconstruction
//-------------------------------------------------------------------------
class ttbarReconstruction {
    private:
        rapidjson::Document ttbar_pdf;
        rapidjson::Document ttbar_resolution;
        TRandom3* r3_;

        // structure to store one solution of the kinematic reconstruction
        struct ZSolutionKinRecoDilepton
        {
          // constructor
          // (set weight to -1 by default)
          ZSolutionKinRecoDilepton(): zWeight(-1.0) {;}
          // top and antitop four momenta
          TLorentzVector zT, zTbar;
          // number of b-tagged jets (can be 0, 1 or 2)
          int zBTag;
          // weight of this solution
          double zWeight;
        };

        float TripleGaus(float A, float B, float mean1, float sigma1, float mean2, float sigma2, float mean3, float sigma3){
            float flat_rand = r3_->Rndm();
            
            float tripleGauss_output;
            if( flat_rand < A ){
                tripleGauss_output = r3_->Gaus(mean1,sigma1);
            }else if( (flat_rand >= A) && (flat_rand < A+B) ){
                tripleGauss_output = r3_->Gaus(mean2,sigma2);
            }else{
                tripleGauss_output = r3_->Gaus(mean3,sigma3);
            }

            return tripleGauss_output;
        }

        float SmearRef(float value_ref, string resolution_name){
            
            float A = ttbar_resolution[resolution_name.c_str()]["A"].GetFloat();
            float B = ttbar_resolution[resolution_name.c_str()]["B"].GetFloat();
            float mean1 = ttbar_resolution[resolution_name.c_str()]["mean1"].GetFloat();
            float sigma1 = ttbar_resolution[resolution_name.c_str()]["sigma1"].GetFloat();
            float mean2 = ttbar_resolution[resolution_name.c_str()]["mean2"].GetFloat();
            float sigma2 = ttbar_resolution[resolution_name.c_str()]["sigma2"].GetFloat();
            float mean3 = ttbar_resolution[resolution_name.c_str()]["mean3"].GetFloat();
            float sigma3 = ttbar_resolution[resolution_name.c_str()]["sigma3"].GetFloat();

            size_t spos = resolution_name.find("_");
            string operation_name = resolution_name.substr(spos+1, resolution_name.length());
            spos = operation_name.find("_");
            string var_name = operation_name.substr(spos+1, operation_name.length());
            operation_name = operation_name.substr(0, spos);
            
            float value_smeared;
            if( operation_name == "ratio" ){
                value_smeared = value_ref * TripleGaus(A, B, mean1, sigma1, mean2, sigma2, mean3, sigma3);
            }else if( operation_name == "diff" ){
                value_smeared = value_ref + TripleGaus(A, B, mean1, sigma1, mean2, sigma2, mean3, sigma3);
            }

            if( var_name == "phi" ){
                if( value_smeared > M_PI ) value_smeared = value_smeared - 2*M_PI;
                else if( value_smeared < -M_PI ) value_smeared = 2*M_PI + value_smeared;
            }
                
            return value_smeared;
        }

        
        vector< vector<TLorentzVector>> GetSmearCombinations(const TLorentzVector& lm_ref, const TLorentzVector& lp_ref, const TLorentzVector& b_ref, const TLorentzVector& bbar_ref, const TLorentzVector& met_ref, bool smeared){ 

            vector< vector<TLorentzVector>> combinations;
            combinations.push_back({lm_ref, lp_ref, b_ref, bbar_ref, met_ref});
            
            if( smeared ){
                vector< vector<TLorentzVector>> candidates;
                vector<float> weights;
                
                vector<float> b_pt;
                vector<float> bbar_pt;
                vector<float> met_pt;
                vector<float> met_phi;
                for (int isp = 0; isp < 3; isp++) {    
                    b_pt.push_back(SmearRef(b_ref.Pt(), "b_ratio_pt"));
                    bbar_pt.push_back(SmearRef(bbar_ref.Pt(), "b_ratio_pt"));
                    met_pt.push_back(SmearRef(met_ref.Pt(), "MET_ratio_pt"));
                    met_phi.push_back(SmearRef(met_ref.Phi(), "MET_diff_phi"));
                }
                
                for (int i0 = 0; i0 < 3; i0++) {
                      for (int i1 = 0; i1 < 3; i1++) {
                            for (int i2 = 0; i2 < 3; i2++) {
                              for (int i3 = 0; i3 < 3; i3++) {
                                TLorentzVector b;
                                TLorentzVector bbar;
                                TLorentzVector met;  
                                b.SetPtEtaPhiM(b_pt[i0], b_ref.Eta(), b_ref.Phi(), 4.8);
                                bbar.SetPtEtaPhiM(bbar_pt[i1], bbar_ref.Eta(), bbar_ref.Phi(), 4.8);
                                met.SetPtEtaPhiM(met_pt[i2], 0., met_phi[i3], 0.);   
                                
                                // Uncomment if I decide not to use all solutions  
                                /*  
                                TLorentzVector lp_b = lp_ref + b;
                                TLorentzVector lm_bbar = lm_ref + bbar;
                                TLorentzVector lp_b_MET = lp_b + met;
                                TLorentzVector lm_bbar_MET = lm_bbar + met;  
                            
                                // calculate weight 
                                float w_lp_b = getPDF(lp_b.M(), "lb_mass_pdf");
                                float w_lm_bbar = getPDF(lm_bbar.M(), "lb_mass_pdf");
                                float w_lp_b_MET = getPDF(lp_b_MET.Mt(), "lbMET_mt_pdf");
                                float w_lm_bbar_MET = getPDF(lm_bbar_MET.Mt(), "lbMET_mt_pdf");  
                                float weight = w_lp_b * w_lm_bbar * w_lp_b_MET * w_lm_bbar_MET;  
                                                            
                                candidates.push_back({lm_ref, lp_ref, b, bbar, met});
                                weights.push_back(weight);
                                */
                                combinations.push_back({lm_ref, lp_ref, b, bbar, met});  
                              }
                            }
                      }
                }

                // Uncomment if I decide not to use all solutions
                /*
                // Create a vector of indices
                vector<int> indices(candidates.size());
                iota(indices.begin(), indices.end(), 0); // Fill with 0, 1, 2, ...
            
                // Sort the indices based on the values in the weights vector
                sort(indices.begin(), indices.end(), [&](int i, int j) {
                    return weights[i] > weights[j]; // Sort in descending order of scores
                });
            
                // Fill the combinations in the sorted order
                int n_smeared_sol = 0;
                for (int i : indices) {
                    if( n_smeared_sol == 15 ) break;
                    combinations.push_back(candidates[i]);
                    n_smeared_sol += 1;
                }
                */
            }

            return combinations;
        }
        
            
        float getPDF( float input_value, string pdf_name ){
            float pdf_value;
            
            rapidjson::Value& bins = ttbar_pdf[pdf_name.c_str()]["bins"];
            assert(bins.IsArray());
            rapidjson::Value& PDF = ttbar_pdf[pdf_name.c_str()]["pdf"];
            assert(PDF.IsArray());

            if( input_value < bins[0].GetFloat() ){
                pdf_value = 0;
            }else if( input_value >= bins[bins.Size()-1].GetFloat() ){
                pdf_value = 0;
            }else{
                for (int iE = 0; iE < bins.Size()-1; iE++) {
                    float x_s = bins[iE].GetFloat();
                    float x_e = bins[iE+1].GetFloat();
                    if( (input_value >= x_s) && (input_value < x_e) ){
                        float y_s = PDF[iE].GetFloat();
                        float y_e = PDF[iE+1].GetFloat();
                        float a = (y_e-y_s)/(x_e-x_s);
                        float b = y_s - a*x_s;
                        pdf_value = a*input_value+b;
                        break;
                    }
                }
            }
            
            return 100*pdf_value; 
        }


        // >>>>>>>>>>>>>>>>> SolveKinRecoDilepton routine >>>>>>>>>>>>>>>>>>>>>>
        // Routine to solve the kinreco problem for given b, bbar jets
        // Arguments:
        //    const TLorentzVector& lm:   lepton- momentum
        //    const TLorentzVector& lp:   lepton+ momentum
        //    const TLorentzVector& b:    b momentum
        //    const TLorentzVector& bbar: bbar momentum
        //    const TLorentzVector& met:  missing transverse energy (MET)
        // Returns the ZSolutionKinRecoDilepton pointer (see above)
        // For math, see Lars Sonnenschein's paper Phys.Rev. D73 (2006) 054015 [Erratum Phys.Rev. D73 (2006) 054015]
        // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        ZSolutionKinRecoDilepton* SolveKinRecoDilepton(const TLorentzVector& lm_ref, const TLorentzVector& lp_ref, 
          const TLorentzVector& b_ref, const TLorentzVector& bbar_ref, const TLorentzVector& met_ref, bool smeared)
        {
          // constants
          const double massW = 80.4; // W boson mass
          const double massTop = 172.5; // top quark mass

          TLorentzVector nuBest, nubarBest;
          double weightBest = -1.0;

          vector< vector<TLorentzVector>> combinations = GetSmearCombinations(lm_ref, lp_ref, b_ref, bbar_ref, met_ref, smeared); 

          TLorentzVector lm;
          TLorentzVector lp;
          TLorentzVector b;
          TLorentzVector bbar;
          TLorentzVector met;
            
          // Loop on the smearing combinations
          for(int ic = 0; ic < combinations.size(); ic++){  

              lm = combinations.at(ic).at(0);
              lp = combinations.at(ic).at(1);
              b = combinations.at(ic).at(2);
              bbar = combinations.at(ic).at(3);
              met = combinations.at(ic).at(4);
            
              // Transform input into double variables with short names
              // jet1 (b)
              double xb = b.X();
              double yb = b.Y();
              double zb = b.Z();
              double mb = b.M();
              double mb2 = mb * mb;
              double eb = b.E();
              double eb2 = eb * eb;
              // jet2 (bbar)
              double xbbar = bbar.X();
              double ybbar = bbar.Y();
              double zbbar = bbar.Z();
              double mbbar = bbar.M();
              double mbbar2 = mbbar * mbbar;
              double ebbar = bbar.E();
              double ebbar2 = ebbar * ebbar;
              // el (lm)
              double xlm = lm.X();
              double xlm2 = xlm * xlm;
              double ylm = lm.Y();
              double ylm2 = ylm * ylm;
              double zlm = lm.Z();
              double zlm2 = zlm * zlm;
              double mlm = lm.M();
              double mlm2 = mlm * mlm;
              double elm = lm.E();
              double elm2 = elm * elm;
              // mu (lp)
              double xlp = lp.X();
              double xlp2 = xlp * xlp;
              double ylp = lp.Y();
              double ylp2 = ylp * ylp;
              double zlp = lp.Z();
              double zlp2 = zlp * zlp;
              double mlp = lp.M();
              double mlp2 = mlp * mlp;
              double elp = lp.E();
              double elp2 = elp * elp;
              // MET
              double ex = met.Px();
              double ex2 = ex * ex;
              double ey = met.Py();
              double ey2 = ey * ey;
              // constraints
              double mw2 = massW * massW;
              double mt2 = massTop * massTop;
              double mn2 = 0.0;
              
              // Calculate coefficients from Lars' paper
              // a coefs
              double a1 = (eb + elp) * (mw2 - mlp2 - mn2) - elp * (mt2 - mb2 - mlp2 - mn2) + 2 * eb * elp2 - 2 * elp * (xb * xlp + yb * ylp + zb * zlp);
            
              double a12 = a1 * a1;
              double a2 = 2 * (eb * xlp - elp * xb);
              double a22 = a2 * a2;
              double a3 = 2 * (eb * ylp - elp * yb);
              double a32 = a3 * a3;
              double a4 = 2 * (eb * zlp - elp * zb);
              double a42 = a4 * a4;
              // b coefs
              double b1 = (ebbar + elm) * (mw2 - mlm2 - mn2) - elm * (mt2 - mbbar2 - mlm2 - mn2) + 2 * ebbar * elm2 - 2 * elm * (xbbar * xlm + ybbar * ylm + zbbar * zlm);
              double b12 = b1 * b1;
              double b2 = 2 * (ebbar * xlm - elm * xbbar);
              double b22 = b2 * b2;
              double b3 = 2 * (ebbar * ylm - elm * ybbar);
              double b32 = b3 * b3;
              double b4 = 2 * (ebbar * zlm - elm * zbbar);
              double b42 = b4 * b4;
              // c coefs
              double c22 = TMath::Power(mw2 - mlp2 - mn2, 2.0) - 4 * (elp2 - zlp2) * a12 / a42 - 4 * (mw2 - mlp2 - mn2) * zlp * a1 / a4;
              double c21 = 4 * (mw2 - mlp2 - mn2) * (xlp - zlp * a2 / a4) - 8 * (elp2 - zlp2) * a1 * a2 / a42 - 8 * xlp * zlp * a1 / a4;
              double c20 = -4 * (elp2 - xlp2) - 4 * (elp2 - zlp2) * a22 / a42 - 8 * xlp * zlp * a2 / a4;
              double c11 = 4 * (mw2 - mlp2 - mn2) * (ylp - zlp * a3 / a4) - 8 * (elp2 - zlp2) * a1 * a3 / a42 - 8 * ylp * zlp * a1 / a4;
              double c10 = -8 * (elp2 - zlp2) * a2 * a3 / a42 + 8 * xlp * ylp - 8 * xlp * zlp * a3 / a4 - 8 * ylp * zlp * a2 / a4;
              double c00 = -4 * (elp2 - ylp2) - 4 * (elp2 - zlp2) * a32 / a42 - 8 * ylp * zlp * a3 / a4;
              // d' coefs
              double d22p = TMath::Power(mw2 - mlm2 - mn2, 2.0) - 4 * (elm2 - zlm2) * b12 / b42 - 4 * (mw2 - mlm2 - mn2) * zlm * b1 / b4;
              double d21p = 4 * (mw2 - mlm2 - mn2) * (xlm - zlm * b2 / b4) - 8 * (elm2 - zlm2) * b1 * b2 / b42 - 8 * xlm * zlm * b1 / b4;
              double d20p = -4 * (elm2 - xlm2) - 4 * (elm2 - zlm2) * b22 / b42 - 8 * xlm* zlm * b2 / b4;
              double d11p = 4 * (mw2 - mlm2 - mn2) * (ylm - zlm * b3 / b4) - 8 * (elm2 - zlm2) * b1 * b3 / b42 - 8 * ylm * zlm * b1 / b4;
              double d10p = -8 * (elm2 - zlm2) * b2 * b3 / b42 + 8 * xlm * ylm - 8 * xlm * zlm * b3 / b4 - 8 * ylm * zlm * b2 / b4;
              double d00p = -4 * (elm2 - ylm2) - 4 * (elm2 - zlm2) * b32 / b42 - 8 * ylm * zlm * b3 / b4;
              // d coefs
              double d22 = d22p + ex2 * d20p + ey2 * d00p + ex * ey * d10p + ex * d21p + ey * d11p;
              double d21 = - d21p - 2 * ex * d20p - ey * d10p;
              double d20 = d20p;
              double d11 = - d11p - 2 * ey * d00p - ex * d10p;
              double d10 = d10p;
              double d00 = d00p;
              // h coefs
              double h4 = c00 * c00 * d22 * d22 + c11 * d22 * (c11 * d00 - c00 * d11) 
                        + c00 * c22 * (d11 * d11 - 2 * d00 * d22) + c22 * d00 * (c22 * d00 - c11 * d11);
              double h3 = c00 * d21 * (2 * c00 * d22 - c11 * d11) + c00 * d11 * (2 * c22 * d10 + c21 * d11)
                        + c22 * d00 * (2 * c21 * d00 - c11 * d10) - c00 * d22 * (c11 * d10 + c10 * d11) 
                        -2 * c00 * d00 * (c22 * d21 + c21 * d22) - d00 * d11 * (c11 * c21 + c10 * c22) 
                        + c11 * d00 * (c11 * d21 + 2 * c10 * d22);
              double h2 = c00 * c00 * (2 * d22 * d20 + d21 * d21) - c00 * d21 * (c11 * d10 + c10 * d11)
                        + c11 * d20 * (c11 * d00 - c00 * d11) + c00 * d10 * (c22 * d10 - c10 * d22)
                        + c00 * d11 * (2 * c21 * d10 + c20 * d11) + (2 * c22 * c20 + c21 * c21) * d00 * d00
                        - 2 * c00 * d00 * (c22 * d20 + c21 * d21 + c20 * d22)
                        + c10 * d00 * (2 * c11 * d21 + c10 * d22) - d00 * d10 * (c11 * c21 + c10 * c22)
                        - d00 * d11 * (c11 * c20 + c10 * c21);
              double h1 = c00 * d21 * (2 * c00 * d20 - c10 * d10) - c00 * d20 * (c11 * d10 + c10 * d11)
                        + c00 * d10 * (c21 * d10 + 2 * c20 * d11) - 2 * c00 * d00 * (c21 * d20 + c20 * d21)
                        + c10 * d00 * (2 * c11 * d20 + c10 * d21) + c20 * d00 * (2 * c21 * d00 - c10 * d11) // this is correct
                        //+ c10 * d00 * (2 * c11 * d20 + c10 * d21) - c20 * d00 * (2 * c21 * d00 - c10 * d11) // this is wrong
                        - d00 * d10 * (c11 * c20 + c10 * c21);
              double h0 = c00 * c00 * d20 * d20 + c10 * d20 * (c10 * d00 - c00 * d10)
                        + c20 * d10 * (c00 * d10 - c10 * d00) + c20 * d00 * (c20 * d00 - 2 * c00 * d20);
            
              
              // solve quartic equation
              ROOT::Math::Polynomial eq(4);
              double pars[5] = { h4, h3, h2, h1, h0 };
              // apply global scaling to avoid possible numerical precision problems
              double minpar = 1e100;
              for(int p = 0; p < 5; p++)
                if(TMath::Abs(pars[p]) < minpar)
                  minpar = pars[p];
              for(int p = 0; p < 5; p++)
                pars[p] /= minpar;
              //printf("parameters: %e %e %e %e %e\n", pars[0], pars[1], pars[2], pars[3], pars[4]);
              eq.SetParameters(pars);
              std::vector<double> roots = eq.FindRealRoots();
    
              // Loop on the roots
              for(int s = 0; s < roots.size(); s++){
                // check main equation
                double sol = pars[0] + pars[1]*roots[s] + pars[2]*roots[s]*roots[s] + pars[3]*roots[s]*roots[s]*roots[s] + pars[4]*roots[s]*roots[s]*roots[s]*roots[s];
                //printf("x: %e  solution: %e\n", roots[s], sol);
            
                // x components
                double xn = roots[s];
                double xnbar = ex - xn;
                // y components
                double c0 = c00;
                double c1 = c11 + c10 * xn;
                double c2 = c22 + c21 * xn + c20 * xn * xn;
                double d0 = d00;
                double d1 = d11 + d10 * xn;
                double d2 = d22 + d21 * xn + d20 * xn * xn;
                double yn = (c0 * d2 - c2 * d0) / (c1 * d0 - c0 * d1);
                double ynbar = ey - yn;
                // z components
                double zn = - (a1 + a2 * xn + a3 * yn) / a4;
                double znbar = - (b1 + b2 * xnbar + b3 * ynbar) / b4;
                // check nan
                if(xn != xn || xnbar != xnbar || yn != yn || ynbar != ynbar || zn != zn || znbar != znbar)
                {
                  continue;
                }
                TLorentzVector nu, nubar;
                nu.SetXYZM(xn, yn, zn, 0.0);
                nubar.SetXYZM(xnbar, ynbar, znbar, 0.0);
                  
                // calculate weight according to nu and nubar energies
                double wnu = getPDF(nu.E(), "nu_energy_pdf");
                double wnubar = getPDF(nubar.E(), "nu_energy_pdf");
                double weight = wnu * wnubar;
                  
                // update solution, if this is the best weight
                if(weight > weightBest)
                {
                  weightBest = weight;
                  nuBest = nu;
                  nubarBest = nubar;
                }
              }
          }
          
          // if the best weight is default negative, there is no solution
          if(weightBest < 0.0)
            return NULL;
          
          // store and return best solution as ZSolutionKinRecoDilepton instance
          ZSolutionKinRecoDilepton* solution = new ZSolutionKinRecoDilepton;
          solution->zT = (nuBest + lp + b);
          solution->zTbar = (nubarBest + lm + bbar);
          solution->zWeight = weightBest;

            
          return solution;
        }
    
    public:
        TLorentzVector t; 
        TLorentzVector tbar; 
        int solved;           // solution status (to be returned)
        int bTagBest;         // best number of b-tagged jets (maximum 2) 
        float finalWeight;    // best (largest) solution weight

        void addPDF( string pdf_file ){
            FILE *fp_pdf = fopen(pdf_file.c_str(), "r"); 
            char buf_pdf[0XFFFF];
            rapidjson::FileReadStream input_pdf(fp_pdf, buf_pdf, sizeof(buf_pdf));
            ttbar_pdf.ParseStream(input_pdf);
        }

        void addResolution( string pdf_file ){
            FILE *fp_pdf = fopen(pdf_file.c_str(), "r"); 
            char buf_pdf[0XFFFF];
            rapidjson::FileReadStream input_pdf(fp_pdf, buf_pdf, sizeof(buf_pdf));
            ttbar_resolution.ParseStream(input_pdf);

            r3_ = new TRandom3();
            r3_->SetSeed(89);
        }

        // >>>>>>>>>>>>>>>>>>>> KinRecoDilepton routine >>>>>>>>>>>>>>>>>>>>>>>>
        // Routine to solve the kinreco problem for the whole event (possibly with more than 2 jets)
        // Arguments:
        //    const TLorentzVector& lm:   lepton- momentum
        //    const TLorentzVector& lp:   lepton+ momentum
        //    const std::vector<TLorentzVector>& jets: container with jet momenta
        //    const TLorentzVector& met:  missing transverse energy (MET)
        //    const TLorentzVector& t:    top momentum (output)
        //    const TLorentzVector& tbar: top momentum (output)
        // Returns 1 for successful kinreco, 0 otherwise
        // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        void KinRecoDilepton(const TLorentzVector lm, const TLorentzVector lp, const std::vector<TLorentzVector> jets, const TLorentzVector met, bool smeared)
        {
          solved = 0;
          bTagBest = 0;
          finalWeight = 0.0;
          t = TLorentzVector(); // Reinitialize to zero  
          tbar = TLorentzVector(); // Reinitialize to zero  
          
          // container with solutions
          std::vector<ZSolutionKinRecoDilepton*> vSolutions;        

          // loop over 1st jet
          for(std::vector<TLorentzVector>::const_iterator jet1 = jets.begin(); jet1 != jets.end(); jet1++)
          {
            // skip if already have solution(s) with two b-tagged jets
            // loop over 2nd jet
            for(std::vector<TLorentzVector>::const_iterator jet2 = jets.begin(); jet2 != jets.end(); jet2++)
            {
              // skip same jets
              if(jet1 == jet2) continue;
              // for this pair of jets, calculate number of b-tagged jets,
              // b-tagged jets are provided with negative masses (see selection.h):
              // account for this, then switch their masses to normal
              int bTagThis = 0;
              TLorentzVector jetB, jetBbar;
              if(jet1->M() < 0)
              {
                TLorentzVector jet;
                jet.SetPtEtaPhiM(jet1->Pt(), jet1->Eta(), jet1->Phi(), -1 * jet1->M());
                jetB = jet;
                bTagThis++;
              }
              else
                jetB = *jet1;
              if(jet2->M() < 0)
              {
                TLorentzVector jet;
                jet.SetPtEtaPhiM(jet2->Pt(), jet2->Eta(), jet2->Phi(), -1 * jet2->M());
                jetBbar = jet;
                bTagThis++;
              }
              else
                jetBbar = *jet2;
              // get solution
              TLorentzVector tThis, tbarThis;
              ZSolutionKinRecoDilepton* solution = SolveKinRecoDilepton(lm, lp, jetB, jetBbar, met, smeared);
              if(!solution || solution->zWeight < 0)
                continue;
              // set b-tagging number
              solution->zBTag = bTagThis;
              // push to the container
              vSolutions.push_back(solution);
            }
          }
          
          // find best solution, preference order:
          //   with 2 b-tagged jets, if no then
          //   with 1 b-tagged jet, if no then
          //   with 0 b-tagged jets. (removed)
          // If more than one solution with the same number of b-tagged jets 
          // is available, take the solution with the largest weight 
          for(std::vector<ZSolutionKinRecoDilepton*>::iterator it = vSolutions.begin(); it != vSolutions.end(); it++){
            ZSolutionKinRecoDilepton* sol = *it;
            if(sol->zBTag < bTagBest){        // worse b-tagging
              continue;
            }else if(sol->zBTag > bTagBest){  // better b-tagging
              bTagBest = sol->zBTag;
              t = sol->zT;
              tbar = sol->zTbar;
              solved = 1;
              finalWeight = sol->zWeight;
            }else{                            // same b-tagging: check weight
              if( (sol->zWeight > finalWeight) && (bTagBest >= 1) ){
                t = sol->zT;
                tbar = sol->zTbar;
                solved = 1;
                finalWeight = sol->zWeight;
              }
            }
          }
        
          // all done, clear memory and return
          for(std::vector<ZSolutionKinRecoDilepton*>::iterator it = vSolutions.begin(); it != vSolutions.end(); it++)
            delete (*it);
            
        }
        
};


