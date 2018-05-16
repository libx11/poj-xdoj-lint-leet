#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
	/**
	* @param matrix: matrix, a list of lists of integers
	* @param target: An integer
	* @return: a boolean, indicate whether matrix contains target
	*/
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		// write your code here
		int i, j, n, m;
		n = matrix.size();
		if (n < 1)
			return false;

		m = matrix[0].size();

		if (target < matrix[0][0] || target > matrix[n - 1][m - 1])
			return false;
		i = 0, j = m - 1;
		while (1)
		{
			if (i > n - 1 || j < 0)
				return false;
			if (matrix[i][j] == target)
				return true;
			else if (matrix[i][j] < target)
			{
				i++;
			}
			else
			{
				j--;
			}
		}

	}
};
int main()
{
	vector<vector<int>> v(3);
	for (int i = 0; i < 3; i++)
	{
		v[i].resize(3);
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			v[i][j] = i;
		}
	}
	v[1][1] = 2;
	Solution s;
	cout<<s.searchMatrix(v, 2);
	getchar();
}