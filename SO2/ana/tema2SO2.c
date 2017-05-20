
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#define required_argument 1 




struct stat fileStat;
DIR *dir_pointer;
struct dirent *entry;
int depth;


void FileFunction(char *parameter);
void listareDirector(char *name,int level);
void filePermissionAndItsDirectory();

int main(int argc, char *argv[])
{
	

	int c;
	int digit_opting =0;
	int index;
	static struct option long_option[]={
		{"mdepth",required_argument,0,'c'},
		{0,0,0,0}
	};
	while(1){

		int this_option_optind = optind ? optind : 1;
		c=getopt_long(argc,argv,"c:",long_option,&index);
		if(c== -1) break;
		switch(c){
			case 'c': depth=atoi(optarg);break;
			default: exit(0);


		}

	}
	
	if(optind<argc)
	{
		if(stat(argv[optind],&fileStat) < 0)    
			return 1;
		dir_pointer = opendir(argv[optind]);
		listareDirector(argv[optind],0);
	}
	

	return 0;
}

void listareDirector(char *name,int level){
	

	if (!(dir_pointer = opendir(name)))
		return;
	if (!(entry = readdir(dir_pointer)))
		return;

	do{	
		if (entry->d_type == DT_DIR) {
			char path[1024];
			sprintf(path, "%s/%s", name, entry->d_name);
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			
			FileFunction(path);
			if(depth>level)
				listareDirector(path, level + 1);
		}
		else
			FileFunction(entry->d_name);





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

