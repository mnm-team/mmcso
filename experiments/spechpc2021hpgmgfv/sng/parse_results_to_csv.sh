#!/bin/sh

# echo "--------------------------------------"
echo bench,nodes,conf,tcore_funneled,tresid_funneled,tcore_multiple,tresid_multiple,tcore_offload,tresid_offload
# echo "--------------------------------------"

for bench in hpgmgfv_t hpgmgfv_s hpgmgfv_m; do
    if [ $bench = hpgmgfv_t ]; then
        # echo "HPC Spec 534.hpgmgfv_t "
        for nodes in 1 2 4 8 16 32 64 128; do
            funneled=./data/spectimes-funneled-$bench-$nodes-nodes-conf-1.txt
            multiple=./data/spectimes-native-$bench-$nodes-nodes-conf-1.txt
            offload=./data/spectimes-offload-$bench-$nodes-nodes-conf-1.txt

            if [ -e $funneled ]; then
                tcore_funneled=$(awk -F'Core time:' '{ printf "%s",$2 }' $funneled)
                tresid_funneled=$(awk -F'Resid time:' '{ printf "%s",$2 }' $funneled)
            fi

            if [ -e $multiple ]; then
                tcore_multiple=$(awk -F'Core time:' '{ printf "%s",$2 }' $multiple)
                tresid_multiple=$(awk -F'Resid time:' '{ printf "%s",$2 }' $multiple)
            fi

            if [ -e $offload ]; then
                tcore_offload=$(awk -F'Core time:' '{ printf "%s",$2 }' $offload)
                tresid_offload=$(awk -F'Resid time:' '{ printf "%s",$2 }' $offload)
            fi

            if [ -e $funneled ]; then
                printf "%s,%d,%d,%f,%f,%f,%f,%f,%f\n" $bench $nodes 1 $tcore_funneled $tresid_funneled $tcore_multiple $tresid_multiple $tcore_offload $tresid_offload
            fi
        done
    fi

    if [ $bench = hpgmgfv_s ]; then
        # echo "HPC Spec 634.hpgmgfv_s"
        for nodes in 4 8 16 32 64 128 256 512; do
            funneled=./data/spectimes-funneled-$bench-$nodes-nodes-conf-1.txt
            multiple=./data/spectimes-native-$bench-$nodes-nodes-conf-1.txt
            offload=./data/spectimes-offload-$bench-$nodes-nodes-conf-1.txt
                
            if [ -e $funneled ]; then
                tcore_funneled=$(awk -F'Core time:' '{ printf "%s",$2 }' $funneled)
                tresid_funneled=$(awk -F'Resid time:' '{ printf "%s",$2 }' $funneled)
            fi

            if [ -e $multiple ]; then
                tcore_multiple=$(awk -F'Core time:' '{ printf "%s",$2 }' $multiple)
                tresid_multiple=$(awk -F'Resid time:' '{ printf "%s",$2 }' $multiple)
            fi

            if [ -e $offload ]; then
                tcore_offload=$(awk -F'Core time:' '{ printf "%s",$2 }' $offload)
                tresid_offload=$(awk -F'Resid time:' '{ printf "%s",$2 }' $offload)
            fi

            if [ -e $funneled ]; then
                printf "%s,%d,%d,%f,%f,%f,%f,%f,%f\n" $bench $nodes 1 $tcore_funneled $tresid_funneled $tcore_multiple $tresid_multiple $tcore_offload $tresid_offload
            fi
        done
    fi

    if [ $bench = hpgmgfv_m ]; then
        # echo "HPC Spec 734.hpgmgfv_m"
        for nodes in 64 128 256 512; do
            funneled=./data/spectimes-funneled-$bench-$nodes-nodes-conf-1.txt
            multiple=./data/spectimes-native-$bench-$nodes-nodes-conf-1.txt
            offload=./data/spectimes-offload-$bench-$nodes-nodes-conf-1.txt
                
            if [ -e $funneled ]; then
                tcore_funneled=$(awk -F'Core time:' '{ printf "%s",$2 }' $funneled)
                tresid_funneled=$(awk -F'Resid time:' '{ printf "%s",$2 }' $funneled)
            fi

            if [ -e $multiple ]; then
                tcore_multiple=$(awk -F'Core time:' '{ printf "%s",$2 }' $multiple)
                tresid_multiple=$(awk -F'Resid time:' '{ printf "%s",$2 }' $multiple)
            fi

            if [ -e $offload ]; then
                tcore_offload=$(awk -F'Core time:' '{ printf "%s",$2 }' $offload)
                tresid_offload=$(awk -F'Resid time:' '{ printf "%s",$2 }' $offload)
            fi

            if [ -e $funneled ]; then
                printf "%s,%d,%d,%f,%f,%f,%f,%f,%f\n" $bench $nodes 1 $tcore_funneled $tresid_funneled $tcore_multiple $tresid_multiple $tcore_offload $tresid_offload
            fi
        done
    fi
done