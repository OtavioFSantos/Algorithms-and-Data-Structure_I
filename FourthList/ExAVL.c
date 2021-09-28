#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node *add(struct Node *node, int number);
struct Node *rightRotate(struct Node *node);
struct Node *leftRotate(struct Node *node);
struct Node *newNode(int key);
void showTree(struct Node *node);
int maximum(int a, int b);
int height(struct Node *node);
int getFB(struct Node *node);
int verify(struct Node *node);
void secondScenario();

struct Node{
    int key;
    struct Node *nodeLeft;
    struct Node *nodeRight;
    int height;
};


int main(){
    struct Node *root = NULL;
    int amount, number;

    printf("\n> Enter the amount of nodes you want to insert: "); scanf("%d", &amount);
	
    srand(time(0));
    for(int i = 0; i < amount; i++){ //generates random nodes
		number = rand() % 100;
		root = add(root, number);
    }
    printf("\n\n");
    showTree(root); //prints the whole tree
    printf("\n");

    if(verify(root) == 0){
        printf("Not ");
    }
    printf("OK\n\n");

    secondScenario();

    return 0;
}


struct Node *add(struct Node *node, int number){
    int fb;

    if(node == NULL){ //simply return a node if it is the first one (root)
        return newNode(number);
    }

    if(number < node->key){ //insert the new node on the left
        node->nodeLeft = add(node->nodeLeft, number);
    }else{ //or on the right
        node->nodeRight = add(node->nodeRight, number);
    }

    node->height = 1 + maximum(height(node->nodeLeft), height(node->nodeRight)); //determinates the height of the new node
    
    fb = getFB(node); //get the balance factor

    if(fb > 1 && number < node->nodeLeft->key){ //right rotate
        return rightRotate(node);
    }
    if(fb < -1 && number > node->nodeRight->key){ //left rotate
        return leftRotate(node);
    }
    if(fb > 1 && number > node->nodeLeft->key){ //double right rotate
        node->nodeLeft = leftRotate(node->nodeLeft); 
        return rightRotate(node);
    }
    if(fb < -1 && number < node->nodeRight->key){ //double left rotate
        node->nodeRight = rightRotate(node->nodeRight);
        return leftRotate(node);
    }

    return node;
}


struct Node *rightRotate(struct Node *node){
    struct Node *auxLeft = node->nodeLeft;
    struct Node *auxRight = auxLeft->nodeRight;

    auxLeft->nodeRight = node;
    node->nodeLeft = auxRight;

    node->height = maximum(height(node->nodeLeft), height(node->nodeRight)) + 1;
    auxLeft->height = maximum(height(auxLeft->nodeLeft), height(auxLeft->nodeRight)) + 1;

    return auxLeft;
}


struct Node *leftRotate(struct Node *node){
    struct Node *auxRight = node->nodeRight;
    struct Node *auxLeft = auxRight->nodeLeft;

    auxRight->nodeLeft = node;
    node->nodeRight = auxLeft;

    node->height = maximum(height(node->nodeLeft), height(node->nodeRight)) + 1;
    auxRight->height = maximum(height(auxRight->nodeLeft), height(auxRight->nodeRight)) + 1;

    return auxRight;
}


int verify(struct Node *node){
    int fb;

	if(node == NULL){
		return 1;
    }	
	if(!verify(node->nodeLeft)){
		return 0;
    }
	if(!verify(node->nodeRight)){
		return 0;
    }
	fb = getFB(node);
	if((fb > 1) || (fb < -1)){
		return 0;
    }else{
		return 1;
    } 
}


int height(struct Node *node){
    if(node == NULL){
        return 0;
    }
    return node->height;
}


int maximum(int a, int b){
    return (a > b) ? a : b; //if a is greater than b, returns a. Otherwise, returns b
}


int getFB(struct Node *node){
    if (node == NULL){
        return 0;
    }
    return (height(node->nodeLeft) - height(node->nodeRight));
}


struct Node *newNode(int key){
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));

    node->key = key; 
    node->nodeLeft = NULL;
    node->nodeRight = NULL;
    node->height = 1;
    return node;
}


void showTree(struct Node *node){
    if(node != NULL){
        printf("(%d", node->key);
        showTree(node->nodeLeft);
        showTree(node->nodeRight);
        printf(")");
    }
}


void secondScenario(){
    struct Node *root = NULL;

    printf("First case:\n");
    root = add(root, 20);
    root = add(root, 4);
    root = add(root, 15);
    showTree(root);

    printf("\nSecond case:\n");
    root = NULL;
    root = add(root, 20);
    root = add(root, 4);
    root = add(root, 26);
    root = add(root, 3);
    root = add(root, 9);
    root = add(root, 15);
    showTree(root);

    printf("\nThird case:\n");
    root = NULL;
    root = add(root, 20);
    root = add(root, 4);
    root = add(root, 26);
    root = add(root, 3);
    root = add(root, 9);
    root = add(root, 21);
    root = add(root, 30);
    root = add(root, 2);
    root = add(root, 7);
    root = add(root, 11);
    root = add(root, 15);
    showTree(root);

    printf("\n\n");
}
