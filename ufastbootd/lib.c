#include<ctype.h>
#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<stdarg.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/time.h>
#include"defines.h"
#include"lib.h"
#include"log.h"

const char*size_units[]={"B","KiB","MiB","GiB","TiB","PiB","EiB","ZiB","YiB",NULL};

ssize_t write_file(int fd,const char*content,const char*file,...){
	va_list va;
	char path[PATH_MAX];
	if(!content||!file)return -1;
	memset(path,0,sizeof(path));
	va_start(va,file);
	vsnprintf(path,sizeof(path)-1,file,va);
	va_end(va);
	int f=openat(fd,path,O_WRONLY);
	if(f<0)return -1;
	ssize_t r=write(f,content,strlen(content));
	close(f);
	return r;
}

ssize_t writef_file(int fd,const char*file,const char*content,...){
	int f;
	va_list va;
	ssize_t r=-1;
	char*cont=NULL;
	if(!content||!file)return -1;
	va_start(va,content);
	vasprintf(&cont,content,va);
	va_end(va);
	if(!cont)return -1;
	if((f=openat(fd,file,O_WRONLY))>=0){
		r=write(f,cont,strlen(cont));
		close(f);
	}
	free(cont);
	return r;
}

ssize_t read_file(int fd,char*buff,size_t len,const char*file,...){
	va_list va;
	char path[PATH_MAX];
	if(!buff||!file||len<=0)return -1;
	memset(path,0,sizeof(path));
	va_start(va,file);
	vsnprintf(path,sizeof(path)-1,file,va);
	va_end(va);
	int f=openat(fd,path,O_RDONLY);
	if(f<0)return -1;
	memset(buff,0,len);
	ssize_t s=read(f,buff,len-1);
	if(s>0){
		if(buff[s-1]=='\n')buff[--s]=0;
		if(buff[s-1]=='\r')buff[--s]=0;
	}
	close(f);
	return s;
}

ssize_t full_write(int fd,const void*data,size_t len){
	ssize_t sent;
	size_t rxl=len;
	void*rxd=(void*)data;
	do{
		errno=0;
		sent=write(fd,rxd,rxl);
		if(sent<0&&errno!=EAGAIN&&errno!=EINTR)return sent;
		rxl-=sent,rxd+=sent;
	}while(rxl>0);
	return (ssize_t)len;
}

ssize_t full_read(int fd,void*data,size_t len){
	ssize_t sent;
	size_t rxl=len;
	void*rxd=data;
	do{
		errno=0;
		sent=read(fd,rxd,rxl);
		if(sent<0&&errno!=EAGAIN&&errno!=EINTR)return sent;
		rxl-=sent,rxd+=sent;
	}while(rxl>0);
	return (ssize_t)len;
}

uint64_t get_now_ms(){
	struct timeval tv_start;
	gettimeofday(&tv_start,NULL);
	return (tv_start.tv_sec*1000000+tv_start.tv_usec)/1000;
}

size_t s_strlcpy(char *buf,const char*src,size_t len){
	char*d0=buf;
	if(!len--)goto finish;
	for(;len&&(*buf=*src);len--,src++,buf++);
	*buf=0;
	finish:
	return buf-d0+strlen(src);
}

size_t s_strlcat(char*buf,const char*src,size_t len){
	size_t slen=strnlen(buf,len);
	return slen==len?
		(slen+strlen(src)):
		(slen+s_strlcpy(buf+slen,src,len-slen));
}

void*s_memdup(void*mem,size_t len){
	void*dup=malloc(len);
	if(!dup)EPRET(ENOMEM);
	memcpy(dup,mem,len);
	return dup;
}

const char*format_size(
	char*buf,size_t len,
	size_t val,
	size_t block,
	size_t display
){
	int unit=0;
	memset(buf,0,len);
	if(val==0)return strncpy(buf,"0",len-1);
	if(block>1)val*=block;
	if(display)val+=display/2,val/=display;
	else while((val>=1024))val/=1024,unit++;
	snprintf(buf,len-1,"%zu %s",val,size_units[unit]);
	return buf;
}
