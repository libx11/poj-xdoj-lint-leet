class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A integer indicate the sum of max subarray
     */
    int maxSubArray(vector<int> &nums) {
        // write your code here
        if(nums.size() <= 0)
            return 0;
        int max = nums[0], sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            /* code */
            if(sum < 0)
                sum = nums[i];
            else
                sum += nums[i];
            if(sum > max)
                max = sum;
        }
        return max;
        
    }
};