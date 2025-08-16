#include <gtest/gtest.h>
#include "./monitor.h"

// Test for overall vitals function
TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_FALSE(vitalsOk(99, 102, 70));  // pulse rate too high
  ASSERT_TRUE(vitalsOk(98.1, 70, 98));  // all vitals normal
}

// Test individual temperature function
TEST(Monitor, TemperatureTests) {
  ASSERT_FALSE(isTemperatureOk(94));    // too low
  ASSERT_FALSE(isTemperatureOk(103));   // too high
  ASSERT_TRUE(isTemperatureOk(98.6));   // normal
  ASSERT_TRUE(isTemperatureOk(95));     // boundary low
  ASSERT_TRUE(isTemperatureOk(102));    // boundary high
}

// Test individual pulse rate function
TEST(Monitor, PulseRateTests) {
  ASSERT_FALSE(isPulseRateOk(59));      // too low
  ASSERT_FALSE(isPulseRateOk(101));     // too high
  ASSERT_TRUE(isPulseRateOk(75));       // normal
  ASSERT_TRUE(isPulseRateOk(60));       // boundary low
  ASSERT_TRUE(isPulseRateOk(100));      // boundary high
}

// Test individual spo2 function
TEST(Monitor, Spo2Tests) {
  ASSERT_FALSE(isSpo2Ok(89));           // too low
  ASSERT_TRUE(isSpo2Ok(95));            // normal
  ASSERT_TRUE(isSpo2Ok(90));            // boundary
  ASSERT_TRUE(isSpo2Ok(100));           // maximum normal
}

// Test combinations of vitals
TEST(Monitor, CombinationTests) {
  ASSERT_FALSE(vitalsOk(94, 70, 95));   // temperature too low
  ASSERT_FALSE(vitalsOk(98, 59, 95));   // pulse too low
  ASSERT_FALSE(vitalsOk(98, 70, 89));   // spo2 too low
  ASSERT_FALSE(vitalsOk(103, 101, 89)); // all vitals out of range
  ASSERT_TRUE(vitalsOk(98.6, 72, 98));  // all vitals normal
}
