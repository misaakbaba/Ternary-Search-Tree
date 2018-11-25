#include<stdlib.h>
#include<stdio.h>
#include <math.h>

struct tst_tree {
    int data;
    struct tst_tree *right, *left, *middle;
};
typedef struct tst_tree tst;

//FUNCTİON PROTOTYPES
void read(char file[]);

void insert(tst **tree, int val);


//GLOBAL VARİABLES


int main() {
    printf("Hello, World!\n");
    return 0;
}

void read(char file[]) { //function that read file content
    FILE *fp;
    fp = fopen(file, "r");
    fp = fopen(file, "r");
    if (fp == NULL) {
        puts("Cannot open file");
        return;
    }
    char str[20];
    while (!feof(fp)) { //read file
        fscanf(fp, "%s", str);
        //    insert(&hdr, str, docId, lenght, category); // insertion word to master linked list
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
    } else if (val > (*tree)->data && val < pow((*tree)->data, 2)) { //middle node
        insert(&(*tree)->middle, val);
    } else if (val > pow((*tree)->data, 2)) { // right node
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
    }
    else if (val > (*tree)->data && val < pow((*tree)->data, 2)) { // middle node
        search(&((*tree)->middle), val);
    }
    else if (val > pow((*tree)->data, 2)) { // right node
        search(&((*tree)->right), val);
    }
    else if (val == (*tree)->data) {
        return *tree; // return search node
    }
}