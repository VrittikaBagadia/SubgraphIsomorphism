time ./compile.sh
time ./main1 test
time ../minisat2.2.0/minisat/core/minisat test.satinput test.satoutput
time ./main2 test test.mapping
