# Matplotlib-cpp Setup and Compilation Instructions

This document provides instructions for setting up matplotlib-cpp and compiling the example visualization programs in the statistical libraries.

## Prerequisites

- Python 3.x installed
- Python development headers installed (e.g., python3-dev or python3-devel)
- Matplotlib installed in Python environment

## Compilation Commands

Use the following commands to compile and run the example programs for each library. Adjust the Python include path and library version as needed.

### DescriptiveStatisticsLib

\`\`\`bash
g++ -std=c++11 -I./matplotlib-cpp -I/usr/include/python3.8 DescriptiveStatisticsLib/main.cpp -o descriptive_stats_plot -lpython3.8 -lpthread -lm -lutil -ldl
./descriptive_stats_plot
\`\`\`

### ExploratoryDataAnalysisLib

\`\`\`bash
g++ -std=c++11 -I./matplotlib-cpp -I/usr/include/python3.8 ExploratoryDataAnalysisLib/main.cpp -o exploratory_data_analysis_plot -lpython3.8 -lpthread -lm -lutil -ldl
./exploratory_data_analysis_plot
\`\`\`

### InferentialStatisticsLib

\`\`\`bash
g++ -std=c++11 -I./matplotlib-cpp -I/usr/include/python3.8 InferentialStatisticsLib/main.cpp -o inferential_statistics_plot -lpython3.8 -lpthread -lm -lutil -ldl
./inferential_statistics_plot
\`\`\`

### MultivariateStatisticsLib

\`\`\`bash
g++ -std=c++11 -I./matplotlib-cpp -I/usr/include/python3.8 MultivariateStatisticsLib/main.cpp -o multivariate_statistics_plot -lpython3.8 -lpthread -lm -lutil -ldl
./multivariate_statistics_plot
\`\`\`

### ProbabilityDistributionsLib

\`\`\`bash
g++ -std=c++11 -I./matplotlib-cpp -I/usr/include/python3.8 ProbabilityDistributionsLib/main.cpp -o probability_distributions_plot -lpython3.8 -lpthread -lm -lutil -ldl
./probability_distributions_plot
\`\`\`

## Notes

- If you encounter errors related to \`Python.h\` not found, ensure Python development headers are installed and the include path is correct.
- Adjust the Python version in the include path and linker flags according to your system.
- The examples demonstrate basic usage of matplotlib-cpp for visualization in each statistical library.
