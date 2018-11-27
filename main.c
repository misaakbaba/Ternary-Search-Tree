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



//GLOBAL VARİABLES
tst *root;

int main() {

    read("input.txt.txt");
   tst *temp=findMax(root);

   printf("%d",temp->data);
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

        insert(&root,num);
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
tst *findMax(tst *tree){
    if(tree==NULL) return NULL;
    if(tree->right==NULL) // right ve middle null ise kendini döndür
        if (tree->middle==NULL) return tree;

    if(tree->right==NULL) //right null ve middle null değilse middle ı recursive fonsiyona gönder
        if (tree->middle!=NULL) return findMax(tree->middle);

    return findMax(tree->right);   //son case right a git
}