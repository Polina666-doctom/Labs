#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


int main()
{
char argv[16][80]; 
char *a[16];
int i=0;
int j=0,k,err_exec,ch,inp,out,inp_flag=0,out_flag=0;;

printf("***");

while((ch=getchar()) != EOF)
{
if (ch=='\n')
{
argv[i][j]='\0';
k=i;
for (i=0;i<=k;++i)
{
a[i]=argv[i];
}
a[i]=NULL;
pid_t pid=fork();
if (pid==-1)
{
perror("fork");
}
else
{
if (!pid)
{
if (out_flag==1) /* проверка на дискрипторы (0-работа с клавиатурой и экраном, 1-работа с файлой, 2- работа  с ошибками)*/
{
int fdout=open(a[out],O_WRONLY|O_CREAT|O_TRUNC,0664); /* создаемфайлдля записи( название файла,атрибут для записи, создаем файл если его несуществует, если в файле что то  естьтоочищаем его), права доступа для пользователя*/
if (fdout==-1) /* проверка на ошибку ,если файл не создался*/
{
perror ("open out");
exit(EXIT_FAILURE);/* файл не создался*/
}
if (-1==dup2(fdout, STDOUT_FILENO)) /* неправильный аргумент дисриптор*/
{
perror("dup out");
exit(EXIT_FAILURE);
}
a[out]=NULL; /*очищаем массив*/
}
if (inp_flag==1) /*то же самое только на вход*/
{
int fdin=open(a[inp],O_RDONLY);
if (fdin==-1)
{
perror ("open inp");
exit(EXIT_FAILURE);
}
if (-1==dup2(fdin, STDIN_FILENO))
{
perror ("dup inp");
exit(EXIT_FAILURE);
}
a[inp]=NULL;
}
err_exec=execvp(a[0],a);
if (err_exec==-1)
{
perror("execvp");
exit(EXIT_FAILURE);
}
exit(EXIT_SUCCESS);
}
}
pid=wait(NULL);
if (pid==-1)
{
perror("wait");
}
printf("$");
i=0;
j=0;
inp_flag=0;out_flag=0;
continue;
}




if (ch==' ') /*проверкана пробел*/
{
argv[i][j]='\0';
++i;
j=0;
continue;
}

if (ch=='<') /*проверка на стрелочкуу (дескриптор на вход)*/
{
inp=i;
if ((ch=getchar()) != ' ')
{
argv[i][j]=' ';
++j;
}
++inp_flag;
continue;
}

if (ch=='>')/*проверка на стрелочкуу (дескриптор на выход)*/
{
if (i==inp)
{
argv[i][j]='\0';
++i; j=0;
}
out=i;
if ((ch=getchar()) !=' ')
{
argv[i][j]=' ';
++j;
}
++out_flag;
continue;
}

argv[i][j]=ch;
++j;



}


return EXIT_SUCCESS;
}
