#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

class TreeNode{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right): val(x), left(left), right(right){}
};

TreeNode* initTree(int nodelist[], int size){
    if(size<1) return nullptr;

    TreeNode **nodes = new TreeNode*[size];
    for(int i=0;i<size;i++){
        if(nodelist[i]==0){
            nodes[i] = nullptr;
        }
        else{
            nodes[i] = new TreeNode(nodelist[i]);
        }
    }

    queue<TreeNode*> nodeQueue;
    nodeQueue.push(nodes[0]);
    TreeNode *node;
    int index = 1;
    while(index < size){
        node = nodeQueue.front();
        nodeQueue.pop();
        if(nodes[index]){
            nodeQueue.push(nodes[index++]); 
            node->left = nodeQueue.back();
        }
        else index++;
        
        if(nodes[index]){
            nodeQueue.push(nodes[index++]); 
            node->right = nodeQueue.back();
        }
        else index++;
    }
    return nodes[0];
}


void preOrderRecursive(TreeNode* root, vector<int>& result){
    if(!root) return;
    result.push_back(root->val);
    preOrderRecursive(root->left, result);
    preOrderRecursive(root->right, result);
}

void preOrder(TreeNode* root, vector<int>& result){
    if(!root) return;
    stack<TreeNode*> nodeStack;
    nodeStack.push(root);
    while(!nodeStack.empty()){
        TreeNode *node = nodeStack.top();
        nodeStack.pop();
        result.push_back(node->val);
        if(node->right) nodeStack.push(node->right);
        if(node->left) nodeStack.push(node->left);
    }
}

void inOrderRecursive(TreeNode* root, vector<int>& result){
    if(!root) return;
    inOrderRecursive(root->left, result);
    result.push_back(root->val);
    inOrderRecursive(root->right, result);
}

void inOrder(TreeNode* root, vector<int>& result){
    stack<TreeNode*> nodeStack;
    while(root || !nodeStack.empty()){
        while(root){ // 用if(root)也可以
            nodeStack.push(root);
            root = root->left;
        }

        if(!nodeStack.empty()){
            root = nodeStack.top();
            nodeStack.pop();
            result.push_back(root->val);
            root = root->right;
        }
    }
}

void postOrderRecursive(TreeNode* root, vector<int>& result){
    if(!root) return;
    postOrderRecursive(root->left, result);
    postOrderRecursive(root->right, result);
    result.push_back(root->val);
}

void postOrder1(TreeNode* root, vector<int>& result){
    if(!root) return;
    stack<TreeNode*> nodeStack1;
    stack<TreeNode*> nodeStack2;
    nodeStack1.push(root);
    while(!nodeStack1.empty()){
        TreeNode *node = nodeStack1.top();
        nodeStack1.pop();
        nodeStack2.push(node);
        if(node->left) nodeStack1.push(node->left);
        if(node->right) nodeStack1.push(node->right);

    }
    while(!nodeStack2.empty()){
        result.push_back(nodeStack2.top()->val);
        nodeStack2.pop();
    }
}

void postOrder2(TreeNode* root, vector<int>& result){
    /** postorder Another way **/
    if(!root) return;
    stack<TreeNode*> nodeStack;
    TreeNode *pre = nullptr; // 记录上次访问的节点
    while(!nodeStack.empty() || root != nullptr){
        while(root != nullptr){
            nodeStack.push(root);
            root = root->left;
        }
        root = nodeStack.top();
        // 当前节点为子节点或上一访问的节点是当前节点的右节点，
        // 即从根节点回溯到右节点
        if(root->right == nullptr || pre == root->right){
            nodeStack.pop();
            result.push_back(root->val);
            pre = root;
            root = nullptr; // 让root到下一循环再更新，防止发生空栈错误
        }else{ // 否则，当前的根节点是从左节点回溯来的，应该先访问右节点
            root = root->right;
        }
    }
}

void levelOrder(TreeNode* root, vector<int>& result){ //BFS
    if(!root) return;
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);
    TreeNode *node;
    while(!nodeQueue.empty()){
        vector<int> levelList;
        int len = nodeQueue.size();  
        for(int i=1;i<=len;i++){ // for循环只是为了二维(res[][])保存层序结果（res[0]保存第一层，res[1]保存第二层），一维下不需要for循环
            node = nodeQueue.front();
            nodeQueue.pop();
            levelList.push_back(node->val);
            // cout << node->val << ' ';
            if(node->left) nodeQueue.push(node->left);
            if(node->right) nodeQueue.push(node->right);
        }
        result.insert(result.end(), levelList.begin(), levelList.end());
    }
}

void DFS(TreeNode* root, vector<int>& result){
    if(!root) return;
    stack<TreeNode*> nodeStack;
    nodeStack.push(root);
    while(!nodeStack.empty()){
        TreeNode *node = nodeStack.top();
        nodeStack.pop();
        result.push_back(node->val);
        if(node->right) nodeStack.push(node->right);
        if(node->left) nodeStack.push(node->left);
    }
}

void traversal(vector<int> list){
    int len = list.size();
    for(int i=0;i<len;i++){
        cout << list[i] << ' ';
    }
    cout << endl;
}

int main(){
    int treeList[] = {1, 2, 3, 4, 0, 5, 6, 7, 0, 8};
    int len = sizeof(treeList)/sizeof(treeList[0]);
    cout << len <<endl;
    TreeNode *root = initTree(treeList, len);

    vector<int> preResult;
    vector<int> inResult;
    vector<int> postResult;
    vector<int> levelResult; //bfsResult
    vector<int> dfsResult;

    cout << "The result of the preorder traversal is:" << endl;
    // preOrderRecursive(root, preResult);
    preOrder(root, preResult); 
    traversal(preResult);
    cout << "The result of the inorder traversal is:" << endl;
    // inOrderRecursive(root, inResult);
    inOrder(root, inResult);
    traversal(inResult);
    cout << "The result of the postorder traversal is:" << endl;
    // postOrderRecursive(root, postResult);
    postOrder2(root, postResult);
    traversal(postResult); 
    cout << "The result of the levelorder traversal is:" << endl;
    levelOrder(root, levelResult);
    traversal(levelResult);
    cout << "The result of the DFS traversal is:" << endl;
    DFS(root, dfsResult);
    traversal(dfsResult);

    return 0;
}
