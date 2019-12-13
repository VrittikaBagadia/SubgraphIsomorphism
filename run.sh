./compile.sh
./main1 test
../minisat2.2.0/minisat/core/minisat test.satinput test.satoutput
./main2 test test.mapping

