#include "common.h"
#include <string.h>
const char* param[]={\
		"---","--x","-w-","-wx"\
		,"r--","r-x","rw-","rwx"\
		};
struct stat* readstat(const char* path)
{
	struct stat* sbuf=(struct stat*)malloc(sizeof(struct stat));
	if((stat(path,sbuf))<0)
	{
		perror("read stat error\n");
		return NULL;
	}
	return sbuf;
}

void readpermission(mode_t mode)
{
	int i,ref;
	char* ans=calloc(8,sizeof(char));
	for(i=2;i>=0;i--)
	{
		ref=(mode>>(i*3))&0x07;
		strcat(ans,param[ref]);
	}
	fprintf(stderr,"%s\n",ans);
	free(ans);
}
//S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH
void createfile(const char* path,mode_t cmask)
{
	if((creat(path,cmask)<0))
	{
		fprintf(stderr,"creat file error\n");
		return;
	}
}
