#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

typedef struct Node
{
    int key;
    int value;
    struct Node *leftchild, *rightchild;
} node;

typedef struct Queue
{
    node *content;
    struct Queue *next;
} queue;

void swap(node **n, node **m);
void insertInQueue(node *x, queue *h);
node *removeOfQueue(queue *h);
void queueEmpty(queue *x);
void condition(node *j, queue *h);
node *insertTreapNode(node *n, node *m);
node *createNode();
node *createNode1(char n, int m);
node *leftRotate(node *n);
node *rightRotate(node *n);
void printTree(node *n);
void printNode(node *n);
node *insertion(node *n, node *m);
//void *unionTree(node *n, node *m, node *b);
node *intersection(node *n, node *m, node *b);
node *difference(node *n, node *m, node *b);
node *union_(node *n, node *m, node *r);

//Testing module
int main(int argc, char **argv)
{
    time_t t;
    srand((unsigned)time(&t));

    node *root = NULL;
    //node *n = createNode();
    node *n = createNode1('f', 10);
    // node *m = createNode();
    node *m = createNode1('h', 20);
    node *j = createNode1('q', 81);
    // node *j = createNode();
    // node *l = createNode();
    root = insertTreapNode(root, n);
    root = insertTreapNode(root, m);
    root = insertTreapNode(root, j);
    //root = insertTreapNode(root, l);
    printTree(root);
    printf("\n");

    node *root2 = NULL;
    //node *n2 = createNode();
    node *n2 = createNode1('d', 50);
    //node *m2 = createNode();
    node *m2 = createNode1('f', 89);
    node *j2 = createNode1('q', 80);
    //node *j2 = createNode();
    // node *l2 = createNode();
    root2 = insertTreapNode(root2, n2);
    root2 = insertTreapNode(root2, m2);
    root2 = insertTreapNode(root2, j2);
    //root2 = insertTreapNode(root2, l2);
    printTree(root2);
    printf("\n");

    node *root3 = NULL;
    //root3 = intersection(root, root2, root3);
    root3 = union_(root, root2, root3);
    printTree(root3);
    free(root);
    free(root2);
    free(root3);

    return 0;
}

void swap(node **n, node **m)
{
    node *aux = (node *)malloc(sizeof(node));

    aux = *m;
    *m = *n;
    *n = aux;
}

void insertInQueue(node *x, queue *h)
{
    queue *p;
    p = (queue *)malloc(sizeof(queue));
    p->content = x;
    p->next = NULL;
    while (h->next != NULL)
        h = h->next;
    h->next = p;
}

node *removeOfQueue(queue *h)
{
    queue *aux;
    aux = h->next;
    h->next = aux->next;
    aux->next = NULL;
    return aux->content;
}

void queueEmpty(queue *x)
{
    queue *j;
    j = (queue *)malloc(sizeof(queue));
    j->next = NULL;
    x = j;
}

void condition(node *j, queue *h)
{
    if (j->rightchild == NULL && j->leftchild != NULL)
        insertInQueue(j->leftchild, h);
    if (j->leftchild == NULL && j->rightchild != NULL)
        insertInQueue(j->rightchild, h);
    if (j->leftchild != NULL && j->rightchild != NULL)
    {
        insertInQueue(j->leftchild, h);
        insertInQueue(j->rightchild, h);
    }
}

node *difference(node *n, node *m, node *b)
{
    queue *a1, *a2;
    node *aux;
    a1 = (queue *)malloc(sizeof(queue));
    a1->next = NULL;
    a2 = (queue *)malloc(sizeof(queue));
    a2->next = NULL;
    insertInQueue(n, a1);
    while (1)
    {
        if (a1->next == NULL)
            break;
        aux = removeOfQueue(a1);
        condition(aux, a1);
        insertInQueue(m, a2);
        while (1)
        {
            node *aux2;
            aux2 = removeOfQueue(a2);
            condition(aux2, a2);
            if (aux->key == aux2->key)
                break;
            if (a2->next == NULL)
            {
                node *x = createNode1(aux->key, aux->value);
                b = insertTreapNode(b, x);
                break;
            }
        }
    }
    queueEmpty(a1);
    queueEmpty(a2);
    insertInQueue(m, a2);
    while (1)
    {
        if (a2->next == NULL)
            break;
        aux = removeOfQueue(a2);
        condition(aux, a2);
        insertInQueue(n, a1);
        while (1)
        {
            node *aux2;
            aux2 = removeOfQueue(a1);
            condition(aux2, a1);
            if (aux->key == aux2->key)
                break;
            if (a1->next == NULL)
            {
                node *x = createNode1(aux->key, aux->value);
                b = insertTreapNode(b, x);
                break;
            }
        }
    }
    return b;
}

node *union_(node *n, node *m, node *r)
{
    node *k;
    node *aux;
    if (n == NULL)
        return m;
    if (m == NULL)
        return n;
    if (n->value < m->value)
    {
        swap(&n, &m);
    }

    if (m->key != n->key)
    {

        k = createNode1(n->key, n->value);

        aux = insertTreapNode(m, k);
    }
    else
    {

        aux = m;
    }

    r = createNode1(n->key, n->value);
    r->leftchild = union_(n->leftchild, aux->leftchild, r);
    r->rightchild = union_(n->rightchild, aux->rightchild, r);

    return r;
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
    if (n == NULL)
        return m;
    if (n->key > m->key)
        n->leftchild = insertion(n->leftchild, m);
    else
        n->rightchild = insertion(n->rightchild, m);
    return n;
}

node *intersection(node *n, node *m, node *b)
{
    if (n == NULL || m == NULL)
        return b;
    if (n->key == m->key)
    {
        node *j = createNode1(n->key, n->value);
        b = insertTreapNode(b, j);
        //printTree(b);
        b = intersection(n->leftchild, m->leftchild, b);
        b = intersection(n->rightchild, m->rightchild, b);
    }
    else if (n->key > m->key)
    {
        b = intersection(n, m->rightchild, b);
        b = intersection(n->leftchild, m, b);
    }
    else
    {
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
        printf("%c\n", (char)n->key);
        printTree(n->leftchild);
        printTree(n->rightchild);
        i--;
    }
}

void printNode(node *n)
{
    printf("key: %d\nvalue: %d\nleftchild: %p\nrightchild: %p\n",
           (char)n->key, n->value, n->leftchild, n->rightchild);
}
