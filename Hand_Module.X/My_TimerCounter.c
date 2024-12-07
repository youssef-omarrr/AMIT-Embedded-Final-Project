#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include"My_TimerCounter.h"
#include "DIO.h"

/**
 * @return void
 * @param clk : division clock of MC by 1,8,64,265,1024, external clock or turn off timer 
 */
void Timer0_setClk(char clk) {

    TCCR0 &= ~((1 << CS00) | (1 << CS01) | (1 << CS02)); //clearing clk bits
    _delay_us(10);

    TCCR0 |= clk;

}

/**
 * @return void
 * @param Mode : normal,ctc,pwm,fast pwm
 */
void Timer0_setMode(char Mode) {

    TCCR0 &= ~((1 << WGM00) | (1 << WGM01));
    _delay_us(10);

    switch (Mode) {

    case NORMAL_MODE:
        TCCR0 &= ~((1 << WGM00) | (1 << WGM01));
        break;

    case PWM_MODE:
        TCCR0 |= (1 << WGM00);
        break;

    case CTC_MODE:
        TCCR0 |= (1 << WGM01);
        break;

    case FAST_PWM_MODE:
        TCCR0 |= ((1 << WGM00) | (1 << WGM01));
        break;

    default:
        break;

    }

}

/**
 * Function to Enable overflow interrupt timer0
 */
void Timer0_INT_EN_TOVF() {

    TIMSK |= (1 << TOIE0);

}

/**
 * Function to Enable O/P compare match interrupt timer0
 */
void Timer0_INT_EN_OCM() {

    TIMSK |= (1 << OCIE0);

}

/**
 * 
 * @param OC0_MODE
 * @return void
 */
void Timer0_COMP_MODE(char OC0_MODE) {

    TCCR0 &= ~((1 << COM00) | (1 << COM01));
    _delay_us(10);

    TCCR0 |= (OC0_MODE << 4);

}

/**
 * set direction of OC0 pin & select mode
 * @param MODE : mode of ctc
 * @return void
 */
void Timer0_init_OC0() {

    setPIN_dir(B, OC0, OUT);
    _delay_us(10);


}

/**
 * @return void
 * @param OCR0_TOP_VAL
 */
void Change_OCR0(char OCR0_TOP_VAL) {

    OCR0 = OCR0_TOP_VAL;

}

/**
 * @return void
 * @param Mode :PWM,FAST PWM,CTC modes
 * @param clk
 */
void init_Timer0_WithOCR0(char Mode, char clk, char OCR0_Val) {


    Timer0_setMode(Mode);

    _delay_ms(10);
    Change_OCR0(OCR0_Val);

    switch (Mode) {


    case FAST_PWM_MODE:
        Timer0_INT_EN_TOVF();
        Timer0_INT_EN_OCM();
        break;

    case PWM_MODE:
    case CTC_MODE:
        //        Timer0_INT_EN_OCM();
        break;

    default:
        break;
    }

    _delay_ms(5);
    Timer0_setClk(clk);


}

/**
 * @return void
 * @param clk
 */
void initNormalMode_Timer_Counter0(char clk) {


    Timer0_setMode(NORMAL_MODE);


    Timer0_INT_EN_TOVF();

    _delay_ms(10);

    Timer0_setClk(clk);


}

void Timer0_waitCTC() {
    while (!(TIFR & (1 << OCF0)));
    TCNT0 = 0;
}
////////////////////////////////////////////////////TIMER2//////////////////////////////////////////////

/**
 * @return void
 * @param clk : division clock of MC by 1,8,32,64,128,265,1024 
 */
void Timer2_setClk(char clk) {

    TCCR2 &= ~((1 << CS20) | (1 << CS21) | (1 << CS22)); //clearing clk bits
    _delay_us(10);

    TCCR2 |= clk;

}

/**
 * @return void
 * @param Mode : normal,ctc,pwm,fast pwm
 */
void Timer2_setMode(char Mode) {

    TCCR2 &= ~((1 << WGM20) | (1 << WGM21));
    _delay_us(10);

    switch (Mode) {

    case NORMAL_MODE:
        TCCR2 &= ~((1 << WGM20) | (1 << WGM21));
        break;

    case PWM_MODE:
        TCCR2 |= (1 << WGM20);
        break;

    case CTC_MODE:
        TCCR2 |= (1 << WGM21);
        break;

    case FAST_PWM_MODE:
        TCCR2 |= ((1 << WGM20) | (1 << WGM21));
        break;

    default:
        break;

    }

}

/**
 * Function to Enable overflow interrupt timer2
 */
void Timer2_INT_EN_TOVF() {

    TIMSK |= (1 << TOIE2);

}

/**
 * Function to Enable O/P compare match interrupt timer2
 */
void Timer2_INT_EN_OCM() {

    TIMSK |= (1 << OCIE2);

}

/**
 * 
 * @param OC2_MODE
 * @return void
 */
void Timer2_COMP_MODE(char OC2_MODE) {

    TCCR2 &= ~((1 << COM20) | (1 << COM21));
    _delay_us(10);

    TCCR2 |= (OC2_MODE << 4);

}

/**
 * set direction of OC2 pin & select mode
 * @param MODE : mode of ctc
 * @return void
 */
void Timer2_init_OC2() {

    setPIN_dir(D, OC2, OUT);
    _delay_us(10);


}

/**
 * @return void
 * @param OCR2_TOP_VAL
 */
void Change_OCR2(char OCR2_TOP_VAL) {

    OCR2 = OCR2_TOP_VAL;

}

/**
 * @return void
 * @param Mode :PWM,FAST PWM,CTC modes
 * @param clk
 */
void init_Timer2_WithOCR2(char Mode, char clk, char OCR2_Val) {


    Timer2_setMode(Mode);

    _delay_ms(10);
    Change_OCR2(OCR2_Val);

    switch (Mode) {


    case FAST_PWM_MODE:
        Timer2_INT_EN_TOVF();
        Timer2_INT_EN_OCM();
        break;

    case PWM_MODE:
    case CTC_MODE:
        Timer2_INT_EN_OCM();
        break;

    default:
        break;
    }

    _delay_ms(5);
    Timer2_setClk(clk);


}

/**
 * @return void
 * @param clk
 */
void initNormalMode_Timer_Counter2(char clk) {

    Timer2_setMode(NORMAL_MODE);
    Timer2_INT_EN_TOVF();
    _delay_ms(10);
    Timer2_setClk(clk);
    TWCR &= ~(1 << TWIE);
    
}

void Timer2_INT_DISABLE_OCM(void) {

    TIMSK &= ~(1 << OCIE2);

}

void Timer2_INT_DISABLE_TOVF(void) {

    TIMSK &= ~(1 << TOIE2);

}

void WAIT_UNTIL_LOAD_DATA_TIMER2() {

    while (!(ASSR & (1 << TCN2UB)));
    while (!(ASSR & (1 << TCR2UB)));
    while (!(ASSR & (1 << OCR2UB)));


}

void Clear_Timer2_Flags() {

    TIFR &= ~((1 << OCF2) | (1 << TOV2));

}

void ChangeBet_SyncAsync(char SyncAsync, char TCNT2_VAL, char Mode, char clk, char OCR2_VAL) {

    Timer2_INT_DISABLE_OCM();
    Timer2_INT_DISABLE_TOVF();

    switch (SyncAsync) {

    case ASync_To_sync:
        ASSR &= ~(1 << AS2);

        TCNT2 = TCNT2_VAL;

        switch (Mode) {

        case NORMAL_MODE:
            initNormalMode_Timer_Counter2(clk);
            Change_OCR2(0);
            break;

        case PWM_MODE:
        case FAST_PWM_MODE:
        case CTC_MODE:
            init_Timer2_WithOCR2(Mode, clk, OCR2_VAL);
            break;

        default:
            break;


        }

        Clear_Timer2_Flags();

        break;

    case Sync_To_Async:
        ASSR |= (1 << AS2);
        TCNT2 = TCNT2_VAL;

        switch (Mode) {

        case NORMAL_MODE:
            initNormalMode_Timer_Counter2(clk);
            Change_OCR2(0);
            break;

        case PWM_MODE:
        case FAST_PWM_MODE:
        case CTC_MODE:
            init_Timer2_WithOCR2(Mode, clk, OCR2_VAL);
            break;

        default:
            break;


        }

        WAIT_UNTIL_LOAD_DATA_TIMER2();

        Clear_Timer2_Flags();
        break;

    }

}

////////////////////////////////////////////////////TIMER1////////////////////////////////////////////////

/**
 * @return void
 * @param clk : division clock of MC by 1,8,64,265,1024, external clock or turn off timer 
 */
void Timer1_setClk(char clk) {

    TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12)); //clearing clk bits
    _delay_us(10);

    TCCR1B |= clk;

}

/**
 * @return void
 * @param Mode : normal,ctc,pwm,fast pwm
 */
void Timer1_setMode(char Mode) {

    TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
    TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
    _delay_us(10);

    switch (Mode) {

    case NORMAL_MODE:
        TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
        TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
        break;

    case PWM_MODE_8bits:
        TCCR1A |= (1 << WGM10);
        break;

    case PWM_MODE_9bits:
        TCCR1A |= (1 << WGM11);
        break;

    case PWM_MODE_10bits:
        TCCR1A |= ((1 << WGM10) | (1 << WGM11));
        break;

    case CTC_MODE_TOPisOCR1A:
        TCCR1B |= (1 << WGM12);
        break;

    case FAST_PWM_MODE_8bits:
        TCCR1B |= (1 << WGM12);
        TCCR1A |= (1 << WGM10);
        break;

    case FAST_PWM_MODE_9bits:
        TCCR1B |= (1 << WGM12);
        TCCR1A |= (1 << WGM11);
        break;

    case FAST_PWM_MODE_10bits:
        TCCR1B |= (1 << WGM12);
        TCCR1A |= ((1 << WGM10) | (1 << WGM11));
        break;

    case PWM_MODE_FREQ_TOPisICR1:
        TCCR1B |= (1 << WGM13);
        break;

    case PWM_MODE_FREQ_TOPisOCR1A:
        TCCR1B |= (1 << WGM13);
        TCCR1A |= (1 << WGM10);
        break;

    case PWM_MODE_TOPisICR1:
        TCCR1B |= (1 << WGM13);
        TCCR1A |= (1 << WGM11);
        break;

    case PWM_MODE_TOPisOCR1A:
        TCCR1B |= (1 << WGM13);
        TCCR1A |= ((1 << WGM10) | (1 << WGM11));
        break;

    case CTC_MODE_TOPisICR1:
        TCCR1B |= ((1 << WGM13) | (1 << WGM12));
        break;

    case FAST_PWM_MODE_TOPisICR1:
        TCCR1B |= ((1 << WGM13) | (1 << WGM12));
        TCCR1A |= (1 << WGM11);
        break;

    case FAST_PWM_MODE_TOPisOCR1A:
        TCCR1B |= ((1 << WGM13) | (1 << WGM12));
        TCCR1A |= ((1 << WGM10) | (1 << WGM11));
        break;

    default:
        break;

    }

}

/**
 * Function to Enable overflow interrupt timer1
 */
void Timer1_INT_EN_TOVF() {

    TIMSK |= (1 << TOIE1);

}

/**
 * Function to Enable O/P compare match interrupt timer1
 */
void Timer1_INT_EN_OCMA() {

    TIMSK |= (1 << OCIE1A);

}

/**
 * Function to Enable O/P compare match interrupt timer1
 */
void Timer1_INT_EN_OCMB() {

    TIMSK |= (1 << OCIE1B);

}

/**
 * Function to Enable O/P I/P Capture interrupt timer1
 */
void Timer1_INT_EN_ICR1() {

    TIMSK |= (1 << TICIE1);

}

void Timer1_INT_DISABLE_TOVF() {

    TIMSK &= ~(1 << TOIE1);

}

/**
 * 
 * @param OC1_MODE
 * @return void
 */
void Timer1_COMP_MODE(char OC1_MODE) {

    TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));
    _delay_us(10);

    TCCR1A |= (OC1_MODE << COM1B0);
    TCCR1A |= (OC1_MODE << COM1A0);

}

/**
 * set direction of OC1A and OC1B pin & select mode
 * @param MODE : mode of ctc
 * @return void
 */
void Timer1_init_OC1() {

    setPIN_dir(D, OC1A, OUT);
    setPIN_dir(D, OC1B, OUT);
    _delay_us(10);


}

/**
 * @return void
 * @param OCR1A_TOP_VAL
 */
void Change_OCR1A(char OCR1A_TOP_VAL) {

    OCR1A = OCR1A_TOP_VAL;

}

/**
 * @return void
 * @param OCR1A_TOP_VAL
 */
void Change_OCR1B(char OCR1B_TOP_VAL) {

    OCR1B = OCR1B_TOP_VAL;

}

/**
 * @return void
 * @param Mode :PWM,FAST PWM,CTC modes
 * @param clk
 */
void init_Timer1_WithOCR1A_AND_B(char Mode, char clk, char OCR1A_Val, char OCR1B_Val) {


    Timer1_setMode(Mode);

    _delay_ms(10);
    Change_OCR1A(OCR1A_Val);
    Change_OCR1B(OCR1B_Val);


    Timer1_INT_EN_TOVF();

    switch (Mode) {


    case CTC_MODE_TOPisICR1:
        Timer1_INT_DISABLE_TOVF();
        Timer1_INT_EN_ICR1();
        break;

    case CTC_MODE_TOPisOCR1A:
        Timer1_INT_DISABLE_TOVF();
        Timer1_INT_EN_OCMA();
        break;

    case FAST_PWM_MODE_TOPisICR1:
        Timer1_INT_EN_ICR1();
        break;

    case FAST_PWM_MODE_TOPisOCR1A:
        Timer1_INT_EN_OCMA();
        break;

    case PWM_MODE_FREQ_TOPisICR1:
        Timer1_INT_EN_ICR1();
        break;

    case PWM_MODE_FREQ_TOPisOCR1A:
        Timer1_INT_EN_OCMA();
        break;

    case PWM_MODE_TOPisICR1:
        Timer1_INT_EN_ICR1();
        break;

    case PWM_MODE_TOPisOCR1A:
        Timer1_INT_EN_OCMA();
        break;

    case FAST_PWM_MODE_8bits:
    case FAST_PWM_MODE_9bits:
    case FAST_PWM_MODE_10bits:

    case PWM_MODE_8bits:
    case PWM_MODE_9bits:
    case PWM_MODE_10bits:
        Timer1_INT_EN_OCMA();
        break;

    default:
        break;
    }

    _delay_ms(5);
    Timer1_setClk(clk);


}

/**
 * @return void
 * @param clk
 */
void initNormalMode_Timer_Counter1(char clk) {


    Timer1_setMode(NORMAL_MODE);


    Timer1_INT_EN_TOVF();

    _delay_ms(10);

    Timer1_setClk(clk);


}

//////////////////////Input_Capture_Unit///////////////////////////////

/**
 * Enable ICP1 pin as an i/p pin
 */
void ICP1_EN() {

    setPIN_dir(D, ICP1, IN);
    _delay_us(10);

}

void Timer1_INT_Disable_ICR1() {

    TIMSK &= ~(1 << TICIE1);

}

/**
 * Clears Input Capture Interrupt Flag
 */
void Clear_ICF1() {

    TIFR &= ~(1 << ICF1);

}

/**
 * @return void
 * @param Source : Analog Comparator, ICP1
 */
void Timer1_Change_TrigSource(char Source) {

    switch (Source) {

    case AC_SOURCE:
        ACSR |= (1 << ACIC);
        break;

    case ICP1_SOURCE:
        ACSR &= ~(1 << ACIC);

    default:
        break;

    }

    Clear_ICF1();

}

/**
 * Enables Analog Comparator Interrupt
 */
void AC_INT_EN() {

    ACSR |= (1 << ACIE);
    _delay_us(10);

}

void Timer1_Enable_NoiseCanceler() {

    TCCR1B |= (1 << ICNC1);

}

/**
 * @return void
 * @param edge :FALLING_EDGE, RISING_EDGE
 */
void Timer1_EdgeDetect_Mode(char edge) {

    switch (edge) {

    case FALLING_EDGE:
        TCCR1B &= ~(1 << ICES1);
        break;

    case RISING_EDGE:
        TCCR1B |= (1 << ICES1);
        break;

    default:
        break;

    }

    Clear_ICF1();

}

short int Read_ICR() {

    return ICR1;

}

char Read_ICRL() {

    return ICR1L;

}

char Read_ICRH() {

    return ICR1H;

}

/**
 * Initialize Input Capture Unit
 * @param Source
 * @param edge
 */
void init_ICU_Timer1(char Source, char edge) {

    Timer1_Enable_NoiseCanceler();

    Timer1_Change_TrigSource(Source);

    Timer1_EdgeDetect_Mode(edge);

    switch (Source) {

    case AC_SOURCE:
        AC_INT_EN();
        break;

    case ICP1_SOURCE:
        ICP1_EN();
        Timer1_INT_EN_ICR1();
        break;

    default:
        break;

    }

}

/**
 * 
 * @param DUTY_PER  : Duty Cycle Percentage
 * @param TIMER_NUM : Timer 0 ,Timer 1 or Timer 2
 * @return void
 */
void Set_DutyCycle(char TIMER_NUM, char DUTY_PER) {

    switch (TIMER_NUM) {

    case TIMER0:
        Timer0_init_OC0();

        Change_OCR0((255 * DUTY_PER) / 100.0);
        break;

    case TIMER1:

        break;

    case TIMER2:
        Timer2_init_OC2();

        Change_OCR2((255 * DUTY_PER) / 100.0);
        break;

    default:
        break;

    }

}

/**
 * 
 * @param TIMER_NUM
 * @return char
 */
char get_DutyCycle(char TIMER_NUM) {


    switch (TIMER_NUM) {

    case TIMER0:
        return(OCR0 * 100) / 255;

    case TIMER1:
        break;

    case TIMER2:
        return(OCR2 * 100) / 255;


    default:
        break;
    }

    return 0;
}