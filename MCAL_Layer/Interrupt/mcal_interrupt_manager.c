/* 
 * File:   mcal_interrupt_manager.c
 * Author: Ahmad Paykli
 *
 * Created on February 1, 2026, 12:55 PM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 flag_check_RB4 = 1, flag_check_RB5 = 1, flag_check_RB6 = 1, flag_check_RB7 = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
void __interrupt() InterruptManagerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF) && (INTCON3bits.INT1IP)){
        INT1_ISR();
    }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF) && (INTCON3bits.INT2IP)){
        INT2_ISR();
    }
    else{/* Nothing */}
    
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF) && (IPR1bits.ADIP)){
        ADC_ISR();
    }
    else{/* Nothing */}
    
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF) && (INTCON2bits.TMR0IP)){
        TMR0_ISR();
    }
    else{/* Nothing */}
    
    /* ============ TMR1 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF) && (IPR1bits.TMR1IP)){
        TMR1_ISR();
    }
    else{/* Nothing */}
    /* ============ TMR1 Internal Interrupt End ============ */
    
    /* ============ TMR2 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF) && (IPR1bits.TMR2IP)){
        TMR2_ISR();
    }
    else{/* Nothing */}
    /* ============ TMR2 Internal Interrupt End ============ */
    
    /* ============ TMR3 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF) && (IPR2bits.TMR3IP)){
        TMR3_ISR();
    }
    else{/* Nothing */}
    /* ============ TMR3 Internal Interrupt End ============ */
    
    /* ============ CCP1 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF) && (IPR1bits.CCP1IP)){
        CCP1_ISR();
    }
    else{/* Nothing */}
    /* ============ CCP1 Internal Interrupt End ============ */
    
    /* ============ CCP2 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF) && (IPR2bits.CCP2IP)){
        CCP2_ISR();
    }
    else{/* Nothing */}
    /* ============ CCP2 Internal Interrupt End ============ */
}

void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF) && (!(INTCON3bits.INT1IP))){
        INT1_ISR();
    }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF) && (!(INTCON3bits.INT2IP))){
        INT2_ISR();
    }
    else{/* Nothing */}
    
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF) && (!(IPR1bits.ADIP))){
        ADC_ISR();
    }
    else{/* Nothing */}
    
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF) && (!(INTCON2bits.TMR0IP))){
        TMR0_ISR();
    }
    else{/* Nothing */}
    
     /* ============ TMR1 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF) && (!(IPR1bits.TMR1IP))){
        TMR1_ISR();
    }
    else{/* Nothing */}
    /* ============ TMR1 Internal Interrupt End ============ */
    
    /* ============ TMR2 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF) && (!(IPR1bits.TMR2IP))){
        TMR2_ISR();
    }
    else{/* Nothing */}
    /* ============ TMR2 Internal Interrupt End ============ */
    
    /* ============ TMR3 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF) && (!(IPR2bits.TMR3IP))){
        TMR3_ISR();
    }
    else{/* Nothing */}
    /* ============ TMR3 Internal Interrupt End ============ */
    
    /* ============ CCP1 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF) && (!(IPR1bits.CCP1IP))){
        CCP1_ISR();
    }
    else{/* Nothing */}
    /* ============ CCP1 Internal Interrupt End ============ */
    
    /* ============ CCP2 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF) && (!(IPR2bits.CCP2IP))){
        CCP2_ISR();
    }
    else{/* Nothing */}
    /* ============ CCP2 Internal Interrupt End ============ */
}
#else
void __interrupt() InterruptManager(void){ 
    /* ============ INTx External Interrupt Start ============ */
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{/* Nothing */}
    /* ============ INTx External Interrupt End ============ */
    
    /* ============ PortB External On Change Interrupt Start ============ */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&& (PORTBbits.RB4 == GPIO_HIGH) && (1 == flag_check_RB4)){
        flag_check_RB4 = 0;
        RB4_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&& (PORTBbits.RB4 == GPIO_LOW) && (0 == flag_check_RB4)){
        flag_check_RB4 = 1;
        RB4_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&& (PORTBbits.RB5 == GPIO_HIGH) && (1 == flag_check_RB5)){
        flag_check_RB5 = 0;
        RB5_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&& (PORTBbits.RB5 == GPIO_LOW) && (0 == flag_check_RB5)){
        flag_check_RB5 = 1;
        RB5_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&& (PORTBbits.RB6 == GPIO_HIGH) && (1 == flag_check_RB6)){
        flag_check_RB6 = 0;
        RB6_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&& (PORTBbits.RB6 == GPIO_LOW) && (0 == flag_check_RB6)){
        flag_check_RB6 = 1;
        RB6_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&& (PORTBbits.RB7 == GPIO_HIGH) && (1 == flag_check_RB7)){
        flag_check_RB7 = 0;
        RB7_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&& (PORTBbits.RB7 == GPIO_LOW) && (0 == flag_check_RB7)){
        flag_check_RB7 = 1;
        RB7_ISR(0);
    }
    else{/* Nothing */}
    /* ============ PortB External On Change Interrupt End ============ */
    
    /* ============ ADC Internal Interrupt Start ============ */
     if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF)){
        ADC_ISR();
    }
    else{/* Nothing */}
    /* ============ ADC Internal Interrupt End ============ */
    
    /* ============ TMR0 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
        TMR0_ISR();
    }
    else{/* Nothing */}
    /* ============ TMR0 Internal Interrupt End ============ */
    
    /* ============ TMR1 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF)){
        TMR1_ISR();
    }
    else{/* Nothing */}
    /* ============ TMR1 Internal Interrupt End ============ */
    
    /* ============ TMR2 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF)){
        TMR2_ISR();
    }
    else{/* Nothing */}
    /* ============ TMR2 Internal Interrupt End ============ */   

    /* ============ TMR3 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF)){
        TMR3_ISR();
    }
    else{/* Nothing */}
    /* ============ TMR3 Internal Interrupt End ============ */
    
    /* ============ CCP1 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF)){
        CCP1_ISR();
    }
    else{/* Nothing */}
    /* ============ CCP1 Internal Interrupt End ============ */
    
    /* ============ CCP2 Internal Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF)){
        CCP2_ISR();
    }
    else{/* Nothing */}
    /* ============ CCP2 Internal Interrupt End ============ */    
}
#endif