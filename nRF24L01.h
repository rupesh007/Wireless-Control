#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "delay.h"


// communication function with the nRF24L01
void nRF24L01_setRxTxAddr(void);
BYTE nRF24L01_sendOneByte(BYTE oneByte);
BYTE nRF24L01_sendInstruction(BYTE instructionWord, BYTE mapAddr);
void nRF24L01_sendPayload(BYTE instructionWord, BYTE* dataArray, BYTE bytes);
void nRF24L01_transmitPayload(void);
void nRF24L01_readPayload(BYTE instructionWord, BYTE* dataArray, BYTE bytes);
void nRF24L01_commonConfiguration(void);
void nRF24L01_SetAsTransmiter( void );
void nRF24L01_SetAsReciever( void );
BYTE nRF24L01_is_RX_DR( void );
BYTE nRF24L01_is_TX_DS( void );
BYTE nRF24L01_is_MAX_RT( void );
void nRF24L01_clear_RX_DR( void );
void nRF24L01_clear_TX_DS( void );
void nRF24L01_clear_MAX_RT( void );
void nRF24_CSN_state( BYTE state );
void nRF24_CE_state( BYTE state );

#define CSN_ON 1
#define CSN_OFF 0
#define CE_ON 1
#define CE_OFF 0

// SPI commands of the nRF24L01
#define R_REGISTER		0x00
#define W_REGISTER		0x20
#define R_RX_PAYLOAD	0x61
#define W_TX_PAYLOAD	0xA0
#define FLUSH_TX		0xE1
#define FLUSH_RX		0xE2
#define REUSE_TX_PL		0xE3
#define NOP				0xFF


// Register addresses
#define CONFIG			0x00
#define EN_AA			0x01
#define EN_RXADDR		0x02
#define SETUP_AW		0x03
#define SETUP_RETR		0x04
#define RF_CH			0x05
#define RF_SETUP		0x06
#define STATUS			0x07
#define OBSERVE_TX		0x08
#define CD				0x09
#define RX_ADDR_P0		0x0A
#define RX_ADDR_P1		0x0B
#define RX_ADDR_P2		0x0C
#define RX_ADDR_P3		0x0D
#define RX_ADDR_P4		0x0E
#define RX_ADDR_P5		0x0F
#define TX_ADDR			0x10
#define RX_PW_P0		0x11
#define RX_PW_P1		0x12
#define RX_PW_P2		0x13
#define RX_PW_P3		0x14
#define RX_PW_P4		0x15
#define RX_PW_P5		0x16
#define FIFO_STATUS		0x17

// IRQ interrupt masks
#define MASK_RX_DR	0x40
#define MASK_TX_DS	0x20
#define MASK_MAX_RT	0x10

// useful STATUS register masks
#define RX_DR_MASK		0x40
#define TX_DS_MASK		0x20
#define TX_FULL_MASK	0x01

// general defines
#define DUMMYDATA		0x00