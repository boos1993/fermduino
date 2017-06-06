void initializeOutputs() {
  
  pinMode(ferm1CompressorRelayPin, OUTPUT);
  digitalWrite(ferm1CompressorRelayPin, HIGH);
  pinMode(ferm1HeaterRelayPin, OUTPUT);
  digitalWrite(ferm1HeaterRelayPin, HIGH);
}

void setOutputs() {
     switch(ferm1State) {
    
        case standby: {
            digitalWrite(ferm1CompressorRelayPin, HIGH);
            digitalWrite(ferm1HeaterRelayPin, HIGH);
          break; 
        }
        case compressor: {
            digitalWrite(ferm1CompressorRelayPin, LOW);
            digitalWrite(ferm1HeaterRelayPin, HIGH);
          break; 
        }
        case heater: {
            digitalWrite(ferm1CompressorRelayPin, HIGH);
            digitalWrite(ferm1HeaterRelayPin, LOW);
          break; 
        }
     }
}
