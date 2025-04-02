import pandas as pd
import numpy as np
import glob
import gc
import matplotlib.pyplot as plt
from matplotlib import colors
from astropy.coordinates import SkyCoord, AltAz, angular_separation
import astropy.units as u
from scipy.stats import binned_statistic
from scipy.signal import lombscargle
import h5py
from astropy.io import fits
from astropy.table import Table
from tables import open_file

import sys
import time

def map_to_csv( h5filein, mapcsvout):
    h5file = open_file(h5filein, "a")
    #
    the_h5_table=h5file.root.configuration.instrument.telescope.camera.geometry_0
    the_map=the_h5_table[:]
    #
    df_the_map = pd.DataFrame(the_map, columns=['pix_id','pix_x','pix_y','pix_area'])
    df_the_map.to_csv(mapcsvout,sep=" ")
    #
    h5file.close()

def images_to_csv(h5filein, csvout):
    h5file = open_file(h5filein, "a")
    #
    the_h5_table=h5file.root.dl1.event.telescope.parameters.LST_LSTCam
    h5_out_obs_id=the_h5_table[:]['obs_id']
    h5_out_event_id=the_h5_table[:]['event_id']
    h5_out_mc_energy=the_h5_table[:]['mc_energy']
    h5_out_mc_core_x=the_h5_table[:]['mc_core_x']
    h5_out_mc_core_y=the_h5_table[:]['mc_core_y']
    h5_out_mc_alt=the_h5_table[:]['mc_alt']
    h5_out_mc_az=the_h5_table[:]['mc_az']
    #
    the_h5_table_image=h5file.root.dl1.event.telescope.image.LST_LSTCam
    image_charge_arr=the_h5_table_image[:]['image']
    image_time_arr=the_h5_table_image[:]['peak_time']
    image_mask_arr=the_h5_table_image[:]['image_mask']
    #
    meta_data_arr=np.array([h5_out_obs_id,h5_out_event_id,h5_out_mc_energy,h5_out_mc_core_x,h5_out_mc_core_y,h5_out_mc_alt,h5_out_mc_az]).transpose()
    meta_data_arr_columns=['obs_id','event_id','mc_energy','mc_core_x','mc_core_y','mc_alt','mc_az']
    [meta_data_arr_columns.append(str('ch'+str(i))) for i in np.arange(len(the_h5_table_image[0]['image']))];
    [meta_data_arr_columns.append(str('cht'+str(i))) for i in np.arange(len(the_h5_table_image[0]['image']))];
    [meta_data_arr_columns.append(str('chm'+str(i))) for i in np.arange(len(the_h5_table_image[0]['image']))];
    #
    print("image_charge ",image_charge_arr.shape)
    print("image_time   ",image_time_arr.shape)
    print("image_mask   ",image_mask_arr.shape)
    print("meta_data    ",meta_data_arr.shape)
    #
    df_h5_out = pd.DataFrame(np.column_stack((meta_data_arr,image_charge_arr,image_time_arr, image_mask_arr.astype(int))), columns=meta_data_arr_columns)
    df_h5_out.to_csv(csvout,sep=" ")
    h5file.close()

if __name__ == "__main__":

    if (len(sys.argv)==3):
        #
        h5filein = str(sys.argv[1])
        csvout = str(sys.argv[2])
        #
        print("h5filein = ", h5filein)
        print("csvout   = ", csvout)
        #
        tic = time.time()
        #test(datafilein)
        images_to_csv(h5filein, csvout)
        toc = time.time()
        print('{:.2f} s'.format(toc - tic))
    elif (len(sys.argv)==2):
        h5filein = str(sys.argv[1])
        mapcsvout = str(h5filein + ".map")
        #
        print("h5filein  = ", h5filein)
        print("mapcsvout = ", mapcsvout)
        #
        tic = time.time()
        #test(datafilein)
        map_to_csv(h5filein, mapcsvout)
        toc = time.time()
        print('{:.2f} s'.format(toc - tic))
