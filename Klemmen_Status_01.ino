/*
 * Terminal status CAN bus message generator
 * 
 * Generates Klemmen_Status_01 messages for MQB platform
 * 
 * Coded by Ronaldo Cordeiro - cordeiroronaldo@hotmail.com
 * 
 * Uses MCP_CAN_lib-master - By Cory J. Fowler 
 * https://github.com/coryjfowler/MCP_CAN_lib
 */

#include <mcp_can.h>
#include <SPI.h>

#define KLEMMEN_STATUS_01_ID 0x3C0

unsigned char kStatusBuf[4] = {0x00,0x00,0x03,0x00};
unsigned char checkSum[16]  = {0x74,0xC1,0x31,0x84,0xFE,0x4B,0xBB,0x0E,0x4F,0xFA,0x0A,0xBF,0xC5,0x70,0x80,0x35};
int i=0;

MCP_CAN CAN(9);

void setup()
{
  Serial.begin(115200);
  CAN.begin(MCP_ANY,CAN_500KBPS,MCP_16MHZ); 
  CAN.setMode(MCP_NORMAL);
}

void loop()
{
      kStatusBuf[0]=checkSum[i];
      kStatusBuf[1]=i;
      CAN.sendMsgBuf(KLEMMEN_STATUS_01_ID, 0 , 4, kStatusBuf);
      i++;
      if (i>15) i=0;
      delay(100);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
