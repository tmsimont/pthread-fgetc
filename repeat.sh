#!/bin/bash

for i in `seq $1`
do
	./mr.out $2 tmp.txt
done
