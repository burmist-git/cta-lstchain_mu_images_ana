#pragma once

//root
#include "TROOT.h"

//C, C++
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

class dl1_muon_ctapipe_csv_reader {
public:    

  dl1_muon_ctapipe_csv_reader(TString csv_file_in, Int_t n_meta_data = 35, Int_t nch = 1855);
  ~dl1_muon_ctapipe_csv_reader();
  //

  inline const vector<Int_t>& get_mc_obs_id_v() const {return _mc_obs_id_v;};
  inline const vector<Int_t>& get_mc_event_id_v() const {return _mc_event_id_v;};
  //
  inline const vector<Float_t>& get_mc_energy_v() const {return _mc_energy_v;};
  inline const vector<Float_t>& get_mc_core_x_v() const {return _mc_core_x_v;};
  inline const vector<Float_t>& get_mc_core_y_v() const {return _mc_core_y_v;};
  inline const vector<Float_t>& get_mc_alt_v() const {return _mc_alt_v;};
  inline const vector<Float_t>& get_mc_az_v() const {return _mc_az_v;};
  //
  inline const vector<Int_t>& get_image_obs_id_v() const {return _image_obs_id_v;};
  inline const vector<Int_t>& get_image_event_id_v() const {return _image_event_id_v;};
  //
  inline const vector<Int_t>& get_mc_image_obs_id_v() const {return _mc_image_obs_id_v;};
  inline const vector<Int_t>& get_mc_image_event_id_v() const {return _mc_image_event_id_v;};
  //
  inline const vector<Int_t>& get_muon_obs_id_v() const {return _muon_obs_id_v;};
  inline const vector<Int_t>& get_muon_event_id_v() const {return _muon_event_id_v;};
  //
  inline const vector<Float_t>& get_muonring_center_fov_lon_v() const {return _muonring_center_fov_lon_v;};
  inline const vector<Float_t>& get_muonring_center_fov_lat_v() const {return _muonring_center_fov_lat_v;};
  inline const vector<Float_t>& get_muonring_radius_v() const {return _muonring_radius_v;};
  inline const vector<Float_t>& get_muonring_center_phi_v() const {return _muonring_center_phi_v;};
  inline const vector<Float_t>& get_muonring_center_distance_v() const {return _muonring_center_distance_v;};
  inline const vector<Float_t>& get_muonparameters_containment_v() const {return _muonparameters_containment_v;};
  inline const vector<Float_t>& get_muonparameters_completeness_v() const {return _muonparameters_completeness_v;};
  inline const vector<Float_t>& get_muonparameters_intensity_ratio_v() const {return _muonparameters_intensity_ratio_v;};
  inline const vector<Float_t>& get_muonparameters_mean_squared_error_v() const {return _muonparameters_mean_squared_error_v;};
  inline const vector<Float_t>& get_muonparameters_ring_intensity_v() const {return _muonparameters_ring_intensity_v;};
  inline const vector<Float_t>& get_muonparameters_intensity_outside_ring_v() const {return _muonparameters_intensity_outside_ring_v;};
  inline const vector<Float_t>& get_muonparameters_n_pixels_in_ring_v() const {return _muonparameters_n_pixels_in_ring_v;};
  inline const vector<Float_t>& get_muonparameters_mean_intensity_outside_ring_v() const {return _muonparameters_mean_intensity_outside_ring_v;};
  inline const vector<Float_t>& get_muonparameters_radial_std_dev_v() const {return _muonparameters_radial_std_dev_v;};
  inline const vector<Float_t>& get_muonparameters_skewness_v() const {return _muonparameters_skewness_v;};
  inline const vector<Float_t>& get_muonparameters_excess_kurtosism_v() const {return _muonparameters_excess_kurtosism_v;};
  inline const vector<Float_t>& get_muonefficiency_width_v() const {return _muonefficiency_width_v;};
  inline const vector<Float_t>& get_muonefficiency_impact_v() const {return _muonefficiency_impact_v;};
  inline const vector<Float_t>& get_muonefficiency_impact_x_v() const {return _muonefficiency_impact_x_v;};
  inline const vector<Float_t>& get_muonefficiency_impact_y_v() const {return _muonefficiency_impact_y_v;};
  inline const vector<Float_t>& get_muonefficiency_optical_efficiency_v() const {return _muonefficiency_optical_efficiency_v;};
  inline const vector<Float_t>& get_muonefficiency_likelihood_value_v() const {return _muonefficiency_likelihood_value_v;}; 
  //
  inline const vector<vector<Float_t>>& get_ch() const {return _ch_v;};
  inline const vector<vector<Float_t>>& get_cht() const {return _cht_v;};
  inline const vector<vector<Float_t>>& get_chm() const {return _chm_v;};
  inline const vector<vector<Float_t>>& get_ch_true() const {return _ch_true_v;};
  //
  bool check_obs_id_event_id();
  //
  
private:

  vector<Int_t> _mc_obs_id_v;
  vector<Int_t> _mc_event_id_v;
  //
  vector<Float_t> _mc_energy_v;
  vector<Float_t> _mc_core_x_v;
  vector<Float_t> _mc_core_y_v;
  vector<Float_t> _mc_alt_v;
  vector<Float_t> _mc_az_v;
  //
  vector<Int_t> _image_obs_id_v;
  vector<Int_t> _image_event_id_v;
  //
  vector<Int_t> _mc_image_obs_id_v;
  vector<Int_t> _mc_image_event_id_v;
  //
  vector<Int_t> _muon_obs_id_v;
  vector<Int_t> _muon_event_id_v;
  //
  vector<Float_t> _muonring_center_fov_lon_v;
  vector<Float_t> _muonring_center_fov_lat_v;
  vector<Float_t> _muonring_radius_v;
  vector<Float_t> _muonring_center_phi_v;
  vector<Float_t> _muonring_center_distance_v;
  vector<Float_t> _muonparameters_containment_v;
  vector<Float_t> _muonparameters_completeness_v;
  vector<Float_t> _muonparameters_intensity_ratio_v;
  vector<Float_t> _muonparameters_mean_squared_error_v;
  vector<Float_t> _muonparameters_ring_intensity_v;
  vector<Float_t> _muonparameters_intensity_outside_ring_v;
  vector<Float_t> _muonparameters_n_pixels_in_ring_v;
  vector<Float_t> _muonparameters_mean_intensity_outside_ring_v;
  vector<Float_t> _muonparameters_radial_std_dev_v;
  vector<Float_t> _muonparameters_skewness_v;
  vector<Float_t> _muonparameters_excess_kurtosism_v;
  vector<Float_t> _muonefficiency_width_v;
  vector<Float_t> _muonefficiency_impact_v;
  vector<Float_t> _muonefficiency_impact_x_v;
  vector<Float_t> _muonefficiency_impact_y_v;
  vector<Float_t> _muonefficiency_optical_efficiency_v;
  vector<Float_t> _muonefficiency_likelihood_value_v;
  //
  vector<vector<Float_t>> _ch_v;
  vector<vector<Float_t>> _cht_v;
  vector<vector<Float_t>> _chm_v;
  vector<vector<Float_t>> _ch_true_v;
  //
  void load_csv_data(TString csv_file_in);
  //
  Int_t _n_meta_data;
  Int_t _nch;  
};
