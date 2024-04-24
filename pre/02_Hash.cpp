#include <iostream>
#include<vector>
#include<algorithm>
#include <unordered_map>
#include<unordered_set>
#include<stack>



using namespace std;


//STL�й�ϣ��Ļ����÷�
void basic()
{
	std::unordered_map<std::string, int> myMap;

	// ��Ӽ�ֵ��
	myMap["Alice"] = 25;
	myMap["Bob"] = 30;
	myMap["Charlie"] = 35;


	//ɾ����ֵ��
	myMap.erase("Bob");

	// �����Ƿ����
	if (myMap.find("David") != myMap.end()) {
		std::cout << "David's age is: " << myMap["David"] << std::endl;
	}
	else {
		std::cout << "David is not in the map." << std::endl;
	}
	// ������ϣ����1
	for (auto it = myMap.begin(); it != myMap.end(); it++) {
		std::cout << it->first << "'s age is: " << it->second << std::endl;
	}
	// ������ϣ����2
	for (const auto& pair : myMap) {
		std::cout << pair.first << "'s age is: " << pair.second << std::endl;
	}
}

//int main()
//{
//
//	basic();
//	return 0;
//}



/// <summary>
/// 1.����֮��--��ϣʵ��
/// </summary>
vector<int> twoSum(std::vector<int>& nums, int target) {
	unordered_map<int, int>map;
	vector<int>result;
	for (int i = 0; i < nums.size(); i++)
	{
		int other = target - nums[i];
		if (map.find(other) != map.end())
		{
			result.push_back(map[other]);
			result.push_back(i);
			return result;
		}
		map[nums[i]] = i;

	}
	return result;
}


//int main() {
//	std::vector<int> nums = { 2, 7, 11, 15 };
//	int target = 14;
//	std::vector<int> result = twoSum(nums, target);
//
//	if (result.size() == 2) {
//		std::cout << "Indices: " << result[0] << " and " << result[1] << std::endl;
//	}
//	else {
//		std::cout << "No solution found." << std::endl;
//	}
//
//	return 0;
//}


/// <summary>
/// ���ظ�����Ӵ��ĳ���
/// </summary>
int lengthOfLongestSubstring(string s) {
	unordered_map<char, int>map;
	int i =0, j = 0;
	int maxlen = 0;
	while (j<s.size())
	{
		if (map[s[j]] == 0) { map[s[j]]++; j++; }
		else { map[s[i]]--; i++; }

		maxlen = max(maxlen, j - i);
	}
	return maxlen;
}



//int main() {
//	string s = "abcb"; // ��������
//	cout << "���ظ��ַ�����Ӵ�����Ϊ��" << lengthOfLongestSubstring(s) << endl;
//	return 0;
//}

/// <summary>
/// ��������ת����
/// </summary>
int romanToInt(string s) {

	unordered_map<char, int>map;
	map['I'] = 1;
	map['V'] = 5;
	map['X'] = 10;
	map['L'] = 50;
	map['C'] = 100;
	map['D'] = 500;
	map['M'] = 1000;

	int result = 0;
	int prevValue = 0;

	for (int i = s.length() - 1; i >= 0; i--) {
		int currentValue = map[s[i]];

		// �����ǰ�ַ����������С��ǰһ���ַ�����Ҫ��ȥ
		if (currentValue < prevValue) {
			result -= currentValue;
		}
		// ���򣬼��ϵ�ǰ�ַ����������
		else {
			result += currentValue;
		}

		prevValue = currentValue;
	}

	return result;
	

}


//int main()
//{
//	string  s1 = { "IV" };
//	int a = romanToInt(s1);
//	cout << a << endl;
//	return 0;
//}



//Ψһ��֮��
int sumOfUnique(vector<int>& nums) {

	unordered_map<int, int> hashMap;
	int sum = 0;

	for (int i = 0; i < 100; ++i) {
		hashMap[i] = 0;
	}
	for (int i = 0; i < nums.size(); i++)
	{
		hashMap[nums[i]]++;
	}
	for (int i = 0; i < nums.size(); i++)
	{
		if (hashMap[nums[i]] == 1)
			sum += nums[i];
	}
	return sum;
}


/// <summary>
/// �����黮�ֳ��������
/// </summary>
bool divideArray(vector<int>& nums) {
	unordered_map<int, int> hashMap;

	for (int i = 0; i < 501; ++i) {
		hashMap[i] = 0;
	}
	for (int i = 0; i < nums.size(); i++)
	{
		hashMap[nums[i]]++;
	}
	for (int i = 0; i < nums.size(); i++)
	{
		if (hashMap[nums[i]] / 2 != 0)
			return false;
		

	}
	return true;

}


/// <summary>
/// �жϾ����Ƿ�Ϊȫ��ĸ��
/// </summary>
bool checkIfPangram(string sentence) {
	unordered_map<char, int> hashMap;
	for (int i = 0; i < 26; i++)
	{
		hashMap['a'+i] = 0;
	}
	for (int i = 0; i < sentence.size(); i++)
	{
		hashMap[sentence[i]]++;
	}
	for (int i = 0; i < 26; i++)
	{
		if (hashMap['a' + i] == 0)
			return false;
	}

	return true;

}



/// <summary>
/// �����Եĸ���
/// </summary>
int numIdenticalPairs(vector<int>& nums) {
	unordered_map<int, int> hashMap;
	int ans = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		ans += hashMap[nums[i]];
		hashMap[nums[i]]++;
	}
	return ans;

}

//int main() {
//	vector<int>nums = { 1,2,1,5,1 };
//	int r = numIdenticalPairs(nums);
//	cout << r << endl;
//}



/// <summary>
/// ��ľ���ֵΪ K ��������Ŀ
/// </summary>

int countKDifference(vector<int>& nums, int k) {
	int result = 0;
	unordered_map<int, int>map;
	for (int i = 0; i < 100; ++i) {
		map[i] = 0;
	}
	for (int i = 0; i < nums.size(); i++)
	{
		int x = nums[i] - k;
		if(x>=1&&x<=100)
			result+=map[x];
		x = nums[i] + k;
		if (x >= 1 && x <= 100)
			result += map[x];
		map[nums[i]]++;
	}
	return result;

}


//int main() {
//	vector<int>nums = {3,2,1,5,4};
//	int k = 2;
//	int r = countKDifference(nums,k);
//	cout <<r<< endl;
//}



/// <summary>
/// ����ͬ�Ķ�Ԫ������
/// </summary>
/// ����һ---��ϣ��ǰ׺��
int numSubarraysWithSum1(vector<int>& nums, int goal) {	
	
	int n = nums.size();
	unordered_map<int, int>map;
	int count = 0;
	int presum = 0;
	for (int i = 0; i < n; i++)
	{
		presum += nums[i];
		if (presum == goal)
		{
			count++;
		}
		//���ǰ׺�����Ѿ��� prefixSum - goal��˵����ǰλ�õ�ǰһ��λ�õ��������Ϊ goal
		if (map.find(presum - goal) != map.end()) 
		{
		count += map[presum - goal];
		}
		// ����ǰ׺�ͼ���
		map[presum]++;
	}
	return count;
}

//�������ڽⷨ
int numSubarraysWithSum(vector<int>& nums, int k) 
{	
	//int left1 = 0;
	//int left2 = 0
	//int sum1 = 0;
	//int sum2 = 0;
	//int count = 0;
	//for (int right = 0; right < nums.size(); right++)
	//{
	//	sum1 += nums[right];
	//	while(left1<=right&&sum1 > goal)
	//	{
	//		sum1 -= nums[left1];
	//		left1++;
	//	}

	//	sum2 += nums[right];
	//	while(left2 <= right && sum2 >= goal)
	//	{
	//		sum2 -= nums[left2];
	//		left2++;
	//	}
	//	if (sum1 == goal) {
	//		count += (left2 - left1);
	//	}

	//}
	//	return count;
	int n = nums.size();
	int left = 0;
	int sum = 0;
	int count = 0;

	for (int right = 0; right < n; right++) {
		sum += nums[right];

		while (left <= right && sum > k) {
			sum -= nums[left];
			left++;
		}

		if (sum == k) {
			count++;
		}
	}

	return count;
}


//int main() {
//	vector<int> nums = { -1,-1,1 };
//	int goal = 0;
//	int result = numSubarraysWithSum(nums, goal);
//	cout << "���к�Ϊ " << goal << " �ķǿ�����������Ϊ��" << result << endl;
//
//	return 0;
//}



/// <summary>
/// ����֮��
/// </summary>
vector<vector<int>> threeSum(vector<int>& nums) {

	vector<vector<int>> ans;
	int n = nums.size();
	sort(nums.begin(), nums.end());
	for (int i = 0; i < n - 2; i++)
	{
		if (i > 0 && nums[i] == nums[i - 1]) {
			continue;
		}
		int l = i+1;
		int r = n - 1;
		while (l < r)
		{
			int sum = nums[l] + nums[r] + nums[i];

			if (sum == 0)
			{
				ans.push_back({ nums[l], nums[r], nums[i] });
				while (l < r && nums[l] == nums[l + 1])
					l++;
				while (l < r && nums[r] == nums[r - 1])
					r--;


				l++;
				r--;
			}
			else if (sum > 0)
				r--;
			else
				l++;


		}
		
	}
	return ans;

}


//int main() {
//	vector<int> nums = { -1, 0, 1, 2, -1, -4 };
//	vector<vector<int>> result = threeSum(nums);
//
//	for (const vector<int>& triplet : result) {
//		for (int num : triplet) {
//			cout << num << " ";
//		}
//		cout << endl;
//	}
//
//	return 0;
//}



/// <summary>
/// ��ĸ��λ��
/// </summary>
/// ֻʹ��һ���򵥵�<char,int>��ϣ��Ļ��������ж�һ���ַ������е���λ��
/// ��ÿ������Ӧ�ɸü���ɵ�������ĸ��λ������ʱ��keyΪstring,��valueΪvector<value>
/// ֻ���ÿ����Ҫ�������ַ�����ֵ��key��֮�����򣬼����ҵ���Ӧ��ϵ
vector<vector<string>> groupAnagrams(vector<string>& strs) {
	vector<vector<string>>ans;
	unordered_map<string, vector<string>>map;
	for (auto str:strs){
		string key = str;
		sort(key.begin(), key.end());
		map[key].emplace_back(str);
	
	}		
	for (auto it = map.begin(); it != map.end(); ++it)
	{
			ans.emplace_back(it->second);
	}
	return ans;

}



//int main() {
//	vector<string> input = { "eat", "tea", "tan", "ate", "nat", "bat" };
//	vector<vector<string>> groupedAnagrams = groupAnagrams(input);
//
//	// Print the grouped anagrams
//	for (const vector<string>& group : groupedAnagrams) {
//		for (const string& word : group) {
//			cout << word << " ";
//		}
//		cout << endl;
//	}
//
//	return 0;
//}


///�Ƚ���һ�º͹�ϣ�����Ƶ�set�Ļ����÷�
///set����C++��׼���е�һ�����򼯺ϣ����ڴ洢Ψһ��Ԫ��
void unorder_set_basic() {

	unordered_set<int> myHashSet;

	// ����Ԫ��
	myHashSet.insert(10);
	myHashSet.insert(5);
	myHashSet.insert(8);
	myHashSet.insert(12);

	// ����Ԫ�ز����
	int searchValue = 8;
	std::unordered_set<int>::iterator it = myHashSet.find(searchValue);
	if (it != myHashSet.end()) {
		std::cout << "Ԫ�� " << searchValue << " �����ڼ����С�" << std::endl;
	}
	else {
		std::cout << "Ԫ�� " << searchValue << " �������ڼ����С�" << std::endl;
	}

	// ɾ��Ԫ��
	myHashSet.erase(5);

	// �������ϲ����
	std::cout << "�����е�Ԫ�أ�";
	for (const int& value : myHashSet) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	// ��鼯���Ƿ�Ϊ��
	if (myHashSet.empty()) {
		std::cout << "����Ϊ�ա�" << std::endl;
	}
	else {
		std::cout << "���ϲ�Ϊ�գ���СΪ��" << myHashSet.size() << std::endl;
	}

	// ʹ�� count ���Ԫ���Ƿ����
	int elementToCheck = 3;
	if (myHashSet.count(elementToCheck) == 1) {
		std::cout << elementToCheck << " �����ڼ����С�" << std::endl;
	}
	else {
		std::cout << elementToCheck << " �������ڼ����С�" << std::endl;
	}


}

/// <summary>
/// ���������
/// </summary>
int longestConsecutive(vector<int>& nums) {
	unordered_set<int>set;
	for (auto num : nums) set.insert(num);
	int curlen = 1, maxlen = 0;
	for (auto& num : nums) {
		if (set.count(num - 1) == 0) {
			int cur = num;
			curlen = 1;
			while (set.count(cur + 1))
			{
				cur++;
				curlen++;
			}
		}
		maxlen = max(curlen, maxlen);
	}
	return maxlen;

}


bool isValid(string s) {
	std::stack<char> stack;
	std::unordered_map<char, char> mapping = { {')', '('}, {']', '['}, {'}', '{'} };
	for (auto c : s) {
		if (mapping.count(c))
		{
			char topElement = stack.empty() ? '#' : stack.top();
			if (topElement != mapping[c]) {
				return false;
			}
			stack.pop();
		}
		else
			stack.push(c);
	
	}
	return stack.empty();
		

}


bool isValid1(string s) {
	if (s.size() % 2 == 1) return false;
	stack<char> st;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') st.push(')');
		else if (s[i] == '{') st.push('}');
		else if (s[i] == '[') st.push(']');
		else if (st.empty() || st.top() != s[i]) return false;
		else st.pop();
	}
	return st.empty();
}

//int main() {
//	string s = "{}[]()";
//	int ans = isValid1(s);
//	return 0;
//}

/// <summary>
/// ��Ч����ĸ��λ��
/// </summary>
bool isAnagram(string s, string t) {
	unordered_map<char, int>map;

	for (auto a : s) map[a]++;

	for (auto a : t) {
		if (map[a] > 0) map[a]--;
		else return false;
	}
	for (auto it = map.begin();it!=map.end();it++)
	{
		if (it->second > 0) return false;
	}
	return true;
}



vector<int> findAnagrams(string s, string p) {
	int sLen = s.size(), pLen = p.size();

	if (sLen < pLen) {
		return vector<int>();
	}

	vector<int> ans;
	vector<int> sCount(26);
	vector<int> pCount(26);
	for (int i = 0; i < pLen; ++i) {
		++sCount[s[i] - 'a'];
		++pCount[p[i] - 'a'];
	}

	if (sCount == pCount) {
		ans.emplace_back(0);
	}
	for (int i = 0; i < sLen - pLen; ++i) {
		--sCount[s[i] - 'a'];
		++sCount[s[i + pLen] - 'a'];

		if (sCount == pCount) {
			ans.emplace_back(i + 1);
		}
	}

	return ans;
}
//int main() {
//	std::string s = "abab";
//	std::string p = "ab";
//
//	std::vector<int> result = findAnagrams1(s, p);
//
//	std::cout << "Anagrams indices: ";
//	for (int index : result) {
//		std::cout << index << " ";
//	}
//	std::cout << std::endl;
//
//	return 0;
//}

int getSum(int n) {
	int ans = 0;
	while (n)
	{
		int a = n % 10;
		ans += a * a;
		n /= 10;
	}
	return ans;

}

/// <summary>
/// ������
/// </summary>
bool isHappy(int n) {
	
	unordered_set<int>set;
	int ans = 0;
	while (1)
	{
		ans = getSum(n);
		if (ans == 1)return true;
		else if (set.count(ans) > 0) return false;
		else set.insert(ans);
		n = ans;
	}
	
}

/// <summary>
/// �����
/// </summary>
bool canConstruct(string ransomNote, string magazine) {
	int map[26] = {0};
	for (auto m : magazine) map[m - 'a']++;
	for (auto r : ransomNote) {
		if (map[r - 'a'] > 0) map[r - 'a']--;
		else	return false;
	}
	return true;
}

//int main() {
//	string ransomNote = "aab";
//	string magazine = "aabb";
//
//	if (canConstruct(ransomNote, magazine)) {
//		cout << "���Թ��������" << endl;
//	}
//	else {
//		cout << "�޷����������" << endl;
//	}
//
//	return 0;
//}

