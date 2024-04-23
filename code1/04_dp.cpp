#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

int fib(int n)
{
    if (n <= 1)
        return n;
    int dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

int minCostClimbingStairs(vector<int> &cost)
{
    int n = cost.size();
    vector<int> dp(n + 1, 0);

    dp[0] = dp[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    }

    // for (auto i : dp)
    //     cout << i << " ";
    // cout << endl;

    return dp[n];
}

// int main()
// {
//     vector<int> costs = {10, 15, 20};
//     cout << minCostClimbingStairs(costs) << endl;
//     system("pause");
//     return 0;
// }
// 整数拆分
int integerBreak(int n)
{
    vector<int> dp(n + 1, 1);
    dp[2] = 1;
    for (int i = 3; i <= n; i++)
        for (int j = 1; j < i; j++)
        {
            dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));
        }
    return dp[n];
}

// int main()
// {
//     cout << integerBreak(10) << endl;
//     system("pause");
//     return 0;
// }

// 不同路径1
int uniquePaths(int m, int n)
{
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = 0;
    for (int i = 1; i < m; i++)
    {
        dp[i][0] = 1;
    }
    for (int j = 1; j < n; j++)
    {
        dp[0][j] = 1;
    }
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            cout << dp[i][j] << " ";
        }
    cout << endl;

    return dp[m - 1][n - 1];
}

// int main()
// {
//     cout << uniquePaths(3, 7) << endl;
//     system("pause");
//     return 0;
// }

// 不同路径2
int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
{
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++)
    {
        if (obstacleGrid[i][0] == 1)
        {
            dp[i][0] = 0;
            break;
        }
        else
            dp[i][0] = 1;
    }
    for (int j = 0; j < n; j++)
    {
        if (obstacleGrid[0][j] == 1)
        {
            dp[0][j] = 0;
            break;
        }
        else
            dp[0][j] = 1;
    }
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
        {
            if (obstacleGrid[i][j] == 1)
                dp[i][j] = 0;
            else
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            // cout << dp[i][j] << " ";
        }
    // cout << endl;

    return dp[m - 1][n - 1];
}

// int main()
// {
//     vector<vector<int>> obstacleGrid = {{1, 0}};
//     cout << uniquePathsWithObstacles(obstacleGrid) << endl;
//     system("pause");
//     return 0;
// }

// 三角形的最小路径和
int minimumTotal(vector<vector<int>> &triangle)
{
    int m = triangle.size();
    int n = triangle[m - 1].size();

    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = triangle[0][0];

    for (int i = 1; i < m; i++)
        for (int j = 0; j < triangle[i].size(); j++)
        {
            if (j == 0)
                dp[i][j] = dp[i - 1][0] + triangle[i][j];
            else if (j == triangle[i].size() - 1)
                dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
            else
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j];
        }
    // int ans = INT_MAX;
    // for (int j = 0; j < triangle[m - 1].size(); j++)
    //     ans = min(dp[m - 1][j], ans);

    // return ans;
    return *min_element(dp[m - 1].begin(), dp[m - 1].end());
}

// int main()
// {
//     vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
//     cout << minimumTotal(triangle) << endl;
//     system("pause");
//     return 0;
// }

// 下降路径最小和2
int minFallingPathSum(vector<vector<int>> &grid)
{
    int n = grid.size();

    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++)
        dp[0][i] = grid[0][i];

    for (int i = 1; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            for (int m = 0; m < n; m++)
            {
                if (j != m)
                    dp[i][j] = min(dp[i][j], grid[i][j] + dp[i - 1][m]);
            }
        }
    return *min_element(dp[n - 1].begin(), dp[n - 1].end());
}

// int main()
// {
//     vector<vector<int>> grid = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//     cout << minFallingPathSum(grid) << endl;
//     system("pause");
//     return 0;
// }

// 最大正方形
int maximalSquare(vector<vector<char>> &matrix)
{
    return 0;
}

int bag01_2(vector<int> weight, vector<int> value, int bagweight)
{
    int n = weight.size();
    // 注意！
    vector<vector<int>> dp(n, vector<int>(bagweight + 1, 0));

    // 初始化第一行
    for (int j = 0; j <= bagweight; j++)
    {
        if (j >= weight[0])
            dp[0][j] = value[0];
    }
    // 先遍历物品，再遍历背包！！
    for (int i = 1; i < n; i++)
        for (int j = 0; j <= bagweight; j++)
        {
            if (j - weight[i] < 0)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - weight[i]] + value[i]);
        }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= bagweight; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    // 注意！
    return dp[n - 1][bagweight];
}

int bag01(vector<int> weight, vector<int> value, int bagweight)
{
    int n = weight.size();
    // 注意！
    vector<int> dp(bagweight + 1, 0);

    // 先遍历物品，再遍历背包！！
    for (int i = 0; i < n; i++)                      // 遍历物品
        for (int j = bagweight; j >= weight[i]; j--) // 逆序遍历背包
        {

            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }

    return dp[bagweight];
}

// int main()
// {
//     vector<int> weight = {1, 3, 4};
//     vector<int> value = {15, 20, 30};
//     cout << bag01(weight, value, 4) << endl;
//     system("pause");
//     return 0;
// }

// 分割等和子集
bool canPartition(vector<int> &nums)
{
    int sum = 0;
    for (auto num : nums)
        sum += num;
    if (sum % 2 != 0)
        return false;
    int n = nums.size();
    int tar = sum / 2;
    vector<int> dp(tar + 1, 0);
    for (int i = 0; i < n; i++)
        for (int j = tar; j >= nums[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
        }
    return dp[tar] == tar;
}

// int main()
// {
//     vector<int> nums = {1, 5, 11, 5};
//     cout << canPartition(nums) << endl;
//     system("pause");
//     return 0;
// }
// 最后一块石头的重量2
int lastStoneWeightII(vector<int> &stones)
{
    int sum = 0;
    for (auto num : stones)
        sum += num;
    int n = stones.size();
    int tar = sum / 2;
    vector<int> dp(tar + 1, 0);
    for (int i = 0; i < n; i++)
        for (int j = tar; j >= stones[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
        }

    return sum - 2 * dp[tar];
}

// int main()
// {
//     vector<int> stones = {2, 7, 4, 1, 8, 1};
//     cout << lastStoneWeightII(stones) << endl;
//     system("pause");
//     return 0;
// }

// 目标和
// 装满背包有多少种方法？
int findTargetSumWays(vector<int> &nums, int target)
{
    int sum = 0;
    int n = nums.size();
    for (auto num : nums)
        sum += num;
    if (abs(target) > sum)
        return 0;
    if ((sum + target) % 2 == 1)
        return 0;
    int bagweight = (sum + target) / 2;

    vector<int> dp(bagweight + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = bagweight; j >= nums[i]; j--)
        {
            dp[j] += dp[j - nums[i]];
            cout << dp[j] << " ";
        }
        cout << endl;
    }

    return dp[bagweight];
}

// int main()
// {
//     vector<int> nums = {1, 1, 1, 1};
//     cout << findTargetSumWays(nums, 3) << endl;
//     system("pause");
//     return 0;
// }

// 一和零
int findMaxForm(vector<string> &strs, int m, int n)
{
    int len = strs.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < len; i++)
    {
        int zeros = 0, ones = 0;
        for (auto c : strs[i])
        {
            if (c == '0')
                zeros++;
            else
                ones++;
        }
        for (int j = m; j >= zeros; j--)
        {
            for (int k = n; k >= ones; k--)
            {
                dp[j][k] = max(dp[j][k], dp[j - zeros][k - ones] + 1);
            }
        }
    }
    return dp[m][n];
}

// 完全背包模板
int bagall(vector<int> weight, vector<int> value, int bagweight)
{
    int n = weight.size();
    // 注意！
    vector<int> dp(bagweight + 1, 0);

    // 先遍历物品，再遍历背包！！
    for (int i = 0; i < n; i++)                      // 遍历物品
        for (int j = weight[i]; j <= bagweight; j++) // 逆序遍历背包
        {

            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }

    return dp[bagweight];
}

// 零钱兑换1
int coinChange(vector<int> &coins, int amount)
{
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int i = 0; i < coins.size(); i++)
        for (int j = coins[i]; j <= amount; j++)
        {
            // if (dp[j - coins[i]] != INT_MAX)
            dp[j] = min(dp[j], dp[j - coins[i]] + 1);
        }
    if (dp[amount] == amount + 1)
        return -1;

    for (auto i : dp)
        cout << i << " ";
    cout << endl;
    return dp[amount];
}

// 零钱兑换2
int change(int amount, vector<int> &coins)
{
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for (int j = 0; j <= amount; j++)
    {
        for (int i = 0; i < coins.size(); i++)
        {
            if (j - coins[i] >= 0)
                dp[j] += dp[j - coins[i]];
            cout << dp[j] << " ";
        }
        cout << endl;
    }
    return dp[amount];
}

// 组合总和4
int combinationSum4(vector<int> &nums, int target)
{
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    for (int j = 0; j <= target; j++)
        for (int i = 0; i < nums.size(); i++)
        {
            if (j - nums[i] >= 0)
                dp[j] += dp[j - nums[i]];
            // cout << dp[j] << " ";
        }
    return dp[target];
}

// int main()
// {
//     vector<int> coins = {1, 2, 3};
//     cout << combinationSum4(coins, 4) << endl;
//     system("pause");
//     return 0;
// }

// 完全平方数
int numSquares(int n)
{
    vector<int> dp(n + 1, n);
    dp[0] = 0;
    for (int i = 0; i * i <= n; i++)
        for (int j = i * i; j <= n; j++)
        {

            dp[j] = min(dp[j], dp[j - i * i] + 1);
        }

    // for (auto i : dp)
    //     cout << i << " ";
    return dp[n];
}

// int main()
// {
//     cout << numSquares(13) << endl;
//     system("pause");
//     return 0;
// }

// 单词拆分
bool wordBreak(string s, vector<string> &wordDict)
{
    int n = s.size();
    vector<int> dp(n + 1, 0);
    unordered_set<string> wordSet(wordDict.begin(), wordDict.end());

    dp[0] = 1;
    // 遍历背包
    for (int j = 1; j <= n; j++)

        // 遍历物品
        for (int i = 0; i < j; i++)
        {

            if (dp[i] && wordSet.find(s.substr(i, j - i)) != wordSet.end())
            {
                dp[j] = true;
            }
        }

    for (auto i : dp)
        cout << i << " ";
    cout << endl;
    return dp[n];
}

// int main()
// {
//     string s = "applepenapple";
//     vector<string> wordDict = {"apple", "pen"};
//     cout << wordBreak(s, wordDict) << endl;
//     system("pause");
//     return 0;
// }

/// @brief 打家劫舍系列
/// @param nums
/// @return

// 打家劫舍1
int rob(vector<int> &nums)
{
    int n = nums.size();
    if (n == 1)
        return nums[0];
    vector<int> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = nums[0];
    dp[2] = max(nums[0], nums[1]);
    for (int i = 3; i <= n; i++)
    {
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]);
    }
    return dp[n];
}

// 打家劫舍2
int rob2(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return nums[0];
    vector<int> nums1 = vector<int>(nums.begin(), nums.end() - 1);
    vector<int> nums2 = vector<int>(nums.begin() + 1, nums.end());
    int ans1 = rob(nums1);
    int ans2 = rob(nums2);
    return max(ans1, ans2);
}

// int main()
// {
//     vector<int> nums = {2, 3, 2};
//     cout << rob2(nums) << endl;
//     system("pause");
//     return 0;
// }

// 打家劫舍3
int rob3(TreeNode *root)
{
}