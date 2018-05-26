#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * @param numbers: An array of Integer
     * @param target: target = numbers[index1] + numbers[index2]
     * @return: [index1, index2] (index1 < index2)
     */
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        // write your code here
         std::map<int, int> m;
         std::vector<int> result;

         for (int i = 0; i < numbers.size(); i++)
         {
             /* code */
             m[numbers[i]] = i+1;

         }
         for (int i = 0; i < numbers.size(); i++)
         {
             if(m[target - numbers[i]] != 0)
             {
                 result.push_back(i);
                 result.push_back(m[target - numbers[i]]-1);
                 break;
             }
         }
         return result;
    }
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
