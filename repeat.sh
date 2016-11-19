#!/bin/bash

echo -e "Total time\tCPU Time"
for i in `seq $1`
do
	rm tmp.txt
	./mr.out $2 tmp.txt
done
