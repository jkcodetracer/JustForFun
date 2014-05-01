#!/bin/sh

if [ $# -lt 3 ]
then 
	echo "report.sh [srcfile] [dstfile] [bin name]"
	exit 1
fi

LD_PRELOAD="/usr/sbin/"

gcov "${3}"

lcov -c -d "${1}" -o srcfile.info
genhtml -o "${2}" srcfile.info
rm srcfile.info


