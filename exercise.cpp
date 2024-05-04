#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

// 最小山形三元组
int minimumSum(vector<int> &nums)
{
    int n = nums.size();
    int left[n];
    int right[n];
    int minnum = INT_MAX;
    left[0] = nums[0];
    for (int i = 1; i < n; i++)
    {
        left[i] = min(left[i - 1], nums[i]);
    }
    right[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        right[i] = min(right[i + 1], nums[i]);
    }
    int sum = INT_MAX;
    for (int i = 1; i < n - 1; i++)
    {
        if (nums[i] > left[i - 1] && nums[i] > right[i + 1])
            sum = min(sum, nums[i] + left[i - 1] + right[i + 1]);
    }
    return sum == INT_MAX ? -1 : sum;
}

// int main()
// {
//     vector<int> nums = {8, 6, 1, 5, 3, 2};
//     cout << minimumSum(nums) << endl;
//     system("pause");
//     return 0;
// }

// 最大乘积子数组
int maxProduct(vector<int> &nums)
{
    int n = nums.size();
    vector<int> maxDp(n), minDp(n);
    maxDp[0] = minDp[0] = nums[0];
    int maxProduct = nums[0];

    for (int i = 1; i < n; i++)
    {
        maxDp[i] = max(max(maxDp[i - 1] * nums[i], minDp[i - 1] * nums[i]), nums[i]);
        minDp[i] = min(min(maxDp[i - 1] * nums[i], minDp[i - 1] * nums[i]), nums[i]);
        maxProduct = max(maxProduct, maxDp[i]);
    }

    return maxProduct;
}
// int main()
// {
//     vector<int> nums = {2, 3, -2, 4, -5};
//     cout << maxProduct(nums) << endl;
//     system("pause");
//     return 0;
// }

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<TreeNode *> allPossibleFBT(int n)
{
    if (n % 2 == 0)
        return {};
    if (n == 1)
        return {new TreeNode(0)};
    vector<TreeNode *> res;
    for (int i = 1; i < n; i += 2)
    {
        vector<TreeNode *> left = allPossibleFBT(i);
        vector<TreeNode *> right = allPossibleFBT(n - i - 1);
        for (auto l : left)
        {
            for (auto r : right)
            {
                TreeNode *root = new TreeNode(0);
                root->left = l;
                root->right = r;
                res.push_back(root);
            }
        }
    }
    return res;
}

// 找出克隆二叉树中的相同节点
TreeNode *getTargetCopy(TreeNode *original, TreeNode *cloned, TreeNode *target)
{
    if (!original)
        return nullptr;
    if (original->val == target->val)
        return cloned;
    TreeNode *left = getTargetCopy(original->left, cloned->left, target);
    TreeNode *right = getTargetCopy(original->right, cloned->right, target);
    return left ? left : right;
}

// int main()
// {

//     TreeNode *root = new TreeNode(0);
//     root->left = new TreeNode(1);
//     root->right = new TreeNode(2);
//     root->left->left = new TreeNode(3);
//     root->left->right = new TreeNode(4);
//     TreeNode *ans = getTargetCopy(root, root, root->left->right);
//     cout << ans->val << endl;
//     system("pause");
//     return 0;
// }

// 使数组连续的最少操作数
int minOperations(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    int n1 = nums.size();
    auto nums2 = unique(nums.begin(), nums.end());
    nums.erase(nums2, nums.end());
    int left = 0;
    int n = nums.size();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        while (nums[left] < nums[i] - n1 + 1)
        {
            left++;
        }
        ans = max(ans, i - left + 1);
    }
    return n1 - ans;
}

// int main()
// {

//     vector<int> nums = {8, 5, 9, 9, 8, 4};
//     cout << minOperations(nums) << endl;
//     system("pause");
//     return 0;
// }

int maximumCount(vector<int> &nums)
{
    int n = nums.size();
    int l = 0, r = n - 1;
    if (nums[0] > 0 || nums[n - 1] < 0)
        return n;
    while (l < r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] > 0)
            r = mid;
        else
            l = mid + 1;
    }
    int ans1 = 0;
    if (l != n - 1)
        ans1 = n - l;
    int l2 = 0;
    r = n - 1;
    while (l2 < r)
    {
        int mid = l2 + (r - l2) / 2;
        if (nums[mid] < 0)
            l2 = mid + 1;
        else
            r = mid;
    }
    return max(ans1, l2);
}

// int main()
// {
//     vector<int> nums = {2};
//     cout << maximumCount(nums) << endl;
//     system("pause");
//     return 0;
// }

// 修改后的最大二进制字符串
string maximumBinaryString(string binary)
{
    int n = binary.size();
    int firstzero = -1;

    for (int i = 0; i < n; i++)
        if (binary[i] == '0')
        {
            firstzero = i;
            break;
        }

    int numzero = 0;
    for (auto bi : binary)
    {
        if (bi == '0')
            numzero++;
    }
    if (numzero == 0)
        return binary;

    string ans(n, '1');
    ans[firstzero + numzero - 1] = '0';
    return ans;
}

// int main()
// {
//     string binary = "1100";
//     cout << maximumBinaryString(binary) << endl;
//     system("pause");
//     return 0;
// }

// 总行驶距离
int distanceTraveled(int mainTank, int additionalTank)
{
    int distance = 0;
    while (mainTank >= 5 && additionalTank > 0)
    {
        distance += 10 * 5;
        mainTank -= 5;
        additionalTank--;
        mainTank++;
    }
    distance += mainTank * 10;
    return distance;
}

int main()
{
    int mainTank = 1;
    int additionalTank = 2;
    cout << distanceTraveled(mainTank, additionalTank) << endl;
    system("pause");
    return 0;
}