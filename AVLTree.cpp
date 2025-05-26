#include "AVLTree.h"
#include <algorithm>  // για max()

// Constructor: αρχικοποίηση κενού δέντρου
AVLTree::AVLTree() : root(nullptr), nodeCount(0) {}

// Destructor: απελευθέρωση όλων των κόμβων
AVLTree::~AVLTree() {
    clearTree(root);
    root = nullptr;
    nodeCount = 0;
}

// Επιστρέφει το ύψος κόμβου ή 0 αν node==nullptr
int AVLTree::height(AVLNode* node) {
    return node ? node->height : 0;
}

// Υπολογίζει balance factor
int AVLTree::balanceFactor(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Δεξιά περιστροφή (LL)
AVLNode* AVLTree::rotateRight(AVLNode* x) {
    AVLNode* y = x->left;
    AVLNode* T2 = y->right;
    // Εκτέλεση περιστροφής
    y->right = x;
    x->left = T2;
    // Ενημέρωση ύψους
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    return y;  // νέα ρίζα
}

// Αριστερή περιστροφή (RR)
AVLNode* AVLTree::rotateLeft(AVLNode* y) {
    AVLNode* x = y->right;
    AVLNode* T2 = x->left;
    // Εκτέλεση περιστροφής
    x->left = y;
    y->right = T2;
    // Ενημέρωση ύψους
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return x;  // νέα ρίζα
}

// Αναδρομική εισαγωγή κόμβου
AVLNode* AVLTree::insertNode(AVLNode* node, int key) {
    if (!node) {
        return new AVLNode(key);
    }
    if (key < node->key) {
        node->left = insertNode(node->left, key);
    }
    else{
        node->right = insertNode(node->right, key);
    }
    
    // Ενημέρωση ύψους
    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = balanceFactor(node);
    // LL περίπτωση
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);
    // RR περίπτωση
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    // LR περίπτωση
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // RL περίπτωση
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;  // χωρίς περιστροφή
}

// Δημόσια μέθοδος εισαγωγής
void AVLTree::insert(int key) {
    if (search(key)) return;        // Αν το key υπάρχει ήδη, το παραλείπουμε
    root = insertNode(root, key);
	nodeCount++;    // Αυξάνουμε το πλήθος κόμβων
}

// Εύρεση κόμβου με ελάχιστο key
AVLNode* AVLTree::findMinNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// Αναδρομική διαγραφή κόμβου
AVLNode* AVLTree::deleteNode(AVLNode* node, int key) {
    if (!node) {
        return node;
    }
    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    }
    else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    }
    else {
        // Περίπτωση με 1 ή 0 παιδιά
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                // χωρίς παιδιά
                temp = node;
                node = nullptr;
            }
            else {
                // με ένα παιδί
                *node = *temp;
            }
            delete temp;
        }
        else {
            // Δύο παιδιά: αντικατάσταση με in-order διάδοχο
            AVLNode* temp = findMinNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }
    if (!node) return node;
    // Ενημέρωση ύψους
    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = balanceFactor(node);
    // LL
    if (balance > 1 && balanceFactor(node->left) >= 0)
        return rotateRight(node);
    // LR
    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // RR
    if (balance < -1 && balanceFactor(node->right) <= 0)
        return rotateLeft(node);
    // RL
    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

// Δημόσια μέθοδος διαγραφής
void AVLTree::deleteKey(int key) {
	if (!search(key)) return;        // Αν το key δεν υπάρχει, το παραλείπουμε
    root = deleteNode(root, key);
    nodeCount--;
}

// Αναζήτηση key (μη αναδρομική)
bool AVLTree::search(int key) {
    AVLNode* cur = root;
    while (cur) {
        if (key == cur->key) return true;
        cur = (key < cur->key ? cur->left : cur->right);
    }
    return false;
}

// Επιστροφή ελάχιστου key ή -1 αν κενό
int AVLTree::findMin() {
    if (!root) return -1;
    AVLNode* mn = findMinNode(root);
    return mn ? mn->key : -1;
}

// Επιστροφή πλήθους κόμβων
int AVLTree::getSize() {
    return nodeCount;
}

// Διαγραφή όλων των κόμβων ενός υποδέντρου
void AVLTree::clearTree(AVLNode* node) {
    if (!node) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// Κατασκευή από πίνακα δεδομένων
void AVLTree::buildFromArray(int* data, int n) {
    // Καθαρισμός παλιού δέντρου
    clearTree(root);
    root = nullptr;
    nodeCount = 0;
    // Εισαγωγή στοιχείων ένα-ένα
    for (int i = 0; i < n; ++i) {
        insert(data[i]);
    }
}
