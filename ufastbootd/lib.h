#ifndef LIB_H
#define LIB_H
#include<stdint.h>
#include<stddef.h>
#define memdup s_memdup
extern void*s_memdup(void*mem,size_t len);
extern size_t s_strlcpy(char *buf,const char*src,size_t len);
extern size_t s_strlcat(char*buf,const char*src,size_t len);
extern const char*format_size(char*buf,size_t len,size_t val,size_t block,size_t display);
extern uint64_t get_now_ms(void);
extern ssize_t full_read(int fd,void*data,size_t len);
extern ssize_t full_write(int fd,const void*data,size_t len);
extern ssize_t read_file(int fd,char*buff,size_t len,const char*file,...)__attribute__((format(printf,4,5)));
extern ssize_t write_file(int fd,const char*content,const char*file,...)__attribute__((format(printf,3,4)));
extern ssize_t writef_file(int fd,const char*file,const char*content,...)__attribute__((format(printf,3,4)));
#endif
