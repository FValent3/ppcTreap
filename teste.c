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

typedef struct Treap
{
    node *root;
}treap;

void insertTreapNode(treap **t, node *m);
treap * createTreap();
node *insertNode(node *n, node *m);
node *createNode();
void printNode(node *n);

//Testing module
int main(int argc, char **argv)
{
    time_t t;
    srand( (unsigned) time(&t));

    treap *tree = createTreap();
    node *n = createNode();
    insertTreapNode(&tree, n);
    //printNode(tree->root);
    node *m = createNode();
    insertTreapNode(&tree, m);

    return 0;
}

treap * createTreap(){
    treap * t = (treap*)malloc(sizeof(treap));
    t->root = NULL;
    return t;
}

void insertTreapNode(treap **t, node *m)
{
    (*t)->root = insertNode((*t)->root, m);
}

node *insertNode(node *n, node *m)
{
    if (n == NULL)
    {
        n = m;
        return n;
    }

    if (m->key <= n->key)
    {
        printf("left\n");
        n->leftchild = insertNode(n->leftchild, m);
    }
    else
    {
        printf("right\n");
        n->rigthchild = insertNode(n->rigthchild, m);
    }
    return n;
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