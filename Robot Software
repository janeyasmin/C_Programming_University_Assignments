/*File: Robot Project.c 
*Authors: Mostafa El Debeiki and Jane Malalane 
*Created in 2019 
*This program enables the robot to detect the beacon and move towards it, whilst avoiding obstacles.
 Whilst the beacon is not detected, LED3 is on and when there is an obstacle within the defined distance sensor detection range, LED1 turns on */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#pragma config OSC = HS     //High speed resonator
#pragma config WDT = OFF    //Watchdog timer off
#pragma config LVP = OFF    //Low voltage programmer disabled
#pragma config PWRT = ON    //Power up timer on

#define LED3 LATBbits.LATB4    //Define LED3
#define LED1 LATBbits.LATB2    //Define LED1
#define RB0 LATBbits.LATB0
#define RB1 LATBbits.LATB1
#define RA4 LATAbits.LATA4
#define RA5 LATAbits.LATA5
#define _XTAL_FREQ 10000000 // define clock frequency for __delay_10ms() 

int main(void)
{

int markspace = 200;  // Mark space value for PWM(50% mark space ratio)

//Flashing LEDs 
void wait10ms(int del);     //generates a delay in multiples of 10ms

//Beacon Sensors
int setpoint_distance = 75; //Beacon detection range 
int max = 380; //Safety distance from which the robot stops before reaching the beacon 

void setupDIOl(void); // Configure digital I/O for left beacon sensor 
unsigned int readDIOl(void); //Read port AN4
void setupDIOr(void); // Configure digital I/O for right beacon sensor 
unsigned int readDIOr(void); //Read port AN3 

//Distance Sensors 
int setpoint_distance2 = 18;   //Distance sensor detection range 

void setupADCl(void);           //Configure A/D
unsigned int readADCl(void);    //Read ADC
void setupADCr(void);//Configure A/D
unsigned int readADCr(void);//Read ADC

    ADCON1 = 0b00001101; // This sets RA0 and RA1 to analogue inputs (AN0 and AN1) and RA2 - RA5 as digital I/O. 
    TRISA  = 0b11001111; // This sets all pins except for RA4 and RA5 as inputs
    TRISB  = 0b11000000; // This sets all pins except for RA6 and RA7 as inputs
    
    //Beacon Sensor
    setupDIOl(); // configure digital I/0 for left sensor 
    setupDIOr(); // configure digital I/0 for right sensor 
    LATB=0b11000011; //clear PORTB bits 2-5
    
    // Distance Sensor 
    setupADCl();         // Configure ADC for left sensor 
    setupADCr();         // Configure ADC for right sensor 
    
    //PWM module
    PR2 = 0b11111111 ;  //set period of PWM
    T2CON = 0b00000111 ;//Timer 2(TMR2) on, Prescaler = 16
    TRISCbits.RC2=0;    //set CCP1(pin13) to an output pin
    TRISCbits.RC1=0;    //set CCP2(pin13) to an output pin
    CCP1CON=0b00001100; //
    CCP2CON=0b00001100;
    CCPR2L=0; //initially stopped
    CCPR1L=0; //initially stopped
    
    {
        TRISB=0b11000000;     	//configure Port B
        /*three second delay during which the LEDs flash every second */
        LATB=0b00111100;   	//turn LED1 - LED4 on
        wait10ms(50);          //delay 1 second
        LATB=0b00000000;   	//turn LED1 - LED4 off;
        wait10ms(50);
        LATB=0b00111100;   	
        wait10ms(50);     
        LATB=0b00000000;   	
        wait10ms(50);
        LATB=0b00111100;   	
        wait10ms(50);
        LATB=0b00000000;   	
        wait10ms(50);
    }
  
    while(1)
    {
        
        if(readDIOl()>= setpoint_distance && readDIOr()>= setpoint_distance ) // while the beacon is not detected, the robot spins (right wheel goes forward and left wheel goes backward)
        {   LED3=1;
            CCPR1L = 60; // load duty cycle into CCP1CON        
            RB0 = 0; 
            RB1 = 1;
            CCPR2L = 60; //load duty cycle into CCP2CON 
            RA4 = 1;
            RA5 = 0;     
        }
        else 
        {
            if (readDIOl()<= setpoint_distance ) //if left beacon sensor detects beacon, robot turns left
            {
                {   CCPR1L = markspace;
                    RB0 = 0;
                    RB1 = 1;
                    CCPR2L = markspace;
                    RA4 = 1;
                    RA5 = 0;
                }
                    if(readADCl() <= setpoint_distance2 && readADCr() <= setpoint_distance2) // if no obstacle is detected, go forward 
                    {CCPR1L = markspace;
                    RB0 = 0;
                    RB1 = 1;
                    CCPR2L = markspace;
                    RA4 = 0;
                    RA5 = 1;
                    }
                    if(readADCr()>= setpoint_distance2) // // if right sensor detects an obstacle, LED 1 turns on and the robot turns left
                    {LED1=1;
                     //CCP1CON = (0x0c);   
                     CCPR1L = markspace;
                     RB0 = 0;
                     RB1 = 1;
                     //CCP2CON = (0x0c);
                     CCPR2L = markspace;
                     RA4 = 1;
                     RA5 = 0;
                    }           
                     if(readADCl()>= setpoint_distance2) // If left sensor detects an obstacle, LED 1 turns on and the robot turns right
                    {LED1=1;
                     CCPR1L = markspace;
                     RB0 = 1;
                     RB1 = 0;
                     CCPR2L = markspace;
                     RA4 = 0;
                     RA5 = 1;
                     } 
                     if(readADCl() >= setpoint_distance2 && readADCr() >= setpoint_distance2)  //If both sensors detect an obstacle, LED 1 turns on and robot stops 
                    {LED1=1;
                    CCPR2L = markspace; 
                     RA4 = 1;
                     RA5 = 1;
                     CCPR1L = markspace;
                     RB0 = 1;
                     RB1 = 1;
                    }
            
            }        
            if (readDIOr()<= setpoint_distance ) // If right beacon sensor detects the beacon, robot turns right
            {   
                {   CCPR1L = markspace;
                    RB0 = 1;
                    RB1 = 0;
                    CCPR2L = markspace;
                    RA4 = 0;
                    RA5 = 1;
                }
                    if(readADCl() <= setpoint_distance2 && readADCr() <= setpoint_distance2) // if no obstacle is detected, go forward 
                    {CCPR1L = markspace;
                    RB0 = 0;
                    RB1 = 1;
                    CCPR2L = markspace;
                    RA4 = 0;
                    RA5 = 1;
                    }
                    if(readADCl() >= setpoint_distance2 && readADCr() >= setpoint_distance2)  //If both sensors detect an obstacle, LED 1 turns on and robot stops
                    {LED1=1;
                     CCPR2L = markspace; 
                     RA4 = 1;
                     RA5 = 1;
                     CCPR1L = markspace;
                     RB0 = 1;
                     RB1 = 1;
                    }

                    if(readADCr()>= setpoint_distance2) // if right  sensor detects an obstacle, LED 1 turns on and the robot turns left
                    {LED1=1;
                     CCPR1L = markspace;
                     RB0 = 0;
                     RB1 = 1;
                     CCPR2L = markspace;
                     RA4 = 1;
                     RA5 = 0;
                    }         

            }
            if(readDIOl <= max && readDIOr <= max) // the robot stops before reaching the beacon, at a close enough distance.  
                
            {CCPR1L = markspace;
            RB0 = 1;
            RB1 = 1;
            CCPR2L = markspace;
            RA4 = 1;
            RA5 = 1;   
            }
        }
    }  
}   

// Delay function configuration 
void wait10ms(int del)
{
    unsigned char c;
    for(c=0;c<del;c++)
        __delay_ms(10);     	//call 10ms delay function 100 times
    return;

}

// Beacon Sensor Configuration
void setupDIOl(void) //configure digital I/O
{
    ADCON2bits.ADCS0=0; // Fosc/32
    ADCON2bits.ADCS1=1;    
    ADCON2bits.ADCS2=0;
    ADCON2bits.ADFM=1; //A/D result right justified  
    ADCON1 = 0b00001100; //This sets RA0 and RA1 to analogue inputs (AN0 and AN1) and RA2 - RA5 as digital I/O. 
    ADCON0bits.ADON=1; //Turn on digital I/O
}
unsigned int readDIOl(void) //Read port AN2
{ 
    // Channel 2 is set (0010)
    ADCON0bits.CHS0=0;      
    ADCON0bits.CHS1=1;
    ADCON0bits.CHS2=0;
    ADCON0bits.CHS3=0;
    ADCON0bits.GO=1;
    while(ADCON0bits.GO) //Do nothing while conversion is in progress
    return ((ADRESH<<8)+ADRESL); //Combines high & low bytes into one 16 bit value and returns Result (A/D value 0-1023) 
   
}
void setupDIOr(void)
{
    ADCON2bits.ADCS0=0; // Fosc/32
    ADCON2bits.ADCS1=1;    
    ADCON2bits.ADCS2=0;
    ADCON2bits.ADFM=1; //A/D result right justified  
    ADCON1 = 0b00001100; //This sets RA0 and RA1 to analogue inputs (AN0 and AN1) and RA2 - RA5 as digital I/O
    ADCON0bits.ADON=1; //Turn on digital I/O
} 
unsigned int readDIOr(void) //Read port AN3
{   
    // Channel 3 is set (0011)
    ADCON0bits.CHS0=1;     
    ADCON0bits.CHS1=1;
    ADCON0bits.CHS2=0;
    ADCON0bits.CHS3=0;
    ADCON0bits.GO=1;
    while(ADCON0bits.GO) //Do nothing while conversion is in progress
    return ((ADRESH<<8)+ADRESL); //Combines high & low bytes into one 16 bit value and returns Result (A/D value 0-1023) 
   
}

// IR Distance Sensors Configuration
void setupADCl(void) //configure A/D
{
    ADCON2bits.ADCS0=0; // Fosc/32
    ADCON2bits.ADCS1=1;     
    ADCON2bits.ADCS2=0;
    ADCON2bits.ADFM=1; //A/D result right justified
    ADCON1=0b00001101; //Set voltage reference and port A0 as A/D
    ADCON0bits.ADON=1; //Turn on ADC
}
unsigned int readADCl(void)	//Read port AN0
{
    //Channel 0 is set (0000)
    ADCON0bits.CHS0=0;        
    ADCON0bits.CHS1=0;  		
    ADCON0bits.CHS2=0;  		
    ADCON0bits.CHS3=0;  		
    ADCON0bits.GO=1;
    while (ADCON0bits.GO);  //do nothing while conversion in progress
    return ((ADRESH<<8)+ADRESL); //Combines high & low bytes into one 16 bit value and returns Result (A/D value 0-1023)
}                           
void setupADCr(void) //configure A/D
{
    ADCON2bits.ADCS0 = 0; // Fosc/32
    ADCON2bits.ADCS1 = 1;
    ADCON2bits.ADCS2 = 0;
    ADCON2bits.ADFM = 1; //A/D result right justified
    ADCON1 = 0b00001110; //Set voltage reference and port A0 as A/D
    ADCON0bits.ADON = 1; //Turn on ADC
}
unsigned int readADCr(void) //Read port AN1
{
    //Channel 1 is set (0001)
    ADCON0bits.CHS0=1;         
    ADCON0bits.CHS1=0;  		
    ADCON0bits.CHS2=0;  		
    ADCON0bits.CHS3=0;  		
    ADCON0bits.GO=1;
    while (ADCON0bits.GO);  //do nothing while conversion in progress
    return ((ADRESH<<8)+ADRESL); //Combines high & low bytes into one 16 bit value and returns Result (A/D value 0-1023)
}
