from eventio import SimTelFile

import numpy as np
import pickle as pkl
import pandas as pd
import sys
import time

def get_ev_type(datafilein):
    sf = SimTelFile(datafilein)
    primary_id=-999
    for ev in sf:
        primary_id=ev['mc_shower']['primary_id']
        break;

    sf.close()
    return int(primary_id)
    
if __name__ == "__main__":

    datafilein = "/home/burmist/home2/work/CTA/corsika7.7_simtelarray_2020-06-28_patch_DBscan/corsika7.7_simtelarray_2020-06-28_patch/run_simtelarray_muons/datafile/muon_run000.simtel.gz"
    print("primary_id for muon   : ",get_ev_type(datafilein))    
    datafilein = "/home/burmist/home2/work/CTA/scratch/simtel_data/gamma/data/corsika_run1.simtel.gz"
    print("primary_id for gamma  : ",get_ev_type(datafilein))    
    datafilein = "/home/burmist/home2/work/CTA/scratch/simtel_data/proton_st/data/corsika_run1.simtel.gz"
    print("primary_id for proton : ",get_ev_type(datafilein))    
