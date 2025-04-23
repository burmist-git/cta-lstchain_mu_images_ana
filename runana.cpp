//my
#include "src/anaConf.hh"
#include "src/dbscan.hh"
#include "src/muonRingFitter.hh"
#include "src/pmtCameraHist.hh"
#include "src/dl1_muon_csv_reader.hh"
#include "src/dl1_muon_ctapipe_csv_reader.hh"
#include "src/fov_lon_fov_lat_img_mask_reader.hh"
#include "src/plt.hh"

//root
#include "TROOT.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TGraph.h"

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]){
  cout<<"--> main "<<endl;
  if(argc == 3 && atoi(argv[1])==0){
    TString pmt_map = argv[2];
    cout<<"--> Parameters <--"<<endl
	<<"pmt_map : "<<pmt_map<<endl;
    //
    pmtCameraHist *pmt_cam = new pmtCameraHist("pmt_cam","pmt_cam",pmt_map,0.0);
    pmt_cam->dump_mapping_info();
    pmt_cam->test();
    pmt_cam->test_out_root();
  }
  else if(argc == 3 && atoi(argv[1])==10){
    TString pmt_map = argv[2];
    cout<<"--> Parameters <--"<<endl
	<<"pmt_map : "<<pmt_map<<endl;
    //
    pmtCameraHist *pmt_cam = new pmtCameraHist("pmt_cam","pmt_cam",pmt_map,0.0,true);
    pmt_cam->dump_mapping_info();
    pmt_cam->test();
    pmt_cam->test_out_root();
  }
  else if(argc == 3 && atoi(argv[1])==1){
    TString csv_in = argv[2];
    cout<<"--> Parameters <--"<<endl
	<<"csv_in : "<<csv_in<<endl;
    dl1_muon_csv_reader *reader = new dl1_muon_csv_reader(csv_in);
  }
  else if(argc == 5 && atoi(argv[1])==2){
    TString csv_in = argv[2];
    TString pmt_map = argv[3];
    TString hist_root_out = argv[4];    
    //    
    cout<<"--> Parameters <--"<<endl
	<<"csv_in        : "<<csv_in<<endl
      	<<"pmt_map       : "<<pmt_map<<endl
      	<<"hist_root_out : "<<hist_root_out<<endl;
    dl1_muon_csv_reader *reader = new dl1_muon_csv_reader(csv_in);
    plt *plotter = new plt(reader,pmt_map);
    plotter->plot_and_save(hist_root_out);
  }
  else if(argc == 5 && atoi(argv[1])==3){
    TString csv_in = argv[2];
    TString pmt_map = argv[3];
    TString hist_root_out = argv[4];    
    //    
    cout<<"--> Parameters <--"<<endl
	<<"csv_in        : "<<csv_in<<endl
      	<<"pmt_map       : "<<pmt_map<<endl
      	<<"hist_root_out : "<<hist_root_out<<endl;
    dl1_muon_ctapipe_csv_reader *reader = new dl1_muon_ctapipe_csv_reader(csv_in);
    plt *plotter = new plt(reader,pmt_map);
    //plotter->plot_and_save_ctapipe(hist_root_out);
    for(unsigned int i = 0; i<100; i++){
      TString out_name = "./out_pdf/test_out_ev";
      out_name += i;
      out_name += ".pdf";
      plotter->plot_muon_all(i, out_name);
    }
    plotter->fill_histos(hist_root_out);
    cout<<"reader->get_mc_obs_id_v().size() = "<<reader->get_mc_obs_id_v().size()<<endl;
  }
  else if(argc > 4 && atoi(argv[1])==4){
    TString pmt_map = argv[2];
    TString hist_root_out = argv[3];
    //    
    cout<<"--> Parameters <--"<<endl
      	<<"hist_root_out : "<<hist_root_out<<endl;
    vector<fov_lon_fov_lat_img_mask_reader*> reader_v;
    vector<plt*> plotter_v;
    vector<TString> csv_in_v;
    //
    for(Int_t i = 3; i<argc; i++ ){
      TString csv_in = argv[i];
      csv_in_v.push_back(csv_in);
      //cout<<"csv_in = "<<csv_in<<endl;
      fov_lon_fov_lat_img_mask_reader *reader = new fov_lon_fov_lat_img_mask_reader(csv_in);
      plt *plotter = new plt(reader,pmt_map);
      reader_v.push_back(reader);
      plotter_v.push_back(plotter);
    }
    //
    for(unsigned int i = 0; i<reader_v.size(); i++ ){
      TString pdf_out_file = csv_in_v.at(i);
      pdf_out_file += ".pdf";
      plotter_v.at(i)->plot_muon_lon_lat( i, pdf_out_file);
      //cout<<"size                   "<<reader_v.at(i)->get_fov_lon_v().size()<<endl
      //	  <<"get_radius_fit         "<<reader_v.at(i)->get_radius_fit()<<endl
      //	  <<"get_center_fov_lon_fit "<<reader_v.at(i)->get_center_fov_lon_fit()<<endl
      //	  <<"get_center_fov_lat_fit "<<reader_v.at(i)->get_center_fov_lat_fit()<<endl;
    }
  }
  else{
    cout<<" --> ERROR in input arguments "<<endl
	<<" runID [1] = 0 (execution ID number)"<<endl
      	<<"       [2] - pmt map"<<endl
	<<" runID [1] = 10 (execution ID number)"<<endl
      	<<"       [2] - lon lat pmt map"<<endl
	<<" runID [1] = 1 (execution ID number)"<<endl
      	<<"       [2] - csv in"<<endl
	<<" runID [1] = 2 (execution ID number)"<<endl
      	<<"       [2] - csv in"<<endl
	<<"       [3] - pmt map"<<endl
	<<"       [4] - hist root out"<<endl
	<<" runID [1] = 3 (execution ID number)"<<endl
      	<<"       [2] - csv in (ctapipe)"<<endl
	<<"       [3] - pmt map"<<endl
	<<"       [4] - hist root out"<<endl;
    cout<<" runID [1] = 4 (execution ID number)"<<endl
      	<<"       [2] - hist root out"<<endl
	<<"       [3] - csv in "<<endl
	<<"       [4] - csv in "<<endl
	<<"       [i] - csv in "<<endl
    	<<"       [n] - csv in "<<endl;
  }
  return 0;
}
