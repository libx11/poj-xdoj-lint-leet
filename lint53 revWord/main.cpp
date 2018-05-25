#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    /*
     * @param s: A string
     * @return: A string
     */
    string reverseWords(string &s) {
        // write your code here

        string result = "";

        int i = 0, j = 0;
        for (i = s.size() - 1; i >= 0; i--)
        {
            /* code */
            if(s[i] != ' ')
            {
                j = i;

                while(j >= 0 && s[j] != ' ')
                    j--;
                result.append(s, j+1, i-j);
                result += " ";
                i = j;
            }

        }
        if(result.size() > 0)
            result.erase( result.size() - 1);
        return result;
    }
};

//   "I love to walk around in bookstores       not because I can buy all the books"

int main()
{
    string str("I love to walk around in bookstores       not because I can buy all the books");

    Solution s;

    cout << s.reverseWords(str) << endl;
    return 0;
}
