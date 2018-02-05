#!bin/bash

cd Histogram/
hadd SingleTop_histogram.root St_sch_4l_histogram.root St_tW_inc_antitop_histogram.root St_tW_inc_top_histogram.root St_tch_inc_antitop_histogram.root St_tch_inc_top_histogram.root
cd ../
