#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

// 无重复字符的最长子串
int lengthOfLongestSubstring(string s)
{
    unordered_map<char, int> map;
    int left = 0;
    int right = 0;

    int n = s.size();
    int max_len = 0;

    while (right < n)
    {
        if (map[s[right]] == 0)
        {
            map[s[right]]++;
            right++;
            max_len = max(max_len, right - left);
            // cout << right - left << " ";
        }

        else
        {
            while (map[s[right]] > 0)
            {
                map[s[left]]--;
                left++;
            }
        }
    }
    return max_len;
}

// 串联所有单词的子串
// 玛德超时了，就差一个例子！！！！写了半天，气死个人！！！！
// 但是为了测试最后一个例子，只能逐个相加了，看看有无更好的的做法
vector<int> findSubstring1(string s, vector<string> &words)
{
    int n = words.size();
    int m = words[0].size();
    int len = n * m;
    vector<int> res;
    int l = 0;
    while (l + len <= s.size())
    {
        unordered_map<string, int> map;
        for (auto word : words)
        {
            map[word]++;
        }
        int newl = l;
        for (int i = 0; i < n; i++)
        {

            if (map.find(s.substr(l + i * m, m)) != map.end() && map[s.substr(l + i * m, m)] > 0)
            {
                newl = l + m;
                map[s.substr(l + i * m, m)]--;
            }
        }
        for (int i = 0; i < m; i++)
        {
            if (map.find(s.substr(l + i, m)) != map.end())
            {
                newl = l + i;
                break;
            }
        }

        bool flag = 1;
        for (const auto &it : map)
        {
            if (it.second != 0)
            {
                flag = 0;
            }
        }
        if (flag == 1)
        {
            res.push_back(l);
        }

        if (newl == l)
            l++;
        else
            l = newl;
    }
    return res;
}

vector<int> findSubstring(string s, vector<string> &words)
{

    int n = words.size(), m = words[0].size(), len = n * m;
    vector<int> res;
    // 统计words中每个单词出现的次数,是固定的
    unordered_map<string, int> map;
    for (auto word : words)
    {
        map[word]++;
    }

    for (int i = 0; i < m; i++)
    {
        unordered_map<string, int> window;
        int cnt = 0;
        for (int j = i; j + m <= s.size(); j += m)
        {
            if (j - i >= len)
            {
                string temp = s.substr(j - len, m);
                window[temp]--;
                if (window[temp] < map[temp])
                {
                    cnt--;
                }
            }
            string word = s.substr(j, m);
            window[word]++;
            if (window[word] <= map[word])
                cnt++;
            if (cnt == n)
            {
                res.push_back(j - len + m);
            }
        }
    }
    return res;
}

// int main()
// {
//     string s = "barfoothefoobarman";
//     vector<string> words = {"foo", "bar"};
//     // string s = "aaaaaaaaaaaaaa";
//     // vector<string> words = {"aa", "aa"};

//     vector<int> res = findSubstring(s, words);
//     for (int i = 0; i < res.size(); i++)
//     {
//         cout << res[i] << " ";
//     }

//     cout << endl;
//     system("pause");
//     return 0;
// }

// 最小覆盖子串
string minWindow(string s, string t)
{
    unordered_map<char, int> map;
    unordered_map<char, int> window;
    int cnt = 0;
    for (auto c : t)
    {
        map[c]++;
        cnt++;
    }

    int left = 0, right = 0, num = 0;
    int min_len = 0;
    int min_left = 0;
    while (right < s.size())
    {
        window[s[right]]++;

        if (window[s[right]] == map[s[right]])
            num += map[s[right]];
        while (num == cnt)
        {
            if (min_len == 0 || min_len > right - left + 1)
            {
                min_len = right - left + 1;
                min_left = left;
            }
            if (window[s[left]] == map[s[left]])
                num -= map[s[left]];
            window[s[left]]--;
            left++;
        }
        right++;
    }
    return s.substr(min_left, min_len);
}

// int main()
// {
//     string s = "acbbaca";
//     string t = "aba";
//     cout << minWindow(s, t) << endl;
//     system("pause");
//     return 0;
// }

// 最小区间
/// 拿下！
vector<int> smallestRange(vector<vector<int>> &nums)
{

    int n = nums.size();
    int m = nums[0].size();
    vector<int> sorted;
    // 创建哈希映射，并且找到最大值和最小值
    unordered_map<int, vector<int>> map;
    int max_num = INT_MIN;
    int min_num = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        for (auto num : nums[i])
        {
            map[num].push_back(i);
            max_num = max(max_num, num);
            min_num = min(min_num, num);
            sorted.push_back(num);
        }
    }
    // cout << max_num << "   " << min_num << endl;
    //  获取所有元素的去重排序数组
    sort(sorted.begin(), sorted.end());
    auto unique1 = unique(sorted.begin(), sorted.end());
    sorted.erase(unique1, sorted.end());
    // for (auto s : sorted)
    //     cout << s << " ";
    // cout << endl;

    // 滑动窗口遍历去重数组,找到所有可能的区间
    int left = 0;
    // 创建哈希表计数
    unordered_map<int, int> set;
    vector<vector<int>> ans;
    for (int right = 0; right < sorted.size(); right++)
    {
        for (auto i : map[sorted[right]])
            set[i]++;
        while (set.size() == n)
        {
            // bestleft = sorted[left];
            // bestright = sorted[right];
            ans.push_back({sorted[left], sorted[right]});
            for (auto i : map[sorted[left]])
            {
                if (set[i] <= 1)
                    set.erase(i);
                else
                    set[i]--;
            }

            left++;
        }
    }

    // for (int i = 0; i < ans.size(); i++)
    // {
    //     cout << "[" << ans[i][0] << " " << ans[i][1] << "]" << endl;
    // }

    // 比较区间，找到最小区间
    int bestleft = min_num;
    int bestright = max_num;
    for (int i = 0; i < ans.size(); i++)
    {
        if (ans[i][1] - ans[i][0] < bestright - bestleft)
        {
            bestleft = ans[i][0];
            bestright = ans[i][1];
        }
        else if (ans[i][1] - ans[i][0] == bestright - bestleft)
        {
            if (ans[i][0] < bestleft)
            {
                bestleft = ans[i][0];
                bestright = ans[i][1];
            }
        }
    }
    // 返回最小区间
    return {bestleft, bestright};
}

// int main()
// {
//     vector<vector<int>> nums = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
//     vector<int> res = smallestRange(nums);
//     cout << "result=[" << res[0] << "," << res[1] << "]";
//     system("pause");
//     return 0;
// }

// 区间子区间的个数
int lessEqualsThan(vector<int> &nums, int k)
{
    int left = 0;
    int ans = 0;
    for (int right = 0; right < nums.size(); right++)
    {
        if (nums[right] > k)
            left = right + 1;
        ans += right - left + 1;
    }
    return ans;
}

int numSubarrayBoundedMax(vector<int> &nums, int left, int right)
{

    return lessEqualsThan(nums, right) - lessEqualsThan(nums, left - 1);
}

// 爱生气的书店老板
// 暴力解法超时了。。。时间复杂度O(n2)
int maxSatisfied1(vector<int> &customers, vector<int> &grumpy, int minutes)
{
    int n = customers.size();
    int sum = 0;
    int l = 0, r = minutes - 1;
    while (r < n)
    {

        int temp = 0;
        for (int i = 0; i < n; i++)
        {
            if (grumpy[i] == 0 || (i >= l && i <= r))
                temp += customers[i];
        }
        sum = max(sum, temp);
        l++;
        r++;
    }

    return sum;
}

// 能否写出时间更少的解法
int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int minutes)
{
    int total = 0;
    int n = customers.size();
    for (int i = 0; i < n; i++)
    {
        if (grumpy[i] == 0)
        {
            total += customers[i];
        }
    }
    int increase = 0;
    for (int i = 0; i < minutes; i++)
    {
        increase += customers[i] * grumpy[i];
    }
    int maxIncrease = increase;
    for (int i = minutes; i < n; i++)
    {
        increase = increase - customers[i - minutes] * grumpy[i - minutes] + customers[i] * grumpy[i];
        maxIncrease = max(maxIncrease, increase);
    }
    return total + maxIncrease;
}

int main()
{
    vector<int> customers = {1, 0, 1, 2, 1, 1, 7, 5};
    vector<int> grumpy = {0, 1, 0, 1, 0, 1, 0, 1};
    int minutes = 3;
    cout << maxSatisfied(customers, grumpy, minutes) << endl;
    system("pause");
    return 0;
}