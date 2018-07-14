#include "coroutine.h"
#include <stdio.h>
#include <iostream>
using namespace std;

void foo(){
  printf("in co 1\n");
  co_yield();
  printf("in co 2\n");
  co_yield();
}

int main(){
  MCoroutine* co = NULL;
  co_create(&co, &foo);
  printf("in main 0\n");
  co_resume(co);
  printf("in main 1\n");
  co_resume(co);
  printf("in main 2\n");
  return 0;
}
