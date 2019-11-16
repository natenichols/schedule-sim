./simulator -c 1 -s fcfs examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c1-fcfs.out
# ./simulator -c 1 -s ppri examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c1-ppri.out
./simulator -c 1 -s pri examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c1-pri.out
# ./simulator -c 1 -s psjf examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c1-psjf.out
# ./simulator -c 1 -s rr1 examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c1-rr1.out
# ./simulator -c 1 -s rr2 examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c1-rr2.out
# ./simulator -c 1 -s rr4 examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c1-rr4.out
./simulator -c 1 -s sjf examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c1-sjf.out

./simulator -c 2 -s fcfs examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c2-fcfs.out
# ./simulator -c 2 -s ppri examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c2-ppri.out
./simulator -c 2 -s pri examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c2-pri.out
# ./simulator -c 2 -s psjf examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c2-psjf.out
# ./simulator -c 2 -s rr1 examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c2-rr1.out
# ./simulator -c 2 -s rr2 examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c2-rr2.out
# ./simulator -c 2 -s rr4 examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c2-rr4.out
./simulator -c 2 -s sjf examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c2-sjf.out

./simulator -c 4 -s fcfs examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c4-fcfs.out
# ./simulator -c 4 -s ppri examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c4-ppri.out
./simulator -c 4 -s pri examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c4-pri.out
# ./simulator -c 4 -s psjf examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c4-psjf.out
# ./simulator -c 4 -s rr1 examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c4-rr1.out
# ./simulator -c 4 -s rr2 examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c4-rr2.out
# ./simulator -c 4 -s rr4 examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c4-rr4.out
./simulator -c 4 -s sjf examples/proc1.csv > test.out ; diff -u test.out examples/proc1-c4-sjf.out

./simulator -c 1 -s fcfs examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c1-fcfs.out
# ./simulator -c 1 -s ppri examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c1-ppri.out
./simulator -c 1 -s pri examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c1-pri.out
# ./simulator -c 1 -s psjf examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c1-psjf.out
# ./simulator -c 1 -s rr1 examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c1-rr1.out
# ./simulator -c 1 -s rr2 examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c1-rr2.out
# ./simulator -c 1 -s rr4 examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c1-rr4.out
./simulator -c 1 -s sjf examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c1-sjf.out

./simulator -c 2 -s fcfs examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c2-fcfs.out
# ./simulator -c 2 -s ppri examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c2-ppri.out
./simulator -c 2 -s pri examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c2-pri.out
# ./simulator -c 2 -s psjf examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c2-psjf.out
# ./simulator -c 2 -s rr1 examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c2-rr1.out
# ./simulator -c 2 -s rr2 examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c2-rr2.out
# ./simulator -c 2 -s rr4 examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c2-rr4.out
./simulator -c 2 -s sjf examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c2-sjf.out

./simulator -c 4 -s fcfs examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c4-fcfs.out
# ./simulator -c 4 -s ppri examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c4-ppri.out
./simulator -c 4 -s pri examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c4-pri.out
# ./simulator -c 4 -s psjf examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c4-psjf.out
# ./simulator -c 4 -s rr1 examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c4-rr1.out
# ./simulator -c 4 -s rr2 examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c4-rr2.out
# ./simulator -c 4 -s rr4 examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c4-rr4.out
./simulator -c 4 -s sjf examples/proc2.csv > test.out ; diff -u test.out examples/proc2-c4-sjf.out

./simulator -c 1 -s fcfs examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c1-fcfs.out
# ./simulator -c 1 -s ppri examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c1-ppri.out
./simulator -c 1 -s pri examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c1-pri.out
# ./simulator -c 1 -s psjf examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c1-psjf.out
# ./simulator -c 1 -s rr1 examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c1-rr1.out
# ./simulator -c 1 -s rr2 examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c1-rr2.out
# ./simulator -c 1 -s rr4 examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c1-rr4.out
./simulator -c 1 -s sjf examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c1-sjf.out

./simulator -c 2 -s fcfs examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c2-fcfs.out
# ./simulator -c 2 -s ppri examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c2-ppri.out
./simulator -c 2 -s pri examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c2-pri.out
# ./simulator -c 2 -s psjf examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c2-psjf.out
# ./simulator -c 2 -s rr1 examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c2-rr1.out
# ./simulator -c 2 -s rr2 examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c2-rr2.out
# ./simulator -c 2 -s rr4 examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c2-rr4.out
./simulator -c 2 -s sjf examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c2-sjf.out

./simulator -c 4 -s fcfs examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c4-fcfs.out
# ./simulator -c 4 -s ppri examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c4-ppri.out
./simulator -c 4 -s pri examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c4-pri.out
# ./simulator -c 4 -s psjf examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c4-psjf.out
# ./simulator -c 4 -s rr1 examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c4-rr1.out
# ./simulator -c 4 -s rr2 examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c4-rr2.out
# ./simulator -c 4 -s rr4 examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c4-rr4.out
./simulator -c 4 -s sjf examples/proc3.csv > test.out ; diff -u test.out examples/proc3-c4-sjf.out


rm test.out