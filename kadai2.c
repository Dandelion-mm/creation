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
  int w, a;
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
  
  printf("\n整数の個数を入力してください ---> ");
  scanf("%d",&n);
  
  /** 乱数を発生させ、座標上の位置を決める */
  int i, j, k;
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
    printf("\nrを設定してください(0<r<1) ---> ");
    scanf("%lf", &r);
    if(r <= 0 || 1 <= r){
      printf("\n適切な値を入力してください\n");
    }
  }while (r <= 0 || 1 <= r);
  
  /** A、Bを設定する  */
  printf("\n**************************************************\n");
  printf("ある２点（Ａ、Ｂ）を発生させた乱数の中から決めます\n");
  printf("A = (%f,%f) とします\n", p[0].x, p[0].y);
  printf("B = (%f,%f) とします\n", p[n-1].x, p[n-1].y);
  printf("**************************************************\n\n");

  /** 
   * Aからの距離をそれぞれ求める
   * 距離がr以下の店に重み１を足す
   */
  double dist = 0;
    
  for(i=1; i<n; i++){
    dist = getDistance(p[0].x, p[0].y, p[i].x, p[i].y);
      if(dist <= r){
	p[i].w = 1;
	p[i].a = 0;
	printf("%dの前は%d\n", i , p[i].a);
      }
      // printf("(%f,%f) --> %d\n", p[i].x, p[i].y,  p[i].w);
  }

  printf("-----\n");
  
  /**
   *重みが１の点から、順々に距離を測り距離r以下の点を探す
   */

  for(i=1; i<n; i++){
    for(j=1; j<n-1; j++){
      //重みが１の点から検索をする
      if(p[j].w == i){
	for(k=2; k<n; k++){
	  dist = getDistance(p[j].x, p[j].y, p[k].x, p[k].y);
	  if(dist <= r || dist != 0){
	    if(p[k].w == 0 || p[j].w + 1 < p[k].w){
	      p[k].w = p[j].w + 1;
	      p[k].a = j;
	      printf("%dの前は%d\n", k , p[k].a);
	    }
	  }
	  if(p[n-1].w > 0){
	    break;
	  }
	}
      }
      if(p[n-1].w > 0){
	break;
      }
    }
    if(p[n-1].w > 0){
      break;
    }
  }

  printf("点Bの重さは%d\n",p[n-1].w);
  //出力お試
  /*for(i=n-1; 0<i; i--){
    printf("%d\n",p[i].a);
    printf("-----\n");
    }*/


  
}
