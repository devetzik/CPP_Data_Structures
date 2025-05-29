#ifndef AVLTREE_H
#define AVLTREE_H

// Δομή κόμβου του AVL δέντρου
struct AVLNode {
    int key;           // το κλειδί/τιμή του κόμβου
    int height;        // το ύψος του υποδέντρου με ρίζα αυτόν τον κόμβο
    AVLNode* left;     // δείκτης στο αριστερό παιδί
    AVLNode* right;    // δείκτης στο δεξί παιδί

    // Κατασκευαστής κόμβου
    AVLNode(int k){
        key = k;
        height = 1;
		left = nullptr;
		right = nullptr;
    }
};


class AVLTree {
private:
    AVLNode* root;     // ρίζα του AVL δέντρου
    int nodeCount;     // πλήθος κόμβων στο δέντρο

    int height(AVLNode* node);          // Επιστρέφει το ύψος του κόμβου, ή 0 αν ο δείκτης είναι nullptr
    int balanceFactor(AVLNode* node);   // Υπολογίζει balance factor = ύψος(αριστερό) − ύψος(δεξί)
    AVLNode* rotateRight(AVLNode* x);   // Δεξιά περιστροφή γύρω από x, επιστρέφει τη νέα ρίζα
    AVLNode* rotateLeft(AVLNode* y);    // Αριστερή περιστροφή γύρω από y, επιστρέφει τη νέα ρίζα
    AVLNode* insertNode(AVLNode* node, int key);  // Αναδρομική εισαγωγή: επιστρέφει νέa ρίζα υποδέντρου
    AVLNode* deleteNode(AVLNode* node, int key);   // Αναδρομική διαγραφή: επιστρέφει νέa ρίζα υποδέντρου
    AVLNode* findMinNode(AVLNode* node);  // Επιστρέφει τον κόμβο με το ελάχιστο key σε ένα υποδέντρο

public:
    AVLTree();                     // constructor

	int max(int a, int b);         // Επιστρέφει το μέγιστο από δύο ακέραιους
    void insert(int key);          // εισαγωγή νέου key
    void deleteKey(int key);       // διαγραφή υπάρχοντος key
    bool search(int key);          // αναζήτηση key, επιστρέφει true αν βρεθεί
    int findMin();                 // επιστρέφει το ελάχιστο key ή -1 αν κενό
    int getSize();                 // επιστρέφει πλήθος κόμβων
    void buildFromArray(int* data, int n);  // κατασκευή από πίνακα δεδομένων
};

#endif