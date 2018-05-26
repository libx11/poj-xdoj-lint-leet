#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	/**
	* @param A: an integer sorted array
	* @param target: an integer to be inserted
	* @return: An integer
	*/
	int searchInsert(vector<int> &A, int target) {
		// write your code here
		int lo = 0;
		int hi = A.size() - 1;
		int mid = (lo + hi) / 2;
		if (A.size() == 0)
			return 0;
		while (1)
		{

			if (A[mid] == target)
				return mid;
			else if (A[mid] < target && hi - lo > 1)
			{
				lo = mid;
				mid = (lo + hi) / 2;
			}
			else if (A[mid] > target && hi - lo > 1)
			{
				hi = mid;
				mid = (lo + hi) / 2;
			}

			else if (A[hi] < target)
				return hi + 1;
			else if (A[lo] < target)
				return hi;
			else if (A[lo] > target)
				return lo;
		}
	}
};

int main()
{
	Solution s;
	vector<int> v(4);
	v[0] = 1;
	v[1] = 2;
	v[2] = 5;
	v[3] = 10;
	cout<<s.searchInsert(v, 9);
}