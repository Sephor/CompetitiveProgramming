#include <iostream>

int main()
{
	std::ios::sync_with_stdio(false);
	unsigned long count;
	std::cin >> count;

	unsigned long n;
	unsigned long h;
	unsigned long h2;
	unsigned long h3;
	unsigned long hc;
	unsigned long hc2;
	unsigned long hc3;

	for (; count > 0; --count)
	{
		std::cin >> n;
		n -= 2;
		h = n / 2;
		h2 = h * h;
		h3 = h2 * h;
		hc = h + (n & 1) - 1;
		hc2 = hc * hc;
		hc3 = hc2 * hc;

		std::cout << (2 * h3 + 3 * h2 + h + 2 * hc3 + 6 * hc2 + 4 * hc) / 6 << std::endl;
	}

    return 0;
}
