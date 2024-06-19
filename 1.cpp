#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// vector<vector<int>> ans14;
// vector<int> path;
// int sum;
// void backtracking(vector<int> &candidates, int target, int start)
// {

//     if (sum > target)
//         return;

//     if (sum == target)
//     {
//         ans14.push_back(path);
//         return;
//     }
//     for (int i = start; i < candidates.size(); i++)
//     {
//         path.push_back(candidates[i]);
//         sum += candidates[i];
//         backtracking(candidates, target, i);
//         path.pop_back();
//         sum -= candidates[i];
//     }
// }

// vector<string> result;
// string road;

// void backtracking11(string s, int start, int sub_size, int num_comma)
// {

//     if (num_comma == 4)
//     {
//         string cur = road.substr(road.size() - 1 - sub_size, sub_size);
//         if (stoi(cur) > 255 || (cur.size() > 1 && cur[0] == '0') || (road.size() - 4 < s.size()))
//             return;
//         else
//         {
//             string r = road;
//             r.pop_back();
//             result.push_back(r);
//             return;
//         }
//     }

//     for (int i = start; i < s.size(); i++)
//     {
//         string cur = s.substr(start, i - start + 1);
//         if (stoi(cur) > 255 || (cur.size() > 1 && cur[0] == '0'))
//             break;

//         road.append(cur);
//         road.append(".");
//         num_comma++;
//         backtracking11(s, i + 1, cur.size(), num_comma);
//         num_comma--;
//         road.pop_back();
//         road.erase(road.size() - cur.size());
//     }
// }

// /// @brief 复原IP地址
// /// @param s
// /// @return
// vector<string> restoreIpAddresses(string s)
// {

//     backtracking11(s, 0, 0, 0);
//     return result;
// }

// int main()
// {

//     string s = "101023";
//     vector<string> result = restoreIpAddresses(s);

//     for (int i = 0; i < result.size(); i++)
//     {
//         for (auto r : result[i])
//             cout << r << " ";
//         cout << endl;
//     }

//     system("pause");
//     return 0;
// }

vector<vector<int>> ans14;
vector<int> path;

void backtracking14(vector<int> &nums, unordered_map<int, int> &used)
{
    if (path14.size() == nums.size())
    {
        ans14.push_back(path14);
        return;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;
        }

        if (used[nums[i]] <= 0)
            continue;

        else
            used[nums[i]]--;

        path14.push_back(nums[i]);
        backtracking11(nums, used);
        used[nums[i]]++;
        path14.pop_back();
    }
}

vector<vector<int>> permuteUnique(vector<int> &nums)
{
    unordered_map<int, int> used;
    for (auto c : nums)
        used[c]++;
    sort(nums.begin(), nums.end());
    backtracking11(nums, used);
    return ans14;
}

int main()
{

    vector<int> nums = {1, 1, 2};
    vector<vector<int>> result = permute(nums);

    for (int i = 0; i < result.size(); i++)
    {
        for (auto r : result[i])
            cout << r << " ";
        cout << endl;
    }

    system("pause");
    return 0;
}