#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct Node
{
    char key;
    int value;
    struct Node *leftchild, *rigthchild;
} node;

node *insertTreapNode(node *n, node *m);
node *createNode();
void printNode(node *n);

//Testing module
int main(int argc, char **argv)
{
    time_t t;
    srand( (unsigned) time(&t));

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
    }
    else
    {
        printf("right\n");
        n->rigthchild = insertTreapNode(n->rigthchild, m);
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
    n->rigthchild = NULL;
    return n;
}

void printNode(node *n)
{
    printf("key: %c\nvalue: %d\nleftchild: %s\nrigthchild: %s\n",
           n->key, n->value, n->leftchild, n->rigthchild);
}