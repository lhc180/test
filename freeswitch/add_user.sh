#!/bin/bash
for i in `seq $1 $2`; do sed -e "s/1000/$i/" 1000.xml > $i.xml ; done
