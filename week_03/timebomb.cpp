#include <iostream>
#include <stdint.h>

#define MAXCOINS 100000

struct SubSeries
{
	SubSeries() {};

	SubSeries(uint32_t len, uint32_t l, bool bottom)
		: length(len)
		, left(l)
		, isBottom(bottom)
	{}

	uint32_t length;
	uint32_t left;
	bool isBottom;
};

uint32_t numbers[2][MAXCOINS];
SubSeries workStack[MAXCOINS];

void merge(uint32_t& stackPointer, uint64_t& counter)
{
	SubSeries& right = workStack[stackPointer--];
	SubSeries& left = workStack[stackPointer];

	if (right.isBottom != left.isBottom) 
	{
		for (uint32_t j = right.left; j < right.left + right.length; ++j)
		{
			numbers[left.isBottom][j] = numbers[right.isBottom][j];
		}
	}

	uint32_t l = 0;
	uint32_t r = 0;
	
	while (l < left.length && r < right.length)
	{
		uint32_t leftNumber = numbers[left.isBottom][left.left + l];
		uint32_t rightNumber = numbers[left.isBottom][right.left + r];
		if (leftNumber >= rightNumber)
		{
			numbers[!left.isBottom][left.left + l + r] = leftNumber;
			++l;
		}
		else
		{
			numbers[!left.isBottom][left.left + l + r] = rightNumber;
			counter += left.length - l;
			++r;
		}
	}
	while (l < left.length)
	{
		numbers[!left.isBottom][left.left + l + r] = numbers[left.isBottom][left.left + l];
		++l;
	}
	while (r < right.length)
	{
		numbers[!left.isBottom][left.left + l + r] = numbers[left.isBottom][right.left + r];
		++r;
	}

	left = SubSeries(left.length + right.length, left.left, !left.isBottom);
}

void cleanStack(uint32_t& stackPointer, uint64_t& counter)
{
	while (stackPointer > 0 && workStack[stackPointer].length >= workStack[stackPointer - 1].length)
	{
		merge(stackPointer, counter);
	}
}

int main()
{
	std::ios::sync_with_stdio(false);

	uint32_t cases;
	std::cin >> cases;

	for (; cases > 0; --cases)
	{
		uint32_t numberCount;
		std::cin >> numberCount;

		for (uint32_t i = 0; i < numberCount; ++i)
		{
			std::cin >> numbers[1][i];
		}

		uint64_t counter = 0;
		uint32_t stackPointer = 0;
		workStack[0] = SubSeries(1, 0, true);

		for (uint32_t i = 1; i < numberCount; ++i)
		{
			workStack[++stackPointer] = SubSeries(1, i, true);
			cleanStack(stackPointer, counter);
		}

		while (stackPointer > 0)
		{
			merge(stackPointer, counter);
		}

		std::cout << counter << '\n';
	}

    return 0;
}
