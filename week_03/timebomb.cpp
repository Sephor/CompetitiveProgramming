#include <iostream>
#include <stdint.h>

#define COUNTER uint32_t
#define MAXCOINS 10

int main()
{
	std::ios::sync_with_stdio(false);

	uint16_t cases;
	std::cin >> cases;

	COUNTER coins[MAXCOINS];

	COUNTER player1[2][MAXCOINS];
	COUNTER player2[2][MAXCOINS];

	bool flip = false;

	for (; cases > 0; --cases)
	{
		uint16_t coinCount;
		std::cin >> coinCount;

		for (uint16_t i = 0; i < coinCount; ++i)
		{
			std::cin >> coins[i];
			player1[flip][i] = coins[i];
			player2[flip][i] = 0;
		}

		for (uint16_t j = 1; j < coinCount; ++j)
		{
			flip = !flip; //flop!
			for (uint16_t i = 0; i < coinCount - j; ++i)
			{
				COUNTER right = coins[i + j] + player2[!flip][i];
				COUNTER left = coins[i] + player2[!flip][i + 1];
				player1[flip][i] = left > right ? left : right;
				player2[flip][i] = left > right ? player1[!flip][i + 1] : player1[!flip][i];
			}
		}

		std::cout << player1[flip][0] << std::endl;
	}

    return 0;
}
