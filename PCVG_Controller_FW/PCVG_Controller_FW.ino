#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <stdlib.h>

#define OLED_RESET 4  //4
Adafruit_SSD1306 display(OLED_RESET);

const int ID_PIN = A4;
const int SIG_PIN = A3;

enum gaugeType {
  notFound,
  fulRangPirani, //idVal 981
  fulRangCombined, //idVal 819
  coldCathode //idVal 655
};

gaugeType curType = notFound;
float curPressure = 0;

//Setup routine
void setup() {

  pinMode(ID_PIN, INPUT);
  pinMode(SIG_PIN, INPUT);
  
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    
  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setTextColor(WHITE);

}

//Read the voltage at the ID_PIN and set the current gauge type.
void identifyGauge() {
  int idVal = analogRead(ID_PIN);
  if ((idVal >= 500) && (idVal < 740)) {
    curType = coldCathode;
  }
  else if ((idVal >= 740) && (idVal < 900)) {
    curType = fulRangCombined;
  }
  else if (idVal >= 900) {
    curType = fulRangPirani;
  }
  else {
    curType = notFound;
  }
}

//Read the voltage at the SIG_PIN, average reading numAvgs times and convert it into a pressure using the formula provided in the datasheet.
void updatePressure() {

  float tmpReading = 0;
  int numAvgs = 50;

  for (int i=0; i < numAvgs; i++) {
    tmpReading += analogRead(SIG_PIN);
    delay(20);
  }

  float avgd = tmpReading / numAvgs; //average reading
  //Serial.println("AVG SIG VAL: " + String(avgd));
  float pressure = pow(10.00, 1.667*(avgd*21/2048)-11.33); //resistor divider and ADC resolution
  curPressure = pressure;

}

//Print the connected gauge type on the display.
void showGaugeType() {
  
  display.setTextSize(1);
  
  if (curType == notFound) {
    display.println("No Gauge found!");
  }
  else if (curType == fulRangPirani) {
    display.println("FRG - Pirani Only");
  }
  else if (curType == fulRangCombined) {
    display.println("FRG - Combined");
  }
  else {
    display.println("Cold Cathode Gauge");
  }

  display.display();
}

//Format the current pressure into a mantissa-exponent format and print it on the display.
char pString[10] = "";
void showPressureReading() {

  display.setTextSize(2);
  display.println("Pressure:");
  //display.println();
  
  display.setTextSize(2.5);
  dtostre(curPressure,pString,2,DTOSTR_ALWAYS_SIGN | DTOSTR_UPPERCASE);
  char *movedP = pString + 1;
  display.println(movedP);

  display.setTextSize(2);
  display.println("      mbar");
  display.display();
  
}

//Main worker loop
void loop() {

  display.clearDisplay();
  identifyGauge();
  updatePressure();

  display.setCursor(0,0);

  showGaugeType();
  showPressureReading();

  //OPT: If request code was received over serial interface, reply with current pressure.
  if (Serial.available() > 0) {
    int incomingByte;
    int index;
    incomingByte = Serial.read();
    index = incomingByte - 48;
    Serial.println(pString);
  }

  delay(50);
  

}
