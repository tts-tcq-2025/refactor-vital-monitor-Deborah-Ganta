#pragma once
// Alert display function (CCN: 1)
void displayAlert(const char* message);

// Main vital monitoring functions with alerts (CCN <= 2 each)
int isTemperatureOk(float temperature);    
int isPulseRateOk(float pulseRate);        
int isSpo2Ok(float spo2);                  

// Main function to check if all vitals are within normal range (CCN: 1)
// Returns 1 if all vitals are OK, 0 if any vital is out of range
// Improved: checks ALL vitals (no short-circuit) for better testability
int vitalsOk(float temperature, float pulseRate, float spo2);

// Pure testable functions (no side effects) - for unit testing (CCN: 1 each)
int isTemperatureInRange(float temperature);  
int isPulseRateInRange(float pulseRate);      
int isSpo2InRange(float spo2);                
int areVitalsInRange(float temperature, float pulseRate, float spo2);

// Test helper functions for monitoring alert behavior
extern int alert_count;  // Global counter for testing alerts
void resetAlertCount(void);
int getAlertCount(void);
