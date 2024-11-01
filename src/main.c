#include<stdio.h>
#include<stddef.h>
#include<getopt.h>
#include"fastboot.h"
#include"log.h"

static int usage(int e){
	fprintf(
		e==0?stdout:stderr,
		"Usage: ufastbootd [OPTIONS]\n"
		"Userspace Fastboot Daemon for Linux.\n\n"
		"Options:\n"
		"\t-p, --path <PATH>      Path to fastboot functionfs mountpoint\n"
		"\t-h, --help             Display this help and exit\n"
	);
}

int main(int argc,char**argv){
	static const struct option lo[]={
		{"help",    no_argument,       NULL,'h'},
		{"path",    required_argument, NULL,'p'},
		{NULL,0,NULL,0}
	};
	int o,ret;
	const char*ffs=NULL;
	while((o=getopt_long(argc,argv,"hp:",lo,NULL))>0)switch(o){
		case 'h':return usage(0);
		case 'p':ffs=optarg;break;
		default:return usage(1);
	}
	if(optind>argc)return usage(1);
	if(!ffs)return ERROR(1,"no functionfs path specified");
	if((ret=fastboot_init(ffs))!=0)return ret;
	fastboot_join();
	fastboot_stop();
	return 0;
}
