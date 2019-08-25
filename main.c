#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

typedef struct Node
{
    long int key;
    long int value;
    struct Node *leftchild, *rightchild;
} node;

node *insertTreapNode(node *n, node *m);
node *createNode();
node *createNode1(char n, int m);
node *leftRotate(node *n);
node *rightRotate(node *n);
void printTree(node *n);
void printNode(node *n);
node *insertion(node *n, node *m);
//void *unionTree(node *n, node *m, node *b);
node * intersection(node *n, node *m, node *b);

//Testing module
int main(int argc, char **argv)
{
    time_t t;
    srand((unsigned)time(&t));

    node * root = NULL;
    node *n = createNode();
	//node *n = createNode1('q',10);
    node *m = createNode();
    //node *m = createNode1('h',20);
    //node *j = createNode1('f',81);
    node *j = createNode();
    node *l = createNode();
    root = insertTreapNode(root, n);
    root = insertTreapNode(root, m);
    root = insertTreapNode(root, j);
    root = insertTreapNode(root, l);
    printTree(root);
    printf("\n");

    node *root2 = NULL;
    node *n2 = createNode();
    //node *n2 = createNode1('d', 50);
    node *m2 = createNode();
    //node *m2 = createNode1('q',89);
    //node *j2 = createNode1('f',80);
    node *j2 = createNode();
    node *l2 = createNode();
    root2 = insertTreapNode(root2, n2);
    root2 = insertTreapNode(root2, m2);
    root2 = insertTreapNode(root2, j2);
    root2 = insertTreapNode(root2, l2);
    printTree(root2);
    printf("\n");

    node *root3 = NULL;
    root3 = intersection(root, root2, root3);
    printTree(root3);

    free (root);
    return 0;
}

node *insertTreapNode(node *n, node *m)
{
    if (!n)
    {
        n = m;
        return n;
    }

    if (m->key <= n->key)
    {

        n->leftchild = insertTreapNode(n->leftchild, m);

        if (n->leftchild->value > n->value)
        {
            n = rightRotate(n);
        }
    }
    else
    {
        n->rightchild = insertTreapNode(n->rightchild, m);

        if (n->rightchild->value > n->value)
        {
            n = leftRotate(n);
        }
    }
    return n;
}

node *createNode()
{
    node *n = (node *)malloc(sizeof(node));

    n->key = rand() % 26 + 97;
    n->value = rand() % 100;
    //printf("key: %c value: %d\n", n->key, n->value);
    n->leftchild = NULL;
    n->rightchild = NULL;
    return n;
}

node *createNode1(char n, int m)
{
    node *l = (node *)malloc(sizeof(node));
    l->key = n;
    l->value = m;
    //printf("key: %c value: %d\n", n->key, n->value);
    l->leftchild = NULL;
    l->rightchild = NULL;
    return l;
}

node *rightRotate(node *n)
{
    node *x = n->leftchild;
    node *y = x->rightchild;
    x->rightchild = n;
    n->leftchild = y;
    return x;
}

node *leftRotate(node *n)
{
    node *y = n->rightchild;
    node *x = y->leftchild;
    y->leftchild = n;
    n->rightchild = x;
    return y;
}

node *insertion(node *n, node *m)
{
    if(n == NULL)
        return m;
    if (n->key > m->key)
       n->leftchild = insertion(n->leftchild, m);
    else
       n->rightchild = insertion(n->rightchild, m);
    return n;
}

node *intersection(node *n, node *m, node *b)
{
    if(n == NULL || m == NULL) 
		return b;
    if(n->key == m->key) {
    	node *j = createNode1(n->key, n->value);
        b = insertTreapNode(b, j);
        //printTree(b);
    	b = intersection(n->leftchild, m->leftchild, b);
    	b = intersection(n->rightchild, m->rightchild, b);
    }
    else if(n->key > m->key) {
    	b = intersection(n, m->rightchild, b);
    	b = intersection(n->leftchild, m, b);
    }
    else  {
    	b = intersection(n->rightchild, m, b);
    	b = intersection(n, m->leftchild, b);
    }
    return b;
}

void printTree(node *n)
{
    static int i = 0, j;
    for (j = 0; j < i; j++)
        printf("   ");
    if (n == NULL)
        printf("-\n");
    else
    {
        i++;
        printf("%c\n", n->key);
        printTree(n->leftchild);
        printTree(n->rightchild);
        i--;
    }
}

void printNode(node *n)
{
    printf("key: %c\nvalue: %d\nleftchild: %s\nrightchild: %s\n",
           n->key, n->value, n->leftchild, n->rightchild);
}
