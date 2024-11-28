/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MY_TIMERCOUNTER_H
#define	MY_TIMERCOUNTER_H

#include <xc.h> // include processor files - each processor file is guarded. 

//mode MACROS
#define NORMAL_MODE   0
#define PWM_MODE      1
#define CTC_MODE      2
#define FAST_PWM_MODE 3

//mode MACROS for TIMER1 
#define NORMAL_MODE              0
#define PWM_MODE_8bits           1
#define PWM_MODE_9bits           2
#define PWM_MODE_10bits          3
#define CTC_MODE_TOPisOCR1A      4
#define FAST_PWM_MODE_8bits      5
#define FAST_PWM_MODE_9bits      6
#define FAST_PWM_MODE_10bits     7
#define PWM_MODE_FREQ_TOPisICR1  8
#define PWM_MODE_FREQ_TOPisOCR1A 9
#define PWM_MODE_TOPisICR1       10
#define PWM_MODE_TOPisOCR1A      11
#define CTC_MODE_TOPisICR1       12
#define FAST_PWM_MODE_TOPisICR1  14
#define FAST_PWM_MODE_TOPisOCR1A 15

//Clock DIV for Timer 0  MACROS
#define TIMER0_NO_CLK             0
#define TIMER0_MC_CLK             1
#define TIMER0_MC_CLK_8           2
#define TIMER0_MC_CLK_64          3
#define TIMER0_MC_CLK_256         4
#define TIMER0_MC_CLK_1024        5
#define TIMER0_EXT_CLK_FALLING    6
#define TIMER0_EXT_CLK_RISING     7

//Clock DIV for Timer 1  MACROS
#define TIMER1_NO_CLK             0
#define TIMER1_MC_CLK             1
#define TIMER1_MC_CLK_8           2
#define TIMER1_MC_CLK_64          3
#define TIMER1_MC_CLK_265         4
#define TIMER1_MC_CLK_1024        5
#define TIMER1_EXT_CLK_FALLING    6
#define TIMER1_EXT_CLK_RISING     7

//Clock DIV for Timer 2  MACROS
#define TIMER2_NO_CLK             0
#define TIMER2_MC_CLK             1
#define TIMER2_MC_CLK_8           2
#define TIMER2_MC_CLK_32          3
#define TIMER2_MC_CLK_64          4
#define TIMER2_MC_CLK_128         5
#define TIMER2_MC_CLK_265         6
#define TIMER2_MC_CLK_1024        7


//Define OC0,OC2,OC1B & OC1A pins
#define OC0  PB3
#define OC2  PD7
#define OC1B PD4
#define OC1A PD5
#define ICP1 PD6

//CTC MODES MACROS TIMER0,2
#define CTC_DISABLE 0
#define CTC_TOGGLE  1
#define CTC_CLEAR   2
#define CTC_SET     3 

//PHASE CORRECT WITH PWM MODES MACROS TIMER0,1,2
#define PWM_DISABLE       0
#define OC1A_TOGGLE       1 
/*WGM13:0 = 9 or 4 : Toggle OC1A on Compare
Match, OC1B disconnected (normal port
operation).
For all other WGM13:0 settings, normal port
operation, OC1A/OC1B disconnected.*/
#define PWM_ClearUpCount  2
#define PWM_SetUpCount    3 

//FAST PWM TIMER0,2  MACROS
#define FPWM_DISABLE     0
#define OC1A_TOGGLE      1 
/*WGM13:0 = 15: Toggle OC1A on Compare
Match, OC1B disconnected (normal port
operation).
For all other WGM13:0 settings, normal port
operation, OC1A/OC1B disconnected.*/
#define FPWM_ClearOnComp 2
#define FPWM_SetOnComp   3

//Sync & Async modes in timer2 change
#define Sync_To_Async 0
#define ASync_To_sync 1

//Analog Comparator Trigger Source or ICP1 input pin
#define AC_SOURCE   1
#define ICP1_SOURCE 0

//Edge Detector in Input Capture Unit
#define FALLING_EDGE 0
#define RISING_EDGE  1

#define TIMER0 0
#define TIMER1 1
#define TIMER2 2

//functions Timer0
void init_Timer0_WithOCR0(char Mode, char clk, char OCR0_Val);
void Timer0_setClk(char clk);
void Timer0_setMode(char Mode);
void Timer0_INT_EN_OCM(void);
void Timer0_INT_EN_TOVF(void);
//void Timer0_INT_DISABLE_OCM(void);
//void Timer0_INT_DISABLE_TOVF(void);
void Timer0_COMP_MODE(char OC0_MODE);
void Timer0_init_OC0();
void Change_OCR0(char OCR0_TOP_VAL);
void initNormalMode_Timer_Counter0(char clk);
void Timer0_waitCTC() ;

//functions Timer1
void init_Timer1_WithOCR1A_AND_B(char Mode, char clk, char OCR1A_Val, char OCR1B_Val);
void Timer1_setClk(char clk);
void Timer1_setMode(char Mode);
void Timer1_INT_EN_OCMA();
void Timer1_INT_EN_OCMB();
void Timer1_INT_EN_TOVF(void);
void Timer1_INT_EN_ICR1() ;
//void Timer1_INT_DISABLE_OCM(void);
void Timer1_INT_DISABLE_TOVF(void);
void Timer1_COMP_MODE(char OC1_MODE);
void Timer1_init_OC1();
void Change_OCR1A(char OCR1A_TOP_VAL);
void Change_OCR1B(char OCR1B_TOP_VAL);
void initNormalMode_Timer_Counter1(char clk);

//functions Timer2
void init_Timer2_WithOCR2(char Mode, char clk, char OCR2_Val);
void Timer2_setClk(char clk);
void Timer2_setMode(char Mode);
void Timer2_INT_EN_OCM(void);
void Timer2_INT_EN_TOVF(void);
void Timer2_INT_DISABLE_OCM(void);
void Timer2_INT_DISABLE_TOVF(void);
void Timer2_COMP_MODE(char OC2_MODE);
void Timer2_init_OC2();
void Change_OCR2(char OCR2_TOP_VAL);
void initNormalMode_Timer_Counter2(char clk);
void Clear_Timer2_Flags();
void WAIT_UNTIL_LOAD_DATA_TIMER2();
void ChangeBet_SyncAsync(char SyncAsync, char TCNT2_VAL, char Mode, char clk, char OCR2_VAL);

//Input Capture Unit Functions
void init_ICU_Timer1(char Source, char edge);
void ICP1_EN();
void Timer1_INT_Disable_ICR1() ;
void Timer1_Change_TrigSource(char Source);
void Clear_ICF1();
void Timer1_Enable_NoiseCanceler();
void Timer1_EdgeDetect_Mode(char edge);
void AC_INT_EN();
short int  Read_ICR();
char Read_ICRL();
char Read_ICRH();

// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#endif	/* MY_TIMERCOUNTER_H */

