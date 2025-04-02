#pragma once

//my
#include "pixel_info.hh"

//root
#include <TObject.h>
#include <TH2Poly.h>
#include <TGraph.h>
#include <TVector2.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLine.h>

//c, c++
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <iomanip>

class pmtCameraHist: public TH2Poly {

public:
  
  pmtCameraHist(const char* name, const char* title, pmtCameraHist *pmtHist);
  pmtCameraHist(const char* name, const char* title, const char* mapping_csv_file, Double_t rot_alpha_deg);
  //pmtCameraHist(const char* name, const char* title, const char* mapping_csv_file, Double_t rot_alpha_deg, TH1D *h1_distance_between_pixels);
  ~pmtCameraHist();
  void dump_mapping_info();
  void test(TString pdf_out_name = "pmtCameraHist_test.pdf");
  void Clean();
  //
  TCanvas *Draw_cam(TString settings = "", TString pdf_out_file = "");
  //
  TString _name;
  TString _title;
  //
  inline const std::vector<pixel_info> &get_pixel_vec() const {return _pixel_vec;}
  void Fill_hist(const std::vector<Float_t>& cam_image);
  //  
  //static void rotatePix(Double_t alpha, const Double_t xo, const Double_t yo, Double_t &xn, Double_t &yn);
  
  private:

  double _pixel_size;
  double _pixel_pitch;
  Double_t _rot_alpha_deg;

  std::vector<pixel_info> _pixel_vec;
  void load_mapping(const char* mapping_csv_file);
  
};
