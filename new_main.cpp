#include <iostream>
#include <queue>
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
        cout << "Duplicate value. Node not inserted.\n";
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
    if (root == nullptr)
        return nullptr;
    while (root->left != nullptr)
        root = root->left;
    return root;
}

Node *findMax(Node *root)
{
    if (root == nullptr)
        return nullptr;
    while (root->right != nullptr)
        root = root->right;
    return root;
}

Node *deleteNode(Node *root, int key)
{
    if (root == nullptr)
    {
        cout << "Node not found!\n";
        return root;
    }

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
        // Node with two children
        else
        {
            Node *temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    return root;
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
        postorder(root->left);
        postorder(root->right);
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

int countNodes(Node *root)
{
    if (root == nullptr)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int findHeight(Node *root)
{
    if (root == nullptr)
        return -1; // Height of empty tree is -1
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return 1 + max(leftHeight, rightHeight);
}

void levelOrderTraversal(Node *root)
{
    if (root == nullptr)
    {
        cout << "Tree is empty!\n";
        return;
    }

    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++)
        {
            Node *current = q.front();
            q.pop();
            cout << current->key << " ";

            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
        }
        cout << endl;
    }
}

void displayMenu()
{
    cout << "\n========== BST OPERATIONS MENU ==========\n";
    cout << "1. Insert Node\n";
    cout << "2. Display BST (Traversals)\n";
    cout << "3. Search Node\n";
    cout << "4. Delete Node\n";
    cout << "5. Find Minimum\n";
    cout << "6. Find Maximum\n";
    cout << "7. Count Total Nodes\n";
    cout << "8. Find Height of BST\n";
    cout << "9. Level Order Traversal (BFS)\n";
    cout << "0. Exit\n";
    cout << "=========================================\n";
    cout << "Enter your choice: ";
}

void displayTraversalMenu()
{
    cout << "\n--- Choose Traversal Type ---\n";
    cout << "1. Inorder (Sorted Order)\n";
    cout << "2. Preorder (Root First)\n";
    cout << "3. Postorder (Root Last)\n";
    cout << "Enter choice: ";
}

int main()
{
    Node *root = nullptr;
    int choice, value, traversalChoice;

    while (true)
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1: // Insert Node
            cout << "Enter value to insert: ";
            cin >> value;
            root = insert(root, value);
            cout << "Node inserted successfully!\n";
            break;

        case 2: // Display BST
            if (root == nullptr)
            {
                cout << "Tree is empty!\n";
                break;
            }
            displayTraversalMenu();
            cin >> traversalChoice;
            switch (traversalChoice)
            {
            case 1:
                cout << "Inorder: ";
                inorder(root);
                cout << endl;
                break;
            case 2:
                cout << "Preorder: ";
                preorder(root);
                cout << endl;
                break;
            case 3:
                cout << "Postorder: ";
                postorder(root);
                cout << endl;
                break;
            default:
                cout << "Invalid traversal choice!\n";
            }
            break;

        case 3: // Search Node
            cout << "Enter value to search: ";
            cin >> value;
            if (search(root, value))
                cout << value << " found in BST!\n";
            else
                cout << value << " not found in BST!\n";
            break;

        case 4: // Delete Node
            cout << "Enter value to delete: ";
            cin >> value;
            root = deleteNode(root, value);
            if (root != nullptr || value == root->key)
                cout << "Node deleted successfully!\n";
            break;

        case 5: // Find Minimum
        {
            Node *minNode = findMin(root);
            if (minNode != nullptr)
                cout << "Minimum value: " << minNode->key << endl;
            else
                cout << "Tree is empty!\n";
            break;
        }

        case 6: // Find Maximum
        {
            Node *maxNode = findMax(root);
            if (maxNode != nullptr)
                cout << "Maximum value: " << maxNode->key << endl;
            else
                cout << "Tree is empty!\n";
            break;
        }

        case 7: // Count Total Nodes
            cout << "Total nodes in BST: " << countNodes(root) << endl;
            break;

        case 8: // Find Height
            cout << "Height of BST: " << findHeight(root) << endl;
            break;

        case 9: // Level Order Traversal
            cout << "Level Order Traversal (BFS):\n";
            levelOrderTraversal(root);
            break;

        case 0: // Exit
            cout << "Exiting program. Goodbye!\n";
            return 0;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}