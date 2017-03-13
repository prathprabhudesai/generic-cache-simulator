./sim_cache 64 16384 4 131072 1 0 0 GCC.t | grep "miss rate"
echo $'\n'
./sim_cache 64 16384 4 131072 2 0 0 GCC.t | grep "miss rate"
echo $'\n'
./sim_cache 64 16384 4 131072 4 0 0 GCC.t | grep "miss rate"
echo $'\n'
./sim_cache 64 16384 4 131072 8 0 0 GCC.t | grep "miss rate"
echo $'\n'

./sim_cache 64 16384 4 131072 1 0 0 MCF.t | grep "miss rate"
echo $'\n'
./sim_cache 64 16384 4 131072 2 0 0 MCF.t | grep "miss rate"
echo $'\n'
./sim_cache 64 16384 4 131072 4 0 0 MCF.t | grep "miss rate"
echo $'\n'
./sim_cache 64 16384 4 131072 8 0 0 MCF.t | grep "miss rate"
echo $'\n'


./sim_cache 64 16384 4 131072 1 0 0 LBM.t | grep "miss rate"
echo $'\n'
./sim_cache 64 16384 4 131072 2 0 0 LBM.t | grep "miss rate"
echo $'\n'
./sim_cache 64 16384 4 131072 4 0 0 LBM.t | grep "miss rate"
echo $'\n'
./sim_cache 64 16384 4 131072 8 0 0 LBM.t | grep "miss rate"
echo $'\n'

