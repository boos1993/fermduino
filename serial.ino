void initializeSerial() {
  Serial.begin(115200);    // We'll send debugging information via the Serial monitor
  infoMessage("FermDuino v0.5");
}


void processCommands() {
    
}

void infoMessage(char* infoText) {
  StaticJsonBuffer<400> jsonOutputBuffer;

  JsonObject& root = jsonOutputBuffer.createObject();
  root["messageType"] = "info";
  root["info"] = infoText;
  
  root.prettyPrintTo(Serial);
}

void dataMessage() {
  StaticJsonBuffer<400> jsonOutputBuffer;

  JsonObject& root = jsonOutputBuffer.createObject();
  root["messageType"] = "data";
  root["systemElapsedSeconds"] = systemElapsedSeconds;
  root["startupDelay"] = startupDelay;
  root["systemMode"] = (int)systemMode;
  root["externalTemp"] = externalTemp;
  
  JsonObject& ferm1 = root.createNestedObject("ferm1");
  ferm1["MinSetpoint"] = ferm1MinSetpoint;
  ferm1["MaxSetpoint"] = ferm1MaxSetpoint;
  ferm1["Hysteresis"] = ferm1Hysteresis;
  ferm1["MinCoolCycle"] = ferm1MinCoolCycle;
  ferm1["MinHeatCycle"] = ferm1MinHeatCycle;
  ferm1["CycleDelay"] = ferm1CycleDelay;
  ferm1["Temp"] = ferm1Temp;
  ferm1["State"] = (int)ferm1State;
  ferm1["CurrentCycleTimer"] = ferm1CurrentCycleTimer;
  ferm1["FanSpeed"] = ferm1FanSpeed;
  
  root.prettyPrintTo(Serial);

}
