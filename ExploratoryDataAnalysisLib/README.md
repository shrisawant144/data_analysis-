# Exploratory Data Analysis (EDA) Library

## 5. Exploratory Data Analysis (EDA)

### What is EDA?

Exploratory Data Analysis (EDA) is the process of examining a dataset visually and statistically to:

- Understand its structure
- Identify patterns, anomalies, and relationships
- Form hypotheses for further analysis

It's like getting to know your data before building models or drawing conclusions.

### Why Do We Use EDA?

| Purpose                          | Example                               |
| -------------------------------- | ------------------------------------- |
| Detect missing or invalid values | Empty fields in sensor logs           |
| Understand distributions         | Is sensor noise normally distributed? |
| Spot outliers                    | Voltage spikes, corrupted readings    |
| Identify variable relationships  | Does temperature affect humidity?     |
| Validate assumptions             | Are features linearly related?        |

### Common EDA Techniques

1. Summary Statistics

   - Mean, median, standard deviation, min, max
   - Used to get a quick feel for each variable

2. Visualizations
   | Plot Type | Use Case |
   | ------------ | --------------------------------- |
   | Histogram | Distribution of a variable |
   | Box Plot | Outliers, quartiles |
   | Scatter Plot | Correlation between two variables |
   | Line Plot | Trends over time |
   | Heatmap | Feature correlation matrix |

3. Missing Value Analysis

   - Count or visualize nulls
   - Replace, drop, or impute missing data

4. Outlier Detection
   - Z-score, IQR method, visual inspection (box plots)

### Tools Used for EDA

| Language | Libraries/Tools                                                          |
| -------- | ------------------------------------------------------------------------ |
| Python   | pandas, matplotlib, seaborn, plotly, sweetviz, ydata-profiling           |
| R        | ggplot2, dplyr, tidyverse                                                |
| C++      | Usually minimal EDA; preprocessing done elsewhere or through CSV parsers |
| Excel    | Pivot tables, filters, charts                                            |

### Example (EDA for IoT Sensor Logs)

Dataset: Environmental sensor log with temperature, humidity, light levels

Steps:

1. Read data from CSV/log file
2. Plot histograms of temperature and humidity
3. Use scatter plot to see correlation between temperature & humidity
4. Detect outliers in light level (sudden drops/spikes)
5. Check missing timestamps or gaps in data logging

### Summary

| Aspect      | Description                                 |
| ----------- | ------------------------------------------- |
| Goal        | Understand your dataset deeply              |
| Outcome     | Cleaned, structured data with hypotheses    |
| Importance  | Helps avoid bad assumptions and poor models |
| When to use | Before modeling, after data collection      |

---

Would you like a downloadable EDA checklist, or an example Python/C++ code for EDA on real sensor or CSV data?
