#ifndef LOG_H
#define LOG_H
extern int debug(const char*file,const char*tag,int line,const char*str,...)__attribute__((format(printf,4,5)));
extern int error(int r,const char*file,const char*tag,int line,const char*str,...)__attribute__((format(printf,5,6)));
extern int failure(int r,const char*file,const char*tag,int line,const char*str,...)__attribute__((format(printf,5,6)));
#define DEBUG(str...) debug(__FILE__,__func__,__LINE__,str)
#define ERROR(err,str...) error(err,__FILE__,__func__,__LINE__,str)
#define FAILURE(err,str...) failure(err,__FILE__,__func__,__LINE__,str)
#endif
