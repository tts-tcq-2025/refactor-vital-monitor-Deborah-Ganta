#include "./monitor.h"

void showAlert(const char* message) {

}

// Main function - improved to check ALL vitals 
int vitalsOk(float temperature, float pulseRate, float spo2) {
  int allOk = 1;
  if (temperature > 102 || temperature < 95) {
    showAlert("Temperature is critical!");
    allOk = 0;
  }
  if (pulseRate < 60 || pulseRate > 100) {
    showAlert("Pulse Rate is out of range!");
    allOk = 0;
  }
  if (spo2 < 90) {
    showAlert("Oxygen Saturation out of range!");
    allOk = 0;
  }
  return allOk;
}
