/*
 *
 * Copyright (C) 2022 BigfootACA <bigfoot@classfun.cn>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 *
 */

#include<stdio.h>
#include<errno.h>
#include<stdarg.h>
#include<unistd.h>
#include<string.h>
#include"log.h"
#include"lib.h"

static int out_fd=STDERR_FILENO;

#define DEBUG_TAG 1

#if DEBUG_TAG == 1
static char*append_tag(
	char*buff,size_t len,
	const char*file __attribute__((unused)),
	const char*func,
	int line __attribute__((unused))
){
	#if DEBUG_LOCATION == 1
	if(file){
		s_strlcat(buff,file,len-1);
		s_strlcat(buff,"@",len-1);
	}
	#endif
	s_strlcat(buff,func,len-1);
	#if DEBUG_LOCATION == 1
	if(line>0){
		size_t l=strlen(buff);
		snprintf(buff+l,len-l-1,":%d",line);
	}
	#endif
	return buff;
}
#endif

int debug(const char*file,const char*tag,int line,const char*str,...){
	va_list va;
	char buf[BUFSIZ];
	memset(buf,0,sizeof(buf));
	#if DEBUG_TAG == 1
	append_tag(buf,sizeof(buf),file,tag,line);
	s_strlcat(buf,": ",sizeof(buf)-1);
	#endif
	size_t tl=strlen(buf);
	va_start(va,str);
	vsnprintf(buf+tl,sizeof(buf)-tl-1,str,va);
	va_end(va);
	write(out_fd,buf,strlen(buf));
	return 0;
}
static int _error(
	int r,int l,
	const char*file,
	const char*tag,
	int line,
	const char*str,
	va_list va
){
	int err=errno;
	ssize_t tl,bs;
	char buf[BUFSIZ];
	memset(buf,0,sizeof(buf));
	#if DEBUG_TAG == 1
	append_tag(buf,sizeof(buf),file,tag,line);
	s_strlcat(buf,": ",sizeof(buf)-1);
	#endif
	tl=strlen(buf),bs=sizeof(buf)-tl-2;
	vsnprintf(buf+tl,bs,str,va);
	if(err!=0){
		tl=strlen(buf),bs=sizeof(buf)-tl-2;
		if(bs>0)snprintf(buf+tl,bs,": %s",strerror(err));
	}
	strcat(buf,"\n");
	write(out_fd,buf,strlen(buf));
	return r==0?err:r;
}

int error(
	int r,
	const char*file,
	const char*tag,
	int line,
	const char*str,...
){
	va_list va;
	va_start(va,str);
	int e=_error(r,3,file,tag,line,str,va);
	va_end(va);
	return e;
}

int failure(
	int r,
	const char*file,
	const char*tag,
	int line,
	const char*str,...
){
	va_list va;
	va_start(va,str);
	int e=_error(r,0,file,tag,line,str,va);
	va_end(va);
	_exit(e);
	return e;
}
