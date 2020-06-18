#include <iostream>
#include "hemu.h"
//#include <vector>

int main()
{
	hemu::Tensor<int> a({ 2,3 });
	a = { 1,2,3,4,5,6 };
	auto b = a.at({ 1,1 });
	std::cout << b << std::endl;
	auto d(a);
	d.at({ 1,1 }) = 7;
	std::cout << d.at({ 1,1 });
	return 0;
}
