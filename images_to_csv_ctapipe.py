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
    mc_h5_table=h5file.root.simulation.event.subarray.shower
    dl1_h5_table_image=h5file.root.dl1.event.telescope.images.tel_001
    mc_image_h5_table=h5file.root.simulation.event.telescope.images.tel_001
    muon_h5_table=h5file.root.dl1.event.telescope.muon.tel_001
    # 7
    mc_obs_id=mc_h5_table[:]['obs_id']
    mc_event_id=mc_h5_table[:]['event_id']
    mc_energy=mc_h5_table[:]['true_energy']
    mc_core_x=mc_h5_table[:]['true_core_x']
    mc_core_y=mc_h5_table[:]['true_core_y']
    mc_alt=mc_h5_table[:]['true_alt']
    mc_az=mc_h5_table[:]['true_az']
    #2
    image_obs_id=dl1_h5_table_image[:]['obs_id']
    image_event_id=dl1_h5_table_image[:]['event_id']
    #2
    mc_image_obs_id=mc_image_h5_table[:]['obs_id']
    mc_image_event_id=mc_image_h5_table[:]['event_id']
    #2
    muon_obs_id=muon_h5_table[:]['obs_id']
    muon_event_id=muon_h5_table[:]['event_id']
    #22
    muonring_center_fov_lon=muon_h5_table[:]['muonring_center_fov_lon']
    muonring_center_fov_lat=muon_h5_table[:]['muonring_center_fov_lat']
    muonring_radius=muon_h5_table[:]['muonring_radius']
    muonring_center_phi=muon_h5_table[:]['muonring_center_phi']
    muonring_center_distance=muon_h5_table[:]['muonring_center_distance']
    muonparameters_containment=muon_h5_table[:]['muonparameters_containment']
    muonparameters_completeness=muon_h5_table[:]['muonparameters_completeness']
    muonparameters_intensity_ratio=muon_h5_table[:]['muonparameters_intensity_ratio']
    muonparameters_mean_squared_error=muon_h5_table[:]['muonparameters_mean_squared_error']
    muonparameters_ring_intensity=muon_h5_table[:]['muonparameters_ring_intensity']
    muonparameters_intensity_outside_ring=muon_h5_table[:]['muonparameters_intensity_outside_ring']
    muonparameters_n_pixels_in_ring=muon_h5_table[:]['muonparameters_n_pixels_in_ring']
    muonparameters_mean_intensity_outside_ring=muon_h5_table[:]['muonparameters_mean_intensity_outside_ring']
    muonparameters_radial_std_dev=muon_h5_table[:]['muonparameters_radial_std_dev']
    muonparameters_skewness=muon_h5_table[:]['muonparameters_skewness']
    muonparameters_excess_kurtosis=muon_h5_table[:]['muonparameters_excess_kurtosis']
    muonefficiency_width=muon_h5_table[:]['muonefficiency_width']
    muonefficiency_impact=muon_h5_table[:]['muonefficiency_impact']
    muonefficiency_impact_x=muon_h5_table[:]['muonefficiency_impact_x']
    muonefficiency_impact_y=muon_h5_table[:]['muonefficiency_impact_y']
    muonefficiency_optical_efficiency=muon_h5_table[:]['muonefficiency_optical_efficiency']
    muonefficiency_likelihood_value=muon_h5_table[:]['muonefficiency_likelihood_value']
    #
    image_charge=dl1_h5_table_image[:]['image']
    image_peak_time=dl1_h5_table_image[:]['peak_time']
    image_mask=dl1_h5_table_image[:]['image_mask']
    true_image=mc_image_h5_table[:]['true_image']
    npixel=len(image_charge[0])
    print("image_charge ",image_charge.shape)
    print("image_time   ",image_peak_time.shape)
    print("image_mask   ",image_mask.shape)
    print("true_image   ",true_image.shape)
    print("npixel       ",npixel)
    #
    data_arr=np.array(
        [ mc_obs_id, mc_event_id, mc_energy, mc_core_x, mc_core_y, mc_alt, mc_az,
          image_obs_id, image_event_id, mc_image_obs_id, mc_image_event_id, muon_obs_id, muon_event_id,
          muonring_center_fov_lon, muonring_center_fov_lat, muonring_radius, muonring_center_phi, muonring_center_distance,
          muonparameters_containment, muonparameters_completeness, muonparameters_intensity_ratio, muonparameters_mean_squared_error,
          muonparameters_ring_intensity, muonparameters_intensity_outside_ring, muonparameters_n_pixels_in_ring,
          muonparameters_mean_intensity_outside_ring, muonparameters_radial_std_dev, muonparameters_skewness,
          muonparameters_excess_kurtosis, muonefficiency_width, muonefficiency_impact, muonefficiency_impact_x,
          muonefficiency_impact_y, muonefficiency_optical_efficiency, muonefficiency_likelihood_value]
    ).transpose()
    data_arr_columns=[
        'mc_obs_id', 'mc_event_id', 'mc_energy', 'mc_core_x', 'mc_core_y', 'mc_alt', 'mc_az',
        'image_obs_id', 'image_event_id', 'mc_image_obs_id', 'mc_image_event_id', 'muon_obs_id', 'muon_event_id',
        'muonring_center_fov_lon', 'muonring_center_fov_lat', 'muonring_radius', 'muonring_center_phi', 'muonring_center_distance',
        'muonparameters_containment', 'muonparameters_completeness', 'muonparameters_intensity_ratio', 'muonparameters_mean_squared_error',
        'muonparameters_ring_intensity', 'muonparameters_intensity_outside_ring', 'muonparameters_n_pixels_in_ring',
        'muonparameters_mean_intensity_outside_ring', 'muonparameters_radial_std_dev', 'muonparameters_skewness',
        'muonparameters_excess_kurtosis', 'muonefficiency_width', 'muonefficiency_impact', 'muonefficiency_impact_x',
        'muonefficiency_impact_y', 'muonefficiency_optical_efficiency', 'muonefficiency_likelihood_value']
    print("data_arr           ",data_arr.shape)
    print("data_arr_columns   ",len(data_arr_columns))
    print("data_arr_columns   ",data_arr_columns)
    #
    [data_arr_columns.append(str('ch'+str(i))) for i in np.arange(npixel)];
    [data_arr_columns.append(str('cht'+str(i))) for i in np.arange(npixel)];
    [data_arr_columns.append(str('chm'+str(i))) for i in np.arange(npixel)];
    [data_arr_columns.append(str('ch_true'+str(i))) for i in np.arange(npixel)];
    #
    #df_h5_out = pd.DataFrame(
    #    data_arr,
    #    columns=data_arr_columns,
    #)
    df_h5_out = pd.DataFrame(
        np.column_stack(
            (
                data_arr,
                image_charge,
                image_peak_time,
                image_mask.astype(int),
                true_image,
            )
        ),
        columns=data_arr_columns
    )
    df_h5_out=df_h5_out.fillna(-999.0)
    df_h5_out.to_csv(csvout,sep=" ")
    h5file.close()
    #

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
