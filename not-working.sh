./simulator -c 1 -s ppri examples/proc1.csv > test.out && diff -u test.out examples/proc1-c1-ppri.out
rm test.out