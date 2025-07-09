#ifndef REGRESSION_ANALYSIS_H
#define REGRESSION_ANALYSIS_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <type_traits>

namespace RegressionAnalysis
{
    /**
     * Perform multiple linear regression.
     * Layman: Find the best-fit line that predicts y from multiple x variables.
     * Technical: Calculate regression coefficients and intercept minimizing squared errors.
     * @param X Matrix of predictor variables (each vector is a predictor)
     * @param y Vector of response variable
     * @return pair of vector of coefficients and intercept
     */
    template <typename T, typename U>
    std::pair<std::vector<double>, double> multipleLinearRegression(const std::vector<std::vector<T>> &X, const std::vector<U> &y)
    {
        size_t n = y.size();
        if (X.empty() || X[0].size() != n)
            throw std::invalid_argument("Dimension mismatch between X and y");

        size_t p = X.size(); // number of predictors

        // Calculate means of each predictor and y
        std::vector<double> meanX(p, 0.0);
        for (size_t j = 0; j < p; ++j)
        {
            meanX[j] = std::accumulate(X[j].begin(), X[j].end(), 0.0) / n;
        }
        double meanY = std::accumulate(y.begin(), y.end(), 0.0) / n;

        // Calculate coefficients using least squares formula
        std::vector<double> beta(p, 0.0);
        for (size_t j = 0; j < p; ++j)
        {
            double numerator = 0.0;
            double denominator = 0.0;
            for (size_t i = 0; i < n; ++i)
            {
                numerator += (X[j][i] - meanX[j]) * (y[i] - meanY);
                denominator += (X[j][i] - meanX[j]) * (X[j][i] - meanX[j]);
            }
            if (denominator == 0)
                throw std::invalid_argument("Denominator zero in coefficient calculation");
            beta[j] = numerator / denominator;
        }

        // Calculate intercept
        double intercept = meanY;
        for (size_t j = 0; j < p; ++j)
        {
            intercept -= beta[j] * meanX[j];
        }

        return std::make_pair(beta, intercept);
    }

    /**
     * Perform logistic regression.
     * Layman: Predict probability of binary outcome from multiple variables.
     * Technical: Use gradient descent to estimate logistic regression coefficients.
     * @param X Matrix of predictor variables (each vector is a predictor)
     * @param y Vector of binary response variable
     * @param learningRate Step size for gradient descent
     * @param iterations Number of iterations for gradient descent
     * @return vector of coefficients including intercept as last element
     */
    template <typename T, typename U>
    std::vector<double> logisticRegression(const std::vector<std::vector<T>> &X, const std::vector<U> &y, double learningRate = 0.01, int iterations = 1000)
    {
        size_t n = y.size();
        if (X.empty() || X[0].size() != n)
            throw std::invalid_argument("Dimension mismatch between X and y");

        size_t p = X.size(); // number of predictors

        // Initialize coefficients and intercept
        std::vector<double> beta(p + 1, 0.0); // last element is intercept

        auto sigmoid = [](double z)
        { return 1.0 / (1.0 + std::exp(-z)); };

        for (int iter = 0; iter < iterations; ++iter)
        {
            std::vector<double> gradients(p + 1, 0.0);

            for (size_t i = 0; i < n; ++i)
            {
                double z = beta[p]; // intercept
                for (size_t j = 0; j < p; ++j)
                {
                    z += beta[j] * X[j][i];
                }
                double pred = sigmoid(z);
                double error = pred - y[i];
                for (size_t j = 0; j < p; ++j)
                {
                    gradients[j] += error * X[j][i];
                }
                gradients[p] += error;
            }

            for (size_t j = 0; j <= p; ++j)
            {
                beta[j] -= learningRate * gradients[j] / n;
            }
        }

        return beta;
    }
}

#endif // REGRESSION_ANALYSIS_H
