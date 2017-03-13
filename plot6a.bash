echo $'\nL1=8 L2=128\n'
res=$(./sim_cache 64 8192 4 131072 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



res=$(./sim_cache 64 8192 4 131072 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'





res=$(./sim_cache 64 8192 4 131072 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



echo $'\nL1=8 L2=256\n'
res=$(./sim_cache 64 8192 4 262144 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




res=$(./sim_cache 64 8192 4 262144 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



res=$(./sim_cache 64 8192 4 262144 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'


echo $'\nL1=8 L2=512\n'

res=$(./sim_cache 64 8192 4 524288 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'


res=$(./sim_cache 64 8192 4 524288 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




res=$(./sim_cache 64 8192 4 524288 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




echo $'\nL1=8 L2=1024\n'


res=$(./sim_cache 64 8192 4 1048576 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



res=$(./sim_cache 64 8192 4 1048576 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



res=$(./sim_cache 64 8192 4 1048576 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



echo $'\nL1=16 L2=128\n'


res=$(./sim_cache 64 16384 4 131072 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



res=$(./sim_cache 64 16384 4 131072 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



res=$(./sim_cache 64 16384 4 131072 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




echo $'\nL1=16 L2=256\n'


res=$(./sim_cache 64 16384 4 262144 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'






res=$(./sim_cache 64 16384 4 262144 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'






res=$(./sim_cache 64 16384 4 262144 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'







echo $'\nL1=16 L2=512\n'


res=$(./sim_cache 64 16384 4 524288 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'






res=$(./sim_cache 64 16384 4 524288 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




res=$(./sim_cache 64 16384 4 524288 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




echo $'\nL1=16 L2=1024\n'


res=$(./sim_cache 64 16384 4 1048576 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




res=$(./sim_cache 64 16384 4 1048576 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




res=$(./sim_cache 64 16384 4 1048576 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'

echo $'\nL1=32 L2=128\n'




res=$(./sim_cache 64 32768 4 131072 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'





res=$(./sim_cache 64 32768 4 131072 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




res=$(./sim_cache 64 32768 4 131072 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




echo $'\nL1=32 L2=256\n'



res=$(./sim_cache 64 32768 4 262144 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




res=$(./sim_cache 64 32768 4 262144 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'

res=$(./sim_cache 64 32768 4 262144 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




echo $'\nL1=32 L2=512\n'


res=$(./sim_cache 64 32768 4 524288 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'


res=$(./sim_cache 64 32768 4 524288 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'


res=$(./sim_cache 64 32768 4 524288 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'


echo $'\nL1=32 L2=1024\n'

res=$(./sim_cache 64 32768 4 1048576 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



res=$(./sim_cache 64 32768 4 1048576 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'


res=$(./sim_cache 64 32768 4 1048576 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'


echo $'L1=64 L2=128\n'

res=$(./sim_cache 64 65536 4 131072 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



res=$(./sim_cache 64 65536 4 131072 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'


res=$(./sim_cache 64 65536 4 131072 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'


echo $'L1=64 L2=256\n'

res=$(./sim_cache 64 65536 4 262144 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



res=$(./sim_cache 64 65536 4 262144 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



res=$(./sim_cache 64 65536 4 262144 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'


echo $'L1=64 L2=512\n'


res=$(./sim_cache 64 65536 4 524288 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'




res=$(./sim_cache 64 65536 4 524288 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



res=$(./sim_cache 64 65536 4 524288 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'


echo $'L1=64 L2=1024\n'


res=$(./sim_cache 64 65536 4 1048576 8 0 0 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'



res=$(./sim_cache 64 65536 4 1048576 8 0 1 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'


res=$(./sim_cache 64 65536 4 1048576 8 0 2 GCC.t | grep "read misses")
temp=$(echo $res | cut -d: -f2-)
first=$(echo $temp | cut -f 1 -d " ")
second=$(echo $temp | cut -d: -f2-)
third=$(($first+$second))
echo $third
echo $'\n'

