#include <iostream>
#include "hemu.h"
//#include <vector>

int main()
{
	hemu::Tensor<int,2> a({ 2,3 });
	a = { 1,2,3,4,5,6 };
	return 0;
}