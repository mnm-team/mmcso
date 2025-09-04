#!/bin/sh

for bench in hpgmgfv_t hpgmgfv_s hpgmgfv_m; do
    if [ $bench = hpgmgfv_t ]; then
        echo "Collect HPC Spec 534.hpgmgfv_t "
        for mode in native offload; do
            if [ $mode = native ]; then 
                cp ./jobs/hpgmgfv_t/1_8_nodes/native_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_t/16_nodes/native_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_t/32_nodes/native_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_t/64_nodes/native_multiple/*.txt ./data/
                # cp ./jobs/hpgmgfv_t/128_nodes/native_multiple/*.txt ./data/
            fi

            if [ $mode = offload ]; then 
                cp ./jobs/hpgmgfv_t/1_8_nodes/offload_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_t/16_nodes/offload_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_t/32_nodes/offload_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_t/64_nodes/offload_multiple/*.txt ./data/
                # cp ./jobs/hpgmgfv_t/128_nodes/offload_multiple/*.txt ./data/
            fi
        done
    fi

    if [ $bench = hpgmgfv_s ]; then
        echo "Collect HPC Spec 634.hpgmgfv_s"
        for mode in native offload; do
            if [ $mode = native ]; then 
                cp ./jobs/hpgmgfv_s/4_8_nodes/native_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_s/16_nodes/native_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_s/32_nodes/native_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_s/64_nodes/native_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_s/128_nodes/native_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_s/256_nodes/native_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_s/512_nodes/native_multiple/*.txt ./data/
            fi

            if [ $mode = offload ]; then 
                cp ./jobs/hpgmgfv_s/4_8_nodes/offload_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_s/16_nodes/offload_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_s/32_nodes/offload_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_s/64_nodes/offload_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_s/128_nodes/offload_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_s/256_nodes/offload_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_s/512_nodes/offload_multiple/*.txt ./data/
            fi
        done
    fi

    if [ $bench = hpgmgfv_m ]; then
        echo "Collect HPC Spec 734.hpgmgfv_m"
        for mode in native offload; do
            if [ $mode = native ]; then 
                cp ./jobs/hpgmgfv_m/64_nodes/native_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_m/128_nodes/native_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_m/256_nodes/native_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_m/512_nodes/native_multiple/*.txt ./data/
            fi

            if [ $mode = offload ]; then 
                cp ./jobs/hpgmgfv_m/64_nodes/offload_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_m/128_nodes/offload_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_m/256_nodes/offload_multiple/*.txt ./data/
                cp ./jobs/hpgmgfv_m/512_nodes/offload_multiple/*.txt ./data/
            fi
        done
    fi
done