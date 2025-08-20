#include "./monitor.h"

// Global alert counter for testability
int alert_count = 0;

void displayAlert(const char* message) {
    // Alert functionality - placeholder that can be extended
    // Increment counter for testing purposes
    alert_count++;
    
    // In a real system, this would display the alert:
    // printf("*** ALERT: %s ***\n", message);
    // or log to file, send notification, etc.
}

void resetAlertCount(void) {
    alert_count = 0;
}

int getAlertCount(void) {
    return alert_count;
}

// Individual vital check functions with alerts (CCN: 2 each)
int isTemperatureOk(float temperature) {
    if (temperature > 102 || temperature < 95) {
        displayAlert("Temperature is critical!");
        return 0;
    }
    return 1;
}

int isPulseRateOk(float pulseRate) {
    if (pulseRate < 60 || pulseRate > 100) {
        displayAlert("Pulse Rate is out of range!");
        return 0;
    }
    return 1;
}

int isSpo2Ok(float spo2) {
    if (spo2 < 90) {
        displayAlert("Oxygen Saturation out of range!");
        return 0;
    }
    return 1;
}

// Main vitals check function - improved for testability (CCN: 1)
int vitalsOk(float temperature, float pulseRate, float spo2) {
    // Check all vitals individually to ensure:
    // 1. All alerts are displayed (not just first failure)
    // 2. Testing is predictable (no short-circuit evaluation)
    // 3. Better user feedback (see all issues at once)
    
    int tempOk = isTemperatureOk(temperature);
    int pulseOk = isPulseRateOk(pulseRate);
    int spo2Ok = isSpo2Ok(spo2);
    
    // Return 1 only if ALL vitals are OK
    return tempOk && pulseOk && spo2Ok;
}

// Pure functions for unit testing - no side effects (CCN: 1 each)
int isTemperatureInRange(float temperature) {
    return (temperature >= 95 && temperature <= 102) ? 1 : 0;
}

int isPulseRateInRange(float pulseRate) {
    return (pulseRate >= 60 && pulseRate <= 100) ? 1 : 0;
}

int isSpo2InRange(float spo2) {
    return (spo2 >= 90) ? 1 : 0;
}

// Pure version of vitalsOk - completely testable (CCN: 1)
int areVitalsInRange(float temperature, float pulseRate, float spo2) {
    return isTemperatureInRange(temperature) && 
           isPulseRateInRange(pulseRate) && 
           isSpo2InRange(spo2);
}
