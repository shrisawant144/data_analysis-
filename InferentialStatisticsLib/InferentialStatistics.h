#ifndef INFERENTIAL_STATISTICS_H
#define INFERENTIAL_STATISTICS_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <map>

namespace InferentialStatistics
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
     * Perform a one-sample t-test.
     * Layman: Test if the sample mean is significantly different from a hypothesized mean.
     * Technical: Calculate the t-statistic for the sample data against the null hypothesis mean.
     * @param data Sample data
     * @param mu Hypothesized population mean
     * @return t-statistic
     */
    template <typename T>
    double tTest(const std::vector<T> &data, double mu)
    {
        if (data.size() < 2)
            throw std::invalid_argument("At least two data points required");
        double m = mean(data);
        double s = standardDeviation(data);
        double n = static_cast<double>(data.size());
        return (m - mu) / (s / std::sqrt(n));
    }

    /**
     * Perform a one-sample z-test.
     * Layman: Test if the sample mean is significantly different from a hypothesized mean with known population stddev.
     * Technical: Calculate the z-statistic for the sample data against the null hypothesis mean.
     * @param data Sample data
     * @param mu Hypothesized population mean
     * @param sigma Population standard deviation (known)
     * @return z-statistic
     */
    template <typename T>
    double zTest(const std::vector<T> &data, double mu, double sigma)
    {
        if (data.empty())
            throw std::invalid_argument("Data vector is empty");
        double m = mean(data);
        double n = static_cast<double>(data.size());
        return (m - mu) / (sigma / std::sqrt(n));
    }

    /**
     * Calculate confidence interval for the mean using t-distribution.
     * Layman: Range where the true mean likely falls with a given confidence.
     * Technical: Compute the confidence interval bounds using sample mean, stddev, and t-critical value.
     * @param data Sample data
     * @param confidenceLevel Confidence level (e.g., 0.95 for 95%)
     * @param tCritical Critical t-value for the confidence level and degrees of freedom
     * @return pair of lower and upper bounds
     */
    template <typename T>
    std::pair<double, double> confidenceInterval(const std::vector<T> &data, double confidenceLevel, double tCritical)
    {
        if (data.size() < 2)
            throw std::invalid_argument("At least two data points required");
        double m = mean(data);
        double s = standardDeviation(data);
        double n = static_cast<double>(data.size());
        double margin = tCritical * s / std::sqrt(n);
        return std::make_pair(m - margin, m + margin);
    }

    /**
     * Perform one-way ANOVA test.
     * @param groups Vector of groups, each group is a vector of data points
     * @return F-statistic
     */
    template <typename T>
    double oneWayANOVA(const std::vector<std::vector<T>> &groups)
    {
        size_t k = groups.size();
        if (k < 2)
            throw std::invalid_argument("At least two groups required");

        size_t totalN = 0;
        double grandSum = 0.0;
        for (const auto &group : groups)
        {
            totalN += group.size();
            grandSum += std::accumulate(group.begin(), group.end(), 0.0);
        }
        double grandMean = grandSum / totalN;

        // Between-group sum of squares
        double ssBetween = 0.0;
        for (const auto &group : groups)
        {
            double groupMean = mean(group);
            ssBetween += group.size() * (groupMean - grandMean) * (groupMean - grandMean);
        }

        // Within-group sum of squares
        double ssWithin = 0.0;
        for (const auto &group : groups)
        {
            double groupMean = mean(group);
            for (const auto &val : group)
            {
                double diff = val - groupMean;
                ssWithin += diff * diff;
            }
        }

        double dfBetween = static_cast<double>(k - 1);
        double dfWithin = static_cast<double>(totalN - k);

        double msBetween = ssBetween / dfBetween;
        double msWithin = ssWithin / dfWithin;

        return msBetween / msWithin;
    }

    /**
     * Perform chi-square test for goodness of fit.
     * @param observed Vector of observed frequencies
     * @param expected Vector of expected frequencies
     * @return chi-square statistic
     */
    template <typename T>
    double chiSquareTest(const std::vector<T> &observed, const std::vector<T> &expected)
    {
        if (observed.size() != expected.size())
            throw std::invalid_argument("Observed and expected vectors must be the same size");
        double chiSquare = 0.0;
        for (size_t i = 0; i < observed.size(); ++i)
        {
            if (expected[i] == 0)
                throw std::invalid_argument("Expected frequency cannot be zero");
            double diff = static_cast<double>(observed[i]) - static_cast<double>(expected[i]);
            chiSquare += (diff * diff) / expected[i];
        }
        return chiSquare;
    }

    /**
     * Perform simple linear regression.
     * @param x Independent variable data
     * @param y Dependent variable data
     * @return pair of slope and intercept
     */
    template <typename T>
    std::pair<double, double> linearRegression(const std::vector<T> &x, const std::vector<T> &y)
    {
        if (x.size() != y.size() || x.empty())
            throw std::invalid_argument("Vectors x and y must be the same size and not empty");
        double meanX = mean(x);
        double meanY = mean(y);
        double numerator = 0.0;
        double denominator = 0.0;
        for (size_t i = 0; i < x.size(); ++i)
        {
            numerator += (x[i] - meanX) * (y[i] - meanY);
            denominator += (x[i] - meanX) * (x[i] - meanX);
        }
        if (denominator == 0)
            throw std::invalid_argument("Denominator in slope calculation is zero");
        double slope = numerator / denominator;
        double intercept = meanY - slope * meanX;
        return std::make_pair(slope, intercept);
    }

    /**
     * Calculate Pearson correlation coefficient.
     * @param x First data vector
     * @param y Second data vector
     * @return correlation coefficient (-1 to 1)
     */
    template <typename T>
    double correlation(const std::vector<T> &x, const std::vector<T> &y)
    {
        if (x.size() != y.size() || x.empty())
            throw std::invalid_argument("Vectors x and y must be the same size and not empty");
        double meanX = mean(x);
        double meanY = mean(y);
        double numerator = 0.0;
        double denomX = 0.0;
        double denomY = 0.0;
        for (size_t i = 0; i < x.size(); ++i)
        {
            double diffX = x[i] - meanX;
            double diffY = y[i] - meanY;
            numerator += diffX * diffY;
            denomX += diffX * diffX;
            denomY += diffY * diffY;
        }
        double denominator = std::sqrt(denomX) * std::sqrt(denomY);
        if (denominator == 0)
            throw std::invalid_argument("Denominator in correlation calculation is zero");
        return numerator / denominator;
    }
}

#endif // INFERENTIAL_STATISTICS_H
