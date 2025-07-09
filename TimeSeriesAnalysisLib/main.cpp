#include <iostream>
#include <vector>
#include <complex>
#include "TimeSeriesAnalysis.h"

int main()
{
    std::vector<double> data = {1.0, 2.0, 3.0, 2.5, 2.0, 1.5, 1.0, 0.5, 1.0, 1.5};

    try
    {
        // Moving Average
        size_t windowSize = 3;
        std::vector<double> ma = TimeSeriesAnalysis::movingAverage(data, windowSize);
        std::cout << "Moving Average (window size " << windowSize << "): ";
        for (double val : ma)
            std::cout << val << " ";
        std::cout << std::endl;

        // Exponential Smoothing
        double alpha = 0.5;
        std::vector<double> es = TimeSeriesAnalysis::exponentialSmoothing(data, alpha);
        std::cout << "Exponential Smoothing (alpha " << alpha << "): ";
        for (double val : es)
            std::cout << val << " ";
        std::cout << std::endl;

        // ARIMA (placeholder)
        int p = 1, d = 0, q = 1;
        std::vector<double> arima = TimeSeriesAnalysis::ARIMA(data, p, d, q);
        std::cout << "ARIMA output (placeholder): ";
        for (double val : arima)
            std::cout << val << " ";
        std::cout << std::endl;

        // Fourier Transform
        std::vector<std::complex<double>> ft = TimeSeriesAnalysis::fourierTransform(data);
        std::cout << "Fourier Transform magnitudes: ";
        for (const auto &c : ft)
            std::cout << std::abs(c) << " ";
        std::cout << std::endl;

        // Seasonal Decomposition example
        {
            std::vector<double> trend, seasonal, residual;
            size_t period = 3;
            TimeSeriesAnalysis::seasonalDecomposition(data, trend, seasonal, residual, period);
            std::cout << "Seasonal Decomposition (period " << period << "):" << std::endl;
            std::cout << "Trend: ";
            for (double val : trend)
                std::cout << val << " ";
            std::cout << std::endl;
            std::cout << "Seasonal: ";
            for (double val : seasonal)
                std::cout << val << " ";
            std::cout << std::endl;
            std::cout << "Residual: ";
            for (double val : residual)
                std::cout << val << " ";
            std::cout << std::endl;
        }

        // LSTM Model example (placeholder)
        {
            TimeSeriesAnalysis::LSTMModel lstm(1, 10, 1);
            std::vector<std::vector<double>> inputs = {{1.0}, {2.0}, {3.0}};
            std::vector<std::vector<double>> targets = {{2.0}, {3.0}, {4.0}};
            lstm.train(inputs, targets, 5);
            std::vector<double> prediction = lstm.predict({5.0});
            std::cout << "LSTM Model prediction (placeholder): ";
            for (double val : prediction)
                std::cout << val << " ";
            std::cout << std::endl;
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
