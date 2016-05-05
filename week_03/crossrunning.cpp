#include <iostream>
#include <stdint.h>
#include <cstring>

#define MAXPOINTS 800000
#define DIGITS 8 //including newlines
#define MAXCHARS MAXPOINTS * DIGITS + 1
#define CHARSIZE 1

//an array to hold all characters from the input stream
char points[MAXCHARS + MAXCHARS / 3 +  10 * DIGITS];

//A struct to deal with unparsed numbers in the points array
//overrides <,>,<=,>=,==,++ operators for convenience
struct Number
{
	//default constructor
	Number() {}

	//Constructs a Number from a starting index. This will seek for the surrounding newline characters.
	Number(uint32_t start)
	{
		left = start;
		right = start + 1;
		while (points[left] != '\n')
		{
			--left;
		}
		while (points[right] != '\n')
		{
			++right;
		}
	}

	//copy constructor
	Number(const Number& other)
		: left(other.left)
		, right(other.right)
	{
	}

	bool operator<(const Number& other) const
	{
		if (right - left < other.right - other.left)
		{
			return true;
		}
		if (right - left > other.right - other.left)
		{
			return false;
		}
		uint32_t j = other.left + 1;
		for (uint32_t i = left + 1; i < right; ++i)
		{
			if (points[i] == points[j])
			{
				++j;
				continue;
			}
			return points[i] < points[j];
		}
		return false;
	}

	bool operator==(const Number& other) const
	{
		if (right - left != other.right - other.left)
		{
			return false;
		}
		uint32_t j = other.left + 1;
		for (uint32_t i = left + 1; i < right; ++i)
		{
			if (points[i] != points[j])
			{
				return false;
			}
			++j;
		}
		return true;
	}

	bool operator>=(const Number& other) const
	{
		return other.operator<(*this) || operator==(other);
	}

	bool operator<=(const Number& other) const
	{
		return operator<(other) || operator==(other);
	}

	bool operator>(const Number& other) const
	{
		return other.operator<(*this);
	}

	void operator++()
	{
		Number temp(right);
		left = temp.left;
		right = temp.right;
	}

	uint32_t left;
	uint32_t right;
};

//prints value. This makes value unusable
void output(Number& value)
{
	++value.left;
	for (; value.left <= value.right; ++value.left)
	{
		std::cout << points[value.left];
	}
}

int main()
{
	uint32_t count;
	std::cin >> count;
	
	uint32_t len = fread(points, CHARSIZE, count * DIGITS + 1, stdin);
	uint32_t start = 0;
	uint32_t end = len - 1; //the rightmost \n

	if (count == 1)
	{
		Number x(start);
		output(x);
		return 0;
	}

	Number m0(start);
	Number m1(m0.right + (end - m0.right) / 3);

	if (count == 2)
	{
		if (m1 < m0)
		{
			output(m1);
			return 0;
		}
		output(m0);
		return 0;
	}

	Number m2((m1.right + end) / 2);

	if (count == 3)
	{
		if (m0 < m1 && m0 < m2)
		{
			output(m0);
			return 0;
		}
		if (m1 < m2 && m1 < m0)
		{
			output(m1);
			return 0;
		}
		output(m2);
		return 0;
	}

	//extend to the right, so that m1 can be found to the right of m2
	std::memcpy(points + len, points + 1, m1.right);

	Number l;
	Number m;
	Number r;
	
	while (true)
	{
		if (m1 < m0 && m1 < m2)
		{
			l = m0;
			m = m1;
			r = m2;
			break;
		}
		if (m0 < m1 && m0 < m2)
		{
			l = m2;
			m = Number(end);
			r = Number(end + m1.left);
			break;
		}
		if (m2 < m0 && m2 < m1)
		{
			l = m1;
			m = m2;
			r = Number(end);
			break;
		}
		if (m0 == m1 || m1 == m2)
		{
			++m1; //what if m1 is m2?
			continue;
		}
		++m0; //what id m0 is m1?
	}

	while (true)
	{
		bool goLeft = (m.left - l.right > r.left - m.right);
		uint32_t spot = goLeft ? (m.left + l.right) / 2 : (r.left + m.right) / 2;
		Number seeker(spot);

		if (seeker < m)
		{
			if (goLeft)
			{
				r = m;
				m = seeker;
			}
			else
			{
				l = m;
				m = seeker;
			}
		}
		else
		{
			if (goLeft)
			{
				l = seeker;
			}
			else
			{
				r = seeker;
			}
		}

		if (l.right == m.left && m.right == r.left)
		{
			output(m);
			return 0;
		}
	}

    return 0;
}
