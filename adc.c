#include "tm4c123gh6pm.h"
#include "adc.h"

 #define PE2   (0x00000001u<<2)
 #define ADC0  (0x1u)
 #define AIN1  (0x1u)

// This initialization function sets up the ADC
// Max sample rate: <=125,000 samples/second
// SS3 triggering event: software trigger
// SS3 1st sample source:  channel 1
// SS3 interrupts: enabled but not promoted to controller
void adc0_init(void)
{
    // Module Init
    volatile uint32_t delay;

    SYSCTL_RCGCADC_R |= ADC0;
    delay = SYSCTL_RCGCADC_R;

    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
    delay = SYSCTL_RCGC2_R;

    GPIO_PORTE_DIR_R &= ~PE2;
    GPIO_PORTE_AFSEL_R |= PE2;
    GPIO_PORTE_PCTL_R = 0;
    GPIO_PORTE_DEN_R &= ~PE2;
    GPIO_PORTE_AMSEL_R |= PE2;

    ADC0_SSPRI_R &= ~ADC_SSPRI_SS3_M;
    ADC0_SSPRI_R |=  ADC_SSPRI_SS0_M;
    // Sample Sequencer Config
    ADC0_ACTSS_R &= ~(ADC_ACTSS_ASEN3|ADC_ACTSS_ASEN2|ADC_ACTSS_ASEN1|ADC_ACTSS_ASEN0);
    ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;
    ADC0_SSMUX3_R = AIN1;
    ADC0_SSCTL3_R = ADC_SSCTL3_END0;
    ADC0_ACTSS_R = ADC_ACTSS_ASEN3;
}

//------------ADC0_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t adc0_get_sample(void)
{
    unsigned long result = 0;
    while(ADC0_ACTSS_R & ADC_ACTSS_BUSY);
    ADC0_PSSI_R |= ADC_PSSI_SS3;
    while(ADC0_ACTSS_R & ADC_ACTSS_BUSY);
    result = (ADC0_SSFIFO3_R & ADC_SSFIFO3_DATA_M);
    return result;
}
