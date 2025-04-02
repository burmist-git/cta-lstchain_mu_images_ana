#pragma once

//root
#include "TROOT.h"

//C, C++
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

class dl1_muon_csv_reader {
public:    

  dl1_muon_csv_reader(TString csv_file_in, Int_t n_meta_data = 7, Int_t nch = 1855);
  ~dl1_muon_csv_reader();
  //
  inline const vector<Int_t>& get_obs_id() const {return _obs_id_v;};
  inline const vector<Int_t>& get_event_id() const {return _event_id_v;};
  inline const vector<Float_t>& get_mc_energy() const {return _mc_energy_v;};
  inline const vector<Float_t>& get_mc_core_x() const {return _mc_core_x_v;};
  inline const vector<Float_t>& get_mc_core_y() const {return _mc_core_y_v;};
  inline const vector<Float_t>& get_mc_alt() const {return _mc_alt_v;};
  inline const vector<Float_t>& get_mc_az()  const {return _mc_az_v;};
  //
  inline const vector<vector<Float_t>>& get_ch()  const {return _ch_v;};
  inline const vector<vector<Float_t>>& get_cht()  const {return _cht_v;};
  inline const vector<vector<Int_t>>& get_chm()  const {return _chm_v;};
  inline const vector<vector<Float_t>>& get_chmf()  const {return _chmf_v;};
  //
  
private:

  vector<Int_t> _obs_id_v;
  vector<Int_t> _event_id_v;
  vector<Float_t> _mc_energy_v;
  vector<Float_t> _mc_core_x_v;
  vector<Float_t> _mc_core_y_v;
  vector<Float_t> _mc_alt_v;
  vector<Float_t> _mc_az_v;
  //
  vector<vector<Float_t>> _ch_v;
  vector<vector<Float_t>> _cht_v;
  vector<vector<Int_t>> _chm_v;
  vector<vector<Float_t>> _chmf_v;

  void load_csv_data(TString csv_file_in);

  Int_t _n_meta_data;
  Int_t _nch;
  
};
