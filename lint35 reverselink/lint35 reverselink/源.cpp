/**
* Definition of singly-linked-list:
*
* class ListNode {
* public:
*     int val;
*     ListNode *next;
*     ListNode(int val) {
*        this->val = val;
*        this->next = NULL;
*     }
* }
*/

class Solution {
public:
	/**
	* @param head: n
	* @return: The new head of reversed linked list.
	*/
	ListNode * reverse(ListNode * head) {
		// write your code here

		if (head == NULL)
			return NULL;
		else
		{
			std::stack<ListNode*> stk;
			while (head != NULL)
			{
				stk.push(head);
				head = head->next;
			}
			ListNode *result;
			result = head = stk.top();
			stk.pop();
			while (!stk.empty())
			{
				head->next = stk.top();
				stk.pop();
				head = head->next;
			}
			head->next = NULL;
			return result;

		}
	}
};