#ifndef DESCRIPTIVE_STATISTICS_H
#define DESCRIPTIVE_STATISTICS_H

#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <numeric>

namespace DescriptiveStatistics
{

    /**
     * Calculate the mean (average) of the data.
     * Layman: The average value of all numbers in your data.
     * Technical: Sum of all data points divided by the number of points.
     */
    template <typename T>
    double mean(const std::vector<T> &data)
    {
        if (data.empty())
            throw std::invalid_argument("Data vector is empty");
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        return sum / data.size();
    }

    /**
     * Calculate the median of the data.
     * Layman: The middle value when your data is sorted from smallest to largest.
     * Technical: The 50th percentile; if even number of points, average of the two middle values.
     */
    template <typename T>
    double median(std::vector<T> data)
    {
        if (data.empty())
            throw std::invalid_argument("Data vector is empty");
        std::sort(data.begin(), data.end());
        size_t n = data.size();
        if (n % 2 == 0)
        {
            return (static_cast<double>(data[n / 2 - 1]) + static_cast<double>(data[n / 2])) / 2.0;
        }
        else
        {
            return static_cast<double>(data[n / 2]);
        }
    }

    /**
     * Calculate the mode(s) of the data.
     * Layman: The number(s) that appear most frequently in your data.
     * Technical: The value(s) with the highest frequency count.
     */
    template <typename T>
    std::vector<T> mode(const std::vector<T> &data)
    {
        if (data.empty())
            throw std::invalid_argument("Data vector is empty");
        std::map<T, int> frequency;
        for (const T &num : data)
        {
            frequency[num]++;
        }
        int max_count = 0;
        for (const auto &pair : frequency)
        {
            if (pair.second > max_count)
            {
                max_count = pair.second;
            }
        }
        std::vector<T> modes;
        for (const auto &pair : frequency)
        {
            if (pair.second == max_count)
            {
                modes.push_back(pair.first);
            }
        }
        return modes;
    }

    /**
     * Calculate the variance of the data.
     * Layman: How spread out your data is from the average.
     * Technical: The average of the squared differences from the mean.
     */
    template <typename T>
    double variance(const std::vector<T> &data)
    {
        if (data.size() < 2)
            throw std::invalid_argument("At least two data points required");
        double m = mean(data);
        double accum = 0.0;
        for (const T &num : data)
        {
            double diff = static_cast<double>(num) - m;
            accum += diff * diff;
        }
        return accum / (data.size() - 1);
    }

    /**
     * Calculate the standard deviation of the data.
     * Layman: A measure of how much the data varies around the average.
     * Technical: The square root of the variance.
     */
    template <typename T>
    double standardDeviation(const std::vector<T> &data)
    {
        return std::sqrt(variance(data));
    }

    /**
     * Find the minimum value in the data.
     * Layman: The smallest number in your data.
     * Technical: The lowest value in the dataset.
     */
    template <typename T>
    T minimum(const std::vector<T> &data)
    {
        if (data.empty())
            throw std::invalid_argument("Data vector is empty");
        return *std::min_element(data.begin(), data.end());
    }

    /**
     * Find the maximum value in the data.
     * Layman: The largest number in your data.
     * Technical: The highest value in the dataset.
     */
    template <typename T>
    T maximum(const std::vector<T> &data)
    {
        if (data.empty())
            throw std::invalid_argument("Data vector is empty");
        return *std::max_element(data.begin(), data.end());
    }

    /**
     * Calculate the range of the data.
     * Layman: The difference between the largest and smallest numbers.
     * Technical: Maximum value minus minimum value.
     */
    template <typename T>
    double range(const std::vector<T> &data)
    {
        return static_cast<double>(maximum(data)) - static_cast<double>(minimum(data));
    }

    /**
     * Calculate the percentile of the data.
     * Layman: A value below which a certain percentage of data falls.
     * Technical: The value at a given percentage position in the sorted data.
     * @param p Percentile (0-100)
     */
    template <typename T>
    double percentile(std::vector<T> data, double p)
    {
        if (data.empty())
            throw std::invalid_argument("Data vector is empty");
        if (p < 0.0 || p > 100.0)
            throw std::invalid_argument("Percentile must be between 0 and 100");
        std::sort(data.begin(), data.end());
        double pos = (p / 100.0) * (data.size() - 1);
        size_t idx = static_cast<size_t>(pos);
        double frac = pos - idx;
        if (idx + 1 < data.size())
        {
            return data[idx] * (1 - frac) + data[idx + 1] * frac;
        }
        else
        {
            return data[idx];
        }
    }

    /**
     * Calculate the quartile of the data.
     * Layman: Special percentiles dividing data into four equal parts.
     * Technical: Percentiles at 25%, 50%, and 75%.
     * @param q Quartile number (1, 2, or 3)
     */
    template <typename T>
    double quartile(std::vector<T> data, int q)
    {
        if (q < 1 || q > 3)
            throw std::invalid_argument("Quartile must be 1, 2, or 3");
        return percentile(data, q * 25.0);
    }

}

#endif // DESCRIPTIVE_STATISTICS_H
