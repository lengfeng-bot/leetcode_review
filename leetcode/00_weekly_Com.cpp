#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// 四百场周赛
int minimumChairs(string s)
{
    int n = s.size();
    int min_ch = INT_MIN;
    int chair = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'E')
        {
            chair++;
            min_ch = max(chair, min_ch);
        }
        else
            chair--;
    }
    return min_ch;
}

int countDays(int days, vector<vector<int>> &meetings)
{
    sort(meetings.begin(), meetings.end());
    vector<vector<int>> result;
    result.push_back(meetings[0]);
    int j = 0;
    for (int i = j + 1; i < meetings.size(); i++)
    {
        if (meetings[i][0] <= result[j][1])
            result[j][1] = max(result[j][1], meetings[i][1]);
        else
        {
            result.push_back(meetings[i]);
            j++;
        }
    }
    int workday = days;
    for (int i = 0; i < result.size(); i++)
    {
        workday -= result[i][1] - result[i][0] + 1;
    }

    return workday;
}

// 这种方法太难维护下标了，不好处理，需要用到栈
//  string clearStars(string &s)
//  {
//      int min_num = 0;
//      for (int i = 1; i <= s.size(); i++)
//      {

//         if (s[i] == '*' && i == s.size())
//         {
//             s.erase(i, 1);
//             s.erase(min_num, 1);
//             break;
//         }
//         else if (s[i] == '*')
//         {
//             s.erase(i, 1);
//             s.erase(min_num, 1);
//             i -= 1;
//         }
//         if (s[i] < s[i - 1])
//             min_num = i;
//     }
//     return s;
// }

// 使用26个栈维护26个字母，把字母push到栈中，如果遇到*，那么就从a栈遍历到z栈，直到存在不为空的栈，pop此元素。
string clearStars(string s)
{
    vector<int> st[26];
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] != '*')
        {
            st[s[i] - 'a'].push_back(i);
            continue;
        }

        for (auto &p : st)
        {
            if (!p.empty())
            {
                p.pop_back();
                break;
            }
        }
    }

    vector<int> idx;
    for (auto &p : st)
    {
        idx.insert(idx.end(), p.begin(), p.end());
    }
    sort(idx.begin(), idx.end());
    string t(idx.size(), 0);
    for (int i = 0; i < idx.size(); i++)
    {
        t[i] = s[idx[i]];
    }
    return t;
}

int main()
{

    string s = "yd**";
    string ans = clearStars(s);

    cout << ans << endl;
    system("pause");
    return 0;
}