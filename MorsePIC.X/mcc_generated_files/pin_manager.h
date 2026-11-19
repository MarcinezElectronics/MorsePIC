/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78.1
        Device            :  PIC16F1619
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.30	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SCL aliases
#define SCL_TRIS                 TRISAbits.TRISA0
#define SCL_LAT                  LATAbits.LATA0
#define SCL_PORT                 PORTAbits.RA0
#define SCL_WPU                  WPUAbits.WPUA0
#define SCL_OD                   ODCONAbits.ODA0
#define SCL_ANS                  ANSELAbits.ANSA0
#define SCL_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define SCL_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define SCL_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define SCL_GetValue()           PORTAbits.RA0
#define SCL_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define SCL_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define SCL_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define SCL_SetPushPull()        do { ODCONAbits.ODA0 = 0; } while(0)
#define SCL_SetOpenDrain()       do { ODCONAbits.ODA0 = 1; } while(0)
#define SCL_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define SCL_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set LED6 aliases
#define LED6_TRIS                 TRISAbits.TRISA2
#define LED6_LAT                  LATAbits.LATA2
#define LED6_PORT                 PORTAbits.RA2
#define LED6_WPU                  WPUAbits.WPUA2
#define LED6_OD                   ODCONAbits.ODA2
#define LED6_ANS                  ANSELAbits.ANSA2
#define LED6_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LED6_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LED6_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LED6_GetValue()           PORTAbits.RA2
#define LED6_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LED6_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LED6_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define LED6_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define LED6_SetPushPull()        do { ODCONAbits.ODA2 = 0; } while(0)
#define LED6_SetOpenDrain()       do { ODCONAbits.ODA2 = 1; } while(0)
#define LED6_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define LED6_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set LED4 aliases
#define LED4_TRIS                 TRISAbits.TRISA5
#define LED4_LAT                  LATAbits.LATA5
#define LED4_PORT                 PORTAbits.RA5
#define LED4_WPU                  WPUAbits.WPUA5
#define LED4_OD                   ODCONAbits.ODA5
#define LED4_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define LED4_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define LED4_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define LED4_GetValue()           PORTAbits.RA5
#define LED4_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define LED4_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define LED4_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define LED4_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define LED4_SetPushPull()        do { ODCONAbits.ODA5 = 0; } while(0)
#define LED4_SetOpenDrain()       do { ODCONAbits.ODA5 = 1; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set Touch aliases
#define Touch_TRIS                 TRISCbits.TRISC1
#define Touch_LAT                  LATCbits.LATC1
#define Touch_PORT                 PORTCbits.RC1
#define Touch_WPU                  WPUCbits.WPUC1
#define Touch_OD                   ODCONCbits.ODC1
#define Touch_ANS                  ANSELCbits.ANSC1
#define Touch_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define Touch_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define Touch_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define Touch_GetValue()           PORTCbits.RC1
#define Touch_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define Touch_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define Touch_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define Touch_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define Touch_SetPushPull()        do { ODCONCbits.ODC1 = 0; } while(0)
#define Touch_SetOpenDrain()       do { ODCONCbits.ODC1 = 1; } while(0)
#define Touch_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define Touch_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set S1 aliases
#define S1_TRIS                 TRISCbits.TRISC4
#define S1_LAT                  LATCbits.LATC4
#define S1_PORT                 PORTCbits.RC4
#define S1_WPU                  WPUCbits.WPUC4
#define S1_OD                   ODCONCbits.ODC4
#define S1_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define S1_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define S1_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define S1_GetValue()           PORTCbits.RC4
#define S1_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define S1_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define S1_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define S1_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define S1_SetPushPull()        do { ODCONCbits.ODC4 = 0; } while(0)
#define S1_SetOpenDrain()       do { ODCONCbits.ODC4 = 1; } while(0)

// get/set LED7 aliases
#define LED7_TRIS                 TRISCbits.TRISC5
#define LED7_LAT                  LATCbits.LATC5
#define LED7_PORT                 PORTCbits.RC5
#define LED7_WPU                  WPUCbits.WPUC5
#define LED7_OD                   ODCONCbits.ODC5
#define LED7_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define LED7_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define LED7_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define LED7_GetValue()           PORTCbits.RC5
#define LED7_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define LED7_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define LED7_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define LED7_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define LED7_SetPushPull()        do { ODCONCbits.ODC5 = 0; } while(0)
#define LED7_SetOpenDrain()       do { ODCONCbits.ODC5 = 1; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/