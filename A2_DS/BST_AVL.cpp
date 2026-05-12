#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

// ================= BOOK =================

// Structure To Store Book Information
struct Book {
    int id;
    string title;
    string author;

    Book(int i = 0, string t = "", string a = "") {
        id = i;
        title = t;
        author = a;
    }
};

// ================= BST =================

// BST Node
class BSTNode {
public:
    Book data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Book value) {
        data = value;
        left = right = NULL;
    }
};

class BST {
public:
    BSTNode* root;

    BST() {
        root = NULL;
    }

    // Insert New Book In BST
    BSTNode* insert(BSTNode* root, Book book) {

        if (root == NULL)
            return new BSTNode(book);

        if (book.id < root->data.id)
            root->left = insert(root->left, book);

        else if (book.id > root->data.id)
            root->right = insert(root->right, book);

        return root;
    }

    void insert(Book book) {
        root = insert(root, book);
    }

    // Search For Book In BST
    BSTNode* search(BSTNode* root, int id) {

        if (root == NULL)
            return NULL;

        if (id == root->data.id)
            return root;

        if (id < root->data.id)
            return search(root->left, id);

        return search(root->right, id);
    }

    void search(int id) {

        BSTNode* result = search(root, id);

        if (result != NULL) {

            cout << "Book Found\n";
            cout << "Book ID: " << result->data.id << endl;
            cout << "Title: " << result->data.title << endl;
            cout << "Author: " << result->data.author << endl;
        }

        else {
            cout << "Book Not Found\n";
        }
    }

    // Find Minimum Node
    BSTNode* findMin(BSTNode* root) {

        while (root->left != NULL)
            root = root->left;

        return root;
    }

    // Delete Book From BST
    BSTNode* deleteNode(BSTNode* root, int id) {

        if (root == NULL)
            return NULL;

        if (id < root->data.id)
            root->left = deleteNode(root->left, id);

        else if (id > root->data.id)
            root->right = deleteNode(root->right, id);

        else {

            // No Child
            if (root->left == NULL && root->right == NULL) {
                delete root;
                return NULL;
            }

            // One Child
            else if (root->left == NULL) {

                BSTNode* temp = root->right;
                delete root;
                return temp;
            }

            else if (root->right == NULL) {

                BSTNode* temp = root->left;
                delete root;
                return temp;
            }

            // Two Children
            else {

                BSTNode* temp = findMin(root->right);

                root->data = temp->data;

                root->right = deleteNode(root->right, temp->data.id);
            }
        }

        return root;
    }

    void deleteBook(int id) {
        root = deleteNode(root, id);
    }

    // Inorder Traversal
    void inorder(BSTNode* root) {

        if (root == NULL)
            return;

        inorder(root->left);

        cout << "Book ID: " << root->data.id << endl;
        cout << "Title: " << root->data.title << endl;
        cout << "Author: " << root->data.author << endl;
        cout << "------------------\n";

        inorder(root->right);
    }

    // Calculate Height
    int getHeight(BSTNode* root) {

        if (root == NULL)
            return 0;

        return 1 + max(getHeight(root->left), getHeight(root->right));
    }

    int treeHeight() {
        return getHeight(root);
    }

    // Count Search Steps
    int searchSteps(BSTNode* root, int id) {

        int steps = 0;

        while (root != NULL) {

            steps++;

            if (id == root->data.id)
                return steps;

            else if (id < root->data.id)
                root = root->left;

            else
                root = root->right;
        }

        return steps;
    }
};

// ================= AVL =================

// AVL Node
class AVLNode {
public:
    Book data;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(Book value) {
        data = value;
        left = right = NULL;
        height = 1;
    }
};

class AVL {
public:
    AVLNode* root;

    AVL() {
        root = NULL;
    }

    // Get Height
    int getHeight(AVLNode* root) {

        if (root == NULL)
            return 0;

        return root->height;
    }

    // Balance Factor
    int getBalance(AVLNode* root) {

        if (root == NULL)
            return 0;

        return getHeight(root->left) - getHeight(root->right);
    }

    // Left Rotation
    AVLNode* leftRotation(AVLNode* root) {

        AVLNode* temp = root->right;
        AVLNode* temp2 = temp->left;

        temp->left = root;
        root->right = temp2;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));

        return temp;
    }

    // Right Rotation
    AVLNode* rightRotation(AVLNode* root) {

        AVLNode* temp = root->left;
        AVLNode* temp2 = temp->right;

        temp->right = root;
        root->left = temp2;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));

        return temp;
    }

    // Left Right Rotation
    AVLNode* leftRightRotation(AVLNode* root) {

        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    // Right Left Rotation
    AVLNode* rightLeftRotation(AVLNode* root) {

        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    // Insert Book
    AVLNode* insert(AVLNode* root, Book book) {

        if (root == NULL)
            return new AVLNode(book);

        if (book.id < root->data.id)
            root->left = insert(root->left, book);

        else if (book.id > root->data.id)
            root->right = insert(root->right, book);

        else
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        // Left Left
        if (balance > 1 && book.id < root->left->data.id)
            return rightRotation(root);

        // Right Right
        if (balance < -1 && book.id > root->right->data.id)
            return leftRotation(root);

        // Left Right
        if (balance > 1 && book.id > root->left->data.id)
            return leftRightRotation(root);

        // Right Left
        if (balance < -1 && book.id < root->right->data.id)
            return rightLeftRotation(root);

        return root;
    }

    void insert(Book book) {
        root = insert(root, book);
    }

    // Search Book
    AVLNode* search(AVLNode* root, int id) {

        if (root == NULL)
            return NULL;

        if (id == root->data.id)
            return root;

        if (id < root->data.id)
            return search(root->left, id);

        return search(root->right, id);
    }

    void search(int id) {

        AVLNode* result = search(root, id);

        if (result != NULL) {

            cout << "Book Found\n";
            cout << "Book ID: " << result->data.id << endl;
            cout << "Title: " << result->data.title << endl;
            cout << "Author: " << result->data.author << endl;
        }

        else {
            cout << "Book Not Found\n";
        }
    }

    // Inorder Traversal
    void inorder(AVLNode* root) {

        if (root == NULL)
            return;

        inorder(root->left);

        cout << "Book ID: " << root->data.id << endl;
        cout << "Title: " << root->data.title << endl;
        cout << "Author: " << root->data.author << endl;
        cout << "------------------\n";

        inorder(root->right);
    }

    // Find Minimum
    AVLNode* findMin(AVLNode* root) {

        while (root->left != NULL)
            root = root->left;

        return root;
    }

    // Delete Book
    AVLNode* deleteNode(AVLNode* root, int id) {

        if (root == NULL)
            return NULL;

        if (id < root->data.id)
            root->left = deleteNode(root->left, id);

        else if (id > root->data.id)
            root->right = deleteNode(root->right, id);

        else {

            if (root->left == NULL || root->right == NULL) {

                AVLNode* temp;

                if (root->left != NULL)
                    temp = root->left;
                else
                    temp = root->right;

                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                }

                else {
                    *root = *temp;
                }

                delete temp;
            }

            else {

                AVLNode* temp = findMin(root->right);

                root->data = temp->data;

                root->right = deleteNode(root->right, temp->data.id);
            }
        }

        if (root == NULL)
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        // Left Left
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotation(root);

        // Left Right
        if (balance > 1 && getBalance(root->left) < 0)
            return leftRightRotation(root);

        // Right Right
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotation(root);

        // Right Left
        if (balance < -1 && getBalance(root->right) > 0)
            return rightLeftRotation(root);

        return root;
    }

    void deleteBook(int id) {
        root = deleteNode(root, id);
    }

    // Print Books In Range
    void printInRange(AVLNode* root, int minID, int maxID) {

        if (root == NULL)
            return;

        if (root->data.id > minID)
            printInRange(root->left, minID, maxID);

        if (root->data.id >= minID && root->data.id <= maxID) {

            cout << "Book ID: " << root->data.id << endl;
            cout << "Title: " << root->data.title << endl;
            cout << "Author: " << root->data.author << endl;
            cout << "------------------\n";
        }

        if (root->data.id < maxID)
            printInRange(root->right, minID, maxID);
    }

    void printInRange(int minID, int maxID) {
        printInRange(root, minID, maxID);
    }

    // Closest Book ID
    int closestID(AVLNode* root, int target) {

        int closest = root->data.id;

        while (root != NULL) {

            if (abs(root->data.id - target) < abs(closest - target))
                closest = root->data.id;

            if (target < root->data.id)
                root = root->left;

            else if (target > root->data.id)
                root = root->right;

            else
                return root->data.id;
        }

        return closest;
    }

    void closestID(int target) {

        if (root == NULL) {
            cout << "Tree Is Empty\n";
            return;
        }

        cout << "Closest Book ID: "
             << closestID(root, target)
             << endl;
    }

    int treeHeight() {
        return getHeight(root);
    }

    // Count Search Steps
    int searchSteps(AVLNode* root, int id) {

        int steps = 0;

        while (root != NULL) {

            steps++;

            if (id == root->data.id)
                return steps;

            else if (id < root->data.id)
                root = root->left;

            else
                root = root->right;
        }

        return steps;
    }
};

// ================= MAIN =================

int main() {

    BST bst;
    AVL avl;

    int randomIDs[] = {
        50,10,70,20,90,
        15,35,80,60,5,
        95,1,40,65,25,
        85,75,55,45,30
    };

    for (int i = 0; i < 20; i++) {

        Book b(
            randomIDs[i],
            "Book",
            "Author"
        );

        bst.insert(b);
        avl.insert(b);
    }

    cout << "===== BST INORDER =====\n\n";
    bst.inorder(bst.root);

    cout << "\n===== AVL INORDER =====\n\n";
    avl.inorder(avl.root);

    cout << "\n===== SEARCH =====\n";
    avl.search(65);

    cout << "\n===== DELETE BOOK =====\n";
    avl.deleteBook(35);

    cout << "After Delete:\n";
    avl.inorder(avl.root);

    cout << "\n===== RANGE SEARCH =====\n";
    avl.printInRange(20, 70);

    cout << "\n===== CLOSEST ID =====\n";
    avl.closestID(77);

    cout << "\n===== COMPARISON =====\n";

    cout << "BST Height: "
         << bst.treeHeight()
         << endl;

    cout << "AVL Height: "
         << avl.treeHeight()
         << endl;

    cout << "BST Search Steps: "
         << bst.searchSteps(bst.root, 90)
         << endl;

    cout << "AVL Search Steps: "
         << avl.searchSteps(avl.root, 90)
         << endl;

    // ===== SORTED IDS =====

    BST bst2;
    AVL avl2;

    for (int i = 10; i <= 200; i += 10) {

        Book b(
            i,
            "SortedBook",
            "Author"
        );

        bst2.insert(b);
        avl2.insert(b);
    }

    cout << "\n===== SORTED IDS COMPARISON =====\n";

    cout << "BST Height: "
         << bst2.treeHeight()
         << endl;

    cout << "AVL Height: "
         << avl2.treeHeight()
         << endl;

    cout << "BST Search Steps: "
         << bst2.searchSteps(bst2.root, 190)
         << endl;

    cout << "AVL Search Steps: "
         << avl2.searchSteps(avl2.root, 190)
         << endl;

    return 0;
}