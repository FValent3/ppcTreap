#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct Node
{
    char key;
    int value;
    struct Node *leftchild, *rightchild;
} node;

node *insertTreapNode(node *n, node *m);
node *createNode();
node *leftRotate(node *n);
node *rightRotate(node *n);
void printNode(node *n);

//Testing module
int main(int argc, char **argv)
{
    time_t t;
    srand((unsigned)time(&t));

    node *root = NULL;
    node *n = createNode();
    node *m = createNode();
    root = insertTreapNode(root, n);
    printNode(root);
    insertTreapNode(root, m);

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

        if (n->leftchild->value > n->value)
        {
            n = rightRotate(n);
        }
    }
    else
    {
        printf("right\n");
        n->rightchild = insertTreapNode(n->rightchild, m);

        if (n->rightchild->value > n->value)
        {
            n = leftRotate(n);
        }
    }
    return m;
}

node *createNode()
{
    node *n = (node *)malloc(sizeof(node));
    n->key = rand() % 26 + 97;
    n->value = rand() % RAND_MAX;
    printf("key: %c value: %d\n", n->key, n->value);
    n->leftchild = NULL;
    n->rightchild = NULL;
    return n;
}

node *rightRotate(node *n)
{
    node *x = n->leftchild;
    node *y = n->rightchild;
    x->rightchild = n;
    n->leftchild = y;
    return x;
}

node *leftRotate(node *n)
{
    node *y = n->rightchild;
    node *x = n->leftchild;
    y->leftchild = n;
    n->rightchild = x;
    return y;
}

void printNode(node *n)
{
    printf("key: %c\nvalue: %d\nleftchild: %s\nrightchild: %s\n",
           n->key, n->value, n->leftchild, n->rightchild);
}