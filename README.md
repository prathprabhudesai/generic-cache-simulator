# A Genereic Cache Simulator

This is a generic cache simulator written in c++. It supports two level of heirarchy i.e. L1 and L2 cache. Provides non-inlusive, inclusive, exclusive implementation with First In First Out and Least Recently Used replacement policies.

## Build the Simulator

<code> git clone https://github.com/prathprabhudesai/Generic_Cache_Simulator.git </code>
<br>
<code> cd Generic_Cache_Simulator </code> 
<br>
<code> make all </code>

## Run the Simulator

<code> ./sim_cache BLOCKSIZE L1_SIZE L1_ASSOC L2_SIZE L2_ASSOC REPL_POLICY INCLUSION TRACE_FILE </code>
