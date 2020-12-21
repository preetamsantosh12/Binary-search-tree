//BST with all traversals !!!
#include<stdlib.h>
#include<stdio.h>

typedef struct bstnode {
    int dat
    struct bstnode * left ;
    struct bstnode * right;
}bstnode;

typedef struct queue {
    bstnode *queuenode;
    struct queue * ptr;
}queue;

bstnode * root = NULL;
queue *front = NULL , *rear = NULL;
int count = 0;

void push(bstnode * temp) {

    queue * newnode = (queue *) malloc(sizeof(queue));
    newnode->queuenode = temp;
    newnode->ptr = NULL;

    if (front == NULL) {
        front = newnode;
        rear = front;
    }
    else {
        queue * temp = rear;
        rear = newnode;
        temp->ptr = rear;
    }
    count ++;
}

void pop() {

    if (front == rear) {
        free(front);
        free(rear);
        front = NULL;
        rear = NULL;
        count = 0;
    }
    else {
        queue * temp = front;
        front = front->ptr;
        free(temp);
        count --;
    }
}

bstnode * queuefront() {
    return front->queuenode;
}

int queueempty() {
    if (front == NULL)
        return 1;
    else
        return 0;
}

bstnode * createnode(int data) {

    bstnode * newnode = (bstnode*)malloc(sizeof(bstnode));

    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

bstnode * insert (bstnode * temp , int data) {

    if (temp == NULL) 
        temp = createnode(data);
    
    else if (data <= temp->data)
        temp->left = insert(temp->left , data);

    else 
        temp->right = insert(temp->right , data);

    return temp;
}

int search (bstnode * temp , int data) {
    int f;
    if (temp == NULL)
        f = 0;
    else if ( data == temp->data)
        f = 1;
    else if ( data < temp->data)
        f = search(temp->left , data);
    else 
        f = search(temp->right , data);

    return f;
}

bstnode * searchmin(bstnode * temp) {

    while(temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

void preorder(bstnode * temp ) {

    if (temp != NULL) {
        printf("%d  " , temp->data );
        preorder(temp->left);

        preorder(temp->right);
    }
}

void inorder( bstnode * temp ) {
     
     if(temp != NULL) {
         inorder(temp->left);
         printf("%d  " , temp->data);

         inorder(temp->right);
     }
}

void postorder( bstnode * temp ) {

    if(temp != NULL ) {
        postorder(temp->left);
        postorder(temp->right);

        printf("%d  " , temp->data);
    }
}

void levelorder(bstnode * temp) {

    push(temp);

    while(!queueempty()) {
        bstnode * current = queuefront();
        printf("%d " , current->data);

        if(current->left != NULL)
            push(current->left);
        if(current->right != NULL)
            push(current->right);

        pop();
    }
}

void displaytree(bstnode * temp , int i) {

    int j = i;

    if(temp != NULL) {

        displaytree(temp->left ,i+1);
        for(j = i ; j<=i ; j++ )
            printf("\t");

        printf("%d \n" , temp->data);
        displaytree(temp->right ,i+1);
    }
}

bstnode * delete(bstnode * temp , int data) {

    if ( temp == NULL) {
        printf("The Binary Search Tree is empty or the element does not exist.\n");
        return temp;
    }
    else if (data < temp->data)
        temp->left = delete(temp->left , data);
    else if (data > temp->data)
        temp->right = delete(temp->right , data);
    else {
        if(temp->left == NULL && temp->right == NULL) {
            free(temp);
            temp = NULL;
        }
        else if (temp->left == NULL) {
            bstnode * ltd = temp;
            temp = temp->right;
            free(ltd);
        }
        else if (temp->right == NULL) {
            bstnode * ltd = temp;
            temp= temp->left;
            free(ltd);
        }
        else {
            bstnode * ltd = searchmin(temp->right);
            temp->data = ltd->data;
            temp->right = delete(temp->right , ltd->data);
        }
    }
    return temp;
}

void display() {

    if(root == NULL) 
        printf("Binary tree has not been created yet.\n");
    else {
        printf("Enter the type of traversing to be performed.\n");
        int cho;
        printf("1. Normal \t 2. Preorder \t 3. Inorder \t 4.Postorder \t 5.LevelOrder : ");
        scanf("%d" , &cho);

        switch(cho) {

            case 1 : displaytree(root , 1 );
                     break;
                    
            case 2 : printf("Pre-order Traversing : ");
                     preorder(root);
                     printf("\n");
                     break;
            
            case 3 : printf("In-order Traversing : ");
                     inorder(root);
                     printf("\n");
                     break;
        
            case 4 : printf("Post-order traversing : ");
                     postorder(root);
                     printf("\n");
                     break;

            case 6 : printf("Pre-order Traversing    : ");
                     preorder(root);
                     printf("\n");
                     printf("In-order Traversing     : ");
                     inorder(root);
                     printf("\n");
                     printf("Post-order traversing   : ");
                     postorder(root);
                     printf("\n");
                     printf("Level-order traversing  : ");
                     levelorder(root);
                     printf("\n");
                     break;

            case 5 : printf("Level-order traversing : ");
                     levelorder(root);
                     printf("\n");
                     break;

            default : printf("Invalid input.\n");
                      break;
        }
    }
}

void main () {

    int choice ,  flag = 1;
    int bit;
    printf("Enter the operation to be performed.\n");

    while(flag) {
        
        printf("1. Insert \t 2. Display \t 3. Search \t 4. Delete \t 5. Exit : ");
        scanf("%d" , &choice);

        switch(choice) {

            case 1 : printf("Enter the data element : ");
                     scanf("%d" , &bit); 
                     root = insert(root , bit);
                     printf("Element %d successfully inserted.\n" , bit);
                     break;
            
            case 2 : display();
                     break;
            
            case 3 : printf("Enter the search Element : ");
                     scanf("%d" , &bit);
                     int j = search(root , bit);
                     (j == 1)?printf("Element found.\n"):printf("Element doesn't exist.\n");
                     break;
            
            case 4 : printf("Enter the element to be deleted : ");
                     scanf("%d" , &bit);
                     root = delete(root , bit);
                     break;

            case 5 : flag = 0;
                     break;
            
            default : printf("Invalid input.\n");
                      break;

        }
    }
}
