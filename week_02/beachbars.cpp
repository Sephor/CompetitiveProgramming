#include <iostream>
#include <stdint.h>
#include <algorithm>

#define MAXPARASOLS 10000
#define MAXSPOTS 20000

int main()
{
	std::ios::sync_with_stdio(false);

	int32_t parasols[MAXPARASOLS];

	//the rightmost parasols of the best spots
	uint16_t bestRight[MAXPARASOLS];
	int32_t bestSpots[MAXSPOTS];

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
		uint16_t foundSpots = 0;
		for (uint16_t r = 0; r < parasolCount; ++r)
		{
			while (parasols[r] - parasols[l] > 200) 
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
				bestRight[0] = r;
				bestCount = count;
				continue;
			}

			bestRight[foundSpots++] = r;
		}

		//output max. parasols
		std::cout << bestCount-- << ' ';

		uint16_t spotCount = 0;
		uint32_t shortest = -1;
		for (uint16_t i = 0; i < foundSpots; ++i)
		{
			int32_t spot = parasols[bestRight[i]] + parasols[bestRight[i] - bestCount];
			
			//can't be "%" because -2 % 2 == -1
			if(spot & 1)
			{
				--spot; //so that result of division is always floored
				spot /= 2;
				uint32_t len = parasols[bestRight[i]] - spot;
				if (len > shortest)
				{
					continue;
				}
				if (len < shortest)
				{
					shortest = len;
					spotCount = 2;
					bestSpots[0] = spot;
					bestSpots[1] = spot + 1;
					continue;
				}
				bestSpots[spotCount++] = spot;
				bestSpots[spotCount++] = spot + 1;
				continue;
			}

			spot /= 2;
			uint32_t len = parasols[bestRight[i]] - spot;
			if (len > shortest)
			{
				continue;
			}
			if (len < shortest)
			{
				shortest = len;
				spotCount = 1;
				bestSpots[0] = spot;
				continue;
			}

			bestSpots[spotCount++] = spot;
		}

		//output shortest maximum distance
		std::cout << shortest << '\n';
		
		std::cout << bestSpots[0];
		for (uint16_t i = 1; i < spotCount; ++i)
		{
			std::cout << ' ' << bestSpots[i];
		}
		std::cout << std::endl;
	}

    return 0;
}
