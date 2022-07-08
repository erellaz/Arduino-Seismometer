#include <SPI.h> //Serial Port Interface
#include <SD.h> //for SD Card access
#define ARDUINO_SAMD_ZERO //solves warning from FastLED library, see here: https://github.com/FastLED/FastLED/issues/393
#include <FastLED.h> // for access to function like EVERY_N_MILLISECOND
#include <Arduino_MKRGPS.h> //for GPS position and clock

const int chipSelect = SDCARD_SS_PIN;
const int resolution=12; //resolution in bits
const float voltscalar=1000*3.25/pow(2,resolution);//scale from bits to milli-volts
const float bias=pow(2,resolution-1)-10; // bias bits
const int analogPin = A0; //We use analog pin A0
unsigned long TimeElapsed;

void setup() {
  
  // Computer serial port inititialization_______________________________________
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // SD Card initialization______________________________________________________
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  //Analog to Digital Converter initialization_________________________________
  analogReadResolution(resolution); // change reolution to 12 bits

  // GPS initialization________________________________________________________ 
  // If you are using the MKR GPS as shield, change the next line to pass
  // the GPS_MODE_SHIELD parameter to the GPS.begin(...)
  if (!GPS.begin()) {
    Serial.println("Failed to initialize GPS!");
    while (1);
  }
  
}



//______________________________________________________________________________
void loop() {
  
  EVERY_N_MILLISECONDS(5) { 
  // read sensor and append to the string:    
    float sensor = ((analogRead(analogPin)-bias)*voltscalar);
    TimeElapsed = millis();
    String dataString = String(sensor);
    
    
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(dataString);
    dataFile.print(", ");
    dataFile.println(String(TimeElapsed));
    dataFile.close();
    // print to the serial port too:
    Serial.print(dataString);
    Serial.print(", ");
    Serial.println(String(TimeElapsed));
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  }
  
//---------------------------------------------------------------------------------
   EVERY_N_SECONDS(15) {
   if (GPS.available()) {
    // read GPS values
    float latitude   = GPS.latitude();
    float longitude  = GPS.longitude();
    float altitude   = GPS.altitude();
    unsigned long epochTime = GPS.getTime();
    int   satellites = GPS.satellites();

    // print GPS values to SD Card_________________________________________________
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    // if the file is available, write to it:
    if (dataFile) {
        dataFile.print("Location: ");
        dataFile.print(latitude, 7);
        dataFile.print(", ");
        dataFile.print(longitude, 7);
    
        dataFile.print("Altitude: ");
        dataFile.print(altitude);
        dataFile.print("m");
    
        dataFile.print("Number of satellites: ");
        dataFile.print(satellites);
    
        dataFile.print("Epoch time: ");
        dataFile.println(epochTime);
    }
    
    // print GPS values to Serial__________________________________________________
    Serial.print("Location: ");
    Serial.print(latitude, 7);
    Serial.print(", ");
    Serial.print(longitude, 7);

    Serial.print("Altitude: ");
    Serial.print(altitude);
    Serial.print("m");

    Serial.print("Number of satellites: ");
    Serial.print(satellites);

    Serial.print("Epoch time: ");
    Serial.println(epochTime);
  }
  
  else{
    Serial.println("GPS unavailable-----------------------------------------");
   }
   
   }
}
