#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <functional>
#include <numeric>
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

// int main()
// {
//     int mainTank = 1;
//     int additionalTank = 2;
//     cout << distanceTraveled(mainTank, additionalTank) << endl;
//     system("pause");
//     return 0;
// }

// 摘樱桃
// 我的思路是，本体需要走两次，所以可以分成两个人，每个人走一次，然后再合并，但是这样的话，会有重复的路径，所以需要去重。我的做法是，第一个人走过的路径中，樱桃的位置置零，第二个人再走，但是这样的话，会出现的问题是，两次都尽可能取最大值，但这未必是两者之和的最大值！自己写的还贼麻烦，，，
// int cherryPickup(vector<vector<int>> &grid)
// {

//     int n = grid.size();
//     vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
//     dp[0][0] = grid[0][0];
//     for (int i = 1; i < n; i++)
//     {
//         if (grid[0][i] == 1)
//         {
//             dp[0][i] = dp[0][i - 1] + grid[0][i];
//             grid[0][i] = 0;
//         }
//         else if (grid[0][i] == 0)
//             dp[0][i] = dp[0][i - 1];
//     }
//     for (int i = 1; i < n; i++)
//     {
//         if (grid[i][0] == 1)
//         {
//             dp[i][0] = dp[i - 1][0] + grid[i][0];
//             grid[i][0] = 0;
//         }
//         else if (grid[i][0] == 0)
//             dp[i][0] = dp[i - 1][0];
//     }
//     vector<int> trace;
//     bool isleft = 0;
//     int start = 0;
//     for (int i = 1; i < n; i++)
//         for (int j = 1; j < n; j++)
//         {

//             if (grid[i][j] == -1)
//                 dp[i][j] = -1;
//             else if (grid[i][j] == 1)
//             {
//                 if (dp[i - 1][j] > dp[i][j - 1])
//                 {
//                     if (i - 1 == 0)
//                     {
//                         start = j;
//                     }

//                     trace.push_back(1);
//                 }
//                 else
//                 {
//                     if (j - 1 == 0)
//                     {
//                         isleft = 1;
//                         start = i;
//                     }
//                     trace.push_back(2);
//                 }

//                 dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + 1;
//                 grid[i][j] = 0;
//             }
//             else
//                 dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
//         }

//     if (isleft)
//     {
//         int s = 0;
//         int q = 0;
//         while (s < n - 1 && q < n - 1)
//         {
//             if (isleft)
//             {
//                 while (s <= start)
//                     if (grid[s][0] == 1)
//                     {
//                         grid[s][0] = 0;
//                         s++;
//                     }
//                 for (int i = 0; i < trace.size(); i++)
//                 {
//                     if (trace[i] == 1)
//                     {
//                         if (grid[s][q + 1] == 1)
//                         {
//                             grid[s][q + 1] = 0;
//                             q++;
//                         }
//                     }
//                     else
//                     {
//                         if (grid[s + 1][q] == 1)
//                         {
//                             grid[s + 1][q] = 0;
//                             s++;
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {

//             cout << dp[i][j] << " ";
//         }
//         cout << endl;
//     }

//     return dp[n - 1][n - 1];
// }

// int main()
// {
//     vector<vector<int>> grid = {{0, 1, -1}, {1, 0, -1}, {1, 1, 1}};
//     int ans1 = cherryPickup(grid);
//     int ans2 = cherryPickup(grid);

//     system("pause");
//     return 0;
// }

// 给植物浇水
int wateringPlants(vector<int> &plants, int capacity)
{
    int n = plants.size();
    int cur = capacity;
    int step = 0;
    for (int i = 0; i < n; i++)
    {
        if (cur >= plants[i])
        {
            cur -= plants[i];
            step++;
        }
        else if (cur < plants[i])
        {
            cur = capacity - plants[i];
            step += 2 * i + 1;
        }
    }
    return step;
}

// int main()
// {
//     vector<int> plants = {1, 3, 2, 2};
//     cout << wateringPlants(plants, 5) << endl;
//     system("pause");
//     return 0;
// }

int climb(int num)
{
    vector<int> dp(num + 1, INT_MAX);
    if (num == 0)
        return 0;
    if (num == 1)
        return -1; // 无法仅通过减去2或3得到0
    dp[0] = 0;
    for (int i = 2; i <= num; ++i)
    {
        if (i - 2 >= 0 && dp[i - 2] != INT_MAX)
        {
            dp[i] = std::min(dp[i], dp[i - 2] + 1);
        }
        if (i - 3 >= 0 && dp[i - 3] != INT_MAX)
        {
            dp[i] = std::min(dp[i], dp[i - 3] + 1);
        }
    }

    return dp[num] == INT_MAX ? -1 : dp[num];
}

// 完成所有任务所需要的最少轮数
int minimumRounds(vector<int> &tasks)
{
    unordered_map<int, int> map;
    for (int i = 0; i < tasks.size(); i++)
    {
        map[tasks[i]]++;
    }
    int num = 0;
    for (auto it = map.begin(); it != map.end(); it++)
    {

        int step = climb(it->second);
        if (step == -1)
            return -1;
        else
            num += step;
    }

    return num;
}

// // 这道题贪心解法更简单，直接让这个数除以3，根据余数判断情况即可。
// int main()
// {

//     vector<int> tasks = {2, 2, 3, 3, 2, 4, 4, 4, 4, 4};
//     cout << minimumRounds(tasks) << endl;
//     system("pause");
//     return 0;
// }

// 完成所有任务的最少时间
// int findMinimumTime(vector<vector<int>> &tasks)
// {
//     int n = tasks.size();
//     sort(tasks.begin(), tasks.end(), [](vector<int> &a, vector<int> &b)
//          { return a[1] < b[1]; });

//     vector<int> run(tasks[n - 1][1] + 1);
//     int res = 0;
//     for (int i = 0; i < n; i++)
//     {
//         int start = tasks[i][0], end = tasks[i][1], duration = tasks[i][2];
//         duration -= accumulate(run.begin() + start, run.begin() + end + 1, 0);
//         res += max(duration, 0);
//         for (int j = end; j >= 0 && duration > 0; j--)
//         {
//             if (run[j] == 0)
//             {
//                 duration--;
//                 run[j] = 1;
//             }
//         }
//     }
//     return res;
// }

// int main()
// {
//     vector<vector<int>> tasks = {{2, 3, 1}, {4, 5, 1}, {1, 5, 2}};
//     cout << findMinimumTime(tasks) << endl;
//     system("pause");
//     return 0;
// }

// 可以工作的最大周数
long long numberOfWeeks(vector<int> &milestones)
{
    // 耗时最长工作所需周数
    long long longest = *max_element(milestones.begin(), milestones.end());
    // 其余工作共计所需周数
    long long rest = accumulate(milestones.begin(), milestones.end(), 0LL) - longest;
    if (longest > rest + 1)
    {
        // 此时无法完成所耗时最长的工作
        return rest * 2 + 1;
    }
    else
    {
        // 此时可以完成所有工作
        return longest + rest;
    }
}

// int main()
// {
//     vector<int> nums = {1, 2, 5};
//     cout << numberOfWeeks(nums) << endl;
//     system("pause");
//     return 0;
// }

// 移除石子的最大的得分
int maximumScore(int a, int b, int c)
{
    int maxnum = max(max(a, b), c);
    int sum = a + b + c;
    int rest = sum - maxnum;
    if (maxnum > rest + 1)
        return rest;
    else
        return sum / 2;
}

// 使数组中所有元素相等的最小开销
int minCostToEqualizeArray(vector<int> &nums, int cost1, int cost2)
{
    return 0;
}

// 找出最长的超赞子字符串
// 想法：超赞子字符串是由n对相同的字符和小于等于1个单独字符组成的。这是满足超赞的必要条件。我的思路是先统计当前区间的单独字符有多少个，如果单独字符串数量小于等于1个时候，统计该区间长度，找出最长即可。
// 通过哈希表可以判断单独字符串的数量，如果字符之前没出现过，单独字符串加一，如果出现过，单独字符串减一。
// 最后的问题就是区间如何选择，两层循环超时，一层循环滑窗没有好的方案。
int longestAwesome(string s)
{
    int n = s.size();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int num_unique = 0;
        unordered_map<char, int> map;
        for (int j = i; j < n; j++)
        {
            map[s[j]]++;

            if (map[s[j]] % 2 == 1)
                num_unique++;
            else if (map[s[j]] % 2 == 0)
                num_unique--;
            if (num_unique <= 1)
                ans = max(ans, j - i + 1);
        }
    }

    return ans;
}

// 答案的方法采用了位运算的方法和数学知识，还是有些难想的
int longestAwesome1(string s)
{
    int n = s.size();
    unordered_map<int, int> prefix = {{0, -1}};
    int ans = 0;
    int sequence = 0;
    for (int j = 0; j < n; ++j)
    {
        int digit = s[j] - '0';
        sequence ^= (1 << digit);
        if (prefix.count(sequence))
        {
            ans = max(ans, j - prefix[sequence]);
        }
        else
        {
            prefix[sequence] = j;
        }
        for (int k = 0; k < 10; ++k)
        {
            if (prefix.count(sequence ^ (1 << k)))
            {
                ans = max(ans, j - prefix[sequence ^ (1 << k)]);
            }
        }
    }
    return ans;
}

// int main()
// {

//     cout << longestAwesome("51224") << endl;
//     system("pause");
//     return 0;
// }

vector<vector<int>> findWinners(vector<vector<int>> &matches)
{
    int n = matches.size();
    unordered_map<int, int> map;
    vector<int> ans1;
    vector<int> ans2;
    for (int i = 0; i < n; i++)
    {
        map[matches[i][1]]++;
    }
    for (int i = 0; i < n; i++)
    {
        if (map[matches[i][0]] == 0)
            ans1.push_back(matches[i][0]);
    }
    sort(ans1.begin(), ans1.end());
    auto nums2 = unique(ans1.begin(), ans1.end());
    ans1.erase(nums2, ans1.end());

    for (auto it = map.begin(); it != map.end(); it++)
    {
        // cout << it->first << " " << it->second << endl;
        if (it->second == 1)
            ans2.push_back(it->first);
    }
    sort(ans2.begin(), ans2.end());
    return {ans1, ans2};
}

// int main()
// {
//     vector<vector<int>> matches = {{1, 3},
//                                    {2, 3},
//                                    {3, 6},
//                                    {5, 6},
//                                    {5, 7},
//                                    {4, 5},
//                                    {4, 8},
//                                    {4, 9},
//                                    {10, 4},
//                                    {10, 9}};
//     vector<vector<int>> ans = findWinners(matches);
//     for (int i = 0; i < ans.size(); i++)
//     {
//         for (auto t : ans[i])
//         {
//             cout << t << " ";
//         }
//         cout << endl;
//     }

//     system("pause");
//     return 0;
// }

// 找出最长的等值子数组
// 先使用哈希映射，之后使用滑动窗口遍历
int longestEqualSubarray(vector<int> &nums, int k)
{
    unordered_map<int, vector<int>> map;
    for (int i = 0; i < nums.size(); i++)
    {
        map[nums[i]].push_back(i);
    }

    int ans = 0;
    for (auto it = map.begin(); it != map.end(); it++)
    {
        for (int i = 0, j = 0; i < it->second.size(); i++)
        {

            while ((it->second)[i] - (it->second)[j] - (i - j) > k)
            {
                j++;
            }
            ans = max(ans, i - j + 1);
        }
    }

    return ans;
}

int main()
{

    vector<int> nums = {1, 3, 2, 3, 1, 2, 3};
    int ans = longestEqualSubarray(nums, 3);
    cout << ans;
    system("pause");
    return 0;
}