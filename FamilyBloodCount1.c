#include <stdio.h>
#include <string.h>

typedef enum {
      myself,child,parent,grandchild,grandparent,greatgrandson,
      Family_count
  } E_Family;
  
typedef struct{
      int family;
} blood;
  
int Change(char *str){
    int input = 0;
    if(strcmp(str,"子供") == 0){
        input = child;
    }else if(strcmp(str,"親") == 0){
        input = parent;
    }else if(strcmp(str,"孫") == 0){
        input = grandchild;
    }else if(strcmp(str,"祖父母") == 0){
        input = grandparent;
    }else if(strcmp(str,"ひ孫") == 0){
        input = greatgrandson;
    }else{ input = -1; }
    
    return input;
}

//呼び方を入れると、それが本人までいくつかかるかの関数
int FamilyNum(blood relation[], int self, int num){
    
    if(self == -1){
        num = -1;
    }else if(relation[self].family != myself){
        num = FamilyNum(relation, relation[self].family, num + 1);
    };
    return num;  
}
  
int main(void){
    
  blood relation[Family_count];
  relation[child].family = myself;
  relation[parent].family = myself;
  relation[grandchild].family = child;
  relation[grandparent].family = parent;
  relation[greatgrandson].family = grandchild;
    
  printf("子供、親、孫、祖父母、ひ孫から選ぶ\n");  

  char str[100];
  scanf("%s", str);
  int input = Change(str);

  int distance = FamilyNum(relation, input, 1);
  
  printf("親等の数は：%d\n", distance);
  
  return 0;
}
