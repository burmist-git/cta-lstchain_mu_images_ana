//my
#include "dl1_muon_ctapipe_csv_reader.hh"

//root
#include "TROOT.h"
#include "TMath.h"
#include "TGraph.h"
#include <TVector2.h>
#include <TVector3.h>
#include <TPolyLine.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TText.h>
#include <TMath.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCrown.h>
#include <TArc.h>
#include <TROOT.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TPad.h>
#include <TString.h>
#include <TFile.h>
#include <TAxis.h>
#include <TVector2.h>
#include <TImage.h>
#include <TColor.h>

//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <math.h>
#include <vector>

using namespace std;

dl1_muon_ctapipe_csv_reader::dl1_muon_ctapipe_csv_reader(TString csv_file_in, Int_t n_meta_data, Int_t nch) : _n_meta_data(n_meta_data), _nch(nch)
{
  load_csv_data(csv_file_in);
  assert(check_obs_id_event_id());
}

dl1_muon_ctapipe_csv_reader::~dl1_muon_ctapipe_csv_reader(){;}

void dl1_muon_ctapipe_csv_reader::load_csv_data(TString csv_file_in){
  cout<<"csv_file_in  "<<csv_file_in<<endl
      <<"_n_meta_data "<<_n_meta_data<<endl
      <<"_nch         "<<_nch<<endl;
  ifstream fFile(csv_file_in);
  string mot;
  Int_t entry_counter;
  //
  Float_t mc_obs_id_tmp;
  Float_t mc_event_id_tmp;
  //
  Float_t mc_energy_tmp;
  Float_t mc_core_x_tmp;
  Float_t mc_core_y_tmp;
  Float_t mc_alt_tmp;
  Float_t mc_az_tmp;
  //
  Float_t image_obs_id_tmp;
  Float_t image_event_id_tmp;
  //
  Float_t mc_image_obs_id_tmp;
  Float_t mc_image_event_id_tmp;
  //
  Float_t muon_obs_id_tmp;
  Float_t muon_event_id_tmp;
  //
  Float_t muonring_center_fov_lon_tmp;
  Float_t muonring_center_fov_lat_tmp;
  Float_t muonring_radius_tmp;
  Float_t muonring_center_phi_tmp;
  Float_t muonring_center_distance_tmp;
  Float_t muonparameters_containment_tmp;
  Float_t muonparameters_completeness_tmp;
  Float_t muonparameters_intensity_ratio_tmp;
  Float_t muonparameters_mean_squared_error_tmp;
  Float_t muonparameters_ring_intensity_tmp;
  Float_t muonparameters_intensity_outside_ring_tmp;
  Float_t muonparameters_n_pixels_in_ring_tmp;
  Float_t muonparameters_mean_intensity_outside_ring_tmp;
  Float_t muonparameters_radial_std_dev_tmp;
  Float_t muonparameters_skewness_tmp;
  Float_t muonparameters_excess_kurtosism_tmp;
  Float_t muonefficiency_width_tmp;
  Float_t muonefficiency_impact_tmp;
  Float_t muonefficiency_impact_x_tmp;
  Float_t muonefficiency_impact_y_tmp;
  Float_t muonefficiency_optical_efficiency_tmp;
  Float_t muonefficiency_likelihood_value_tmp;  
  //
  Float_t ch_val_tmp;
  Float_t cht_val_tmp;
  Float_t chm_val_tmp;
  Float_t ch_true_val_tmp;
  //
  //
  if(fFile.is_open()){
    for(Int_t i = 0;i<_n_meta_data;i++)
      fFile>>mot;
    for(Int_t i = 0;i<_nch;i++)
      fFile>>mot;
    for(Int_t i = 0;i<_nch;i++)
      fFile>>mot;
    for(Int_t i = 0;i<_nch;i++)
      fFile>>mot;
    for(Int_t i = 0;i<_nch;i++)
      fFile>>mot;
    //cout<<mot<<endl;
    //
    while(fFile
	  >>entry_counter
	  >>mc_obs_id_tmp
	  >>mc_event_id_tmp
	  >>mc_energy_tmp
	  >>mc_core_x_tmp
	  >>mc_core_y_tmp
	  >>mc_alt_tmp
	  >>mc_az_tmp
	  >>image_obs_id_tmp
	  >>image_event_id_tmp
	  >>mc_image_obs_id_tmp
	  >>mc_image_event_id_tmp
	  >>muon_obs_id_tmp
	  >>muon_event_id_tmp
	  >>muonring_center_fov_lon_tmp
	  >>muonring_center_fov_lat_tmp
	  >>muonring_radius_tmp
	  >>muonring_center_phi_tmp
	  >>muonring_center_distance_tmp
	  >>muonparameters_containment_tmp
	  >>muonparameters_completeness_tmp
	  >>muonparameters_intensity_ratio_tmp
	  >>muonparameters_mean_squared_error_tmp
	  >>muonparameters_ring_intensity_tmp
	  >>muonparameters_intensity_outside_ring_tmp
	  >>muonparameters_n_pixels_in_ring_tmp
	  >>muonparameters_mean_intensity_outside_ring_tmp
	  >>muonparameters_radial_std_dev_tmp
	  >>muonparameters_skewness_tmp
	  >>muonparameters_excess_kurtosism_tmp
	  >>muonefficiency_width_tmp
	  >>muonefficiency_impact_tmp
	  >>muonefficiency_impact_x_tmp
	  >>muonefficiency_impact_y_tmp
	  >>muonefficiency_optical_efficiency_tmp
	  >>muonefficiency_likelihood_value_tmp){
      //
      //
      _mc_obs_id_v.push_back((Int_t)mc_obs_id_tmp);
      _mc_event_id_v.push_back((Int_t)mc_event_id_tmp);
      //
      _mc_energy_v.push_back(mc_energy_tmp);
      _mc_core_x_v.push_back(mc_core_x_tmp);
      _mc_core_y_v.push_back(mc_core_y_tmp);
      _mc_alt_v.push_back(mc_alt_tmp);
      _mc_az_v.push_back(mc_az_tmp);
      //
      _image_obs_id_v.push_back((Int_t)image_obs_id_tmp);
      _image_event_id_v.push_back((Int_t)image_event_id_tmp);
      //
      _mc_image_obs_id_v.push_back((Int_t)mc_image_obs_id_tmp);
      _mc_image_event_id_v.push_back((Int_t)mc_image_event_id_tmp);
      //
      _muon_obs_id_v.push_back((Int_t)muon_obs_id_tmp);
      _muon_event_id_v.push_back((Int_t)muon_event_id_tmp);
      //
      _muonring_center_fov_lon_v.push_back(muonring_center_fov_lon_tmp);
      _muonring_center_fov_lat_v.push_back(muonring_center_fov_lat_tmp);
      _muonring_radius_v.push_back(muonring_radius_tmp);
      _muonring_center_phi_v.push_back(muonring_center_phi_tmp);
      _muonring_center_distance_v.push_back(muonring_center_distance_tmp);
      _muonparameters_containment_v.push_back(muonparameters_containment_tmp);
      _muonparameters_completeness_v.push_back(muonparameters_completeness_tmp);
      _muonparameters_intensity_ratio_v.push_back(muonparameters_intensity_ratio_tmp);
      _muonparameters_mean_squared_error_v.push_back(muonparameters_mean_squared_error_tmp);
      _muonparameters_ring_intensity_v.push_back(muonparameters_ring_intensity_tmp);
      _muonparameters_intensity_outside_ring_v.push_back(muonparameters_intensity_outside_ring_tmp);
      _muonparameters_n_pixels_in_ring_v.push_back(muonparameters_n_pixels_in_ring_tmp);
      _muonparameters_mean_intensity_outside_ring_v.push_back(muonparameters_mean_intensity_outside_ring_tmp);
      _muonparameters_radial_std_dev_v.push_back(muonparameters_radial_std_dev_tmp);
      _muonparameters_skewness_v.push_back(muonparameters_skewness_tmp);
      _muonparameters_excess_kurtosism_v.push_back(muonparameters_excess_kurtosism_tmp);
      _muonefficiency_width_v.push_back(muonefficiency_width_tmp);
      _muonefficiency_impact_v.push_back(muonefficiency_impact_tmp);
      _muonefficiency_impact_x_v.push_back(muonefficiency_impact_x_tmp);
      _muonefficiency_impact_y_v.push_back(muonefficiency_impact_y_tmp);
      _muonefficiency_optical_efficiency_v.push_back(muonefficiency_optical_efficiency_tmp);
      _muonefficiency_likelihood_value_v.push_back(muonefficiency_likelihood_value_tmp);
      //
      if(entry_counter%1000 == 0){
	cout<<"entry_counter "<<entry_counter<<endl
	    <<"mc_obs_id_tmp   "<<mc_obs_id_tmp<<endl
	    <<"mc_event_id_tmp "<<mc_event_id_tmp<<endl
	    <<"mc_energy_tmp   "<<mc_energy_tmp<<endl
	    <<"mc_core_x_tmp   "<<mc_core_x_tmp<<endl
	    <<"mc_core_y_tmp   "<<mc_core_y_tmp<<endl
	    <<"mc_alt_tmp      "<<mc_alt_tmp<<endl
	    <<"mc_az_tmp       "<<mc_az_tmp<<endl
	    <<"muonring_center_fov_lon_tmp         "<<muonring_center_fov_lon_tmp<<endl
	    <<"muonring_center_fov_lat_tmp         "<<muonring_center_fov_lat_tmp<<endl
	    <<"muonefficiency_likelihood_value_tmp "<<muonefficiency_likelihood_value_tmp<<endl;
      }
      //
      //
      vector<Float_t> ch_v_tmp;
      vector<Float_t> cht_v_tmp;
      vector<Float_t> chm_v_tmp;
      vector<Float_t> ch_true_v_tmp;      
      //
      for(Int_t i = 0;i<_nch;i++){
	fFile>>ch_val_tmp;
	ch_v_tmp.push_back(ch_val_tmp);
      }
      for(Int_t i = 0;i<_nch;i++){
	fFile>>cht_val_tmp;
	cht_v_tmp.push_back(cht_val_tmp);
      }
      for(Int_t i = 0;i<_nch;i++){
	fFile>>chm_val_tmp;
	chm_v_tmp.push_back(chm_val_tmp);
      }
      for(Int_t i = 0;i<_nch;i++){
	fFile>>ch_true_val_tmp;
	ch_true_v_tmp.push_back(ch_true_val_tmp);
      }
      _ch_v.push_back(ch_v_tmp);
      _cht_v.push_back(cht_v_tmp);
      _chm_v.push_back(chm_v_tmp);
      _ch_true_v.push_back(ch_true_v_tmp);
    }  
    //
    fFile.close();
  }
}

bool dl1_muon_ctapipe_csv_reader::check_obs_id_event_id(){
  //
  if(_mc_obs_id_v.size() != _image_obs_id_v.size())
    return false;
  if(_mc_obs_id_v.size() != _mc_image_obs_id_v.size())
    return false;
  if(_mc_obs_id_v.size() != _muon_obs_id_v.size())
    return false;
  //
  if( _mc_event_id_v.size() != _image_event_id_v.size())
    return false;
  if( _mc_event_id_v.size() != _mc_image_event_id_v.size())
    return false;
  if( _mc_event_id_v.size() != _muon_event_id_v.size())
    return false;
  //
  unsigned int i = 0;
  //
  for(i = 0;i<_mc_obs_id_v.size();i++)
    if(_mc_obs_id_v.at(i) != _image_obs_id_v.at(i))
      return false;
  for(i = 0;i<_mc_obs_id_v.size();i++)
    if(_mc_obs_id_v.at(i) != _mc_image_obs_id_v.at(i))
      return false;
  for(i = 0;i<_mc_obs_id_v.size();i++)
    if(_mc_obs_id_v.at(i) != _muon_obs_id_v.at(i))
      return false;
  //
  for(i = 0;i<_mc_event_id_v.size();i++)
    if(_mc_event_id_v.at(i) != _image_event_id_v.at(i))
      return false;
  for(i = 0;i<_mc_event_id_v.size();i++)
    if(_mc_event_id_v.at(i) != _mc_image_event_id_v.at(i))
      return false;
  for(i = 0;i<_mc_event_id_v.size();i++)
    if(_mc_event_id_v.at(i) != _muon_event_id_v.at(i))
      return false;
  //
  //
  return true;
}
