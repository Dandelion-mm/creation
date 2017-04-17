/**
 *
 * kadai1.c
 *
 * Created on : 2017/04/17
 *     Author : murota
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** 型(Point)の定義 */
typedef struct{
  double x, y;
} Point;


int main(void){

  /** n個の整数の数を決める */
  int n=0;

  printf("整数の個数を入力してください。\n");
  scanf("%d",&n);

  /** 乱数を発生させ、座標上の位置xを決める */
  int i, p[n][n];

  srand(time(NULL));

  for(i=0; i<n; i++){
    Point p = {(double)rand()/RAND_MAX, (double)rand()/RAND_MAX};
    printf("(x,y) = (%f,%f)\n", p.x, p.y);
  }
}
