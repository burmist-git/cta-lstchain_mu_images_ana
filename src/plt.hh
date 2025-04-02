#pragma once

//my
#include "dl1_muon_csv_reader.hh"

//root
#include "TROOT.h"

//C, C++
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

class plt {
public:    

  plt(dl1_muon_csv_reader* reader, TString pmt_map);
  ~plt();
  //
  void plot_and_save(TString hist_root_out);
  
private:

  dl1_muon_csv_reader* _reader;
  TString _pmt_map;
  
};
