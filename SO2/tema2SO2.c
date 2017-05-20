
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
DIR *dir_pointer;
struct dirent *entry;
int depth=-1;
char *permisiune;


void FileFunction(char *parameter);
void listareDirector(char *name,int level);
void filePermissionAndItsDirectory();
void calculateDepth(int,char**);
int openDirandAssignstat(char *argument);
void showIDandGroupID();




int main(int argc, char *argv[])
{
	
	calculateDepth(argc,argv);
	openDirandAssignstat(argv[optind]);
	//printf("%s\n",permisiune );
	

	return 0;
}
void calculateDepth(int argc,char **argv){
	int c;
	
	
	static struct option long_option[]={
		{"mdepth",required_argument,0,'c'},
		 {"permisiuni",required_argument,0,'p'},
		{0,0,0,0}
	};
	while(1){

		//int this_option_optind = optind ? optind : 1;
		c=getopt_long(argc,argv,"c:",long_option,NULL);
		if(c== -1) break;
		switch(c){
			case 'c': depth=atoi(optarg);break;
			case 'p': strcpy(permisiune,optarg); break;
			default: exit(0);


		}

	}

}

int openDirandAssignstat(char *argument){
	if(stat(argument,&fileStat) < 0)    
		return 1;
	dir_pointer = opendir(argument);
	listareDirector(argument,0);

	return 1;
}

void listareDirector(char *name,int level){
	char path[1024];

	if (!(dir_pointer = opendir(name)))
		return;
	if (!(entry = readdir(dir_pointer)))
		return;

	do{	
		if (entry->d_type == DT_DIR) {
			
			sprintf(path, "%s/%s", name, entry->d_name);
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			
			FileFunction(path);
			showIDandGroupID();
			if(depth>level || depth==-1)
				listareDirector(path, level + 1);
		}
		else
		{
			;
			//sprintf(path, "%s/%s", name, entry->d_name);
			//FileFunction(path);
		}

	} while ( (entry = readdir(dir_pointer) ));
	
}

void FileFunction(char *parameter)
{
	
	stat(parameter,&fileStat);

	printf("\nInformation for %s\n",parameter);
	printf("---------------------------\n");
	printf("File Size: \t\t%ld bytes\n",fileStat.st_size);
	printf("Number of Links: \t%ld\n",fileStat.st_nlink);
	printf("File inode: \t\t%ld\n",fileStat.st_ino);
	filePermissionAndItsDirectory();
	
	printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
}

void filePermissionAndItsDirectory() {

	printf("File Permissions: \t");
	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n\n");
}


void showIDandGroupID(){

struct passwd  *pwd;
struct group   *grp;

	if ((pwd = getpwuid(fileStat.st_uid)) != NULL)
		printf(" %-8.8s\n", pwd->pw_name);
	else
		printf(" %-8d\n", fileStat.st_uid);



	if ((grp = getgrgid(fileStat.st_gid)) != NULL)
		printf(" %-8.8s\n", grp->gr_name);
	else
		printf(" %-8d\n", fileStat.st_gid);
}