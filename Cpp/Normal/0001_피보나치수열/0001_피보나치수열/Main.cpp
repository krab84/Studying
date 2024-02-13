#include <iostream>
#include "CFibonacci.h"

int main() 
{
	const int maxCnt = 50;
	{
		CFibonacci cfib;
		for (int i = 0; i < maxCnt; ++i)
		{
			std::cout << cfib.GetResult1(i) << ", ";
		}
		std::cout << "\n";
	}

	{
		CFibonacci cfib;
		for (int i = maxCnt; i >= 0; --i)
		{
			std::cout << cfib.GetResult1(i) << ", ";
		}
		std::cout << "\n";
	}

	{
		CFibonacci cfib;
		for (int i = 0; i < maxCnt; ++i)
		{
			std::cout << cfib.GetResult4(i) << ", ";
		}
		std::cout << "\n";
	}

	{
		CFibonacci cfib;
		for (int i = maxCnt; i >= 0; --i)
		{
			std::cout << cfib.GetResult4(i) << ", ";
		}
		std::cout << "\n";
	}
	return 0;
}