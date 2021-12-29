#!/bin/sh

for i in {10000..250000..10000}; do
  VEC1=$(python generate-vectors.py $i)
  VEC2=$(python generate-vectors.py $i)
  echo "$VEC1" > vector.txt
  echo "$VEC2" >> vector.txt
  BENCH=$(hyperfine "run < vector.txt" | grep -Po "([\\d\\.]+)\\s+[m]?s ±" | head -c-7)
  echo "$i,$BENCH" >> result-problem-2.csv
done
