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
  pmtCameraHist(const char* name, const char* title, const char* mapping_csv_file, Double_t rot_alpha_deg = 0.0, bool lon_lat_key = false);

  ~pmtCameraHist();
  void dump_mapping_info();
  void test(TString pdf_out_name = "pmtCameraHist_test.pdf");
  void test_out_root(TString root_out_name = "hist_pmtCameraHist_test.root");

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
  inline void set_lon_lat_key(bool lon_lat_key) {_lon_lat_key = lon_lat_key;}
  
  //static void rotatePix(Double_t alpha, const Double_t xo, const Double_t yo, Double_t &xn, Double_t &yn);
  
private:

  double _pixel_size;
  double _pixel_pitch;
  Double_t _rot_alpha_deg;

  bool _lon_lat_key;
  
  std::vector<pixel_info> _pixel_vec;
  void load_mapping(const char* mapping_csv_file);
  void load_mapping_log_lat(const char* mapping_csv_file);
  
};
