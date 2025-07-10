#include <iostream>
#include <vector>
#include "DescriptiveStatistics.h"
#include "../matplotlib-cpp/matplotlibcpp.h"
#include <cmath>

int main()
{
    std::vector<int> dataInt = {10, 12, 23, 23, 16, 23, 21, 16};
    std::vector<double> dataDouble = {10.5, 12.1, 23.3, 23.3, 16.2, 23.3, 21.0, 16.8};

    std::cout << "Integer Data: ";
    for (int d : dataInt)
    {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    std::cout << "Mean: " << DescriptiveStatistics::mean(dataInt) << std::endl;
    std::cout << "Median: " << DescriptiveStatistics::median(dataInt) << std::endl;

    std::vector<int> modesInt = DescriptiveStatistics::mode(dataInt);
    std::cout << "Mode(s): ";
    for (int m : modesInt)
    {
        std::cout << m << " ";
    }
    std::cout << std::endl;

    std::cout << "Variance: " << DescriptiveStatistics::variance(dataInt) << std::endl;
    std::cout << "Standard Deviation: " << DescriptiveStatistics::standardDeviation(dataInt) << std::endl;
    std::cout << "Minimum: " << DescriptiveStatistics::minimum(dataInt) << std::endl;
    std::cout << "Maximum: " << DescriptiveStatistics::maximum(dataInt) << std::endl;
    std::cout << "Range: " << DescriptiveStatistics::range(dataInt) << std::endl;
    std::cout << "25th Percentile (Q1): " << DescriptiveStatistics::quartile(dataInt, 1) << std::endl;
    std::cout << "50th Percentile (Q2): " << DescriptiveStatistics::quartile(dataInt, 2) << std::endl;
    std::cout << "75th Percentile (Q3): " << DescriptiveStatistics::quartile(dataInt, 3) << std::endl;

    std::cout << std::endl;

    std::cout << "Double Data: ";
    for (double d : dataDouble)
    {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    std::cout << "Mean: " << DescriptiveStatistics::mean(dataDouble) << std::endl;
    std::cout << "Median: " << DescriptiveStatistics::median(dataDouble) << std::endl;

    std::vector<double> modesDouble = DescriptiveStatistics::mode(dataDouble);
    std::cout << "Mode(s): ";
    for (double m : modesDouble)
    {
        std::cout << m << " ";
    }
    std::cout << std::endl;

    std::cout << "Variance: " << DescriptiveStatistics::variance(dataDouble) << std::endl;
    std::cout << "Standard Deviation: " << DescriptiveStatistics::standardDeviation(dataDouble) << std::endl;
    std::cout << "Minimum: " << DescriptiveStatistics::minimum(dataDouble) << std::endl;
    std::cout << "Maximum: " << DescriptiveStatistics::maximum(dataDouble) << std::endl;
    std::cout << "Range: " << DescriptiveStatistics::range(dataDouble) << std::endl;
    std::cout << "25th Percentile (Q1): " << DescriptiveStatistics::quartile(dataDouble, 1) << std::endl;
    std::cout << "50th Percentile (Q2): " << DescriptiveStatistics::quartile(dataDouble, 2) << std::endl;
    std::cout << "75th Percentile (Q3): " << DescriptiveStatistics::quartile(dataDouble, 3) << std::endl;

    // Visualization of Descriptive Statistics
    namespace plt = matplotlibcpp;

    // Plot raw data points
    plt::scatter(dataDouble, std::vector<double>(dataDouble.size(), 0), 50);

    // Calculate statistics
    double mean_val = DescriptiveStatistics::mean(dataDouble);
    double median_val = DescriptiveStatistics::median(dataDouble);
    std::vector<double> modes = DescriptiveStatistics::mode(dataDouble);

    // Plot mean, median, and mode as vertical lines
    plt::axvline(mean_val, 0, 1, {{"color", "red"}, {"label", "Mean"}});
    plt::axvline(median_val, 0, 1, {{"color", "green"}, {"label", "Median"}});
    for (auto mode_val : modes)
    {
        plt::axvline(mode_val, 0, 1, {{"color", "blue"}, {"label", "Mode"}});
    }

    // Add title and legend
    plt::title("Descriptive Statistics Visualization");
    plt::legend();

    // Show plot
    plt::show();

    return 0;
}
