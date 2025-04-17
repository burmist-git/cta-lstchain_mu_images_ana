#pragma once

//root
#include "TROOT.h"

//C, C++
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

class dl1_muon_csv_reader;
class dl1_muon_ctapipe_csv_reader;
class pmtCameraHist;
class TGraph;

class TCanvas;

using namespace std;

class plt {
public:    

  plt(dl1_muon_csv_reader* reader, TString pmt_map);
  plt(dl1_muon_ctapipe_csv_reader* reader, TString pmt_map);
  ~plt();
  //
  void plot_and_save(TString hist_root_out);
  void plot_and_save_ctapipe(TString hist_root_out);
  TCanvas* plot_muon_all(unsigned int evID = 0, TString pdf_out_file = "");

  static void gen_ring(TGraph *gr, Int_t np, Double_t x0, Double_t y0, Double_t R);
  static Double_t get_m_from_deg(Double_t deg, Double_t effective_focal_length_m);
  static Double_t get_canonical_phi_deg_from_phi_deg(Double_t phi_deg);
  
  void fill_histos(TString hist_root_out);
  
private:

  dl1_muon_csv_reader* _reader;
  dl1_muon_ctapipe_csv_reader* _reader_ctapipe;
  TString _pmt_map;

  //
  pmtCameraHist *_pmt_cam;
  pmtCameraHist *_pmt_cam_charge;
  pmtCameraHist *_pmt_cam_time;
  pmtCameraHist *_pmt_cam_mask;
  pmtCameraHist *_pmt_cam_charge_true;
  
};
