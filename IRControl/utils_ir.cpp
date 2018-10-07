#include "utils_ir.h"

#ifdef IR_IN_USE

//#include <IRremoteESP8266.h>
#include <IRsend.h>
//#include <IRrecv.h>

#include <pins_arduino.h>
#include "utils_debug.h"

//#define IR_RECV_PIN     D3
#define IR_SEND_PIN     D3

//IRrecv irrecv(IR_RECV_PIN);
IRsend irsend(IR_SEND_PIN);

int           ir_type   = 0;
int           ir_bits   = 0;
unsigned long ir_value  = 0;

typedef struct
{
  int           type;
  int           bits;
  unsigned long value;
} ir_send_cmd_t;

void setup_ir(void)
{
  //irrecv.enableIRIn();
  irsend.begin();
}

/*
void handle_ir_recv(void)
{
  decode_results results;   

  if (irrecv.decode(&results)) 
  {
    if(results.overflow) 
    {
      PRINTLN("IR code too long. Edit IRremoteInt.h and increase RAWBUF.");
      return;
    }

    ir_type  = results.decode_type;
    ir_bits  = results.bits;
    ir_value = results.value;

    irrecv.resume();
  }
}
*/

void ir_send(ir_send_cmd_t cmd)
{
  int           bits   = cmd.bits;
  unsigned long value  = cmd.value;

  //PRINT("Type : ");
  switch(cmd.type)
  {
    case NEC:
      //PRINT("NEC : ");Serial.print(value, HEX);PRINT(", ");PRINTLN(bits);
      irsend.sendNEC(value, bits);
      break ;
      
    case SONY:
      //PRINT("SONY : ");Serial.print(value, HEX);PRINT(", ");PRINTLN(bits);
      irsend.sendSony(value, bits, 2);
      break ;
      
    default:
      PRINTLN("Unknown type!!!");
  }
}

void ir_send(int type, int bits, unsigned long value)
{
  //PRINT("Type : ");
  switch(type)
  {
    case NEC:
      //PRINTLN("NEC");
      irsend.sendNEC(value, bits);
      break ;
      
    case SONY:
      //PRINTLN("SONY");
      irsend.sendSony(value, bits);
      break ;
      
    default:
      PRINTLN("Unknown type!!!");
  }
}

// TV Control
ir_send_cmd_t ir_cmds[10] =  { {NEC,   32, 0x20250AF},         // TV ON                // 0
                                    {NEC,   32, 0x20250AF},         // TV OFF
                                    {NEC,   32, 0x202F00F},         // TV MUTE
                                    {NEC,   32, 0x202F00F},         // TV UNMUTE
                                    {NEC,   32, 0x202A857},         // TV VOLUME UP
                                    {NEC,   32, 0x20238C7},         // TV VOLUME DOWN
                                    /*
                                    {NEC,   32, 0x0000000},         // RESERVED
                                    {NEC,   32, 0x0000000},         // RESERVED
                                    {NEC,   32, 0x0000000},         // RESERVED
                                    {NEC,   32, 0x0000000},         // RESERVED
                                    {NEC,   32, 0x0000000},         // RESERVED
                                    {NEC,   32, 0x0000000},         // RESERVED
                                    {NEC,   32, 0x0000000},         // RESERVED
                                    {NEC,   32, 0x0000000},         // RESERVED
                                    {NEC,   32, 0x0000000},         // RESERVED
                                    {NEC,   32, 0x0000000},         // RESERVED
                                    {NEC,   32, 0x0000000},         // RESERVED
                                    {NEC,   32, 0x0000000},         // RESERVED*/
                                    
                                    {SONY,  15, 0x000540C},         // SPEAKER ON/OFF
                                    {SONY,  15, 0x000140C},         // SPEAKER MUTE
                                    {SONY,  15, 0x000240C},         // SPEAKER VOLUME UP
                                    {SONY,  15, 0x000640C}          // SPEAKER VOLUME DOWN
                                  };


void turn_on_tv(void)
{
	ir_send(ir_cmds[DEV_TV_ON]);
}

void turn_off_tv(void)
{
  //ir_send(ir_cmds[DEV_TV_OFF]);
}

void tv_mute(void)
{
  //ir_send(ir_cmds[DEV_TV_MUTE]);
}

void tv_unmute(void)
{
  //ir_send(ir_cmds[DEV_TV_UNMUTE]);
}

void tv_vol_up(void)
{
  //ir_send(ir_cmds[DEV_TV_VOL_UP]);
  //delay(100);
  //ir_send(ir_cmds[DEV_TV_VOL_UP]);
}

void tv_vol_down(void)
{
  //ir_send(ir_cmds[DEV_TV_VOL_DOWN]);
  //delay(100);
  //ir_send(ir_cmds[DEV_TV_VOL_DOWN]);
}

#endif
