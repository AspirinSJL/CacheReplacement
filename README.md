CacheReplacement
================
  This small project simulates how cache works with different replacement polices.
  In addition, block matrix multiplication can exploit the cache to improve cache hit rate.
  
  
Contents
----------------
  1. policies.cpp & polices.h: implement 4 polices which are FIFO, LIFO, LRU, OPT
  2. generate.cpp: generate memory accesses sequence
  3. main.cpp: test the policies
  4. in.txt: data for test2
  5. Makefile: GNU version
  6. REPORT OF CS3230 PJ1 TASKA(&BC): description & analysis of the implementation
  7. blockMatrixMultiplication.cpp: optimize matrix multiplication considering cache
     (this one is a seperate file)


###input
    for test1
    1. tc: test count
    2. s: cache size
    3. n: memory size
    4. m: number of memory accesses
    5. entries: memory accesses sequence
    
    for test2
    1. tc: test count
    2. s: cache size
    3. p, x, q: matrix size of A and B

###output
    cache misses for each policy
