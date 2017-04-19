/**
 *
 * kadai2.c
 *
 * Created on : 2017/04/17
 *     Author : murota
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/**
 *型の定義
 *点をPointとして定義する
 */
typedef struct{
  double x, y;
  int w;
} Point;

/**
 * ２点間の距離を求める
 * @param px １つ目の点のx座標
 * @param py １つ目の点のy座標
 * @param qx ２つ目の点のx座標
 * @param qy ２つ目の点のy座標
 * @return ２点間の距離
 */
double getDistance(double px, double py, double qx, double qy) {
  double distance = sqrt((qx - px) * (qx - px) + (qy - py) * (qy - py));
  return distance;
}

/**
 * Mainの実行
 */
int main(void){

  /** 整数の数nを決める */
  int n = 0;

  printf("整数の個数を入力してください\n");
  scanf("%d",&n);

  /** 乱数を発生させ、座標上の位置を決める */
  int i;
  Point p[n];

  srand(time(NULL));

  for(i=0; i<n; i++){
    p[i].x = (double)rand() / RAND_MAX;
    p[i].y = (double)rand() / RAND_MAX;
    p[i].w = 0;
  }

  /** rの距離の設定 */
  double r = 0;

  do{
    printf("rを設定してください(0<r<1)\n");
    scanf("%lf", &r);
    if(r <= 0 || 1 <= r){
      printf("適切な値を入力してください\n");
    }
  }while (r <= 0 || 1 <= r);
  
  /** A、Bを設定する  */
  printf("ある２点（A、B）を発生させた乱数の中から決めます\n");
  printf("A = (%f,%f) とします\n", p[0].x, p[0].y);
  printf("B = (%f,%f) とします\n", p[n-1].x, p[n-1].y);

  /** Aからの距離をそれぞれ求める */
  double tmp = 0;
    
  for(i=1; i<n; i++){
    tmp = getDistance(p[0].x, p[0].y, p[i].x, p[i].y);
      if(tmp <= r){
	p[i].w = 1;
      }
  }
  
  for(i=1; i<n; i++){
    tmp = getDistance(p[0].x, p[0].y, p[i].x, p[i].y);
    if(p[i].w == 1 && tmp <= r)
  }
  
}