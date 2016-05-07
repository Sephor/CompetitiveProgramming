#include <iostream>
#include <stdint.h>

#define MAXCOINS 100000
#define MINLEN 2

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

void selectSort(SubSeries& sub, uint64_t& counter)
{
	for (uint32_t i = sub.left; i < sub.left + sub.length; ++i)
	{
		uint32_t number = numbers[sub.isBottom][i];
		uint32_t j = i;
		while (j > sub.left && number > numbers[sub.isBottom][j - 1])
		{
			numbers[sub.isBottom][j] = numbers[sub.isBottom][j - 1];
			--j;
			++counter;
		}
		numbers[sub.isBottom][j] = number;
	}
}

void merge(SubSeries& left, SubSeries& right, uint64_t& counter)
{
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

void cleanStack(uint32_t& stackSize, uint64_t& counter)
{
	SubSeries* left = &workStack[stackSize - 2];
	SubSeries* right = &workStack[stackSize - 1];
	while (stackSize > 1 && right->length >= left->length)
	{
		left = &workStack[stackSize - 2];
		right = &workStack[stackSize - 1];
		merge(*left, *right, counter);
		--stackSize;
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
		uint32_t stackSize = 0;

		uint32_t sortedEnd = 0;
		while (sortedEnd < numberCount)
		{
			workStack[stackSize] = SubSeries(1, sortedEnd, true);
			SubSeries& nextSeries = workStack[stackSize];
			++stackSize;
			++sortedEnd;
			while (nextSeries.length < MINLEN && sortedEnd < numberCount)
			{
				++nextSeries.length;
				++sortedEnd;
			}
			selectSort(nextSeries, counter);
			cleanStack(stackSize, counter);
		}

		while (stackSize > 1)
		{
			SubSeries& left = workStack[stackSize - 2];
			SubSeries& right = workStack[stackSize - 1];
			merge(left, right, counter);
			--stackSize;
		}

		std::cout << counter << '\n';
	}

    return 0;
}
