#include<iostream>
#include<vector>
#include <functional>
#include<deque>
#include <queue>

using namespace std;



// ����������ڵ�ṹ
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


/// <summary>
/// �ͷŶ�����
/// </summary>
void  freeTree(TreeNode* root) {
    if(root)
    {
        freeTree(root->right);
        freeTree(root->left);
        delete  root;

    }
}


///�������ı���
/// ǰ�����  �� �� ��
/// �������  �� �� ��
/// ��������  �� �� ��
// �����ݹ麯��
void inorderHelper(TreeNode* node, vector<int>& result) {
    if (node == nullptr)
        return;
    inorderHelper(node->left, result);
    result.push_back(node->val);
    inorderHelper(node->right, result);
}

// �����������
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    inorderHelper(root, result);
    return result;
}

/// <summary>
/// ����������Ľڵ����
/// </summary>
int countNodes(TreeNode* root) {
    if (!root)
    {
        return 0;
    }
    return countNodes(root->left) + countNodes(root->right) + 1;
}


/// <summary>
/// ���������������
/// </summary>
int maxDepth(TreeNode* root) {

    if (!root)
    {
        return 0;
    }
    return max(maxDepth(root->right), maxDepth(root->left))+1;

}


/// <summary>
/// �������������С���
/// </summary>
int minDepth(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    if (!root->left || !root->right)  return minDepth(root->right) + minDepth(root->left) + 1;  //important!
    return min(minDepth(root->right), minDepth(root->left)) + 1;
}


//int main() {
// /*����һ��������
//        1
//       / \
//      5    2
//          / \
//         3   4
//*/
//    TreeNode* root = new TreeNode(1);
//    root->left = new TreeNode(5);
//    root->right = new TreeNode(2);
//    root->right->left = new TreeNode(3);
//    root->right->right = new TreeNode(4);
//
//    //// �����������
//    //vector<int> result = inorderTraversal(root);
//
//    //// ����������
//    //cout << "����������: ";
//    //for (int val : result) {
//    //    cout << val << " ";
//    //}
//    //cout << endl;
//
//    int depth = minDepth(root);
//    cout << "��������С���: " << depth << endl;
//
//
//    // �ͷ��ڴ�
//    freeTree(root);
//
//    return 0;
//}


/// <summary>
/// ��ת������
/// </summary>
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;

    // ����������
    TreeNode* temp = root->left;

    // ��ת������Ϊ������
    root->left = invertTree(root->right);

    // ��ת������Ϊ���ݵ�������
    root->right = invertTree(temp);

    return root;
}




/// <summary>
/// ����������С�ڵ�
/// </summary>
int findMinimumValue(TreeNode* root) {
    if (!root) return INT_MAX;

  
    int min1 = min(findMinimumValue(root->left), findMinimumValue(root->right));

    return min(min1,root->val);


}

/// <summary>
/// �������е����ڶ�С�Ľڵ�
/// </summary>
/// 
//int answer = -1;
//void dfs(TreeNode* root, int cur) {
//    if (!root) return;
//    if (root->val != cur) {
//        if (answer == -1) answer = root->val;
//        else answer = min(answer, root->val);
//        return;
//    }
//    else
//    {
//        dfs(root->left, cur);
//        dfs(root->right, cur);
//    }
//}
//
//int findSecondMinimumValue(TreeNode* root) {
//
//    dfs(root, root->val);
//    return answer;
//
//}





void printTree(TreeNode* root, int depth = 0, char prefix = ' ') {
    if (!root) {
        return;
    }

    // ��ӡ������
    printTree(root->right, depth + 1, '/');

    // ��ӡ��ǰ�ڵ�
    std::cout << std::string(depth * 4, ' ') << prefix << "[" << root->val << "]" << std::endl;

    // ��ӡ������
    printTree(root->left, depth + 1, '\\');
}



/// <summary>
/// �ж϶������Ƿ�Գ�
/// </summary>
/// 
bool check(TreeNode* l, TreeNode* r) {
    if (!l && !r) return true;
    if (!l || !r)  return false;
    return l->val == r->val && check(l->left, r->right)&& check(l->right,r->left);
}
//bool isSymmetric(TreeNode* root) {
//    check(root->left, root->right);
//}





/// <summary>
/// ������������
/// </summary>
TreeNode* constructMaximumBinaryTree(vector<int>& nums,int left,int right) {
    if (left > right) {
        return nullptr;
    }
    int maxIndex = left;
    for (int i = left+1; i <= right; i++)
    {  
        if (nums[i] > nums[maxIndex]) {
            maxIndex = i;
        }

    }

    TreeNode* root = new TreeNode(nums[maxIndex]);

    root->left = constructMaximumBinaryTree(nums,left, maxIndex - 1);
    root->right = constructMaximumBinaryTree(nums, maxIndex + 1,right);

    return root;

}

TreeNode* constructMaximumBinaryTree(std::vector<int>& nums) {
    return constructMaximumBinaryTree(nums, 0, nums.size() - 1);
}



//int main() {
//    vector<int>  nums = {3, 2, 1, 6, 0, 5};
//    TreeNode* root = constructMaximumBinaryTree(nums);
//    printTree(root);
//    // �ͷ��ڴ�
//    freeTree(root);
//
//    return 0;
//}



/// <summary>
/// ������������� -----BFS
/// </summary>
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>>ans;
    queue<TreeNode*>q;
    if (root)
        q.push(root);
    while (!q.empty())
    {
        vector<int>vals;
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++)  //���ﲻ��ֱ�� i<q.size(),��Ϊforѭ���еĲ�����ı�size�Ĵ�С
        {
            TreeNode* cur = q.front();
            q.pop();
            vals.push_back(cur->val);
            if (cur->left)
                q.push(cur->left);
            if (cur->right)
                q.push(cur->right);
        }
        ans.push_back(vals);
    }
    return ans;
}


/// <summary>
/// ����������β������
/// </summary>
/// ������ĺܽӽ���������Ҫ��ż������з���ķ�ת����ʱ��˫�˶��о͸��ʺ���
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>>ans;
    deque<TreeNode*>dq;
    if (root)
       dq.push_front(root);
    bool leftToRight = true; // ���Ʊ�������
    while (!dq.empty())
    {
        vector<int>vals;
        int levelSize = dq.size();
        for (int i = 0; i < levelSize; i++)  //���ﲻ��ֱ�� i<q.size(),��Ϊforѭ���еĲ�����ı�size�Ĵ�С
        {
            if (leftToRight)
            {
            TreeNode* cur = dq.front();
            dq.pop_front();

            vals.push_back(cur->val);
            if (cur->left)
                dq.push_back(cur->left);
            if (cur->right)
                dq.push_back(cur->right);
            }
            else
            {  
                TreeNode* cur = dq.back();
                dq.pop_back();
                vals.push_back(cur->val);
                if (cur->right)
                    dq.push_front(cur->right);
                if (cur->left)
                    dq.push_front(cur->left);

            }

        }
        leftToRight = !leftToRight;
        ans.push_back(vals);
    }
    return ans;
}


/// <summary>
/// ��������ֱ��
/// </summary>
/// 
/// 
//int dfs(TreeNode* node, int& diameter) {
//    if (!node) return 0;
//    int L = dfs(node->left, diameter);
//    int R = dfs(node->right, diameter);
//
//    diameter =max(diameter, L + R);
//    return max(L , R) + 1;
//}
//
//int diameterOfBinaryTree(TreeNode* root) {
//    if (root == nullptr)
//        return 0;
//
//    int diameter = 0;
//    dfs(root, diameter);
//    return diameter;
//}


//int main() {
//    // ����һ�ö�������ʾ��
//    TreeNode* root = new TreeNode(1);
//    root->left = new TreeNode(2);
//    root->right = new TreeNode(3);
//    root->left->left = new TreeNode(4);
//    root->left->right = new TreeNode(5);
//
//
//    int result =diameterOfBinaryTree(root);
//
//    cout << "��������ֱ����: " << result << endl;
//
//    return 0;
//}

/// <summary>
/// ��ͬ����
/// </summary>
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr) {
        return true;
    }
    else if (p == nullptr || q == nullptr) {
        return false;
    }
    else if (p->val != q->val) {
        return false;
    }
    else {
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }

}


bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!root) return false;
    if (isSameTree(root, subRoot))
        return true;
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};
/// <summary>
/// �������е�����
/// </summary>
//bool dfs(TreeNode* rt, ListNode* head) {
//    // �����Ѿ�ȫ��ƥ���꣬ƥ��ɹ�
//    if (head == NULL) return true;
//    // ���������ʵ��˿սڵ㣬ƥ��ʧ��
//    if (rt == NULL) return false;
//    // ��ǰƥ��Ķ������Ͻڵ��ֵ������ڵ��ֵ����ȣ�ƥ��ʧ��
//    if (rt->val != head->val) return false;
//    return dfs(rt->left, head->next) || dfs(rt->right, head->next);
//}
//
//bool isSubPath(ListNode* head, TreeNode* root) {
//     if (root == NULL) return false;
//     return dfs(root, head) || isSubPath(head, root->left) || isSubPath(head, root->right);
//}


/// <summary>
/// �������½ǵ�ֵ
/// </summary>
/// ����һ��BFS����
/// 
int findBottomLeftValue1(TreeNode* root) {
    queue<TreeNode*>q;
    q.push(root);
    int result = 0;
    while (!q.empty())
    {
        vector<int>layer;
        int layersize = q.size();
        for (int i = 0; i < layersize; i++)
        {
             TreeNode* cur = q.front();
             q.pop();
             layer.push_back(cur->val);
             if (cur->left)
                q.push(cur->left);
             if (cur->right)
                q.push(cur->right);
        }
        result = layer[0];
       
    }
    return result;
}

/// <summary>
/// ����һ��DFS���
/// </summary>
/// ��ͬ��ȣ�����ߣ���ͬ��ȣ�����������
/// 

//void dfs(TreeNode* root, int height, int& curval, int& curheight) {
//    if (root == nullptr) return;
//    height++;
//    dfs(root->left, height, curval, curheight);
//    dfs(root->right, height, curval, curheight);
//    if (height > curheight) {
//        curheight = height;
//        curval = root->val;
//    }
//}
//int findBottomLeftValue(TreeNode* root) {
//    int curval = 0;
//    int curheight = 0;
//    dfs(root, 0, curval, curheight);
//    return curval;
//}



/// <summary>
/// ��ÿ�������������ֵ
/// </summary>
vector<int> largestValues(TreeNode* root) {
    if (!root)  return {};
    queue<TreeNode*>q;
    q.push(root);
    int result = 0;
    vector<int>layer;
    while (!q.empty())
    {
        
        int layersize = q.size();
        int a = 0;
        for (int i = 0; i < layersize; i++)
        {
            TreeNode* cur = q.front();
            q.pop();
            a = max(a, cur->val);
            if (cur->left)
                q.push(cur->left);
            if (cur->right)
                q.push(cur->right);
        }
        layer.push_back(a);

    }
    return layer;
}


/// <summary>
/// ��ȫ�������ڵ����
/// </summary>
int countNodes1(TreeNode* root) {
    if (!root) return 0;
    TreeNode* l = root->left;
    TreeNode* r = root->right;
    int leftdepth = 0, rightdepth = 0;
    while (l)
    {
        l = l->left;
        leftdepth++;
    }
    while (r)
    {
        r = r->right;
        rightdepth++;
    }
    if (leftdepth == rightdepth)  return (2 << leftdepth) - 1;
    return  countNodes(root->left) + countNodes(root->right) + 1;
}



/// <summary>
/// ƽ�������
/// </summary>
/// 
int treeHeight(TreeNode* root) {
    if (!root) return 0;
    int leftHeight = treeHeight(root->left);
    if (leftHeight == -1) return -1;
    int rightHeight = treeHeight(root->right);
    if (rightHeight == -1) return -1;
    return abs(leftHeight - rightHeight) > 1 ? -1 : 1 + max(leftHeight, rightHeight);
}

bool isBalanced(TreeNode* root) {
    return treeHeight(root) == -1 ? false : true;
}


/// <summary>
/// ������������·��
/// </summary>
/// 
/// 
//void dfs(TreeNode* root, vector<string>& paths, string cur_path) {
//
//    if (root == nullptr) return;
//
//    cur_path += to_string(root->val);
//    
//    if (root->left == nullptr && root->right == nullptr) {
//        paths.push_back(cur_path);
//        return;
//    }
//    cur_path += "->";
//    dfs(root->left, paths, cur_path);
//    dfs(root->right, paths, cur_path);
//}


//vector<string> binaryTreePaths(TreeNode* root) {
//    vector<std::string> paths;
//    string cur_path = "";
//    dfs(root, paths, cur_path);
//    return paths;
//}


/// <summary>
/// ������������ͼ
/// </summary>
/// bfsд��
//vector<int> rightSideView(TreeNode* root) {
//    vector<int>ans;
//    if (root == nullptr)  return ans;
//    queue<TreeNode*>q;
//    q.push(root);
//    while (!q.empty())
//    {
//        int size = q.size();
//        for (int i = 0; i < size; i++)
//        {
//            TreeNode* cur = q.front();
//            q.pop();
//            if (cur->left)q.push(cur->left);
//            if (cur->right)q.push(cur->right);
//            if (i == size - 1) ans.push_back(cur->val);
//        }
//
//    }
//    return ans;
//}

//void dfs(TreeNode* root, int depth,vector<int>&ans) {
//    if (root == nullptr)  return;
//    if (depth == ans.size()) ans.push_back(root->val);
//    depth++;
//    dfs(root->right, depth, ans);
//    dfs(root->left, depth, ans);
//}
//
//vector<int> rightSideView(TreeNode* root) {
//    vector<int>ans;
//    dfs(root, 0, ans);
//    return ans;
//
//}



//int main() {
//    TreeNode* root = new TreeNode(1);
//    root->left = new TreeNode(2);
//    root->right = new TreeNode(3);
//    root->left->right = new TreeNode(4);
//    vector<int>ans = rightSideView(root);
//
//    for (auto a : ans) cout << a << " ";
//    return 0;
//}



/// <summary>
/// ������������·��
/// </summary>
/// 
/// 
//void dfs(TreeNode* root, vector<string>& paths, string cur_path) {
//
//    if (root == nullptr) return;
//
//    cur_path += to_string(root->val);
//    
//    if (root->left == nullptr && root->right == nullptr) {
//        paths.push_back(cur_path);
//        return;
//    }
//    cur_path += "->";
//    dfs(root->left, paths, cur_path);
//    dfs(root->right, paths, cur_path);
//}


//vector<string> binaryTreePaths(TreeNode* root) {
//    vector<std::string> paths;
//    string cur_path = "";
//    dfs(root, paths, cur_path);
//    return paths;
//}


/// <summary>
/// ·��֮��
/// </summary>
bool hasPathSum(TreeNode* root, int targetSum) {

    if (!root) return false;

    if (!root->left && !root->right && targetSum == root->val) return true;

    return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
}


/// <summary>
/// ·��֮��2
/// </summary>
/// 
//void dfs(TreeNode* root, vector<vector<int>>&paths, vector<int>cur_path, int targetSum) {
//    if (!root) return;
//
//    cur_path.push_back(root->val);
//
//    if (!root->left && !root->right) {
//        if (targetSum == root->val)  paths.push_back(cur_path);
//    }
//
//    dfs(root->left, paths, cur_path, targetSum - root->val);
//    dfs(root->right, paths, cur_path, targetSum - root->val);
//    cur_path.pop_back();
//}
//
//
//vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
//    vector<vector<int>>ans;
//    vector<int>cur_path;
//    dfs(root, ans, cur_path, targetSum);
//    return ans;
//}


//int main() {
//    TreeNode* root = new TreeNode(1);
//    root->left = new TreeNode(2);
//    root->right = new TreeNode(3);
//    root->left->left = new TreeNode(1);
//    root->left->right = new TreeNode(5);
//
//    int targetSum = 4;
//    vector<vector<int>>ans = pathSum(root, targetSum);
//
//    for (auto an : ans) {
//        for (auto a : an) cout << a << " ";
//
//        cout << endl;
//    }
//
//    return 0;
//}
#include<unordered_map>
/// <summary>
/// ·��֮��3
/// </summary>
int totalPaths = 0; // ȫ�ֱ��������ڴ洢·������

void dfs(TreeNode* node, int currentSum, int targetSum, unordered_map<int, int>& prefixSumCount) {
    if (!node) return;

    // ���µ�ǰ·����
    currentSum += node->val;

    // ����ҵ�һ��·���͵���targetSum�������·������
    if (prefixSumCount.find(currentSum - targetSum) != prefixSumCount.end()) {
        totalPaths += prefixSumCount[currentSum - targetSum];
    }

    // ���¹�ϣ��
    prefixSumCount[currentSum]++;

    // ����̽����������
    dfs(node->left, currentSum, targetSum, prefixSumCount);
    dfs(node->right, currentSum, targetSum, prefixSumCount);

    // ���ݣ�������ǰ�ڵ��·����
    prefixSumCount[currentSum]--;
}



int pathSum3(TreeNode* root, int targetSum) {
    unordered_map<int, int> prefixSumCount;
    prefixSumCount[0] = 1;
    dfs(root, 0, targetSum, prefixSumCount);
    return totalPaths;
}


//int main() {
//    TreeNode* root = new TreeNode(1);
//    root->left = new TreeNode(2);
//    root->right = new TreeNode(3);
//    root->left->left = new TreeNode(1);
//    root->right->right = new TreeNode(4);
//
//    int targetSum = 3;
//    int ans = pathSum3(root, targetSum);
//    cout << ans;
//    return 0;
//
//
//}







/// <summary>
/// �����������������й��������
/// </summary>
//TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
//
//    if (inorder.size() == 0) return nullptr;
//    TreeNode* root = new TreeNode(postorder[postorder.size() - 1]);
//    int num = 0;
//
//    for (auto in : inorder) if (in == root->val) break; else num++;
//
//    postorder.pop_back();
//    //cout << num<<endl;
//    vector<int> inorder1(inorder.begin(), inorder.begin() + num);
//
//    vector<int> inorder2(inorder.begin() + num+1, inorder.end());
//    /*for (auto in : inorder1) { cout << in << " "; } cout << endl;
//    for (auto in : inorder2) { cout << in << " "; }*/
//    vector<int> postorder1(postorder.begin(), postorder.begin() + num);
//    vector<int> postorder2(postorder.begin()+num, postorder.end());
//    /*for (auto in : postorder1) { cout << in << " "; }cout << endl;
//    for (auto in : postorder2) { cout << in << " "; }*/
//    root->left = buildTree(inorder1, postorder1);
//    root->right = buildTree(inorder2, postorder2);
//
//    return root;
//}



//��ǰ��������������й��������
//TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//    if (preorder.size() == 0) return nullptr;
//    int num = 0;
//    TreeNode* root = new TreeNode(preorder[0]);
//    for (auto in : inorder) if (in == root->val) break; else num++;
//    vector<int> preorder1(preorder.begin()+1, preorder.begin() + num+1);
//    vector<int> preorder2(preorder.begin() + num+1, preorder.end());
//
//    for (auto in : preorder1) { cout << in << " "; } cout << endl;
//    for (auto in : preorder2) { cout << in << " "; }
//
//    vector<int> inorder1(inorder.begin(), inorder.begin() + num);
//    vector<int> inorder2(inorder.begin() + num + 1, inorder.end());
//
//
//
//    root->left = buildTree(preorder1, inorder1);
//    root->right = buildTree(preorder2, inorder2);
//    return root;
//}


//int main() {
//    vector<int>inorder = {2,1,3};
//    vector<int>preorder = { 1,2,3 };
//    TreeNode* root = buildTree(preorder, inorder);
//    return 0;
//}

int maxSum = INT_MIN;
int dfs(TreeNode* root) {
    if (!root) return 0;

    int left_gain = max(dfs(root->left),0);
    int right_gain = max(dfs(root->right), 0);
    int path = root->val + left_gain + right_gain;
    maxSum = max(path, maxSum);
    return root->val+max(left_gain,right_gain) ;
}



/// <summary>
/// �������е����·����
/// </summary>
int maxPathSum(TreeNode* root) {
    dfs(root);
    return maxSum;
}


//int main() {
//    TreeNode* root = new TreeNode(1);
//    root->left = new TreeNode(2);
//    root->right = new TreeNode(3);
//    root->left->left = new TreeNode(4);
//    root->right->right = new TreeNode(5);
//
//    int ans = maxPathSum(root);
//    cout << ans;
//    return 0;
//
//
//}


/// <summary>
/// ����������BST
/// </summary>



/// <summary>
/// ����������������
/// </summary>
TreeNode* searchBST(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    TreeNode* result = nullptr;
    if (root->val > val) result = searchBST(root->left, val);
    else if (root->val < val) result = searchBST(root->right, val);
    return result;
}


/// <summary>
/// ��֤����������
/// </summary>

void dfs(TreeNode* root,vector<int>& ans)
{
    if (!root) return;
    dfs(root->left, ans);
    ans.push_back(root->val);
    dfs(root->right, ans);
}


bool isValidBST(TreeNode* root) {
    vector<int>ans;
    dfs(root, ans);
    for (int i = 0; i < ans.size() - 1; i++)
    {
        if (ans[i] > ans[i + 1]) return false;
    }
    return 1;
}

//int main() {
//    TreeNode* root = new TreeNode(3);
//    root->left = new TreeNode(2);
//    root->right = new TreeNode(5);
//    root->left->left = new TreeNode(1);
//    root->right->right = new TreeNode(6);
//    cout << isValidBST(root) << endl;
//    return 0;
//
//
//}


//����������ת��Ϊ����������
//TreeNode* buildTree(vector<int>& nums, int left.int right) {
//    if (left > right) return nullptr;
//    int mid = left + (right - left) / 2;
//    TreeNode* root = new TreeNode(nums[mid]);
//    root->left = sortedArrayToBST(nums,left,mid-1);
//    root->right = sortedArrayToBST(nums,mid+1,right);
//
//    return root;
//}
//
//
//TreeNode* sortedArrayToBST(vector<int>& nums) {
//
//    return buildTree(nums,0,nums.size()-1)
//
//}

/// <summary>
/// �����������е�KС��Ԫ��
/// </summary>
/// �����������˳��ģ����ˣ�
int kthSmallest(TreeNode* root, int k) {
    vector<int>ans;
    dfs(root, ans);
    
    return ans[k-1];
}





/// <summary>
/// ������չ��Ϊ����
/// </summary>
void flatten(TreeNode* root) {
    if (!root)return;

    flatten(root->left);
    flatten(root->right);

    TreeNode* temp = root->right;
    root->right = root->left;
    root->left = NULL;


    TreeNode* cur = root;
    while (cur->right != NULL) cur = cur->right;
    cur->right = temp;

}


/// <summary>
/// �������������������
/// </summary>
/// node�����p.q�����ڵ�ֱ���node�������������ҵ��Ļ�����ô���ǵ�������Ⱦ���node.�����������ͬ��������ô�������������ֱ�������ڲ�ͬ����
/// ���q�������ڵ㣬����q����������ܷ��ҵ�p,�ҵ��Ļ�������q��
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

    if (q == root || p == root || root == nullptr)  return root;
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left == nullptr) return right;
    if (right == nullptr)  return left;
    return root;
}

/// <summary>
/// �����������������������
/// </summary>
/// �ж�p,q�ֱ���ڸ��ڵ�Ĵ�С���ɣ�������߶����ڻ���С�ڸ��ڵ㣬��ô���������������ʱ�ĸ��ڵ��������������ȡ�
TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
        
    if (root->val > p->val && root->val > q->val)
        return  lowestCommonAncestor(root->left, p, q);
    if (root->val < p->val && root->val < q->val)
        return lowestCommonAncestor(root->right, p, q);
    return root;
}