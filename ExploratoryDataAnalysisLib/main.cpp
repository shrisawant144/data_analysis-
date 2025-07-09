#include <iostream>
#include <vector>
#include <string>
#include "EDA.h"

int main()
{
    try
    {
        std::vector<double> data = {1.2, 2.3, 2.1, 3.5, 2.8, 3.0, 2.9, 10.0};

        // Histogram
        std::vector<double> binEdges;
        std::vector<int> counts;
        EDA::histogram(data, 5, binEdges, counts);
        std::cout << "Histogram bins and counts:" << std::endl;
        for (size_t i = 0; i < counts.size(); ++i)
        {
            std::cout << "[" << binEdges[i] << ", " << binEdges[i + 1] << "): " << counts[i] << std::endl;
        }

        // Box plot stats
        double min, q1, median, q3, max;
        EDA::boxPlotStats(data, min, q1, median, q3, max);
        std::cout << "Box Plot Stats - Min: " << min << ", Q1: " << q1 << ", Median: " << median
                  << ", Q3: " << q3 << ", Max: " << max << std::endl;

        // Correlation
        std::vector<double> x = {1, 2, 3, 4, 5};
        std::vector<double> y = {2, 4, 5, 4, 5};
        double corr = EDA::correlation(x, y);
        std::cout << "Pearson correlation coefficient: " << corr << std::endl;

        // Outlier detection
        std::vector<double> outliers = EDA::detectOutliers(data);
        std::cout << "Outliers detected: ";
        for (double val : outliers)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        // Scatter plot
        EDA::scatterPlot(x, y);

        // Correlation heatmap
        std::vector<std::vector<double>> dataset = {
            {1, 2, 3, 4, 5},
            {2, 4, 5, 4, 5},
            {5, 3, 2, 1, 0}};
        std::vector<std::string> labels = {"Var1", "Var2", "Var3"};
        EDA::correlationHeatmap(dataset, labels);

        // Additional: Summary statistics
        std::cout << "Summary Statistics:" << std::endl;
        std::cout << "Mean: " << std::accumulate(data.begin(), data.end(), 0.0) / data.size() << std::endl;
        std::vector<double> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());
        std::cout << "Median: " << (sortedData.size() % 2 == 0 ? (sortedData[sortedData.size() / 2 - 1] + sortedData[sortedData.size() / 2]) / 2 : sortedData[sortedData.size() / 2]) << std::endl;
        std::cout << "Min: " << sortedData.front() << std::endl;
        std::cout << "Max: " << sortedData.back() << std::endl;
        double sq_sum = std::inner_product(data.begin(), data.end(), data.begin(), 0.0);
        double stdev = std::sqrt(sq_sum / data.size() - std::pow(std::accumulate(data.begin(), data.end(), 0.0) / data.size(), 2));
        std::cout << "Standard Deviation: " << stdev << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
