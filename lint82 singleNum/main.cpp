#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * @param A: An integer array
     * @return: An integer
     */
    int singleNumber(vector<int> &A) {
        // write your code here
        int result = 0;
        int size = A.size();
        for (int i = 0; i < size; i++) {
            /* code */
            result ^= A[i];
        }
        return result;
    }
};

int main()
{

    return 0;
}
