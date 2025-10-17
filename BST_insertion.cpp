
#include <iostream>
using namespace std;
struct Node
{
    int key;
    Node *left;
    Node *right;
    Node(int item)
    {
        key = item;
        left = NULL;
        right = NULL;
    }
};
Node *insert(Node *node, int key)
{
    if (node == NULL)
    {
        return new Node(key);
    }
    if (node->key == key)
    {
        return node;
    }
    if (node->key < key)
    {
        node->right = insert(node->right, key);
    }
    else
    {
        node->left = insert(node->left, key);
    }
    return node;
}
Node *findMin(Node *root)
{
    while (root->left != nullptr)
        root = root->left;
    return root;
}

// Delete a node from BST
Node *deleteNode(Node *root, int key)
{
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        // Node with only one child or no child
        if (root->left == nullptr)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
    }
}
void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}
void preorder(Node *root)
{
    if (root != NULL)
    {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(Node *root)
{
    if (root != NULL)
    {
        postorder(root->right);
        postorder(root->left);
        cout << root->key << " ";
    }
}
bool search(Node *root, int key)
{
    if (root == nullptr)
        return false;
    if (key == root->key)
        return true;
    else if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}
int main()
{
    /* bst tree :
                 60
                /  \
               45   75
              /  \  /  \
            35  50  70  80
    */
    Node *root = new Node(60);
    root = insert(root, 45);
    root = insert(root, 35);
    root = insert(root, 50);
    root = insert(root, 75);
    root = insert(root, 70);
    root = insert(root, 80);

    cout << "inorder" << endl;
    inorder(root);
    cout << endl;
    cout << "preorder" << endl;
    preorder(root);
    cout << endl;
    cout << "post order" << endl;
    postorder(root);
    cout << "before deletion" << endl;
    inorder(root);
    cout << endl;
    root = deleteNode(root, 50);
    cout << "after deletion" << endl;
    inorder(root);
    inorder(root);
    int target = 60;
    if (search(root, target))
        cout << "Found " << target << " in BST.\n";
    else
        cout << target << " not found in BST.\n";
    cout << endl;
    return 0;
}
