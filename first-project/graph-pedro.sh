#!/bin/sh

echo "n,time" > results.csv

for i in {100..1000..100}; do
  python generate-vectors.py $i > vector.txt
  BENCH=$(hyperfine "run < vector.txt" | grep -Po "([\\d\\.]+)\\s+[m]?s ±" | head -c-7)
  echo "$i,$BENCH" >> results.csv
done
