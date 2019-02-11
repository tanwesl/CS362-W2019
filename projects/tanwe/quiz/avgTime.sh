#!/bin/bash

i="0"
timeSum="0"

while [ $i -lt 10 ]
do
	timeDeltaLo=$(date +"%s%N")
	./testme
	timeDeltaHi=$(date +"%s%N")
	timeSum=$[$timeSum + $timeDeltaHi - $timeDeltaLo]
	i=$[$i + 1]
done
timeAvg=$[$timeSum/600000000000]
echo "Avg Exec Time: $timeAvg"
