// Binary Search Tree - Implemenation in C++
// Author : Mayur Pawar (Pune, 2016)

#include <iostream>
#include <queue>
using namespace std;

struct node {
    int data;
    int count;
    node* left;
    node* right;
};

node* createNode(int data){
    node* newNode = new node();
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

node* insertNode(node* root, int data) {
    if (root==NULL) root = createNode(data);
    else if (data <= root->data) root->left = insertNode(root->left, data);
    else root->right = insertNode(root->right, data);
    return root;
}

bool searchNumber(node* root, int data){
    if (root == NULL) return false;
    if (root->data == data) return true;
    if (data <= root->data) return searchNumber(root->left, data);
    else return searchNumber(root->right, data);
}

int minElement(node* root){
    if (root->left == NULL) return root->data;
    else return minElement(root->left);
}

int maxElement(node* root){
    if (root->right == NULL) return root->data;
    else return maxElement(root->right);
}

int height(node* root){
    if (root == NULL) return -1;
    return max(height(root->left), height(root->right))+1;
}

void BFS(node* root){
    queue<node*> Q;
    if (root == NULL) return;
    Q.push(root);
    while (!Q.empty()) {
        node* current = Q.front();
        cout << current->data << ' ';
        if (current->left != NULL) Q.push(current->left);
        if (current->right != NULL) Q.push(current->right);
        Q.pop();
    }
}

void pre(node* root){
    if (root == NULL) return;
    cout << root->data << ' ';
    pre(root->left);
    pre(root->right);
}

void in(node* root){
    if (root == NULL) return;
    in(root->left);
    cout << root->data << ' ';
    in(root->right);
}

void post(node* root){
    if (root == NULL) return;
    post(root->left);
    post(root->right);
    cout << root->data << ' ';
}

bool isBST(node* root){
    if (root->left <= root && root->right > root) return true;
    return true;
}

void topView(node* root){
    static int count = 0;
    if (root->left && count >= 0) {
        count++;
        topView(root->left);
    }
    cout << root->data << ' ';
    count--;
    if (root->right && count < 0) {
        //count--;
        topView(root->right);
    }
}

BstNode* inOrderSuccesor(BstNode* root, int data){
    BstNode* current=findNode(root, data);
    if (current==NULL) return NULL;
    if (current->right!=NULL) {
        BstNode* temp=current->right;
        while (temp->left!=NULL) temp=temp->left;
        return temp;
    }
    else {
        BstNode* successor=NULL;
        BstNode* ansestor=root;
        while (ansestor!=current) {
            if (data<ansestor->data) {
                successor=ansestor;
                ansestor=ansestor->left;
            }
            else ansestor=ansestor->right;
        }
        return successor;
    }
}

int main() {
    node* root = NULL;
    root = insertNode(root, 15);
    root = insertNode(root, 234);
    root = insertNode(root, 9);
    root = insertNode(root, 34);
    root = insertNode(root, 24);
    root = insertNode(root, 4555);
    root = insertNode(root, 1);
    root = insertNode(root, 20);
    root = insertNode(root, 0);
    
    //cout << minElement(root);
    //cout << maxElement(root);
    //cout << height(root);
    //BFS(root);
    
    post(root);
    BstNode* temp = inOrderSuccesor(root, 3);
    cout << "Inorder Successor : ";
    if (temp==NULL) cout << "No successor" << endl;
    else cout << temp->data << endl;
    
    //topView(root);
}
