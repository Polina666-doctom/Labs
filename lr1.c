#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



int main()
 {
  char argv[16][80]; /*массив аргументов для программы*/
  char *a[16];  /*массив указателей(там будет храниться имя программы) */
  int i=0;
  int j=0,k,err_exec,ch;/*K- число символов в строке,err_exec номер ошибки,ch - переменная для движения по строке*/

   printf("***"); /*вывод звездочек в начале строки*/

  while((ch=getchar()) != EOF) /*пока не конец файла*/
  {
    if (ch=='\n') /*если конец строки*/
      {
         argv[i][j]='\0'; /*конец ввода*/
         k=i;
         for(i=0;i<=k;i++)
             {
               a[i]=argv[i]; /*записываем название программы*/
             }
        a[i]=NULL; /*массив аргументов для программы*/

        pid_t pid = fork(); /* создаем пустой процесс */
        if (pid==-1)  /* проверка на запуск */
             {
               perror("fork");
             }
         else
         if (!pid) 
             {
               err_exec=execvp(a[0],a); /*замещает процесс которыйбыл в форк, на тот который мыввели с консоли*/
               if (err_exec==-1) /* проверка на запуск */
                     {
                       perror("execvp");
                     }
             }
           pid=wait(NULL); /* режим ожидания */
           if (pid==-1)  /* проверка на запуск */
               {
                perror("wait");
               }
          printf("$");
       i=0; j=0;
       continue;
      }
    if (ch==' ')  {
        argv[i][j]='\0';
        ++i;
        j=0;
        continue;
                  }
    argv[i][j]=ch;
    ++j;
  }

return EXIT_SUCCESS; 
}