class Solution {
public:
	/**
	* @param matrix: matrix, a list of lists of integers
	* @param target: An integer
	* @return: a boolean, indicate whether matrix contains target
	*/
	int searchMatrix(vector< vector<int> > &matrix, int target) {
		// write your code here
		int i, j, n, m, cnt = 0;
		n = matrix.size();
		if (n < 1)
			return 0;

		m = matrix[0].size();

		if (target < matrix[0][0] || target > matrix[n - 1][m - 1])
			return 0;
		i = 0, j = m - 1;
		while (1)
		{
			if (i > n - 1 || j < 0)
				break;
			if (matrix[i][j] == target)
			{
				cnt++;
				for (int tmp = j + 1; matrix[i][tmp] == target; tmp++)
				{
					cnt++;
				}
				j--;
			}

			else if (matrix[i][j] < target)
			{
				i++;
			}
			else
			{
				j--;
			}
		}
		return cnt;

	}
};