#!/bin/sh

touch diffs.txt

for i in {1..100..1}; do
  echo "Running test $i" >> diffs.txt
  VEC=$(python generate-vectors.py $i)
  echo "$VEC" > vector.txt
  GASPA=$(./a.out < vector.txt) # usa o executavel que te mandei
  RAFA=$(./<vosso exe> < vector.txt) # usa o executavel que te mandei
  if [ "$GASPA" != "$RAFA" ]; then
    echo "Test $i failed" >> diffs.txt
    echo "GASPA: $GASPA" >> diffs.txt
    echo "RAFA: $RAFA" >> diffs.txt
    echo "VECTOR: $VEC" >> diffs.txt
  fi
  echo "---" >> diffs.txt
done