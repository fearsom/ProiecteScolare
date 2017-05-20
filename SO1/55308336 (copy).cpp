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
 printf("%d\n",nrArgumente );
    int parametruB=0,parametruN=0,parametruE=0,parametruS=0;
   int i=1,j=0;
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
  
    FILE * fp=fopen(argumente[1] ,"r");;
    int k=1;
    if (fp == NULL)
        exit(EXIT_FAILURE);
    char caracter,ultimulCaracter;
    ultimulCaracter = (char)malloc(strlen(caracter) * sizeof(char));
    int nrL=0;
    printf("parametru este %d\n",parametruE );
  while( caracter=fgetc(fp),!feof(fp))
  {
    
    if( caracter =='\n')
    {
        if(parametruE==1)       
            printf("$\n");
        else
             printf("\n");
        if( parametruB==1 )//&& ultimulCaracter=='\n'){
        {
            printf("%d\t",nrL );
            nrL++;
            //ultimulCaracter='\n';
        }
    }
    else
    {
        printf("%c",caracter);
    }
    //strcpy(ultimulCaracter,caracter);

    
     
    }      
        //pt -b
        /*    if(IsEmptyLine(line))
                { printf("\n");
                continue;}
            printf("%d\t",k);
    printf("%s", line);
      k++;       
         
      //pt -n
printf("%d\t",k);
    printf("%s", line);
      k++;       
*/
      //pt -s
       /* if(IsEmptyLine(line) && cateLiniiAlbeAm==0)  
        { cateLiniiAlbeAm=1;       
                continue;}
         printf("%s", line);
         cateLiniiAlbeAm=0;
*/
         // pt -E
         
         
         

         
         
            
             
       

            
           
   
fclose(fp);
}

void headCommand(char** argumente, int nrArgumente){
int parametruC=0,parametruN=0,parametruQ=0,parametruV=0;
int pozitieC,pozitieN,pozitieQ,pozitieV;
   int i=1,nrDeLinii=0,contor=0;

for(i;i<nrArgumente;i++)
        {
    if(strcmp(argumente[i],"-c"))
           {parametruC=1;pozitieC=i;continue;}
       if(strcmp(argumente[i],"-n"))
           {parametruN=1;pozitieN=i;continue;}
       if(strcmp(argumente[i],"-q"))
          { parametruQ=1;pozitieQ=i;continue;}
       if(strcmp(argumente[i],"-v"))
           {parametruV=1;pozitieV=i;continue;}

    }
  FILE * fp;
    char line[300];
   

    fp = fopen(argumente[1] ,"r");
  
    if (fp == NULL)
        exit(EXIT_FAILURE);
  // while (fgets (line, sizeof(line), fp)) 
   // nrDeLinii++;

int aux=1,j;
while (fgets (line, sizeof(line), fp)) 
    {
        //pt nici un argument
       /*  if(contor==10)
        break;
        printf("%s", line);
        contor++;
*/
        //pt -n

        /*int conversie= atoi(argumente[pozitieN-1]);
        if(contor == conversie)
            break;
   printf("%s", line);
        contor++;*/

   // pt -q
        /*int conversie= atoi(argumente[pozitieN-1]);
        if(contor == conversie)
            break;
   printf("%s", line);
        contor++;*/

   // pt -v
   /*if(aux==1)
   {aux=0;printf("==> %s <==\n",argumente[1]);}
        if(contor==10)
        break;
        printf("%s", line);
        contor++;*/
    }

    //pt -c
    
    int conversie= atoi(argumente[pozitieC-1]);
    fscanf(fp,"%c",argumente[1]);

       
    
        
     }

void envCommand(char** argumente, int nrArgumente)   
{

    int count = 0;

  printf("\n");
  while(environ[count] != NULL)
  {
    printf("%s :: \n", environ[count]);
    count++;
  }


  while(1)
  {
    sleep(2);
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
          cmdArgc = parse(input, cmdArgv, &supplement, &mod);
       if(strcmp(*cmdArgv, "cat") == 0)
            {
        	catCommand(cmdArgv,cmdArgc);
        	// cmdArgc = parse(input, cmdArgv, &supplement, &mod);
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
        execvp(*cmdArgv, cmdArgv);
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
                execvp(*cmdArgv2, cmdArgv2);
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