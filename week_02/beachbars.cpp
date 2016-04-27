#include <iostream>
#include <stdint.h>
#include <algorithm>

int main()
{
	std::ios::sync_with_stdio(false);

	int32_t parasols[10000];

	//the rightmost parasols of the best spots
	//can be max. 5000 configurations with given limits, with two spots each
	int32_t bestSpots[10000];

	uint16_t beachCount;
	std::cin >> beachCount;
	for (; beachCount > 0; --beachCount)
	{
		uint16_t parasolCount;
		std::cin >> parasolCount;
		
		for (uint16_t i = 0; i < parasolCount; ++i)
		{
			std::cin >> parasols[i];
		}

		//complexity O(nlogn) if we realy want O(n) we can use counting sort, for the given 10000 limit this is ok
		std::sort(parasols, &parasols[parasolCount]);

		uint16_t bestCount = 0;
		uint16_t l = 0;
		int16_t foundSpots = 0;
		for (uint16_t r = 0; r < parasolCount; ++r)
		{
			while (parasols[r] - parasols[l] > 201) 
			{
				++l;
			}

			uint16_t count = r - l + 1;
			if (count < bestCount)
			{
				continue;
			}

			if (count > bestCount)
			{
				foundSpots = 1;
				bestSpots[0] = r;
				bestCount = count;
				continue;
			}

			bestSpots[foundSpots++] = r;
		}

		//output max. parasols
		std::cout << bestCount-- << ' ';

		//bad naming: this is 10000 - 1 - spotCount
		uint16_t spotCount = 9999;
		uint32_t shortest = -1;
		--foundSpots;
		for (; foundSpots >= 0; --foundSpots)
		{
			int32_t spot = parasols[bestSpots[foundSpots]] + parasols[bestSpots[foundSpots] - bestCount];
			
			//can't be "%" because -2 % 2 == -1
			if(spot & 1)
			{
				--spot; //so that result of division is always floored
				spot /= 2;
				uint32_t len = parasols[bestSpots[foundSpots]] - spot;
				if (len > shortest)
				{
					continue;
				}
				if (len < shortest)
				{
					shortest = len;
					spotCount = 9997; //found 2 spots
					bestSpots[9999] = spot + 1;
					bestSpots[9998] = spot;
					continue;
				}
				bestSpots[spotCount--] = spot + 1;
				bestSpots[spotCount--] = spot;
				continue;
			}

			spot /= 2;
			uint32_t len = parasols[bestSpots[foundSpots]] - spot;
			if (len > shortest)
			{
				continue;
			}
			if (len < shortest)
			{
				shortest = len;
				spotCount = 9998; //found 1 spots
				bestSpots[9999] = spot;
				continue;
			}

			bestSpots[spotCount--] = spot;
		}

		//output shortest maximum distance
		std::cout << shortest << '\n';
		
		std::cout << bestSpots[(++spotCount)++];
		for (; spotCount < 10000; ++spotCount)
		{
			std::cout << ' ' << bestSpots[spotCount];
		}
		std::cout << '\n';
	}

    return 0;
}
