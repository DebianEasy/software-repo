#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
//version 0.2
int passcmp(char user[],char passwd[])
{
    FILE *fp;
    int count;
    int count2;
    char TmpCmd[1024];
    char buf[1024];
    char GetentPasswd[] = "getent passwd ";
    char DevNull[] = " > /dev/null";
    char GetentShadow[]="getent shadow ";
    char Awk[]="| awk -F: \'{print $2}\'";
    char IFS[]="IFS=$ ";
    char HashType[16];
    char ENT2[128];
    char MkPasswd[]="mkpasswd -sm ";
    char Bash[]="bash -c ";
    char Perl[]="perl -e \' print crypt \"";
    char Echon[]="; echo";
    char PassCode[1024];
    char SaltCode[1024];
    char *p ;
    char DivCode[16][1024];
    strcpy(TmpCmd,GetentPasswd);
    strcat(TmpCmd,user);
    strcat(TmpCmd,DevNull);
    if ( system(TmpCmd) == 0 )
    {
        strcpy(TmpCmd,GetentShadow);
        strcat(TmpCmd,user);
        strcat(TmpCmd,Awk);
        fp = popen(TmpCmd,"r");
        if (!fp) {
            puts("Internal error");
            return 1;
        }
        fgets(buf,1024,fp);
        pclose(fp);
        strcpy(PassCode,buf);
        p = strtok(buf,"$");
        //puts(PassCode);
        count=0;
        while(p)
        {
            strcpy(DivCode[count],p);
           // puts(DivCode[count]);
            count=count+1;
            p = strtok(NULL,"$");
        }
        //printf("%d",count);
        count=count-1;
        strcpy(SaltCode,"\\$");
        count2=0;
        while  ( count2<count ){
            strcat(SaltCode,DivCode[count2]);
            strcat(SaltCode,"\\$");
            count2=count2+1;
        }
        //puts(SaltCode);
        strcpy(TmpCmd,Perl);
        strcat(TmpCmd,passwd);
        strcat(TmpCmd,"\", \"");
        strcat(TmpCmd,SaltCode);
        strcat(TmpCmd,"\"\'");
        strcat(TmpCmd,Echon);
        //puts(TmpCmd);
        fp = popen(TmpCmd,"r");
        if (!fp) {
            puts("Internal error");
            return 1;
        }
        fgets(buf,1024,fp);
        //puts(buf);
        pclose(fp);
        return strcmp(buf,PassCode);
    }
    else{
        puts("User Not Found");
        return 1;
    }
}

int echohelp(char name0[] ){
    printf("Usage: %s user passwd\n",name0);
}

int main(int argc,char *argv[]){
    int flag;
    if (argc != 3){
        echohelp(argv[0]);
    }
    else
    {
    setuid(0);
    flag=passcmp(argv[1],argv[2]);
    if ( flag == 0 ){
        printf("Password correct\n");
        return 0;
    }
    else{
        printf("Password not correct\n");
        return 1;
    }
    }
}
