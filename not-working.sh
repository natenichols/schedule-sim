./simulator -c 1 -s ppri examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-ppri.out
./simulator -c 1 -s psjf examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-psjf.out

./simulator -c 1 -s ppri examples/proc2.csv > test.out && diff -u test.out examples/proc2-c1-ppri.out
./simulator -c 1 -s psjf examples/proc2.csv > test.out && diff -u test.out examples/proc2-c1-psjf.out

./simulator -c 2 -s ppri examples/proc2.csv > test.out && diff -u test.out examples/proc2-c2-ppri.out
./simulator -c 2 -s psjf examples/proc2.csv > test.out && diff -u test.out examples/proc2-c2-psjf.out

./simulator -c 1 -s ppri examples/proc3.csv > test.out && diff -u test.out examples/proc3-c1-ppri.out
./simulator -c 1 -s psjf examples/proc3.csv > test.out && diff -u test.out examples/proc3-c1-psjf.out

./simulator -c 2 -s ppri examples/proc3.csv > test.out && diff -u test.out examples/proc3-c2-ppri.out
./simulator -c 2 -s psjf examples/proc3.csv > test.out && diff -u test.out examples/proc3-c2-psjf.out

./simulator -c 4 -s ppri examples/proc3.csv > test.out && diff -u test.out examples/proc3-c4-ppri.out
./simulator -c 4 -s psjf examples/proc3.csv > test.out && diff -u test.out examples/proc3-c4-psjf.out
rm test.out