/* Memory Map ***********************************************************************/
/*
 * 0x0000:0000 - Beginning of FLASH. Address of vectors (if not using bootloader)
 * 0x0002:0000 - Address of vectors if using bootloader
 * 0x0003:ffff - End of flash
 * 0x2000:0000 - Start of SRAM and start of .data (_sdata)
 *             - End of .data (_edata) and start of .bss (_sbss)
 *             - End of .bss (_ebss) and bottom of idle stack
 *             - _ebss + CONFIG_IDLETHREAD_STACKSIZE = end of idle stack, start of heap
 * 0x2000:ffff - End of SRAM and end of heap
 */

#define STACK (_ebss + 4096)

/************************************************************************************
 * Global Symbols
 ************************************************************************************/

    .SYNTAX     unified
    .CPU        cortex-m4
    .THUMB
    .FILE       "tm4c123gh6pm.s"
    .GLOBL      __start

/************************************************************************************
 * Vectors
 ************************************************************************************/

    .section    .vectors, "ax"
    .code       16
    .align      2
    .globl      _vectors
    .type       _vectors, function

_vectors:

    .long     (_ebss + 4096)              /* Top of Stack */
    .long     Reset_Handler               /* Reset Handler */
    .long     NMI_Handler                 /* NMI Handler */
    .long     HardFault_Handler           /* Hard Fault Handler */
    .long     MemManage_Handler           /* MPU Fault Handler */
    .long     BusFault_Handler            /* Bus Fault Handler */
    .long     UsageFault_Handler          /* Usage Fault Handler */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     SVC_Handler                 /* SVCall Handler */
    .long     DebugMon_Handler            /* Debug Monitor Handler */
    .long     0                           /* Reserved */
    .long     PendSV_Handler              /* PendSV Handler */
    .long     SysTick_Handler             /* SysTick Handler */
    .long     GPIOPortA_Handler           /* GPIO Port A */
    .long     GPIOPortB_Handler           /* GPIO Port B */
    .long     GPIOPortC_Handler           /* GPIO Port C */
    .long     GPIOPortD_Handler           /* GPIO Port D */
    .long     GPIOPortE_Handler           /* GPIO Port E */
    .long     UART0_Handler               /* UART0 Rx and Tx */
    .long     UART1_Handler               /* UART1 Rx and Tx */
    .long     SSI0_Handler                /* SSI0 Rx and Tx */
    .long     I2C0_Handler                /* I2C0 Master and Slave */
    .long     PWM0Fault_Handler           /* PWM 0 Fault */
    .long     PWM0Generator0_Handler      /* PWM 0 Generator 0 */
    .long     PWM0Generator1_Handler      /* PWM 0 Generator 1 */
    .long     PWM0Generator2_Handler      /* PWM 0 Generator 2 */
    .long     Quadrature0_Handler         /* Quadrature Encoder 0 */
    .long     ADC0Seq0_Handler            /* ADC0 Sequence 0 */
    .long     ADC0Seq1_Handler            /* ADC0 Sequence 1 */
    .long     ADC0Seq2_Handler            /* ADC0 Sequence 2 */
    .long     ADC0Seq3_Handler            /* ADC0 Sequence 3 */
    .long     WDT_Handler                 /* Watchdog */
    .long     Timer0A_Handler             /* Timer 0 subtimer A  */
    .long     Timer0B_Handler             /* Timer 0 subtimer B */
    .long     Timer1A_Handler             /* Timer 1 subtimer A */
    .long     Timer1B_Handler             /* Timer 1 subtimer B */
    .long     Timer2A_Handler             /* Timer 2 subtimer A */
    .long     Timer2B_Handler             /* Timer 2 subtimer B */
    .long     Comp0_Handler               /* Analog Comp 0 */
    .long     Comp1_Handler               /* Analog Comp 1 */
    .long     Comp2_Handler               /* Analog Comp 2 */
    .long     SysCtl_Handler              /* System Control */
    .long     FlashCtl_Handler            /* Flash Control */
    .long     GPIOPortF_Handler           /* GPIO Port F */
    .long     GPIOPortG_Handler           /* GPIO Port G */
    .long     GPIOPortH_Handler           /* GPIO Port H */
    .long     UART2_Handler               /* UART2 Rx and Tx */
    .long     SSI1_Handler                /* SSI1 Rx and Tx */
    .long     Timer3A_Handler             /* Timer 3 subtimer A */
    .long     Timer3B_Handler             /* Timer 3 subtimer B */
    .long     I2C1_Handler                /* I2C1 Master and Slave */
    .long     Quadrature1_Handler         /* Quadrature Encoder 1 */
    .long     CAN0_Handler                /* CAN0 */
    .long     CAN1_Handler                /* CAN1 */
    .long     CAN2_Handler                /* CAN2 */
    .long     Ethernet_Handler            /* Ethernet */
    .long     Hibernate_Handler           /* Hibernate */
    .long     USB0_Handler                /* USB0 */
    .long     PWM0Generator3_Handler      /* PWM 0 Generator 3 */
    .long     uDMA_Handler                /* uDMA Software Transfer */
    .long     uDMA_Error                  /* uDMA Error */
    .long     ADC1Seq0_Handler            /* ADC1 Sequence 0 */
    .long     ADC1Seq1_Handler            /* ADC1 Sequence 1 */
    .long     ADC1Seq2_Handler            /* ADC1 Sequence 2 */
    .long     ADC1Seq3_Handler            /* ADC1 Sequence 3 */
    .long     I2S0_Handler                /* I2S0 */
    .long     ExtBus_Handler              /* External Bus Interface 0 */
    .long     GPIOPortJ_Handler           /* GPIO Port J */
    .long     GPIOPortK_Handler           /* GPIO Port K */
    .long     GPIOPortL_Handler           /* GPIO Port L */
    .long     SSI2_Handler                /* SSI2 Rx and Tx */
    .long     SSI3_Handler                /* SSI3 Rx and Tx */
    .long     UART3_Handler               /* UART3 Rx and Tx */
    .long     UART4_Handler               /* UART4 Rx and Tx */
    .long     UART5_Handler               /* UART5 Rx and Tx */
    .long     UART6_Handler               /* UART6 Rx and Tx */
    .long     UART7_Handler               /* UART7 Rx and Tx */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     I2C2_Handler                /* I2C2 Master and Slave */
    .long     I2C3_Handler                /* I2C3 Master and Slave */
    .long     Timer4A_Handler             /* Timer 4 subtimer A */
    .long     Timer4B_Handler             /* Timer 4 subtimer B */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     0                           /* Reserved */
    .long     Timer5A_Handler             /* Timer 5 subtimer A */
    .long     Timer5B_Handler             /* Timer 5 subtimer B */
    .long     WideTimer0A_Handler         /* Wide Timer 0 subtimer A */
    .long     WideTimer0B_Handler         /* Wide Timer 0 subtimer B */
    .long     WideTimer1A_Handler         /* Wide Timer 1 subtimer A */
    .long     WideTimer1B_Handler         /* Wide Timer 1 subtimer B */
    .long     WideTimer2A_Handler         /* Wide Timer 2 subtimer A */
    .long     WideTimer2B_Handler         /* Wide Timer 2 subtimer B */
    .long     WideTimer3A_Handler         /* Wide Timer 3 subtimer A */
    .long     WideTimer3B_Handler         /* Wide Timer 3 subtimer B */
    .long     WideTimer4A_Handler         /* Wide Timer 4 subtimer A */
    .long     WideTimer4B_Handler         /* Wide Timer 4 subtimer B */
    .long     WideTimer5A_Handler         /* Wide Timer 5 subtimer A */
    .long     WideTimer5B_Handler         /* Wide Timer 5 subtimer B */
    .long     FPU_Handler                 /* FPU */
    .long     PECI0_Handler               /* PECI 0 */
    .long     LPC0_Handler                /* LPC 0 */
    .long     I2C4_Handler                /* I2C4 Master and Slave */
    .long     I2C5_Handler                /* I2C5 Master and Slave */
    .long     GPIOPortM_Handler           /* GPIO Port M */
    .long     GPIOPortN_Handler           /* GPIO Port N */
    .long     Quadrature2_Handler         /* Quadrature Encoder 2 */
    .long     Fan0_Handler                /* Fan 0 */
    .long     0                           /* Reserved */
    .long     GPIOPortP_Handler           /* GPIO Port P (Summary or P0) */
    .long     GPIOPortP1_Handler          /* GPIO Port P1 */
    .long     GPIOPortP2_Handler          /* GPIO Port P2 */
    .long     GPIOPortP3_Handler          /* GPIO Port P3 */
    .long     GPIOPortP4_Handler          /* GPIO Port P4 */
    .long     GPIOPortP5_Handler          /* GPIO Port P5 */
    .long     GPIOPortP6_Handler          /* GPIO Port P6 */
    .long     GPIOPortP7_Handler          /* GPIO Port P7 */
    .long     GPIOPortQ_Handler           /* GPIO Port Q (Summary or Q0) */
    .long     GPIOPortQ1_Handler          /* GPIO Port Q1 */
    .long     GPIOPortQ2_Handler          /* GPIO Port Q2 */
    .long     GPIOPortQ3_Handler          /* GPIO Port Q3 */
    .long     GPIOPortQ4_Handler          /* GPIO Port Q4 */
    .long     GPIOPortQ5_Handler          /* GPIO Port Q5 */
    .long     GPIOPortQ6_Handler          /* GPIO Port Q6 */
    .long     GPIOPortQ7_Handler          /* GPIO Port Q7 */
    .long     GPIOPortR_Handler           /* GPIO Port R */
    .long     GPIOPortS_Handler           /* GPIO Port S */
    .long     PWM1Generator0_Handler      /* PWM 1 Generator 0 */
    .long     PWM1Generator1_Handler      /* PWM 1 Generator 1 */
    .long     PWM1Generator2_Handler      /* PWM 1 Generator 2 */
    .long     PWM1Generator3_Handler      /* PWM 1 Generator 3 */
    .long     PWM1Fault_Handler           /* PWM 1 Fault */


/************************************************************************************/
.macro  HANDLER, label
    .thumb_func
\label:
    b       \label
    .endm

    .text
    .type   handlers, function
    .thumb_func
handlers:
    HANDLER Reserved_Handler        /* Unexpected/reserved vector */
    HANDLER NMI_Handler             /* Vector  2: Non-Maskable Interrupt (NMI) */
    HANDLER HardFault_Handler       /* Vector  3: Hard fault */
    HANDLER MemManage_Handler       /* Vector  4: Memory management (MPU) */
    HANDLER BusFault_Handler        /* Vector  5: Bus fault */
    HANDLER UsageFault_Handler      /* Vector  6: Usage fault */
    HANDLER SVC_Handler             /* Vector 11: SVC call */
    HANDLER DebugMon_Handler        /* Vector 12: Debug Monitor */
    HANDLER PendSV_Handler          /* Vector 14: Penable system service request */

/************************************************************************************/

        .weak LowLevelInit
        .weak SystemInit

        .macro   FUNCTION name
        .func    \name,\name
        .type    \name,%function
        .thumb_func
        .align
\name\():
        .endm

        .macro  ENDFUNC name
        .size   \name, . - \name
        .pool
        .endfunc
        .endm

    FUNCTION    Reset_Handler
/*
        ldr                 r0,=LowLevelInit
        cmp                 r0,#0
        it                  ne
        blxne               r0

        ldr                 r0,=SystemInit
        cmp                 r0,#0
        it                  ne
        blxne               r0


        ldr                 r1,=_sdata
        ldr                 r2,=__sram_data_start__
        ldr                 r3,=__sram_data_end__
        bl                  copy

        movs                r0,#0
        ldr                 r1,=__bss_start__
        ldr                 r2,=__bss_end__

LoopZI: cmp                 r1,r2
        it                  cc
        strlo               r0,[r1],#4
        blo                 LoopZI
*/
/* Start main() */

        ldr    r0,=main
        blx    r0
        b      Reserved_Handler

copy:
        cmp                 r2,r3                       /* check if we've reached the end */
        it                  cc
        ldrlo               r0,[r1],#4                  /* if end not reached, get word and advance source pointer */
        it                  cc
        strlo               r0,[r2],#4                  /* if end not reached, store word and advance destination pointer */
        blo                 copy                        /* if end not reached, branch back to loop */
        bx                  lr                          /* return to caller */

    ENDFUNC    Reset_Handler

/************************************************************************************/

.macro  INTHANDLER, INT
.weakref \INT, Reserved_Handler
.endm

    .text
    .type   inthandlers, function
    .thumb_func

inthandlers:
    INTHANDLER SysTick_Handler
    INTHANDLER GPIOPortA_Handler
    INTHANDLER GPIOPortB_Handler
    INTHANDLER GPIOPortC_Handler
    INTHANDLER GPIOPortD_Handler
    INTHANDLER GPIOPortE_Handler
    INTHANDLER UART0_Handler
    INTHANDLER UART1_Handler
    INTHANDLER SSI0_Handler
    INTHANDLER I2C0_Handler
    INTHANDLER PWM0Fault_Handler
    INTHANDLER PWM0Generator0_Handler
    INTHANDLER PWM0Generator1_Handler
    INTHANDLER PWM0Generator2_Handler
    INTHANDLER Quadrature0_Handler
    INTHANDLER ADC0Seq0_Handler
    INTHANDLER ADC0Seq1_Handler
    INTHANDLER ADC0Seq2_Handler
    INTHANDLER ADC0Seq3_Handler
    INTHANDLER WDT_Handler
    INTHANDLER Timer0A_Handler
    INTHANDLER Timer0B_Handler
    INTHANDLER Timer1A_Handler
    INTHANDLER Timer1B_Handler
    INTHANDLER Timer2A_Handler
    INTHANDLER Timer2B_Handler
    INTHANDLER Comp0_Handler
    INTHANDLER Comp1_Handler
    INTHANDLER Comp2_Handler
    INTHANDLER SysCtl_Handler
    INTHANDLER FlashCtl_Handler
    INTHANDLER GPIOPortF_Handler
    INTHANDLER GPIOPortG_Handler
    INTHANDLER GPIOPortH_Handler
    INTHANDLER UART2_Handler
    INTHANDLER SSI1_Handler
    INTHANDLER Timer3A_Handler
    INTHANDLER Timer3B_Handler
    INTHANDLER I2C1_Handler
    INTHANDLER Quadrature1_Handler
    INTHANDLER CAN0_Handler
    INTHANDLER CAN1_Handler
    INTHANDLER CAN2_Handler
    INTHANDLER Ethernet_Handler
    INTHANDLER Hibernate_Handler
    INTHANDLER USB0_Handler
    INTHANDLER PWM0Generator3_Handler
    INTHANDLER uDMA_Handler
    INTHANDLER uDMA_Error
    INTHANDLER ADC1Seq0_Handler
    INTHANDLER ADC1Seq1_Handler
    INTHANDLER ADC1Seq2_Handler
    INTHANDLER ADC1Seq3_Handler
    INTHANDLER I2S0_Handler
    INTHANDLER ExtBus_Handler
    INTHANDLER GPIOPortJ_Handler
    INTHANDLER GPIOPortK_Handler
    INTHANDLER GPIOPortL_Handler
    INTHANDLER SSI2_Handler
    INTHANDLER SSI3_Handler
    INTHANDLER UART3_Handler
    INTHANDLER UART4_Handler
    INTHANDLER UART5_Handler
    INTHANDLER UART6_Handler
    INTHANDLER UART7_Handler
    INTHANDLER I2C2_Handler
    INTHANDLER I2C3_Handler
    INTHANDLER Timer4A_Handler
    INTHANDLER Timer4B_Handler
    INTHANDLER Timer5A_Handler
    INTHANDLER Timer5B_Handler
    INTHANDLER WideTimer0A_Handler
    INTHANDLER WideTimer0B_Handler
    INTHANDLER WideTimer1A_Handler
    INTHANDLER WideTimer1B_Handler
    INTHANDLER WideTimer2A_Handler
    INTHANDLER WideTimer2B_Handler
    INTHANDLER WideTimer3A_Handler
    INTHANDLER WideTimer3B_Handler
    INTHANDLER WideTimer4A_Handler
    INTHANDLER WideTimer4B_Handler
    INTHANDLER WideTimer5A_Handler
    INTHANDLER WideTimer5B_Handler
    INTHANDLER FPU_Handler
    INTHANDLER PECI0_Handler
    INTHANDLER LPC0_Handler
    INTHANDLER I2C4_Handler
    INTHANDLER I2C5_Handler
    INTHANDLER GPIOPortM_Handler
    INTHANDLER GPIOPortN_Handler
    INTHANDLER Quadrature2_Handler
    INTHANDLER Fan0_Handler
    INTHANDLER GPIOPortP_Handler
    INTHANDLER GPIOPortP1_Handler
    INTHANDLER GPIOPortP2_Handler
    INTHANDLER GPIOPortP3_Handler
    INTHANDLER GPIOPortP4_Handler
    INTHANDLER GPIOPortP5_Handler
    INTHANDLER GPIOPortP6_Handler
    INTHANDLER GPIOPortP7_Handler
    INTHANDLER GPIOPortQ_Handler
    INTHANDLER GPIOPortQ1_Handler
    INTHANDLER GPIOPortQ2_Handler
    INTHANDLER GPIOPortQ3_Handler
    INTHANDLER GPIOPortQ4_Handler
    INTHANDLER GPIOPortQ5_Handler
    INTHANDLER GPIOPortQ6_Handler
    INTHANDLER GPIOPortQ7_Handler
    INTHANDLER GPIOPortR_Handler
    INTHANDLER GPIOPortS_Handler
    INTHANDLER PWM1Generator0_Handler
    INTHANDLER PWM1Generator1_Handler
    INTHANDLER PWM1Generator2_Handler
    INTHANDLER PWM1Generator3_Handler
    INTHANDLER PWM1Fault_Handler
/************************************************************************************/
