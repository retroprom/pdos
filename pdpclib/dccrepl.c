/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards, kerravon@w3.to             */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  dccrepl - replace DCC lines generated by GCC 3.2 with 370        */
/*  assembler.  Yes, it should really have been done as an           */
/*  assembler macro.  When I learn how to write assembler macros,    */
/*  I'll keep you in the loop. :-)                                   */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

static int tprintf(const char *format, ...);

int main(int argc, char **argv)
{
    char buf[200];
    char *d;
    char *e;
    char *f;
    char *p;
    int frame;
    int csects = 0;
    int numregs = 1;

    if (argc > 1)
    {
        numregs = atoi(*(argv + 1));
    }
    while (fgets(buf, sizeof buf, stdin) != NULL)
    {
        d = strstr(buf, "DCCPRLG");
        if (strstr(buf, "'") != NULL) d = NULL;
        if (d != NULL)
        {
            frame = 0;
            e = strstr(buf, "ENTRY=YES");
            f = strstr(buf, "FRAME");
            if (f != NULL)
            {
                frame = atoi(f + 6);
            }
            if (e != NULL)
            {
                p = strchr(buf, '\t');
                if (p != NULL)
                {
                    *p = '\0';
                    tprintf("\tENTRY\t%s\n", buf);
                    *p = '\t';
                }
            }
            strcpy(d, "CSECT\n");
            tprintf("%s", buf);
            tprintf("\tUSING\t*,12");
            if (numregs > 1)
            {
                tprintf(",7");
            }
            if (numregs > 2)
            {
                tprintf(",8");
            }
            if (numregs > 3)
            {
                tprintf(",9");
            }
            tprintf("\n");
            tprintf("\tSAVE\t(14,12)");
            p = strchr(buf, '\t');
            if (p != NULL)
            {
                *p = '\0';
                tprintf(",,%s_&SYSDATE", buf);
                *p = '\t';
            }
            tprintf("\n");
            tprintf("\tLR\t12,15\n");
            
            if (numregs > 1)
            {
                tprintf("\tLR\t7,12\n");
                tprintf("\tLA\t7,2048(7)\n");
                tprintf("\tLA\t7,2048(7)\n");
            }
            if (numregs > 2)
            {
                tprintf("\tLA\t8,2048(7)\n");
                tprintf("\tLA\t8,2048(8)\n");
            }
            if (numregs > 3)
            {
                tprintf("\tLA\t9,2048(8)\n");
                tprintf("\tLA\t9,2048(9)\n");
            }
            
            tprintf("\tL\t15,76(13)\n");
            tprintf("\tST\t13,4(15)\n");
            tprintf("\tST\t15,8(13)\n");
            tprintf("\tLR\t13,15\n");
            tprintf("\tA\t15,=F'%d'\n", frame);
            tprintf("\tST\t15,76(13)\n");
        }
        else if (((d = strstr(buf, "DCCEPIL")) != NULL)
                 && (strstr(buf, "'") == NULL))
        {
            tprintf("\tL\t13,4(13)\n");
            strcpy(d, "RETURN (14,12),RC=(15)\n");
            tprintf("%s", buf);
        }
        else if (strncmp(buf, "@FRAMESIZE_", 11) == 0)
        {
            tprintf("*");
            buf[10] = '@';
            tprintf("%s", buf);
        }
        else if ((strstr(buf, "CSECT") != NULL)
                 && (strchr("@$", buf[0]) != NULL))
        {
            csects++;
            tprintf("*");
            tprintf("%s", buf);
            if (csects == 1)
            {
                tprintf("\tCSECT\n");
            }
        }
        else if (buf[0] == '*')
        {
            if (strlen(buf) > 65)
            {
                strcpy(buf + 60, "\n");
            }
            tprintf("%s", buf);
        }
        else
        {
            tprintf("%s", buf);
        }
    }
    return (0);
}

static int tprintf(const char *format, ...)
{
    va_list arg;
    char buf[300];
    size_t icnt;
    size_t ocnt;

    va_start(arg, format);
    vsprintf(buf, format, arg);
    va_end(arg);
    ocnt = icnt = 0;
    while (buf[icnt] != '\0')
    {
        if (buf[icnt] == '\t')
        {
            if (ocnt < 9)
            {
                for (; ocnt < 9; ocnt++)
                {
                    putchar(' ');
                }
            }
            else if (ocnt < 15)
            {
                for (; ocnt < 15; ocnt++)
                {
                    putchar(' ');
                }
            }
            else
            {
                putchar(' ');
            }
        }
        else
        {
            putchar(buf[icnt]);
            ocnt++;
        }
        icnt++;
    }
    return (ocnt);
}
