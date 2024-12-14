/* ===================================================================
        Binary Search Trees - BST - Author: Alaa Eddine FARJALLAH
   ===================================================================  */

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
Node* InsertTreeNode(Node* root, int value);
void PreOrderTraversal(Node* root);
void InOrderTraversal(Node* root);
void PostOrderTraversal(Node* root);
void BreadFirstSearch(Node* root);
void DepthFirstSearch(Node* root);
void DestroyTree(Node* root);
bool FindNodeRecursively(Node* root, int value);
bool FindNodeIteratively(Node* root, int value);
bool NodeisLeaf(Node* node);
bool AreIdentical(Node* root1, Node* root2);
int TreeHeight(Node* root);
int CountNodes(Node* root);
int CountLeaves(Node* root);
int TreeMax(Node* root);
int TreeMin(Node* root);
int TreeSum(Node* root);
Node* RemoveTreeNode(Node* root, int value);

int main() 
{
//  CHECK THE ASSOCIATED PICTURE TO BETTER UNDERSTAND THE TEST FUNCTIONS!
    Node* root = CreateTreeNode(50);
    root = InsertTreeNode(root, 38);
    root = InsertTreeNode(root, 55);
    root->left = InsertTreeNode(root->left, 33);
    root->left->left->right = InsertTreeNode(root->left->left->right, 34);
    root->right->left = InsertTreeNode(root->right->left, 53);
    root->right->left->left = InsertTreeNode(root->right->left->left, 51);
    root->right->right = InsertTreeNode(root->right->right, 68);
    root->right->right = InsertTreeNode(root->right->right, 69);

    std::cout << "Height of the tree: " << TreeHeight(root);
    std::cout << "\n\n";
    
    std::cout << "Pre-order Traversal:  ";
    PreOrderTraversal(root);
    std::cout << "\n";

    std::cout << "In-order Traversal:   ";
    InOrderTraversal(root);
    std::cout << "\n";

    std::cout << "Post-order Traversal: ";
    PostOrderTraversal(root);
    std::cout << "\n\n";

    BreadFirstSearch(root);
    DepthFirstSearch(root);
    std::cout << "\n";

    std::cout << "Sum of all the numbers in the tree: " << TreeSum(root);
    std::cout << "\n";

    std::cout << "Nodes in the tree: " << CountNodes(root);
    std::cout << "\n";

    std::cout << "Leaves in the tree: " << CountLeaves(root);
    std::cout << "\n\n";

    int valueToFind = 47;
    std::cout << "Finding value " << valueToFind << " recursively: ";
    std::cout << (FindNodeRecursively(root, valueToFind) ? "Found" : "Not Found") << "\n";
    std::cout << "Finding value " << valueToFind << " iteratively: ";
    std::cout << (FindNodeIteratively(root, valueToFind) ? "Found" : "Not Found") << "\n\n";

    valueToFind = 53;
    std::cout << "Finding value " << valueToFind << " recursively: ";
    std::cout << (FindNodeRecursively(root, valueToFind) ? "Found" : "Not Found") << "\n";
    std::cout << "Finding value " << valueToFind << " iteratively: ";
    std::cout << (FindNodeIteratively(root, valueToFind) ? "Found" : "Not Found") << "\n\n";

    std::cout << "Biggest number in the tree: " << TreeMax(root);
    std::cout << "\n";

    int valueToRemove = TreeMax(root);
    root = RemoveTreeNode(root, valueToRemove);
    std::cout << "Tree after removing " << valueToRemove << ":\n";
    BreadFirstSearch(root);
    std::cout << "\n";

    std::cout << "Biggest number in the tree now: " << TreeMax(root);
    std::cout << "\n";

    std::cout << "Lowest number in the tree: " << TreeMin(root);
    std::cout << "\n\n";

    std::cout << "Sum of all the numbers in the tree now: " << TreeSum(root);
    std::cout << "\n\n";

//  NEVER FORGET THIS STEP!
    DestroyTree(root);

    return 0;
}

Node* CreateTreeNode(int value) {
    Node* NewNode = new Node;
    NewNode->data = value;
    NewNode->left = NewNode->right = nullptr;
    return NewNode;
}

Node* InsertTreeNode(Node* root, int value) {
    if (root == nullptr) return CreateTreeNode(value);

    if (root->data < value) root->right = InsertTreeNode(root->right, value);
    else if (root->data > value) root->left = InsertTreeNode(root->left, value);

    return root;
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

bool FindNodeRecursively(Node* root, int value) {
    if (root == nullptr) return false;
    if (root->data == value) return true;
    if (root->data < value) return FindNodeRecursively(root->right, value); 
    return FindNodeRecursively(root->left, value);  
}

bool FindNodeIteratively(Node* root, int value) {
    while (root != nullptr && value != root->data) {
        if (root->data < value) root = root->right;
        else root = root->left;
    }
    return (root != nullptr);
}

bool NodeisLeaf(Node* node) {
    return (node != nullptr && node->left == nullptr && node->right == nullptr);
}

bool AreIdentical(Node* root1, Node* root2) {
    if (root1 == nullptr && root2 == nullptr) return true;
    if (root1 == nullptr || root2 == nullptr) return false;

    bool cond1 = root1->data == root2->data;
    bool cond2 = AreIdentical(root1->left, root2->left);
    bool cond3 = AreIdentical(root1->right, root2->right);

    return cond1 && cond2 && cond3;
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
    else return std::max(root->data ,TreeMax(root->right));
}

int TreeMin(Node* root) {
    if (root == nullptr) return std::numeric_limits<int>::max();
    else return std::min(root->data ,TreeMin(root->left));
}

int TreeSum(Node* root) {
    if (root == nullptr) return 0;
    int leftSum = TreeSum(root->left);
    int rightSum = TreeSum(root->right);
    return root->data + leftSum + rightSum;
}

Node* RemoveTreeNode(Node* root, int value) {
    if (root == nullptr) return root;

    if (root->data > value) root->left = RemoveTreeNode(root->left, value);
    else if (root->data < value) root->right = RemoveTreeNode(root->right, value);
    else {
        if (NodeisLeaf(root)) {
            DestroyTree(root);
            return nullptr;
        } else if (root->left == nullptr && root->right != nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->left != nullptr && root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
        //  If node has both left and right childred:
            Node* temp = root->right;   //One step to the right than left all the way down.
            while (temp->left != nullptr) temp = temp->left;
    
        //  We can however go one step to the left and than right all the way down, works too.
        //  Node* temp = root->left;
        //  while (temp->right != nullptr) temp = temp->right;
            
            root->data = temp->data;
            root->right = RemoveTreeNode(root->right, temp->data);
        //  root->left = RemoveTreeNode(root->left, temp->data);
        }
    }
    return root;
} 