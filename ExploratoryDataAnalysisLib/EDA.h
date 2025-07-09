#ifndef EDA_H
#define EDA_H

#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>

namespace EDA
{
    /**
     * Calculate histogram bins and counts.
     * Layman: Group data into bins and count how many fall into each.
     * Technical: Compute bin edges and frequency counts for histogram.
     */
    template <typename T>
    void histogram(const std::vector<T> &data, int bins, std::vector<T> &binEdges, std::vector<int> &counts)
    {
        if (bins <= 0)
            throw std::invalid_argument("Number of bins must be positive");
        if (data.empty())
            throw std::invalid_argument("Data vector is empty");

        T minVal = *std::min_element(data.begin(), data.end());
        T maxVal = *std::max_element(data.begin(), data.end());
        T binWidth = (maxVal - minVal) / bins;

        binEdges.resize(bins + 1);
        counts.assign(bins, 0);

        for (int i = 0; i <= bins; ++i)
        {
            binEdges[i] = minVal + i * binWidth;
        }

        for (const auto &val : data)
        {
            int binIndex = std::min(static_cast<int>((val - minVal) / binWidth), bins - 1);
            counts[binIndex]++;
        }
    }

    // Calculate box plot statistics: min, Q1, median, Q3, max
    template <typename T>
    void boxPlotStats(std::vector<T> data, T &min, T &q1, T &median, T &q3, T &max)
    {
        if (data.empty())
            throw std::invalid_argument("Data vector is empty");

        std::sort(data.begin(), data.end());
        min = data.front();
        max = data.back();

        auto medianCalc = [](const std::vector<T> &v) -> T
        {
            size_t n = v.size();
            if (n % 2 == 0)
                return (v[n / 2 - 1] + v[n / 2]) / 2;
            else
                return v[n / 2];
        };

        median = medianCalc(data);

        std::vector<T> lower(data.begin(), data.begin() + data.size() / 2);
        std::vector<T> upper;
        if (data.size() % 2 == 0)
            upper = std::vector<T>(data.begin() + data.size() / 2, data.end());
        else
            upper = std::vector<T>(data.begin() + data.size() / 2 + 1, data.end());

        q1 = medianCalc(lower);
        q3 = medianCalc(upper);
    }

    // Calculate Pearson correlation coefficient between two variables
    template <typename T>
    double correlation(const std::vector<T> &x, const std::vector<T> &y)
    {
        if (x.size() != y.size() || x.empty())
            throw std::invalid_argument("Vectors must be of same non-zero length");

        double meanX = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
        double meanY = std::accumulate(y.begin(), y.end(), 0.0) / y.size();

        double numerator = 0.0;
        double denomX = 0.0;
        double denomY = 0.0;

        for (size_t i = 0; i < x.size(); ++i)
        {
            numerator += (x[i] - meanX) * (y[i] - meanY);
            denomX += (x[i] - meanX) * (x[i] - meanX);
            denomY += (y[i] - meanY) * (y[i] - meanY);
        }

        double denominator = std::sqrt(denomX * denomY);
        if (denominator == 0)
            throw std::runtime_error("Division by zero in correlation calculation");

        return numerator / denominator;
    }

    // Detect outliers using IQR method
    template <typename T>
    std::vector<T> detectOutliers(const std::vector<T> &data)
    {
        if (data.empty())
            throw std::invalid_argument("Data vector is empty");

        std::vector<T> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());

        T q1, q3, median, min, max;
        boxPlotStats(sortedData, min, q1, median, q3, max);

        T iqr = q3 - q1;
        T lowerBound = q1 - 1.5 * iqr;
        T upperBound = q3 + 1.5 * iqr;

        std::vector<T> outliers;
        for (const auto &val : data)
        {
            if (val < lowerBound || val > upperBound)
                outliers.push_back(val);
        }
        return outliers;
    }

    // Simple scatter plot (prints x,y pairs)
    template <typename T>
    void scatterPlot(const std::vector<T> &x, const std::vector<T> &y)
    {
        if (x.size() != y.size())
            throw std::invalid_argument("Vectors must be of same length");

        std::cout << "Scatter Plot (x, y):" << std::endl;
        for (size_t i = 0; i < x.size(); ++i)
        {
            std::cout << "(" << x[i] << ", " << y[i] << ")" << std::endl;
        }
    }
    template <typename T>
    void correlationHeatmap(const std::vector<std::vector<T>> &data, const std::vector<std::string> &labels)
    {
        if (data.empty())
        {
            std::cout << "Empty dataset." << std::endl;
            return;
        }

        size_t nVars = data.size();
        for (const auto &col : data)
        {
            if (col.size() != data[0].size())
            {
                std::cout << "Inconsistent column sizes." << std::endl;
                return;
            }
        }

        // Compute correlation matrix
        std::vector<std::vector<double>> corrMatrix(nVars, std::vector<double>(nVars, 0.0));
        for (size_t i = 0; i < nVars; ++i)
        {
            for (size_t j = 0; j < nVars; ++j)
            {
                if (i == j)
                    corrMatrix[i][j] = 1.0;
                else
                    corrMatrix[i][j] = correlation(data[i], data[j]);
            }
        }

        // Print heatmap header
        std::cout << "Correlation Heatmap:" << std::endl;
        std::cout << std::setw(7) << " " << " ";
        for (const auto &label : labels)
        {
            std::cout << std::setw(7) << label.substr(0, 7) << " ";
        }
        std::cout << std::endl;

        // Print heatmap rows
        for (size_t i = 0; i < nVars; ++i)
        {
            std::cout << std::setw(7) << labels[i].substr(0, 7) << " ";
            for (size_t j = 0; j < nVars; ++j)
            {
                std::cout << std::setw(7) << std::fixed << std::setprecision(2) << corrMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

// Generate a textual heatmap of correlation matrix for given dataset (columns as variables)
template <typename T>
void correlationHeatmap(const std::vector<std::vector<T>> &data, const std::vector<std::string> &labels)
{
    if (data.empty())
    {
        std::cout << "Empty dataset." << std::endl;
        return;
    }

    size_t nVars = data.size();
    for (const auto &col : data)
    {
        if (col.size() != data[0].size())
        {
            std::cout << "Inconsistent column sizes." << std::endl;
            return;
        }
    }

    // Compute correlation matrix
    std::vector<std::vector<double>> corrMatrix(nVars, std::vector<double>(nVars, 0.0));
    for (size_t i = 0; i < nVars; ++i)
    {
        for (size_t j = 0; j < nVars; ++j)
        {
            if (i == j)
                corrMatrix[i][j] = 1.0;
            else
                corrMatrix[i][j] = correlation(data[i], data[j]);
        }
    }

    // Print heatmap header
    std::cout << "Correlation Heatmap:" << std::endl;
    std::cout << "       ";
    for (const auto &label : labels)
    {
        std::cout << label.substr(0, 7) << " ";
    }
    std::cout << std::endl;

    // Print heatmap rows
    for (size_t i = 0; i < nVars; ++i)
    {
        std::cout << labels[i].substr(0, 7) << " ";
        for (size_t j = 0; j < nVars; ++j)
        {
            std::cout << std::fixed << std::setprecision(2) << corrMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
#endif // EDA_H
