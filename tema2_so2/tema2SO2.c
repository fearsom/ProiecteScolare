
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include <pwd.h>
#include <grp.h>
#define required_argument 1 




struct stat fileStat;

int depth=-1,varDeAles;
static char vectorPermisiune[20];
char userid[20];
char groupid[20];
long int dimensiuneMinima,dimensiuneMaxima;


void FileFunction(char *parameter);
void listareDirector(char *name,int level);
void assaignParameters(int,char**);
int openDirandAssignstat(char *argument);
char* filePermissionAndItsDirectory(char *);
void verificareSiAfisare(struct passwd  *pwd,struct group   *grp,char *path);
long int calculateFileSize(char *fullpath);



int main(int argc, char *argv[])
{
	  int index;
	assaignParameters(argc,argv);
 for (index = optind; index < argc; index++)
   openDirandAssignstat(argv[index]);
 

	return 0;
}
void assaignParameters(int argc,char **argv){
	int a;	
	
	static struct option long_option[]={
		{"mdepth",required_argument,0,'c'},
		{"userid",required_argument,0,'u'},
		{"groupid",required_argument,0,'g'},
		{"permission",required_argument,0,'p'},
		{"dimmin",required_argument,0,'d'},
		{"dimmax",required_argument,0,'i'},
		{0,0,0,0}
	};
	while(1){

		a=getopt_long(argc,argv,"c:p:u:g:d:i:",long_option,NULL);
		if(a== -1) break;
		switch(a){
			case 'c': depth=atoi(optarg);break;
			case 'p': strcpy(vectorPermisiune,optarg);varDeAles=3;break;
			case 'u':  strcpy(userid,optarg);varDeAles=1; break;
			case 'g': strcpy(groupid,optarg);varDeAles=2; break;
			case 'd': dimensiuneMinima=atoi(optarg);varDeAles=4;break;
			case 'i': dimensiuneMaxima=atoi(optarg);break;
			default: exit(0);

		}

	}
	


}

int openDirandAssignstat(char *argument){
	if(stat(argument,&fileStat) < 0)    
		return 1;
	listareDirector(argument,0);

	return 1;
}

void listareDirector(char *name,int level){
	
	struct passwd  *pwd;
	struct group   *grp;
	DIR *dir_pointer;
	struct dirent *entry;

	if (!(dir_pointer = opendir(name)))
		return;
	if (!(entry = readdir(dir_pointer)))
		return;

	do{
		char path[1024];

		pwd = getpwuid(fileStat.st_uid);
		grp = getgrgid(fileStat.st_gid);
		snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
		if (entry->d_type == DT_DIR) {
			


			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;

			if(depth>=level || depth==-1){
				verificareSiAfisare(pwd,grp,path);
				listareDirector(path, level + 1);
			}	
			
		}
		else	
			if(depth>=level || depth==-1)
				verificareSiAfisare(pwd,grp,path);			

		}while ((entry = readdir(dir_pointer)));

		closedir(dir_pointer);
	}

	void verificareSiAfisare(struct passwd  *pwd,struct group   *grp,char *path){

		switch(varDeAles){

			case 1: if(strcmp(pwd->pw_name,userid)==0){

				FileFunction(path);
				printf("Group ID %-8.8s\n", pwd->pw_name);
			}
			break;
			case 2: 
			if(strcmp(grp->gr_name,groupid)==0){
				FileFunction(path);
				printf("Group ID %-8.8s\n", grp->gr_name);				
			}
			break;

			case 3:    if(strcmp(filePermissionAndItsDirectory(path),vectorPermisiune)==0)
				FileFunction(path);
				
			
			break;
			case 4: 		
			if(dimensiuneMinima <= calculateFileSize(path) && dimensiuneMaxima>=calculateFileSize(path))
				FileFunction(path);
			break;
			default:	FileFunction(path); break;		

		}



	}

	void FileFunction(char *parameter)
	{
		stat(parameter,&fileStat);

		printf("\nInformation for %s\n",parameter);
		printf("---------------------------\n");
		printf("File Size: \t\t%ld bytes\n",calculateFileSize(parameter));
		printf("Number of Links: \t%ld\n",fileStat.st_nlink);
		printf("File inode: \t\t%ld\n",fileStat.st_ino);
		printf("File Permissions: \t");
		printf(filePermissionAndItsDirectory(parameter));
		printf("\n\n");

		printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
	}

	char* filePermissionAndItsDirectory(char *parameter) {
		stat(parameter,&fileStat);
		char *permisiuneFisier=(char*)malloc(11*sizeof(char));

		strcpy(permisiuneFisier,((S_ISDIR(fileStat.st_mode)) ? "d" : "-"));
		strcat(permisiuneFisier, ((fileStat.st_mode & S_IRUSR) ? "r" : "-"));
		strcat(permisiuneFisier,((fileStat.st_mode & S_IWUSR) ? "w" : "-"));
		strcat(permisiuneFisier,((fileStat.st_mode & S_IXUSR) ? "x" : "-"));
		strcat(permisiuneFisier,((fileStat.st_mode & S_IRGRP) ? "r" : "-"));
		strcat(permisiuneFisier,((fileStat.st_mode & S_IWGRP) ? "w" : "-"));
		strcat(permisiuneFisier,((fileStat.st_mode & S_IXGRP) ? "x" : "-"));
		strcat(permisiuneFisier,((fileStat.st_mode & S_IROTH) ? "r" : "-"));
		strcat(permisiuneFisier,((fileStat.st_mode & S_IWOTH) ? "w" : "-"));
		strcat(permisiuneFisier, ((fileStat.st_mode & S_IXOTH) ? "x" : "-"));


		return permisiuneFisier;

	}

	long int calculateFileSize(char *fullpath){
		long int dimensiuneFisier;
		stat(fullpath,&fileStat);

		dimensiuneFisier=fileStat.st_size;

		return dimensiuneFisier;
	}


