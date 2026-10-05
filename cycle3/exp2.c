#include <stdio.h>
#include <string.h>
int st;
void closure(int state, int matrix[][st]){
    for(int i=0;i<st;i++){
        if(matrix[state][i]==1){
            printf(", q%d", i);
            closure(i,matrix);
        }
    }
}
int main(){
    FILE *fp=fopen("input.txt", "r");
    if(!fp) printf("File not Found !!!");
    printf("Enter the number of states: ");
    scanf("%d", &st);
    char state1[100], input[100], state2[100];
    int s1,s2;
    int matrix[st][st];
    for(int i=0;i<st;i++){
        for(int j=0;j<st;j++){
            matrix[i][j]=0;
        }
    }
    while(fscanf(fp, "%s %s %s", state1, input, state2)!=EOF){
        if(strcmp(input, "e")==0){
            s1=state1[1]-'0';
            s2=state2[1]-'0';
            matrix[s1][s2]=1;
        }
    }
    fclose(fp);
    printf("\n Epsilon Closure\n");
    for(int i=0;i<st;i++){
        printf("q%d={ q%d ",i,i);
        closure(i,matrix);
        printf(" }\n");
    }
    return 0;
}