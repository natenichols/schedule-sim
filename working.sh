./simulator -c 1 -s fcfs examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-fcfs.out
# ./simulator -c 1 -s ppri examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-ppri.out
./simulator -c 1 -s pri examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-pri.out
# ./simulator -c 1 -s psjf examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-psjf.out
./simulator -c 1 -s rr1 examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-rr1.out
./simulator -c 1 -s rr2 examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-rr2.out
./simulator -c 1 -s rr4 examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-rr4.out
./simulator -c 1 -s sjf examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-sjf.out

rm test.out