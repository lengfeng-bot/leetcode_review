#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<string>
#include<unordered_set>
using namespace std;

//可以使用「贪心算法」的问题需要满足的条件
//最优子结构：规模较大的问题的解由规模较小的子问题的解组成，区别于「动态规划」,可以使用「贪心算法」的问题「规模较大的问题的解」只由其中一个「规模较小的子问题的解」决定
//无后效性：后面阶段的求解不会修改前面阶段已经计算好的结果
//贪心选择性质：从局部最优解可以得到全局最优解。
//总结:贪心无套路！




//从最经典的贪心例题来！
//分发饼干
int findContentChildren(vector<int>& g, vector<int>& s) {
	sort(g.begin(), g.end());
	sort(s.begin(), s.end());
	int i = 0;
	int j = 0;
	int num = 0;
	while (i < g.size() && j < s.size())
	{
		if (s[j] >= g[i])
		{
			i++;
			j++;
			num++;
		}
		else
			j++;
	}
	return num;
}


/// <summary>
/// 反着来也行
/// </summary>
int findContentChildren2(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end()); 
    int count = 0;
    int i = g.size() - 1;
    int j = s.size()-1;
    while (i>=0&&j>=0)
    {
        if (g[i] > s[j]) i--;
        else
        {
            count++;
            i--;
            j--;
        }
    }
    return count;
}


//int main() {
//    // 示例输入
//    vector<int> g = { 1, 2, 3 };
//    vector<int> s = { 1, 1 };
//
//    // 调用函数并输出结果
//    int result = wtf(g, s);
//    cout << "最大满足条件的小孩数量是: " << result << endl;
//
//    return 0;
//}


/// <summary>
/// 摆动序列
/// </summary>
/// 直接先把数组相邻数的插值算出来，如果连续符号相同，不加，等出现符号不同的时候再加
/// 这个题目最重要的是要注意等于的情况，分好几种情况讨论
int wiggleMaxLength(vector<int>& nums) {
    if (nums.size() < 2) {
        return nums.size();  // 数组长度小于2，直接返回数组长度
    }

    int result = 1;  // 最长摆动序列的初始长度为1
    int prevDiff = 0;  // 前一个元素与当前元素的差值

    for (int i = 1; i < nums.size(); ++i) {
        int currDiff = nums[i] - nums[i - 1];
        // 如果当前差值与前一个差值不同号，表示摆动趋势
        if ((currDiff > 0 && prevDiff <= 0) || (currDiff < 0 && prevDiff >= 0)) {
            result++;  // 增加摆动序列的长度
            prevDiff = currDiff;  // 更新前一个差值
        }
    }

    return result;
}

//int main() {
//    vector<int> nums1 = { 1, 7, 4, 9, 2, 5 };
//    vector<int> nums2 = { 1, 4, 7, 2, 5 };
//    vector<int> nums3 = { 1, 7, 4, 5, 5 };
//
//    cout << "最长摆动序列的长度：" << wiggleMaxLength(nums1) << endl;  // 输出：6
//    cout << "最长摆动序列的长度：" << wiggleMaxLength(nums2) << endl;  // 输出：4
//    cout << "最长摆动序列的长度：" << wiggleMaxLength(nums3) << endl;  // 输出：4
//
//    return 0;
//}



/// <summary>
/// 最大子数组和
/// </summary>
/// 这个有点难想啊，思路就是累加和为负数的时候，直接抛弃，从下一个数重新计算。这样就可以一直取到局部最优
int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    int sum = 0;
    int result = INT32_MIN;
    for (int i = 0; i < n; i++)
    {  
        sum += nums[i];
        if (sum > result) { // 取区间累计的最大值（相当于不断确定最大子序终止位置）
            //result = count;
        }
        if (sum <= 0) sum = 0; // 相当于重置最大子序起始位置，因为遇到负数一定是拉低总和
    }
    return result;
}

/// <summary>
/// 柠檬水找零
/// </summary>
/// 这尼玛，不就是把所有情况列出来吗。。。
bool lemonadeChange(vector<int>& bills) {
    int five = 0, ten = 0;
    for (auto& bill : bills) {
        if (bill == 5) {
            five++;
        }
        else if (bill == 10) {
            if (five == 0) {
                return false;
            }
            five--;
            ten++;
        }
        else {
            if (five > 0 && ten > 0) {
                five--;
                ten--;
            }
            else if (five >= 3) {
                five -= 3;
            }
            else {
                return false;
            }
        }
    }
    return true;
}


//区域选择问题
//有一类使用「贪心算法」解决的问题称为「活动选择问题」，解决这一类问题的直觉是「优先选择活动最早的活动」。
//我觉得这个套路就是先排序期间的起始位置，之后一个for循环解决问题！

/// <summary>
/// 无重叠区间
/// </summary>
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) {
        return 0;
    }

    // 按结束时间升序排序
    std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[1] < b[1];
        });

    int count = 0; // 记录需要移除的区间数量
    int end = intervals[0][1]; // 当前所选区间的结束时间

    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] < end) {
            // 当前区间与前一个区间重叠，需要移除一个区间
            ++count;
        }
        else {
            // 当前区间与前一个区间不重叠，更新结束时间
            end = intervals[i][1];
        }
    }

    return count;
}

/// <summary>
/// 上面这个是按照结束位置从大到小排序的，我写一个按照起始位置从大到小的代码
/// </summary>
int eraseOverlapIntervals2(vector<vector<int>>& intervals) {
    if (intervals.empty()) {
        return 0;
    }

    // 按结束时间升序排序
    sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[0] < b[0];
        });
    int count = 0; // 记录需要移除的区间数量
    int end = intervals[0][1]; // 当前所选区间的结束时间

    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] < end) {
            // 当前区间与前一个区间重叠，需要移除一个区间
            count++;
            //选取更小的结束时间
            end = min(end, intervals[i][1]);
        }
        else {
            // 当前区间与前一个区间不重叠，更新结束时间
            end = intervals[i][1];
        }
    }

    return count;
}



//用最少数量的箭引爆气球
//每一支箭射出的位置都在某个气球的右边界，才是最优的射法。之后判断射到最小的右边界时候，这个右边界的右边是否还存在没有被射到的气球，
// 如果有，就要加一个箭，继续之前的操作。
//这太难想了吧！！！~
int findMinArrowShots(vector<vector<int>>& points) {

    if (points.empty()) {
        return 0;
    }

    // 按照气球的结束位置进行排序
    sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b) {
        return a[1] < b[1];
        });

    int arrows = 1;
    int endPos = points[0][1];

    for (int i = 1; i < points.size(); ++i) {
        if (points[i][0] > endPos) {
            // 需要一支新箭来引爆下一个气球
            arrows++;
            endPos = points[i][1];
        }
    }

    return arrows;
}

///第二次做，好不容易写出来了，居然说我超时？？这就一层循环啊，还有天理没？
//耗时少的答案见209行
int findMinArrowShots2(vector<vector<int>>& points) {

    sort(points.begin(), points.end(), [](vector<int>a, vector<int>b) {if (a[0] == b[0])return a[1] < b[1]; return a[0] < b[0]; });
    int n = points.size();
    int start = points[0][0];
    int end = points[0][1];
    int count = 1;
    for (int i = 1; i < n; i++)
    {

        if (points[i][0] <= end) {
            start = max(start, points[i][0]);
            end = min(end, points[i][1]);
        }

        else
        {
            count++;
            start = points[i][0];
            end = points[i][1];
        }

    }
    return count;

}



/// <summary>
/// 划分字母区间
/// </summary>
/// 我的想法是这样的。先用一个集合或者哈希表找出每个字母出现的起始位置，然后对于不同字母不同的区间进行划分
/// 被包含的小区间与大区间合并
/// 有交集的区间合并
/// 这样获得的就是没有交集区间就是分割的次数，为了保证尽可能划分最多的区间，每当区间起始点相等，当作不同区间。
/// 
/// 你这思路太复杂了，，，官方这个思路太优雅了！！两行代码，哈希表统计每个字符出现的最后位置。
/// 然后用一个巧妙地判断，彻底拿下!
vector<int> partitionLabels(string s) {
    vector<int>ans;
    int hash[27] = { 0 }; // i为字符，hash[i]为字符出现的最后位置
    for (int i = 0; i < s.size(); i++) { // 统计每一个字符最后出现的位置
        hash[s[i] - 'a'] = i;
    }
    int left = 0;
    int right = 0;
    for (int i = 0; i < s.size(); i++)
    {
        right = max(right, hash[s[i] - 'a']);
        if (right = i) {
            ans.push_back(right - left + 1);
            left = i + 1;
        }

    }
    return ans;
}


//合并区间
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {


    sort(intervals.begin(), intervals.end());
    vector<vector<int>>result;
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

/// <summary>
/// 第二遍自己做的，相当于一个正常的模拟
/// </summary>
vector<vector<int>> merge2(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>>ans;
    ans.push_back(intervals[0]);
    int right = intervals[0][1];
    int j = 0;
    for (int i =1 ; i < intervals.size(); i++)
    {
        if (intervals[i][0] > right) { ans.push_back(intervals[i]); right = intervals[i][1];  j++; }
        else { right = max(right, intervals[i][1]); ans[j][1] = right; }

    }
    return ans;
}
//int main() {
//    vector<vector<int>> intervals = { {2,3},{1,3},{5,7},{4,6} };
//    vector<vector<int>> merged = merge2(intervals);
//
//    cout << "合并后的区间：" << endl;
//    for (const vector<int>& interval : merged) {
//        cout << "[" << interval[0] << ", " << interval[1] << "] ";
//    }
//    cout << endl;
//
//    return 0;
//}



/// <summary>
/// 跳跃游戏
/// </summary>
bool canJump(vector<int>& nums) {

    int cover = 0;
    if (nums.size() == 1) return true; // 只有一个元素，就是能达到
    for (int i = 0; i <= cover; i++) { // 注意这里是小于等于cover
        cover = max(i + nums[i], cover);
        if (cover >= nums.size() - 1) return true; // 说明可以覆盖到终点了
    }
    return false;


}

/// <summary>
/// 跳跃游戏2
/// </summary>
int jump(vector<int>& nums) {
    int ans = 0;
    int start = 0;
    int end = 1;
    while (end <nums.size())
    {
        int maxlen = 0;
        for (int  i = start; i < end; i++)
        {
            maxlen = max(maxlen, i + nums[i]);

        }
            start = end;
            end = maxlen + 1;
            ans++;
    }
    return ans;
}





//int main() {
//    vector<int> nums = { 3,2,1,0,4 };
//    bool result = canJump(nums);
//
//    if (result) {
//        cout << "可以到达最后一个位置" << endl;
//    }
//    else {
//        cout << "无法到达最后一个位置" << endl;
//    }
//
//    return 0;
//}


/// <summary>
/// 玩筹码
/// </summary>
/// 秒了！统计数组奇数偶数的个数，最小
int minCostToMoveChips(vector<int>& position) {
    int even = 0, odd = 0;
    for (int pos : position) {
        if (pos % 2) {
            odd++;
        }
        else {
            even++;
        }
    }
    return min(odd, even);
}


/// <summary>
/// 最小分割和
/// </summary>
/// 我只知道num1和num2最多相差一个。但还应该发现另一个关键:num1,num2中的数字都是单调递增的，且任何一个数字，都不能大于任何一个数中比它位数更小的数字
/// 这样的话直接排序，然后交替分配数字即可
int splitNum(int num) {
    string stnum = to_string(num);
    sort(stnum.begin(), stnum.end());
    int num1 = 0;
    int num2 = 0;
    for (int i = 0; i < stnum.size(); i++) {
        if (i % 2 == 0)
            num1 = num1 * 10 + (stnum[i] - '0');
        else
            num2 = num2 * 10 + (stnum[i] - '0');
    }
    return num1 + num2;
}


/// <summary>
/// 加油站
/// </summary>
/// 关键在于设置一个当前和和累加和，遍历数组，若当前和小于0，就说明这个点不可能作为起点，直接下一个。
/// 走完一圈要保证每个点油剩余量都要大于等于0
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int n = gas.size();
    int curcost = 0;
    int sumcost = 0;
    int a = 0;
    for (int i = 0; i < n; i++)
    {
            curcost += gas[i]-cost[i];
            sumcost += gas[i]-cost[i];
            if (curcost < 0)
            {
                a = (i + 1) % n;
                curcost = 0;
            }
   }
    if (sumcost >= 0) return a;
    else return -1;
}

/// <summary>
/// 分发糖果
/// </summary>
/// 我敲！！！这困难题也不难嘛，我就想着试一下，没想到一下拿下了！
/// 关键在于要遍历两边，从左到右和从右到左
int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int>ans(n, 1);
    for (int i = 0; i < n-1; i++)
    {
        if (ratings[i + 1] > ratings[i]) ans[i + 1] = ans[i] + 1;
        else if (ratings[i + 1] < ratings[i]) 
            if(ans[i]==ans[i+1])ans[i]++;
    }

    for (int i = n - 1; i > 0; i--)
    {
       if (ratings[i - 1] > ratings[i]) ans[i - 1] = max(ans[i - 1], ans[i] + 1);
       else if (ratings[i - 1] < ratings[i]) 
            if (ans[i] == ans[i - 1])  ans[i]++;
            
     }

    int sum = 0;
    for (auto a : ans) sum += a;

    return sum;
}


/// <summary>
/// 根据身高重建队列
/// </summary>
vector<vector<int>> reconstructQueue1(vector<vector<int>>& people) {
    vector<vector<int>>ans(people.size(), std::vector<int>(2, -1));
    sort(people.begin(), people.end(), [](vector<int>a, vector<int>b) {return a[0] < b[0]; });
    unordered_set<int> seenNumbers;
    int n = people.size();
    for (int i = 0; i < n; i++)
    {
        int num = people[i][1];
        if (seenNumbers.count(num) > 0) {
            ans[num] = people[i];
            int j = i;
            while (j>=0) {        
                ans[j + 1] = ans[j];
                j--;
            }
        }
        else {
            seenNumbers.insert(people[i][1]);
            ans[num] = people[i];
        }
    }
    return ans;
}

/// <summary>
/// 这是正确答案，我怎么就写不出来呢！！
/// </summary>
static bool cmp(const vector<int>& a, const vector<int>& b) {
    if (a[0] == b[0]) return a[1] < b[1];
    return a[0] > b[0];
}
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), cmp);
    vector<vector<int>> que;
    for (int i = 0; i < people.size(); i++) {
        int position = people[i][1];
        que.insert(que.begin() + position, people[i]);
    }
    return que;
}

//int main() {
//    vector<vector<int>> people = { {2,3},{1,5},{6,7} };
//    vector<vector<int>>a = reconstructQueue(people);
//    return 0;
//}

/// <summary>
/// 单调递增的数字
/// </summary>
/// 我的思路是，首先进行判断，若这个数字递增（大于等于），返回本身，否则从不递增的数字开始，前面不变，当前数减一。后面补9
/// 487 -> 479 这种情况，百位不变，只变十位
/// 实际上上面的方法能解决 296/308个示例，没法解决这种668841
/// 应该从后往前遍历，而且不要break
int monotoneIncreasingDigits(int n) {
    string s = to_string(n);
    int fig = s.size();
    bool isincrease = true;
    for (int i = s.size() - 1; i > 0; i--) {
        if (s[i - 1] > s[i]) {
            fig = i;
            s[i - 1]--;
        }
    }

    for (int i = fig; i < s.size(); i++)
    {
        s[i] = '9';
    }
    return stoi(s);

}