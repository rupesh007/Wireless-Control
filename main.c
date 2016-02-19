//----------------------------------------------------------------------------
// Hesinki Metropolia UAS
// Department of IT
// Embedded System Engineering (2012)
//----------------------------------------------------------------------------

/*******************************************************************************
*	This program transmits 2 bytes of payload through nRF24L01 module. SPI
*	protocol is used to interface the RF with MCU. The transmission here is 
*	half duplex.
*******************************************************************************/


#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "nRF24L01.h"


#define button_0 ( Button_0_Data_ADDR & Button_0_MASK )
#define button_1 ( Button_1_Data_ADDR & Button_1_MASK )
#define button_2 ( Button_2_Data_ADDR & Button_2_MASK )



// Local prototypes
void feed_payload(BYTE data);
void displayPayload( BYTE *payload );
void transmit_data(void);

BYTE payloadData[2] ={0,255};
unsigned int i, loop, count;
char theStr[] = "transmit";
char blank[]="    ";




void main(void)
{
	
	M8C_EnableGInt;	

	// initialization: SPIM is needed by RF-module
	SPIM_Start(SPIM_SPIM_MODE_0 | SPIM_SPIM_MSB_FIRST);
	
//	PGA_SetGain(PGA_G1_00);
//	PGA_Start(PGA_MEDPOWER);
//	
//	ADCINC_Start(ADCINC_HIGHPOWER); // Apply power to the SC Block	
//	ADCINC_GetSamples(0); // Have ADC run continuously		

   	LCD_Start(); 
    LCD_Position(0,7);            // Place LCD cursor at row 0, col 5.  
    LCD_PrString(theStr);         // Print "PSoC LCD" on the LCD  

	// This is the transmitter side, but just to test mode changing we first make this receiver
	
//	// Initialize RF module
//	nRF24L01_commonConfiguration();
//	// Set as a trasmitter
//	nRF24L01_SetAsReciever();
   
	// Initialize RF module
	nRF24L01_commonConfiguration();
	// Set as a trasmitter
 	nRF24L01_SetAsTransmiter();
	
//	LCD_Position(0,5);            // Place LCD cursor at row 0, col 5.  
//    LCD_PrCString("DD");         // Print "PSoC LCD" on the LCD  

	
	
	
	
	while (1) {
	
	//payloadData[1]--;
	
	//****************************************************
	if (!button_0 && !button_1 && !button_2)
	
	{
	
		
		feed_payload(0x05);
		LCD_Position(0,0);            // Place LCD cursor at row 0, col 5.  
    	LCD_PrCString("off");         // Print "PSoC LCD" on the LCD  
	
		
	}
	
	
	
	else if (button_0 && !button_1 && !button_2)
	
	{
		
		feed_payload(0x0A);
		LCD_Position(0,0);            // Place LCD cursor at row 0, col 5.  
		LCD_PrCString("A");         // Print "PSoC LCD" on the LCD  
		
	}
	
	
	
	
	else if (button_1 && !button_0 && !button_2) 
	
	{
		
		feed_payload(0x0B);
		LCD_Position(0,0);            // Place LCD cursor at row 0, col 5.  
		LCD_PrCString("B");         // Print "PSoC LCD" on the LCD  
	}
	
	
	
	else if (button_2 && !button_1 && !button_0)
	
	{
		
		feed_payload(0x0C);
		LCD_Position(0,0);            // Place LCD cursor at row 0, col 5.  
		LCD_PrCString("C");         // Print "PSoC LCD" on the LCD  
	}
	
	
	else if (button_0 && button_1 && !button_2 ) 
	
	{
	
		
		feed_payload(0x0D);
		LCD_Position(0,0);            // Place LCD cursor at row 0, col 5.  
		LCD_PrCString("AB");         // Print "PSoC LCD" on the LCD  
	
	}

	
	else if (button_0 && button_2 && !button_1 )
	
	{
		
		feed_payload(0x0E);
		LCD_Position(0,0);            // Place LCD cursor at row 0, col 5.  
		LCD_PrCString("AC");         // Print "PSoC LCD" on the LCD  
	
	}
	
	else if (button_1 && button_2 && !button_0 )
	
	{
		
		feed_payload(0x0F);
		LCD_Position(0,0);            // Place LCD cursor at row 0, col 5.  
		LCD_PrCString("BC");         // Print "PSoC LCD" on the LCD  
	
	}
	
//	if (button_0 && button_1 && button_2)
	else 
	
	{
		
		feed_payload(0x09);
		LCD_Position(0,0);            // Place LCD cursor at row 0, col 5.  
		LCD_PrCString("ABC");         // Print "PSoC LCD" on the LCD  
	
	}

	//************************************************************

	
	
	

		

// The code below is just for testing fullduplex transmission.
// Do not try to make it work.

/*		// Set as receiver
		nRF24L01_SetAsReciever();

		count = 0; // count receives
		
		// this will end when data has been received 10 times
		while( count < 10 ) {
			// check if something has been received
			if( nRF24L01_is_RX_DR() == 1 ){
				// read payload
				nRF24L01_readPayload( R_RX_PAYLOAD, payloadData, 2);
				// clear interrupt
				nRF24L01_clear_RX_DR();
				// Print it out
				displayPayload( payloadData );
				count++; // count 10 receives and start transmitting
			}
		}
*/
		
	}	
}

void displayPayload( BYTE *payload ) {
			LCD_Position(1,0);    
			LCD_PrCString("P1: " );
		    LCD_Position(1,4);    
			LCD_PrHexByte(payload[0]);
		    LCD_Position(1,7);    
			LCD_PrCString("P2: " );
		    LCD_Position(1,10);
			LCD_PrHexByte(payload[1]);
}

void transmit_data(void){
	
				while( nRF24L01_is_TX_DS() != 1 ){
   
				nRF24L01_sendPayload(W_TX_PAYLOAD, payloadData, 2);
    
				nRF24L01_transmitPayload();
     

				if( nRF24L01_is_MAX_RT() ){
					nRF24L01_clear_MAX_RT();
					break;  // This breaks out of while loop
				}		
			}
			// Clear the interrupt status
			nRF24L01_clear_TX_DS();
	
			

}

void feed_payload (BYTE data)

{
	payloadData[0]=data;
	transmit_data();
	
	displayPayload( payloadData );
	LCD_Position(0,0); 
	LCD_PrString(blank); 

}