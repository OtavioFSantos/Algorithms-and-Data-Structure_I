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
void cleanNode(struct Node *node);
void cleanTree(struct Node *root);
void secondScenario();

struct Node{
  int key; //aka value
  struct Node *nodeLeft; //self explanatory
  struct Node *nodeRight;
  int height;
};


int main(){
  struct Node *root = NULL; //initialize the root on null, otherwise there will be some errors on valgrind
  int amount, number;

  printf("\n> Enter the amount of nodes you want to insert: "); scanf("%d", &amount);

  srand(time(0));
  for(int i = 0; i < amount; i++){ //generates random nodes
    number = rand() % 100; //generates a random number
    root = add(root, number); //insert the random number
  }
  printf("\n\n");
  showTree(root); //prints the whole tree
  printf("\n");

  if(verify(root) == 0){ //tests the tree
    printf("Not ");
  }
  printf("OK\n\n");

  cleanTree(root); //clean the whole tree
  secondScenario(); //activates second scenario

  return 0;
}


struct Node *add(struct Node *node, int number){
  int fb; //balance factor

  if(node == NULL){ //simply return a node if it is the first one (root) or some leaf
    return newNode(number);
  }

  if(number < node->key){ //insert the new node on the left
    node->nodeLeft = add(node->nodeLeft, number);
  }else{ //or on the right
    node->nodeRight = add(node->nodeRight, number);
  }

  node->height = 1 + maximum(height(node->nodeLeft), height(node->nodeRight)); //determinates the height of the new node
  
  fb = getFB(node); //get the balance factor of the node

  if(fb > 1 && number < node->nodeLeft->key){ //right rotate
    return rightRotate(node);
  }
  if(fb < -1 && number > node->nodeRight->key){ //left rotate
    return leftRotate(node);
  }
  if(fb > 1 && number > node->nodeLeft->key){ //double right rotate
    node->nodeLeft = leftRotate(node->nodeLeft); //1 = 2
    return rightRotate(node);
  }
  if(fb < -1 && number < node->nodeRight->key){ //double left rotate
    node->nodeRight = rightRotate(node->nodeRight);
    return leftRotate(node);
  }

  return node;
}


struct Node *rightRotate(struct Node *node){ //if theres this situation: (3(2(1))))
  struct Node *auxLeft = node->nodeLeft; //then auxLeft = 2
  struct Node *auxRight = auxLeft->nodeRight; //and auxRight = NULL

  auxLeft->nodeRight = node; //2->nodeRight = 3
  node->nodeLeft = auxRight; //3->nodeLeft = NULL

  //and now is (2(1)(3))

  node->height = maximum(height(node->nodeLeft), height(node->nodeRight)) + 1; //update the height of the 3
  auxLeft->height = maximum(height(auxLeft->nodeLeft), height(auxLeft->nodeRight)) + 1; //update the height of the 2

  return auxLeft; //return the 2
}


struct Node *leftRotate(struct Node *node){ //if theres this situation: (3(1(2))) node is 1
  struct Node *auxRight = node->nodeRight; //then auxRight = 2
  struct Node *auxLeft = auxRight->nodeLeft; //and auxLeft = NULL

  auxRight->nodeLeft = node; //2->nodeLeft = 1
  node->nodeRight = auxLeft; //1->nodeRight = NULL

  //and now is (3(2(1)))

  node->height = maximum(height(node->nodeLeft), height(node->nodeRight)) + 1; //update the height of the 1
  auxRight->height = maximum(height(auxRight->nodeLeft), height(auxRight->nodeRight)) + 1; //update the height of the 2

  return auxRight; //return the 2
}


int verify(struct Node *node){
  int fb;

  if(node == NULL){ //if the tree is empty, or is a leaf, then theres nothing wrong
    return 1;
    }	
  if(!verify(node->nodeLeft)){ //check the left node
    return 0;
  }
  if(!verify(node->nodeRight)){ //check the right node
    return 0;
  }
  fb = getFB(node);
  if((fb > 1) || (fb < -1)){ //check if it is balanced
    return 0;
  }else{
    return 1;
  } 
}


int height(struct Node *node){ //simply return the height of the node
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
  return (height(node->nodeLeft) - height(node->nodeRight)); //return height of left node - height of right node
}


struct Node *newNode(int key){
  struct Node *node = (struct Node *)calloc(1, sizeof(struct Node)); //allocate the new node

  node->key = key; 
  node->nodeLeft = NULL;
  node->nodeRight = NULL;
  node->height = 1;
  return node;
}


void showTree(struct Node *node){ //simply shows the tree
    if(node != NULL){
        printf("(%d", node->key);
        showTree(node->nodeLeft);
        showTree(node->nodeRight);
        printf(")");
    }
}


void cleanNode(struct Node *node){
  if(node != NULL){
    cleanNode(node->nodeLeft);
    cleanNode(node->nodeRight);
    free(node); //cleans the nodes before cleaning itself
  }
}

void cleanTree(struct Node *root){ 
  if(root != NULL){
    cleanNode(root); //clean root
  }    
}


void secondScenario(){
  printf("First case:\n");
  struct Node *root1 = NULL; 

  root1 = add(root1, 20);
  root1 = add(root1, 4);
  root1 = add(root1, 15);
  showTree(root1);
  cleanTree(root1);
  
  printf("\nSecond case:\n");
  struct Node *root2 = NULL;
  
  root2 = add(root2, 20);
  root2 = add(root2, 4);
  root2 = add(root2, 26);
  root2 = add(root2, 3);
  root2 = add(root2, 9);
  root2 = add(root2, 15);
  showTree(root2);
  cleanTree(root2);

  printf("\nThird case:\n");
  struct Node *root3 = NULL;

  root3 = add(root3, 20);
  root3 = add(root3, 4);
  root3 = add(root3, 26);
  root3 = add(root3, 3);
  root3 = add(root3, 9);
  root3 = add(root3, 21);
  root3 = add(root3, 30);
  root3 = add(root3, 2);
  root3 = add(root3, 7);
  root3 = add(root3, 11);
  root3 = add(root3, 15);
  showTree(root3);
  cleanTree(root3);

  printf("\n\n");
}
