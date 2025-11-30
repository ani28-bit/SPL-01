#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "Random.h"
#include "Timer.h"

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "     TESTING UTILITY CLASSES" << endl;
    cout << "========================================" << endl;
    
    // ========== TEST RANDOM CLASS ==========
    cout << "\n========== TESTING RANDOM CLASS ==========" << endl;
    
    // Test 1: Initialize with fixed seed for reproducibility
    cout << "\n[TEST 1] Initialize Random with seed 42" << endl;
    Random::initialize(42);
    cout << "✓ PASS: Random initialized" << endl;
    
    // Test 2: Random integers
    cout << "\n[TEST 2] Random Integers (0-10)" << endl;
    cout << "Generating 10 random integers: ";
    int countInRange = 0;
    for (int i = 0; i < 10; i++) {
        int val = Random::getInt(0, 10);
        cout << val << " ";
        if (val >= 0 && val <= 10) countInRange++;
    }
    cout << endl;
    if (countInRange == 10) {
        cout << "✓ PASS: All integers in range [0,10]" << endl;
    } else {
        cout << "✗ FAIL: Some integers out of range" << endl;
        return 1;
    }
    
    // Test 3: Random doubles
    cout << "\n[TEST 3] Random Doubles [0.0, 1.0)" << endl;
    cout << fixed << setprecision(4);
    cout << "Generating 10 random doubles: ";
    int countInDoubleRange = 0;
    for (int i = 0; i < 10; i++) {
        double val = Random::getDouble();
        cout << val << " ";
        if (val >= 0.0 && val < 1.0) countInDoubleRange++;
    }
    cout << endl;
    if (countInDoubleRange == 10) {
        cout << "✓ PASS: All doubles in range [0.0, 1.0)" << endl;
    } else {
        cout << "✗ FAIL: Some doubles out of range" << endl;
        return 1;
    }
    
    // Test 4: Random doubles with custom range
    cout << "\n[TEST 4] Random Doubles [10.0, 20.0)" << endl;
    cout << "Generating 5 random doubles: ";
    int countInCustomRange = 0;
    for (int i = 0; i < 5; i++) {
        double val = Random::getDouble(10.0, 20.0);
        cout << val << " ";
        if (val >= 10.0 && val < 20.0) countInCustomRange++;
    }
    cout << endl;
    if (countInCustomRange == 5) {
        cout << "✓ PASS: All doubles in range [10.0, 20.0)" << endl;
    } else {
        cout << "✗ FAIL: Some doubles out of range" << endl;
        return 1;
    }
    
    // Test 5: Random boolean
    cout << "\n[TEST 5] Random Boolean (50% probability)" << endl;
    int trueCount = 0;
    int totalTests = 1000;
    for (int i = 0; i < totalTests; i++) {
        if (Random::getBool(0.5)) trueCount++;
    }
    double trueRatio = (double)trueCount / totalTests;
    cout << "True count: " << trueCount << "/" << totalTests 
         << " (" << (trueRatio * 100) << "%)" << endl;
    // Should be roughly 50% (allow 40-60% margin)
    if (trueRatio >= 0.4 && trueRatio <= 0.6) {
        cout << "✓ PASS: Boolean distribution reasonable" << endl;
    } else {
        cout << "✗ FAIL: Boolean distribution seems biased" << endl;
        return 1;
    }
    
    // Test 6: Shuffle
    cout << "\n[TEST 6] Shuffle Array" << endl;
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = 10;
    
    cout << "Original: ";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
    
    Random::shuffle(arr, size);
    
    cout << "Shuffled: ";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
    
    // Check all elements still present
    bool allPresent = true;
    for (int i = 0; i < size; i++) {
        bool found = false;
        for (int j = 0; j < size; j++) {
            if (arr[j] == i) {
                found = true;
                break;
            }
        }
        if (!found) {
            allPresent = false;
            break;
        }
    }
    
    if (allPresent) {
        cout << "✓ PASS: All elements present after shuffle" << endl;
    } else {
        cout << "✗ FAIL: Some elements missing after shuffle" << endl;
        return 1;
    }
    
    // ========== TEST TIMER CLASS ==========
    cout << "\n========== TESTING TIMER CLASS ==========" << endl;
    
    // Test 7: Basic timing
    cout << "\n[TEST 7] Basic Timer Test" << endl;
    Timer timer;
    timer.start();
    
    cout << "Sleeping for 100 milliseconds..." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    
    timer.stop();
    
    double elapsed = timer.getElapsedMilliseconds();
    cout << "Elapsed time: " << elapsed << " ms" << endl;
    
    // Allow some tolerance (90-150 ms)
    if (elapsed >= 90.0 && elapsed <= 150.0) {
        cout << "✓ PASS: Timer measurement accurate" << endl;
    } else {
        cout << "✗ FAIL: Timer measurement seems off" << endl;
        return 1;
    }
    
    // Test 8: Timer in seconds
    cout << "\n[TEST 8] Timer in Seconds" << endl;
    timer.reset();
    timer.start();
    
    this_thread::sleep_for(chrono::milliseconds(500));
    timer.stop();
    
    double elapsedSec = timer.getElapsedSeconds();
    cout << "Elapsed time: " << elapsedSec << " seconds" << endl;
    
    if (elapsedSec >= 0.45 && elapsedSec <= 0.65) {
        cout << "✓ PASS: Timer seconds measurement accurate" << endl;
    } else {
        cout << "✗ FAIL: Timer seconds measurement off" << endl;
        return 1;
    }
    
    // Test 9: Running timer
    cout << "\n[TEST 9] Timer While Running" << endl;
    timer.reset();
    timer.start();
    
    this_thread::sleep_for(chrono::milliseconds(50));
    double running1 = timer.getElapsedMilliseconds();
    
    this_thread::sleep_for(chrono::milliseconds(50));
    double running2 = timer.getElapsedMilliseconds();
    
    cout << "Time at 50ms: " << running1 << " ms" << endl;
    cout << "Time at 100ms: " << running2 << " ms" << endl;
    
    if (running2 > running1) {
        cout << "✓ PASS: Timer updates while running" << endl;
    } else {
        cout << "✗ FAIL: Timer not updating properly" << endl;
        return 1;
    }
    
    // Final summary
    cout << "\n========================================" << endl;
    cout << "    ALL TESTS PASSED! ✓✓✓" << endl;
    cout << "    Utility classes working!" << endl;
    cout << "========================================" << endl;
    
    return 0;
}