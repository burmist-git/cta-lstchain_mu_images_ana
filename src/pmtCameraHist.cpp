//my
#include "pmtCameraHist.hh"

//c, c++
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

//root
#include <TVector2.h>
#include <TVector3.h>
#include <TPolyLine.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TGraph.h>
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

using namespace std;

pmtCameraHist::pmtCameraHist(const char* name, const char* title, pmtCameraHist *pmtHist) : TH2Poly()
{
  //
  SetName(name);
  SetTitle(title);
  //
  _name = name;
  _title = title;
  //
  for(unsigned int i = 0;i<pmtHist->get_pixel_vec().size();i++)
    AddBin(pmtHist->get_pixel_vec().at(0).n,
	   pmtHist->get_pixel_vec().at(i).xp,
	   pmtHist->get_pixel_vec().at(i).yp);
}

pmtCameraHist::pmtCameraHist(const char* name, const char* title, const char* mapping_csv_file, Double_t rot_alpha_deg) : TH2Poly(), _rot_alpha_deg(rot_alpha_deg)
{
  //
  load_mapping( mapping_csv_file);
  //
  SetName(name);
  SetTitle(title);
  //
   _name = name;
   _title = title;
  //
  for(unsigned int i = 0;i<_pixel_vec.size();i++)
    AddBin(_pixel_vec.at(0).n,_pixel_vec.at(i).xp,_pixel_vec.at(i).yp);
}

pmtCameraHist::~pmtCameraHist(){
}

void pmtCameraHist::load_mapping(const char* mapping_csv_file){
  //
  ifstream fFile(mapping_csv_file);
  //cout<<mapping_csv_file<<std::endl;
  //
  Float_t pix_x, pix_y, pix_area;
  Int_t pixel_id = 0;
  Int_t entry_id = 0;
  string mot;
  //
  if(fFile.is_open()){
    fFile>>mot>>mot>>mot>>mot;
    while(fFile>>entry_id>>pixel_id>>pix_x>>pix_y>>pix_area){
      pixel_info pix_i;      
      //
      pix_x = pix_x;
      pix_y = pix_y;      
      //
      pix_i.entry_id = entry_id;
      pix_i.pixel_id = pixel_id;
      pix_i.pix_x = pix_x;
      pix_i.pix_y = pix_y;
      pix_i.pix_area = pix_area;
      pix_i.rotatePix(_rot_alpha_deg);
      pix_i.pixel_rot_alpha_deg = 0.0;
      //
      TVector2 vv(pix_i.pix_x,pix_i.pix_y);
      pix_i.pix_phi = vv.Phi();
      pix_i.pix_r = vv.Mod();
      //
      pixel_id++;
      _pixel_vec.push_back(pix_i);
    }
    fFile.close();
  }
  //
  _pixel_size = pixel_info::get_pixel_size_from_pix_area(pix_area);
  _pixel_pitch = pixel_info::get_pixel_pitch(_pixel_vec);
  Float_t pixel_rot_alpha_deg = pixel_info::get_pixel_pixel_rotation_angle_deg(_pixel_vec);
  for(unsigned int j = 0;j<_pixel_vec.size();j++){
    _pixel_vec.at(j).pixel_rot_alpha_deg = pixel_rot_alpha_deg;
    _pixel_vec.at(j).build_Cell(0, _pixel_size);
  }
  //
}

void pmtCameraHist::dump_mapping_info(){
  pixel_info::print_info_header();
  for(unsigned int i = 0;i<_pixel_vec.size();i++)
    _pixel_vec.at(i).print_info();
}
 
void pmtCameraHist::Clean(){
  for(Int_t i = 0;i<GetNcells();i++){
    SetBinContent(i,0);
  }
}

TCanvas *pmtCameraHist::Draw_cam( TString settings, TString pdf_out_file){
  //
  Double_t lx_camera = 2.5;
  Double_t ly_camera = 2.5;
  //Double_t lx_camera = 0.5;
  //Double_t ly_camera = 0.5;
  Double_t d_frame = 0.1;
  //
  //gStyle->SetPalette(kRainBow);
  //gStyle->SetPalette(kCool);
  //gStyle->SetPalette(kIsland);
  //gStyle->SetPalette(kCherry);
  //TColor::InvertPalette();
  //
  gStyle->SetPalette(kInvertedDarkBodyRadiator);
  //
  gStyle->SetOptStat(kFALSE);
  SetTitle("");
  SetName("");
  //
  TCanvas *c1 = new TCanvas("c1","c1",600,600);
  gPad->SetRightMargin(0.12);
  gPad->SetLeftMargin(0.12);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.15);
  //
  //gPad->SetGridx();
  //gPad->SetGridy();
  //gPad->SetLogz();
  //
  //SetMaximum(500.0);
  //SetMinimum(300.0);
  //SetMinimum(280.0);
  //SetMinimum(299.0);
  //SetMaximum(308.0);
  //
  TH2F *frame = new TH2F( "h2", "h2", 40, -lx_camera/2.0-d_frame,lx_camera/2.0+d_frame,40, -ly_camera/2.0-d_frame,ly_camera/2.0+d_frame);
  frame->SetTitle("");
  frame->GetXaxis()->SetTitle("x, m");
  frame->GetYaxis()->SetTitle("y, m");
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->CenterTitle();
  frame->GetYaxis()->SetTitleOffset(1.5);
  frame->SetStats(kFALSE);
  frame->Draw();
  //
  //settings += " same TEXT";
  settings += " same";
  //
  Draw(settings.Data());
  //
  if(pdf_out_file != "")
    c1->SaveAs(pdf_out_file.Data());
  //
  //
  return c1;
}

void pmtCameraHist::test(TString pdf_out_name){
  for(Int_t i = 0;i<GetNcells();i++)
    SetBinContent(i,i);
  //
  //TRandom3 *rnd = new TRandom3(123123);
  //for(Int_t i = 0;i<GetNcells();i++)
  //SetBinContent(i,(Int_t)rnd->Uniform(1,10));
  //else
  //  SetBinContent(i,10);
  //}
  //SetBinContent(1,1);
  //SetBinContent(2,2);
  //SetBinContent(3,3);
  //SetMarkerSize(0.1);
  //SetLineWidth(0.01);
  Draw_cam("ZCOLOR",pdf_out_name.Data());
  //
}

void pmtCameraHist::Fill_hist(const vector<Float_t>& cam_image){
  for(unsigned int i = 0;i<cam_image.size();i++)
    SetBinContent(i+1,cam_image.at(i));
}

//Double_t pmtCameraHist::angle_between_optical_axis_and_particle( Double_t tel_theta, Double_t tel_phi,
//								 Double_t azimuth, Double_t altitude){
//
//Double_t part_theta = TMath::Pi()-altitude;
//Double_t part_phi = azimuth;
//
//TVector3 tel;
//TVector3 part;
//tel.SetMagThetaPhi(1.0,tel_theta,tel_phi);
//part.SetMagThetaPhi(1.0,part_theta,part_phi);
//return TMath::ACos(tel.Dot(part));
//}

//void pmtCameraHist::rotatePix(Double_t alpha, const Double_t xo, const Double_t yo, Double_t &xn, Double_t &yn){
//if(alpha != 0.0){
//  TVector2 v( xo, yo);
//  xn = v.Rotate(alpha).X();
//  yn = v.Rotate(alpha).Y();
//}
//else{
//  xn = xo;
//  yn = yo;
//}
//}
