#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int n;
void closure(int state, int matrix[][n]){
    for(int r=0;r<n;r++){
        if(matrix[state][r]==1){
            printf(", q%d",r);
            closure(r,matrix);
        }
    }
}
int main(){
    FILE *INPUT=fopen("input2.txt","r");
    if (!INPUT){
        printf("File not found");
        exit(1);
    }
    char state1[10],input[10],state2[10];
    int s1,s2;
    printf("Enter the number of States:");
    scanf("%d",&n);
    int matrix[n][n];
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matrix[i][j]=0;
        }
    }
    while(fscanf(INPUT,"%s %s %s",state1,input,state2)!=EOF){
        if (strcmp(input,"e")==0){
            s1=state1[1]-'0';
            s2=state2[1]-'0';
            matrix[s1][s2]=1;
        }
    }
    fclose(INPUT);
    for ( int i=0;i<n;i++){
        printf("q%d:{ q%d",i,i);
        closure(i,matrix);
        printf("}\n");
    }
}