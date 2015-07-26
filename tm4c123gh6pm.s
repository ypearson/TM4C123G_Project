/* Memory Map ***********************************************************************/
/*
 * 0x0000:0000 - Beginning of FLASH. Address of vectors (if not using bootloader)
 * 0x0002:0000 - Address of vectors if using bootloader
 * 0x0003:ffff - End of flash
 * 0x2000:0000 - Start of SRAM and start of .data (_sdata)
 *             - End of .data (_edata) abd start of .bss (_sbss)
 *             - End of .bss (_ebss) and bottom of idle stack
 *             - _ebss + CONFIG_IDLETHREAD_STACKSIZE = end of idle stack, start of heap
 * 0x2000:ffff - End of SRAM and end of heap
 */

#define IDLE_STACK      (_ebss+CONFIG_IDLETHREAD_STACKSIZE-4)
#define HEAP_BASE       (_ebss+CONFIG_IDLETHREAD_STACKSIZE)

/************************************************************************************
 * Global Symbols
 ************************************************************************************/

    .syntax     unified
    .thumb
    .file       "tm4c123gh6pm.s"
    .globl      __start

/************************************************************************************
 * Macros
 ************************************************************************************/

/* On entry into an IRQ, the hardware automatically saves the xPSR, PC, LR, R12, R0-R3
 * registers on the stack, then branches to an instantantiation of the following
 * macro.  This macro simply loads the IRQ number into R0, then jumps to the common
 * IRQ handling logic.
 */

    .macro  HANDLER, label, irqno
    .thumb_func
\label:
    mov     r0, #\irqno
    b       exception_common
    .endm

/************************************************************************************
 * Vectors
 ************************************************************************************/

    .section    .vectors, "ax"
    .code       16
    .align      2
    .globl      _vectors
    .type       _vectors, function

_vectors:

    .long     Stack                       // Top of Stack
    .long     Reset_Handler               // Reset Handler
    .long     NMI_Handler                 // NMI Handler
    .long     HardFault_Handler           // Hard Fault Handler
    .long     MemManage_Handler           // MPU Fault Handler
    .long     BusFault_Handler            // Bus Fault Handler
    .long     UsageFault_Handler          // Usage Fault Handler
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     SVC_Handler                 // SVCall Handler
    .long     DebugMon_Handler            // Debug Monitor Handler
    .long     0                           // Reserved
    .long     PendSV_Handler              // PendSV Handler
    .long     SysTick_Handler             // SysTick Handler
    .long     GPIOPortA_Handler           // GPIO Port A
    .long     GPIOPortB_Handler           // GPIO Port B
    .long     GPIOPortC_Handler           // GPIO Port C
    .long     GPIOPortD_Handler           // GPIO Port D
    .long     GPIOPortE_Handler           // GPIO Port E
    .long     UART0_Handler               // UART0 Rx and Tx
    .long     UART1_Handler               // UART1 Rx and Tx
    .long     SSI0_Handler                // SSI0 Rx and Tx
    .long     I2C0_Handler                // I2C0 Master and Slave
    .long     PWM0Fault_Handler           // PWM 0 Fault
    .long     PWM0Generator0_Handler      // PWM 0 Generator 0
    .long     PWM0Generator1_Handler      // PWM 0 Generator 1
    .long     PWM0Generator2_Handler      // PWM 0 Generator 2
    .long     Quadrature0_Handler         // Quadrature Encoder 0
    .long     ADC0Seq0_Handler            // ADC0 Sequence 0
    .long     ADC0Seq1_Handler            // ADC0 Sequence 1
    .long     ADC0Seq2_Handler            // ADC0 Sequence 2
    .long     ADC0Seq3_Handler            // ADC0 Sequence 3
    .long     WDT_Handler                 // Watchdog
    .long     Timer0A_Handler             // Timer 0 subtimer A
    .long     Timer0B_Handler             // Timer 0 subtimer B
    .long     Timer1A_Handler             // Timer 1 subtimer A
    .long     Timer1B_Handler             // Timer 1 subtimer B
    .long     Timer2A_Handler             // Timer 2 subtimer A
    .long     Timer2B_Handler             // Timer 2 subtimer B
    .long     Comp0_Handler               // Analog Comp 0
    .long     Comp1_Handler               // Analog Comp 1
    .long     Comp2_Handler               // Analog Comp 2
    .long     SysCtl_Handler              // System Control
    .long     FlashCtl_Handler            // Flash Control
    .long     GPIOPortF_Handler           // GPIO Port F
    .long     GPIOPortG_Handler           // GPIO Port G
    .long     GPIOPortH_Handler           // GPIO Port H
    .long     UART2_Handler               // UART2 Rx and Tx
    .long     SSI1_Handler                // SSI1 Rx and Tx
    .long     Timer3A_Handler             // Timer 3 subtimer A
    .long     Timer3B_Handler             // Timer 3 subtimer B
    .long     I2C1_Handler                // I2C1 Master and Slave
    .long     Quadrature1_Handler         // Quadrature Encoder 1
    .long     CAN0_Handler                // CAN0
    .long     CAN1_Handler                // CAN1
    .long     CAN2_Handler                // CAN2
    .long     Ethernet_Handler            // Ethernet
    .long     Hibernate_Handler           // Hibernate
    .long     USB0_Handler                // USB0
    .long     PWM0Generator3_Handler      // PWM 0 Generator 3
    .long     uDMA_Handler                // uDMA Software Transfer
    .long     uDMA_Error                  // uDMA Error
    .long     ADC1Seq0_Handler            // ADC1 Sequence 0
    .long     ADC1Seq1_Handler            // ADC1 Sequence 1
    .long     ADC1Seq2_Handler            // ADC1 Sequence 2
    .long     ADC1Seq3_Handler            // ADC1 Sequence 3
    .long     I2S0_Handler                // I2S0
    .long     ExtBus_Handler              // External Bus Interface 0
    .long     GPIOPortJ_Handler           // GPIO Port J
    .long     GPIOPortK_Handler           // GPIO Port K
    .long     GPIOPortL_Handler           // GPIO Port L
    .long     SSI2_Handler                // SSI2 Rx and Tx
    .long     SSI3_Handler                // SSI3 Rx and Tx
    .long     UART3_Handler               // UART3 Rx and Tx
    .long     UART4_Handler               // UART4 Rx and Tx
    .long     UART5_Handler               // UART5 Rx and Tx
    .long     UART6_Handler               // UART6 Rx and Tx
    .long     UART7_Handler               // UART7 Rx and Tx
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     I2C2_Handler                // I2C2 Master and Slave
    .long     I2C3_Handler                // I2C3 Master and Slave
    .long     Timer4A_Handler             // Timer 4 subtimer A
    .long     Timer4B_Handler             // Timer 4 subtimer B
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     0                           // Reserved
    .long     Timer5A_Handler             // Timer 5 subtimer A
    .long     Timer5B_Handler             // Timer 5 subtimer B
    .long     WideTimer0A_Handler         // Wide Timer 0 subtimer A
    .long     WideTimer0B_Handler         // Wide Timer 0 subtimer B
    .long     WideTimer1A_Handler         // Wide Timer 1 subtimer A
    .long     WideTimer1B_Handler         // Wide Timer 1 subtimer B
    .long     WideTimer2A_Handler         // Wide Timer 2 subtimer A
    .long     WideTimer2B_Handler         // Wide Timer 2 subtimer B
    .long     WideTimer3A_Handler         // Wide Timer 3 subtimer A
    .long     WideTimer3B_Handler         // Wide Timer 3 subtimer B
    .long     WideTimer4A_Handler         // Wide Timer 4 subtimer A
    .long     WideTimer4B_Handler         // Wide Timer 4 subtimer B
    .long     WideTimer5A_Handler         // Wide Timer 5 subtimer A
    .long     WideTimer5B_Handler         // Wide Timer 5 subtimer B
    .long     FPU_Handler                 // FPU
    .long     PECI0_Handler               // PECI 0
    .long     LPC0_Handler                // LPC 0
    .long     I2C4_Handler                // I2C4 Master and Slave
    .long     I2C5_Handler                // I2C5 Master and Slave
    .long     GPIOPortM_Handler           // GPIO Port M
    .long     GPIOPortN_Handler           // GPIO Port N
    .long     Quadrature2_Handler         // Quadrature Encoder 2
    .long     Fan0_Handler                // Fan 0
    .long     0                           // Reserved
    .long     GPIOPortP_Handler           // GPIO Port P (Summary or P0)
    .long     GPIOPortP1_Handler          // GPIO Port P1
    .long     GPIOPortP2_Handler          // GPIO Port P2
    .long     GPIOPortP3_Handler          // GPIO Port P3
    .long     GPIOPortP4_Handler          // GPIO Port P4
    .long     GPIOPortP5_Handler          // GPIO Port P5
    .long     GPIOPortP6_Handler          // GPIO Port P6
    .long     GPIOPortP7_Handler          // GPIO Port P7
    .long     GPIOPortQ_Handler           // GPIO Port Q (Summary or Q0)
    .long     GPIOPortQ1_Handler          // GPIO Port Q1
    .long     GPIOPortQ2_Handler          // GPIO Port Q2
    .long     GPIOPortQ3_Handler          // GPIO Port Q3
    .long     GPIOPortQ4_Handler          // GPIO Port Q4
    .long     GPIOPortQ5_Handler          // GPIO Port Q5
    .long     GPIOPortQ6_Handler          // GPIO Port Q6
    .long     GPIOPortQ7_Handler          // GPIO Port Q7
    .long     GPIOPortR_Handler           // GPIO Port R
    .long     GPIOPortS_Handler           // GPIO Port S
    .long     PWM1Generator0_Handler      // PWM 1 Generator 0
    .long     PWM1Generator1_Handler      // PWM 1 Generator 1
    .long     PWM1Generator2_Handler      // PWM 1 Generator 2
    .long     PWM1Generator3_Handler      // PWM 1 Generator 3
    .long     PWM1Fault_Handler           // PWM 1 Fault


/************************************************************************************
 * .text
 ************************************************************************************/



.macro  HANDLER, label
    .thumb_func
\label:
    b       label
    .endm



    .text
    .type   handlers, function
    .thumb_func
handlers:
    HANDLER tiva_reserved        /* Unexpected/reserved vector */
    HANDLER tiva_nmi /* Vector  2: Non-Maskable Interrupt (NMI) */
    HANDLER tiva_hardfault      /* Vector  3: Hard fault */
    HANDLER tiva_mpu              /* Vector  4: Memory management (MPU) */
    HANDLER tiva_busfault        /* Vector  5: Bus fault */
    HANDLER tiva_usagefault    /* Vector  6: Usage fault */
    HANDLER tiva_svcall            /* Vector 11: SVC call */
    HANDLER tiva_dbgmonitor    /* Vector 12: Debug Monitor */
    HANDLER tiva_pendsv            /* Vector 14: Penable system service request */
    HANDLER tiva_systick          /* Vector 15: System tick */




NMI_Handler:
HardFault_Handler:
MemManage_Handler:
BusFault_Handler:
UsageFault_Handler:

/* Common IRQ handling logic.  On entry here, the return stack is on either
 * the PSP or the MSP and looks like the following:
 *
 *      REG_XPSR
 *      REG_R15
 *      REG_R14
 *      REG_R12
 *      REG_R3
 *      REG_R2
 *      REG_R1
 * MSP->REG_R0
 *
 * And
 *      R0 contains the IRQ number
 *      R14 Contains the EXC_RETURN value
 *      We are in handler mode and the current SP is the MSP
 */

    .globl      exception_common
    .type       exception_common, function
exception_common:

    /* Complete the context save */

#ifdef CONFIG_BUILD_PROTECTED
    /* The EXC_RETURN value will be 0xfffffff9 (privileged thread) or 0xfffffff1
     * (handler mode) if the stack is on the MSP.  It can only be on the PSP if
     * EXC_RETURN is 0xfffffffd (unprivileged thread)
     */

    tst     r14, #EXC_RETURN_PROCESS_STACK /* nonzero if context on process stack */
    beq     1f                      /* Branch if context already on the MSP */
    mrs     r1, psp                 /* R1=The process stack pointer (PSP) */
    mov     sp, r1                  /* Set the MSP to the PSP */

1:
#endif

    /* r1 holds the value of the stack pointer AFTER the excption handling logic
     * pushed the various registers onto the stack.  Get r2 = the value of the
     * stack pointer BEFORE the interrupt modified it.
     */

    mov     r2, sp                  /* R2=Copy of the main/process stack pointer */
    add     r2, #HW_XCPT_SIZE       /* R2=MSP/PSP before the interrupt was taken */
#ifdef CONFIG_ARMV7M_USEBASEPRI
    mrs     r3, basepri             /* R3=Current BASEPRI setting */
#else
    mrs     r3, primask             /* R3=Current PRIMASK setting */
#endif

#ifdef CONFIG_ARCH_FPU
    /* Skip over the block of memory reserved for floating pointer register save.
     * Lazy FPU register saving is used.  FPU registers will be saved in this
     * block only if a context switch occurs (this means, of course, that the FPU
     * cannot be used in interrupt processing).
     */

    sub     sp, #(4*SW_FPU_REGS)
#endif

    /* Save the remaining registers on the stack after the registers pushed
     * by the exception handling logic. r2=SP and r3=primask or basepri, r4-r11,
     * r14=register values.
     */

#ifdef CONFIG_BUILD_PROTECTED
    stmdb   sp!, {r2-r11,r14}       /* Save the remaining registers plus the SP value */
#else
    stmdb   sp!, {r2-r11}           /* Save the remaining registers plus the SP value */
#endif

#ifndef CONFIG_ARCH_HIPRI_INTERRUPT
    /* Disable interrupts, select the stack to use for interrupt handling
     * and call up_doirq to handle the interrupt
     */

    cpsid   i                       /* Disable further interrupts */

#else
    /* Set the BASEPRI register so that further normal interrupts will be
     * masked.  Nested, high priority may still occur, however.
     */

    mov     r2, #NVIC_SYSH_DISABLE_PRIORITY
    msr     basepri, r2             /* Set the BASEPRI */
#endif

    /* There are two arguments to up_doirq:
     *
     *   R0 = The IRQ number
     *   R1 = The top of the stack points to the saved state
     */

    mov     r1, sp

#if CONFIG_ARCH_INTERRUPTSTACK > 3
    /* If CONFIG_ARCH_INTERRUPTSTACK is defined, we will set the MSP to use
     * a special special interrupt stack pointer.  The way that this is done
     * here prohibits nested interrupts without some additional logic!
     */

    ldr     sp, =g_intstackbase
    str     r1, [sp, #-4]!          /* Save the MSP on the interrupt stack */
    bl      up_doirq                /* R0=IRQ, R1=register save (msp) */
    ldr     r1, [sp, #+4]!          /* Recover R1=main stack pointer */

#else
    /* Otherwise, we will re-use the interrupted thread's stack.  That may
     * mean using either MSP or PSP stack for interrupt level processing (in
     * kernel mode).
     */

    bl      up_doirq                /* R0=IRQ, R1=register save (msp) */
    mov     r1, sp                  /* Recover R1=main stack pointer */
#endif

    /* On return from up_doirq, R0 will hold a pointer to register context
     * array to use for the interrupt return.  If that return value is the same
     * as current stack pointer, then things are relatively easy.
     */

    cmp     r0, r1                  /* Context switch? */
    beq     2f                      /* Branch if no context switch */

    /* We are returning with a pending context switch.
     *
     * If the FPU is enabled, then we will need to restore FPU registers.
     * This is not done in normal interrupt save/restore because the cost
     * is prohibitive.  This is only done when switching contexts.  A
     * consequence of this is that floating point operations may not be
     * performed in interrupt handling logic.
     *
     * Here:
     *   r0 = Address of the register save area
    
     * NOTE: It is a requirement that up_restorefpu() preserve the value of
     * r0!
     */

#ifdef CONFIG_ARCH_FPU
    bl      up_restorefpu           /* Restore the FPU registers */
#endif

    /* We are returning with a pending context switch.  This case is different
     * because in this case, the register save structure does not lie in the
     * stack but, rather, within a TCB structure.  We'll have to copy some
     * values to the stack.
     */

    add     r1, r0, #SW_XCPT_SIZE   /* R1=Address of HW save area in reg array */
    ldmia   r1, {r4-r11}            /* Fetch eight registers in HW save area */
    ldr     r1, [r0, #(4*REG_SP)]   /* R1=Value of SP before interrupt */
    stmdb   r1!, {r4-r11}           /* Store eight registers in HW save area */
#ifdef CONFIG_BUILD_PROTECTED
    ldmia   r0, {r2-r11,r14}        /* Recover R4-R11, r14 + 2 temp values */
#else
    ldmia   r0, {r2-r11}            /* Recover R4-R11 + 2 temp values */
#endif
    b       3f                      /* Re-join common logic */

    /* We are returning with no context switch.  We simply need to "unwind"
     * the same stack frame that we created
     *
     * Here:
     *   r1 = Address of the return stack (same as r0)
     */

2:
#ifdef CONFIG_BUILD_PROTECTED
    ldmia   r1!, {r2-r11,r14}       /* Recover R4-R11, r14 + 2 temp values */
#else
    ldmia   r1!, {r2-r11}           /* Recover R4-R11 + 2 temp values */
#endif

#ifdef CONFIG_ARCH_FPU
    /* Skip over the block of memory reserved for floating pointer register
     * save. Then R1 is the address of the HW save area
     */

    add     r1, #(4*SW_FPU_REGS)
#endif

    /* Set up to return from the exception
     *
     * Here:
     *   r1 = Address on the target thread's stack position at the start of
     *        the registers saved by hardware
     *   r3 = primask or basepri
     *   r4-r11 = restored register values
     */

3:

#ifdef CONFIG_BUILD_PROTECTED
    /* The EXC_RETURN value will be 0xfffffff9 (privileged thread) or 0xfffffff1
     * (handler mode) if the stack is on the MSP.  It can only be on the PSP if
     * EXC_RETURN is 0xfffffffd (unprivileged thread)
     */

    mrs     r2, control             /* R2=Contents of the control register */
    tst     r14, #EXC_RETURN_PROCESS_STACK /* nonzero if context on process stack */
    beq     4f                      /* Branch if privileged */

    orr     r2, r2, #1              /* Unprivileged mode */
    msr     psp, r1                 /* R1=The process stack pointer */
    b       5f
4:
    bic     r2, r2, #1              /* Privileged mode */
    msr     msp, r1                 /* R1=The main stack pointer */
5:
    msr     control, r2             /* Save the updated control register */
#else
    msr     msp, r1                 /* Recover the return MSP value */

    /* Preload r14 with the special return value first (so that the return
     * actually occurs with interrupts still disabled).
     */

    ldr     r14, =EXC_RETURN_PRIVTHR    /* Load the special value */
#endif

    /* Restore the interrupt state */

#ifdef CONFIG_ARMV7M_USEBASEPRI
    msr     basepri, r3             /* Restore interrupts priority masking */
#ifndef CONFIG_ARCH_HIPRI_INTERRUPT
    cpsie   i                       /* Re-enable interrupts */
#endif

#else
    msr     primask, r3             /* Restore interrupts */
#endif

    /* Always return with R14 containing the special value that will: (1)
     * return to thread mode, and (2) continue to use the MSP
     */

    bx      r14                     /* And return */
    .size   handlers, .-handlers

/************************************************************************************
 *  Name: g_intstackalloc/g_intstackbase
 *
 * Description:
 *   Shouldn't happen
 *
 ************************************************************************************/

#if CONFIG_ARCH_INTERRUPTSTACK > 3
    .bss
    .global g_intstackalloc
    .global g_intstackbase
    .align  4
g_intstackalloc:
    .skip   (CONFIG_ARCH_INTERRUPTSTACK & ~3)
g_intstackbase:
    .size   g_intstackalloc, .-g_intstackalloc
#endif
#endif /* CONFIG_ARMV7M_CMNVECTOR */

/************************************************************************************
 * .rodata
 ************************************************************************************/

    .section    .rodata, "a"

/* Variables: _sbss is the start of the BSS region (see ld.script) _ebss is the end
 * of the BSS regsion (see ld.script). The idle task stack starts at the end of BSS
 * and is of size CONFIG_IDLETHREAD_STACKSIZE.  The IDLE thread is the thread that
 * the system boots on and, eventually, becomes the idle, do nothing task that runs
 * only when there is nothing else to run.  The heap continues from there until the
 * end of memory.  See g_idle_topstack below.
 */

    .globl  g_idle_topstack
    .type   g_idle_topstack, object
g_idle_topstack:
    .word   HEAP_BASE
    .size   g_idle_topstack, .-g_idle_topstack

    .end
