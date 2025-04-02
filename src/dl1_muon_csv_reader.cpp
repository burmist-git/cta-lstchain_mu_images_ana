//my
#include "dl1_muon_csv_reader.hh"

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

dl1_muon_csv_reader::dl1_muon_csv_reader(TString csv_file_in, Int_t n_meta_data, Int_t nch) : _n_meta_data(n_meta_data), _nch(nch)
{
  load_csv_data(csv_file_in);
}

dl1_muon_csv_reader::~dl1_muon_csv_reader(){;}

void dl1_muon_csv_reader::load_csv_data(TString csv_file_in){
  cout<<"csv_file_in  "<<csv_file_in<<endl
      <<"_n_meta_data "<<_n_meta_data<<endl
      <<"_nch         "<<_nch<<endl;
  ifstream fFile(csv_file_in);
  string mot;
  Int_t entry_counter;
  //
  Float_t obs_id_tmp;
  Float_t event_id_tmp;
  Float_t mc_energy_tmp;
  Float_t mc_core_x_tmp;
  Float_t mc_core_y_tmp;
  Float_t mc_alt_tmp;
  Float_t mc_az_tmp;
  //
  //
  Float_t ch_val_tmp;
  Float_t cht_val_tmp;
  Float_t chm_val_tmp;
  //
  //
  if(fFile.is_open()){
    for(Int_t i = 0;i<_n_meta_data;i++)
      fFile>>mot;
    for(Int_t i = 0;i<_nch;i++)
      fFile>>mot;
    for(Int_t i = 0;i<_nch;i++)
      fFile>>mot;
    for(Int_t i = 0;i<_nch;i++){
      fFile>>mot;
      //cout<<mot<<endl;
    }
    //
    while(fFile
	  >>entry_counter
	  >>obs_id_tmp
	  >>event_id_tmp
	  >>mc_energy_tmp
	  >>mc_core_x_tmp
	  >>mc_core_y_tmp
	  >>mc_alt_tmp
	  >>mc_az_tmp){
      //
      _obs_id_v.push_back((Int_t)obs_id_tmp);
      _event_id_v.push_back((Int_t)event_id_tmp);
      _mc_energy_v.push_back(mc_energy_tmp);
      _mc_core_x_v.push_back(mc_core_x_tmp);
      _mc_core_y_v.push_back(mc_core_y_tmp);
      _mc_alt_v.push_back(mc_alt_tmp);
      _mc_az_v.push_back(mc_az_tmp);
      //
      if(entry_counter%1000 == 0){
	cout<<"entry_counter "<<entry_counter<<endl
	    <<"obs_id_tmp    "<<obs_id_tmp<<endl
	    <<"event_id_tmp  "<<event_id_tmp<<endl
	    <<"mc_energy_tmp "<<mc_energy_tmp<<endl
	    <<"mc_core_x_tmp "<<mc_core_x_tmp<<endl
	    <<"mc_core_y_tmp "<<mc_core_y_tmp<<endl
	    <<"mc_alt_tmp    "<<mc_alt_tmp<<endl
	    <<"mc_az_tmp     "<<mc_az_tmp<<endl;
      }
      //
      //
      vector<Float_t> ch_v_tmp;    
      for(Int_t i = 0;i<_nch;i++){
	fFile>>ch_val_tmp;
	ch_v_tmp.push_back(ch_val_tmp);
      }
      _ch_v.push_back(ch_v_tmp);
      //cout<<"ch_val_tmp "<<ch_val_tmp<<endl;
      //
      vector<Float_t> cht_v_tmp;
      for(Int_t i = 0;i<_nch;i++){
	fFile>>cht_val_tmp;
	cht_v_tmp.push_back(cht_val_tmp);
      }
      _cht_v.push_back(cht_v_tmp);
      //cout<<"cht_val_tmp "<<cht_val_tmp<<endl;
      //
      vector<Int_t> chm_v_tmp;
      vector<Float_t> chmf_v_tmp;
      for(Int_t i = 0;i<_nch;i++){
	fFile>>chm_val_tmp;
	chm_v_tmp.push_back((Int_t)chm_val_tmp);
	chmf_v_tmp.push_back(chm_val_tmp);
      }
      _chm_v.push_back(chm_v_tmp);
      _chmf_v.push_back(chmf_v_tmp);
      //cout<<"chm_val_tmp "<<chm_val_tmp<<endl;
    }
    //
    fFile.close();
  }
}
