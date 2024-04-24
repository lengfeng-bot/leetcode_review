#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<stack>
#include<queue>
#include<string>
using namespace std;



/// <summary>
/// �ַ�������
/// </summary>
/// �漰����Ե�[,]����(,)�������һ����ջ�������ҵ���Ӧ�����
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
/// ɾ���ַ����е����������ظ���
/// </summary>
/// �����Ŀ����֮�����ڣ����ֱ��ʹ��ջ�Ļ���������Ƿ���ģ�����Ҫ��������һ�¡�Ȼ��
/// ���ǿ���ֱ�Ӱ��ַ�������һ��ջ����Ϊ�ַ�������������ջ�ͳ�ջ���ƵĽӿڣ������Ļ�ֱ�����£�
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
/// ��ջʵ�ֶ���
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
/// �ö���ʵ��ջ
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
		while (size--) { // ������ͷ����Ԫ�أ��������һ��Ԫ���⣩ ������ӵ�����β��
			que.push(que.front());
			que.pop();
		}
		int result = que.front(); // ��ʱ������Ԫ��˳�����ջ��˳����
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
/// ����滻��Ĵ��Ƿ���Ч
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
/// �沨�����ʽ��ֵ
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



/// ���ܼ�������ջ����Ŀ
/// 
/// 
/// 
/// <summary>
/// 1.��Ʊ�۸���
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
/// 2.ÿ���¶�
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
/// ��һ������Ԫ��1
/// </summary>
/// ����ջ���Ϲ�ϣ��
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
	//����ջ��ʣ���Ԫ��
	while (!st.empty()) {
		map[nums2[st.top()]] = -1; // ջ��ʣ��Ԫ��û����һ������Ԫ��
		st.pop();
	}
	for (auto num : nums1) {
		ans.push_back(map[num]);
	}

	return ans;
}
/// <summary>
/// ��һ������Ԫ��2
/// </summary>
/// ���������Ĳ�֮ͬ�����ڣ����ѭ�������ˣ����Ҳ���Ҫ��ϣӳ�䣬�����˺���
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
/// 3.����ˮ
/// </summary>
/// �����Ĺؼ��ǣ���Ҫ����ߵ�һ���ȵ�ǰԪ�ش�ģ���Ҫ���ұߵģ��Ҿ��ÿ��Խ����������飬�ֱ��ʾ��ǰԪ����һ������Ԫ�ص�λ�á�
/// �õ�����������֮�󣬼���һ��СС���жϣ���������׵õ�ÿ��Ԫ���ܽӵ�ˮ�����ˡ�
/// �������˼·��Щ���⣺��Ҫ�ҵĲ��ǵ�һ���ȵ�ǰ���Ԫ�أ����ǵ�ǰԪ����߻����ұ�����Ԫ�ز��С���Ҫ�Ľ��������.
/// ��Ȼ���Ľ�֮�������ˣ��������ǿ��˿��ٷ���⣬�õ�����ջ���������ˡ��Ұѹٷ��ⷨ��������
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
/// �ҿ�������,������ұߵ�һ�������Ԫ�أ�ͬʱ��ջ��Ԫ�ص���һ��Ԫ�ؾ�����߸���Ԫ�أ�Ȼ����(����)��⣬�ֱ�����ߺͿ���������ǰ���������
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
/// ��״ͼ�����ľ���
/// </summary>
/// �����ͽ���ˮ̫���ˣ�һ���������߸���Ԫ�أ�һ�������߸�СԪ�ء�������Ҫע�����
int largestRectangleArea(vector<int>& heights) {

	stack<int>s;
	int sum = 0;
	//��β������0�Ļ���ÿ��Ԫ�����߶��и�СԪ����

	heights.insert(heights.begin(), 0); // ����ͷ������Ԫ��0
	heights.push_back(0); // ����β������Ԫ��0
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
/// ��Сջ
/// </summary>
class MinStack {
public:
	MinStack() {
	}

	// ѹջ������ͬʱ������Сֵ
	void push(int x) {
		dataStack.push(x);
		if (minStack.empty() || x <= minStack.top()) {
			minStack.push(x);
		}
	}

	// ��ջ������ͬʱ������Сֵ
	void pop() {
		if (!dataStack.empty()) {
			if (dataStack.top() == minStack.top()) {
				minStack.pop();
			}
			dataStack.pop();
		}
	}

	// ��ȡջ��Ԫ��
	int top() {
		return dataStack.top();
	}

	// ��ȡջ����СԪ��
	int getMin() {
		return minStack.top();
	}

private:
	std::stack<int> dataStack; // �洢���ݵ�ջ
	std::stack<int> minStack;  // �洢��Сֵ��ջ
};

//int main() {
//	MinStack minStack;
//
//	minStack.push(-2);
//	minStack.push(0);
//	minStack.push(-3);
//
//	std::cout << "ջ����СԪ���ǣ�" << minStack.getMin() << std::endl; // ��� -3
//
//	minStack.pop();
//
//	std::cout << "ջ�ж���Ԫ���ǣ�" << minStack.top() << std::endl; // ��� 0
//	std::cout << "ջ����СԪ���ǣ�" << minStack.getMin() << std::endl; // ��� -2
//
//	return 0;
//}


/// <summary>
/// �����п��Կ���������
/// </summary>
vector<int> canSeePersonsCount(vector<int>& heights) {
	int n = heights.size();
	stack<int> stack;
	vector<int> res(n, 0);
	//�������һ���ˣ�������˶��ܿ��������ұߵ��ˣ�����ұߵ��˱��Լ�����
	// �����ѭ������һ������ұߵ��˱��Լ��ߣ���ô������ѭ������ʱջ��Ϊ�գ���һ
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
		//������һ������Ԫ�أ���������
		while (!st.empty() && heights[i] > heights[st.top()]) {

			ans[st.top()] += 1;
			st.pop();
		}
		//�ڵ�ǰԪ�غ���һ������Ԫ���м�Ĵ���
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
		// ɾ�������в��ڵ�ǰ���ڷ�Χ�ڵ�Ԫ��
		while (!dq.empty() && dq.front() < i - k + 1)
			dq.pop_front();

		// ɾ��������С�ڵ�ǰԪ�ص�Ԫ�أ���Ϊ���ǲ������Ǵ������ֵ
		while (!dq.empty() && nums[dq.back()] < nums[i])
			dq.pop_back();

		dq.push_back(i);

		// ���������ֵ��������
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