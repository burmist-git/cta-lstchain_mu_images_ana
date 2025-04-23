//my
#include "plt.hh"
#include "pmtCameraHist.hh"
#include "dl1_muon_csv_reader.hh"
#include "dl1_muon_ctapipe_csv_reader.hh"
#include "fov_lon_fov_lat_img_mask_reader.hh"

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
#include <TH1D.h>
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

plt::plt(dl1_muon_csv_reader* reader, TString pmt_map) : _reader(reader), _pmt_map(pmt_map)
{
  _pmt_cam = NULL;
  _pmt_cam_charge = NULL; 
  _pmt_cam_time = NULL;
  _pmt_cam_mask = NULL;
  _pmt_cam_charge_true = NULL; 
}

plt::plt(dl1_muon_ctapipe_csv_reader* reader, TString pmt_map) : _reader_ctapipe(reader), _pmt_map(pmt_map)
{
  //
  _pmt_cam = new pmtCameraHist("pmt_cam","pmt_cam",_pmt_map,0.0);
  _pmt_cam_charge = new pmtCameraHist("pmt_cam_charge","pmt_cam_charge",_pmt_cam);
  _pmt_cam_time = new pmtCameraHist("pmt_cam_time","pmt_cam_time",_pmt_cam);
  _pmt_cam_mask = new pmtCameraHist("pmt_cam_mask","pmt_cam_mask",_pmt_cam);
  _pmt_cam_charge_true = new pmtCameraHist("pmt_cam_charge_true","pmt_cam_charge_true",_pmt_cam);
}

plt::plt(fov_lon_fov_lat_img_mask_reader* reader, TString pmt_map) : _reader_fov_lon_fov_lat(reader), _pmt_map(pmt_map)
{
  _pmt_cam = new pmtCameraHist("pmt_cam","pmt_cam",_pmt_map,0.0,true);
  _pmt_cam_charge = new pmtCameraHist("pmt_cam_charge","pmt_cam_charge",_pmt_cam);
  _pmt_cam_time = NULL;
  _pmt_cam_mask = new pmtCameraHist("pmt_cam_mask","pmt_cam_mask",_pmt_cam);
  _pmt_cam_charge_true = NULL;
}

plt::~plt(){;}

void plt::plot_and_save(TString hist_root_out){
  pmtCameraHist *pmt_cam = new pmtCameraHist("pmt_cam","pmt_cam",_pmt_map,0.0);
  //pmt_cam->dump_mapping_info();
  //pmt_cam->test();
 //----------------------
  TFile* rootFile = new TFile(hist_root_out.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<hist_root_out.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<hist_root_out.Data()<<endl;
  //
  TString hist_name = "pmt_cam";
  TString hist_title = "pmt_cam";
  TString pdf_out;
  for(unsigned int i = 0;i<100;i++){
    cout<<"_reader->get_event_id().at(i)  "<<_reader->get_event_id().at(i)<<endl;
    cout<<"_reader->get_mc_energy().at(i) "<<_reader->get_mc_energy().at(i)<<endl;
    hist_name = "pmt_cam_ev";
    hist_title = "pmt_cam_ev";
    hist_name += i;
    hist_title += i;
    //pdf_out = "./mask/pmt_cam_";
    //pdf_out = "./time/pmt_cam_";
    pdf_out = "./charge/pmt_cam_";
    pdf_out += _reader->get_event_id().at(i);
    pdf_out += "_ev";
    pdf_out += ".pdf";
    pmt_cam->Clean();
    pmt_cam->SetName(hist_name);
    pmt_cam->SetTitle(hist_title);
    //pmt_cam->SetMinimum(0.0);
    //pmt_cam->SetMaximum(2.0);
    //pmt_cam->SetMinimum(10.0);
    //pmt_cam->SetMaximum(25.0);
    pmt_cam->SetMinimum(0.0);
    pmt_cam->SetMaximum(10.0);
    pmt_cam->Fill_hist(_reader->get_ch().at(i));
    pmt_cam->Draw_cam("ZCOLOR",pdf_out)->Write();
  }
  //
  //
  //
  rootFile->Close();
}

void plt::plot_and_save_ctapipe(TString hist_root_out){
  pmtCameraHist *pmt_cam = new pmtCameraHist("pmt_cam","pmt_cam",_pmt_map,0.0);
  //pmt_cam->dump_mapping_info();
  //pmt_cam->test();
 //----------------------
  TFile* rootFile = new TFile(hist_root_out.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<hist_root_out.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<hist_root_out.Data()<<endl;
  //
  TString hist_name = "pmt_cam";
  TString hist_title = "pmt_cam";
  TString pdf_out;
  for(unsigned int i = 0;i<100;i++){
    cout<<"_reader_ctapipe->get_event_id().at(i)  "<<_reader_ctapipe->get_mc_event_id_v().at(i)<<endl;
    cout<<"_reader_ctapipe->get_mc_energy().at(i) "<<_reader_ctapipe->get_mc_energy_v().at(i)<<endl;
    hist_name = "pmt_cam_ev";
    hist_title = "pmt_cam_ev";
    hist_name += i;
    hist_title += i;
    //pdf_out = "./mask/pmt_cam_";
    //pdf_out = "./time/pmt_cam_";
    //pdf_out = "./charge/pmt_cam_";
    pdf_out = "./charge_true/pmt_cam_";
    pdf_out += _reader_ctapipe->get_mc_event_id_v().at(i);
    pdf_out += "_ev";
    pdf_out += ".pdf";
    pmt_cam->Clean();
    pmt_cam->SetName(hist_name);
    pmt_cam->SetTitle(hist_title);
    //pmt_cam->SetMinimum(0.0);
    //pmt_cam->SetMaximum(2.0);
    //pmt_cam->SetMinimum(10.0);
    //pmt_cam->SetMaximum(25.0);
    pmt_cam->SetMinimum(0.0);
    pmt_cam->SetMaximum(10.0);
    //pmt_cam->Fill_hist(_reader_ctapipe->get_ch().at(i));
    //pmt_cam->Fill_hist(_reader_ctapipe->get_cht().at(i));
    //pmt_cam->Fill_hist(_reader_ctapipe->get_chm().at(i));
    pmt_cam->Fill_hist(_reader_ctapipe->get_ch_true().at(i));
    pmt_cam->Draw_cam("ZCOLOR",pdf_out)->Write();
  }
  //
  //
  //
  rootFile->Close();
}

TCanvas* plt::plot_muon_lon_lat(unsigned int evID, TString pdf_out_file){
  //
  _pmt_cam_charge->Clean();
  _pmt_cam_mask->Clean();
  //
  _pmt_cam_charge->Fill_hist(_reader_fov_lon_fov_lat->get_img_v());
  _pmt_cam_mask->Fill_hist(_reader_fov_lon_fov_lat->get_mask_v());
  //
  TGraph *gr_ring_reco = new TGraph();
  TGraph *gr_ring_r0 = new TGraph();
  TGraph *gr_lon_lat_greed = new TGraph();
  TGraph *gr_lon_lat_greed_mask = new TGraph();
  gr_lon_lat_greed->SetPoint(0,0,0);
  gr_lon_lat_greed_mask->SetPoint(0,0,0);
  //
  //  
  //
  Int_t mask_counter = 0;
  for(unsigned int jj = 0; jj<_reader_fov_lon_fov_lat->get_fov_lon_v().size(); jj++){
    gr_lon_lat_greed->SetPoint((Int_t)jj,
    			       _reader_fov_lon_fov_lat->get_fov_lon_v().at(jj),
    			       _reader_fov_lon_fov_lat->get_fov_lat_v().at(jj));
    if(_reader_fov_lon_fov_lat->get_mask_v().at(jj)>0.0){
      gr_lon_lat_greed_mask->SetPoint(mask_counter,
    				      _reader_fov_lon_fov_lat->get_fov_lon_v().at(jj),
    				      _reader_fov_lon_fov_lat->get_fov_lat_v().at(jj));
      mask_counter++;
    }
  }
  //
  //
  //
  //  
  gen_ring(gr_ring_reco, 100,
	   _reader_fov_lon_fov_lat->get_center_fov_lon_fit(),
	   _reader_fov_lon_fov_lat->get_center_fov_lat_fit(),
	   _reader_fov_lon_fov_lat->get_radius_fit());
  gr_ring_reco->SetLineColor(kGreen+2);
  gr_ring_reco->SetLineWidth(2);
  gr_ring_r0->SetPoint( 0, _reader_fov_lon_fov_lat->get_center_fov_lon_fit(), _reader_fov_lon_fov_lat->get_center_fov_lat_fit());
  gr_ring_r0->SetMarkerColor(kGreen+2);
  gr_ring_r0->SetMarkerStyle(43);
  gr_ring_r0->SetMarkerSize(2.0);
  //
  //
  //
  Double_t lx_camera = 5.0;
  Double_t ly_camera = 5.0;
  Double_t d_frame = 0.1;
  //gStyle->SetPalette(kRainBow);
  //gStyle->SetPalette(kCool);
  //gStyle->SetPalette(kIsland);
  //gStyle->SetPalette(kCherry);
  //TColor::InvertPalette();
  gStyle->SetPalette(kInvertedDarkBodyRadiator);
  gStyle->SetOptStat(kFALSE);
  TH2F *frame_Charge = new TH2F( "h2_Charge", "h2_Charge", 40, -lx_camera/2.0-d_frame,lx_camera/2.0+d_frame,40, -ly_camera/2.0-d_frame,ly_camera/2.0+d_frame);
  frame_Charge->SetTitle("Charge");
  frame_Charge->GetXaxis()->SetTitle("x, m");
  frame_Charge->GetYaxis()->SetTitle("y, m");
  frame_Charge->GetXaxis()->CenterTitle();
  frame_Charge->GetYaxis()->CenterTitle();
  frame_Charge->GetYaxis()->SetTitleOffset(1.5);
  frame_Charge->SetStats(kFALSE);
  TH2F *frame_Mask = new TH2F( "h2_Mask", "h2_Mask", 40, -lx_camera/2.0-d_frame,lx_camera/2.0+d_frame,40, -ly_camera/2.0-d_frame,ly_camera/2.0+d_frame);
  frame_Mask->SetTitle("Mask");
  frame_Mask->GetXaxis()->SetTitle("x, m");
  frame_Mask->GetYaxis()->SetTitle("y, m");
  frame_Mask->GetXaxis()->CenterTitle();
  frame_Mask->GetYaxis()->CenterTitle();
  frame_Mask->GetYaxis()->SetTitleOffset(1.5);
  //
  //
  _pmt_cam_charge->SetMinimum(0.0);
  _pmt_cam_charge->SetMaximum(10.0);
  _pmt_cam_mask->SetMinimum(0.0);
  _pmt_cam_mask->SetMaximum(2.0);
  //
  //
  TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
  c1->Divide(2,2);
  //
  c1->cd(1);
  gPad->SetRightMargin(0.12);
  gPad->SetLeftMargin(0.12);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.15);
  frame_Charge->Draw();
  _pmt_cam_charge->Draw("ZCOLOR same");
  gr_ring_reco->Draw("same");
  gr_ring_r0->Draw("sameP");
  //
  c1->cd(2);
  gPad->SetRightMargin(0.12);
  gPad->SetLeftMargin(0.12);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.15);
  frame_Mask->Draw();
  _pmt_cam_mask->Draw("ZCOLOR same");
  gr_ring_reco->Draw("same");
  gr_ring_r0->Draw("sameP");
  //
  c1->cd(3);
  gr_lon_lat_greed->Draw("AP");
  gr_ring_reco->Draw("same");
  gr_ring_r0->Draw("sameP");
  c1->cd(4);
  gr_lon_lat_greed_mask->Draw("AP");
  gr_ring_reco->Draw("same");
  gr_ring_r0->Draw("sameP");
  
  if(pdf_out_file != "")
    c1->SaveAs(pdf_out_file.Data());

  delete _pmt_cam_charge;
  delete _pmt_cam_mask;
  delete frame_Charge;
  delete frame_Mask;
  delete gr_ring_reco;
  delete gr_ring_r0;
  delete gr_lon_lat_greed;
  delete gr_lon_lat_greed_mask;
  delete c1;
}

TCanvas* plt::plot_muon_all(unsigned int evID, TString pdf_out_file){
  //
  _pmt_cam_charge->Clean();
  _pmt_cam_time->Clean();
  _pmt_cam_mask->Clean();
  _pmt_cam_charge_true->Clean();
  //
  _pmt_cam_charge->Fill_hist(_reader_ctapipe->get_ch().at(evID));
  _pmt_cam_time->Fill_hist(_reader_ctapipe->get_cht().at(evID));
  _pmt_cam_mask->Fill_hist(_reader_ctapipe->get_chm().at(evID));
  _pmt_cam_charge_true->Fill_hist(_reader_ctapipe->get_ch_true().at(evID));  
  //
  //
  //
  //
  //
  //inline const vector<Float_t>& get_muonring_center_fov_lon_v() const {return _muonring_center_fov_lon_v;};
  //inline const vector<Float_t>& get_muonring_center_fov_lat_v() const {return _muonring_center_fov_lat_v;};
  //inline const vector<Float_t>& get_muonring_radius_v() const {return _muonring_radius_v;};
  //inline const vector<Float_t>& get_muonring_center_phi_v() const {return _muonring_center_phi_v;};
  //inline const vector<Float_t>& get_muonring_center_distance_v() const {return _muonring_center_distance_v;};
  //
  //
  //
  //
  //
  Double_t effective_focal_length_m = 29.30565071105957;
  TVector2 v2;
  TVector2 v2_fov_lon_lat;
  TVector3 v3_tmp;
  TGraph *gr_ring_reco = new TGraph();
  TGraph *gr_ring_r0 = new TGraph();
  //Double_t muonring_radius = get_m_from_deg((Double_t)_reader_ctapipe->get_muonring_radius_v().at(evID),effective_focal_length_m);
  //Double_t muonring_center_phi = _reader_ctapipe->get_muonring_center_phi_v().at(evID);
  //Double_t muonring_center_distance = get_m_from_deg((Double_t)_reader_ctapipe->get_muonring_center_distance_v().at(evID),effective_focal_length_m);
  Double_t muonring_radius = get_m_from_deg((Double_t)_reader_ctapipe->get_muonring_radius_v().at(evID),effective_focal_length_m);
  v2_fov_lon_lat.SetX(get_m_from_deg((Double_t)_reader_ctapipe->get_muonring_center_fov_lon_v().at(evID),effective_focal_length_m));
  v2_fov_lon_lat.SetY(get_m_from_deg((Double_t)_reader_ctapipe->get_muonring_center_fov_lat_v().at(evID),effective_focal_length_m));
  //Double_t muonring_center_phi = _reader_ctapipe->get_muonring_center_phi_v().at(evID);
  //Double_t muonring_center_distance = get_m_from_deg((Double_t)_reader_ctapipe->get_muonring_center_distance_v().at(evID),effective_focal_length_m);
  Double_t muonring_center_phi = v2_fov_lon_lat.Phi();
  Double_t muonring_center_distance = v2_fov_lon_lat.Mod();
  //
  //
  Int_t image_obs_id = _reader_ctapipe->get_image_obs_id_v().at(evID);
  Int_t image_event_id = _reader_ctapipe->get_image_event_id_v().at(evID);
  Int_t muonring_radius_int = (Int_t)(muonring_radius*100.0);
  Int_t muonring_center_phi_int = (Int_t)muonring_center_phi;
  Int_t muonring_center_distance_int = (Int_t)(muonring_center_distance*100.0);
  Int_t muonparameters_completeness_int = (Int_t)(_reader_ctapipe->get_muonparameters_completeness_v().at(evID)*100.0);
  Int_t muonefficiency_impact_x_int = (Int_t)(_reader_ctapipe->get_muonefficiency_impact_x_v().at(evID)*100.0);
  Int_t muonefficiency_impact_y_int = (Int_t)(_reader_ctapipe->get_muonefficiency_impact_y_v().at(evID)*100.0);
  //
  //  
  //if(muonring_radius>0.0){
  v2.SetMagPhi(muonring_center_distance,get_canonical_phi_deg_from_phi_deg(muonring_center_phi));
  v3_tmp.SetXYZ(v2.X(), v2.Y(),0.0);
  v3_tmp.RotateY(TMath::Pi());
  v3_tmp.RotateZ(-TMath::Pi()/2.0);
  gen_ring(gr_ring_reco, 100, v3_tmp.X(), v3_tmp.Y(), muonring_radius);
  //gen_ring(gr_ring_reco, 100, -v2.Y(), -v2.X(), muonring_radius);
  gr_ring_reco->SetLineColor(kGreen+2);
  gr_ring_reco->SetLineWidth(2);
  gr_ring_r0->SetPoint( 0, v3_tmp.X(), v3_tmp.Y());
  //gr_ring_r0->SetPoint( 0, -v2.Y(), -v2.X());
  gr_ring_r0->SetMarkerColor(kGreen+2);
  gr_ring_r0->SetMarkerStyle(43);
  gr_ring_r0->SetMarkerSize(2.0);
  //}
  //
  //
  //
  _pmt_cam_charge->SetMinimum(0.0);
  _pmt_cam_charge->SetMaximum(10.0);
  _pmt_cam_time->SetMinimum(0.0);
  _pmt_cam_time->SetMaximum(40.0);
  _pmt_cam_mask->SetMinimum(0.0);
  _pmt_cam_mask->SetMaximum(2.0);
  _pmt_cam_charge_true->SetMinimum(0.0);
  _pmt_cam_charge_true->SetMaximum(10.0);
  //
  //
  //
  //
  Double_t lx_camera = 2.5;
  Double_t ly_camera = 2.5;
  Double_t d_frame = 0.1;
  //gStyle->SetPalette(kRainBow);
  //gStyle->SetPalette(kCool);
  //gStyle->SetPalette(kIsland);
  //gStyle->SetPalette(kCherry);
  //TColor::InvertPalette();
  gStyle->SetPalette(kInvertedDarkBodyRadiator);
  gStyle->SetOptStat(kFALSE);
  TH2F *frame_Charge = new TH2F( "h2_Charge", "h2_Charge", 40, -lx_camera/2.0-d_frame,lx_camera/2.0+d_frame,40, -ly_camera/2.0-d_frame,ly_camera/2.0+d_frame);
  frame_Charge->SetTitle("Charge");
  frame_Charge->GetXaxis()->SetTitle("x, m");
  frame_Charge->GetYaxis()->SetTitle("y, m");
  frame_Charge->GetXaxis()->CenterTitle();
  frame_Charge->GetYaxis()->CenterTitle();
  frame_Charge->GetYaxis()->SetTitleOffset(1.5);
  frame_Charge->SetStats(kFALSE);
  TH2F *frame_Time = new TH2F( "h2_Time", "h2_Time", 40, -lx_camera/2.0-d_frame,lx_camera/2.0+d_frame,40, -ly_camera/2.0-d_frame,ly_camera/2.0+d_frame);
  frame_Time->SetTitle("Time");
  frame_Time->GetXaxis()->SetTitle("x, m");
  frame_Time->GetYaxis()->SetTitle("y, m");
  frame_Time->GetXaxis()->CenterTitle();
  frame_Time->GetYaxis()->CenterTitle();
  frame_Time->GetYaxis()->SetTitleOffset(1.5);
  frame_Time->SetStats(kFALSE);
  TH2F *frame_Mask = new TH2F( "h2_Mask", "h2_Mask", 40, -lx_camera/2.0-d_frame,lx_camera/2.0+d_frame,40, -ly_camera/2.0-d_frame,ly_camera/2.0+d_frame);
  frame_Mask->SetTitle("Mask");
  frame_Mask->GetXaxis()->SetTitle("x, m");
  frame_Mask->GetYaxis()->SetTitle("y, m");
  frame_Mask->GetXaxis()->CenterTitle();
  frame_Mask->GetYaxis()->CenterTitle();
  frame_Mask->GetYaxis()->SetTitleOffset(1.5);
  frame_Mask->SetStats(kFALSE);
  TH2F *frame_Charge_true = new TH2F( "h2_Charge_true", "h2_Charge_true", 40, -lx_camera/2.0-d_frame,lx_camera/2.0+d_frame,40, -ly_camera/2.0-d_frame,ly_camera/2.0+d_frame);
  frame_Charge_true->SetTitle("Charge_true");
  frame_Charge_true->GetXaxis()->SetTitle("x, m");
  frame_Charge_true->GetYaxis()->SetTitle("y, m");
  frame_Charge_true->GetXaxis()->CenterTitle();
  frame_Charge_true->GetYaxis()->CenterTitle();
  frame_Charge_true->GetYaxis()->SetTitleOffset(1.5);
  frame_Charge_true->SetStats(kFALSE);
  //
  //SetTitle("");
  //SetName("");
  //
  TCanvas *c1 = new TCanvas("c1","c1",1500,1000);
  c1->Divide(3,2);
  //
  c1->cd(1);
  gPad->SetRightMargin(0.12);
  gPad->SetLeftMargin(0.12);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.15);
  frame_Charge->Draw();
  _pmt_cam_charge->Draw("ZCOLOR same");
  gr_ring_reco->Draw("same");
  gr_ring_r0->Draw("sameP");
  //
  c1->cd(2);
  gPad->SetRightMargin(0.12);
  gPad->SetLeftMargin(0.12);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.15);
  frame_Time->Draw();
  _pmt_cam_time->Draw("ZCOLOR same");
  gr_ring_reco->Draw("same");
  gr_ring_r0->Draw("sameP");
  //
  c1->cd(4);
  gPad->SetRightMargin(0.12);
  gPad->SetLeftMargin(0.12);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.15);
  frame_Mask->Draw();
  _pmt_cam_mask->Draw("ZCOLOR same");
  gr_ring_reco->Draw("same");
  gr_ring_r0->Draw("sameP");
  //
  c1->cd(5);
  gPad->SetRightMargin(0.12);
  gPad->SetLeftMargin(0.12);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.15);
  frame_Charge_true->Draw();
  _pmt_cam_charge_true->Draw("ZCOLOR same");
  gr_ring_reco->Draw("same");
  gr_ring_r0->Draw("sameP");
  //
  //gPad->SetGridx();
  //gPad->SetGridy();
  //gPad->SetLogz();
  //
  //settings += " same TEXT";
  //settings += " same";
  //
  //
  //
  TString image_obs_id_str = "image obs id : "; image_obs_id_str += image_obs_id;
  TString image_event_id_str = "image event id : "; image_event_id_str += image_event_id;
  TString muonring_radius_int_str = "ring radius : "; muonring_radius_int_str += muonring_radius_int; muonring_radius_int_str += " cm";
  TString muonring_center_phi_int_str = "ring center phi : "; muonring_center_phi_int_str += muonring_center_phi_int; muonring_center_phi_int_str += " deg";
  TString muonring_center_distance_int_str = "ring center dist : "; muonring_center_distance_int_str += muonring_center_distance_int; muonring_center_distance_int_str += " cm";
  TString muonparameters_completeness_int_str = "completeness : "; muonparameters_completeness_int_str += muonparameters_completeness_int; muonparameters_completeness_int_str += " %";
  TString muonefficiency_impact_x_int_str = "impact x : "; muonefficiency_impact_x_int_str += muonefficiency_impact_x_int; muonefficiency_impact_x_int_str += " cm";
  TString muonefficiency_impact_y_int_str = "impact y : "; muonefficiency_impact_y_int_str += muonefficiency_impact_y_int; muonefficiency_impact_y_int_str += " cm";
  //
  //
  //
  c1->cd(3);
  TText *t00 = new TText(0.4,0.95,image_obs_id_str.Data());
  t00->SetTextAlign(22);
  t00->SetTextFont(43);
  t00->SetTextSize(25);
  t00->Draw();
  TText *t01 = new TText(0.4,0.90,image_event_id_str.Data());
  t01->SetTextAlign(22);
  t01->SetTextFont(43);
  t01->SetTextSize(25);
  t01->Draw();
  TText *t02 = new TText(0.4,0.85,muonring_radius_int_str.Data());
  t02->SetTextAlign(22);
  t02->SetTextFont(43);
  t02->SetTextSize(25);
  t02->Draw();
  TText *t03 = new TText(0.4,0.80,muonring_center_phi_int_str.Data());
  t03->SetTextAlign(22);
  t03->SetTextFont(43);
  t03->SetTextSize(25);
  t03->Draw();
  TText *t04 = new TText(0.4,0.75,muonring_center_distance_int_str.Data());
  t04->SetTextAlign(22);
  t04->SetTextFont(43);
  t04->SetTextSize(25);
  t04->Draw();
  TText *t05 = new TText(0.4,0.70,muonparameters_completeness_int_str.Data());
  t05->SetTextAlign(22);
  t05->SetTextFont(43);
  t05->SetTextSize(25);
  t05->Draw();
  TText *t06 = new TText(0.4,0.65,muonefficiency_impact_x_int_str.Data());
  t06->SetTextAlign(22);
  t06->SetTextFont(43);
  t06->SetTextSize(25);
  t06->Draw();
  TText *t07 = new TText(0.4,0.60,muonefficiency_impact_y_int_str.Data());
  t07->SetTextAlign(22);
  t07->SetTextFont(43);
  t07->SetTextSize(25);
  t07->Draw();
  //
  //
  //
  if(pdf_out_file != "")
    c1->SaveAs(pdf_out_file.Data());
  return c1;
}

void plt::gen_ring(TGraph *gr, Int_t np, Double_t x0, Double_t y0, Double_t R){
  Double_t phi = 0.0;
  TVector2 rc(x0,y0);
  for(Int_t i = 0;i<np;i++){
    TVector2 p;
    p.SetMagPhi(R,2*TMath::Pi()/(np-1)*i);
    TVector2 pt = rc + p;
    gr->SetPoint( i, pt.X(), pt.Y());
  }
}

Double_t plt::get_m_from_deg(Double_t deg, Double_t effective_focal_length_m){
  return TMath::Tan(deg/180.0*TMath::Pi())*effective_focal_length_m;
}

void plt::fill_histos(TString hist_root_out){
  //
  TH1D *h1_muonring_radius_deg = new TH1D("h1_muonring_radius_deg","h1_muonring_radius_deg",100,0.0,2.0);
  TH1D *h1_muonring_center_phi_deg = new TH1D("h1_muonring_center_phi_deg","h1_muonring_center_phi_deg",200, -400, 400);
  TH1D *h1_muonring_center_phi_canonical_deg = new TH1D("h1_muonring_center_phi_canonical_deg","h1_muonring_center_phi_canonical_deg",200, -400, 400);
  TH1D *h1_muonring_center_distance_deg = new TH1D("h1_muonring_center_distance_deg","h1_muonring_center_distance_deg",100,0.0,2.0);
  //
  //
  //Int_t muonring_radius_int = (Int_t)(muonring_radius*100.0);
  //Int_t muonring_center_phi_int = (Int_t)muonring_center_phi;
  //Int_t muonring_center_distance_int = (Int_t)(muonring_center_distance*100.0);
  //Int_t muonparameters_completeness_int = (Int_t)(_reader_ctapipe->get_muonparameters_completeness_v().at(evID)*100.0);
  //Int_t muonefficiency_impact_x_int = (Int_t)(_reader_ctapipe->get_muonefficiency_impact_x_v().at(evID)*100.0);
  //Int_t muonefficiency_impact_y_int = (Int_t)(_reader_ctapipe->get_muonefficiency_impact_y_v().at(evID)*100.0);
  //
  //
  for(unsigned int i = 0; i<_reader_ctapipe->get_muonring_radius_v().size(); i++){
    h1_muonring_radius_deg->Fill(_reader_ctapipe->get_muonring_radius_v().at(i));
    h1_muonring_center_phi_deg->Fill(_reader_ctapipe->get_muonring_center_phi_v().at(i));
    h1_muonring_center_phi_canonical_deg->Fill(get_canonical_phi_deg_from_phi_deg(_reader_ctapipe->get_muonring_center_phi_v().at(i)));
    h1_muonring_center_distance_deg->Fill(_reader_ctapipe->get_muonring_center_distance_v().at(i));
  }
  //----------------------
  //
  TFile* rootFile = new TFile(hist_root_out.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<hist_root_out.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<hist_root_out.Data()<<endl;
  //
  h1_muonring_radius_deg->Write();
  h1_muonring_center_phi_deg->Write();
  h1_muonring_center_phi_canonical_deg->Write();
  h1_muonring_center_distance_deg->Write();
  //
  rootFile->Close();
}

//  phi in [-180.0, 180.0] phi out [0,360.0]
Double_t plt::get_canonical_phi_deg_from_phi_deg(Double_t phi_deg){
  if(phi_deg > 180.0 || phi_deg < -180.0){
    cout<<" ERROR --> phi_deg > 180.0 || phi_deg < -180.0 "<<endl
        <<"                              phi_deg = "<<phi_deg<<endl;
  }
  if( phi_deg >= 0.0 && phi_deg <= 180.0){
    return phi_deg;
  }  
  return 360.0 + phi_deg;
}
