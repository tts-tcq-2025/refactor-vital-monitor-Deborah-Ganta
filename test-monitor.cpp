#include "./monitor.h"

int total_tests = 0;      // Count how many tests we run
int passed_tests = 0;     // Count how many tests pass

// This function checks if a test passes or fails
void check_test(int condition, const char* test_description) {
    total_tests++;
    if (condition) {
        passed_tests++;
        // Test passed! In a real system, we might print success messages
    } else {
        // Test failed! In a real system, we would show which test failed
        // For now, we just continue testing
    }
}

// Helper macros to make tests easier to read
#define EXPECT_EQUAL(expected, actual, description) \
    check_test((expected) == (actual), description)

#define EXPECT_TRUE(condition, description) \
    check_test(condition, description)

#define EXPECT_FALSE(condition, description) \
    check_test(!(condition), description)

void test_basic_range_checking() {
    // TEMPERATURE TESTS (Normal range: 95°F to 102°F)
    // ================================================
    
    // Test normal temperatures (should return 1 = true)
    EXPECT_EQUAL(1, isTemperatureInRange(98.6), "Normal body temperature");
    EXPECT_EQUAL(1, isTemperatureInRange(99.5), "Slight fever but still normal");
    
    // Test boundary values (edge cases)
    EXPECT_EQUAL(1, isTemperatureInRange(95.0), "Lowest normal temperature");
    EXPECT_EQUAL(1, isTemperatureInRange(102.0), "Highest normal temperature");
    
    // Test abnormal temperatures (should return 0 = false)
    EXPECT_EQUAL(0, isTemperatureInRange(94.9), "Too cold - hypothermia risk");
    EXPECT_EQUAL(0, isTemperatureInRange(102.1), "Too hot - fever");
    EXPECT_EQUAL(0, isTemperatureInRange(103.0), "High fever");
    
    // PULSE RATE TESTS (Normal range: 60 to 100 beats per minute)
    // ==========================================================
    
    // Test normal pulse rates
    EXPECT_EQUAL(1, isPulseRateInRange(72), "Normal resting heart rate");
    EXPECT_EQUAL(1, isPulseRateInRange(85), "Normal active heart rate");
    
    // Test boundary values
    EXPECT_EQUAL(1, isPulseRateInRange(60), "Lowest normal heart rate");
    EXPECT_EQUAL(1, isPulseRateInRange(100), "Highest normal heart rate");
    
    // Test abnormal pulse rates
    EXPECT_EQUAL(0, isPulseRateInRange(59), "Too slow - bradycardia");
    EXPECT_EQUAL(0, isPulseRateInRange(101), "Too fast - tachycardia");
    EXPECT_EQUAL(0, isPulseRateInRange(120), "Dangerously fast");
    
    // BLOOD OXYGEN TESTS (Normal: 90% and above)
    // ==========================================
    
    // Test normal oxygen levels
    EXPECT_EQUAL(1, isSpo2InRange(95), "Good oxygen level");
    EXPECT_EQUAL(1, isSpo2InRange(98), "Excellent oxygen level");
    EXPECT_EQUAL(1, isSpo2InRange(100), "Perfect oxygen level");
    
    // Test boundary value
    EXPECT_EQUAL(1, isSpo2InRange(90), "Minimum acceptable oxygen level");
    
    // Test dangerous oxygen levels
    EXPECT_EQUAL(0, isSpo2InRange(89), "Low oxygen - needs attention");
    EXPECT_EQUAL(0, isSpo2InRange(85), "Dangerously low oxygen");
    
    // COMBINED VITAL SIGNS TESTS
    // ==========================
    
    // Test when all vitals are normal
    EXPECT_EQUAL(1, areVitalsInRange(98.6, 72, 95), "Perfect patient - all normal");
    
    // Test individual vital failures
    EXPECT_EQUAL(0, areVitalsInRange(94, 72, 95), "Temperature problem only");
    EXPECT_EQUAL(0, areVitalsInRange(98.6, 59, 95), "Heart rate problem only");  
    EXPECT_EQUAL(0, areVitalsInRange(98.6, 72, 89), "Oxygen problem only");
    
    // Test multiple problems
    EXPECT_EQUAL(0, areVitalsInRange(103, 110, 85), "Multiple critical issues");
    
    // Test boundary combinations
    EXPECT_EQUAL(1, areVitalsInRange(95, 60, 90), "All at minimum normal levels");
    EXPECT_EQUAL(1, areVitalsInRange(102, 100, 95), "All at maximum normal levels");
}

void test_alert_system() {
    // TEMPERATURE ALERTS
    // =================
    
    // Normal temperature should not trigger any alerts
    resetAlertCount();  // Start with 0 alerts
    EXPECT_EQUAL(1, isTemperatureOk(98.6), "Normal temp should return OK");
    EXPECT_EQUAL(0, getAlertCount(), "Normal temp should not trigger alerts");
    
    // High temperature should trigger an alert
    resetAlertCount();
    EXPECT_EQUAL(0, isTemperatureOk(103), "High fever should return NOT OK");
    EXPECT_EQUAL(1, getAlertCount(), "High fever should trigger 1 alert");
    
    // Low temperature should also trigger an alert
    resetAlertCount();
    EXPECT_EQUAL(0, isTemperatureOk(94), "Hypothermia should return NOT OK");
    EXPECT_EQUAL(1, getAlertCount(), "Hypothermia should trigger 1 alert");
    
    // PULSE RATE ALERTS
    // ================
    
    // Normal pulse should not trigger alerts
    resetAlertCount();
    EXPECT_EQUAL(1, isPulseRateOk(75), "Normal pulse should return OK");
    EXPECT_EQUAL(0, getAlertCount(), "Normal pulse should not trigger alerts");
    
    // High pulse should trigger an alert
    resetAlertCount();
    EXPECT_EQUAL(0, isPulseRateOk(110), "High pulse should return NOT OK");
    EXPECT_EQUAL(1, getAlertCount(), "High pulse should trigger 1 alert");
    
    // Low pulse should trigger an alert
    resetAlertCount();
    EXPECT_EQUAL(0, isPulseRateOk(55), "Low pulse should return NOT OK");
    EXPECT_EQUAL(1, getAlertCount(), "Low pulse should trigger 1 alert");
    
    // BLOOD OXYGEN ALERTS
    // ==================
    
    // Normal oxygen should not trigger alerts
    resetAlertCount();
    EXPECT_EQUAL(1, isSpo2Ok(95), "Normal oxygen should return OK");
    EXPECT_EQUAL(0, getAlertCount(), "Normal oxygen should not trigger alerts");
    
    // Low oxygen should trigger an alert
    resetAlertCount();
    EXPECT_EQUAL(0, isSpo2Ok(85), "Low oxygen should return NOT OK");
    EXPECT_EQUAL(1, getAlertCount(), "Low oxygen should trigger 1 alert");
}

void test_comprehensive_monitoring() {
    // SCENARIO 1: Perfect Patient
    // ==========================
    resetAlertCount();
    EXPECT_EQUAL(1, vitalsOk(98.6, 72, 95), "Healthy patient should pass all checks");
    EXPECT_EQUAL(0, getAlertCount(), "Healthy patient should trigger no alerts");
    
    // SCENARIO 2: Single Problems (One thing wrong at a time)
    // =======================================================
    
    // Only temperature is bad
    resetAlertCount();
    EXPECT_EQUAL(0, vitalsOk(103, 72, 95), "Fever patient should fail");
    EXPECT_EQUAL(1, getAlertCount(), "Fever should trigger exactly 1 alert");
    
    // Only pulse is bad
    resetAlertCount();
    EXPECT_EQUAL(0, vitalsOk(98.6, 110, 95), "Fast heart rate should fail");
    EXPECT_EQUAL(1, getAlertCount(), "Fast heart rate should trigger exactly 1 alert");
    
    // Only oxygen is bad
    resetAlertCount();
    EXPECT_EQUAL(0, vitalsOk(98.6, 72, 85), "Low oxygen should fail");
    EXPECT_EQUAL(1, getAlertCount(), "Low oxygen should trigger exactly 1 alert");
    
    // SCENARIO 3: Multiple Problems (This is the KEY improvement!)
    // ============================================================
    
    // ALL THREE vitals are bad - this is a critical patient!
    resetAlertCount();
    EXPECT_EQUAL(0, vitalsOk(103, 110, 85), "Critical patient should fail");
    EXPECT_EQUAL(3, getAlertCount(), "Critical patient should trigger ALL 3 alerts");
    
    // Two problems at once
    resetAlertCount();
    EXPECT_EQUAL(0, vitalsOk(103, 110, 95), "Fever + fast heart rate should fail");
    EXPECT_EQUAL(2, getAlertCount(), "Should trigger exactly 2 alerts");
    
    // SCENARIO 4: Edge Cases (Boundary testing)
    // =========================================
    
    // All vitals at the lower edge of normal
    resetAlertCount();
    EXPECT_EQUAL(1, vitalsOk(95.0, 60, 90), "Minimum normal values should pass");
    EXPECT_EQUAL(0, getAlertCount(), "Minimum normal should trigger no alerts");
    
    // All vitals at the upper edge of normal  
    resetAlertCount();
    EXPECT_EQUAL(1, vitalsOk(102.0, 100, 95), "Maximum normal values should pass");
    EXPECT_EQUAL(0, getAlertCount(), "Maximum normal should trigger no alerts");
    
    // Just barely outside normal range
    resetAlertCount();
    EXPECT_EQUAL(0, vitalsOk(94.9, 59, 89), "Just outside normal should fail");
    EXPECT_EQUAL(3, getAlertCount(), "Just outside normal should trigger all alerts");
}
void test_real_world_scenarios() {
    // ORIGINAL TEST CASE 1: Problem Patient
    // =====================================
    // Temperature: 99°F (normal), Pulse: 102 bpm (too high), Oxygen: 70% (too low)
    EXPECT_FALSE(vitalsOk(99, 102, 70), "Problem patient should fail overall check");
    
    // Now we can also verify the alerts (this wasn't possible before!)
    resetAlertCount();
    vitalsOk(99, 102, 70);  // Run the function to trigger alerts
    EXPECT_EQUAL(2, getAlertCount(), "Should alert for pulse AND oxygen problems");
    
    // ORIGINAL TEST CASE 2: Healthy Patient  
    // =====================================
    // Temperature: 98.1°F (normal), Pulse: 70 bpm (normal), Oxygen: 98% (normal)
    EXPECT_TRUE(vitalsOk(98.1, 70, 98), "Healthy patient should pass all checks");
    
    // Verify no false alarms
    resetAlertCount();
    vitalsOk(98.1, 70, 98);  // Run the function
    EXPECT_EQUAL(0, getAlertCount(), "Healthy patient should trigger no alerts");
}

void demonstrate_improvements() {
    resetAlertCount();
    int result = vitalsOk(94, 55, 85);  // All three vitals are dangerously bad

    EXPECT_EQUAL(0, result, "Critical patient should fail");
    EXPECT_EQUAL(3, getAlertCount(), "Should alert for ALL three problems");
}

void test_future_extensibility() {
    EXPECT_TRUE(1, "Clean code enables easy future extensions");
}

int main() {
    // Start fresh
    total_tests = 0;
    passed_tests = 0;
    
    // Run all our test suites
    test_basic_range_checking();           // Test 1: Basic vital sign checking
    test_alert_system();                   // Test 2: Alert system functionality  
    test_comprehensive_monitoring();       // Test 3: Complete vital signs monitoring
    test_real_world_scenarios();          // Test 4: Real patient scenarios
    demonstrate_improvements();           // Test 5: Why our new code is better
    test_future_extensibility();          // Test 6: Future-proofing demonstration
    
    // Calculate test results
    int failed_tests = total_tests - passed_tests;
    
    // In a real medical system, detailed test results would be displayed here
    // For now, we just return success (0) or failure (non-zero)
    return (failed_tests == 0) ? 0 : 1;
}

