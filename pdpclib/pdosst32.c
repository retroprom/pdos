/* Startup code for PDOS */
/* written by Paul Edwards */
/* released to the public domain */

/* We can get away with a minimal startup code, plus make it
   a C program.  Do not put any string literals in here though,
   as the code needs to start immediately.  This is IT!  */

#include <pos.h>

#ifdef __WATCOMC__
#define CTYP __cdecl
#else
#define CTYP
#endif

int __pstart(int *i1, int *i2, int *i3, POS_EPARMS *exep);

int CTYP __pdosst32(int i1, int i2, int i3, void *exep)
{
    int rc;

    rc = __pstart(&i1, &i2, &i3, exep);
    return (rc);
}
