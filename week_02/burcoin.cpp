#include <iostream>
#include <stdint.h>

#define COUNTER uint32_t
#define MAXCOINS 1000

COUNTER player1[MAXCOINS][MAXCOINS];
COUNTER player2[MAXCOINS][MAXCOINS];

int main()
{
	std::ios::sync_with_stdio(false);

	uint16_t cases;
	std::cin >> cases;

	for (; cases > 0; --cases)
	{
		uint16_t coinCount;
		std::cin >> coinCount;

		for (uint16_t i = 0; i < coinCount; ++i)
		{
			std::cin >> player1[i][0];
			player2[i][0] = 0;
		}

		for (uint16_t j = 1; j < coinCount; ++j)
		{
			for (uint16_t i = 0; i < coinCount - j; ++i)
			{
				COUNTER right = player1[i + j][0] + player2[i][j - 1];
				COUNTER left = player1[i][0] + player2[i + 1][j - 1];
				player1[i][j] = left > right ? left : right;
				player2[i][j] = left > right ? player1[i + 1][j - 1] : player1[i][j - 1];
			}
		}

		std::cout << player1[0][coinCount - 1] << std::endl;
	}

    return 0;
}
