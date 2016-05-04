#include <iostream>
#include <stdint.h>

#define MAXPOINTS 800000
#define DIGITS 8 //including newlines
#define MAXCHARS MAXPOINTS * DIGITS + 1
#define CHARSIZE 1

//max number of character in the input stream
char points[MAXCHARS + 2 * DIGITS];

void output(uint32_t start, uint32_t end)
{
	for (; start <= end; ++start)
	{
		std::cout << points[start];
	}
}

bool lessThan(uint32_t startA, uint32_t endA, uint32_t startB, uint32_t endB)
{
	if (endA - startA < endB - startB)
	{
		return true;
	}
	if (endA - startA > endB - startB)
	{
		return false;
	}
	for (; startA < endA; ++startA)
	{
		if (points[startA] == points[startB])
		{
			++startB;
			continue;
		}
		return points[startA] < points[startB];
	}
	return false;
}

int main()
{
	uint32_t count;
	std::cin >> count;
	uint32_t len = fread(points + DIGITS, CHARSIZE, count * DIGITS + 1, stdin);
	uint32_t l = DIGITS;
	uint32_t r = DIGITS + len - 1;

	//copy the rightmost and leftmost number to the opposing ends
	uint32_t copyL = l - 1;
	uint32_t copyR = r + 1;
	for (uint32_t i = 0; i < DIGITS; ++i)
	{
		points[copyL] = points[r - i - 1];
		points[copyR] = points[l + i + 1];
		--copyL;
		++copyR;
	}

	while (true) 
	{
		//Find the delimiters of the middle number
		uint32_t midStart = (l + r) / 2;
		uint32_t midEnd = midStart + 1; //careful!
		while (points[midStart] != '\n')
		{
			--midStart;
		}
		while (points[midEnd] != '\n')
		{
			++midEnd;
		}

		//Check whether there's only one Element left
		if (midStart == l && midEnd == r)
		{
			output(++midStart, midEnd);
			return 0;
		}

		//Find the delimiters of the neighbours of the middle number
		uint32_t midStartL = midStart - 1;
		while (points[midStartL] != '\n')
		{
			--midStartL;
		}
		uint32_t midEndR = midEnd + 1;
		while (points[midEndR] != '\n') 
		{
			++midEndR;
		}
		
		//Compare the middle to it's neighbours
		bool midLessThanLeft = lessThan(midStart, midEnd, midStartL, midStart);
		bool midLessThanRight = lessThan(midStart, midEnd, midEnd, midEndR);
		if (midLessThanLeft && midLessThanRight)
		{
			output(++midStart, midEnd);
			return 0;
		}

		//Compare the neighbours to eachother
		bool leftLEQRight;
		if (midLessThanLeft != midLessThanRight)
		{
			//(m < l != m < r) =>  (l <= m < r) || (l > m >= r)
			//1. => (m < l) => (l > m >= r) => (l > r) => !( l <= r)
			//2. => !(m < l) => (m >= l) => (l <= m < r) => (l <= r)
			leftLEQRight = !midLessThanLeft;
		}
		else
		{
			leftLEQRight = !lessThan(midStartL, midStart, midEnd, midEndR);
		}

		if (leftLEQRight)
		{
			r = midStart;
			if (r == DIGITS)
			{
				output(++midStartL, midStart);
				return 0;
			}
		}
		else
		{
			l = midEnd;
			if (l == len + DIGITS - 1)
			{
				output(++midEnd, midEndR);
				return 0;
			}
		}
	}


    return 0;
}
