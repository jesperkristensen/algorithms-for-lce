# http://www.majorgeeks.com/CPU-Z_d425.html
# http://www.cpuid.com/softwares/cpu-z/versions-history.html
# Caches: L1 D: 32KB,8-way,64B lines ; L1 I: 32KB,8-way,64B lines ; L2: 3072KB,12-way,64B lines
CXXFLAGS="-DCACHE_ALLA=1" make main -s
../valgrind/valgrind-3.6.1/vg-in-place --tool=cachegrind --D1=32768,8,64 --I1=32768,8,64 --LL=3145728,12,64 --cachegrind-out-file=cachegrind-alla.out main.exe > cachegrind-alla.txt 2> cachegrind-alla-err.txt
#../valgrind/valgrind-3.6.1/vg-in-place --tool=cachegrind --D1=32768,8,64 --I1=32768,8,64 --LL=1073741824,262144,4096 --cachegrind-out-file=cachegrind-swap-alla.out main.exe > cachegrind-swap-alla.txt 2> cachegrind-swap-alla-err.txt
CXXFLAGS="-DCACHE_RAND10=1" make main -s
../valgrind/valgrind-3.6.1/vg-in-place --tool=cachegrind --D1=32768,8,64 --I1=32768,8,64 --LL=3145728,12,64 --cachegrind-out-file=cachegrind-rand10.out main.exe > cachegrind-rand10.txt 2> cachegrind-rand10-err.txt
#../valgrind/valgrind-3.6.1/vg-in-place --tool=cachegrind --D1=32768,8,64 --I1=32768,8,64 --LL=1073741824,262144,4096 --cachegrind-out-file=cachegrind-swap-rand10.out main.exe > cachegrind-swap-rand10.txt 2> cachegrind-swap-rand10-err.txt
../valgrind/valgrind-3.6.1/cachegrind/cg_annotate cachegrind-alla.out --auto=yes > cachegrind-alla-annotate.txt
../valgrind/valgrind-3.6.1/cachegrind/cg_annotate cachegrind-rand10.out --auto=yes > cachegrind-rand10-annotate.txt
#../valgrind/valgrind-3.6.1/cachegrind/cg_annotate cachegrind-swap-alla.out --auto=yes > cachegrind-swap-alla-annotate.txt
#../valgrind/valgrind-3.6.1/cachegrind/cg_annotate cachegrind-swap-rand10.out --auto=yes > cachegrind-swap-rand10-annotate.txt
