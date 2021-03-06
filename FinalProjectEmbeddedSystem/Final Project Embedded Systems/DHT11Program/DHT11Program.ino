#include <dht11.h>

dht11 DHT;
//Pin 4 of Arduino to Data of DHT11
#define DHT11_PIN 2
#define dev1 3
#define dev2 4
#define dev3 5
#define dev4 6

//Structure to define a temperature Sensor
struct tempSensor{
  int humidity;
  int temp;
};

//A house can have up to 8 devices connected
/// 1 temperature sensor
/// 7 ON OFF type devices
struct House {
  struct tempSensor sensor;
  /*
  *Each bit defines ON or OFF state
   *for the number of device in its bit position
   */
  char stateOfDevices;
};

struct House myHouse; 
String inString = "";

void setup()
{
  Serial.begin(9600);
  int check;
  //Serial.print("DHT11 STATUS – \t");
  check = DHT.read(DHT11_PIN);
  //check status
  switch (check)
  {
  case DHTLIB_OK:
    Serial.print("OK\n");
    break;
  case DHTLIB_ERROR_CHECKSUM:
    //Serial.print("Checksum error\n");
    break;
  case DHTLIB_ERROR_TIMEOUT:
    //Serial.print("Timeout error\n");
    break;
  default:
    //Serial.print("Unknown error\n");
    break;
  }

  pinMode(dev1,OUTPUT);
  pinMode(dev2,OUTPUT);
  pinMode(dev3,OUTPUT);
  pinMode(dev4,OUTPUT);

}

void loop()
{
  int check;

  check = readNumberFromSerial();
  turnOnOffDevices(check);
  //Serial.print(check);
  inString = "";

  DHT.read(DHT11_PIN);
  myHouse.sensor.temp = DHT.temperature;
  myHouse.sensor.humidity = DHT.humidity;
  myHouse.stateOfDevices = DHT.temperature;

  //  //humidity and temperature output
  //  Serial.print("H");
  //  Serial.print(myHouse.sensor.humidity, 1);
  //  Serial.print(" ");
  //  Serial.print("T");
    Serial.println(myHouse.sensor.temp, 1);
  //  turnOnOffDevices(myHouse.stateOfDevices);

  delay(1000);
}

/*
*This Function is for read digit from serial
 */
int readNumberFromSerial(){
 static int lastState = 0;
 
  if(Serial.available() > 0)
  {
    while(Serial.available() > 0)
    {
      int inChar = Serial.read();
  
      if( inChar >= 48 && inChar <= 57)
      {
        inString += (char)inChar;
      }
  
    }
    
    lastState = inString.toInt();
    return lastState;
  }
  
  return lastState;
}

/*
*This functions recieves the char with the eight states
 *of the on-off devices in the house and turns on or off
 *the corresponding port i the arduino.
 */
void turnOnOffDevices(int value)
{
  //Primer Device attached to port 3
  if( value&0x01 ){
    digitalWrite(dev1,HIGH);
  }
  else{
    digitalWrite(dev1,LOW);
  }

  //Primer Device attached to port 4
  if( value&0x02 ){
    digitalWrite(dev2,HIGH);
  }
  else{
    digitalWrite(dev2,LOW);
  }

  //Primer Device attached to port 5
  if( value&0x04 ){
    digitalWrite(dev3,HIGH);
  }
  else{
    digitalWrite(dev3,LOW);
  }

  //Primer Device attached to port 6
  if( value&0x08 ){
    digitalWrite(dev4,HIGH);
  }
  else{
    digitalWrite(dev4,LOW);
  }

}
