#pragma once

int vitalsOk(float temperature, float pulseRate, float spo2);
 
// Individual vital check functions (CCN <= 2 each)
// Returns 1 if vital is OK, 0 if out of range
int isTemperatureOk(float temperature);    // CCN: 2
int isPulseRateOk(float pulseRate);        // CCN: 2
int isSpo2Ok(float spo2);                  // CCN: 2
 
// Alert display function (CCN: 1)
void displayAlert(const char* message);
