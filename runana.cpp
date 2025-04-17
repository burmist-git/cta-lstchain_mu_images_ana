//my
#include "src/anaConf.hh"
#include "src/dbscan.hh"
#include "src/muonRingFitter.hh"
#include "src/pmtCameraHist.hh"
#include "src/dl1_muon_csv_reader.hh"
#include "src/dl1_muon_ctapipe_csv_reader.hh"
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
    for(unsigned int i = 0; i<1000; i++){
      TString out_name = "./out_pdf/test_out_ev";
      out_name += i;
      out_name += ".pdf";
      plotter->plot_muon_all(i, out_name);
    }
    plotter->fill_histos(hist_root_out);
  }
  else{
    cout<<" --> ERROR in input arguments "<<endl
	<<" runID [1] = 0 (execution ID number)"<<endl
      	<<"       [2] - pmt map"<<endl
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
  }
  return 0;
}
