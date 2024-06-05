#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <list>
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

// int main()
// {
//     vector<int> nums = {2, 3, 1, 1, 4};
//     cout << jump(nums) << endl;
//     system("pause");
//     return 0;
// }

// 合并区间
vector<vector<int>> merge(vector<vector<int>> &intervals)
{

    sort(intervals.begin(), intervals.end());
    vector<vector<int>> result;
    result.push_back(intervals[0]);
    int j = 0;
    for (int i = j + 1; i < intervals.size(); i++)
    {
        if (intervals[i][0] <= result[j][1])
            result[j][1] = max(result[j][1], intervals[i][1]);
        else
        {
            result.push_back(intervals[i]);
            j++;
        }
    }
    return result;
}

vector<vector<int>> merge1(vector<vector<int>> &intervals)
{

    sort(intervals.begin(), intervals.end());
    for (int i = 1; i < intervals.size(); i++)
    {
        if (intervals[i][0] <= intervals[i - 1][1])
        {
            intervals[i - 1][1] = max(intervals[i][1], intervals[i - 1][1]);
            intervals.erase(intervals.begin() + i);
            i--;
        }
    }
    return intervals;
}

// int main()
// {
//     vector<vector<int>> inter = {{1, 4}, {3, 5}, {6, 7}};
//     vector<vector<int>> ans = merge1(inter);
//     for (auto a : ans)
//         cout << a[0] << " " << a[1] << endl;
//     system("pause");
//     return 0;
// }

// 无重叠区间
int eraseOverlapIntervals(vector<vector<int>> &intervals)
{
    sort(intervals.begin(), intervals.end());
    int count = 0;             // 记录需要移除的区间数量
    int end = intervals[0][1]; // 当前所选区间的结束时间

    for (int i = 1; i < intervals.size(); ++i)
    {
        if (intervals[i][0] < end)
        {
            // 当前区间与前一个区间重叠，需要移除一个区间
            count++;
            // 选取更小的结束时间
            end = min(end, intervals[i][1]);
        }
        else
        {
            // 当前区间与前一个区间不重叠，更新结束时间
            end = intervals[i][1];
        }
    }

    return count;
}

// int main()
// {
//     vector<vector<int>> inter = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
//     int ans = eraseOverlapIntervals(inter);
//     cout << ans << endl;
//     system("pause");
//     return 0;
// }

// 划分字母区间
vector<int> partitionLabels(string s)
{
    unordered_map<char, int> map;
    for (int i = 0; i < s.size(); i++)
    {
        map[s[i]] = i;
    }

    vector<int> ans;
    int start = 0, end = 0;
    for (int i = 0; i < s.size(); i++)
    {
        end = max(end, map[s[i]]);
        if (i == end)
        {
            ans.push_back(end - start + 1);
            start = end + 1;
        }
    }

    return ans;
}

// int main()
// {
//     string s = "ababcbacadefegdehijhklij";
//     vector<int> ans = partitionLabels(s);
//     for (auto a : ans)
//         cout << a << " ";
//     cout << endl;
//     system("pause");
//     return 0;
// }

// 用最少的箭引爆气球
int findMinArrowShots(vector<vector<int>> &points)
{

    sort(points.begin(), points.end(), [](vector<int> &a, vector<int> &b)
         { return a[1] < b[1]; });
    int end = points[0][1];
    int cnt = 1;
    for (int i = 1; i < points.size(); i++)
    {
        if (end >= points[i][0])
            continue;
        else
        {
            end = points[i][1];
            cnt++;
        }
    }
    return cnt;
}

// 根据身高重建队列
vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
{
    int n = people.size();
    sort(people.begin(), people.end(), [](const vector<int> &u, const vector<int> &v)
         { return u[0] > v[0] || (u[0] == v[0] && u[1] < v[1]); });
    vector<vector<int>> ans;
    for (int i = 0; i < people.size(); i++)
    {
        ans.insert(ans.begin() + people[i][1], people[i]);
    }
    return ans;
}

// int main()
// {
//     vector<vector<int>> people = {{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}};
//     vector<vector<int>> ans = reconstructQueue(people);
//     for (int i = 0; i < ans.size(); i++)
//     {
//         cout << ans[i][0] << " " << ans[i][1] << endl;
//     }
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
// 我的做法没办法完成{1, 14, 14, 15}这个例子，只能算出等于26，但是结果是20.究其原因在于未必把所有数变成原数组中最大的数就可以了。也许变成更大的数M会更好
int minCostToEqualizeArray(vector<int> &nums, int cost1, int cost2)
{
    int max_num = *max_element(nums.begin(), nums.end());
    for (auto &num : nums)
    {
        num -= max_num;
        num = -num;
    }
    int sum = accumulate(nums.begin(), nums.end(), 0LL);
    const int MOD = 1e9 + 7;
    // 这两种情况直接求解
    if (nums.size() <= 2 || 2 * cost1 <= cost2)
        return sum * cost1 % MOD;
    // 剩余的情况
    int max2 = *max_element(nums.begin(), nums.end());
    int rest = sum - max2;
    if (max2 > rest + 1)
        return cost2 * rest + cost1 * (max2 - rest);
    else
        return cost2 * rest;
}

// int main()
// {

//     vector<int> nums = {1, 14, 14, 15};
//     cout << minCostToEqualizeArray(nums, 2, 1);
//     system("pause");
//     return 0;
// }

// 情侣牵手
// 成对的数字中，因为是从0-1开始的，所以每对情侣中奇数是大于偶数的。此外，如果想要进行配对，更改某一对的第一个数字和第二个数字都是可以的。
// 所以我们就看每一对的第一个数，如果是奇数x，那么与他配对的就是x-1;反之，如果是偶数x,那么与他配对的就是x+1。
// 要完成这么目的，我们需要事先直到与当前配对的元素在哪个位置，这就需要 一个数据结构储存数字下标和元素大小，哈希表再合适不过了。
int minSwapsCouples(vector<int> &row)
{
    int n = row.size();
    int count = 0;
    // unordered_map<int, int> map;
    // for (int i = 0; i < n; i++)
    // {
    //     map[row[i]] = i;
    // }

    for (int i = 0; i < n; i += 2)
    {
        unordered_map<int, int> map;
        for (int j = 0; j < n; j++)
        {
            map[row[j]] = j;
        }

        if (abs(row[i + 1] - row[i]) > 1 || (row[i] % 2 != 0 && row[i] + 1 == row[i + 1]))
        {
            count++;
            if (row[i] % 2 == 0)
                swap(row[i + 1], row[map[row[i] + 1]]);
            else
                swap(row[i + 1], row[map[row[i] - 1]]);
        }
    }
    return count;
}

int main()
{

    vector<int> nums = {5, 6, 4, 0, 2, 1, 9, 3, 8, 7, 11, 10};
    cout << minSwapsCouples(nums) << endl;
    system("pause");
    return 0;
}