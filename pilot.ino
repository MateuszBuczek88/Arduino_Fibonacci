
#include <IRremote.h>
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

void drawn(unsigned long int x) {
  u8g.setFont(u8g_font_freedoomr25n);
  String to_draw = String(x);
  u8g.drawStr( 0, 26, to_draw.c_str());

}

int ir_to_digit (unsigned long int x) {
  switch( x ) {
case 3238126971:
    return 0;
    break;   
case 2534850111:
    return 1;
    break; 
case 1033561079:
    return 2;
    break;
case 1635910171:
    return 3;
    break;
case 2351064443:
    return 4;
    break;
case 1217346747:
    return 5;
    break;
case 71952287:
    return 6;
    break;
case 851901943:
    return 7;
    break;
case 465573243:
    return 8;
    break;  
case 1053031451:
    return 9;
    break;         
default:
    break;
  }
}

int fib(int x) {
  if(x == 0) return 0;
  if(x == 1) return 1;
  else return fib(x-1) + fib(x-2);
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  } else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  } else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  } else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }
  pinMode(8, OUTPUT);
}

void loop()
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    u8g.firstPage();
    
    do {
      int pass = results.value;
      drawn(fib(ir_to_digit(results.value)));
      } while(u8g.nextPage());
      
      irrecv.resume();
      delay(1);
  }
}
