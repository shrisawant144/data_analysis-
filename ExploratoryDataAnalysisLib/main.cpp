#include <iostream>
#include <vector>
#include <string>
#include "EDA.h"
#include "../matplotlib-cpp/matplotlibcpp.h"
#include <numeric>
#include <algorithm>
#include <cmath>

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

        // Visualization using matplotlib-cpp
        namespace plt = matplotlibcpp;

        // Plot histogram
        std::vector<double> binCenters(counts.size());
        for (size_t i = 0; i < counts.size(); ++i)
        {
            binCenters[i] = (binEdges[i] + binEdges[i + 1]) / 2.0;
        }
        plt::bar(binCenters, std::vector<double>(counts.begin(), counts.end()));
        plt::title("Histogram");
        plt::show();

        // Plot box plot using vertical lines
        plt::clf();
        plt::axvline(min, 0, 1, {{"color", "blue"}, {"label", "Min"}});
        plt::axvline(q1, 0, 1, {{"color", "cyan"}, {"label", "Q1"}});
        plt::axvline(median, 0, 1, {{"color", "green"}, {"label", "Median"}});
        plt::axvline(q3, 0, 1, {{"color", "yellow"}, {"label", "Q3"}});
        plt::axvline(max, 0, 1, {{"color", "red"}, {"label", "Max"}});
        plt::title("Box Plot Stats");
        plt::legend();
        plt::show();

        // Plot scatter plot
        plt::scatter(x, y);
        plt::title("Scatter Plot");
        plt::show();

        // Plot correlation heatmap
        // Convert dataset to a flat array and provide dimensions for imshow
        int rows = dataset.size();
        int cols = dataset[0].size();
        std::vector<double> flat_data;
        for (const auto &row : dataset)
        {
            flat_data.insert(flat_data.end(), row.begin(), row.end());
        }
        // Convert double data to unsigned char for imshow
        std::vector<unsigned char> uchar_data(flat_data.size());
        double min_val = *std::min_element(flat_data.begin(), flat_data.end());
        double max_val = *std::max_element(flat_data.begin(), flat_data.end());
        for (size_t i = 0; i < flat_data.size(); ++i)
        {
            uchar_data[i] = static_cast<unsigned char>(255 * (flat_data[i] - min_val) / (max_val - min_val));
        }
        // matplotlib-cpp imshow returns void, so cannot assign to img
        plt::imshow(uchar_data.data(), rows, cols, 1);
        plt::colorbar();
        plt::title("Correlation Heatmap");
        plt::show();
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
