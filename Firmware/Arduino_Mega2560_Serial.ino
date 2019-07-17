/****************************************************************************************	
**  This is example LINX firmware for use with the Arduino Mega 2560 with the serial 
**  interface enabled.
**
**  For more information see:           www.labviewmakerhub.com/linx
**  For support visit the forums at:    www.labviewmakerhub.com/forums/linx
**  
**  Written By Sam Kristoff
**
**  BSD2 License.
****************************************************************************************/	

//Include All Peripheral Libraries Used By LINX
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h>

//Include Device Sepcific Header From Sketch>>Import Library (In This Case LinxArduinoMega2560.h)
//Also Include Desired LINX Listener From Sketch>>Import Library (In This Case LinxSerialListener.h)
#include <LinxArduinoMega2560.h>
#include <LinxSerialListener.h>

//Create A Pointer To The LINX Device Object We Instantiate In Setup()
LinxArduinoMega2560* LinxDevice;

//Initialize LINX Device And Listener
void setup()
{
  
  //Instantiate The LINX Device
  LinxDevice = new LinxArduinoMega2560();
  
  //The LINX Listener Is Pre Instantiated, Call Start And Pass A Pointer To The LINX Device And The UART Channel To Listen On
  LinxSerialConnection.Start(LinxDevice, 0);  

  //Setting PWM pins 9 and 10 PWM frequency to 30.64 Hz for Multicomp SSR
  
  TCCR2B = TCCR2B & 0b11111000 | 0x07; 
  
  // for PWM frequency of 30.64 Hz 0x07 is the right setting.
  
  //This frequency setting is for using Multicomp SSR, that cannot input too high frequency without cutting the usable scale.
  //With, lowest possible, ~30 Hz frequency (setting 0x07 for timer 2) almost full scale is usable, percentages balow 10% are not usable
  //Setting 0x06 cuts out about 50% marker.
  /*
   * Settings:
   * https://etechnophiles.com/change-frequency-pwm-pins-arduino-uno/
   * https://forum.arduino.cc/index.php?topic=72092.0
   * 
   * Arduino Mega has different pins on timers than Uno in link. Mega timers
  timer 0 (controls pin 13, 4);
  timer 1 (controls pin 12, 11);
  timer 2 (controls pin 10, 9);
  timer 3 (controls pin 5, 3, 2);
  timer 4 (controls pin 8, 7, 6);
  */
}

void loop()
{
  //Listen For New Packets From LabVIEW
  LinxSerialConnection.CheckForCommands();
  
  //Your Code Here, But It will Slow Down The Connection With LabVIEW
}
