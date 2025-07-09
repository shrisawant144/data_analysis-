#include <iostream>
#include <vector>
#include "MultivariateStatistics.h"

int main()
{
    try
    {
        // Example data: 6 samples, 3 features
        std::vector<std::vector<double>> data = {
            {2.5, 2.4, 1.0},
            {0.5, 0.7, 0.5},
            {2.2, 2.9, 1.2},
            {1.9, 2.2, 0.9},
            {3.1, 3.0, 1.1},
            {2.3, 2.7, 1.3}};

        // PCA
        std::vector<std::vector<double>> components;
        std::vector<double> explainedVariances;
        MultivariateStatistics::PCA(data, components, explainedVariances);
        std::cout << "PCA first principal component:" << std::endl;
        for (double val : components[0])
            std::cout << val << " ";
        std::cout << std::endl;
        std::cout << "Explained variance: " << explainedVariances[0] << std::endl;

        // K-means clustering
        int k = 2;
        std::vector<int> labels = MultivariateStatistics::kMeans(data, k);
        std::cout << "K-means cluster assignments:" << std::endl;
        for (int label : labels)
            std::cout << label << " ";
        std::cout << std::endl;

        // DBSCAN clustering
        double eps = 1.0;
        int minPts = 2;
        std::vector<int> dbscanLabels = MultivariateStatistics::DBSCAN(data, eps, minPts);
        std::cout << "DBSCAN cluster assignments:" << std::endl;
        for (int label : dbscanLabels)
            std::cout << label << " ";
        std::cout << std::endl;

        // Factor Analysis (placeholder)
        std::vector<std::vector<double>> loadings;
        MultivariateStatistics::factorAnalysis(data, loadings);
        std::cout << "Factor Analysis loadings (first component):" << std::endl;
        if (!loadings.empty())
        {
            for (double val : loadings[0])
                std::cout << val << " ";
            std::cout << std::endl;
        }
        else
        {
            std::cout << "No loadings computed." << std::endl;
        }

        // Multivariate Regression example
        std::vector<double> y = {1.0, 2.0, 1.5, 1.8, 2.2, 1.9};
        std::vector<double> beta = MultivariateStatistics::multivariateRegression(data, y);
        std::cout << "Multivariate Regression coefficients:" << std::endl;
        for (double coeff : beta)
            std::cout << coeff << " ";
        std::cout << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
