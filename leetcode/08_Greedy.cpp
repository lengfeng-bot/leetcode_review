#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// 分发饼干
int findContentChildren(vector<int> &g, vector<int> &s)
{
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());

    int a = 0, b = 0;
    int num = 0;
    while (a < g.size() && b < s.size())
    {
        if (g[a] <= s[b])
        {
            num++;
            a++;
            b++;
        }
        else
            b++;
    }
    return num;
}

// 最大子数组的和
int maxSubArray(vector<int> &nums)
{
    int n = nums.size();
    int sum = 0;
    int maxsum = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        sum += nums[i];
        if (sum > maxsum)
            maxsum = sum;

        if (sum <= 0)
            sum = 0;
    }
    return maxsum;
}

// 分发糖果
int candy(vector<int> &ratings)
{
    int n = ratings.size();
    if (n == 1)
        return 1;
    vector<int> left(n, 1);
    vector<int> right(n, 1);

    for (int i = 1; i < n; i++)
    {
        if (ratings[i] > ratings[i - 1])
            left[i] = left[i - 1] + 1;
    }

    for (int i = n - 2; i >= 0; i--)
    {
        if (ratings[i] > ratings[i + 1])
            right[i] = right[i + 1] + 1;
    }
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++)
    {
        ans[i] = max(left[i], right[i]);
        cout << ans[i] << " ";
    }
    cout << endl;
    return accumulate(ans.begin(), ans.end(), 0);
}

// int main()
// {

//     vector<int> ratings = {1, 0, 2};
//     cout << candy(ratings) << endl;
//     system("pause");

//     return 0;
// }

// 跳跃游戏
bool canJump(vector<int> &nums)
{
    int sum = 0;
    if (nums.size() == 1)
        return true;
    for (int i = 0; i < nums.size() - 1; i++)
    {
        if (i <= sum)
        {
            sum = max(sum, i + nums[i]);
            if (sum >= nums.size() - 1)
                return true;
        }
    }
    return false;
}

// int main()
// {
//     vector<int> nums = {2, 0, 2, 3};
//     cout << canJump(nums) << endl;
//     system("pause");
//     return 0;
// }
// 跳跃游戏2,dp解法
int Jump(vector<int> &nums)
{

    int n = nums.size();

    vector<int> dp(n, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int minstep = INT_MAX;
        for (int j = 0; j < i; j++)
        {

            if (j + nums[j] >= i)
            {
                minstep = min(minstep, dp[j]);
                dp[i] = minstep + 1;
            }
        }
    }
    return dp[n - 1];
}

// 贪心解法
int jump(vector<int> &nums)
{
    int maxPos = 0, n = nums.size(), end = 0, step = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        if (maxPos >= i)
        {
            maxPos = max(maxPos, i + nums[i]);
            if (i == end)
            {
                end = maxPos;
                ++step;
            }
        }
    }
    return step;
}

int main()
{
    vector<int> nums = {2, 3, 1, 1, 4};
    cout << Jump(nums) << endl;
    system("pause");
    return 0;
}