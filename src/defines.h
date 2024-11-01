#ifndef DEFINES_H
#define DEFINES_H
#define O_DIR O_RDONLY|O_DIRECTORY
#ifndef MIN
#define MIN(a,b)((b)>(a)?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b)((b)<(a)?(a):(b))
#endif

#define ALIGN(val,alg) ((val)+(((alg)-(val))&((alg)-1)))
#define ARRLEN(x)(sizeof(x)/sizeof((x)[0]))
#define ERET(e){return -(errno=(e));}
#define EXRET(e){if(errno==0)errno=e;return -(errno);}
#define EPRET(e){errno=(e);return NULL;}
#define EGOTO(err,str...) {\
	e=ERROR(err,str);\
	goto fail;\
}
#define ERGOTO(err,str...){\
	ERROR(-1,str);\
	errno=err;\
	goto fail;\
}
#define EXGOTO(err,str...){\
	int _er=errno;\
	ERROR(-1,str);\
	errno=_er?:err;\
	goto fail;\
}
#define ENGOTO(err) {\
	errno=err;\
	goto fail;\
}
#endif
