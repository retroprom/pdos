/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  pdos.c - Public Domain Operating System                          */
/*  (version for S/370, S/380 and S/390 IBM mainframes)              */
/*                                                                   */
/*  When this (main) program is entered, interrupts are disabled,    */
/*  and the program should not assume anything about the status of   */
/*  low memory - ie this program needs to set the interrupt vectors, */
/*  initialize timer, and enable interrupts.                         */
/*                                                                   */
/*  To cope with multitasking, and multiple CPUs, from the outset,   */
/*  the following strategy is being used:                            */
/*                                                                   */
/*  Given that most time is spent in an application, rather than     */
/*  doing OS work, we can envision that 4 CPUs are busy doing some   */
/*  calculations, e.g. LA R2,7(R2). They each have their own version */
/*  of the registers, and they have each been loaded in advance      */
/*  with virtual memory settings that only give access to real       */
/*  memory that doesn't clash with any other CPU.                    */
/*                                                                   */
/*  Each of those CPUs can generate an interrupt at any time, by     */
/*  executing an illegal instruction, or having an expired timer,    */
/*  or requesting a service.                                         */
/*                                                                   */
/*  Each time there is an interrupt, interrupts will be switched     */
/*  off. The CPU receiving the interrupt needs to save its           */
/*  registers, and return to the point at which it last dispatched   */
/*  some interruptable work.                                         */
/*                                                                   */
/*  So a function like dispatch_until_interrupt() should be called,  */
/*  and it is expected to return with an interrupt identifier.       */
/*                                                                   */
/*  Since the interrupt may be a program check etc, this task        */
/*  should remain suspended until the interrupt has been             */
/*  analyzed. So what we're after is:                                */
/*                                                                   */
/*  while (!time_to_terminate)                                       */
/*  {                                                                */
/*      dispatch_until_interrupt();                                  */
/*      if (interrupt == ILLEGAL_INSTRUCTION) time_to_terminate = 1; */
/*      else if (interrupt == TIMER)                                 */
/*      {                                                            */
/*          checkElapsedTimeAgainstAllowedTime();                    */
/*          if (over_time_limit) time_to_terminate = 1;              */
/*      }                                                            */
/*  }                                                                */
/*                                                                   */
/*  In order to effect this simplicity, what that                    */
/*  dispatch_until_interrupt function translates into is:            */
/*                                                                   */
/*  LPSW of user's application code, with interrupts enabled.        */
/*  All interrupts point to the address after that LPSW.             */
/*                                                                   */
/*  Registers are provided and loaded prior to execution of the      */
/*  LPSW. The LPSW will refer to an address in low memory so that    */
/*  the (now invalid) register 0 can be used.                        */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef {
    int abend;
} TASK;

static int intrupt;

int main(int argc, char **argv)
{
    TASK *task;

    printf("Welcome to PDOS!!!\n");
    init();
    
    /* The OS is not designed to exit */
    while (1)
    {
        /* all this will be done with interrupts disabled,
           and in supervisor status */
        task  = getNextAvailTask();
        if (task == NULL)
        {
            /* suspend the computer until an interrupt occurs */
            goWaitState();
        }
        
        sliceOver = 0;
        while (!sliceOver)
        {
            sliceOver = 1; /* assume any interrupt will be the end
                              of this timeslice. */
        
            /* If the task has abended, the equivalent of a
               branch to user-space code is done, to perform
               the cleanup, as this is an expensive operation,
               so should be timesliced. */
            intrupt = dispatch_until_interrupt();
            if (intrupt == INTERRUPT_TIMER)
            {
                /* this will check how long the program has been
                   running for, and if the limit has been reached,
                   the context will be switched to an abend routine,
                   which will be dispatched at the next timeslice. */
                checkElapsedTime();
            }
        
            else if (intrupt == INTERRUPT_ILLEGAL)
            {
                /* this function will switch the context to an abend
                   handler to do the dump, timesliced. */
                processIllegal();
            }
        
            else if (intrupt == INTERRUPT_SVC)
            {
                /* This function switches context to an SVC handler,
                   but it won't actually execute it until the next
                   timeslice, to avoid someone doing excessive
                   SVCs that hog the CPU. It will execute in
                   supervisor status when eventually dispatched though. */
                startSVC();
            }
        
            else if (intrupt == INTERRUPT_IO)
            {
                /* This running app shouldn't have to pay the price
                   for someone else's I/O completing. */
                
                saveTimer();
                
                processIO();
                
                /* If the timeslice has less than 10% remaining, it
                   isn't worth dispatching again. Otherwise, set
                   this slice to be run again. */
                if (resetTimer())
                {
                    sliceOver = 0;
                }
            }
        }
    }
    return (0);
}