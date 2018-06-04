#include <iostream>

using namespace std;

/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param root: The root of binary tree.
     * @return: True if this Binary tree is Balanced, or false.
     */
     bool balanced(TreeNode * root, int &depth)
     {
        if(root == NULL)
            return true;

        int leftDepth = 0, rightDepth = 0;

        if(!balanced(root -> left, leftDepth))
            return false;
        if(!balanced(root -> right, rightDepth))
            return false;

        if(abs(leftDepth - rightDepth) <= 1)
        {
            depth = max(leftDepth, rightDepth) + 1;
            return true;
        }

        return false;
     }

    bool isBalanced(TreeNode * root) {
        // write your code here
        int depth = 0;
        return balanced(root, depth);
    }
};
int main()
{
    return 0;
}
