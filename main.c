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

tst *deleteNode(tst *root, int key);

void rebuild(tst *tree);

void traversal(tst *tree);



//GLOBAL VARİABLES
tst *root;

int main() {

    read("input.txt.txt");
    root = deleteNode(root, 40);
    rebuild(root->right->right);
    traversal(root->right);
//    printf("%d",root->right->middle->data);

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

tst *deleteNode(tst *root, int key) {
/*
 * 1   burada silinecek node un yerini bul if else ile
 * 2
*/
    //base case
    if (root == NULL) return root;
    tst *temp;
    //left side case
    if (key < root->data)
        root->left = deleteNode(root->left, key);

        //middle side case
    else if (key > root->data && (key < (root->data * root->data)))
        root->middle = deleteNode(root->middle, key);

        //right side case
    else if (key > (root->data * root->data))
        root->right = deleteNode(root->right, key);

        //if the same root's key
    else {
        if (root->left && root->middle) {
            temp = findMin(root->middle);
            root->data = temp->data;
            root->middle = deleteNode(root->middle, root->data);
        } else {
            temp = root;
            if (root->left == NULL)
                root = root->right;
            else if (root->right == NULL)
                root = root->left;
            free(temp);
        }

    }
    return root;

}
//        if (root->left == NULL){
//            tst *temp=root->right;
//            free(root);
//            return temp;
//        }
//        else if (root->right==NULL){
//            tst *temp=root->left;
//            free(root);
//            return temp;
//        }
/*
 * buraya da aradan ayıklama işlemi yazılacak
 */

void rebuild(tst *tree) {
//    tst *temp = baseRoot;

    if (tree == NULL) return;
    rebuild(tree->left);
    rebuild(tree->middle);
    rebuild(tree->right);

//    printf("%d--",tree->data);
    int data = tree->data;
    deleteNode(tree, data);
    insert(&root, data);

}
void traversal(tst *tree){
    if (tree == NULL) return;
    traversal(tree->left);
    traversal(tree->middle);
    traversal(tree->right);

    printf("%d--",tree->data);
}

