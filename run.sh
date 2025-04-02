#!/bin/bash

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d                  : single root file"
    echo " [0] -h                  : help"
    echo " [0] -c                  : recompile"
    echo " [0] --map               : get map"
    echo " [0] --r0_to_dl1         : r0_to_dl1"
    echo " [0] --dl1_muon_analysis : dl1_muon_analysis"
    echo " [0] --images_to_csv     : images_to_csv"
}

if [ $# -eq 0 ]; then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	printHelp
    elif [ "$1" = "-h" ]; then
	printHelp
    elif [ "$1" = "--r0_to_dl1" ]; then
	echo "--r0_to_dl1"
	#for i in $(seq 0 9); do
	#    datafileIn="/home/burmist/home2/work/CTA/corsika7.7_simtelarray_2020-06-28_patch_DBscan/corsika7.7_simtelarray_2020-06-28_patch/run_simtelarray_muons/datafile/muon_run00$i.simtel.gz"
	#    outputDir="/home/burmist/home2/work/CTA/cta-lstchain/run/run_00$i"
	#    configFile="/home/burmist/home2/work/CTA/cta-lstchain/run/lstchain_mc_config_muons.json"
	#    echo "$datafileIn"
	#    time python /home/burmist/home2/work/CTA/cta-lstchain/lstchain/scripts/lstchain_mc_r0_to_dl1.py --input-file $datafileIn --output-dir $outputDir --config $configFile
	#done
    elif [ "$1" = "--dl1_muon_analysis" ]; then
	echo "--dl1_muon_analysis"
	#for i in $(seq 0 9); do
	#    h5fileIn="/home/burmist/home2/work/CTA/cta-lstchain/run/run_00$i/dl1_muon_run00$i.h5"
	#    fitsfileOut="/home/burmist/home2/work/CTA/cta-lstchain/run/run_00$i/muon_run00$i.fits"
	#    echo $h5fileIn
	#    python /home/burmist/home2/work/CTA/cta-lstchain/lstchain/scripts/lstchain_dl1_muon_analysis.py --input-file $h5fileIn --output-file $fitsfileOut
	#done
    elif [ "$1" = "--images_to_csv" ]; then
	echo "--images_to_csv"
	#for i in $(seq 0 9); do
	#    python images_to_csv.py run_00$i/dl1_muon_run00$i.h5 run_00$i/dl1_muon_run00$i.csv
	#done
    elif [ "$1" = "--map" ]; then
	python images_to_csv.py ./data/run_000/dl1_muon_run000.h5 
    elif [ "$1" = "-c" ]; then
	make clean; make -j	
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi
	
#srun /home/vadym.voitsekhovskyi/mambaforge/envs/lstchain/lib/python3.11/site-packages/lstchain/scripts/lstchain_mc_r0_to_dl1.py --input-file /fefs/aswg/workspace/vadym.voitsekhovskyi/2024muons/lst_study/simtel/output/new_nsb_study/2024year_tuned_no_outliers_additional/run101_muon.simtel.gz --output-dir /fefs/aswg/workspace/vadym.voitsekhovskyi/2024muons/lst_study/lstchain_postprocess/output/psf_work/eslope_-27 --config /fefs/aswg/workspace/vadym.voitsekhovskyi/2024muons/lst_study/config_folder/lstchain_standard_config_global_integration_cor.json

#datafileIn="/home/burmist/home2/work/CTA/corsika7.7_simtelarray_2020-06-28_patch_DBscan/corsika7.7_simtelarray_2020-06-28_patch/run_simtelarray_muons/datafile/muon_run001.simtel.gz"
#outputDir="/home/burmist/home2/work/CTA/cta-lstchain/run/run_001"
#configFile="/home/burmist/home2/work/CTA/cta-lstchain/run/lstchain_mc_config_muons.json"
#python /home/burmist/home2/work/CTA/cta-lstchain/lstchain/scripts/lstchain_mc_r0_to_dl1.py --input-file $datafileIn --output-dir $outputDir --config $configFile

#srun /home/vadym.voitsekhovskyi/mambaforge/envs/lstchain/lib/python3.11/site-packages/lstchain/scripts/lstchain_dl1_muon_analysis.py --input-file /fefs/aswg/workspace/vadym.voitsekhovskyi/2024muons/lst_study/lstchain_postprocess/output/psf_work/eslope_-27/dl1_run101_muon.h5 --output-file /fefs/aswg/workspace/vadym.voitsekhovskyi/2024muons/lst_study/lstchain_postprocess/output/psf_work/eslope_-27/tables/muon_table_run1.fits

#h5fileIn="/home/burmist/home2/work/CTA/cta-lstchain/run/run_001/dl1_muon_run001.h5"
#fitsfileOut="/home/burmist/home2/work/CTA/cta-lstchain/run/run_001/muon_run001.fits"
#python /home/burmist/home2/work/CTA/cta-lstchain/lstchain/scripts/lstchain_dl1_muon_analysis.py --input-file $h5fileIn --output-file $fitsfileOut



