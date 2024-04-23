

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
using namespace std;

// 动态规划的的四个解题步骤是：
//
// 1.定义子问题
// 2.写出子问题的递推关系
// 3.确定 DP 数组的计算顺序
// 4.空间优化(可选)

// 1.确定dp数组（dp table）以及下标的含义
// 2.确定递推公式
// 3.dp数组如何初始化
// 4.确定遍历顺序
// 5.举例推导dp数组

/// <summary>
/// 先从最经典的爬楼梯开始
/// </summary>
int climbStairs(int n)
{
	if (n <= 2)
		return n;

	vector<int> dp(n + 1, 0);
	dp[1] = 1;
	dp[2] = 2;

	for (int i = 3; i <= n; i++)
	{
		dp[i] = dp[i - 1] + dp[i - 2];
	}

	return dp[n];
}

/// <summary>
/// 斐波那契数列
/// </summary>
/// 在代码中等价爬楼梯
int fib(int n)
{
	if (n <= 1)
		return n;
	int first = 0;
	int second = 1;
	for (int i = 2; i <= n; i++)
	{

		int third = first + second;
		first = second;
		second = third;
	}
	return second;
}

/// <summary>
/// 第N个斐波那契数
/// </summary>
int tribonacci(int n)
{
	if (n == 0)
		return 0;
	if (n == 1 || n == 2)
		return 1;

	vector<int> dp(n + 1, 0);
	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 1;

	for (int i = 3; i <= n; i++)
	{
		dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
	}

	return dp[n];
}

/// <summary>
/// 使用最小花费爬楼梯
/// </summary>
int minCostClimbingStairs(vector<int> &cost)
{
	int n = cost.size();
	vector<int> dp(n + 1, 0);
	dp[0] = dp[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
	}
	return dp[n];
}

/// <summary>
/// 打家劫舍1
///</summary>
int rob(vector<int> &nums)
{
	int n = nums.size();
	if (n == 1)
		return nums[0];

	vector<int> dp(n + 1, 0);
	dp[0] = 0;
	dp[1] = nums[0];

	for (int i = 2; i <= n; i++)
	{
		dp[i] = max(dp[i - 2] + nums[i - 1], dp[i - 1]);
	}

	return dp[n];
}

/// <summary>
/// 删除并获得点数
/// </summary>
/// 数组 dp 中的每个元素 dp[i] 表示当选择数字 i 时可以获得的最大点数。
int deleteAndEarn(vector<int> &nums)
{
	if (nums.empty())
		return 0;

	int max_element = *std::max_element(nums.begin(), nums.end());
	vector<int> count(max_element + 1, 0);

	for (int num : nums)
	{
		count[num]++;
	}

	vector<int> dp(max_element + 1, 0);
	dp[0] = 0;
	dp[1] = count[1] * 1;

	for (int i = 2; i <= max_element; i++)
	{
		dp[i] = max(dp[i - 1], dp[i - 2] + count[i] * i);
	}

	return max(dp[max_element], dp[max_element - 1]);
}

/// <summary>
/// 解法二，这题就是打家劫舍？！
/// </summary>
int deleteAndEarn2(vector<int> &nums)
{
	int maxVal = 0;
	for (int val : nums)
	{
		maxVal = max(maxVal, val);
	}
	vector<int> sum(maxVal + 1);
	for (int val : nums)
	{
		sum[val] += val;
	}
	return rob(sum);
}

// int main() {
//
//	vector<int>nums = { 1,2,3,1 };
//	int ans = rob(nums);
//	cout << ans;
//	return 0;
// }

/// <summary>
/// 不同路径
/// </summary>
int uniquePaths(int m, int n)
{
	vector<vector<int>> dp(m, vector<int>(n, 0));
	dp[0][0] = 0;
	for (int i = 0; i < m; i++)
	{
		dp[i][0] = 1;
	}
	for (int j = 0; j < n; j++)
	{
		dp[0][j] = 1;
	}
	for (int i = 1; i < m; i++)
		for (int j = 1; j < n; j++)
		{
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}

	// for (int i = 0; i < m; i++)
	//	for (int j = 0; j < n; j++)
	//	{
	//		cout << dp[i][j] << " ";
	//	}

	return dp[m - 1][n - 1];
}

/// <summary>
/// 最小路径和
/// </summary>
int minPathSum(vector<vector<int>> &grid)
{
	int m = grid.size();
	int n = grid[0].size();
	vector<vector<int>> dp(m, vector<int>(n, 0));
	dp[0][0] = grid[0][0];
	for (int i = 1; i < m; i++)
	{
		dp[i][0] = dp[i - 1][0] + grid[i][0];
	}
	for (int j = 1; j < n; j++)
	{
		dp[0][j] = dp[0][j - 1] + grid[0][j];
	}
	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
		}
	}
	return dp[m - 1][n - 1];

	// for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < m; j++)
	//	{
	//		cout << grid[i][j] << " ";
	//	}
	//	cout << endl;

	//}
	// cout << "************" << endl;

	// for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < m; j++)
	//	{
	//		cout << dp[i][j] << " ";
	//	}
	//	cout << endl;

	//}
}

/// <summary>
/// 不同路径2----有障碍物的情况
/// </summary>
/// 这个和普通的情况基本上一样，把有障碍物的地方设为0就行
int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
{
	int m = obstacleGrid.size();
	int n = obstacleGrid[0].size();
	vector<vector<int>> dp(m, vector<int>(n, 0));
	dp[0][0] = 0;
	for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++)
	{
		dp[i][0] = 1;
	}
	for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++)
	{
		dp[0][j] = 1;
	}
	for (int i = 1; i < m; i++)
		for (int j = 1; j < n; j++)
		{
			if (obstacleGrid[i][j] == 1)
				dp[i][j] = 0;
			else
			{
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}

	// for (int i = 0; i < m; i++)
	//	for (int j = 0; j < n; j++)
	//	{
	//		cout << dp[i][j] << " ";
	//	}

	return dp[m - 1][n - 1];
}

/// <summary>
/// 三角形最小路径和
/// </summary>
/// 从上到下不行，这样找的是局部最小值，属于贪心算法，于是考虑从下到上
// int minimumTotal(vector<vector<int>>& triangle) {
//	int m = triangle.size();
//	int n = triangle[0].size();
//	vector<int>dp(m, 0);
//	dp[0] = triangle[0][0];
//	int j = 0;
//	for (int i = 1; i < m; i++)
//	{
//		if (triangle[i][j] > triangle[i][j + 1]) {
//		dp[i] = dp[i - 1] +triangle[i][j+1];
//		j = j + 1;
//		}
//		else
//			dp[i] = dp[i - 1] + triangle[i][j];
//
//	}
//	for (int i = 0; i < m; i++)
//	{
//		cout << dp[i] << " ";
//	}
//	return dp[m - 1];
// }

/// <summary>
/// dp[0]是不断更新的，dp数组代表第i层到达最后一层的最短路径
/// </summary>
/// <param name="triangle"></param>
/// <returns></returns>
int minimumTotal(vector<vector<int>> &triangle)
{
	int m = triangle.size();
	vector<int> dp(triangle.back());
	for (int i = m - 2; i >= 0; i--)
	{

		for (int j = 0; j <= i; j++)
			dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];

		for (int i = 0; i < m; i++)
		{
			cout << dp[i] << " ";
		}
		cout << endl;
	}

	return dp[0];
}

/// <summary>
/// 下降路径的最小和
/// </summary>
/// 这个和上面一题基本上一模一样，看看能不能自己写出来
/// 写出来了！这道题必须得用O(n2)的空间复杂度，因为矩形和三角形不一样，三角形刚好j要用到的下一个数，没有被之前的动过，两个数处理为一个结果，这样的话，第二个数仍能保持下一行的数据
int minFallingPathSum(vector<vector<int>> &matrix)
{
	int n = matrix.size();
	vector<vector<int>> dp = matrix;
	for (int i = n - 2; i >= 0; i--)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == 0)
				dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + matrix[i][j];
			else if (j == n - 1)
				dp[i][j] = min(dp[i + 1][j], dp[i + 1][j - 1]) + matrix[i][j];
			else
				dp[i][j] = min(dp[i + 1][j + 1], min(dp[i + 1][j], dp[i + 1][j - 1])) + matrix[i][j];
		}
	}
	// for (int i = 0; i < n; i++)
	//{
	//	cout << dp[i] << " ";
	// }
	// cout << endl;
	// }
	int ans = INT_MAX;
	for (int i = 0, j = 0; j < n; j++)
	{
		ans = min(ans, dp[0][j]);
	}
	return ans;
}

/// <summary>
/// 最大正方形
/// </summary>
/// 用 dp(i,j)表示以 (i,j)为右下角，且只包含 1 的正方形的边长最大值。
int maximalSquare(vector<vector<char>> &matrix)
{
	int m = matrix.size();
	int n = matrix[0].size();
	int maxSide = 0;
	vector<vector<int>> dp(m, vector<int>(n));
	for (int i = 0; i < m; i++)
	{
		if (matrix[i][0] == '0')
			dp[i][0] = 0;
		else
			dp[i][0] = 1;
		maxSide = max(maxSide, dp[i][0]);
	}
	for (int i = 0; i < n; i++)
	{
		if (matrix[0][i] == '0')
			dp[0][i] = 0;
		else
			dp[0][i] = 1;
		maxSide = max(maxSide, dp[0][i]);
	}
	for (int i = 1; i < m; i++)
		for (int j = 1; j < n; j++)
		{
			if (matrix[i][j] == '0')
				dp[i][j] = 0;
			else
			{
				dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
			}
			maxSide = max(maxSide, dp[i][j]);
		}

	return maxSide * maxSide;
}

// int main() {
//	//vector<vector<int>> triangle = { {2,1,3} ,{6,5,4},{7,8,9}};
//	///*int ans = uniquePaths(3, 3);*/
//	////int ans = uniquePathsWithObstacles(grid);
//	//int ans = minFallingPathSum(triangle);
//	vector<vector<char>>matrix = { {'1', '0', '1', '0', '0'},{'1', '0', '1', '1', '1'},{'1', '1', '1', '1', '1'},{'1', '0', '0', '1', '0'} };
//	int ans = maximalSquare(matrix);
//	cout << ans;
//	return 0;
// }

/// <summary>
/// 整数拆分
/// </summary>
int integerBreak(int n)
{
	vector<int> dp(n + 1, 0);
	dp[2] = 1;
	for (int i = 3; i <= n; i++)
		for (int j = 1; j < i; j++)
		{
			dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
		}

	return dp[n];
}

/// <summary>
/// 不同的二叉搜索树
/// </summary>
int numTrees(int n)
{
	vector<int> dp(n + 1, 0);
	dp[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			dp[i] += dp[j - 1] * dp[i - j];
		}
	}
	return dp[n];
}

///****************************
/// 动态规划在字符串中的应用
///****************************

/// <summary>
/// 最长回文子串
/// </summary>
/// 动态规划解决
string longestPalindrome(string s)
{
	int n = s.size();
	if (n <= 1)
	{
		return s;
	}

	vector<vector<bool>> dp(n, vector<bool>(n, false));

	// 初始化长度为1的回文子串
	for (int i = 0; i < n; i++)
	{
		dp[i][i] = true;
	}

	int start = 0;	// 记录最长回文子串的起始位置
	int maxLen = 1; // 记录最长回文子串的长度

	// 动态规划填表
	for (int len = 2; len <= n; len++)
	{
		for (int i = 0; i < n - len + 1; i++)
		{
			int j = i + len - 1;

			if (s[i] == s[j])
			{
				if (len == 2 || dp[i + 1][j - 1])
				{
					dp[i][j] = true;
					if (len > maxLen)
					{
						maxLen = len;
						start = i;
					}
				}
			}
		}
	}

	return s.substr(start, maxLen);
}

// int main() {
//
//	string s = "abcba";
//	string ans = longestPalindrome(s);
//	for (auto an : ans)
//		cout << an;
//
// }

/// <summary>
/// 0-1背包问题！！
/// </summary>
/// dp[i][j]的含义：从下标为[0-i]的物品里任意取，放进容量为j的背包，价值总和最大是多少。
int bag01(vector<int> weight, vector<int> value, int bagweight)
{
	vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));

	// 初始化第一行，从大于等于bagweight开始
	for (int i = weight[0]; i <= bagweight; i++)
	{
		dp[0][i] = value[0];
	}

	for (int i = 1; i < weight.size(); i++)
		for (int j = 1; j <= bagweight; j++)
		{
			if (weight[i] > j)
				dp[i][j] = dp[i - 1][j];
			else
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
		}

	// 打印dp数组
	for (int i = 0; i < weight.size(); i++)
	{
		for (int j = 0; j <= bagweight; j++)
		{
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	return dp[weight.size() - 1][bagweight];
}

/// <summary>
/// 使用滚动数组优化，将二位转化为一维
/// </summary>
int bag01_1(vector<int> weight, vector<int> value, int bagweight)
{
	vector<int> dp(bagweight + 1, 0);

	// 初始化第一行，从大于等于bagweight开始
	for (int i = weight[0]; i <= bagweight; i++)
	{
		dp[i] = value[0];
	}
	// 先遍历物品，再遍历背包，顺序不可以换，如果遍历背包容量放在上一层，那么每个dp[j]就只会放入一个物品，即：背包里只放入了一个物品。
	// 倒序遍历的原因是，本质上还是一个对二维数组的遍历，并且右下角的值依赖上一层左上角的值，因此需要保证左边的值仍然是上一层的，从右向左覆盖。
	for (int i = 0; i < weight.size(); i++)
		for (int j = bagweight; j >= weight[i]; j--)
		{
			dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
		}

	// 打印dp数组
	for (int i = 0; i <= bagweight; i++)
	{

		cout << dp[i] << " ";
	}
	cout << endl;
	return dp[bagweight];
}

// int main() {
//	vector<int>weight = {1,3,4};
//	vector<int>value = {15,20,30};
//	int ans = bag01_1(weight, value,4);
//	cout << ans;
// }

/// <summary>
/// 完全平方数
/// </summary>
/// 这道题和上面的整数拆分基本上一模一样
/// 这个代码是我自己写的，使用二维数组模拟01背包问题，虽然有点复杂，但是我想下面我会进行优化的！
int numSquares(int n)
{
	int squareRoot = static_cast<int>(sqrt(n));
	vector<vector<int>> dp(squareRoot + 1, vector<int>(n + 1, 0));

	dp[0][0] = 0;

	for (int i = 1; i <= n; i++)
	{
		dp[0][i] = i;
	}

	for (int j = 1; j <= n; j++)
	{
		for (int i = 1; i * i <= n; i++)
		{
			if (j - i * i >= 0)
				dp[i][j] = min(dp[i - 1][j], dp[i][j - i * i] + 1);
			else
			{
				dp[i][j] = dp[i - 1][j];
			}
		}
	}

	// 打印dp数组
	for (int i = 1; i * i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	return dp[squareRoot][n];
}

/// <summary>
/// 开始进行优化
/// </summary>

int numSquares1(int n)
{
	vector<int> dp(n + 1, INT_MAX);

	dp[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j * j <= i; j++)
		{
			dp[i] = min(dp[i], dp[i - j * j] + 1);
		}
	}

	// 打印dp数组
	for (int j = 0; j <= n; j++)
	{
		cout << dp[j] << " ";
	}
	cout << endl;

	return dp[n];
}

// int main() {
//	int ans = numSquares1(10);
//	cout << ans;
// }

/// <summary>
/// 分割等和子集
/// </summary>
/// dp[j]表示 背包总容量（所能装的总重量）是j，放进物品后，背的最大重量为dp[j]。
bool canPartition(vector<int> &nums)
{
	int sum = 0;
	int n = nums.size();
	vector<int> dp(10001, 0);
	for (auto num : nums)
		sum += num;

	if (sum % 2 == 1)
		return false;
	int target = sum / 2;

	for (int i = 0; i < n; i++)
		for (int j = target; j >= nums[i]; j--) // 每一个元素一定是不可重复放入，所以从大到小遍历
		{
			dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
		}
	// 集合中的元素正好可以凑成总和target
	if (dp[target] == target)
		return true;
	return false;
}

// int main() {
//	vector<int>nums = { 1,5,11,5 };
//	bool ans = canPartition(nums);
//	cout << ans;
// }

/// <summary>
/// 最后一块石头的重量2
/// </summary>
/// 本题的关键就是转化为一个重要的概念，把石头尽可能分为相同重量的两堆，这样的话，这个题目简直就跟上面的题目一模一样了
int lastStoneWeightII(vector<int> &stones)
{
	int sum = 0;
	int n = stones.size();
	vector<int> dp(1501, 0);
	for (auto num : stones)
		sum += num;

	int target = sum / 2;

	for (int i = 0; i < n; i++)
		for (int j = target; j >= stones[i]; j--) // 每一个元素一定是不可重复放入，所以从大到小遍历
		{
			dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
		}
	// 集合中的元素正好可以凑成总和target
	return sum - dp[target] - dp[target];
}

/// <summary>
/// 目标和
/// </summary>
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
	int left = (sum + target) / 2;
	vector<int> dp(left + 1, 0);
	dp[0] = 1;
	for (int i = 0; i < n; i++)
		for (int j = left; j >= nums[i]; j--)
		{
			dp[j] += dp[j - nums[i]];
		}
	return dp[left];
}

/// <summary>
/// 一和零
/// </summary>
/// 这道题刚开始给我看蒙了，相当于背包有两个维度的0-1背包，最好的方法是先写出一维的情况，二维情况就清楚了
int findMaxForm(vector<string> &strs, int m, int n)
{
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
	for (auto str : strs)
	{
		int count0 = 0;
		int count1 = 0;
		for (auto st : str)
		{
			if (st == '0')
				count0++;
			if (st == '1')
				count1++;
		}

		for (int i = m; i >= count0; i--)
			for (int j = n; j >= count1; j--)
			{
				dp[i][j] = max(dp[i][j], dp[i - count0][j - count1] + 1);
			}
	}
	// for (auto arr : arr0) cout << arr << " ";
	// cout << endl;
	// for (auto arr : arr1) cout << arr << " ";

	return dp[m][n];
}

// int main() {
//	vector<string>nums = { "10", "0001", "111001", "1", "0" };
//	int ans = findMaxForm(nums,1,1);
// }

/// 总结
// 纯 0 - 1 背包(opens new window)是求 给定背包容量 装满背包 的最大价值是多少。

// 416. 分割等和子集(opens new window)是求 给定背包容量，能不能装满这个背包。

// 1049. 最后一块石头的重量 II(opens new window)是求 给定背包容量，尽可能装，最多能装多少

// 494. 目标和(opens new window)是求 给定背包容量，装满背包有多少种方法。

// 一和零  是求 给定背包容量(二维)，装满背包最多有多少个物品。

/// <summary>
/// 完全背包问题！
/// 与0-1背包的唯一不同就是，每件物品都可以多次放入背包，代码与之对应的就是，背包应该从小到大进行遍历
/// </summary>
int bagCom(vector<int> weight, vector<int> value, int bagweight)
{
	vector<int> dp(bagweight + 1, 0);

	// 初始化第一行，从大于等于bagweight开始
	for (int i = weight[0]; i <= bagweight; i++)
	{
		dp[i] = value[0];
	}
	for (int i = 0; i < weight.size(); i++)
		// 不同之处！！
		for (int j = weight[i]; j <= bagweight; j++)
		{
			dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
		}

	// 打印dp数组
	for (int i = 0; i <= bagweight; i++)
	{

		cout << dp[i] << " ";
	}
	cout << endl;
	return dp[bagweight];
}

/// <summary>
/// 零钱兑换2
/// </summary>
int change(int amount, vector<int> &coins)
{
	vector<int> dp(amount + 1, 0);
	// 这里必须是1，需要体会一下
	dp[0] = 1;
	for (int i = 0; i < coins.size(); i++)
		for (int j = coins[i]; j <= amount; j++)
		{
			dp[j] += dp[j - coins[i]];
		}

	return dp[amount];
}

/// <summary>
/// 组合总和
/// </summary>
/// 体会一下，组合和排序有哪些区别
/// 组合不强调顺序，而排列不同的顺序是不同的排列，所以本题是排列问题
///
int combinationSum4(vector<int> &nums, int target)
{
	vector<int> dp(target + 1, 0);
	// 这里必须是1，需要体会一下
	dp[0] = 1;
	for (int i = 0; i <= target; i++)
		for (int j = 0; j < nums.size(); j++)
		{
			if (nums[j] <= i)
				dp[i] += dp[i - nums[j]];
		}

	for (auto d : dp)
		cout << d << " ";
	return dp[target];
}

// int main() {
//	vector<int>nums = {1,2,3};
//	int ans = combinationSum4(nums, 4);
//	return 0;
// }

// 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
// 每次你可以爬至多m(1 <= m < n)个台阶。你有多少种不同的方法可以爬到楼顶呢？
//	注意：给定 n 是一个正整数。

int climbStairsplus(int m, int n)
{
	vector<int> dp(n + 1, 0);
	// 这里必须是1，需要体会一下
	dp[0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < m; j++)
		{
			if (j <= i)
				dp[i] += dp[i - j];
		}

	return dp[n];
}

/// <summary>
/// 零钱兑换
/// </summary>
/// 这个相当于给定价值，求满足该价值的背包的最小物品数量
/// dp[j]含义是，总金额为j时，凑出给定价值的最小数量
int coinChange(vector<int> &coins, int amount)
{
	vector<int> dp(amount + 1, INT_MAX);
	dp[0] = 0;
	for (int i = 0; i < coins.size(); i++)
		for (int j = coins[i]; j <= amount; j++)
		{
			if (dp[j - coins[i]] != INT_MAX)
				dp[j] = min(dp[j], dp[j - coins[i]] + 1);
		}
	for (auto d : dp)
		cout << d << " ";
	if (dp[amount] == INT_MAX)
		return -1;
	return dp[amount];
}
// int main() {
//	vector<int>nums = {2};
//	int ans = coinChange(nums, 3);
//	return 0;
// }

/// <summary>
/// 单词拆分
/// </summary>
bool wordBreak(string s, vector<string> &wordDict)
{
	int n = s.size();
	unordered_set<string> wordSet(wordDict.begin(), wordDict.end());

	vector<bool> dp(n + 1, false);
	dp[0] = true;

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (dp[j] && wordSet.count(s.substr(j, i - j)))
			{
				dp[i] = true;
				break;
			}
		}
	}

	return dp[n];
}

/// <summary>
/// 解决智力问题
/// </summary>
/// dp[j]代表解决前j道题目获得的最高分数
/// 这个太难了，前面题目的选择决定了后面的结果  ，要用到无后效性，啥玩意啊
long long mostPoints(vector<vector<int>> &questions)
{
	int n = questions.size();
	vector<long long> dp(n + 1, 0);
	long long ans = 0;
	for (int i = 0; i < questions.size(); i++)
	{
		dp[i] = questions[i][0];
		for (int j = 0; j < i; j++)
		{
			if (i - j > questions[j][1])
				dp[i] = max(dp[i], dp[j] + questions[i][0]);
		}
		ans = max(ans, dp[i]);
	}

	return ans;
}

// int main() {
//	vector<vector<int>>nums = { {3,2},{4,3},{4,4},{2,5} };
//	long long ans = mostPoints(nums);
//	return 0;
// }

/// <summary>
/// 打家劫舍Ⅱ
/// </summary>
/// 这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。
/// 同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。
/// 这道题可以转化为两个基础的打家劫舍，因为首尾相连的话，就相当于首和尾只能取一个，按照这个思路，取两次结果的最大，就是最终的结果
int rob2(vector<int> &nums)
{
	int n = nums.size();
	if (n == 0)
	{
		return 0;
	}
	if (n == 1)
	{
		return nums[0];
	}

	vector<int> dp1(n, 0);
	vector<int> dp2(n + 1, 0);
	dp1[0] = 0;
	dp1[1] = nums[0];
	dp2[0] = 0;
	dp2[1] = 0;
	// 从0:n-1个房子dp
	for (int i = 2; i <= n - 1; i++)
	{
		dp1[i] = max(dp1[i - 1], dp1[i - 2] + nums[i - 1]);
	}
	// 从1:n个房子dp
	for (int i = 2; i <= n; i++)
	{
		dp2[i] = max(dp2[i - 1], dp2[i - 2] + nums[i - 1]);
	}

	return max(dp1[n - 1], dp2[n]);
}

/// <summary>
/// 买股票的最佳时机1
/// </summary>
/// <param name="prices"></param>
/// <returns></returns>
int maxProfit(vector<int> &prices)
{
	return 0;
}

/// <summary>
/// 最低票价
/// </summary>
/// 我们定义dp数组 f ，其中 f[i] 表示达到 day[i] 所需要的最低消费。
/// 根据题意，我们有三种方法可以到达 day[i]， 假设我们是从 days[j] 到达 day[i] 。
int mincostTickets(vector<int> &days, vector<int> &costs)
{
	int n = days.size();
	vector<int> dp(days.size() + 1, 0);
	dp[0] = 0;
	for (int i = 0; i < n; i++)
	{

		dp[i + 1] = dp[i] + costs[0];
		for (int j = i - 1; j >= 0; j--)
		{
			int dif = days[i] - days[j];
			if (dif < 7)
				dp[i + 1] = min(dp[i + 1], dp[j] + costs[1]);
			if (dif < 30)
				dp[i + 1] = min(dp[i + 1], dp[j] + costs[2]);
			else
				break;
		}
	}
	return dp[n];
}

/// <summary>
/// 跳跃游戏4
/// </summary>
/// 我的第一个思路是用动态规划解答。dp[i]表示走到第i个元素时候的最大得分。这样的话，走到下一个元素的最大的分
/// 要么选择当前元素，要么是从之前的dp[i]中跳转到的。之前简单情况下，直接选择是否取当前元素就可以了。但是这道题可以跳跃k步，是不是更复杂一些？
/// 解决办法，再加一个for循环循环k，就好了！成功运行，但是只通过部分示例。。。
/// 原因是超过时间限制了！！！！想想如何优化
int maxResult(vector<int> &nums, int k)
{
	int n = nums.size();
	vector<int> dp(n, 0);
	dp[0] = nums[0];
	for (int i = 1; i < n; i++)
		for (int j = 1; j <= k; j++)
		{
			if (i - j >= 0)
				dp[i] = max(dp[i - 1], dp[i - j]) + nums[i];
			else
				break;
		}

	for (auto d : dp)
		cout << d << " ";
	cout << endl;
	return dp[n - 1];
}

/// <summary>
/// 没想出来，看了一下题解，转移来自定长区间，可以使用单调队列优化dp场景。
/// 之前没有接触过单调队列，单调队列对于滑动窗口很有用，值得了解一下。接下来做几道单调队列的题目
/// 先贴一下官方代码
int maxResult1(vector<int> &nums, int k)
{
	int n = nums.size();
	vector<int> dp(n);
	dp[0] = nums[0];
	deque<int> queue;
	queue.push_back(0);
	for (int i = 1; i < n; i++)
	{
		while (!queue.empty() && queue.front() < i - k)
		{
			queue.pop_front();
		}
		dp[i] = dp[queue.front()] + nums[i];
		while (!queue.empty() && dp[queue.back()] <= dp[i])
		{
			queue.pop_back();
		}
		queue.push_back(i);
	}
	return dp[n - 1];
}

// int main() {
//	vector<int>nums = { 1,-1,-2,4,-7,3 };
//	int ans = maxResult1(nums, 2);
//	cout << ans << endl;
//	return 0;
// }