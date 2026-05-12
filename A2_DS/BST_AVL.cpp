#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

// ================= BOOK =================

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

    // Insert New Book
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

    // Search For Book
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
            cout << "Book Found!\n";
            cout << "Book ID: " << result->data.id << endl;
            cout << "Title:   " << result->data.title << endl;
            cout << "Author:  " << result->data.author << endl;
        }
        else {
            cout << "Book Not Found.\n";
        }
    }

    // Find Minimum Node
    BSTNode* findMin(BSTNode* root) {

        while (root->left != NULL)
            root = root->left;

        return root;
    }

    // Delete Book
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

        cout << "ID: " << root->data.id
             << " | Title: " << root->data.title
             << " | Author: " << root->data.author << "\n";

        inorder(root->right);
    }

    void inorder() {
        inorder(root);
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

    int searchSteps(int id) {
        return searchSteps(root, id);
    }

    // Print Books In ID Range
    void printInRange(BSTNode* root, int minID, int maxID) {

        if (root == NULL)
            return;

        if (root->data.id > minID)
            printInRange(root->left, minID, maxID);

        if (root->data.id >= minID && root->data.id <= maxID) {
            cout << "ID: " << root->data.id
                 << " | Title: " << root->data.title
                 << " | Author: " << root->data.author << "\n";
        }

        if (root->data.id < maxID)
            printInRange(root->right, minID, maxID);
    }

    void printInRange(int minID, int maxID) {
        printInRange(root, minID, maxID);
    }

    // Find Closest Book ID
    int closestID(BSTNode* root, int target) {

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
            cout << "Tree Is Empty.\n";
            return;
        }

        cout << "Closest Book ID to " << target << ": "
             << closestID(root, target) << "\n";
    }
};

// ================= AVL =================

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
            cout << "Book Found!\n";
            cout << "Book ID: " << result->data.id << endl;
            cout << "Title:   " << result->data.title << endl;
            cout << "Author:  " << result->data.author << endl;
        }
        else {
            cout << "Book Not Found.\n";
        }
    }

    // Inorder Traversal
    void inorder(AVLNode* root) {

        if (root == NULL)
            return;

        inorder(root->left);

        cout << "ID: " << root->data.id
             << " | Title: " << root->data.title
             << " | Author: " << root->data.author << "\n";

        inorder(root->right);
    }

    void inorder() {
        inorder(root);
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
            cout << "ID: " << root->data.id
                 << " | Title: " << root->data.title
                 << " | Author: " << root->data.author << "\n";
        }

        if (root->data.id < maxID)
            printInRange(root->right, minID, maxID);
    }

    void printInRange(int minID, int maxID) {
        printInRange(root, minID, maxID);
    }

    // Find Closest Book ID
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
            cout << "Tree Is Empty.\n";
            return;
        }

        cout << "Closest Book ID to " << target << ": "
             << closestID(root, target) << "\n";
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

    int searchSteps(int id) {
        return searchSteps(root, id);
    }
};

// ================= MAIN =================

int main() {

    BST bst;
    AVL avl;

    // 20 Books With Random IDs
    Book books[] = {
        Book(50,  "The Great Gatsby",         "F. Scott Fitzgerald"),
        Book(10,  "To Kill a Mockingbird",    "Harper Lee"),
        Book(70,  "1984",                     "George Orwell"),
        Book(20,  "Pride and Prejudice",      "Jane Austen"),
        Book(90,  "The Catcher in the Rye",   "J.D. Salinger"),
        Book(15,  "Brave New World",          "Aldous Huxley"),
        Book(35,  "The Hobbit",               "J.R.R. Tolkien"),
        Book(80,  "Fahrenheit 451",           "Ray Bradbury"),
        Book(60,  "Jane Eyre",                "Charlotte Bronte"),
        Book(5,   "Moby Dick",                "Herman Melville"),
        Book(95,  "War and Peace",            "Leo Tolstoy"),
        Book(1,   "Crime and Punishment",     "Fyodor Dostoevsky"),
        Book(40,  "The Alchemist",            "Paulo Coelho"),
        Book(65,  "The Picture of Dorian Gray","Oscar Wilde"),
        Book(25,  "Anna Karenina",            "Leo Tolstoy"),
        Book(85,  "Les Miserables",           "Victor Hugo"),
        Book(75,  "Don Quixote",              "Miguel de Cervantes"),
        Book(55,  "Wuthering Heights",        "Emily Bronte"),
        Book(45,  "Great Expectations",       "Charles Dickens"),
        Book(30,  "The Odyssey",              "Homer")
    };

    for (int i = 0; i < 20; i++) {
        bst.insert(books[i]);
        avl.insert(books[i]);
    }

    // ===== INORDER TRAVERSAL =====
    cout << "========================================\n";
    cout << "         BST - INORDER TRAVERSAL        \n";
    cout << "========================================\n";
    bst.inorder();

    cout << "\n========================================\n";
    cout << "         AVL - INORDER TRAVERSAL        \n";
    cout << "========================================\n";
    avl.inorder();

    // ===== SEARCH =====
    cout << "\n========================================\n";
    cout << "                 SEARCH                 \n";
    cout << "========================================\n";
    cout << "[BST] Searching for ID 65:\n";
    bst.search(65);
    cout << "\n[AVL] Searching for ID 65:\n";
    avl.search(65);

    // ===== DELETE =====
    cout << "\n========================================\n";
    cout << "                 DELETE                 \n";
    cout << "========================================\n";
    cout << "Deleting Book ID 35 from both trees...\n\n";
    bst.deleteBook(35);
    avl.deleteBook(35);
    cout << "[BST] After Delete:\n";
    bst.inorder();
    cout << "\n[AVL] After Delete:\n";
    avl.inorder();

    // ===== RANGE SEARCH =====
    cout << "\n========================================\n";
    cout << "              RANGE SEARCH              \n";
    cout << "========================================\n";
    cout << "[BST] Books with IDs between 20 and 70:\n";
    bst.printInRange(20, 70);
    cout << "\n[AVL] Books with IDs between 20 and 70:\n";
    avl.printInRange(20, 70);

    // ===== CLOSEST ID =====
    cout << "\n========================================\n";
    cout << "               CLOSEST ID               \n";
    cout << "========================================\n";
    cout << "[BST] ";
    bst.closestID(77);
    cout << "[AVL] ";
    avl.closestID(77);

    // ===== COMPARISON - RANDOM IDs =====
    cout << "\n========================================\n";
    cout << "       COMPARISON - RANDOM IDs          \n";
    cout << "========================================\n";
    cout << "BST Height:         " << bst.treeHeight() << "\n";
    cout << "AVL Height:         " << avl.treeHeight() << "\n";
    cout << "BST Search Steps (ID=90): " << bst.searchSteps(90) << "\n";
    cout << "AVL Search Steps (ID=90): " << avl.searchSteps(90) << "\n";

    // ===== COMPARISON - SORTED IDs =====
    BST bst2;
    AVL avl2;

    string sortedTitles[] = {
        "Book Alpha","Book Beta","Book Gamma","Book Delta","Book Epsilon",
        "Book Zeta","Book Eta","Book Theta","Book Iota","Book Kappa",
        "Book Lambda","Book Mu","Book Nu","Book Xi","Book Omicron",
        "Book Pi","Book Rho","Book Sigma","Book Tau","Book Upsilon"
    };

    for (int i = 0; i < 20; i++) {
        Book b((i + 1) * 10, sortedTitles[i], "Author " + to_string(i + 1));
        bst2.insert(b);
        avl2.insert(b);
    }

    cout << "\n========================================\n";
    cout << "       COMPARISON - SORTED IDs          \n";
    cout << "========================================\n";
    cout << "BST Height:         " << bst2.treeHeight() << "\n";
    cout << "AVL Height:         " << avl2.treeHeight() << "\n";
    cout << "BST Search Steps (ID=190): " << bst2.searchSteps(190) << "\n";
    cout << "AVL Search Steps (ID=190): " << avl2.searchSteps(190) << "\n";

    cout << "\n========================================\n";
    cout << "               SUMMARY                  \n";
    cout << "========================================\n";
    cout << "Random IDs -> BST Height: " << bst.treeHeight()
         << " | AVL Height: " << avl.treeHeight() << "\n";
    cout << "Sorted IDs -> BST Height: " << bst2.treeHeight()
         << " | AVL Height: " << avl2.treeHeight() << "\n";
    cout << "(Sorted IDs expose BST worst case: linear height)\n";

    return 0;
}
