#include <iostream>

using namespace std;

class Solution {
public:
    /*
     * @param nums: a list of integers
     * @return: find a  majority number
     */
    int majorityNumber(vector<int> &nums) {
        // write your code here
        int count = 0, major = 0;
        for (int i = 0; i < nums.size(); i++) {
            /* code */
            if(count == 0)
            {
                major = nums[i];
                count++;
            }

            else
            {
                if(nums[i] == major)
                    count++;
                else
                    count--;
            }
        }
        return major;
    }
};

int main()
{
    return 0;
}
