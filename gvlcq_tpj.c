#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  int chav;
  struct no *left;
  struct no *right;
  int left_child;
  int right_child;
  int altura;
} no;

int max (int a, int b) {
  if(a > b){
    return a;
  }else{
    return b;
  } 
}

int altura (no *raiz) {
  if(raiz == NULL){
  return 0; 
  }else{
    return raiz -> altura;
  } 
}

no *novo_no (int chav, int left_child, int right_child, int raiz){
  no *tmp_no = malloc(sizeof(no) );
  if (!tmp_no){
    printf("Allocation Fail, not enought memory!\n");
    return 0;
  }
  else{
    tmp_no -> chav = chav;
    tmp_no -> left = NULL;
    tmp_no -> right = NULL;
    tmp_no -> altura = 1; //lembrar cuidado c a alltura
    tmp_no -> right_child = right_child;
    tmp_no -> left_child = left_child;
    return tmp_no;
  }
}

int get_balance_factor (no *raiz) {
  if (raiz == NULL) return 0;
  else return altura(raiz -> left) - altura(raiz -> right);
}

no *right_rotate (no *y) {
  no *x = y -> left;
  no *z = x -> right;

  x -> right = y;
  y -> left = z;

  y -> altura = max( altura(y -> left), altura(y -> right) ) + 1;
  x -> altura = max( altura(x -> left), altura(x -> right) ) + 1;
  
  if (z != NULL) y -> left_child = z -> left_child + z -> right_child + 1; else y -> left_child = 0;
  x -> right_child = y -> left_child + y -> right_child + 1;

  return x;
}

no *left_rotate (no *x) {
  no *y = x -> right;
  no *z = y -> left;

  y -> left = x;
  x -> right = z;

  x -> altura = max( altura(x -> left), altura(x -> right) ) + 1;
  y -> altura = max( altura(y -> left), altura(y -> right) ) + 1;

  if (z != NULL) x -> right_child = z -> left_child + z -> right_child + 1; else x -> right_child = 0;
  y -> left_child = x -> left_child + x -> right_child + 1;
  
}

no *insert(no *raiz, int chav) {
  if (raiz == NULL) return novo_no(chav, 0, 0);
  if (chav < raiz -> chav) {
    raiz -> left = insert(raiz -> left, chav);
    raiz -> left_child++;
  }
  else if (chav > raiz -> chav) {
    raiz -> right = insert(raiz -> right, chav);
    raiz -> right_child++;
  }
  else return raiz;

  raiz -> altura = max( altura(raiz -> left), altura(raiz -> right) ) + 1;

  int balance = get_balance_factor(raiz);

  if ( (balance > 1) && (chav < raiz -> left -> chav) ) return right_rotate(raiz);

  if ( (balance < -1) && (chav > raiz -> right -> chav) ) return left_rotate(raiz);

  if ( (balance > 1) && (chav > raiz -> left -> chav) ) {
    raiz -> left = left_rotate(raiz -> left);
    return right_rotate(raiz);
  }

  if ( (balance < -1) && (chav < raiz -> right -> chav) ) {
    raiz -> right = right_rotate(raiz -> right);
    return left_rotate(raiz);
  }

  return raiz;
}

void ordem (no *raiz) {
  if (raiz != NULL) {
    printf("%d %d %d\n", raiz -> chav, raiz -> left_child, raiz -> right_child);
    ordem(raiz -> left);
    ordem(raiz -> right);
  }
}
