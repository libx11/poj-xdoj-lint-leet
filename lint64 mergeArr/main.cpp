#include <iostream>

using namespace std;

class Solution {
public:
    /*
     * @param A: sorted integer array A which has m elements, but size of A is m+n
     * @param m: An integer
     * @param B: sorted integer array B which has n elements
     * @param n: An integer
     * @return: nothing
     */
    void mergeSortedArray(int A[], int m, int B[], int n) {
        // write your code here

        int i = m - 1;
        int j = n - 1;
        int p = i + j + 1;

        while(i >= 0 && j >= 0)
        {

            if(A[i] > B[j])
                A[p--] = A[i--];
            else
                A[p--] = B[j--];

        }
        if(i < 0)
        {
            for (int x = 0; x < j+1; x++)
            {
                A[x] = B[x];
            }
        }
        return;
    }
};

int main()
{

    return 0;
}
