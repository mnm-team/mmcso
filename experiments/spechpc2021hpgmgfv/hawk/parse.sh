#!/bin/sh

echo bench,nodes,conf,mode,tcore_default,tresid_default,tcore_offload,tresid_offload

for bench in 534.hpgmgfv_t 634.hpgmgfv_s 734.hpgmgfv_m 834.hpgmgfv_l; do
    for conf in 1 2 3; do
        for nodes in 1 2 4 8 16 32 64 128 256 512; do
            for mode in multiple funneled; do
                default=spectimes-$bench-$mode-nodes-$nodes-conf-$conf.txt
                offload=spectimes-$bench-offload-$mode-nodes-$nodes-conf-$conf.txt
                
                if [ -e $default ]; then
                    tcore_default=$(awk -F'Core time:' '{ printf "%s",$2 }' $default)
                    tresid_default=$(awk -F'Resid time:' '{ printf "%s",$2 }' $default)
                fi

                if [ -e $offload ]; then
                    tcore_offload=$(awk -F'Core time:' '{ printf "%s",$2 }' $offload)
                    tresid_offload=$(awk -F'Resid time:' '{ printf "%s",$2 }' $offload)
                fi

                if [ -e $default ]; then
                    printf "%s,%d,%d,%s,%f,%f,%f,%f\n" $bench $nodes $conf $mode $tcore_default $tresid_default $tcore_offload $tresid_offload
                fi
            done
        done
    done
done