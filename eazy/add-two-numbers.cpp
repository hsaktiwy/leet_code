/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* newNode(int val)
{
    struct ListNode* node = malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* head = NULL;
    struct ListNode* current;
    int carry = 0;
    int v = 0;

    current = NULL;
    while (l1 || l2 || carry !=0)
    {
        v = (l1 ? l1->val:0) + (l2 ? l2->val:0)+carry;
        carry = v/10;
        if (!(current))
        {
            head = newNode(v%10);
            (current) = head;
        }
        else
        {
            (current)->next = newNode(v%10);
        }
        if (l1)
            l1 = l1->next;
        if (l2)
            l2 = l2->next;
        if ((current)->next)
        (current) = (current)->next;
    }
    return head;
}
