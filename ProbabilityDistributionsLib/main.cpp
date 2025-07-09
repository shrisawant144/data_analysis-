#include <iostream>
#include "ProbabilityDistributions.h"

int main()
{
    try
    {
        // Normal Distribution example
        double x = 1.0;
        double mean = 0.0;
        double stddev = 1.0;
        double normal_pdf = ProbabilityDistributions::normalPDF(x, mean, stddev);
        std::cout << "Normal PDF at x=" << x << ": " << normal_pdf << std::endl;

        // Poisson Distribution example
        int k = 3;
        double lambda = 2.5;
        double poisson_pmf = ProbabilityDistributions::poissonPMF(k, lambda);
        std::cout << "Poisson PMF at k=" << k << ": " << poisson_pmf << std::endl;

        // Binomial Distribution example
        int n = 10;
        int binomial_k = 4;
        double p = 0.5;
        double binomial_pmf = ProbabilityDistributions::binomialPMF(n, binomial_k, p);
        std::cout << "Binomial PMF at k=" << binomial_k << ": " << binomial_pmf << std::endl;

        // Exponential Distribution example
        double exp_x = 1.5;
        double exp_lambda = 1.0;
        double exponential_pdf = ProbabilityDistributions::exponentialPDF(exp_x, exp_lambda);
        std::cout << "Exponential PDF at x=" << exp_x << ": " << exponential_pdf << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
