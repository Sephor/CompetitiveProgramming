#include <iostream>
#include <string>

int main()
{
	std::ios::sync_with_stdio(false);

			   //123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ
	char* map = "1SE Z  8        A   3  HIL JM O   2TUVWXY5";
	map -= 49;
	std::string messages[] = {
		" -- is not a palindrome.\n",
		" -- is a mirrored string.\n",
		" -- is a regular palindrome.\n",
		" -- is a mirrored palindrome.\n",
	};

	int count;
	std::cin >> count;

	char palindrome;
	char mirror;

	for (; count > 0; --count)
	{
		std::string input;
		std::cin >> input;
		int r = input.length();
		int half = input.length() / 2;
		mirror = r & 1 ? map[input[half]] == input[half] : 1;
		palindrome = 1;

		for (int l = 0; l < half; ++l)
		{
			--r;
			palindrome &= input[l] == input[r];
			mirror &= map[input[l]] == input[r];

			if (!palindrome && !mirror)
			{
				break;
			}
		}
		mirror |= (palindrome << 1);
		std::cout << input << messages[mirror];
	}

    return 0;
}
