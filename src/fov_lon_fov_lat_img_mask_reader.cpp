//my
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

fov_lon_fov_lat_img_mask_reader::fov_lon_fov_lat_img_mask_reader(TString csv_file_in)
{
  load_csv_data(csv_file_in);
}

fov_lon_fov_lat_img_mask_reader::~fov_lon_fov_lat_img_mask_reader(){;}

//
//fov_lon fov_lat img mask radius_fit center_fov_lon_fit center_fov_lat_fit
//0 0.0 0.0 -1.5426441431045532 0.0 2.1750308444886923 0.9279470380075997 1.0183999799278696
void fov_lon_fov_lat_img_mask_reader::load_csv_data(TString csv_file_in){
  cout<<"csv_file_in  "<<csv_file_in<<endl;
  _nch = 0;
  ifstream fFile(csv_file_in);
  //
  string mot;
  Int_t entry_counter;
  //
  Float_t fov_lon;
  Float_t fov_lat;
  Float_t img;
  Float_t mask;
  //
  if(fFile.is_open()){
    for(Int_t i = 0;i<7;i++)
      fFile>>mot;
    cout<<mot<<endl;
    //
    while(fFile
	  >>entry_counter
	  >>fov_lon
	  >>fov_lat
	  >>img
	  >>mask
	  >>_radius_fit
	  >>_center_fov_lon_fit
	  >>_center_fov_lat_fit){
      _fov_lon_v.push_back(fov_lon);
      _fov_lat_v.push_back(fov_lat);
      _img_v.push_back(img);
      _mask_v.push_back(mask);
      _nch++;
      //if(entry_counter%1000 == 0){
      //	cout<<"entry_counter "<<entry_counter<<endl
      //    <<"fov_lon             "<<fov_lon<<endl
      //    <<"fov_lat             "<<fov_lat<<endl
      //    <<"img                 "<<img<<endl
      //    <<"mask                "<<mask<<endl
      //    <<"_radius_fit         "<<_radius_fit<<endl
      //    <<"_center_fov_lon_fit "<<_center_fov_lon_fit<<endl
      //    <<"_center_fov_lat_fit "<<_center_fov_lat_fit<<endl;
      //}
    }  
    //
    fFile.close();
    //cout<<"_nch "<<_nch<<endl;
  }
}
