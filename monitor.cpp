#include "./monitor.h"

void displayAlert(const char* message) {
    // Alert functionality - could be implemented with available I/O
    // For now, just a placeholder that can be extended
}

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

int vitalsOk(float temperature, float pulseRate, float spo2) {
    return isTemperatureOk(temperature) && 
           isPulseRateOk(pulseRate) && 
           isSpo2Ok(spo2);
}
