# http://valgrind.org/docs/manual/dist.readme-developers.html
cd ~/thesis/valgrind
tar -xjf valgrind-3.6.1.tar.bz2
cd valgrind-3.6.1
patch < ../../src/valgrind.diff
./configure
make
# cd ~/thesis/src
# ../valgrind/valgrind-3.6.1/vg-in-place --tool=cachegrind --LL=<size>,<assoc>,<linesize> main.exe
