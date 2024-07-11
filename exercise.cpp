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

// int main()
// {

//     vector<int> nums = {1, 3, 2, 3, 1, 2, 3};
//     int ans = longestEqualSubarray(nums, 3);
//     cout << ans;
//     system("pause");
//     return 0;
// }

vector<int> findIndices(vector<int> &nums, int indexDifference, int valueDifference)
{
    int n = nums.size();
    int maxidx = 0;
    int minidx = 0;

    for (int i = indexDifference; i < n; i++)
    {
        int j = i - indexDifference;
        if (nums[j] > nums[maxidx])
        {
            maxidx = j;
        }
        if (nums[j] < nums[minidx])
        {
            minidx = j;
        }

        if (nums[i] - nums[minidx] >= valueDifference)
        {
            return {minidx, i};
        }
        if (nums[maxidx] - nums[i] >= valueDifference)
        {
            return {maxidx, i};
        }
    }
    return {-1, -1};
}

int greaterCount(vector<int> nums, int val)
{

    int count = 0;
    for (auto num : nums)
        if (num > val)
            count++;
    return count;
}

// 将元素分配到两个数组中Ⅱ
// 这个解法果然超时了，正确的做法是使用树形数组！但这个之前没遇到过
vector<int> resultArray(vector<int> &nums)
{
    vector<int> arr1;
    vector<int> arr2;
    arr1.push_back(nums[0]);
    arr2.push_back(nums[1]);
    for (int i = 2; i < nums.size(); i++)
    {
        if (greaterCount(arr1, nums[i]) > greaterCount(arr2, nums[i]))
            arr1.push_back(nums[i]);
        else if (greaterCount(arr1, nums[i]) < greaterCount(arr2, nums[i]))
            arr2.push_back(nums[i]);
        else
        {
            if (arr1.size() > arr2.size())
                arr2.push_back(nums[i]);
            else
                arr1.push_back(nums[i]);
        }
    }
    arr1.insert(arr1.end(), arr2.begin(), arr2.end());
    return arr1;
}

// 先抄一个官方代码
class BinaryIndexedTree
{
private:
    vector<int> tree;

public:
    BinaryIndexedTree(int n) : tree(n + 1) {}

    void add(int i)
    {
        while (i < tree.size())
        {
            tree[i] += 1;
            i += i & -i;
        }
    }

    int get(int i)
    {
        int res = 0;
        while (i > 0)
        {
            res += tree[i];
            i &= i - 1;
        }
        return res;
    }
};

vector<int> resultArray1(vector<int> &nums)
{
    int n = nums.size();
    vector<int> sortedNums = nums;
    sort(sortedNums.begin(), sortedNums.end());
    unordered_map<int, int> index;
    for (int i = 0; i < n; ++i)
    {
        index[sortedNums[i]] = i + 1;
    }

    vector<int> arr1 = {nums[0]};
    vector<int> arr2 = {nums[1]};
    BinaryIndexedTree tree1(n), tree2(n);
    tree1.add(index[nums[0]]);
    tree2.add(index[nums[1]]);

    for (int i = 2; i < n; ++i)
    {
        int count1 = arr1.size() - tree1.get(index[nums[i]]);
        int count2 = arr2.size() - tree2.get(index[nums[i]]);
        if (count1 > count2 || (count1 == count2 && arr1.size() <= arr2.size()))
        {
            arr1.push_back(nums[i]);
            tree1.add(index[nums[i]]);
        }
        else
        {
            arr2.push_back(nums[i]);
            tree2.add(index[nums[i]]);
        }
    }

    arr1.insert(arr1.end(), arr2.begin(), arr2.end());
    return arr1;
}

// int main()
// {

//     vector<int> nums = {5, 14, 3, 1, 2};
//     vector<int> ans = resultArray(nums);
//     for (auto a : ans)
//         cout << a << " ";
//     cout << endl;
//     system("pause");
//     return 0;
// }

// 统计1的个数，在哪个位置需要变成一，那就在这个位置之前的元素需要处理
long long minimumSteps(string s)
{
    long long num_one = 0;
    for (auto c : s)
        if (c == '1')
            num_one++;

    int begin = s.size() - num_one;
    long long count = 0;
    int index_1 = 0;
    int index_0 = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (i < begin)
        {
            if (s[i] == '1')
                index_1 += i;
        }
        else
        {
            if (s[i] == '0')
                index_0 += i;
        }
    }

    return index_0 - index_1;
}

// 更简便的方法，统计每个白球左边黑球的数量，有多少个黑球就交换几次
long long minimumSteps1(string s)
{
    long long ans = 0;
    int sum = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '1')
        {
            sum++;
        }
        else
        {
            ans += sum;
        }
    }
    return ans;
}

// int main()
// {

//     cout << minimumSteps("11000111") << endl;
//     system("pause");
//     return 0;
// }

/// 还未解答！
///  @brief 戳气球
///  @param nums
///  @return
int maxCoins(vector<int> &nums)
{
    int n = nums.size();

    if (n == 1)
        return nums[0];
    if (n == 2)
        return nums[0] * nums[1] + max(nums[0], nums[1]);
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            nums.erase(nums.begin() + i);
            return nums[i] * nums[i + 1] + maxCoins(nums);
        }
        else if (i = n - 1)
        {
            nums.erase(nums.begin() + i);
            return nums[i] * nums[i - 1] + maxCoins(nums);
        }
        else
        {
            nums.erase(nums.begin() + i);
            return nums[i - 1] * nums[i] * nums[i + 1] + maxCoins(nums);
        }
    }

    return 0;
}

// int main()
// {
//     vector<int> nums = {3, 1, 8, 5};
//     cout << maxCoins(nums) << endl;
//     system("pause");
//     return 0;
// }

int countBattleships(vector<vector<char>> &board)
{
    int m = board.size();
    int n = board[0].size();
    int count = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 'X' && (i == 0 || board[i - 1][j] != 'X') && (j == 0 || board[i][j - 1] != 'X'))
                count++;
        }

    return count;
}

// int main()
// {

//     vector<vector<char>> board = {
//         {'X', '.', '.', 'X'},
//         {'.', '.', '.', 'X'},
//         {'.', '.', '.', 'X'}};

//     cout
//         << countBattleships(board) << endl;
//     system("pause");
//     return 0;
// }

/// @brief 给墙壁刷油漆
/// @param cost
/// @param time
/// @return
// 要使得开销最少，那就要多用免费油漆工，但是免费工刷一堵墙一天，且在付费工工作时候才工作，那么就需要付费工尽量工作较多的天数，同时不能工作较多的花费。关键在于如何对这两者进行平衡
// 由题意可知，免费工工作的天数，是小于等于付费工的。假设付费工刷了t堵墙，工作了sum1天,应该满足 sum1刚好大于等于 n-t。在此基础上，要满足付费工这t天开销最少
int paintWalls(vector<int> &cost, vector<int> &time)
{

    int n = cost.size();
    // 创建一个包含cost和time对的vector
    std::vector<std::pair<int, int>> costTimePairs;
    for (size_t i = 0; i < cost.size(); ++i)
    {
        costTimePairs.emplace_back(cost[i], time[i]);
    }

    // 对costTimePairs进行排序
    std::sort(costTimePairs.begin(), costTimePairs.end());

    // 提取排序后的结果
    for (size_t i = 0; i < costTimePairs.size(); ++i)
    {
        cost[i] = costTimePairs[i].first;
        time[i] = costTimePairs[i].second;
    }
    cout << "sorted cost:" << endl;
    for (auto c : cost)
        cout << c << " ";
    cout << endl;

    cout << "sorted time:" << endl;
    for (auto c : time)
        cout << c << " ";
    cout << endl;

    int t = 0;
    int sum1 = 0;
    int cost1 = 0;
    for (int i = 0; i < cost.size() - 1; i++)
    {

        sum1 += time[i];
        t++;
        cost1 += cost[i];

        if (sum1 - time[i] + time[i + 1] >= n - t && sum1 < n - t && cost[i + 1] - cost[i] <= cost[i] && time[i + 1] > time[i])
        {
            cost1 -= cost[i];
            continue;
        }
        if (sum1 >= cost.size() - t)
        {

            break;
        }
    }

    return cost1;
}

// 上面的方法根本求不出来，要考虑的情况太多了，只能用动态规划了，先抄一下
int paintWalls1(vector<int> &cost, vector<int> &time)
{
    int n = cost.size();
    vector<int> f(n * 2 + 1, INT_MAX / 2);
    f[n] = 0;
    for (int i = 0; i < n; ++i)
    {
        vector<int> g(n * 2 + 1, INT_MAX / 2);
        for (int j = 0; j <= n * 2; ++j)
        {
            // 付费
            g[min(j + time[i], n * 2)] = min(g[min(j + time[i], n * 2)], f[j] + cost[i]);
            // 免费
            if (j > 0)
            {
                g[j - 1] = min(g[j - 1], f[j]);
            }
        }
        f = move(g);
    }
    return *min_element(f.begin() + n, f.end());
}

// int main()
// {
//     vector<int> cost = {26, 53, 10, 24, 25, 20, 63, 51};
//     vector<int> time = {1, 1, 1, 1, 2, 2, 2, 1};

//     cout << paintWalls(cost, time) << endl;
//     system("pause");
//     return 0;
// }

// 检查操作是否合法
// 这道题目看起来麻烦，但看完之后感觉还好。。因为只需改变一个格子，然后判断是否能构成好线段即可，只需要把四个方向都判断一下，如果有一个方向可以组成好线段，那么返回true即可。
// 需要注意的是，改变的格子必须是好线段的顶点才行，不能是中间的点
// 四个方向继续分就有八种情况，这也太麻烦了吧。。。
// 可以整个到一个函数，循环八次。。
bool checkMove(vector<vector<char>> &board, int rMove, int cMove, char color)
{
    int n = 8;
    char goodcolor;

    if (color == 'B')
        goodcolor = 'W';
    else
        goodcolor = 'B';

    // 上
    int row = rMove;
    int col = cMove;
    while (row >= 0)
    {
        row--;
        if (row == rMove - 1)
        {
            if (board[row][col] != goodcolor)
                break;
        }
        if (board[row][col] == '.')
            break;
        if (board[row][col] == color)
            return true;
    }

    // 下
    row = rMove;
    col = cMove;
    while (row < 8)
    {
        row++;
        if (row == rMove + 1)
        {
            if (board[row][col] != goodcolor)
                break;
        }
        if (board[row][col] == '.')
            break;
        if (board[row][col] == color)
            return true;
    }

    // 左
    row = rMove;
    col = cMove;
    while (col >= 0)
    {
        col--;
        if (col == cMove - 1)
        {
            if (board[row][col] != goodcolor)
                break;
        }
        if (board[row][col] == '.')
            break;
        if (board[row][col] == color)
            return true;
    }

    // 右
    row = rMove;
    col = cMove;
    while (col < 8)
    {
        col++;
        if (col == cMove + 1)
        {
            if (board[row][col] != goodcolor)
                break;
        }
        if (board[row][col] == '.')
            break;
        if (board[row][col] == color)
            return true;
    }

    // 左上
    row = rMove;
    col = cMove;
    while (col >= 0 && row >= 0)
    {
        col--;
        row--;
        if (col == cMove - 1)
        {
            if (board[row][col] != goodcolor)
                break;
        }
        if (board[row][col] == '.')
            break;
        if (board[row][col] == color)
            return true;
    }

    // 右下
    row = rMove;
    col = cMove;
    while (col < 8 && row < 8)
    {
        col++;
        row++;
        if (col == cMove + 1)
        {
            if (board[row][col] != goodcolor)
                break;
        }
        if (board[row][col] == '.')
            break;
        if (board[row][col] == color)
            return true;
    }

    // 左下
    row = rMove;
    col = cMove;
    while (col >= 0 && row < 8)
    {
        col--;
        row++;
        if (col == cMove - 1)
        {
            if (board[row][col] != goodcolor)
                break;
        }
        if (board[row][col] == '.')
            break;
        if (board[row][col] == color)
            return true;
    }

    // 右下
    row = rMove;
    col = cMove;
    while (col < 8 && row >= 0)
    {
        col++;
        row--;
        if (col == cMove + 1)
        {
            if (board[row][col] != goodcolor)
                break;
        }
        if (board[row][col] == '.')
            break;
        if (board[row][col] == color)
            return true;
    }

    return false;
}

/// @brief 统计移除递增子数组的数目l
/// @param nums
/// @return

bool isIncrease(vector<int> nums, int begin, int end)
{
    if (begin == end)
        return true;

    for (int i = begin; i < end; i++)
    {
        if (nums[i] >= nums[i + 1])
            return false;
    }
    return true;
}

// 这道题之所以是简单题目，因为暴力可以解出来。数据量变一下，直接成困难题了。
// int incremovableSubarrayCount(vector<int> &nums)
// {
//     int n = nums.size();
//     int count = 1;
//     for (int i = 0; i < n; i++)

//         for (int j = i; j < n; j++)
//         {

//             if (i > 0 && j < n - 1)
//             {
//                 if (isIncrease(nums, 0, i - 1) && isIncrease(nums, j + 1, n - 1))
//                 {

//                     if (nums[i - 1] < nums[j + 1])
//                         count++;
//                 }
//             }
//             else if (i == 0 && j < n - 1)
//             {
//                 if (isIncrease(nums, j + 1, n - 1))
//                     count++;
//             }
//             else if (i > 0 && j == n - 1)
//             {
//                 if (isIncrease(nums, 0, i - 1))
//                     count++;
//             }
//         }

//     return count;
// }

/// @brief 统计移除递增子数组的数目2
/// @param nums
/// @return
// 这道题目的双指针解法太妙了！时间复杂度直接变为O(n)。
// 具体的思路是，先让左指针移动到最长递增下标。如果当前数组为单调递增，那么直接返回（n）*(n+1)/2。
// 如果数组前i个数组是单调递增，那么就让left = i。之后使得right 指向数组末尾，逐渐向左移动，直到出现 nums[right]>nums[left].
// 那么此时可以移除以right-1为右边界，0-left-1为左边界的所有子数组。共有left+2个。之后继续向左移动左指针，将结果累加即可。这个过程调试一下才能清楚

long long incremovableSubarrayCount(vector<int> &nums)
{
    long long ans = 0;
    int n = nums.size();
    int left = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (nums[i] >= nums[i + 1])
            break;
        else
            left++;
    }
    if (left == n - 1)
        return (n + 1) * n / 2;

    ans += left + 2;
    for (int right = n - 1; right >= 0; right--)
    {
        if (right < n - 1 && nums[right] >= nums[right + 1])
        {
            break;
        }
        while (left >= 0 && nums[left] >= nums[right])
            left--;
        ans += left + 2;
    }

    return ans;
}

int main()
{

    vector<int> nums = {1, 3, 4, 1, 2};
    cout << incremovableSubarrayCount(nums) << endl;
    system("pause");
    return 0;
}