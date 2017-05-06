/**
 *
 * kadai3.c
 *
 * Created on : 2017/05/06
 *        Author : murota
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/** グローバル変数 */
int n = 0;    //点の個数

/**
 * 型の定義
 * 点をPointとして定義する
 */
typedef struct{
  int name;            //配列の名前(番号)
  double sx;          //移動前のx座標
  double sy;          //移動前のy座標
  double mx;         //移動中のx座標
  double my;         //移動中のy座標
  double dx;          //目的地のx座標
  double dy;          //目的地のy座標
  double speed;    //移動速度
  double cos;        //目的地と移動前との正弦
  double sin;         //目的地と移動前との余弦
  int weight;          //その点が持つ重み
  int pPoint;          //この点の前の点情報
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
 * A,Bの値を出力する関数
 * @param ax Aのx座標
 * @param ay Aのy座標
 * @param bx Bのx座標
 * @param by Bのy座標
 */
void PrintAandB(double ax, double ay, double bx, double by){
  printf("\n**************************************************\n");
  printf("ある2点(A,B)を発生させた乱数の中から決めます\n");
  printf("A = (%f,%f) とします\n", ax, ay);
  printf("B = (%f,%f) とします\n", bx, by);
  printf("**************************************************\n\n");
}

/**
 * Main関数
 */
int main(void){
    printf("\n整数の個数を入力してください : ");
    scanf("%d",&n);

    /** 乱数を発生させ、座標上の位置を決める */
    int i, j, k;             //for文用の変数
    int sp = 0;          //点A
    int dp = n - 1;    //点B
    Point p[n];         //Point型の配列P

    srand(time(NULL));

    for(i=0; i<n; i++){
        p[i].sx = (double)rand() / RAND_MAX;
        p[i].sy = (double)rand() / RAND_MAX;
        p[i].weight = 0;    //全地点の重さの初期値は0
        p[i].name = i;
    }

    /** 距離rの設定 */
    double r = 0;

    do{
        printf("\nrを設定してください(0<r<1) : ");
        scanf("%lf", &r);
        if(r <= 0 || 1 <= r){
            printf("\n適切な値を入力してください\n");
        }
    }while(r <= 0 || 1 <= r);

    /** A、Bを設定する  */
    PrintAandB(p[sp].sx, p[sp].sy, p[dp].sx, p[dp].sy);

    /**
     * Aからの距離をそれぞれ求める
     * 距離がr以下の点に重み１を足す
     */
    double dist = 0;    //２点間の距離を格納する変数

	for(i=1; i<n; i++){
	    dist = getDistance(p[0].sx, p[0].sy, p[i].sx, p[i].sy);
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
    double sRoute[][2] = {0};    //最短経路を記憶しておく配列

    for(i=1; i<n; i++){
        for(j=1; j<n-1; j++){
        //重みが１の点から検索する
            if(p[j].weight == i){
	            for(k=2; k<n; k++){
	                dist = getDistance(p[j].sx, p[j].sy, p[k].sx, p[k].sy);
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

    sRoute[0][0] = p[dp].sx;
    sRoute[0][1] = p[dp].sy;
    j = p[dp].pPoint;    //目的地の一個前の点情報を代入
    for(i=1; i<p[dp].weight; i++){
        sRoute[i][0] = p[j].sx;
        sRoute[i][1] = p[j].sy;
        j = p[j].pPoint;
    }

    /** 出力メソッド */
    if(p[dp].weight != 0){
        printf("初めのAからBへの最短経路は\n\n");
        printf("B");

        j = p[dp].pPoint;    //目的地の一個前の点情報を代入
        for(i=0; i<p[dp].weight; i++){
            printf(" (%f,%f)\n", sRoute[i][0], sRoute[i][1]);
            printf(" <-- ");
        }
        printf("A(%f,%f)\n\n", p[0].sx ,p[0].sy);
    }else{
        printf("AとBはつながりませんでした\n\n");
    }

    /** 点の移動を考える */
    double dTime = 0.01;    //微小時間Δt
    double aTime = 0;         //additional Time
    double CP[][2] = {0};      //Change Point

    /** 最初のランダムウェイポイント */
    for(i=0; i<n; i++){
        /** 目的地を決める */
        p[i].dx = (double)rand() / RAND_MAX;
        p[i].dy = (double)rand() / RAND_MAX;
        //printf("%dの目的地 --> (%f,%f)\n", i, p[i].dx, p[i].dy);

        /** 速度を決める */
        p[i].speed = (double)rand() / RAND_MAX;

        /** 2点間の距離を出す */
        dist = getDistance(p[i].sx, p[i].sy, p[i].dx, p[i].dy);

        /** sin,cosを求める */
        p[i].cos = (p[i].dx - p[i].sx) / dist;
        p[i].sin = (p[i].dy - p[i].sy) / dist;
    }

    for(i=0; i<100; i += 0.01){
        for(j=0; j<n; j++){
            /** 移動中の点を出す */
            p[j].mx = p[j].sx + p[j].speed * p[j].cos * dTime;
            p[j].my = p[j].sy + p[j].speed * p[j].sin * dTime;

            /** 到達判定 */
            if(p[j].mx >= p[j].dx){
	            p[j].sx = p[j].dx;
	            p[j].sy = p[j].dx;

                /** dTimeより先に到着した場合の、dTimeまでの残りの時間 */
	            aTime = dTime - getDistance(p[j].sx, p[j].sy, p[j].dx, p[j].dy) / p[j].speed;

	            /** 新たな目的地を決める */
	            p[j].dx = (double)rand() / RAND_MAX;
	            p[j].dy = (double)rand() / RAND_MAX;
	            //printf("%dの目的地 --> (%f,%f)\n", j, p[j].dx, p[j].dy);

	            /** 新たな速度を決める */
	            p[j].speed = (double)rand() / RAND_MAX;

	            /** 2点間の距離を出す */
                dist = getDistance(p[i].sx, p[i].sy, p[i].dx, p[i].dy);

	            /** sin,cosを求める */
	            p[j].cos = (p[j].dx - p[j].sx) / dist;
	            p[j].sin = (p[j].dy - p[j].sy) / dist;

	            p[j].mx = p[j].sx + p[j].speed * p[j].cos * aTime;
	            p[j].my = p[j].sy + p[j].speed * p[j].sin * aTime;
            }
        }

        /** ダイクストラ法を用い、最短経路が変更したかどうかを判断する */


    }

    printf("end\n");


}