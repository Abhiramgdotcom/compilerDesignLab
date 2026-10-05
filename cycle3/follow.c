#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int n,m; //number of productions, number of first or follow.
char a[10][10], f[10],ch; //a is for storing productions, f is for storing first or follow.

void first(char c){
    if(islower(c)){
        f[m++]=c;
        return;
    }
    for(int i=0;i<n;i++){
        if(a[i][0]==c){
            first(a[i][3]);
        }
    }
}
void follow(char c){
    if(c==a[0][0]){
        f[m++]='$';
    }
    for(int i=0;i<n;i++){
        for(int j=3;j<strlen(a[i]);j++){
            if(a[i][j]==c){
                if(a[i][j+1]!='\0'){
                    first(a[i][j+1]);
                }
                else if(a[i][j+1]=='\0' && a[i][0]!=c){
                    follow(a[i][0]);
                }
            }
        }
    }
}
int main(){
    int z;
    printf("Enter the number of productions :");
    scanf("%d",&n);
    printf("Enter the productions :\n");
    for(int i=0;i<n;i++){
        scanf("%s",a[i]);
    }
    do{
        printf("Enter the element whose first and follow is to be found :");
        scanf(" %c",&ch);
        m=0;
        first(ch);
        printf("First of %c : { ",ch);
        for(int i=0;i<m;i++){
            printf("%c ",f[i]);
        }
        printf("}\n");
        m=0;
        follow(ch);
        printf("Follow of %c : { ",ch);
        for(int i=0;i<m;i++){
            printf("%c ",f[i]);
        }
        printf("}\n");
        printf("Is contineing(0/1) ");
        scanf("%d",&z);
    }while(z==1);
    return 0;
}
/*
    Example Productions:
    S->AB
    A->a
    B->b

    In a[0]=S->AB
       a[1]=A->a
       a[2]=B->b
    
    first(S)={a}
    first(A)={a}
    first(B)={b}

    follow(S)={$}
    follow(A)={b}
    follow(B)={$}
*/