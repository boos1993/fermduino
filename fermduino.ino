#include <OneWire.h>
#include <DallasTemperature.h>
#include <SimpleTimer.h>
#include <ArduinoJson.h>
#include "types.h"

#define ONE_WIRE_BUS A5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// the timer object
SimpleTimer timer;

//******************************************************************
//                           System
//******************************************************************
unsigned long systemElapsedSeconds = 0;

int startupDelay = 10;
enum MODE systemMode = dual;

float externalTemp = 72.0;                // The current temperature of the external environment

//------------------------------------------------------------------


//******************************************************************
//                         Fermenter #1
//******************************************************************
#define ferm1CompressorRelayPin A3
#define ferm1HeaterRelayPin A4

float ferm1MinSetpoint = 60.0;    // The min temperature that the fermenter can reach before starting a heat cycle
float ferm1MaxSetpoint = 62.0;      // The max temperature that the fermenter can reach before starting a cool cycle
float ferm1Hysteresis = 0.25;       // The amount of temperature hysteresis to use when calculating cycle startup/shutoff
float ferm1MinCoolCycle = 60;       // The minimum amount of time for a cool cycle to run
float ferm1MinHeatCycle = 60;       // The minimum amount of time for a heat cycle to run
float ferm1CycleDelay = 30;         // The minimum amount of time between heat/cool cycles

float ferm1Temp = 72.0;                // The current temperature of the fermenter

enum STATE ferm1State = standby;        // The current operating state of the fermenter heat/cool functionality
int ferm1CurrentCycleTimer = 0;     // The elapsed time of the current heat/cool/standby/off cycle

float ferm1FanSpeed = 0;            // The fan speed setpoint
//------------------------------------------------------------------

void initializeSerial();
void processCommands();
void infoMessage();
void dataMessage();

void calculateState();

void initializeOutputs();
void setOutputs();

void setup(void) {
  
  initializeOutputs();

  initializeSerial();
  
  sensors.begin();
  
  // Initialize timer 
  timer.setInterval(1000, callback);
}

void loop(void) {
  timer.run();
}
 
 void callback(){
  
  // Update timers
  if(startupDelay > 0)  startupDelay--;
  systemElapsedSeconds++;
  ferm1CurrentCycleTimer++;
  
  // Update temperature readings 
  sensors.requestTemperatures(); // Send the command to get temperatures
  ferm1Temp = DallasTemperature::toFahrenheit(sensors.getTempCByIndex(0)); 
  //externalTemp = DallasTemperature::toFahrenheit(sensors.getTempCByIndex(1)); 

  // Application logic
  processCommands(); // Process any incoming commands
  calculateState(); // Calculate the standby/compressor/heater state based on the mode
  
  setOutputs(); // Set the output ports
  
  dataMessage();  // Log the data to the serial port
  
  digitalWrite(13, !digitalRead(13));
}

void formatTimeDigits(char strOut[3], int num)
{
  strOut[0] = '0' + (num / 10);
  strOut[1] = '0' + (num % 10);
  strOut[2] = '\0';
}
