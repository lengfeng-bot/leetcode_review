#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;


/*
///排序算法通常按照时间复杂度进行分类
1.时间复杂度为O(n2)  
  --冒泡排序
  --选择排序
  --插入排序
2.时间复杂度为O(nlog(n))
  --希尔排序
  --堆排序
  --快速排序
  --归并排序
3.时间复杂度为O(n))
  --计数排序
  --基数排序
  --桶排序
*/
void swap(int &a, int &b) {
	int tem = a;
	a = b;
	b = tem;
}

void print(vector<int> nums) {
	for (const int& num : nums) {
		std::cout << num << " ";
	}

	std::cout << std::endl;
}

/*
对于时间复杂度为O(n2)的排序方法，基本上用不到，但是面试的时候有可能会让你敲一个，所以要会自己敲才行
*/

//冒泡排序(稳定）
void bubbleSort(vector<int> &nums)
{
	int n = nums.size();
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n-i-1; j++)
		{
			if (nums[j + 1] < nums[j])
				swap(nums[j + 1], nums[j]);
		}

}

/// <summary>
/// 选择排序(不稳定)
/// </summary>
void selectionSort(vector<int>& nums)
{
	int n = nums.size();
	int minIndex = 0;
	for (int i = 0; i < n - 1; i++) 
	{
		minIndex = i;
		for (int j = i+1; j < n; j++)
		{
			if (nums[minIndex] > nums[j])
				minIndex = j;
		}
	// 将最小元素交换至首位
	int temp = nums[i];
	nums[i] = nums[minIndex];
	nums[minIndex] = temp;
	}

}

/// <summary>
/// 插入排序(稳定)
/// </summary>
void insertSort(vector<int>& nums) {

	int n = nums.size();
	for (int i = 1; i < n; i++)
	{
		int j = i;
		while (j >= 1 && nums[j] < nums[j - 1]) {
			swap(nums[j], nums[j - 1]);
			j--;
		}	
	}
}

/// <summary>
/// 插入排序还有一个重要用途--操作链表！
/// </summary>
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
	
};

ListNode* insertionSortList(ListNode* head) {

	if (head == nullptr) {
		return head;
	}
	ListNode* dummyHead = new ListNode(0);
	dummyHead->next = head;
	ListNode* lastSorted = head;
	ListNode* curr = head->next;
	while (curr != nullptr) {
		if (lastSorted->val <= curr->val) {
			lastSorted = lastSorted->next;
		}
		else {
			ListNode* prev = dummyHead;
			while (prev->next->val <= curr->val) {
				prev = prev->next;
			}
			lastSorted->next = curr->next;
			curr->next = prev->next;
			prev->next = curr;
		}
		curr = lastSorted->next;
	}
	return dummyHead->next;
}

/// <summary>
/// 希尔排序
/// </summary>
void shellSort(vector<int>& nums)
{
	for (int gap = nums.size() / 2; gap > 0; gap /= 2) // 外层遍历增量序列元素
	{

		for (int i = 0; i < gap; ++i) // 内层循环遍历每个分组，gap等于分组数
		{

			// 对每个分组依次进行插入排序
			for (int j = i + gap; j < nums.size(); j += gap) // 假设每组第一个元素有序，然后遍历待排数组
			{
				for (int k = i; k < j; k += gap) // 从左边开始依次遍历有序数组，找到合适的位置，然后该位置所有元素依次右移一位，将待排元素插入该位置
				{
					// 注：从第j个待排元素开始排序，说明前面有j-1个有序数组，故j是遍历有序数组终止条件
					if (nums[k] > nums[j]) // 待排序元素从有序数组左边第一个开始寻找，找到第一个大于待排元素的数，即为要插入的位置；如果没找到，则说明不用变
					{
						int tmp = nums[j];
						for (int p = j; p > k; p -= gap) // 找到第k元素为要插入的位置，k+gap后面待排元素依次往后移一位，直到j位置截止
						{
							nums[p] = nums[p - gap]; // 注意：这里要确保减法溢出不为负数！
						}
						nums[k] = tmp; // 将待排序元素插入第k位置，完成一个待排元素排序
						break; // 跳出遍历有序数组，进行下一个待排元素排序
					}

				}
			}
		}
	}


}

/// <summary>
/// 堆排序
/// </summary>

/// 调整堆
void heapify(vector<int>&nums, int n, int i) {
	int largest = i;         //设此节点为最大节点
	int lson = i * 2 + 1;    //找到它的左孩子下标
	int rson = i * 2 + 2;	//找到右孩子下标
	if (lson<n && nums[lson]>nums[largest])
	{
		largest = lson;
	}	
	if (rson<n && nums[rson]>nums[largest])
	{
		largest = rson;
	}
	if (largest != i) {
		swap(nums[largest], nums[i]);
		heapify(nums,n,largest);
	}


}




void heapSort(vector<int>&nums) {

	//构建一个大顶堆
	int n = nums.size();
	int lastNode = n - 1; //数组长度为n
	int parent = (lastNode - 1) / 2;

	for (int i = parent; i >= 0; i--) {
		heapify(nums,n,i);
	}  //到这里已经成为了一个大顶堆

		//排序
	for (int i = n - 1; i >= 0; i--) {
		swap(nums[i], nums[0]);  //最后一个元素和第一个元素（大顶堆）做交换
		heapify(nums, i, 0);  //交换完之后还要维护大顶堆性质
	}



}


//快速排序
void quickSort(vector<int>& nums, int left, int right) {

	if (left >= right)
		return;
	int l = left;
	int r = right;
	int pivot = nums[l];
	while (l < r)
	{
		while (nums[r] >= pivot && l < r)
			r--;
		while (nums[l] <= pivot && l < r)
			l++;
		if (l < r) {
		int temp = nums[l];
		nums[l] = nums[r];
		nums[r] = temp;
		}

	}
	nums[left] = nums[l];
	nums[l] = pivot;
	quickSort(nums,left,l-1);
	quickSort(nums,l+1,right);

}



//void quickSort2(vector<int>& nums, int left, int right) {
//
//	if (left >= right)
//		return;
//
//	int i = left;
//	int j = right;
//	int key = nums[left];
//	while (i<j)
//	{
//		while (nums[j] >= key&&i<j)
//			j--;
//		while (nums[i] <= key&&i<j)
//			i++;
//		if(i<j){
//		int temp = nums[i];
//		nums[i] = nums[j];
//		nums[j] = temp;}
//
//	}
//	nums[left] = nums[i];
//	nums[i] = key;
//	quickSort2(nums, left, i - 1);
//	quickSort2(nums, i + 1, right);
//
//}




/// <summary>
/// 归并排序
/// </summary>
void mergeSort(vector<int>& nums,int left,int right) {
	if (left >= right) return;
	int mid = left + (right - left) / 2;
	mergeSort(nums, left, mid);
	mergeSort(nums, mid + 1, right);
	int* ans = new int[right-left+1];
	int i = left;
	int j = mid + 1;
	int k = 0;
	while (i<=mid&&j<=right)
	{
		if (nums[i] <= nums[j])
			ans[k++] = nums[i++];
		else
		{
			ans[k++] = nums[j++];
		}
	}
	while (i<=mid)
	{
		ans[k++] = nums[i++];
	}
	while (j<=right)
	{
		ans[k++] = nums[j++];
	}
	k = 0;
	for (int i = left; i < right; i++)
	{
		nums[i] = ans[k++];
	}
	delete[] ans;

}


//int main() {
//	vector<int>nums = { 1,6,2,3,5,4 };
//	print(nums);
//	//bubbleSort(nums);
//	//selectionSort(nums);
//	//insertSort(nums);
//	//shellSort(nums);
//	//heapSort(nums);
//	//quickSort(nums,0,nums.size()-1);
//	mergeSort(nums, 0, nums.size());
//	print(nums);
//
//}