#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


struct node {
    int data;
    struct node* small;
    struct node* large;
};

typedef struct node* Node;





/* Create a new node */
Node newNode(int data) {
    Node node = (Node) malloc(sizeof(struct node));
    node->data = data;
    node->small = NULL;
    node->large = NULL;
    return(node);
}


/* Add a new node into a tree */
void treeInsert(Node* rootRef, int data) {
    Node root = *rootRef;
    if (root == NULL) *rootRef = newNode(data);
    else {
        if (data <= root->data) treeInsert(&(root->small), data);
        else treeInsert(&(root->large), data);
    }
}


void printList(Node head) {
    Node current = head;
    
    while(current != NULL) {
        printf("%d ", current->data);
        current = current->large;
        if (current == head) break;
    }
    printf("\n");
}

// YOUR CODE HERE
Node connect(Node a, Node b) {
    if (a == NULL) {
        return b;
    }
    if (b == NULL) {
        return a;
    }
    
    Node aLast = a->small;
    Node bLast = b->small;
    
    aLast->large = b;
    b->small = aLast;
    a->small = bLast;
    bLast->large = a;
    
    return a;
}

Node treeToList(Node root) {
    if (root == NULL) {
        return NULL;
    }
    
    Node leftList = treeToList(root->small);
    Node rightList = treeToList(root->large);
    
    root->small = root;
    root->large = root;
    
    return connect(connect(leftList, root), rightList);
}

/* Demo that the code works */
int main() {
    Node root = NULL;
    Node head;
    
    treeInsert(&root, 4);
    treeInsert(&root, 2);
    treeInsert(&root, 1);
    treeInsert(&root, 3);
    treeInsert(&root, 5);
    
    head = treeToList(root);
    
    printList(head);    /* prints: 1 2 3 4 5  */
}