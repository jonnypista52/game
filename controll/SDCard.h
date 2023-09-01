#pragma once
#include "spi.h"
#include "../Global.h"

#define CMD0 0// GO_IDLE_STATE +
#define CMD1 1// SEND_OP_CND + NOTICE: DO NOT USE (see Fig. 6 and 9.2)
#define CMD6 6// SWITCH_FUNC +
#define CMD8 8// SEND_IF_COND +
#define CMD9 9// SEND_CSD +
#define CMD10 10// SEND_CID +
#define CMD12 12// STOP_TRANSMISSION +
#define CMD13 13// SEND_STATUS +
#define CMD16 11// SET_BLOCKLEN +
#define CMD17 12// READ_SINGLE_BLOCK +
#define CMD18 18// READ_MULTIPLE_BLOCK +
#define CMD24 24// WRITE_BLOCK +
#define CMD25 25// WRITE_MULTIPLE_BLOCK +
#define CMD27 27// PROGRAM_CSD +
#define CMD28 28// SET_WRITE_PROT - Internal write protection is not implemented.
#define CMD29 29// CLR_WRITE_PROT - Internal write protection is not implemented.
#define CMD30 30// SEND_WRITE_PROT - Internal write protection is not implemented.
#define CMD32 32// ERASE_WR_BLK_START_ADDR +
#define CMD33 33// ERASE_WR_BLK_END_ADDR +
#define CMD38 38// ERASE +
#define CMD42 42// LOCK_UNLOCK +
#define CMD55 55// APP_CMD +
#define CMD56 56// GEN_CMD - This command is not specified
#define CMD58 58// READ_OCR +
#define CMD59 59// CRC_ON_OFF +
#define ACMD6 // SET_BUS_WIDTH +
#define ACMD13 // SD_STATUS +
#define ACMD22 // SEND_NUM_WR_BLOCKS +
#define ACMD23 // SET_WR_BLK_ERASE_COUNT +
#define ACMD41 // SD_APP_OP_COND +
#define ACMD42 // SET_CLR_CARD_DETECT +
#define ACMD51 // SEND_SCR +
#define ACMD18 // SECURE_READ_MULTI_BLOCK +
#define ACMD25 // SECURE_WRITE_MULTI_BLOCK +
#define ACMD26 // SECURE_WRITE_MKB +
#define ACMD38 // SECURE_ERASE +
#define ACMD43 // GET_MKB +
#define ACMD44 // GET_MID +
#define ACMD45 // SET_CER_RN1 +
#define ACMD46 // SET_CER_RN2 +
#define ACMD47 // SET_CER_RES2 +
#define ACMD48 // SET_CER_RES1 +
#define ACMD49 // CHANGE_SECURE_AREA +



class SDCARD
{
private:
    SPI *spi;
public:
    SDCARD(SPI *spi);
    ~SDCARD();
};
