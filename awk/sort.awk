#!/bin/awk
BEGIN {
	FS="\n"
	RS=""
}
{
	while(++i <= NF)
		data[i] = $(i);
	
	for(t = 1; t <= NF; t++)
		printf("%s ", data[t]);
	printf("----\n");
}
END {
	qsort(data, 1, NF);
	reduce(data, NF, output);

	for(i = 1; i <= NF; i++)
		printf("%s \n", output[i]);
}
function reduce(data, size, output)
{
	j = 1;
	current=data[1];
	for(i = 1; i <= NF; i++)	
	{
		split(current, curarr, ":");
		split(data[i], dataarr, ":");

		if(dataarr[2] != curarr[2]){
			output[j++] = current;	
			current = data[i];
		} else if(dataarr[1] > currarr[i]){
			current = data[i];	
		}
	}
}

function qsort(arr, low, high)
{
	last = low;
	j = low;

	if(low >= high)
		return;
	split(arr[low], arrlow, ":");	
	while(j <= high)
	{
		split(arr[j], arrj, ":");
		if(arrj[2] < arrlow[2])	
		{
			last++;
			tmp = arr[j] ;	
			arr[j] = arr[last];
			arr[last] = tmp;
		}
		j++;
	}

	tmp = arr[low] ;	
	arr[low] = arr[last];
	arr[last] = tmp;
	
	qsort(arr, low, last-1);
	qsort(arr, last+1, high);
}

