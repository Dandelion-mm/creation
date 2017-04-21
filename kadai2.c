/**
 *
 * kadai2.c
 *
 * Created on : 2017/04/21
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
  double x;      //x座標
  double y;      //y座標
  int weight;    //その点が持つ重み
  int pPoint;    //この点の前の点情報
  int name;      //配列の名前（番号）
} Point;

/**
 * ２点間の距離を求める関数
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
  
  printf("\n整数の個数を入力してください : ");
  scanf("%d",&n);
  
  /** 乱数を発生させ、座標上の位置を決める */
  int i, j, k;            //for文用の変数
  int dp = n-1;     //目的地
  Point p[n];        //Point型の配列p
  
  srand(time(NULL));
  
  for(i=0; i<n; i++){
    p[i].x = (double)rand() / RAND_MAX;
    p[i].y = (double)rand() / RAND_MAX;
    p[i].weight = 0;    //全地点の重さの初期値は0
    p[i].name = i;
  }
  
  /**
   * 図を作成するために
   * 乱数を別ファイルに保存しておく
   */
  FILE *file;
  file = fopen("point.txt","w");
  for(i=0; i<n; i++){
    fprintf(file,"%f %f\n",p[i].x,p[i].y);
  }
  fclose(file);
  
  /** rの距離の設定 */
  double r = 0;
  
  do{
    printf("\nrを設定してください(0<r<1) : ");
    scanf("%lf", &r);
    if(r <= 0 || 1 <= r){
      printf("\n適切な値を入力してください\n");
    }
  }while (r <= 0 || 1 <= r);
  
  /** A、Bを設定する  */
  printf("\n**************************************************\n");
  printf("ある２点（Ａ、Ｂ）を発生させた乱数の中から決めます\n");
  printf("A = (%f,%f) とします\n", p[0].x, p[0].y);
  printf("B = (%f,%f) とします\n", p[dp].x, p[dp].y);
  printf("**************************************************\n\n");
  
  /** 
   * Aからの距離をそれぞれ求める
   * 距離がr以下の点に重み１を足す
   */
  double dist = 0;    //２点間の距離を格納する変数
  
  for(i=1; i<n; i++){
    dist = getDistance(p[0].x, p[0].y, p[i].x, p[i].y);
    if(dist <= r){
      p[i].weight = 1;    //重みに１を足す
      p[i].pPoint = 0;    //前の点はスタートであるＡ(0)
    }
  }
  
  /**
   * ダイクストラ法を用い、
   * 重みが１の点から、他の点への距離を測り
   * 距離r以下の点を探していく
   * Bに重みがついた時点で、最短経路が確定する
   */
  
  for(i=1; i<n; i++){
    for(j=1; j<n-1; j++){
      //重みが１の点から検索する
      if(p[j].weight == i){
	for(k=2; k<n; k++){
	  dist = getDistance(p[j].x, p[j].y, p[k].x, p[k].y);
	  if(dist <= r && dist != 0){
	    if(p[k].weight == 0 || p[j].weight + 1 < p[k].weight){
	      p[k].weight = p[j].weight + 1;
	      p[k].pPoint = j;
	    }
	  }
	  if(p[dp].weight > 0){
	    break;
	  }
	}
      }
      if(p[dp].weight > 0){
	break;
      }
    }
    if(p[dp].weight > 0){
      break;
    }
  }
    
    /** 出力メソッド */
  if(p[dp].weight != 0){
    printf("AからBへの最短経路は\n\n");
    printf("B(%f,%f)\n", p[dp].x ,p[dp].y);
    printf(" <-- ");
    
    j = p[dp].pPoint;    //目的地の一個前の点情報を代入
    for(i=0; i<p[dp].weight - 1; i++){
      printf(" (%f,%f)\n", p[j].x ,p[j].y);
      j = p[j].pPoint;
      printf(" <-- ");
    }
    printf("A(%f,%f)\n\n", p[0].x ,p[0].y);
  }else{
    printf("AとBはつながりませんでした\n\n");
  }
}
