/**
 * Group name: Huffman
 * Group member name/Github username:
 * Yuheng Chen/acse-cc223
 * Panier, Atys/edsml-azp123
 * Crespin, Francois/Fc-1223
 * Xuan Zhan/edsml-xz3323
 * Yixuan Jiang/ACSE-yj3023
*/

/**
 * @file TestFramework.h
 * @brief Header file containing testing framework functions.
 */
#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <string>

/**
 * @struct TestCase
 * @brief Structure representing a test case.
 */
struct TestCase {
    std::string name;
    std::function<void()> testFunction;

    /**
     * @brief Constructor for TestCase.
     * @param name The name of the test case.
     * @param func The function representing the test case.
     */
    TestCase(std::string name, std::function<void()> func) : name(name), testFunction(func) {}
};

/**
 * @class TestRunner
 * @brief Class responsible for running test cases.
 */
class TestRunner {
public:
    static TestRunner& getInstance() {
        /**
         * @brief Gets the instance of TestRunner (singleton pattern).
         * @return The instance of TestRunner.
         */
        static TestRunner instance;
        return instance;
    }

    /**
     * @brief Adds a test case to the test runner.
     * @param testCase The test case to add.
     */
    void addTest(TestCase testCase) {
        tests.push_back(testCase);
    }

    /**
     * @brief Runs all added test cases.
     */
    void run() {
        int passed = 0;
        for (auto& test : tests) {
            try {
                test.testFunction();
                std::cout << test.name << ": PASS\n";
                ++passed;
            }
            catch (std::exception& e) {
                std::cout << test.name << ": FAIL\n";
            }
        }
        std::cout << "\n" << passed << "/" << tests.size() << " tests passed\n";
    }

private:
    std::vector<TestCase> tests;
    /**
     * @brief Private constructor for TestRunner (singleton pattern).
     */
    TestRunner() {}
};

/**
 * @brief Macro for defining a test case.
 * @param testName The name of the test case.
 */
#define TEST(testName) \
void testName(); \
struct testName##Helper { \
    testName##Helper() { \
        TestRunner::getInstance().addTest(TestCase(#testName, testName)); \
    } \
}; \
static testName##Helper testName##HelperInstance; \
void testName()

/**
 * @brief Macro for asserting equality in a test case.
 * @param expected The expected value.
 * @param actual The actual value.
 */
#define ASSERT_EQ(expected, actual) \
    if ((expected) != (actual)) throw std::runtime_error("Assertion failed: " #expected " != " #actual);

