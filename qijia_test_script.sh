# Block size in kB
for blocksize in 32 64 128 256 512 1024
do
    # Iter
    for i in `seq 1 3`
    do
        numactl -C0 -m0 ./lzbench -ezstd,1/lz4/zlib,6/qpl/qpl_sw -b$blocksize ../lineitem.tbl
        echo "Finished BlockSize="$blocksize",iter "$i
    done
done

