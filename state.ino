
void setState(enum STATE newState) {
  ferm1State = newState;
  ferm1CurrentCycleTimer = 0;
}

void calculateState_off();
void calculateState_dual();
void calculateState_cool();
void calculateState_heat();

void calculateState(void) {
    if (startupDelay > 0) return;
    
    switch(systemMode) {
      
      case off :
         calculateState_off();
       break; 
      
      case dual :
         calculateState_dual();
       break; 
      
      case cool :
         calculateState_cool();
       break; 
      
      case heat :
         calculateState_heat();
       break; 
    }
}


void calculateState_off(void) {
     switch(ferm1State) {

              case standby: {
                  return; // Do nothing
                break; 
              }
              case compressor: {
                if (ferm1CurrentCycleTimer < ferm1MinCoolCycle) return; // Wait until the minimum cycle time has elapsed
                setState(standby);
                break; 
              }
              case heater: {
                if (ferm1CurrentCycleTimer < ferm1MinHeatCycle) return; // Wait until the minimum cycle time has elapsed
                setState(standby);
                break; 
              }
      }      
 }
 
 void calculateState_dual(void) {
     switch(ferm1State) {
              case standby: {
               if (ferm1CurrentCycleTimer < ferm1CycleDelay) return; // Wait until the minimum cycle delay time has elapsed
                if (ferm1Temp > ferm1MaxSetpoint + ferm1Hysteresis && externalTemp > ferm1MaxSetpoint) setState(compressor);
                if (ferm1Temp < ferm1MinSetpoint - ferm1Hysteresis && externalTemp < ferm1MinSetpoint) setState(heater);
                break; 
              }
              case compressor: {
                if (ferm1CurrentCycleTimer < ferm1MinCoolCycle) return; // Wait until the minimum cycle time has elapsed
                if (ferm1Temp < ferm1MinSetpoint - ferm1Hysteresis) setState(standby);
                break; 
              }
              case heater: {
                if (ferm1CurrentCycleTimer < ferm1MinHeatCycle) return; // Wait until the minimum cycle time has elapsed
                if (ferm1Temp > ferm1MaxSetpoint + ferm1Hysteresis) setState(standby);
                break; 
              }
      }      
 }
 
  void calculateState_cool(void) {
     switch(ferm1State) {
              case standby: {
               if (ferm1CurrentCycleTimer < ferm1CycleDelay) return; // Wait until the minimum cycle delay time has elapsed
                if (ferm1Temp > ferm1MaxSetpoint + ferm1Hysteresis) setState(compressor);
                break; 
              }
              case compressor: {
                if (ferm1CurrentCycleTimer < ferm1MinCoolCycle) return; // Wait until the minimum cycle time has elapsed
                if (ferm1Temp < ferm1MinSetpoint - ferm1Hysteresis) setState(standby);
                break; 
              }
              case heater: {
                if (ferm1CurrentCycleTimer < ferm1MinHeatCycle) return; // Wait until the minimum cycle time has elapsed
                setState(standby);
                break; 
              }
      }      
 }
 
  void calculateState_heat(void) {
     switch(ferm1State) {
              case standby: {
               if (ferm1CurrentCycleTimer < ferm1CycleDelay) return; // Wait until the minimum cycle delay time has elapsed
                if (ferm1Temp < ferm1MinSetpoint - ferm1Hysteresis) setState(heater);
                break; 
              }
              case compressor: {
                if (ferm1CurrentCycleTimer < ferm1MinCoolCycle) return; // Wait until the minimum cycle time has elapsed
                setState(standby);
                break; 
              }
              case heater: {
                if (ferm1CurrentCycleTimer < ferm1MinHeatCycle) return; // Wait until the minimum cycle time has elapsed
                if (ferm1Temp > ferm1MaxSetpoint + ferm1Hysteresis) setState(standby);
                break; 
              }
      }      
 }
