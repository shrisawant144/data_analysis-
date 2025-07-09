# DescriptiveStatisticsLib - Practical Analysis Using Descriptive Statistics

## Overview

Descriptive statistics help summarize key insights from raw data, making it easier to understand and use. This library provides fundamental statistical functions to support various types of analysis commonly needed in real-world projects involving sensor data, logs, measurements, and more.

---

## ✅ Types of Analysis Using Descriptive Statistics

### 1. 📉 Sensor Behavior Summary

**Use Case:** Environmental monitoring system (e.g., temperature, humidity sensors)

- **Mean**: What is the average temperature over 24 hours?
- **Min/Max**: What’s the coldest/hottest reading?
- **Standard Deviation**: Is the temperature stable or fluctuating a lot?
- **Range**: What's the span between extremes?

✅ Helps engineers understand how "noisy" or stable their sensors are.

---

### 2. ⚙️ System Performance Baseline

**Use Case:** Embedded system measuring CPU or memory usage

- **Mean CPU usage** over time
- **Peak (Max) usage** — for thermal or power planning
- **Standard deviation** — to detect unpredictable spikes

✅ Helps profile the system to choose proper microcontroller or adjust firmware settings.

---

### 3. 🔍 Anomaly Detection (First Step)

**Use Case:** Detecting unusual behavior in device metrics

- **Outliers** using Z-score or IQR
- E.g., a temperature sensor suddenly reads 99°C while the mean is 26°C
- Helps flag faulty sensors or tampering

✅ Often used before advanced ML models

---

### 4. 📦 Batch Quality Analysis

**Use Case:** Analyzing readings from a manufacturing batch (e.g., resistors)

- **Mean Resistance** vs. Target Value
- **Variance**: Indicates production consistency
- **Percentiles**: Are 95% of products within spec?

✅ Used in quality control labs

---

### 5. 📊 User Behavior Patterns (IoT or Apps)

**Use Case:** Smart home logs or user interactions with a device

- Average time a device is ON
- Most frequent usage hour (mode)
- Day-to-day usage variance

✅ Used in UX tuning, battery life planning

---

### 6. 🧪 Test Summary Reports

**Use Case:** After a test run (like integration or stress tests)

- Mean response time
- Number of requests handled per second
- Max retry attempts
- 95th percentile latency

✅ Used for performance benchmarking

---

### 7. 🕐 Time-Based Rollups

**Use Case:** Real-time systems or dashboards

- Calculate moving average or hourly min/max
- Store `mean per hour` to reduce storage
- Identify trends

✅ Used in dashboards and embedded UIs

---

## 🧠 Recap Table

| Use Case                        | Descriptive Stats Used         | Insight Gained                |
| ------------------------------- | ------------------------------ | ----------------------------- |
| Sensor Summary                  | Mean, Min, Max, Std Dev        | Normal behavior, fluctuations |
| Performance Monitoring          | Mean, Max, Range, Std Dev      | Resource profiling            |
| Anomaly Detection               | Mean, Std Dev, Z-score, Range  | Outlier identification        |
| Quality Control (Manufacturing) | Mean, Variance, Percentiles    | Production consistency        |
| Usage Analytics (IoT)           | Mean, Mode, Median, Range      | User habits                   |
| Test Report Summaries           | Mean, Percentile, Max, Count   | System stability              |
| Time-based Trends               | Rolling Mean, Range per period | Trend analysis, forecasting   |

---

If you would like, I can provide a C++ example implementation for one of these analyses, such as rolling average or outlier detection. Please let me know your preference.
