//my
#include "plt.hh"
#include "pmtCameraHist.hh"
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

plt::plt(dl1_muon_csv_reader* reader, TString pmt_map) : _reader(reader), _pmt_map(pmt_map)
{
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
