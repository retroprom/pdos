/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards, 3:711/934@fidonet.         */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  stddef.h - assert header file.                                   */
/*                                                                   */
/*********************************************************************/

#ifndef __STDDEF_INCLUDED
#define __STDDEF_INCLUDED

typedef int ptrdiff_t;
#ifndef __SIZE_T_DEFINED
#define __SIZE_T_DEFINED
#if (defined(__OS2__) || defined(__32BIT__) || defined(__MVS__))
typedef unsigned long size_t;
#endif
#if (defined(__MSDOS__) || defined(__DOS__) || defined(__POWERC))
typedef unsigned int size_t;
#endif
#endif
#ifndef __WCHAR_T_DEFINED
#define __WCHAR_T_DEFINED
typedef char wchar_t;
#endif

#define NULL ((void *)0)
#define offsetof(x, y) (size_t)&(((x *)0)->y)

#endif
