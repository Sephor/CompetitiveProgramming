#include <iostream>
#include <stdint.h>



int main()
{
	std::ios::sync_with_stdio(false);


	uint32_t pointCount;
	std::cin >> pointCount;

	uint32_t prevPoint;
	uint32_t point;
	bool falling = false;
	std::cin >> prevPoint;
	uint32_t firstPoint = prevPoint;
	for (; pointCount > 0; --pointCount)
	{
		std::cin >> point;
		if (point < prevPoint)
		{
			falling = true;
		}

		if (falling && point > prevPoint)
		{
			std::cout << prevPoint;
			return 0;
		}
		prevPoint = point;
	}

	std::cout << (point > firstPoint) ? firstPoint : point;


    return 0;
}
