/*Manacher's algorithm is used to find the longest palindrome in a string in O(n) time.
 @author Anna Hwang
 @github hwangas
 @date Feb 12, 2015
*/

#include <iostream>
#include <string>

int findPalLength(std::string T, int cur);
std::string extractPal(std::string s);
std::string preprocess(std::string &T);

int main()
{
	std::cout << "Enter your string: ";

	std::string input;
	std::getline(std::cin, input);
	
	std::string T = preprocess(input);

	int largestIndex = 0;
	int P[256];

	int cur = 0;
	while (cur < T.length())
	{
		int palLength = findPalLength(T, cur);
		P[cur] = palLength;

		if (P[cur] >= P[largestIndex]) {
			largestIndex = cur;
		}

		if (palLength > 1)
		{
			int center = cur;
			int endOfPal = center + palLength;

			for (cur += 1; cur <= endOfPal; ++cur)
			{
				int mirror = P[2 * center - cur];
				if (endOfPal - cur < mirror) {
					break;
				}
				P[cur] = mirror;
			}

			--cur;
		}

		++cur;
	}

	std::string ans = extractPal(T.substr(largestIndex - P[largestIndex], 2*P[largestIndex]));
	std::cout << "Longest palindrome: " << ans.c_str() << std::endl;
	std::cin.get();

	return 0;
}

std::string extractPal(std::string s)
{
	std::string ans;
	for (int i = 0; i < s.length(); ++i)
	{
		if (s[i] != '#')
			ans += s[i];
	}

	return ans;
}

int findPalLength(std::string T, int cur)
{
	int length = 0;
	while (cur - length > 0 && cur + length < T.length() && T[cur - length - 1] == T[cur + length + 1]) {
		++length;
	}

	return length;
}

std::string preprocess(std::string &str)
{
	std::string T = "^#";
	for (int i = 0; i < str.length(); ++i) {
		T = T + str[i] + "#";
	}

	T += "$";
	return T;
}