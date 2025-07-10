#include <iostream>
#include <vector>
#include <complex>
#include "TimeSeriesAnalysis.h"
#include "../matplotlib-cpp/matplotlibcpp.h"
#include <iostream>
#include <vector>
#include <complex>

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

    // Visualization using matplotlib-cpp
    namespace plt = matplotlibcpp;

    // Plot original data
    std::vector<int> indices(data.size());
    for (size_t i = 0; i < data.size(); ++i)
        indices[i] = i + 1;
    plt::plot(indices, data);
    plt::title("Original Data");
    plt::show();

    // Plot moving average
    plt::clf();
    std::vector<int> ma_indices(ma.size());
    for (size_t i = 0; i < ma.size(); ++i)
        ma_indices[i] = i + 1;
    plt::plot(ma_indices, ma);
    plt::title("Moving Average");
    plt::show();

    // Plot exponential smoothing
    plt::clf();
    std::vector<int> es_indices(es.size());
    for (size_t i = 0; i < es.size(); ++i)
        es_indices[i] = i + 1;
    plt::plot(es_indices, es);
    plt::title("Exponential Smoothing");
    plt::show();

    // Plot seasonal decomposition components
    plt::clf();
    std::vector<int> trend_indices(trend.size());
    for (size_t i = 0; i < trend.size(); ++i)
        trend_indices[i] = i + 1;
    plt::plot(trend_indices, trend);
    plt::title("Seasonal Decomposition - Trend");
    plt::show();

    plt::clf();
    std::vector<int> seasonal_indices(seasonal.size());
    for (size_t i = 0; i < seasonal.size(); ++i)
        seasonal_indices[i] = i + 1;
    plt::plot(seasonal_indices, seasonal);
    plt::title("Seasonal Decomposition - Seasonal");
    plt::show();

    plt::clf();
    std::vector<int> residual_indices(residual.size());
    for (size_t i = 0; i < residual.size(); ++i)
        residual_indices[i] = i + 1;
    plt::plot(residual_indices, residual);
    plt::title("Seasonal Decomposition - Residual");
    plt::show();

    // Plot Fourier transform magnitudes
    plt::clf();
    std::vector<int> ft_indices(ft.size());
    for (size_t i = 0; i < ft.size(); ++i)
        ft_indices[i] = i + 1;
    std::vector<double> ft_magnitudes;
    for (const auto &c : ft)
        ft_magnitudes.push_back(std::abs(c));
    plt::plot(ft_indices, ft_magnitudes);
    plt::title("Fourier Transform Magnitudes");
    plt::show();

    // Plot LSTM prediction
    plt::clf();
    std::vector<int> pred_indices(prediction.size());
    for (size_t i = 0; i < prediction.size(); ++i)
        pred_indices[i] = i + 1;
    plt::plot(pred_indices, prediction);
    plt::title("LSTM Model Prediction");
    plt::show();

    return 0;
}
