#include "./monitor.h"
#include <stdio.h>

// Simple test without external dependencies
int main() {
    printf("=== Medical Monitor Test Program ===\n\n");
    
    // Test normal values
    printf("Testing normal values (98.6°F, 72 bpm, 98%% SpO2):\n");
    int result1 = vitalsOk(98.6, 72, 98);
    printf("Result: %s\n\n", result1 ? "VITALS OK" : "VITALS NOT OK");
    
    // Test out of range temperature
    printf("Testing high temperature (103°F, 72 bpm, 98%% SpO2):\n");
    int result2 = vitalsOk(103, 72, 98);
    printf("Result: %s\n\n", result2 ? "VITALS OK" : "VITALS NOT OK");
    
    // Test out of range pulse
    printf("Testing high pulse rate (98.6°F, 110 bpm, 98%% SpO2):\n");
    int result3 = vitalsOk(98.6, 110, 98);
    printf("Result: %s\n\n", result3 ? "VITALS OK" : "VITALS NOT OK");
    
    // Test out of range spo2
    printf("Testing low SpO2 (98.6°F, 72 bpm, 85%% SpO2):\n");
    int result4 = vitalsOk(98.6, 72, 85);
    printf("Result: %s\n\n", result4 ? "VITALS OK" : "VITALS NOT OK");
    
    printf("=== Individual Function Tests ===\n");
    
    // Test individual functions
    printf("Temperature 98.6°F: %s\n", isTemperatureOk(98.6) ? "OK" : "NOT OK");
    printf("Pulse Rate 72 bpm: %s\n", isPulseRateOk(72) ? "OK" : "NOT OK");
    printf("SpO2 98%%: %s\n\n", isSpo2Ok(98) ? "OK" : "NOT OK");
    
    printf("=== Boundary Value Tests ===\n");
    
    // Test boundary values
    printf("Temperature 95°F (boundary): %s\n", isTemperatureOk(95) ? "OK" : "NOT OK");
    printf("Temperature 102°F (boundary): %s\n", isTemperatureOk(102) ? "OK" : "NOT OK");
    printf("Pulse Rate 60 bpm (boundary): %s\n", isPulseRateOk(60) ? "OK" : "NOT OK");
    printf("Pulse Rate 100 bpm (boundary): %s\n", isPulseRateOk(100) ? "OK" : "NOT OK");
    printf("SpO2 90%% (boundary): %s\n", isSpo2Ok(90) ? "OK" : "NOT OK");
    
    printf("\n=== Test Complete ===\n");
    
    return 0;
}
