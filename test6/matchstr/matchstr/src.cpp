#include<iostream>
using namespace std;
class Solution {
public:
	/*
	* @param source: source string to be scanned.
	* @param target: target string containing the sequence of characters to match
	* @return: a index to the first occurrence of target in source, or -1  if target is not part of source.
	*/
	public int strStr(const char *source, const char *target) {
		// write your code here
		if (source == NULL || target == NULL)
			return -1;
		if (strlen(target) == 0)
			return 0;
		for (int i = 0; i < int(strlen(source) - strlen(target) + 1); i++) {
			if (target[0] == source[i])
			{
				int flag = 1;

				for (int j = 0; j < strlen(target); j++) {
					if (source[i + j] != target[j])
					{
						flag = 0;
						break;
					}

				}
				if (flag)
				{
					return i;
				}
			}

		}
		return -1;
	}
};
