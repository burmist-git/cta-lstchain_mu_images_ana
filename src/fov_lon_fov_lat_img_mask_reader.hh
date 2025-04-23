#pragma once

//root
#include "TROOT.h"

//C, C++
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

class fov_lon_fov_lat_img_mask_reader {
public:    

  fov_lon_fov_lat_img_mask_reader(TString csv_file_in);
  ~fov_lon_fov_lat_img_mask_reader();
  
  inline const Float_t get_radius_fit() const {return _radius_fit;};
  inline const Float_t get_center_fov_lon_fit() const {return _center_fov_lon_fit;};
  inline const Float_t get_center_fov_lat_fit() const {return _center_fov_lat_fit;};
  //  
  inline const vector<Float_t>& get_fov_lon_v() const {return _fov_lon_v;};
  inline const vector<Float_t>& get_fov_lat_v() const {return _fov_lat_v;};
  inline const vector<Float_t>& get_img_v() const {return _img_v;};
  inline const vector<Float_t>& get_mask_v() const {return _mask_v;};
  //
  
private:

  //
  vector<Float_t> _fov_lon_v;
  vector<Float_t> _fov_lat_v;
  vector<Float_t> _img_v;
  vector<Float_t> _mask_v;
  //
  Float_t _radius_fit;
  Float_t _center_fov_lon_fit;
  Float_t _center_fov_lat_fit;
  //
  void load_csv_data(TString csv_file_in);
  //
  Int_t _nch;  
};
