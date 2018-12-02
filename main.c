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

tst *deleteNode2(tst **tree, int key);


void rebuild(tst *tree);

void traversal(tst *tree);


//GLOBAL VARİABLES
tst *root;

int main() {

    read("input.txt.txt");
    traversal(root->right);
    puts("");
    deleteNode(root, 40);
//    root = deleteNode(root, 2000);
//    root = deleteNode(root, 1700);
    rebuild(root->right->right);
    root->right->right = NULL;
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
            if (root->left != NULL)
                root = root->left;
            else if (root->right != NULL)
                root = root->right;
            else if (root->middle != NULL)
                root = root->middle;
            else if (root->middle == NULL && root->left == NULL && root->right == NULL)
                root = NULL;
            free(temp);
        }

    }
    return root;

}

tst *deleteNode2(tst **tree, int key) {
/*
 * 1   burada silinecek node un yerini bul if else ile
 * 2
*/
    //base case
    if ((*tree) == NULL) return (*tree);
    tst *temp;
    //left side case
    if (key < (*tree)->data)
        (*tree)->left = deleteNode2((*tree)->left, key);

        //middle side case
    else if (key > (*tree)->data && (key < ((*tree)->data * (*tree)->data)))
        (*tree)->middle = deleteNode2((*tree)->middle, key);

        //right side case
    else if (key > ((*tree)->data * (*tree)->data))
        (*tree)->right = deleteNode2((*tree)->right, key);

        //if the same (*tree)'s key
    else {
        if ((*tree)->left && (*tree)->middle) {
            temp = findMin((*tree)->middle);
            (*tree)->data = temp->data;
            (*tree)->middle = deleteNode2((*tree)->middle, (*tree)->data);
        } else {
            temp = (*tree);
            if ((*tree)->left != NULL)
                (*tree) = (*tree)->left;
            else if ((*tree)->right != NULL)
                (*tree) = (*tree)->right;
            else if ((*tree)->middle != NULL)
                (*tree) = (*tree)->middle;
            else if ((*tree)->middle == NULL && (*tree)->left == NULL && (*tree)->right == NULL)
                (*tree) = NULL;
            free(temp);
        }

    }
    return (*tree);

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

//    printf("tree data is:%d--",tree->data);
    int data = tree->data;
//    tree=NULL;
//    tree->data=-1;
    deleteNode(tree, data);
//    tst *temp=search(&tree,data);
//    temp = NULL;
//    free(temp);
    insert(&root, data);

}

void traversal(tst *tree) {
    if (tree == NULL) return;
    traversal(tree->left);
    traversal(tree->middle);
    traversal(tree->right);


    printf("%d--", tree->data);
}

