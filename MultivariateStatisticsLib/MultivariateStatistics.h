#ifndef MULTIVARIATE_STATISTICS_H
#define MULTIVARIATE_STATISTICS_H

#include <vector>
#include <cmath>
#include <limits>
#include <queue>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <iostream>

namespace MultivariateStatistics
{
    // Helper function to compute mean of a vector
    template <typename T>
    T mean(const std::vector<T> &v)
    {
        T sum = std::accumulate(v.begin(), v.end(), T(0));
        return sum / static_cast<T>(v.size());
    }

    // Helper function to compute covariance matrix
    template <typename T>
    std::vector<std::vector<T>> covarianceMatrix(const std::vector<std::vector<T>> &data)
    {
        size_t n = data.size();
        if (n == 0)
            throw std::invalid_argument("Empty data");
        size_t dim = data[0].size();

        std::vector<T> means(dim, T(0));
        for (size_t j = 0; j < dim; ++j)
        {
            std::vector<T> col(n);
            for (size_t i = 0; i < n; ++i)
                col[i] = data[i][j];
            means[j] = mean(col);
        }

        std::vector<std::vector<T>> cov(dim, std::vector<T>(dim, T(0)));
        for (size_t i = 0; i < dim; ++i)
        {
            for (size_t j = i; j < dim; ++j)
            {
                T cov_ij = T(0);
                for (size_t k = 0; k < n; ++k)
                {
                    cov_ij += (data[k][i] - means[i]) * (data[k][j] - means[j]);
                }
                cov_ij /= static_cast<T>(n - 1);
                cov[i][j] = cov_ij;
                cov[j][i] = cov_ij;
            }
        }
        return cov;
    }

    // Power iteration to find dominant eigenvector and eigenvalue
    template <typename T>
    void powerIteration(const std::vector<std::vector<T>> &matrix,
                        std::vector<T> &eigenvector,
                        T &eigenvalue,
                        int maxIter = 1000,
                        T tol = 1e-6)
    {
        size_t n = matrix.size();
        eigenvector.assign(n, T(1));
        T norm = T(0);

        for (int iter = 0; iter < maxIter; ++iter)
        {
            std::vector<T> nextVec(n, T(0));
            for (size_t i = 0; i < n; ++i)
            {
                for (size_t j = 0; j < n; ++j)
                {
                    nextVec[i] += matrix[i][j] * eigenvector[j];
                }
            }
            norm = std::sqrt(std::inner_product(nextVec.begin(), nextVec.end(), nextVec.begin(), T(0)));
            for (size_t i = 0; i < n; ++i)
                nextVec[i] /= norm;

            T diff = T(0);
            for (size_t i = 0; i < n; ++i)
                diff += std::abs(nextVec[i] - eigenvector[i]);

            eigenvector = nextVec;

            if (diff < tol)
                break;
        }

        // Rayleigh quotient for eigenvalue
        std::vector<T> mv(n, T(0));
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                mv[i] += matrix[i][j] * eigenvector[j];

        eigenvalue = std::inner_product(eigenvector.begin(), eigenvector.end(), mv.begin(), T(0));
    }

    // Principal Component Analysis (PCA) with power iteration for first component
    template <typename T>
    void PCA(const std::vector<std::vector<T>> &data,
             std::vector<std::vector<T>> &components,
             std::vector<T> &explainedVariances)
    {
        auto cov = covarianceMatrix(data);
        std::vector<T> eigenvector;
        T eigenvalue;
        powerIteration(cov, eigenvector, eigenvalue);

        components.clear();
        components.push_back(eigenvector);
        explainedVariances.clear();
        explainedVariances.push_back(eigenvalue);
    }

    // Euclidean distance between two points
    template <typename T>
    T euclideanDistance(const std::vector<T> &a, const std::vector<T> &b)
    {
        T sum = T(0);
        for (size_t i = 0; i < a.size(); ++i)
        {
            T diff = a[i] - b[i];
            sum += diff * diff;
        }
        return std::sqrt(sum);
    }

    // K-means clustering
    template <typename T>
    std::vector<int> kMeans(const std::vector<std::vector<T>> &data, int k, int maxIter = 100)
    {
        size_t n = data.size();
        if (n == 0)
            return {};
        size_t dim = data[0].size();

        // Initialize centroids (first k points)
        std::vector<std::vector<T>> centroids(data.begin(), data.begin() + k);
        std::vector<int> labels(n, -1);

        for (int iter = 0; iter < maxIter; ++iter)
        {
            bool changed = false;

            // Assign labels
            for (size_t i = 0; i < n; ++i)
            {
                T minDist = std::numeric_limits<T>::max();
                int bestCluster = -1;
                for (int c = 0; c < k; ++c)
                {
                    T dist = euclideanDistance(data[i], centroids[c]);
                    if (dist < minDist)
                    {
                        minDist = dist;
                        bestCluster = c;
                    }
                }
                if (labels[i] != bestCluster)
                {
                    labels[i] = bestCluster;
                    changed = true;
                }
            }

            if (!changed)
                break;

            // Update centroids
            std::vector<std::vector<T>> newCentroids(k, std::vector<T>(dim, T(0)));
            std::vector<int> counts(k, 0);
            for (size_t i = 0; i < n; ++i)
            {
                int c = labels[i];
                for (size_t j = 0; j < dim; ++j)
                    newCentroids[c][j] += data[i][j];
                counts[c]++;
            }
            for (int c = 0; c < k; ++c)
            {
                if (counts[c] == 0)
                    continue;
                for (size_t j = 0; j < dim; ++j)
                    newCentroids[c][j] /= counts[c];
            }
            centroids = newCentroids;
        }
        return labels;
    }

    // DBSCAN clustering
    template <typename T>
    std::vector<int> DBSCAN(const std::vector<std::vector<T>> &data, T eps, int minPts)
    {
        size_t n = data.size();
        std::vector<int> labels(n, -1);
        int clusterId = 0;

        auto regionQuery = [&](size_t idx)
        {
            std::vector<size_t> neighbors;
            for (size_t i = 0; i < n; ++i)
            {
                if (euclideanDistance(data[idx], data[i]) <= eps)
                    neighbors.push_back(i);
            }
            return neighbors;
        };

        for (size_t i = 0; i < n; ++i)
        {
            if (labels[i] != -1)
                continue;
            auto neighbors = regionQuery(i);
            if (neighbors.size() < static_cast<size_t>(minPts))
            {
                labels[i] = -2; // noise
                continue;
            }
            std::queue<size_t> q;
            q.push(i);
            labels[i] = clusterId;

            while (!q.empty())
            {
                size_t curr = q.front();
                q.pop();
                auto currNeighbors = regionQuery(curr);
                if (currNeighbors.size() >= static_cast<size_t>(minPts))
                {
                    for (auto nb : currNeighbors)
                    {
                        if (labels[nb] == -1 || labels[nb] == -2)
                        {
                            if (labels[nb] == -1)
                                q.push(nb);
                            labels[nb] = clusterId;
                        }
                    }
                }
            }
            clusterId++;
        }
        return labels;
    }

    // Factor Analysis (placeholder)
    template <typename T>
    void factorAnalysis(const std::vector<std::vector<T>> &data,
                        std::vector<std::vector<T>> &loadings)
    {
        // Placeholder: use PCA for factor analysis
        std::vector<T> explainedVariances; // create a named variable for third argument
        PCA(data, loadings, explainedVariances);
    }

    // Multivariate Regression (Ordinary Least Squares)
    template <typename T>
    std::vector<T> multivariateRegression(const std::vector<std::vector<T>> &data,
                                          const std::vector<T> &y)
    {
        size_t n = data.size();
        if (n == 0)
            return {};
        size_t dim = data[0].size();
        if (y.size() != n)
            throw std::invalid_argument("Size mismatch between data and target vector");

        // Compute X^T * X
        std::vector<std::vector<T>> XtX(dim, std::vector<T>(dim, T(0)));
        for (size_t i = 0; i < dim; ++i)
        {
            for (size_t j = 0; j < dim; ++j)
            {
                for (size_t k = 0; k < n; ++k)
                {
                    XtX[i][j] += data[k][i] * data[k][j];
                }
            }
        }

        // Compute X^T * y
        std::vector<T> Xty(dim, T(0));
        for (size_t i = 0; i < dim; ++i)
        {
            for (size_t k = 0; k < n; ++k)
            {
                Xty[i] += data[k][i] * y[k];
            }
        }

        // Solve XtX * beta = Xty using Gaussian elimination
        std::vector<std::vector<T>> A = XtX;
        std::vector<T> b = Xty;
        std::vector<T> beta(dim, T(0));

        // Gaussian elimination
        for (size_t i = 0; i < dim; ++i)
        {
            // Pivot
            size_t maxRow = i;
            for (size_t r = i + 1; r < dim; ++r)
            {
                if (std::abs(A[r][i]) > std::abs(A[maxRow][i]))
                    maxRow = r;
            }
            if (maxRow != i)
            {
                std::swap(A[i], A[maxRow]);
                std::swap(b[i], b[maxRow]);
            }

            if (std::abs(A[i][i]) < 1e-12)
                throw std::runtime_error("Matrix is singular or nearly singular");

            // Eliminate
            for (size_t r = i + 1; r < dim; ++r)
            {
                T factor = A[r][i] / A[i][i];
                for (size_t c = i; c < dim; ++c)
                    A[r][c] -= factor * A[i][c];
                b[r] -= factor * b[i];
            }
        }

        // Back substitution
        for (int i = static_cast<int>(dim) - 1; i >= 0; --i)
        {
            T sum = b[i];
            for (size_t c = i + 1; c < dim; ++c)
                sum -= A[i][c] * beta[c];
            beta[i] = sum / A[i][i];
        }

        return beta;
    }

    // Placeholders for MANOVA and Canonical Correlation
    template <typename T>
    void MANOVA(const std::vector<std::vector<T>> &data)
    {
        // Placeholder implementation
        std::cout << "MANOVA not implemented yet." << std::endl;
    }

    template <typename T>
    void canonicalCorrelation(const std::vector<std::vector<T>> &data1,
                              const std::vector<std::vector<T>> &data2)
    {
        // Placeholder implementation
        std::cout << "Canonical Correlation not implemented yet." << std::endl;
    }
}

#endif // MULTIVARIATE_STATISTICS_H
