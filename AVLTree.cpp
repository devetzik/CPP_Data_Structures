#include "AVLTree.h"

// Constructor
AVLTree::AVLTree(){
    root = nullptr;
    nodeCount = 0;
}


// Επιστρέφει το ύψος κόμβου ή 0 αν node==nullptr
int AVLTree::height(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
	else {
		return node->height;
    }
}

// Υπολογίζει balance factor
int AVLTree::balanceFactor(AVLNode* node) {
	if (node == nullptr) {
		return 0;
	}
    else {
		return height(node->left) - height(node->right);
    }
}


// Δεξιά περιστροφή (LL)
AVLNode* AVLTree::rotateRight(AVLNode* x) {
    AVLNode* y = x->left;
    AVLNode* T2 = y->right;
    
    y->right = x;
    x->left = T2;   // Εκτέλεση περιστροφής
    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;   // Ενημέρωση ύψους
    return y;  // νέα ρίζα
}


// Αριστερή περιστροφή (RR)
AVLNode* AVLTree::rotateLeft(AVLNode* y) {
    AVLNode* x = y->right;
    AVLNode* T2 = x->left;
    
    x->left = y;
    y->right = T2;   // Εκτέλεση περιστροφής

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;    // Ενημέρωση ύψους
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

    node->height = 1 + max(height(node->left), height(node->right));    // Ενημέρωση ύψους
    int balance = balanceFactor(node);

    if (balance > 1 && key < node->left->key)    // LL περίπτωση
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)    // RR περίπτωση
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {    // LR περίπτωση
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {    // RL περίπτωση
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;  // χωρίς περιστροφή
}


// Eισαγωγή νέου κόμβου
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
        if (!node->left || !node->right) {        // Περίπτωση με 1 ή 0 παιδιά
            AVLNode* temp;
            if (node->left) {
                temp = node->left;
            }
            else {
                temp = node->right;
            }

            if (!temp) {    // χωρίς παιδιά
                temp = node;
                node = nullptr;
            }
            else {   // με ένα παιδί
                *node = *temp;
            }
            delete temp;
        }
        else {
            AVLNode* temp = findMinNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }
    if (!node) {
        return node;
    }
    node->height = 1 + max(height(node->left), height(node->right));    // Ενημέρωση ύψους
    int balance = balanceFactor(node);
 
    if (balance > 1 && balanceFactor(node->left) >= 0)   // LL
        return rotateRight(node);
   
    if (balance > 1 && balanceFactor(node->left) < 0) {  // LR
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
   
    if (balance < -1 && balanceFactor(node->right) <= 0)  // RR
        return rotateLeft(node);

    if (balance < -1 && balanceFactor(node->right) > 0) {  // RL
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
        if (key == cur->key) {
            return true;
        }
        cur = (key < cur->key ? cur->left : cur->right);
    }
    return false;
}


// Επιστροφή ελάχιστου key ή -1 αν κενό
int AVLTree::findMin() {
    if (!root) return -1;
    AVLNode* mn = findMinNode(root);
    if (mn == nullptr) { 
        return -1;
    }
    else{
		return mn->key;
    }
}


// Επιστροφή πλήθους κόμβων
int AVLTree::getSize() {
    return nodeCount;
}


// Κατασκευή από πίνακα δεδομένων
void AVLTree::buildFromArray(int* data, int n) {
    root = nullptr;
    nodeCount = 0;
    for (int i = 0; i < n; ++i) {
        insert(data[i]);    // Εισαγωγή στοιχείων ένα-ένα
    }
}


// Βοηθητική συνάρτηση για το μέγιστο δύο ακεραίων
int AVLTree::max(int a, int b) {
    if (a < b) {
        return b;
    }
	else {
		return a;
    }
}