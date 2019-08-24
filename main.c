#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char key;
    int value;
    struct Node *leftchild, *rigthchild;
} node;

node *insertTreapNode(node *n, node *m);
node *createNode(char key, int value);
void printNode(node *n);

//Testing module
int main(int argc, char **argv)
{
    node *root = NULL;
    node *n = createNode('a', 2);
    node *m = createNode('c', 1);
    root = insertTreapNode(root, n);
    printNode(root);
    insertTreapNode(root, m);
    printNode(root->rigthchild);

    return 0;
}

node *insertTreapNode(node *n, node *m)
{
    if (!n)
    {
        return m;
    }

    if (m->key <= n->key)
    {
        printf("left\n");
        n->leftchild = insertTreapNode(n->leftchild, m);
    }
    else
    {
        printf("right\n");
        n->rigthchild = insertTreapNode(n->rigthchild, m);
    }
    return m;
}

node *createNode(char key, int value)
{
    node *n = (node *)malloc(sizeof(node));
    n->key = key;
    n->value = value;
    n->leftchild = NULL;
    n->rigthchild = NULL;
    return n;
}

void printNode(node *n)
{
    printf("key: %c\nvalue: %d\nleftchild: %s\nrigthchild: %s\n",
           n->key, n->value, n->leftchild, n->rigthchild);
}