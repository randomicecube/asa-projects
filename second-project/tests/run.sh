#!/bin/sh

echo > myout; for t in {0..1000}; do ../src/a.out < $t.in >> myout; done; diff myout out