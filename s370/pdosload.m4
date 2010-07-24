//PDPMVS   JOB CLASS=C,REGION=0K
//*
//PDPASM   PROC MEMBER=''
//ASM      EXEC PGM=ASMA90,
//   PARM='DECK,LIST'
//*SYSLIB   DD DSN=TEMP.DSS.MAC,DISP=SHR
//SYSLIB   DD DSN=SYS1.MACLIB,DISP=SHR
//         DD DSN=&&MACLIB,DISP=(OLD,PASS)
//         DD DSN=SYS1.MODGEN,DISP=SHR
//SYSUT1   DD UNIT=SYSALLDA,SPACE=(CYL,(20,10))
//SYSUT2   DD UNIT=SYSALLDA,SPACE=(CYL,(20,10))
//SYSUT3   DD UNIT=SYSALLDA,SPACE=(CYL,(20,10))
//SYSPRINT DD SYSOUT=*
//SYSLIN   DD DUMMY
//SYSGO    DD DUMMY
//SYSPUNCH DD DSN=&&OBJSET,UNIT=SYSALLDA,SPACE=(80,(200,200)),
//            DISP=(,PASS)
//*
//LKED     EXEC PGM=IEWL,PARM='NCAL',
//            COND=(4,LT,ASM)
//SYSLIN   DD DSN=&&OBJSET,DISP=(OLD,DELETE)
//SYSLMOD  DD DSN=&&NCALIB(&MEMBER),DISP=(OLD,PASS)
//SYSUT1   DD UNIT=SYSALLDA,SPACE=(CYL,(2,1))
//SYSPRINT DD SYSOUT=*
//         PEND
//CREATE   EXEC PGM=IEFBR14
//DD12     DD DSN=&&NCALIB,DISP=(,PASS),
// DCB=(RECFM=U,LRECL=0,BLKSIZE=3200),
// SPACE=(CYL,(1,1,20)),UNIT=SYSALLDA
//DD13     DD DSN=&&LOADLIB,DISP=(,PASS),
// DCB=(RECFM=U,LRECL=0,BLKSIZE=3200),
// SPACE=(CYL,(1,1,20)),UNIT=SYSALLDA
//DD14     DD DSN=&&MACLIB,DISP=(,PASS),
// DCB=(RECFM=FB,LRECL=80,BLKSIZE=3120),
// SPACE=(CYL,(1,1,20)),UNIT=SYSALLDA
//*
//PDPTOP   EXEC PGM=IEBGENER
//SYSUT2   DD  DSN=&&MACLIB(PDPTOP),DISP=(OLD,PASS)
//SYSUT1   DD  *
undivert(pdptop.mac)/*
//SYSPRINT DD  SYSOUT=*
//SYSIN    DD  DUMMY
//*
//PDPPRLG  EXEC PGM=IEBGENER
//SYSUT2   DD  DSN=&&MACLIB(PDPPRLG),DISP=(OLD,PASS)
//SYSUT1   DD  *
undivert(pdpprlg.mac)/*
//SYSPRINT DD  SYSOUT=*
//SYSIN    DD  DUMMY
//*
//PDPEPIL  EXEC PGM=IEBGENER
//SYSUT2   DD  DSN=&&MACLIB(PDPEPIL),DISP=(OLD,PASS)
//SYSUT1   DD  *
undivert(pdpepil.mac)/*
//SYSPRINT DD  SYSOUT=*
//SYSIN    DD  DUMMY
//*
//MVSMACS  EXEC PGM=IEBGENER
//SYSUT2   DD  DSN=&&MACLIB(MVSMACS),DISP=(OLD,PASS)
//SYSUT1   DD  *
undivert(mvsmacs.mac)/*
//SYSPRINT DD  SYSOUT=*
//SYSIN    DD  DUMMY
//*
//SAPSTART EXEC PDPASM,MEMBER=SAPSTART
//SYSIN  DD  *
undivert(sapstart.asm)/*
//SAPSUPA  EXEC PDPASM,MEMBER=SAPSUPA
//SYSIN  DD  *
undivert(sapsupa.asm)/*
//START    EXEC PDPASM,MEMBER=START
//SYSIN  DD *
undivert(start.s)/*
//STDIO    EXEC PDPASM,MEMBER=STDIO
//SYSIN  DD *
undivert(stdio.s)/*
//STDLIB   EXEC PDPASM,MEMBER=STDLIB
//SYSIN  DD  *
undivert(stdlib.s)/*
//CTYPE    EXEC PDPASM,MEMBER=CTYPE
//SYSIN  DD  *
undivert(ctype.s)/*
//STRING   EXEC PDPASM,MEMBER=STRING
//SYSIN  DD  *
undivert(string.s)/*
//TIME     EXEC PDPASM,MEMBER=TIME
//SYSIN  DD  *
undivert(time.s)/*
//ERRNO    EXEC PDPASM,MEMBER=ERRNO
//SYSIN  DD  *
undivert(errno.s)/*
//ASSERT   EXEC PDPASM,MEMBER=ASSERT
//SYSIN  DD  *
undivert(assert.s)/*
//LOCALE   EXEC PDPASM,MEMBER=LOCALE
//SYSIN  DD  *
undivert(locale.s)/*
//MATH     EXEC PDPASM,MEMBER=MATH
//SYSIN  DD  *
undivert(math.s)/*
//SETJMP   EXEC PDPASM,MEMBER=SETJMP
//SYSIN  DD  *
undivert(setjmp.s)/*
//SIGNAL   EXEC PDPASM,MEMBER=SIGNAL
//SYSIN  DD  *
undivert(signal.s)/*
//@@MEMMGR EXEC PDPASM,MEMBER=@@MEMMGR
//SYSIN  DD  *
undivert(__memmgr.s)/*
//PDOSLOAD EXEC PDPASM,MEMBER=PDOSLOAD
//SYSIN  DD  *
undivert(pdosload.s)/*
//LKED     EXEC PGM=IEWL,PARM='MAP,LIST'
//SYSLIN   DD DDNAME=SYSIN
//SYSLIB   DD DSN=TEMP.DSS.LOAD,DISP=SHR
//         DD DSN=&&NCALIB,DISP=(OLD,PASS)
//SYSLMOD  DD DSN=&&LOADLIB(PDOSLOAD),DISP=(OLD,PASS)
//SYSUT1   DD UNIT=SYSALLDA,SPACE=(CYL,(2,1))
//SYSPRINT DD SYSOUT=*
//SYSIN DD *
 INCLUDE SYSLIB(SAPSTART)
 INCLUDE SYSLIB(START)
 INCLUDE SYSLIB(SAPSUPA)
 INCLUDE SYSLIB(STDIO)
 INCLUDE SYSLIB(STDLIB)
 INCLUDE SYSLIB(CTYPE)
 INCLUDE SYSLIB(STRING)
 INCLUDE SYSLIB(TIME)
 INCLUDE SYSLIB(ERRNO)
 INCLUDE SYSLIB(ASSERT)
 INCLUDE SYSLIB(LOCALE)
 INCLUDE SYSLIB(MATH)
 INCLUDE SYSLIB(SETJMP)
 INCLUDE SYSLIB(SIGNAL)
 INCLUDE SYSLIB(@@MEMMGR)
 INCLUDE SYSLIB(PDOSLOAD)
 ENTRY @@MAIN
/*
//*
//PDOSLOAD  EXEC PGM=LOADZERO,PARM='dd:pds(PDOSLOAD) PDOSLOAD dd:out'
//STEPLIB  DD  DSN=MVSSRC.OZPD.LINKLIB,DISP=SHR
//* &&LOADLIB,DISP=(OLD,PASS)
//PDS      DD  DSN=&&LOADLIB,DISP=(OLD,PASS)
//OUT      DD  DSN=&&LMOD,DISP=(,PASS),SPACE=(CYL,(10,10)),
//         UNIT=SYSALLDA,DCB=(RECFM=U,LRECL=0,BLKSIZE=18452)
//SYSPRINT DD  SYSOUT=*
//SYSTERM  DD  SYSOUT=*
//SYSIN    DD  DUMMY
//SYSUDUMP DD  SYSOUT=*
//*
//HEXDUMP  EXEC PGM=HEXDUMP,PARM='DD:IN'
//STEPLIB  DD  DSN=PDPCLIB.LINKLIB,DISP=SHR
//SYSIN    DD  DUMMY
//*SYSPRINT DD  SYSOUT=*
//SYSPRINT DD  DSN=HERC02.IEBCOPY,DISP=(,KEEP),UNIT=TAPE,
//         LABEL=(1,SL),VOL=SER=MFTOPC,
//         DCB=(RECFM=F,LRECL=80,BLKSIZE=8000)
//SYSTERM  DD  SYSOUT=*
//IN       DD  DSN=&&LMOD,DISP=(OLD,PASS)
//*
//