/**
 * \file map.cpp
 * \author  wzj
 * \brief test map...
 * \version 
 * \note  
 * \date: 2012年08月12日星期日15:39:53
 */ 
#include <map>
#include <stdio.h>

using namespace std;

int main()
{
	int i = 0;
	map<int, int> tmap;
	map<int, int>::iterator pmap;
	tmap.insert(make_pair(5,2));

	for(i = 0; i < 100; ++i)
	{
		tmap.insert(make_pair(i,i+1));
	}

	pmap = tmap.begin();

	for(i = 0;pmap != tmap.end(); pmap++)
	{
		if(pmap->second == 2)
		{
			tmap.erase(pmap);
		}
	}

	while(pmap != tmap.end())
	{
		tmap.erase(pmap++);
	}
	printf("odd num:%d\n", i);
	return 0;
}
