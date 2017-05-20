#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <string.h>

void execute(char **, int, char **);
int parse(char *input, char *cmdArgv[], char **suplcpinput, int *modcp);
void chop(char *cpinput);
extern char **environ;

#define INPUT_SIZE          101
#define NORMAL              1
#define REDIRECTIE  		3
#define PIPE            	2
#define OUT  				4




    
void catCommand(char **argumente,int nrArgumente)
{
 
    int parametruB=0,parametruN=0,parametruE=0,parametruS=0;
   int i=1;
for(i;i<nrArgumente;i++)
        {
        if(strcmp(argumente[i],"-b")==0)
           parametruB=1; 
       if(strcmp(argumente[i],"-E")==0)
           parametruE=1;
       if(strcmp(argumente[i],"-n")==0)
           parametruN=1;
       if(strcmp(argumente[i],"-s")==0)
           parametruS=1;

        }
  
    FILE * fp=fopen(argumente[1] ,"r");   
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    int  nrLiniiGoale=0;
    char line[100],areDolar=' ';
    int nrL=0;
    if(parametruE)areDolar='$';
  while (fgets(line, sizeof(line), fp) != NULL)
  {
    line[strlen(line) - 1] = '\0'; 
    
            if(parametruE==0 && parametruB==0 && parametruN==0 && parametruS ==0)
            {
              printf("%s\n", line);
              continue;
            }
  nrL++;
   if (strlen(line) == 0)
   { 
      nrLiniiGoale++;
         
    if (parametruS)
        {
          if(nrLiniiGoale==1)printf("%c\n",areDolar);
          nrL--;
        continue;
        }
    if(parametruB)
      {
        
         nrL--;
         printf("%c\n",areDolar);
      continue;
      }
    }
    else
      nrLiniiGoale=0;

              if(parametruB==1 && strlen(line) != 0)
              {
                printf("%d %s%c\n",nrL,line,areDolar); continue;
              }
             
              if(parametruN==1 && parametruS==0)
               printf("%d %s%c\n",nrL,line,areDolar);
              else if(!parametruB)
                printf("%s%c\n", line,areDolar);
   }
fclose(fp);
}

void headCommand(char** argumente, int nrArgumente)
{
int parametruC=0,parametruN=0,parametruQ=0,parametruV=0;
int pozitieC,pozitieN,pozitieQ,pozitieV;
   int i=1,nrDeLinii=0,contor=0;

for(i;i<nrArgumente;i++)
        {
    if(strcmp(argumente[i],"-c")==0)
           {parametruC=1;pozitieC=i;}
       if(strcmp(argumente[i],"-n")==0)
           {parametruN=1;pozitieN=i;}
       if(strcmp(argumente[i],"-q")==0)
          { parametruQ=1;pozitieQ=i;}
       if(strcmp(argumente[i],"-v")==0)
           {parametruV=1;pozitieV=i;}

    }
  FILE * fp;
    char line[300];
   

    fp = fopen(argumente[1] ,"r");
  
    if (fp == NULL)
        exit(EXIT_FAILURE);
   
    if(parametruV==1)
      printf("==> %s <==\n",argumente[1]);

   while (fgets (line, sizeof(line), fp)) 
   {
  nrDeLinii++;
    if(parametruN==0 && !parametruC && nrDeLinii<11)
    {
        printf("%s",line );
        continue;
    }

   if (parametruN==1 && nrDeLinii< atoi(argumente[pozitieN+1])+1)
   {
     printf("%s",line );continue;
    }

break;
   }
 
char c;
if(parametruC==1)
{
   pozitieC= atoi(argumente[pozitieC+1])+1;

while ((c = fgetc(fp)) != EOF && (pozitieC--)!=0)
   {
    printf("%c",c );


   }
   printf("\n");
}
  
}
bool checkIfIsName(char *l,char * envVariable)
{
  char * parser =l;
  int i = 0;
  char *c = (char*)malloc((strlen(l)+1)*sizeof(char));
  strcpy(c,l);
  while(i<strlen(l) && c[i]!= '=')i++;
  c[i] = '\0';
 
  return strcmp(c,envVariable) ==0;
}
void envCommand(char** argumente, int nrArgumente)   
{
  int i=1,parametruU=0;
  char * envVariable;
  
for(i;i<nrArgumente;i++)
        {
    if(strcmp(argumente[i],"-u")==0)
    {
      parametruU=1;
      envVariable = (char*)malloc((strlen(argumente[i+1])+1)*sizeof(char));
  strcpy(envVariable,argumente[i+1]);
      }
        }
    int count = 0;
    int p;
  printf("\n");
  printf("%s\n",envVariable );
  while(environ[count] != NULL)
  {
    if(!(parametruU==1 && checkIfIsName(environ[count],envVariable)))
         printf("%s :: \n", environ[count]);

    count++;
  }


}

int main(int argc, char *argv[])
{
    int ok=1;
    int opt=0;
    int bflag = 0;
    int i, mod = NORMAL, cmdArgc;
    size_t len = INPUT_SIZE;
    char *input, *cmdArgv[INPUT_SIZE], *supplement = NULL;

    char curDir[100];
    while(ok==1)
    {
    	mod=NORMAL;
    	getcwd(curDir, 100);
    	printf("%s@%s->", getlogin(),curDir);
    	input = (char*)malloc(sizeof(char)*INPUT_SIZE);
    	input = readline("");
    	if (input[0]!=0)
            add_history(input);
        if (strcmp(input,"exit")==0)
            {
            	ok=0;
            }
            if (strlen(input)==0)
           continue;
          cmdArgc = parse(input, cmdArgv, &supplement, &mod);
       if(strcmp(*cmdArgv, "cat") == 0)
            {
        	catCommand(cmdArgv,cmdArgc);
        	
            }
        
           
        else if(strcmp(*cmdArgv, "head") == 0)
            headCommand(cmdArgv,cmdArgc);
        
        else if(strcmp(*cmdArgv, "env") == 0)
                envCommand(cmdArgv, cmdArgc);
          else execute(cmdArgv, mod, &supplement); 
        
    
          
        }
        free(input);
    
 
    return 0;
}

int parse(char *input, char *cmdArgv[], char **suplcpinput, int *modcp)
{
    int cmdArgc = 0, terminate = 0;
    char *cpinput = input;
    while(*cpinput != '\0' && terminate == 0)
    {
        *cmdArgv = cpinput;
        cmdArgc++;
        while(*cpinput != ' ' && *cpinput != '\t' && *cpinput != '\0' && *cpinput != '\n' && terminate == 0)
        {
            switch(*cpinput)
            {
                case '>':
                    *modcp = REDIRECTIE;
                    *cmdArgv = '\0';
                    cpinput++;
                    while(*cpinput == ' ')
                        cpinput++;
                    *suplcpinput = cpinput;
                    chop(*suplcpinput);
                    terminate = 1;
                    break;
                case '|':
                    *modcp = PIPE;
                    *cmdArgv = '\0';
                    cpinput++;
                    while(*cpinput == ' ')
                        cpinput++;
                    *suplcpinput = cpinput;
                    terminate = 1;
                    break;
            }
            cpinput++;
        }
        while((*cpinput == ' ') && terminate == 0)
        {
            *cpinput = '\0';
            cpinput++;
        }
        cmdArgv++;
    }
    *cmdArgv = '\0';
    return cmdArgc;
}

void chop(char *cpinput)
{
    while(*cpinput != ' ' && *cpinput != '\t' && *cpinput != '\n')
    {
        cpinput++;
    }
    *cpinput = '\0';
}

void execute(char **cmdArgv, int mod, char **suplcpinput)
{
    pid_t pid, pid2;
    FILE *fp;
    int mod2 = NORMAL, status1;
    char *cmdArgv2[INPUT_SIZE], *supplement2 = NULL;
    int myPipe[2];
    if(mod == PIPE)
    {
        pipe(myPipe);
        parse(*suplcpinput, cmdArgv2, &supplement2, &mod2);
    }
    pid = fork();
    if(pid == 0)
    {
        switch(mod)
        {
            case REDIRECTIE:
                fp = fopen(*suplcpinput, "w+");
                dup2(fileno(fp), 1);
                break;
            case PIPE:
                close(myPipe[0]);
                dup2(myPipe[1], fileno(stdout));
                close(myPipe[1]);
                break;
        }
        if(execvp(*cmdArgv, cmdArgv)<0)
          {
            printf("Undefined" );
          }
        fclose(fp);
    }
    else
    {
        if(mod == PIPE)
        {
            waitpid(pid, &status1, 0);      
            pid2 = fork();
            if(pid2 == 0)
            {
                close(myPipe[1]);       
                dup2(myPipe[0], fileno(stdin));
                close(myPipe[0]);
                
                if(execvp(*cmdArgv2, cmdArgv2)<0)
          {
            printf("Undefined" );
          }
            }
            else
            {


                close(myPipe[0]);
                close(myPipe[1]);

            }
        }


        else
            waitpid(pid, &status1, 0);
    }
}