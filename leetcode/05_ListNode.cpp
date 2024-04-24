#include <iostream>
#include <vector>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *deleteNode(ListNode *head, int val)
{
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *cur = dummy;
    ListNode *nxt = dummy->next;
    while (nxt)
    {
        if (nxt->val == val)
        {
            cur->next = nxt->next;
            delete nxt;
            break;
        }
        else
        {
            cur = nxt;
            nxt = nxt->next;
        }
    }

    head = dummy->next;
    delete dummy;
    return head;
}

void printList(ListNode *head)
{
    ListNode *cur = head;
    while (cur)
    {
        if (cur->next == nullptr)
            cout << cur->val;
        else
            cout << cur->val << "->";
        cur = cur->next;
    }
}

ListNode *reverseList(ListNode *head)
{
    ListNode *cur = nullptr;
    ListNode *nxt = head;

    while (nxt)
    {
        ListNode *temp = nxt->next;
        nxt->next = cur;

        cur = nxt;
        nxt = temp;
    }
    head = cur;
    return head;
}

// 判断是否为回文链表
bool isPalindrome(ListNode *head)
{
    vector<int> nums;
    ListNode *cur = head;
    while (cur)
    {
        nums.push_back(cur->val);
        cur = cur->next;
    }
    int n = nums.size();
    int l = 0;
    int r = n - 1;
    while (l < r)
    {
        if (nums[l] != nums[r])
            return false;
        l++;
        r--;
    }
    return true;
}

// 删除链表倒数第n个节点
ListNode *removeNthFromEnd(ListNode *head, int n)
{
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *slow = dummy;
    ListNode *fast = dummy;

    for (int i = 0; i < n + 1; i++)
    {
        fast = fast->next;
    }
    while (fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    slow->next = slow->next->next; // 删除倒数第n个节点

    head = dummy->next;
    delete dummy;
    return head;
}

// 环形链表1
bool hasCycle(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast)
    {
        fast = fast->next;
        if (!fast)
            return false;
        else
            fast = fast->next;

        if (slow == fast)
            return true;
        slow = slow->next;
    }
    return false;
}

// 环形链表2
ListNode *detectCycle(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (slow == fast)
            break;
    }
    if (fast == nullptr)
        return nullptr;
    fast = head;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// int main()
// {
//     // ListNode *head = nullptr;
//     ListNode *head = new ListNode(0);
//     head->next = new ListNode(1);
//     head->next->next = new ListNode(2);
//     head->next->next->next = new ListNode(3);
//     head->next->next->next->next = new ListNode(4);

//     printList(head);
//     cout << endl;
//     head = deleteNode(head, -3);
//     // head = reverseList(head);
//     // cout << isPalindrome(head) << endl;

//     head = removeNthFromEnd(head, 0);
//     printList(head);

//     cout << endl;
//     system("pause");

//     return 0;
// }

// 两两交换链表中的节点
ListNode *swapPairs(ListNode *head)
{
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;

    ListNode *pre = dummy;

    while (pre->next && pre->next->next)
    {
        ListNode *cur = pre->next;
        ListNode *nxt = pre->next->next;

        cur->next = nxt->next;
        pre->next = nxt;
        nxt->next = cur;

        pre = cur;
    }

    head = dummy->next;
    delete dummy;
    return head;
}

// int main()
// {
//     ListNode *head = new ListNode(0);
//     head->next = new ListNode(1);
//     head->next->next = new ListNode(2);
//     head->next->next->next = new ListNode(3);
//     head->next->next->next->next = new ListNode(4);

//     printList(head);
//     cout << endl;
//     head = swapPairs(head);
//     printList(head);
//     cout << endl;
//     system("pause");
//     return 0;
// }

// 链表相交
//  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
//  {
//      if(!headA||!headB)
//          return nullptr;
//      ListNode *pA = headA, *pB = headB;
//      while (pA != pB)
//      {
//          pA = pA == nullptr ? headB : pA->next;
//          pB = pB == nullptr ? headA : pB->next;
//      }
//      return pA;
//  }

// 反转链表2
ListNode *reverseBetween(ListNode *head, int left, int right)
{
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;

    // 找出begin1,bgein2
    ListNode *begin = dummy;
    ListNode *begin2 = dummy;
    int num = 1;
    while (num <= left)
    {
        begin = begin2;
        begin2 = begin2->next;
        num++;
    }

    ListNode *end1 = begin2;
    ListNode *end2 = end1->next;
    // 反转操作
    // 并且找出end1,end2
    while (num <= right)
    {
        ListNode *temp = end2->next;
        end2->next = end1;

        end1 = end2;
        end2 = temp;

        num++;
    }
    // 进行连接！
    begin->next = end1;
    begin2->next = end2;

    head = dummy->next;
    delete dummy;
    return head;
}

// int main()
// {

//     ListNode *head = new ListNode(1);
//     head->next = new ListNode(2);
//     // head->next->next = new ListNode(3);
//     // head->next->next->next = new ListNode(4);
//     //   head->next->next->next->next = new ListNode(5);
//     //   head->next->next->next->next->next = new ListNode(6);

//     printList(head);

//     cout << endl;
//     head = reverseBetween(head, 1, 1);

//     printList(head);
//     cout << endl;

//     system("pause");
//     return 0;
// }

// 旋转链表
ListNode *rotateRight(ListNode *head, int k)
{
    if (!head)
        return nullptr;
    int len = 0;
    // 统计节点长度
    ListNode *cur = head;
    while (cur)
    {
        cur = cur->next;
        len++;
    }
    cur = head;
    // 计算新的头节点位置和尾节点位置
    int num = len - k % len;
    if (k % len == 0)
        return head;
    ListNode *newend = head;
    while (num > 0 && cur->next)
    {
        newend = cur;
        cur = cur->next;
        num--;
    }
    // 新的尾节点指向空
    newend->next = nullptr;
    ListNode *prebegin = head;
    head = cur;
    // 找到旧的尾节点，连接到旧的头节点
    while (cur->next)
    {
        cur = cur->next;
    }
    cur->next = prebegin;
    return head;
}

// 排序链表
// 1.插入排序，时间复杂度O(n2).
ListNode *sortList(ListNode *head)
{
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *pre = dummy;
    ListNode *cur = head;
    while (cur)
    {
        ListNode *first = dummy;
        while (first->next->val < cur->val)
        {
            first = first->next;
        }
        if (first->next != cur)
        {
            pre->next = cur->next;
            cur->next = first->next;
            first->next = cur;
            cur = pre->next;
        }
        else
        {
            pre = cur;
            cur = cur->next;
        }
    }
    ListNode *head = dummy->next;
    delete dummy;
    return head;
}

// 归并排序 O(nlog(n))
ListNode *sortList(ListNode *head)
{
}
int main()
{
    // ListNode *head = nullptr;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(4);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(2);
    head->next->next->next->next = new ListNode(5);

    printList(head);
    cout << endl;
    head = sortList(head);
    printList(head);
    cout << endl;
    system("pause");
    return 0;
}