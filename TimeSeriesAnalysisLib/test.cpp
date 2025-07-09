#include <iostream>
#include <vector>
#include <cassert>
#include "TimeSeriesAnalysis.h"

void testMovingAverage()
{
    // Test normal case
    std::vector<double> data = {1, 2, 3, 4, 5};
    auto ma = TimeSeriesAnalysis::movingAverage(data, 3);
    std::vector<double> expected = {2.0, 3.0, 4.0};
    assert(ma == expected);

    // Test window size 1 (should return original data)
    ma = TimeSeriesAnalysis::movingAverage(data, 1);
    expected = data;
    assert(ma == expected);

    // Test invalid window size (0)
    try
    {
        ma = TimeSeriesAnalysis::movingAverage(data, 0);
        assert(false); // Should not reach here
    }
    catch (const std::invalid_argument &)
    {
    }

    // Test window size larger than data
    try
    {
        ma = TimeSeriesAnalysis::movingAverage(data, 10);
        assert(false);
    }
    catch (const std::invalid_argument &)
    {
    }
}

void testExponentialSmoothing()
{
    std::vector<double> data = {1, 2, 3, 4, 5};
    auto es = TimeSeriesAnalysis::exponentialSmoothing(data, 0.5);
    std::vector<double> expected = {1, 1.5, 2.25, 3.125, 4.0625};
    for (size_t i = 0; i < es.size(); ++i)
    {
        assert(std::abs(es[i] - expected[i]) < 1e-6);
    }

    // Test invalid alpha
    try
    {
        es = TimeSeriesAnalysis::exponentialSmoothing(data, -0.1);
        assert(false);
    }
    catch (const std::invalid_argument &)
    {
    }

    try
    {
        es = TimeSeriesAnalysis::exponentialSmoothing(data, 1.1);
        assert(false);
    }
    catch (const std::invalid_argument &)
    {
    }
}

void testARIMA()
{
    std::vector<double> data = {1, 2, 3};
    auto arima = TimeSeriesAnalysis::ARIMA(data, 1, 0, 1);
    assert(arima == data); // Placeholder returns input
}

void testFourierTransform()
{
    // Use a different data set to ensure non-zero magnitude
    std::vector<double> data = {1, 1, 1, 1};
    auto ft = TimeSeriesAnalysis::fourierTransform(data);
    assert(ft.size() == data.size());
    double mag0 = std::abs(ft[0]);
    assert(mag0 > 1e-10);
}

void testSeasonalDecomposition()
{
    std::vector<double> data = {1, 2, 3, 4, 5, 6};
    std::vector<double> trend, seasonal, residual;
    TimeSeriesAnalysis::seasonalDecomposition(data, trend, seasonal, residual, 2);
    assert(trend.size() == data.size());
    assert(seasonal.size() == data.size());
    assert(residual.size() == data.size());
}

void testLSTMModel()
{
    TimeSeriesAnalysis::LSTMModel lstm(1, 2, 1);
    std::vector<std::vector<double>> inputs = {{1.0}, {2.0}};
    std::vector<std::vector<double>> targets = {{2.0}, {3.0}};
    lstm.train(inputs, targets, 3);
    auto pred = lstm.predict({1.5});
    assert(pred.size() == 1);
}

int main()
{
    testMovingAverage();
    testExponentialSmoothing();
    testARIMA();
    testFourierTransform();
    testSeasonalDecomposition();
    testLSTMModel();

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
