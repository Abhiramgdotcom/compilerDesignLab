#include <stdio.h>
#include <string.h>
#include <ctype.h>
char keyWords[][20]={
    "int","float","char","double","if","else","while",
    "for","return","void","break","continue","switch","case","default"
};
int isKeywords(char str[]){
    int n=sizeof(keyWords)/sizeof(keyWords[0]);
    for(int i=0;i<n;i++){
        if (strcmp(str,keyWords[i])==0){
            return 1;
        }
    }
    return 0;
}
int main(){
    FILE *fp;
    char ch,buffer[100];
    int i;
    fp=fopen("input.c","r");
    if (fp==NULL){
        printf("File not opening\n");
        return 0;
    }
    while ((ch=fgetc(fp))!=EOF){
        if (isspace(ch))
            continue;
        if (ch=='/'){
            char next=fgetc(fp);
            if (next=='/'){
                while ((ch=fgetc(fp))!='\n' && ch!=EOF){
                    continue;
                }
            }
            else if(next=='*'){
                char prev=0;
                while((ch=fgetc(fp))!=EOF){
                    if (prev=='*' && ch=='/')
                        break;
                    prev=ch;
                }
                continue;
            }
            else{
                printf("%s\t\t%c\n","OPERATOR",ch);
                fseek(fp,-1,SEEK_CUR);
                continue;
            }
        }
        if (isalpha(ch) || ch=='_'){
            i=0;
            buffer[i++]=ch;
            while((ch=fgetc(fp))!=EOF && ((isalnum(ch)) || ch=='_')){
                buffer[i++]=ch;
            }
            buffer[i]='\0';
            if (ch!=EOF)
                fseek(fp,-1,SEEK_CUR);
            if (isKeywords(buffer))
                printf("KEYWORD\t\t%s\n",buffer);
            else
                printf("IDENTIFIER\t\t%s\n",buffer);
        }
        else if(isdigit(ch)){
            i=0;
            buffer[i++]=ch;
            while((ch=fgetc(fp))!=EOF && isdigit(ch)){
                buffer[i++]=ch;
            }
            buffer[i]='\0';
            if(ch!=EOF)
                fseek(fp,-1,SEEK_CUR);
            printf("NUMBER\t\t%s\n",buffer);
        }
        else if(ch=='"'){
            i=0;
            while((ch= fgetc(fp))!=EOF && ch!='"'){
                buffer[i++]=ch;
            }
            buffer[i]='\0';
            printf("LITERAL\t\t\"%s\"\n",buffer);
            continue;
        }
        else if (strchr("+-*=<>!%",ch))
            printf("OPERATOR\t\t%c\n",ch);
        else if (strchr("(){}[];:,@#",ch))
            printf("SPECIAL\t\t%c\n",ch);
    }
    fclose(fp);
    return 0;
}