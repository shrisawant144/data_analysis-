#include <iostream>
#include <vector>
#include "RegressionAnalysis.h"

int main()
{
    try
    {
        // Multiple Linear Regression example with double
        std::vector<std::vector<double>> X_double = {
            {230.1, 44.5, 17.2, 151.5, 180.8},
            {37.8, 39.3, 45.9, 41.3, 10.8},
            {69.2, 45.1, 69.3, 58.5, 58.4}};
        std::vector<double> y_double = {22.1, 10.4, 9.3, 18.5, 12.9};

        auto result_double = RegressionAnalysis::multipleLinearRegression(X_double, y_double);
        auto coefficients_double = result_double.first;
        auto intercept_double = result_double.second;
        std::cout << "Multiple Linear Regression coefficients (double): ";
        for (double c : coefficients_double)
            std::cout << c << " ";
        std::cout << "\nIntercept: " << intercept_double << std::endl;

        // Multiple Linear Regression example with float
        std::vector<std::vector<float>> X_float = {
            {230.1f, 44.5f, 17.2f, 151.5f, 180.8f},
            {37.8f, 39.3f, 45.9f, 41.3f, 10.8f},
            {69.2f, 45.1f, 69.3f, 58.5f, 58.4f}};
        std::vector<float> y_float = {22.1f, 10.4f, 9.3f, 18.5f, 12.9f};

        auto result_float = RegressionAnalysis::multipleLinearRegression(X_float, y_float);
        auto coefficients_float = result_float.first;
        auto intercept_float = result_float.second;
        std::cout << "Multiple Linear Regression coefficients (float): ";
        for (double c : coefficients_float)
            std::cout << c << " ";
        std::cout << "\nIntercept: " << intercept_float << std::endl;

        // Logistic Regression example with double
        std::vector<std::vector<double>> sensorData_double = {
            {0.5, 1.5, 3.0, 2.5, 1.0},
            {1.0, 2.0, 1.5, 2.0, 1.5}};
        std::vector<int> faultLabels = {0, 0, 1, 1, 0};

        std::vector<double> logisticCoeffs_double = RegressionAnalysis::logisticRegression(sensorData_double, faultLabels, 0.1, 5000);
        std::cout << "Logistic Regression coefficients (double, including intercept): ";
        for (double c : logisticCoeffs_double)
            std::cout << c << " ";
        std::cout << std::endl;

        // Logistic Regression example with float
        std::vector<std::vector<float>> sensorData_float = {
            {0.5f, 1.5f, 3.0f, 2.5f, 1.0f},
            {1.0f, 2.0f, 1.5f, 2.0f, 1.5f}};
        std::vector<int> faultLabels_int = {0, 0, 1, 1, 0};

        std::vector<double> logisticCoeffs_float = RegressionAnalysis::logisticRegression(sensorData_float, faultLabels_int, 0.1, 5000);
        std::cout << "Logistic Regression coefficients (float, including intercept): ";
        for (double c : logisticCoeffs_float)
            std::cout << c << " ";
        std::cout << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
