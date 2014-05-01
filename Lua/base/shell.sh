#!/bin/sh
# 不支持数组

a=(123 123 551 23 adf 123)

a[0]=123
a[1]=1sdf
a[2]=12344

i=0

while [ ${i} -gt 5 ]
do
	echo $a[${i}]
	let i=$i+1
done

