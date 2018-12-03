#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct tst_tree {
    int data;
    struct tst_tree *right, *left, *middle;
};
typedef struct tst_tree tst;

//FUNCTİON PROTOTYPES
void read(char file[]);

void insert(tst **tree, int val);

tst *search(tst **tree, int val);

tst *findMax(tst *tree);

tst *findMin(tst *tree);

tst *deleteNode(tst *tree, int key);

void rebuild(tst *tree, tst *base);

void traversal(tst *tree);


//GLOBAL VARİABLES
tst *root;

int main() {
    read("input.txt.txt");
//    traversal(root->right);
//    deleteNode(root, 40);
//    puts("");
//    traversal(root->right);
    deleteNode(root, 3);
    deleteNode(root, 2);


}

void read(char file[]) { //function that read file content
    FILE *fp;
    fp = fopen(file, "r");
    fp = fopen(file, "r");
    if (fp == NULL) {
        puts("Cannot open file");
        return;
    }
    int num;
    while (!feof(fp)) { //read file
        fscanf(fp, "%d", &num);
//        printf("%d\t",num);
        insert(&root, num);
    }
    fclose(fp);
}

void insert(tst **tree, int val) {
    tst *temp = NULL;
    if (!(*tree)) {
        temp = malloc(sizeof(tst));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if (val < (*tree)->data) { //left node
        insert(&(*tree)->left, val);
    } else if (val > (*tree)->data && val < ((*tree)->data * (*tree)->data)) { //middle node
        insert(&(*tree)->middle, val);
    } else if (val > ((*tree)->data * (*tree)->data)) { // right node
        insert(&(*tree)->right, val);
    }
}

tst *search(tst **tree, int val) {
    if (!(*tree)) {
        return NULL;
    }
    if (val < (*tree)->data) // left node
    {
        search(&((*tree)->left), val);
    } else if (val > (*tree)->data && val < ((*tree)->data * (*tree)->data)) { // middle node
        search(&((*tree)->middle), val);
    } else if (val > ((*tree)->data * (*tree)->data)) { // right node
        search(&((*tree)->right), val);
    } else if (val == (*tree)->data) {
        return *tree; // return search node
    }
}

tst *findMax(tst *tree) {
    if (tree == NULL) return NULL;
    if (tree->right == NULL) // right ve middle null ise kendini döndür
        if (tree->middle == NULL) return tree;

    if (tree->right == NULL) //right null ve middle null değilse middle ı recursive fonsiyona gönder
        if (tree->middle != NULL) return findMax(tree->middle);

    return findMax(tree->right);   //son case right a git
}

tst *findMin(tst *tree) {
    tst *current = tree;

    while (current->left != NULL)
        current = current->left;

    return current;
}

tst *deleteNode(tst *tree, int key) {

    if (tree == NULL) return tree;  //base case
    tst *temp;
    //left side case
    if (key < tree->data)
        tree->left = deleteNode(tree->left, key);

        //middle side case
    else if (key > tree->data && (key < (tree->data * tree->data)))
        tree->middle = deleteNode(tree->middle, key);

        //right side case
    else if (key > (tree->data * tree->data))
        tree->right = deleteNode(tree->right, key);

        //if the same tree's key
    else {
        if (tree->left && tree->middle) {
            temp = findMin(tree->middle);
            tree->data = temp->data;
            tree->middle = deleteNode(tree->middle, tree->data);
            rebuild(tree->right, tree->right);
        } else if (tree->left && tree->right) {
            temp = findMax(tree->left);
            tree->data = temp->data;
            tree->left = deleteNode(tree->left, tree->data);
        } else {
            temp = tree;
            if (tree->left != NULL)
                tree = tree->left;
            else if (tree->right != NULL)
                tree = tree->right;
            else if (tree->middle != NULL)
                tree = tree->middle;
            else if (tree->middle == NULL && tree->left == NULL && tree->right == NULL)
                tree = NULL;
            free(temp);
        }
    }
    return tree;
}

void rebuild(tst *tree, tst *base) {
//    tst *temp = baseRoot;
    //base case
    int data = findMax(base)->data;
    if (tree->right == NULL || (base->data) * ((base->data)) < data) {
        tree->right = NULL;
        return;
    }
    deleteNode(base->right, data);
    insert(&root, data);
    if (tree->right->left == NULL && tree->right->middle == NULL && tree->right->right == NULL) {
        data = findMax(base)->data;
        deleteNode(base->right, data);
        insert(&root, data);
        tree->right = NULL;
        return;
    }
    rebuild(tree, base);
}

void traversal(tst *tree) {
    if (tree == NULL) return;
    traversal(tree->left);
    traversal(tree->middle);
    traversal(tree->right);

    printf("%d--", tree->data);
}