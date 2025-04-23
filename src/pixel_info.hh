#pragma once

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

class TVector3;

struct pixel_info {
  //
  Int_t entry_id;
  Int_t pixel_id;
  Float_t pix_x, pix_y, pix_area;
  //
  Float_t pix_phi;
  Float_t pix_r;
  //
  Float_t pixel_rot_alpha_deg;
  //
  const Int_t n = 7;
  Double_t *xp = new Double_t[n];
  Double_t *yp = new Double_t[n];
  //
  pixel_info(){
    entry_id = -999;
    pixel_id = -999;
    pix_x = -999.0;
    pix_y = -999.0;
    pix_area = -999.0;
    //
    pix_phi = -999.0;
    pix_r = -999.0;
    //
    pixel_rot_alpha_deg = 0.0;
    //
    for(Int_t i = 0;i<n;i++){
      xp[i] = -999.0;
      yp[i] = -999.0;
    }
  }
  void print_info(){
    std::cout<<std::setw(15)<<entry_id<<" "
	     <<std::setw(15)<<pixel_id<<" "
	     <<std::setw(15)<<pix_x<<" "
      	     <<std::setw(15)<<pix_y<<" "
      	     <<std::setw(15)<<pix_area<<" "
	     <<std::endl;
  }
  static void print_info_header(){
    std::cout<<std::setw(15)<<"entry_id"<<" "
	     <<std::setw(15)<<"pixel_id"<<" "
      	     <<std::setw(15)<<"pix_x"<<" "
	     <<std::setw(15)<<"pix_y"<<" "
      	     <<std::setw(15)<<"pix_area"<<" "
	     <<std::endl;
  }
  static Double_t get_pixel_size_from_pix_area(Double_t pix_area){
    if(pix_area<0.0)
      return 0.0;
    return 2.0*TMath::Sqrt(pix_area/3.0)*0.94;
  }
  static Float_t get_pixel_pitch(const std::vector<pixel_info> &pixel_vec){
    Float_t x1 = pixel_vec.at(0).pix_x;
    Float_t y1 = pixel_vec.at(0).pix_y;
    Float_t x2 = pixel_vec.at(1).pix_x;
    Float_t y2 = pixel_vec.at(1).pix_y;
    return get_dist_between_pixel( x1, y1, x2, y2);
  }  
  static Float_t get_dist_between_pixel(Float_t x1, Float_t y1, Float_t x2, Float_t y2){
    return TMath::Sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
  }
  static Float_t get_pixel_pixel_rotation_angle_deg(const std::vector<pixel_info> &pixel_vec){
    Float_t x1 = pixel_vec.at(0).pix_x;
    Float_t y1 = pixel_vec.at(0).pix_y;
    Float_t x2 = pixel_vec.at(1).pix_x;
    Float_t y2 = pixel_vec.at(1).pix_y;
    TVector2 v( x2 - x1, y2 - y1);
    std::cout<<"v.Phi() "<<v.Phi()*180.0/TMath::Pi()<<std::endl;
    return v.Phi()*180.0/TMath::Pi();
  }
  static Float_t get_dist_in_m_from_deg(Float_t val_in_deg, Float_t effective_focal_length_m = 29.30565071105957){
    return effective_focal_length_m*TMath::Tan(val_in_deg*TMath::Pi()/180.0);
  }
  static Float_t get_deg_from_dist_in_m(Float_t val_in_m, Float_t effective_focal_length_m = 29.30565071105957){
    return  TMath::ATan(val_in_m/effective_focal_length_m)*180.0/TMath::Pi();
  }
  void rotatePix(Double_t rot_alpha_deg){
    if(rot_alpha_deg != 0.0){
      TVector2 v(pix_x,pix_y);
      pix_x = v.Rotate(rot_alpha_deg/180.0*TMath::Pi()).X();
      pix_y = v.Rotate(rot_alpha_deg/180.0*TMath::Pi()).Y();
    }
  }
  void build_Cell(Int_t cell_type_id, Double_t l, Float_t x_v, Float_t y_v){
    if(cell_type_id == 0){
      Double_t alpha   = 2.0*TMath::Pi()/6.0;
      Double_t alpha_2 = alpha/2.0;
      Double_t alpha0  = alpha_2;
      Double_t l_2 = l/2.0;
      Double_t r = l_2/TMath::Cos(alpha_2);
      Double_t theta = 0.0;
      for(Int_t i = 0;i<n;i++){
	theta = alpha0 + alpha*i;
	TVector2 v(r*TMath::Cos(theta),r*TMath::Sin(theta));
	xp[i] = v.Rotate(pixel_rot_alpha_deg/180.0*TMath::Pi()).X() + x_v;
	yp[i] = v.Rotate(pixel_rot_alpha_deg/180.0*TMath::Pi()).Y() + y_v;
      }
    }
    else{
      std::cout<<"  ---> ERROR : cell_type_id = "<<cell_type_id<<std::endl;
      assert(0);
    }
  }
  void build_Cell(Int_t cell_type_id, Double_t l){
    build_Cell(cell_type_id, l, pix_x, pix_y);
  }
};
