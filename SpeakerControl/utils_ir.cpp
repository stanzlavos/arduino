#include "utils_ir.h"

#ifdef IR_IN_USE

#include <IRremoteESP8266.h>
#include <IRsend.h>
//#include <IRrecv.h>

#include <pins_arduino.h>
#include "utils_debug.h"
#include "utils_speaker.h"

//#define IR_RECV_PIN     D3
#define IR_SEND_PIN       D0
#define VOL_MAX_MIN_CNT   4

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

// SPEAKER Control

ir_send_cmd_t ir_cmds[10] =  {      /*{NEC,   32, 0x20250AF},         // TV ON                // 0
                                    {NEC,   32, 0x20250AF},         // TV OFF
                                    {NEC,   32, 0x202F00F},         // TV MUTE
                                    {NEC,   32, 0x202F00F},         // TV UNMUTE
                                    {NEC,   32, 0x202A857},         // TV VOLUME UP
                                    {NEC,   32, 0x20238C7},         // TV VOLUME DOWN*/
                                    
                                    /*{NEC,   32, 0x0000000},         // RESERVED
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
                                    
                                    {SONY,  15, 0x000540C},         // SPEAKER ON             // 0
                                    {SONY,  15, 0x000540C},         // SPEAKER OFF
                                    {SONY,  15, 0x000140C},         // SPEAKER MUTE
                                    {SONY,  15, 0x000140C},         // SPEAKER UNMUTE
                                    {SONY,  15, 0x000240C},         // SPEAKER VOLUME UP
                                    {SONY,  15, 0x000640C},         // SPEAKER VOLUME DOWN
                                  };

void turn_on_speaker(void)
{
	if(!is_speaker_on())
		ir_send(ir_cmds[DEV_SPEAKER_ON]);
}

void turn_off_speaker(void)
{
	if(is_speaker_on())
		ir_send(ir_cmds[DEV_SPEAKER_OFF]);
}

void speaker_mute(void)
{
  ir_send(ir_cmds[DEV_SPEAKER_MUTE]);
}

void speaker_unmute(void)
{
  ir_send(ir_cmds[DEV_SPEAKER_UNMUTE]);
}

void speaker_vol_up(void)
{
  ir_send(ir_cmds[DEV_SPEAKER_VOL_UP]);
  delay(100);
  ir_send(ir_cmds[DEV_SPEAKER_VOL_UP]);
}

void speaker_vol_down(void)
{
  ir_send(ir_cmds[DEV_SPEAKER_VOL_DOWN]);
  delay(100);
  ir_send(ir_cmds[DEV_SPEAKER_VOL_DOWN]);
}

void speaker_vol_min(void) {
  for(int i=0; i < VOL_MAX_MIN_CNT; i++) {
    speaker_vol_down();
    delay(100);  
  }
}

void speaker_vol_max(void) {
  for(int i=0; i < VOL_MAX_MIN_CNT; i++) {
    speaker_vol_up();
    delay(100);  
  }
}

#endif
