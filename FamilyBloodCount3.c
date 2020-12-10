#include <stdio.h>
#include <string.h>
//mallocで動的にメモリを確保するため
#include <stdlib.h>



//グローバル関数
char** blood_name;
int blood_num;
int **blood;
int *pair_name;


//登場人物の名前入力
char** ques_name(){
  char **name;
  name = malloc(sizeof(char*)*blood_num);
  for(int i = 0; i < blood_num; i++){
    name[i] = malloc(sizeof(char)*10);
  }  
  for(int i = 0; i < blood_num; i++){
    printf("%d人目の名前を入力してください\n", i + 1);
    scanf("%s", name[i]);
  }
  return name;
}




//二重配列の全てに特定の値を代入
//num*numの配列boxをinnumという値で初期化
int** allin_num(int** box, int innum){
  for(int i = 0; i < blood_num; i++){
    for(int j = 0; j < blood_num; j++){
      box[i][j] = innum;
    }
  }	
  return box;
}  




//配列boxにaとbの関係relation_numを代入する
int** pair_relation(int** box, int a, int b, int relation_num){
  box[a][b] = relation_num;
  box[b][a] = relation_num;
  return box;
}

//nameのいづれかを入力させる
//出力は名前の配列番号名
int name_check(){
  int name_number = 0;
  char* this_name;
  this_name = malloc(sizeof(char)*10);
  scanf("%s",this_name);
  int i = 0;
  while(i < blood_num){
    if(!strcmp(blood_name[i], this_name)){
      name_number = i; 
      break;
    }
    i++;
    if(i == blood_num){
      printf("入力した人の名前を入力してください\n");
      name_number = name_check();
    }
  }
  return name_number;
}

//夫婦関係であれば0を、親子関係であれば1を代入
//nameがrelationという関係であれば、num*numの配列boxにinnumを代入する
int** relation_number(char* relation, int** box, int innum){
  int num;
  for(int i = 0; i < blood_num; i++){
    printf("%s%sの人は何人いますか？\n",blood_name[i], relation);
    scanf("%d", &num);
    for(int j = 0; j < num; j++){
      printf("%s%sの%d人目は誰ですか？\n", blood_name[i], relation, j+1);
      int pair_num;
      pair_num = name_check();
      box = pair_relation(box, i, pair_num, innum);
    }
  }    
  return box;
}




//親等数を求める二人を入力する
int* input_pairname(){
  int *ask_relation;
  ask_relation = malloc(sizeof(int)*2);
  for(int i = 0; i < 2; i++){
    printf("親等数を求めたい二人の内、%d人目を入力してください\n",i+1);
    ask_relation[i] = name_check();
  }
  return ask_relation;
}



//夫婦関係の親等
int* zero_distance(int* blood_distance, int now_distance){
  //夫婦が複雑な場合があるため、完全に0の関係性を入力し終えるまでは繰り返す。
  int *pre_blood_distance;
  pre_blood_distance = blood_distance;
  //全員の記されている距離が今調べている距離と等しいか調べる
  //(0を調べてるなら最初の人物だけ)
  //(now_distanceが0なら、0が記入)
  for(int i = 0; i < blood_num; i++){
    if(blood_distance[i] == now_distance){
      //調べる人物の関係性
      //(最初の人物の夫婦)
      for(int j = 0; j < blood_num; j++){
        if(blood[i][j] == 0 && blood_distance[j] == -1){
	  blood_distance[j] = now_distance;
	}
      }
    }
  }
  if(pre_blood_distance != blood_distance){
    blood_distance = zero_distance(blood_distance, now_distance);
  }
  return blood_distance;
} 

//親子関係の親等
int* one_distance(int* blood_distance, int now_distance){
  //全員の記されている距離が今調べている距離と等しいか調べる
  //(0を調べてるなら最初の人物だけ)
  //(now_distanceが0なら、1が記入)
  for(int i = 0; i < blood_num; i++){
    if(blood_distance[i] == now_distance){
      //調べる人物の関係性
      //(最初の人物の親子)
      for(int j = 0; j < blood_num; j++){
        if(blood[i][j] == 1 && blood_distance[j] == -1){
	  blood_distance[j] = now_distance + 1;
	}
      }
    }
  }
  return blood_distance;
}

int* reserch_distance(int* blood_distance){
  int now_distance = 0;
  int * pre_blood_distance;
  //変化がなくなるまで繰り返す
  for(int i = 0; i < blood_num; i++){
    pre_blood_distance = blood_distance;
    blood_distance = zero_distance(blood_distance, i);
    blood_distance = one_distance(blood_distance, i);
    
    /*
    //テスト
    for(int i = 0; i < blood_num; i++){
      printf("%sと%sとの距離は%d\n",blood_name[pair_name[0]], blood_name[i], blood_distance[i]);
    }
    */
  } 

  /* うまくいかなかった(変更前の値を参照できない？)
  do{
    pre_blood_distance = blood_distance;
    blood_distance = zero_distance(blood_distance, now_distance);
    blood_distance = one_distance(blood_distance, now_distance);
    now_distance++;
    //テスト
    for(int i = 0; i < blood_num; i++){
      printf("pre%sと%sとの距離は%d\n",blood_name[pair_name[0]], blood_name[i],pre_blood_distance[i]);
    } 
    //テスト
    for(int i = 0; i < blood_num; i++){
      printf("post%sと%sとの距離は%d\n",blood_name[pair_name[0]], blood_name[i],blood_distance[i]);
    } 
  }while(pre_blood_distance != blood_distance);
  */
  return blood_distance;
}

//親等数を求める
int relation_distance(){
  //親等数を入れるblood_distanceを作成
  //初期値を-1に
  int *blood_distance;
  blood_distance = malloc(sizeof(int)*blood_num);
  for(int i = 0; i < blood_num; i++){
    blood_distance[i] = -1;
  }
  //最初の一人を0にする
  blood_distance[pair_name[0]] = 0;

  blood_distance = reserch_distance(blood_distance);
  
  /*
  //テスト
  for(int i = 0; i < blood_num; i++){
    printf("%sと%sとの距離は%d\n",blood_name[pair_name[0]], blood_name[i],blood_distance[i]);
  } 
  */
   
  return blood_distance[pair_name[1]];
}



int main(void){
  //人の名前をnameに保存する(namenum個の文字列をm回分)
  //char **name;
  //int num;
  printf("何人入力しますか？\n");
  scanf("%d",&blood_num);
  blood_name = ques_name();
 
  
  //人数分、関係性を入れる配列を作る(隣接行列？)
  blood = malloc(sizeof(int*)*blood_num);
  for(int i = 0; i < blood_num; i++){
    blood[i] = malloc(sizeof(int)*blood_num);
  }
  
  
  //bloodを-1で初期化
  blood = allin_num(blood, -1);
  
  //親子関係の人の関係性を1とする
  blood = relation_number("と親子関係", blood, 1);
  //夫婦関係の人の関係性を0にする
  blood = relation_number("と夫婦関係", blood, 0);
 
  /*  
  //テスト
  printf("\n");
  printf("0が夫婦,1が親子,-1がそれ以外\n");
  for(int i = 0; i < blood_num; i++){
    for(int j = 0; j < blood_num; j++){
      printf("%sと%sの関係は%d。\n", blood_name[i], blood_name[j], blood[i][j]);
    }
  } 
  */
  
  //親等数を求める二人を入力 
  pair_name = input_pairname();
  
  int ans = relation_distance();
  printf("%sと%sの親等数は%d\n", blood_name[pair_name[0]], blood_name[pair_name[1]], ans);

  return 0;
}
