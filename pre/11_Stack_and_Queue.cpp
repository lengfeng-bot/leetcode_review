#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<stack>
#include<queue>
#include<string>
using namespace std;



/// <summary>
/// 字符串解码
/// </summary>
/// 涉及到配对的[,]或者(,)的情况，一般用栈来储存找到相应的配对
string decodeString(string s) {
	int n = s.size();
	string ans;
	stack<char>check;
	for (int i = 0; i < n; i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			ans.push_back(s[i]);
		else if(s[i]=='[')
		{
			check.push(s[i]);

		}

	}
	return ans;
}


/// <summary>
/// 删除字符串中的所有相邻重复项
/// </summary>
/// 这个题目神奇之处在于，如果直接使用栈的话，输出的是反序的，还需要继续处理一下。然后
/// 我们可以直接把字符串当成一个栈，因为字符串本来就有入栈和出栈类似的接口，这样的话直接拿下！
string removeDuplicates(string s) {
	string st;
	int n = s.size();
	for (int i = 0; i < n; i++)
	{
		if (st.size() && st.back() == s[i])
		{
			st.pop_back();
		}
		else st += s[i];
	}
	return st;
}
//int main() {
//	string S = "abbaca";
//	cout << "Original string: " << S << endl;
//	cout << "String after removing duplicates: " << removeDuplicates(S) << endl;
//
//	return 0;
//}


/// <summary>
/// 用栈实现队列
/// </summary>
class MyQueue {
public:
	MyQueue() {

	}

	void push(int x) {
		stackin.push(x);
	}

	int pop() {
		if (stackout.empty())
		{
			while (!stackin.empty())
			{	
				stackout.push(stackin.top());
				stackin.pop();
			}
			
		}
		int ans = stackout.top();
		stackout.pop();
		return ans;
	}

	int peek() {
		int ans = this->pop();
		stackout.push(ans);
		return ans;
	}

	bool empty() {
		if (stackin.empty() && stackout.empty()) return true;
		else return false;
	}
public:
	stack<int>stackin;
	stack<int>stackout;
};


//int main() {
//	MyQueue* obj = new MyQueue();
//	obj->push(1);
//	obj->push(2);
//	obj->push(3);
//	obj->pop();
//	obj->push(4);
//	obj->pop();
//	//cout << param_1 << endl;
//	cout << param_2 << endl;
//	return 0;
//}


/// <summary>
/// 用队列实现栈
/// </summary>
class MyStack {
public:
	queue<int> que;
	/** Initialize your data structure here. */
	MyStack() {

	}
	/** Push element x onto stack. */
	void push(int x) {
		que.push(x);
	}
	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		int size = que.size();
		size--;
		while (size--) { // 将队列头部的元素（除了最后一个元素外） 重新添加到队列尾部
			que.push(que.front());
			que.pop();
		}
		int result = que.front(); // 此时弹出的元素顺序就是栈的顺序了
		que.pop();
		return result;
	}

	/** Get the top element. */
	int top() {
		return que.back();
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return que.empty();
	}
};


/// <summary>
/// 检查替换后的词是否有效
/// </summary>
/// 
bool isValid11(string s) {
	stack<char>st;
	for (int i = 0; i < s.size(); i++)
	{	
		if (!st.empty()) {
			if (st.top() == 'b' && s[i] == 'c') {
				st.pop();
				if (!st.empty()) {
					if (st.top() == 'a') st.pop();
					else return false;
				}
				else return false;
			}
			else st.push(s[i]);
		}
		else st.push(s[i]);
	}
	return st.empty();
}

//int main() {
//	string s = "babcc";
//	cout << "Is \"" << s << "\" valid? " << (isValid11(s) ? "Yes" : "No") << endl;
//
//	return 0;
//}

/// <summary>
/// 逆波兰表达式求值
/// </summary>
int evalRPN(vector<string>& tokens) {
	stack<int>stk;
	
	for (const string& token : tokens)
	{
		if (token == "+" || token == "-" || token == "*" || token == "/") {
			int num2 = stk.top(); stk.pop();
			int num1 = stk.top(); stk.pop();
			if (token == "+") stk.push(num1 + num2);
			else if (token == "-") stk.push(num1 - num2);
			else if (token == "*") stk.push(num1 * num2);
			else if (token == "/") stk.push(num1 / num2);
		}
		else stk.push(stoi(token));

	}
	return stk.top();
}

//int main() {
//	vector<string> tokens = { "2", "1", "+", "3", "*" };
//	cout << "Result: " << evalRPN(tokens) << endl;
//
//	return 0;
//}



/// 介绍几个单调栈的题目
/// 
/// 
/// 
/// <summary>
/// 1.股票价格跨度
/// </summary>
class StockSpanner {
public:
	StockSpanner() {
		this->stk.emplace(-1, INT_MAX);
		this->idx = -1;
	}

	int next(int price) {
		idx++;
		while (price >= stk.top().second)
		{
			stk.pop();
		}
		int m = idx - stk.top().first;
		stk.emplace(idx, price);

		return m;


	}

private:
	stack<pair<int, int>> stk;
	int idx;
};


//int main() {
//    StockSpanner spanner;
//    std::vector<int> prices = { 100, 80, 60, 70, 60, 75, 85 };
//
//    for (int price : prices) {
//        int span = spanner.next(price);
//        std::cout << span << " ";
//    }
//
//    return 0;
//}


/// <summary>
/// 2.每日温度
/// </summary>
vector<int> dailyTemperatures(vector<int>& temperatures) {
	int n = temperatures.size();
	stack<int>st;
	vector<int>ans(n, 0);
	for (int i = 0; i < n; i++)
	{
		while (!st.empty() && temperatures[i] > temperatures[st.top()])
		{
			int num = i - st.top();
			ans[st.top()] = num;
			st.pop();

		}
		st.push(i);
	}
	return ans;
}




/// <summary>
/// 下一个更大元素1
/// </summary>
/// 单调栈加上哈希表
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
	stack<int>st;
	vector<int>ans;
	unordered_map<int, int>map;
	int n = nums2.size();
	for (int i = 0; i < n; i++)
	{
		while (!st.empty() && nums2[i] > nums2[st.top()])
		{
			map[nums2[st.top()]] = nums2[i];
			st.pop();
		}
		st.push(i);
	}
	//处理栈中剩余的元素
	while (!st.empty()) {
		map[nums2[st.top()]] = -1; // 栈中剩余元素没有下一个更大元素
		st.pop();
	}
	for (auto num : nums1) {
		ans.push_back(map[num]);
	}

	return ans;
}
/// <summary>
/// 下一个更大元素2
/// </summary>
/// 这个和上面的不同之处在于，变成循环数组了，而且不需要哈希映射，更简单了好像
/// 
vector<int> nextGreaterElements2(vector<int>& nums) {
	int n = nums.size();
	vector<int>ans(n, -1);

	stack<int>st;
	for (int i = 0; i < 2 * n; i++)
	{
		int index = i % n;
		while (!st.empty() && nums[index] > nums[st.top()])
		{
			ans[st.top()] = nums[index];
			st.pop();
		}
		st.push(index);
	}
	return ans;
}


//int main() {
//	vector<int>nums1 = { 4,1,2 };
//	vector<int>  nums2 = { 1,3,4,2 };
//	vector<int>
//		ans = nextGreaterElements2(nums1);
//	for (int i = 0; i < ans.size(); i++)
//	{
//		cout << ans[i] << endl;
//	}
//
//
//}

/// <summary>
/// 3.接雨水
/// </summary>
/// 这道题的关键是，既要找左边第一个比当前元素大的，又要找右边的，我觉得可以建立两个数组，分别表示当前元素下一个更大元素的位置。
/// 得到这两个数组之后，加上一点小小的判断，便可以轻易得到每个元素能接到水的量了。
/// 我上面的思路有些问题：我要找的不是第一个比当前大的元素，而是当前元素左边或者右边最大的元素才行。需要改进这个问题.
/// 果然，改进之后，拿下了！！！但是看了看官方题解，用到单调栈，还更简单了。我把官方解法列在下面
//int trap(vector<int>& height) {
//	int n = height.size();
//	vector<int>rmax(n, -1);
//	vector<int>lmax(n, -1);
//	stack<int>s;
//	
//
//	int maxRight = height[n - 1];
//	for (int i = n - 2; i >= 0; --i) {
//		if (height[i] < maxRight) {
//			rmax[i] = maxRight;
//		}
//		else {
//			maxRight = height[i];
//		}
//	}
//	int maxLeft = height[0];
//	for (int i = 1; i < n; ++i) {
//		if (height[i] < maxLeft) {
//			lmax[i] = maxLeft;
//		}
//		else {
//			maxLeft = height[i];
//		}
//	}
//
//	//for (int i = 0; i < n; i++)
//	//{	
//	//	while (!s.empty() && height[i] > height[s.top()]) {
//	//		rmax[s.top()] = height[i];
//	//		s.pop();
//	//	}
//	//	s.push(i);
//	//	
//	//}
//	//for (int i = n-1; i >=0; i--)
//	//{
//	//	while (!s.empty() && height[i] > height[s.top()]) {
//	//		lmax[s.top()] = height[i];
//	//		s.pop();
//	//	}
//	//	s.push(i);
//	//}
//
//	for(auto m:height)
//		cout << m << " ";
//	cout << endl;
//	for (auto m : rmax)
//		cout << m << " ";
//	cout << endl;
//	for (auto m : lmax)
//		cout << m << " ";
//
//	int sum = 0;
//	for (int i = 0; i < n; i++)
//	{
//		if (lmax[i] != -1 && rmax[i] != -1) {
//		sum += (min(lmax[i], rmax[i]) - height[i]);
//		}
//
//	}
//	return sum;
//}

/// <summary>
/// 我看明白了,先求出右边第一个更大的元素，同时该栈顶元素的下一个元素就是左边更大元素，然后按行(横向)求解，分别求出高和宽。我上面的是按照列求解的
/// </summary>
int trap(vector<int>& height) {
	stack<int> st;
	int sum = 0;
	int n = height.size();
	for (int i = 0; i < n; i++)
	{
		while (!st.empty() && height[i] > height[st.top()]) {
			int mid = st.top();
			st.pop();
			if (!st.empty()) {
				int h = min(height[i], height[st.top()]) - height[mid];
				int w = i - st.top() - 1;
				sum += h * w;
			}
		}
		st.push(i);
	}
	return sum;
}

//int main() {
//	vector<int>nums = { 4,2,0,3,2,5 };
//	int a = trap(nums);
//	cout <<endl<< a;
//	return 0;
//}


/// <summary>
/// 柱状图中最大的矩形
/// </summary>
/// 这道题和接雨水太像了，一个是求两边更大元素，一个求两边更小元素。但是需要注意的是
int largestRectangleArea(vector<int>& heights) {

	stack<int>s;
	int sum = 0;
	//首尾都加上0的话，每个元素两边都有更小元素了

	heights.insert(heights.begin(), 0); // 数组头部加入元素0
	heights.push_back(0); // 数组尾部加入元素0
	int n = heights.size();
	for (int i = 0; i < n; i++)
	{
		while (!s.empty() && heights[i] < heights[s.top()]) {
			int mid = s.top();
			s.pop();
			sum = max(sum, (heights[mid] * (i - s.top() - 1)));
		}
		s.push(i);
	}
	return sum;
}
//int main() {
//	vector<int>nums = { 2,1,5,6,2,3 };
//	int a = largestRectangleArea(nums);
//	cout <<endl<< a;
//	return 0;
//}



/// <summary>
/// 最小栈
/// </summary>
class MinStack {
public:
	MinStack() {
	}

	// 压栈操作，同时更新最小值
	void push(int x) {
		dataStack.push(x);
		if (minStack.empty() || x <= minStack.top()) {
			minStack.push(x);
		}
	}

	// 弹栈操作，同时更新最小值
	void pop() {
		if (!dataStack.empty()) {
			if (dataStack.top() == minStack.top()) {
				minStack.pop();
			}
			dataStack.pop();
		}
	}

	// 获取栈顶元素
	int top() {
		return dataStack.top();
	}

	// 获取栈中最小元素
	int getMin() {
		return minStack.top();
	}

private:
	std::stack<int> dataStack; // 存储数据的栈
	std::stack<int> minStack;  // 存储最小值的栈
};

//int main() {
//	MinStack minStack;
//
//	minStack.push(-2);
//	minStack.push(0);
//	minStack.push(-3);
//
//	std::cout << "栈中最小元素是：" << minStack.getMin() << std::endl; // 输出 -3
//
//	minStack.pop();
//
//	std::cout << "栈中顶部元素是：" << minStack.top() << std::endl; // 输出 0
//	std::cout << "栈中最小元素是：" << minStack.getMin() << std::endl; // 输出 -2
//
//	return 0;
//}


/// <summary>
/// 队列中可以看到的人数
/// </summary>
vector<int> canSeePersonsCount(vector<int>& heights) {
	int n = heights.size();
	stack<int> stack;
	vector<int> res(n, 0);
	//除了最后一个人，其余的人都能看到相邻右边的人，如果右边的人比自己矮，
	// 则进入循环，加一，如果右边的人比自己高，那么不进入循环，此时栈不为空，加一
	for (int i = n - 1; i >= 0; i--) {
		int h = heights[i];
		while (!stack.empty() && stack.top() < h) {
			stack.pop();
			res[i] += 1;
		}
		if (!stack.empty()) {
			res[i] += 1;
		}
		stack.push(h);
	}
	return res;

}

vector<int> canSeePersonsCount1(vector<int>& heights) {
	int n = heights.size();
	stack<int>st;
	vector<int>ans(n,0);
	for (int i = 0; i < n; i++)
	{
		//遇到下一个更大元素，正常处理
		while (!st.empty() && heights[i] > heights[st.top()]) {

			ans[st.top()] += 1;
			st.pop();
		}
		//在当前元素和下一个更大元素中间的处理
		if(!st.empty()) ans[st.top()] += 1;

		st.push(i);
	}
	return ans;
}

//int main() {
//	vector<int>height = { 10,6,8,5,11,9 };
//	vector<int>ans = canSeePersonsCount1(height);
//	for (auto a : ans) cout << a << " ";
//	return 0;
//}

vector<int> test(vector<int>& nums) {
	int n = nums.size();
	stack<int>st;
	vector<int>ans(n, -1);
	for (int i = 0; i < n; i++)
	//for (int i = n-1; i >=0; i--)
	{
		while (!st.empty() && nums[i] > nums[st.top()])
		{
			ans[st.top()] = nums[i];
			st.pop();

		}
		//if (!st.empty()) { ans[i] = nums[st.top()]; }
		st.push(i);
	}
	return ans;
}

//int main() {
//	vector<int>nums = { 1,3,4,2 };
//	vector<int> ans = test(nums);
//	for (auto a : ans) cout << a << " ";
//	return 0;
//}


vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
	vector<int> result;
	deque<int> dq;

	for (int i = 0; i < nums.size(); ++i) {
		// 删除队列中不在当前窗口范围内的元素
		while (!dq.empty() && dq.front() < i - k + 1)
			dq.pop_front();

		// 删除队列中小于当前元素的元素，因为它们不可能是窗口最大值
		while (!dq.empty() && nums[dq.back()] < nums[i])
			dq.pop_back();

		dq.push_back(i);

		// 将窗口最大值加入结果集
		if (i >= k - 1)
			result.push_back(nums[dq.front()]);
	}

	return result;
}

//int main() {
//	std::vector<int> nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
//	int k = 3;
//	std::vector<int> result = maxSlidingWindow(nums, k);
//
//	std::cout << "Sliding window maximums: ";
//	for (int num : result)
//		std::cout << num << " ";
//	std::cout << std::endl;
//
//	return 0;
//}