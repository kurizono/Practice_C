#include <stdio.h>
#include <string.h>
//mallocで動的にメモリを確保するため
#include <stdlib.h>

//登場人物の名前入力
char** ques_name(int num){
  char **name;
  name = malloc(sizeof(char*)*num);
  for(int i = 0; i < num; i++){
    name[i] = malloc(sizeof(char)*10);
  }  
  for(int i = 0; i < num; i++){
    printf("%d人目の名前を入力してください\n", i + 1);
    scanf("%s", name[i]);
    //printf("%s\n", name[i]);
  }
  return name;
}

int main(void){
  
  //人の名前をnameに保存する(namenum個の文字列をm回分)
  char **name;
  int num;
  printf("何人入力しますか？\n");
  scanf("%d",&num);
  name = ques_name(num);
  
  //printf("%d人入力\n", num);
  
  //blood[n][0][0]が夫婦、blood[n][1][m]が子ども
  //現段階では同じ名前の人物を複数回入力しても通ってしまう
  int ***blood;
  blood = malloc(sizeof(int**)*num);
  for(int i = 0; i < num; i++){
    blood[i] = malloc(sizeof(int*)*2);
  }
  
  
  printf("0までクリア\n");
  
  //夫婦関係の人がいればblood[n][0][0]に入力
  for(int i = 0; i < num; i++){
    char *marry = malloc(sizeof(char)*10);
    while(1){
      printf("%sと夫婦関係の人はいますか？(Yes/No)\n", name[i]);
      scanf("%s",marry);
      if(!strcmp(marry,"Yes")){
        int judge = 0;
        while(judge == 0){
          printf("%sと夫婦関係の人は誰ですか？\n", name[i]);
          scanf("%s",marry);
          //現段階では、同じ人を夫婦関係としても成立する(＊)
	  for(int j = 0; j < num; j++){
            if(!strcmp(marry,name[j])){
                printf("成功\n");
		blood[i][0] = malloc(sizeof(int)*1);
		blood[i][0][0] = j;
                judge = 1;
                break;
            }
          }
	  if(judge == 0){
	  printf("入力した人の名前を入力してください\n");
          }
	} 
        break;  
      }
      else if(!strcmp(marry,"No")){
        break;
      }
      else{
          printf("Yes/Noで答えてください\n");
      }
    }
  }
  printf("1までクリア\n");
 
  //親子関係の人がいればblood[n][1][n]に入力
  for(int i = 0; i < num; i++){
    char *parent = malloc(sizeof(char)*10);
    int parentnum;
    //現段階では親子関係の人が入力した人数以上でも通ってしまう(*)
    //現段階では数字がマイナスでも通ってしまう
    printf("%sと親子関係の人は何人いますか？(数字で)\n", name[i]);
    scanf("%d",&parentnum);
    blood[i][1] = malloc(sizeof(int)*parentnum);
    //現段階では自分自身を親子関係としても通ってしまう(*)
    //現段階では同一人物を複数回親子関係としても通ってしまう(*)
    for(int j = 0; j < parentnum; j++){
      printf("%sと親子関係の%d人目を答えてください\n", name[i],j+1);
      //break文で特定のwhile文から脱出する方法を知りたい(！)
      int judge = 0;
      while(judge == 0){
        scanf("%s", parent);
	for(int k = 0; k < num; k++){
	  if(!strcmp(name[k],parent)){
	    blood[i][1][j] = k;
	    judge = 1;
	  }
	}
	if(judge == 0){
	  printf("入力した人の名前を入力してください\n");
	}
      }
    }
  }
  printf("2までクリア\n");

  //テスト
  //bloodの値を全て並べてみる
  //失敗例　printf("blood[0][1]の要素数は %d\n", sizeof(blood[0][1])/sizeof(int));

  //解決したいこと、配列内の要素数の計算(この後要素数だけforで繰り返すのに使いたい)
  //解決策1：配列内の要素数を定義するときにintで記憶する(もっとスマートな方法あり？)
  //解決策2：配列の最後に-1を入れて、それが出るまで繰り返す(ネットでの検索)

  //この後したいこと
  
  //親等数を求めたい二人の名前を入力
  //while文でずっと繰り返し
  //  先に入力した名前の人物の親等数nの人物を全て求める
  //  (求める方法として、親等数n-1の人のblood[0][1]の人を全て羅列)
  //  (親等数n-1のblood[0][0]の人を全て羅列)
  //  親等数nとして求めた人の内、被りを全て排除する
  //  親等数nとして求めた人の内、親等数n未満の人を排除する
  //　親等数nとして求めた人の内、後に入力した名前の人物がいればbreak
  //親等数nを出力
  //
  
  return 0;
}
