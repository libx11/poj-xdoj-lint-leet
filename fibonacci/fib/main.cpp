#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * @param n: an integer
     * @return: an ineger f(n)
     */
    int fibonacci(int n) {
        // write your code here
        int a = 0;
        int b = 1;
        int c = 1;
        if(n < 2)
            return 0;
        else if(n == 2)
        {
            return 1;
        }
        else
        {
            for(int i = 2; i < n; i++)
            {
                c = a + b;
                a = b;
                b = c;
            }
            return b;
        }
    }
};
