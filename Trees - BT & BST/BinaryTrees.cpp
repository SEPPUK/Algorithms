/* ===========================================================
        Binary Trees - BT - Author: Alaa Eddine FARJALLAH
   ===========================================================  */

#include <iostream>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;

} Node;

Node* CreateTreeNode(int value);
void PreOrderTraversal(Node* root);
void InOrderTraversal(Node* root);
void PostOrderTraversal(Node* root);
void BreadFirstSearch(Node* root);
void DepthFirstSearch(Node* root);
void DestroyTree(Node* root);
bool NodeisLeaf(Node* node);
int TreeHeight(Node* root);
int CountNodes(Node* root);
int CountLeaves(Node* root);
int TreeMax(Node* root);
int TreeMin(Node* root);
int TreeSum(Node* root);
bool FindNodeRecursively(Node* root, int value);
bool AreIdentical(Node* root1, Node* root2);

int main() {
//  CHECK THE ASSOCIATED PICTURE TO BETTER UNDERSTAND THE TEST FUNCTIONS!
    Node* root1 = CreateTreeNode(2);
    root1->left = CreateTreeNode(7);
    root1->right = CreateTreeNode(5);
    root1->left->left = CreateTreeNode(2);
    root1->left->right = CreateTreeNode(6);
    root1->right->right = CreateTreeNode(9);
    root1->right->right->left = CreateTreeNode(4);
    root1->left->right->right = CreateTreeNode(11);
    root1->left->right->left = CreateTreeNode(5);
    
    Node* root2 = CreateTreeNode(2);
    root2->left = CreateTreeNode(7);
    root2->right = CreateTreeNode(5);
    root2->left->left = CreateTreeNode(4);
    root2->left->right = CreateTreeNode(5);

    Node* root3 = CreateTreeNode(2);
    root3->left = CreateTreeNode(7);
    root3->right = CreateTreeNode(5);
    root3->left->left = CreateTreeNode(2);
    root3->left->right = CreateTreeNode(6);
    root3->right->right = CreateTreeNode(9);
    root3->right->right->left = CreateTreeNode(4);
    root3->left->right->right = CreateTreeNode(11);
    root3->left->right->left = CreateTreeNode(5);

    std::cout << "Pre-order traversal:  ";
    PreOrderTraversal(root1);
    std::cout << std::endl;

    std::cout << "In-order traversal:   ";
    InOrderTraversal(root1);
    std::cout << std::endl;

    std::cout << "Post-order traversal: ";
    PostOrderTraversal(root1);
    std::cout << "\n\n";

    BreadFirstSearch(root1);
    DepthFirstSearch(root1);
    std::cout << std::endl;

    std::cout << "Tree height: " << TreeHeight(root1) << std::endl;
    std::cout << "Total number of nodes: " << CountNodes(root1) << std::endl;
    std::cout << "Number of leaf nodes: " << CountLeaves(root1) << std::endl;
    std::cout << "Maximum value in the tree: " << TreeMax(root1) << std::endl;
    std::cout << "Minimum value in the tree: " << TreeMin(root1) << std::endl;
    std::cout << "Sum of all nodes: " << TreeSum(root1) << "\n\n";

    int valueToFind = 8;
    std::cout << "Is value " << valueToFind << " present in the tree? ";
    std::cout << (FindNodeRecursively(root1, valueToFind) ? "YES" : "NO") << "\n\n";

    std::cout << "Tree1 and Tree2 are identical: ";
    std::cout << (AreIdentical(root1, root2) ? "YES" : "NO") << std::endl;

    std::cout << "Tree1 and Tree3 are identical: ";
    std::cout << (AreIdentical(root1, root3) ? "YES" : "NO") << std::endl;
    
//  NEVER FORGET THIS STEP!
    DestroyTree(root1);
    DestroyTree(root2);
    DestroyTree(root3);

    return 0;
}

Node* CreateTreeNode(int value) {
    return new Node{value, nullptr, nullptr};
}

void PreOrderTraversal(Node* root) {
    if (root != nullptr) {
        std::cout << root->data << " ";
        PreOrderTraversal(root->left);
        PreOrderTraversal(root->right);
    }
}

void InOrderTraversal(Node* root) {
    if (root != nullptr) {
        InOrderTraversal(root->left);
        std::cout << root->data << " ";
        InOrderTraversal(root->right);
    }
}

void PostOrderTraversal(Node* root) {
    if (root != nullptr) {
        PostOrderTraversal(root->left);
        PostOrderTraversal(root->right);
        std::cout << root->data << " ";
    }
}

void BreadFirstSearch(Node* root) {
    if (root == nullptr) return;

    std::queue<Node*> q;
    q.push(root);

    std::cout << "BFS: ";
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        std::cout << current->data << " ";
        if (current->right != nullptr) q.push(current->right);
        if (current->left != nullptr) q.push(current->left);
    }
    std::cout << std::endl;    
}

void DepthFirstSearch(Node* root) {
    if (root == nullptr) return;

    std::stack<Node*> s;
    s.push(root);

    std::cout << "DFS: ";
    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        std::cout << current->data << " ";
        if (current->right != nullptr) s.push(current->right); 
        if (current->left != nullptr) s.push(current->left);   
    }
    std::cout << std::endl;    
}

void DestroyTree(Node* root) {
    if (root != nullptr) {
        DestroyTree(root->right);
        DestroyTree(root->left);
        delete root;
    }
}

bool NodeisLeaf(Node* node) {
    return (node != nullptr && node->left == nullptr && node->right == nullptr);
}

int TreeHeight(Node* root) {
    if (root == nullptr) return 0;
    int leftHeight = TreeHeight(root->left);
    int rightHeight = TreeHeight(root->right);
    return 1 + std::max(leftHeight, rightHeight);
}

int CountNodes(Node* root) {
    if (root == nullptr) return 0;
    return 1 + CountNodes(root->left) + CountNodes(root->right);
}

int CountLeaves(Node* root) {
    if (root == nullptr) return 0;
    if (NodeisLeaf(root)) return 1;
    return CountLeaves(root->left) + CountLeaves(root->right);
}

int TreeMax(Node* root) {
    if (root == nullptr) return std::numeric_limits<int>::lowest();
    return std::max(root->data, std::max(TreeMax(root->left), TreeMax(root->right)));
}

int TreeMin(Node* root) {
    if (root == nullptr) return std::numeric_limits<int>::max();
    return std::min(root->data, std::min(TreeMin(root->left), TreeMin(root->right)));
}

int TreeSum(Node* root) {
    if (root == nullptr) return 0;
    int leftSum = TreeSum(root->left);
    int rightSum = TreeSum(root->right);
    return root->data + leftSum + rightSum;
}

bool FindNodeRecursively(Node* root, int value) {
    if (root == nullptr) return false;
    if (root->data == value) return true;
    return (FindNodeRecursively(root->left, value) || FindNodeRecursively(root->right, value));
}

bool AreIdentical(Node* root1, Node* root2) {
    if (root1 == nullptr && root2 == nullptr) return true;
    if (root1 == nullptr || root2 == nullptr) return false;

    bool cond1 = root1->data == root2->data;
    bool cond2 = AreIdentical(root1->left, root2->left);
    bool cond3 = AreIdentical(root1->right, root2->right);

    return cond1 && cond2 && cond3;
}