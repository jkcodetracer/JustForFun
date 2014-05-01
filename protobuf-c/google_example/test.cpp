#include "hello.pb.h"
#include <iostream>

using namespace::std;

int main(void)
{
	helloworld msg1;

	msg1.set_id(102);	
	msg1.set_dd2(333);

	fstream output("./log", ios::out | ios::trun);

	return 0;
}

