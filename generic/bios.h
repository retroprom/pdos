/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  bios.h - C library exported by BIOS                              */
/*                                                                   */
/*********************************************************************/

#include <stddef.h>

typedef struct {
    void *mem_base;
    size_t mem_amt;
    char *disk_name;
    int (*printf)(const char *format, ...);
    void *(*fopen)(const char *filename, const char *mode);
    int (*fseek)(void *stream, long offset, int whence);
    size_t (*fread)(void *ptr, size_t size, size_t nmemb, void *stream);
    int (*fclose)(void *stream);
    size_t (*fwrite)(const void *ptr, size_t size, size_t nmemb, void *stream);
    char *(*fgets)(char *s, int n, void *stream);
    void *Xstdin;
    void *Xstdout;
    int (*fflush)(void *stream);
    int (*setvbuf)(void *stream, char *buf, int mode, size_t size);
} BIOS;
