./simulator -c 1 -s fcfs examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-fcfs.out
./simulator -c 1 -s pri examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-pri.out

rm test.out