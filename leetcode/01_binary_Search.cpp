#include <iostream>
#include<vector>
#include<string>


using namespace std;


//ģ��1
/// <summary>
/// 1.��򵥵Ķ��ֲ���[left, right]
/// </summary>
int binarySearch1(vector<int>& nums, int target) {

	int len = nums.size();    
	int left = 0;
	int right = len - 1;             // [left, right]
	int mid = left + (right - left) / 2;
	while (left<=right)
	{
		if (nums[mid] == target)
			return mid;
		if (nums[mid] < target)
			left = mid + 1;
		else
			right = mid - 1 ;
		mid = left + (right - left) / 2;
	}

	return -1;
		
}





/// <summary>
/// 2.x��ƽ����
/// </summary>
/// <param name="x"></param>
/// <returns></returns>
int mySqrt(int x) {
	if (x == 0) return 0;
	int left = 1;
	int right = x;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (mid <= x / mid && (mid + 1) > x / (mid + 1)) 
			{ return mid; }
		else if ((mid + 1) <= x / (mid + 1))
		 { left = mid + 1; }
		else if 
			(mid > x / mid) { right = mid - 1; }
	}
	return -1;



}

int mySqrt1(int x) {
	if (x == 0) return 0;
	int ans = 1;
	int left = 1;
	int right = x;
	while (left < right) {
		int mid = left+(right-left)/2;
		if ((long long)mid * mid <= x) { ans = mid; left = mid + 1; }
		else right = mid;
	}
	return  ans;
}

bool isPerfectSquare(int num) {
	if (num == 0 || num == 1) return true;
	int left = 0;
	int right = num;             
	
	while (left <= right)
	{	int mid = left + (right - left) / 2;
		if (mid*mid == num)
			return true;
		if (mid * mid < num)
			left = mid + 1;
		else
			right = mid - 1;
	}

	return -1;
}

//int main() {
//
//	//vector<int>nums = { 1,2,3,4,5,6,7 };
//	//int tar = 0;
//	//int result = search(nums, tar);
//	//cout << result << endl;
//
//	int x = 2147483647;
//	int result = mySqrt1(x);
//	cout << result << endl;
//
//}




/// <summary>
/// 3. ������ת��������(���ȷʵֵ����ϸ����ʹ�ö��ַ����ֳ��ı��ǵ������䣬֮���ټ���ʹ�ö��ַ����в���Ŀ��ֵ)
/// </summary>

int searchplus(vector<int>& nums, int target) {

	int l = 0;
	int r = nums.size()-1;

	while (l < r)
	{
		int mid = l + (r - l) / 2;
		if (nums[mid] ==target)
			return mid;
		else if (nums[mid] >= nums[l]) {
			if (target == nums[mid])
				return mid;
			else if (target>= nums[l] && target< nums[mid])
				r = mid ;
			else 
				l = mid + 1;}

		else
		{
			if (target == nums[mid])
				return mid;
			else if (target > nums[mid] && target <= nums[r])
				l = mid + 1;
			else
				r = mid ;

		}

	}
	return -1;

}

//int main(){
//	vector<int>nums = { 4,5,6,7,0,1,2 };
//	int tar = 0;
//	int result = search(nums, tar);
//	cout << result << endl;
//	return 0;
//	}







//ģ��� ���ڲ�����Ҫ���������е�ǰ��������ֱ�����ھ�������Ԫ�ػ�������
int binarySearch2(vector<int>& nums, int target) {
	if (nums.size() == 0)
		return -1;

	int left = 0, right = nums.size();  //ע�⣡   // [left, right)
	while (left < right) {						//ע�⣡
		int mid = left + (right - left) / 2;
		if (nums[mid] == target) { return mid; }  //ע�⣡
		else if (nums[mid] < target) { left = mid + 1; }
		else { right = mid; }
	}

	// Post-processing:
	// End Condition: left == right
	if (left != nums.size() && nums[left] == target) return left;
	return -1;
}




/// <summary>
/// 1.Ѱ�ҷ�ֵ
/// </summary>
int findPeakElement(vector<int>& nums) {
	if (nums.size() == 1)return 0;

	int left = 0, right = nums.size() - 1;
	while (left < right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] > nums[mid + 1]) { right = mid-1; }
		else if (nums[mid] < nums[mid + 1]) { left = mid + 1; }
	}
	return left;
}




//int main(){
//	vector<int>nums = { 3,2,1};
//	
//	int result = findPeakElement(nums);
//	cout << result << endl;
//	return 0;
//	}


/// <summary>
/// 2.Ѱ����ת���������е���Сֵ
/// </summary>
int findMin(vector<int>& nums) {
	if (nums.size() == 1)return 0;

	int left = 0, right = nums.size() - 1;
	while (left < right) {
		int mid = left + (right - left) / 2;
		if (nums[left] < nums[right]) { return nums[left]; }
		else  if (nums[mid] >= nums[left])left = mid + 1;
		else right = mid;
	}

	return nums[left];

}


int findMin1(vector<int>& nums) {
	int l = 0, r = nums.size() - 1;
	while (l<r)
	{
		int mid = l + (r - l) / 2;
		if (nums[l] < nums[r]) return nums[l];
		else if (nums[mid] >= nums[l]) { l = mid+1;  cout << "����ѡ��Ϊ:[" << l << "," << r << "]" << endl; }
		else { r = mid; cout << "����ѡ��Ϊ:[" << l << "," << r << "]" << endl; }
	}
	return nums[l];
}

//int main() {
//	vector<int>nums = { 1,2,3};
//
//	int result = findMin2(nums);
//	cout << result << endl;
//	return 0;
//}





/// <summary>
/// ģ����-����������Ҫ���ʵ�ǰ���������������е�ֱ�������ھ�������Ԫ�ػ�������
/// </summary>
int binarySearch3(vector<int>& nums, int target) {  
	if (nums.size() == 0)
		return -1;

	int left = 0, right = nums.size() - 1;     //// (left, right)
	while (left + 1 < right) {
		// Prevent (left + right) overflow
		int mid = left + (right - left) / 2;
		if (nums[mid] == target) {
			return mid;
		}
		else if (nums[mid] < target) {
			left = mid;
		}
		else {
			right = mid;
		}
	}

	// Post-processing:
	// End Condition: left + 1 == right
	if (nums[left] == target) return left;
	if (nums[right] == target) return right;
	return -1;
}





/// <summary>
/// 1.�����������в���Ԫ�صĵ�һ�������һ��λ��
/// </summary>
vector<int> searchRange(vector<int>& nums, int target) {
	vector<int> arr = { -1, -1 };

	int left = 0, right = nums.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		int mid1 = mid;

		if (nums[mid] == target) {
			while (mid > 0 && nums[mid - 1] == nums[mid]) {
				mid--;
			}
			while (mid1 < nums.size() - 1 && nums[mid1 + 1] == nums[mid1]) {
				mid1++;
			}
			arr[0] = mid;
			arr[1] = mid1;
			return arr;
		}
		else if (nums[mid] < target) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	return arr;
}


/// <summary>
/// ��������������
/// </summary>
vector<int> searchRange1(vector<int>& nums, int target) {
	int n = nums.size();
	int l = 0, r = n-1;
	vector<int>ans = { -1,-1 };
	while (l<r)
	{
		int mid = (l + r) >> 1;
		if (nums[mid] >= target) r = mid;
		else l = mid + 1;
	}
	if (nums[l] == target) ans[0] = l;

	int c = 0, d = n ;
	while (c < d)
	{
		int mid = (c + d) >> 1;
		if (nums[mid] <= target) c = mid+1;
		else d = mid;
	}
	if (c == 0) ans = {-1,-1};
	else if (nums[c-1] == target) ans[1] = c-1;

	return ans;
}

//int main() {
//
//	vector<int>nums = { 1};
//	int tar = 0;
//	vector<int> result = searchRange1(nums, tar);
//
//	cout << result[0]<<" "<<result[1] << endl;
//
//}




/// <summary>
/// 2.�ҵ� K ����ӽ���Ԫ��
/// </summary>
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
	vector<int>  a;
	int left = 0, right = arr.size() - k;
	while (left < right) {
		int mid = left + (right - left) / 2;
		if (x-arr[mid] > arr[mid + k] - x)left = mid + 1;    //ѡ������[4,5,6]����[3,4,5]�Ĺؼ�����[3,4,5,6]���ж�ɾ��3����6���൱���������Ϊһ������֮�����
		else right = mid;
	}
	for (int i = left; i < k+left; i++)
	{
		a.push_back(arr[i]);
	}
	return a;
}

//int main() {
//
//	vector<int>nums = { 1,1,1,10,10,10};
//	int k = 1;
//	int x = 9;
//	vector<int> result = findClosestElements(nums,k,x);
//
//	for (int i = 0; i < result.size(); i++)
//	{
//		cout <<result[i] << endl;
//	}
//	
//
//}



/// <summary>
/// �ۺ�����
/// </summary>
/// 1.x��n�η�
/// 
double traval(double x, int n) {
	if (n == 0) {
		return 1;
	}
	double val = traval(x, n / 2);
	return n % 2 == 0 ? val * val : val * val * x;
}


double myPow(double x, int n) {
	if (n == 0) {
		return 1;
	}
	int N = n > 0 ? n : 0 - n;
	double val = traval(x, N);
	return n > 0 ? val : 1 / val;
}


/// <summary>
/// 2.Ѱ�ұ�Ŀ����ĸ�����С��ĸ
/// </summary>
char nextGreatestLetter(vector<char>& letters, char target) {

	int left = 0, right = letters.size()-1;  //ע�⣡   // [left, right)

	while (left < right) {						//ע�⣡
		int mid = left + (right - left) / 2;
		 if (letters[mid] > target)
				right = mid;

		else if (letters[mid] <= target) { left = mid + 1; }
		
	}
	if (target >= letters[letters.size() - 1]) return letters[0];
	return letters[left];

	//return letters[left] <= target ? letters[0] : letters[left];
}


//int main() {
//	vector<char> s = { 'c','f','j'};
//	char target = 'c';
//	char c = nextGreatestLetter(s,target);
//	cout << c << endl;
//
//
//}




//������ת��������2
//�����1��һ���ĵ����ڿ������ظ�Ԫ�أ������Ļ��������һ�����⡣����������������һ���ǲ�����������(��ֵ��һ��),��ôʣ�µ�һ�������û���ж��ǵ������Ƿǵ�����
//����˵��� [1,0,1,1,1] �����Ļ���0 ���ȿ�����100��Ҳ������0��������Ҫ���ж�����

//��˵�������м�����߶�����������������ֻ�ܽ���ǰ�����������߽��һ���ұ߽��һ��Ȼ�����������ϼ������ֲ��ҡ�������ʱ�临�Ӷȶ�O(n)�ˣ�������
bool search(vector<int>& nums, int target) {
	int n = nums.size();
	int left = 0, right = n - 1;
	while (left<=right)
	{
		int mid = left + (right- left) / 2;
		if (nums[mid] == target) return true;
		//��ӵ����У�����û������������[1,1,1,1,1,1,1,1,2,1,1],���߶����м���ͬ����û���ж���һ���ˣ�����ֻ�����ͷ�в�ͨ����Ҫ������У�
		// �������Ļ����ö��ַ���û�����ˣ�O��n���Ĵ������о�д���ˣ�������ô����ô�죿��
		else if (nums[mid] == nums[right]) { right = mid - 1;  cout << "����ѡ��Ϊ:[" << left << "," << right << "]" << endl; }
		else if (nums[mid] == nums[left]) { left = mid + 1;  cout << "����ѡ��Ϊ:[" << left << "," << right << "]" << endl; }

		else if (nums[mid] >= nums[right]) {
			if (nums[mid] == target) return true;
			else if (nums[left] <= target && target<nums[mid]) right = mid - 1;
			else left = mid + 1;
			cout << "����ѡ��Ϊ:[" << left << "," << right << "]" << endl;
		}
		else {
			if (nums[mid] == target) return true;
			else if (nums[right] >= target && target>nums[mid]) left = mid + 1;
			else right = mid - 1;
			cout << "����ѡ��Ϊ:[" << left << "," << right << "]" << endl;
		}

	}
	return false;
		

	
}


int leftbound(vector<int>nums, int target) {
	int n = nums.size();
	int l = 0, r = n - 1;
	while (l<r)
	{
		int mid = (l + r) >> 1;
		if (nums[mid] == target) r = mid;
		else if (nums[mid] > target) r = mid;
		else l = mid + 1;
	}
	if (nums[l] == target) return l;
	return -1;
}

int rightbound(vector<int>nums, int target) {
	int n = nums.size();
	int l = 0, r = n-1;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (nums[mid] == target) l = mid+1;
		else if (nums[mid] < target) l = mid+1;
		else r = mid;
	}
	if (l == 0) return -1;
	if (l == n-1) return l;
	return nums[l - 1] == target ? (l - 1) : -1;
	
}




int findMin2(vector<int>& nums) {
	int left = 0, right = nums.size() - 1;
	while (left < right) {
		int mid = left + (right - left) / 2;

		if (nums[left] < nums[right]) { return nums[left]; }
		else  if (nums[mid] > nums[left])left = mid + 1;
		else left++;
	}

	return nums[left];
}

//int main(){
//	vector<int>nums = {10,10,10,1,10};
//	int ans = findMin2(nums);
//	cout << ans;
//	return 0;
//}


