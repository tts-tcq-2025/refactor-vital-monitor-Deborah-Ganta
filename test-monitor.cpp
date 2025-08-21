#include "./monitor.h"

// Simple test framework - no external dependencies
int tests_run = 0;
int tests_passed = 0;

void test_assert(int condition, const char* message) {
  tests_run++;
  if (condition) {
    tests_passed++;
  }
}

// Test cases covering all conditions
void runTests() {
  // Original test cases
  test_assert(!vitalsOk(99, 102, 70), "Pulse high, SpO2 low should fail");
  test_assert(vitalsOk(98.1, 70, 98), "All normal should pass");
  
  // Individual vital failures
  test_assert(!vitalsOk(103, 72, 95), "High temperature should fail");
  test_assert(!vitalsOk(94, 72, 95), "Low temperature should fail");
  test_assert(!vitalsOk(98, 110, 95), "High pulse should fail");
  test_assert(!vitalsOk(98, 55, 95), "Low pulse should fail");
  test_assert(!vitalsOk(98, 72, 85), "Low SpO2 should fail");
  
  // Multiple failures - tests that ALL vitals are checked
  test_assert(!vitalsOk(103, 110, 85), "All vitals bad should fail");
  test_assert(!vitalsOk(94, 55, 89), "All vitals low should fail");
  
  // Boundary conditions
  test_assert(vitalsOk(95, 60, 90), "Lower boundaries should pass");
  test_assert(vitalsOk(102, 100, 90), "Upper boundaries should pass");
  test_assert(!vitalsOk(94.9, 60, 90), "Just below temp boundary should fail");
  test_assert(!vitalsOk(95, 59, 90), "Just below pulse boundary should fail");
  test_assert(!vitalsOk(95, 60, 89), "Just below SpO2 boundary should fail");
}

int main() {
  runTests();
  
  // Return 0 if all tests pass, 1 if any fail
  return (tests_passed == tests_run) ? 0 : 1;
}
