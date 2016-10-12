
#include <SoftwareSerial.h> 
#include <EEPROM.h>

float maxv, concentration;
int ratio, humi, kelv, cel, fah,CO, NO2, circ = 5, heat = 6;
unsigned long sampletime_ms=30000;
unsigned long starttime, endtime;
unsigned long duration, lowpulseoccupancy;
int addr = 0;

SoftwareSerial myserial(10, 11); 

void setup()
{

  delay(100);  // Short delay, wait for the Mate to send back CMD
  myserial.begin(9600);  // Start bluetooth serial at 9600
  Serial.begin(115200); //Serial communication for Arduino Serial Monitor

  pinMode(circ, OUTPUT);
  pinMode(heat, OUTPUT);
}

void GetTemp()
{
cel = (5.0 * analogRead(A2) * 100.0) / 1024;

}

void loop()
{
  //call up the calculation functions
  GetHumi();
  GetTemp();
  GetCO();
  GetNO2();
  GetDust();
  //Display of humidity
  myserial.print("Humidity: ");
  myserial.print(humi);
  myserial.print("\n");  
    EEPROM.write(addr,humi);
    ++addr;
  Serial.print("Humidity: ");
  Serial.print(humi);
  Serial.print("% ");
  //Display of CO gas sensor
  myserial.print("CO Gas: ");
  myserial.print(CO);
  myserial.print("\n");
    EEPROM.write(addr,CO);
    ++addr;
  Serial.print("CO Gas: ");
  Serial.print(CO);
  Serial.print("% ");

  //Display of temperature in K, C, and F
  
  myserial.print("Temperature: ");
  myserial.print(cel);
  myserial.print("\n");
      EEPROM.write(addr,cel);
      ++addr;
  Serial.print("Temperature: ");
  Serial.print(cel);
  Serial.print("C ");
  //Display of NO2 conc
  myserial.print("NO2 Gas: ");
  myserial.print(NO2);
  myserial.print("\n");
      EEPROM.write(addr,NO2);
      ++addr;
  Serial.print("NO2 Gas: ");
  Serial.print(NO2);
  Serial.println("%");
  //Display of Dust ratio
  myserial.print("Dust Ratio: ");
  myserial.print(ratio);
  myserial.print("\n");
        EEPROM.write(addr,ratio);
        ++addr;
  Serial.print("Dust Ratio: ");
  Serial.print(ratio);
  Serial.println("%");
  
  //Display of Dust conc
  myserial.print("Dust Conc: ");
  myserial.print(concentration);
  myserial.print("\n");
  Serial.print("Dust Conc: ");
  Serial.println(concentration);

  delay(270000);

}

void GetCO()
{
  digitalWrite(circ, LOW);
  analogWrite(heat, 245);
  delay(14);
  analogWrite(heat, 0);
  delay(981);
  digitalWrite(circ, HIGH);
  delay(3);
  int val1 = analogRead(A1);
  CO = map(val1, 0 , 1023, 0, 5);
}

void GetHumi()
{
  float val0 = analogRead(A0);
  float maxv = (3.27-(0.006706*cel));
  humi = ((((val0/1023)*5)-0.8)/maxv)*100;
}

void GetNO2()
{
  int val3 = analogRead(A3);
  NO2 = map(val3, 1023, 0, 0, 5);
}
void GetDust(){
  starttime=millis();

  while(1){
  duration = pulseIn(2, LOW);
  lowpulseoccupancy += duration;
  endtime = millis();
  
  if ((endtime-starttime) > sampletime_ms){
    break;
    }
  }
    ratio = (lowpulseoccupancy)/(sampletime_ms*10);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    lowpulseoccupancy = 0;
  
}

int map(int x, float in_min, float in_max, float out_min, float out_max)
{
  return x/4;
}
