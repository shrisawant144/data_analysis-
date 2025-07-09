#ifndef PROBABILITY_DISTRIBUTIONS_H
#define PROBABILITY_DISTRIBUTIONS_H

#include <cmath>
#include <stdexcept>
#include <vector>

namespace ProbabilityDistributions
{
    /**
     * Calculate the probability density function (PDF) of the normal distribution.
     * Layman: Probability of a value occurring in a normal distribution.
     * Technical: Compute the normal distribution PDF at x with given mean and stddev.
     */
    template <typename T>
    T normalPDF(T x, T mean, T stddev)
    {
        if (stddev <= 0)
            throw std::invalid_argument("Standard deviation must be positive");
        T coeff = 1 / (stddev * std::sqrt(2 * M_PI));
        T exponent = -((x - mean) * (x - mean)) / (2 * stddev * stddev);
        return coeff * std::exp(exponent);
    }

    /**
     * Calculate the probability mass function (PMF) of the Poisson distribution.
     * Layman: Probability of k events occurring in a fixed interval.
     * Technical: Compute Poisson PMF with parameter lambda at k.
     */
    template <typename T>
    T poissonPMF(int k, T lambda)
    {
        if (lambda <= 0)
            throw std::invalid_argument("Lambda must be positive");
        if (k < 0)
            throw std::invalid_argument("k must be non-negative");
        T result = std::exp(-lambda);
        for (int i = 1; i <= k; ++i)
        {
            result *= lambda / i;
        }
        return result;
    }

    /**
     * Calculate the binomial coefficient "n choose k".
     * Layman: Number of ways to choose k items from n.
     * Technical: Compute combinatorial coefficient C(n, k).
     */
    template <typename T>
    T binomialCoefficient(int n, int k)
    {
        if (k > n || k < 0)
            return 0;
        if (k == 0 || k == n)
            return 1;
        T res = 1;
        for (int i = 1; i <= k; ++i)
        {
            res *= (n - (k - i));
            res /= i;
        }
        return res;
    }

    /**
     * Calculate the probability mass function (PMF) of the binomial distribution.
     * Layman: Probability of k successes in n trials with success probability p.
     * Technical: Compute binomial PMF using binomial coefficient and powers of p.
     */
    template <typename T>
    T binomialPMF(int n, int k, T p)
    {
        if (p < 0 || p > 1)
            throw std::invalid_argument("Probability p must be between 0 and 1");
        T coeff = binomialCoefficient<T>(n, k);
        return coeff * std::pow(p, k) * std::pow(1 - p, n - k);
    }

    /**
     * Calculate the probability density function (PDF) of the exponential distribution.
     * Layman: Probability of time between events in a Poisson process.
     * Technical: Compute exponential PDF at x with rate lambda.
     */
    template <typename T>
    T exponentialPDF(T x, T lambda)
    {
        if (lambda <= 0)
            throw std::invalid_argument("Lambda must be positive");
        if (x < 0)
            return 0;
        return lambda * std::exp(-lambda * x);
    }
}

#endif // PROBABILITY_DISTRIBUTIONS_H
