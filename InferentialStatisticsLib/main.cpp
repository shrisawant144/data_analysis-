#include <iostream>
#include <vector>
#include "InferentialStatistics.h"
#include "../matplotlib-cpp/matplotlibcpp.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "../matplotlib-cpp/matplotlibcpp.h"
#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    std::vector<double> sampleData = {2.3, 2.5, 2.1, 2.6, 2.4, 2.7, 2.2};
    double hypothesizedMean = 2.0;

    std::cout << "Sample Data: ";
    for (double d : sampleData)
    {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    try
    {
        double t_stat = InferentialStatistics::tTest(sampleData, hypothesizedMean);
        std::cout << "One-sample t-test statistic: " << t_stat << std::endl;

        double sigma = 0.5; // assumed known population std dev for z-test
        double z_stat = InferentialStatistics::zTest(sampleData, hypothesizedMean, sigma);
        std::cout << "One-sample z-test statistic: " << z_stat << std::endl;

        double tCritical = 2.447; // example critical t-value for 95% confidence, df=6
        auto ci = InferentialStatistics::confidenceInterval(sampleData, 0.95, tCritical);
        std::cout << "95% Confidence Interval for mean: [" << ci.first << ", " << ci.second << "]" << std::endl;

        std::vector<std::vector<double>> groups = {
            {2.3, 2.5, 2.1},
            {2.6, 2.4, 2.7},
            {2.2, 2.8, 2.9}};
        double f_stat = InferentialStatistics::oneWayANOVA(groups);
        std::cout << "One-way ANOVA F-statistic: " << f_stat << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    try
    {
        // Chi-square test example
        std::vector<int> observed = {50, 30, 20};
        std::vector<int> expected = {40, 40, 20};
        double chiSquare = InferentialStatistics::chiSquareTest(observed, expected);
        std::cout << "Chi-square test statistic: " << chiSquare << std::endl;

        // Linear regression example
        std::vector<double> x = {1, 2, 3, 4, 5};
        std::vector<double> y = {2, 4, 5, 4, 5};
        double slope, intercept;
        std::tie(slope, intercept) = InferentialStatistics::linearRegression(x, y);
        std::cout << "Linear regression slope: " << slope << ", intercept: " << intercept << std::endl;

        // Correlation example
        double corr = InferentialStatistics::correlation(x, y);
        std::cout << "Pearson correlation coefficient: " << corr << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    // Calculate confidence interval for plotting
    double tCritical = 2.447; // example critical t-value for 95% confidence, df=6
    auto ci = InferentialStatistics::confidenceInterval(sampleData, 0.95, tCritical);

    // Visualization using matplotlib-cpp
    namespace plt = matplotlibcpp;

    // Plot sample data points
    std::vector<double> indices(sampleData.size());
    for (size_t i = 0; i < sampleData.size(); ++i)
        indices[i] = i + 1;
    plt::scatter(indices, sampleData);
    plt::title("Sample Data Points");
    plt::xlabel("Index");
    plt::ylabel("Value");
    plt::show();

    // Plot confidence interval as horizontal lines using plot instead of hlines
    plt::clf();
    plt::scatter(indices, sampleData);
    std::vector<double> mean_line_x = {0, static_cast<double>(sampleData.size() + 1)};
    std::vector<double> mean_line_y = {InferentialStatistics::mean(sampleData), InferentialStatistics::mean(sampleData)};
    plt::plot(mean_line_x, mean_line_y, {{"color", "red"}, {"label", "Mean"}});
    std::vector<double> lower_ci_y = {ci.first, ci.first};
    plt::plot(mean_line_x, lower_ci_y, {{"color", "green"}, {"label", "Lower CI"}});
    std::vector<double> upper_ci_y = {ci.second, ci.second};
    plt::plot(mean_line_x, upper_ci_y, {{"color", "blue"}, {"label", "Upper CI"}});
    plt::title("Confidence Interval");
    plt::legend();
    plt::show();

    // Plot linear regression line with data points
    plt::clf();

    // Declare x, y, slope, intercept here for plotting
    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {2, 4, 5, 4, 5};
    double slope, intercept;
    std::tie(slope, intercept) = InferentialStatistics::linearRegression(x, y);

    plt::scatter(x, y);
    std::vector<double> reg_line_x = x;
    std::vector<double> reg_line_y;
    for (auto val : x)
        reg_line_y.push_back(slope * val + intercept);
    plt::plot(reg_line_x, reg_line_y);
    plt::title("Linear Regression");
    plt::show();

    return 0;
}
