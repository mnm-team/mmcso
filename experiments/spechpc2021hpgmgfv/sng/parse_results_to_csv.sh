#!/bin/sh

# echo "--------------------------------------"
echo bench,nodes,conf,mode,tcore_default,tresid_default,tcore_offload,tresid_offload
# echo "--------------------------------------"

for bench in hpgmgfv_t hpgmgfv_s hpgmgfv_m; do
    if [ $bench = hpgmgfv_t ]; then
        # echo "HPC Spec 534.hpgmgfv_t "
        for nodes in 1 2 4 8 16 32 64; do

            default=./data/spectimes-native-hpgmgfv_t-$nodes-nodes-conf-1.txt
            offload=./data/spectimes-offload-hpgmgfv_t-$nodes-nodes-conf-1.txt
                
            if [ -e $default ]; then
                tcore_default=$(awk -F'Core time:' '{ printf "%s",$2 }' $default)
                tresid_default=$(awk -F'Resid time:' '{ printf "%s",$2 }' $default)
            fi

            if [ -e $offload ]; then
                tcore_offload=$(awk -F'Core time:' '{ printf "%s",$2 }' $offload)
                tresid_offload=$(awk -F'Resid time:' '{ printf "%s",$2 }' $offload)
            fi

            if [ -e $default ]; then
                printf "%s,%d,%d,%s,%f,%f,%f,%f\n" $bench $nodes 1 multiple $tcore_default $tresid_default $tcore_offload $tresid_offload
            fi
        done
    fi

    if [ $bench = hpgmgfv_s ]; then
        # echo "HPC Spec 634.hpgmgfv_s"
        for nodes in 4 8 16 32 64 128 256 512; do
            default=./data/spectimes-native-hpgmgfv_s-$nodes-nodes-conf-1.txt
            offload=./data/spectimes-offload-hpgmgfv_s-$nodes-nodes-conf-1.txt
                
            if [ -e $default ]; then
                tcore_default=$(awk -F'Core time:' '{ printf "%s",$2 }' $default)
                tresid_default=$(awk -F'Resid time:' '{ printf "%s",$2 }' $default)
            fi

            if [ -e $offload ]; then
                tcore_offload=$(awk -F'Core time:' '{ printf "%s",$2 }' $offload)
                tresid_offload=$(awk -F'Resid time:' '{ printf "%s",$2 }' $offload)
            fi

            if [ -e $default ]; then
                printf "%s,%d,%d,%s,%f,%f,%f,%f\n" $bench $nodes 1 multiple $tcore_default $tresid_default $tcore_offload $tresid_offload
            fi
        done
    fi

    if [ $bench = hpgmgfv_m ]; then
        # echo "HPC Spec 734.hpgmgfv_m"
        for nodes in 64 128 256 512; do
            default=./data/spectimes-native-hpgmgfv_m-$nodes-nodes-conf-1.txt
            offload=./data/spectimes-offload-hpgmgfv_m-$nodes-nodes-conf-1.txt
                
            if [ -e $default ]; then
                tcore_default=$(awk -F'Core time:' '{ printf "%s",$2 }' $default)
                tresid_default=$(awk -F'Resid time:' '{ printf "%s",$2 }' $default)
            fi

            if [ -e $offload ]; then
                tcore_offload=$(awk -F'Core time:' '{ printf "%s",$2 }' $offload)
                tresid_offload=$(awk -F'Resid time:' '{ printf "%s",$2 }' $offload)
            fi

            if [ -e $default ]; then
                printf "%s,%d,%d,%s,%f,%f,%f,%f\n" $bench $nodes 1 multiple $tcore_default $tresid_default $tcore_offload $tresid_offload
            fi
        done
    fi
done