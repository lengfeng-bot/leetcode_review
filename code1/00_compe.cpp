#include <iostream>
#include <vector>
#include <string>
using namespace std;

// int main()
// {
//     string s;
//     cin >> s;
//     string shifted = s.substr(3) + s.substr(0, 3);
//     for (auto c : shifted)
//     {
//         cout << int(c);
//     }

//     system("pause");
//     return 0;
// }

// 删除字符串中间的字串

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <stack>
using namespace std;

// 定义两个字母
const char H = 'H'; // 表示“好”
const char X = 'X'; // 表示“行”

// 根据规则进行转换
// 根据 Z 语言规则进行转换
string apply_rules(string &s)
{
    stack<char> st;
    st.push(s[0]);
    for (char c : s)
    {
        if (st.size() < 2)
        {
            st.push(c);
        }
        else
        {
            char temp = st.top();
            st.pop();
            while (temp == st.top() && st.top() == 'H')
            {
                st.pop();
                st.push('X');
                temp = st.top();
            }
            while (temp == st.top() && st.top() == 'X')
            {
                st.pop();
                st.push('H');
                temp = st.top();
            }
            st.push(c);
        }
    }
    s = "";
    while (!st.empty())
    {
        s.push_back(st.top());
        st.pop();
    }

    return s;
}

bool isSame(string s1, string s2, int a, int b, int c, int d)
{

    string subs1 = s1.substr(a - 1, b - a + 1);
    string subs2 = s2.substr(c - 1, d - c + 1);

    subs1 = apply_rules(subs1);
    subs2 = apply_rules(subs2);
    return subs1 == subs2;
}

// int main()
// {
//     string s;
//     cin >> s;
//     string t;
//     cin >> t;
//     int n;
//     cin >> n;
//     for (int i = 0; i < n; i++)
//     {
//         int a, b, c, d;
//         cin >> a >> b >> c >> d;
//         if (isSame(s, t, a, b, c, d))
//             cout << "YES" << endl;
//         else
//             cout << "NO" << endl;
//     }

//     system("pause");
//     return 0;
// }

// #include <iostream>
// #include <vector>
// using namespace std;

// int main()
// {
//     long long a, b;
//     cin >> a >> b;

//     if (abs(a - b) >= 2)
//     {
//         cout << "Alice" << endl;
//     }
//     else
//     {
//         cout << "Brown" << endl;
//     }
//     system("pause");
//     return 0;
// }
// #include <unordered_map>
// int main()
// {

//     int n;
//     int p;
//     cin >> n >> n >> p;
//     vector<int> nums(n, 0);
//     for (int i = 0; i < n; i++)
//     {
//         cin >> nums[i];
//     }

//     vector<int> good(n, 0);
//     for (int i = 0; i < n; i++)
//     {
//         cin >> good[i];
//     }
//     int l = 0;
//     int r = n - 1;

//     unordered_map<int, int> mp;
//     for (int i = 0; i < n; i++)
//     {
//         mp[nums[i]] = i;
//     }
//     int len = 0;
//     for (int i = 0; i < n; i++)
//     {
//         if (mp[nums[i]] > 1)
//             l = i;
//     }

//     system("pause");
//     return 0;
// }

int longestMonotonicSubarray(vector<int> &nums)
{
    int n = nums.size();
    int len = 1;
    int maxlen = 0;
    for (int i = 1; i < n; i++)
    {
        if (nums[i] > nums[i - 1])
        {
            len++;
            maxlen = max(maxlen, len);
        }
        else
            len = 1;
    }
    len = 1;
    for (int i = 1; i < n; i++)
    {
        if (nums[i] < nums[i - 1])
        {
            len++;
            maxlen = max(maxlen, len);
        }
        else
            len = 1;
    }

    return maxlen;
}
// int main()
// {
//     vector<int> nums = {1, 2, 7, 4, 5, 6, 10, 8, 9};
//     cout << longestMonotonicSubarray(nums) << endl;
//     system("pause");
//     return 0;
// }

string getSmallestString(string &s, int k)
{
    if (k == 0)
        return s;
    int n = s.size();
    int count = k;
    int i = 0;
    while (count > 0 && i < n)
    {

        if (s[i] == 'a')
        {
            i++;
            continue;
        }
        if (('z' - s[i] + 1) < s[i] - 'a')

            if (s[i] + count >= 'z')
            {
                count = count - ('z' - s[i] + 1);
                s[i] = 'a';
                i++;
                continue;
            }

        if (s[i] - count <= 'a')
        {
            count -= s[i] - 'a';
            s[i] = 'a';
            i++;
            continue;
        }
        else
        {
            s[i] = s[i] - count;
            count = 0;
            i++;
        }
    }
    return s;
}

// int main()
// {
//     string s = "kb";
//     int k = 16;
//     cout << getSmallestString(s, k) << endl;
//     system("pause");
//     return 0;
// }

long long minOperationsToMakeMedianK(vector<int> &nums, int k)
{
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int mid = n / 2;

    long long ans = 0;
    if (k == nums[mid])
        return 0;
    if (k < nums[mid])
    {
        for (int i = mid; i >= 0; i--)
        {
            if (nums[i] >= k)
                ans += nums[i] - k;
            else
                break;
        }
    }
    else
    {
        for (int i = mid; i < n; i++)
        {
            if (nums[i] <= k)
                ans += k - nums[i];
            else
                break;
        }
    }
    return ans;
}
int main()
{
    vector<int> nums = {2, 5, 6, 8, 5};
    int k = 4;
    cout << minOperationsToMakeMedianK(nums, k) << endl;
    system("pause");
    return 0;
}