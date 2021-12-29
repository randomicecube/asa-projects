#!/bin/sh

for i in {1000000..10000000..100000}; do
  python generate-vectors.py $i > vector.txt
  BENCH=$(hyperfine "run < vector.txt" --warmup 10 | grep -Po "([\\d\\.]+)\\s+[m]?s ±" | head -c-7)
  echo "$i,$BENCH" >> result-problem-1.csv
done
