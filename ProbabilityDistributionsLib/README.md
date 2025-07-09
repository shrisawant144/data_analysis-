# Probability Distributions Library

## What is a Probability Distribution?

A **probability distribution** describes how the **values of a random variable** are distributed — that is, how likely each outcome is.

It answers:
**“What is the probability that a random variable takes a certain value (or range of values)?”**

## Two Main Types

| Type           | Description                                   | Example                    |
| -------------- | --------------------------------------------- | -------------------------- |
| **Discrete**   | Probabilities assigned to **specific values** | Dice rolls, coin tosses    |
| **Continuous** | Probabilities over **ranges of values**       | Heights, temperature, etc. |

## Discrete Probability Distributions

### 1. **Bernoulli Distribution**

- Outcome: 0 or 1 (yes/no, success/failure)
- Example: Tossing a coin once
- Parameters: `p` (probability of success)

### 2. **Binomial Distribution**

- Repeated Bernoulli trials (e.g., 10 coin tosses)
- Example: How many heads in 10 tosses?
- Parameters: `n` (number of trials), `p` (prob. of success)

### 3. **Poisson Distribution**

- Counts of events in a fixed interval (time/space)
- Example: Number of calls received per hour
- Parameter: `λ` (average rate of occurrence)

## Continuous Probability Distributions

### 1. **Normal Distribution (Gaussian)**

- Bell curve shape
- Most real-world measurements (height, IQ, sensor noise)
- Parameters: `μ` (mean), `σ` (standard deviation)

### 2. **Uniform Distribution**

- All outcomes in a range are equally likely
- Example: Random number between 0 and 1

### 3. **Exponential Distribution**

- Time between events in a Poisson process
- Example: Time between arrivals at a queue

## Summary Table

| Distribution          | Type       | Common Use Case                            |
| --------------------- | ---------- | ------------------------------------------ |
| **Bernoulli**         | Discrete   | One-time yes/no outcome                    |
| **Binomial**          | Discrete   | Count of successes in repeated trials      |
| **Poisson**           | Discrete   | Count of rare events                       |
| **Uniform**           | Continuous | Equal probability across range             |
| **Normal (Gaussian)** | Continuous | Measurement, sensor data                   |
| **Exponential**       | Continuous | Time between events (e.g., system failure) |

## Why Use Probability Distributions?

| Purpose               | Examples                          |
| --------------------- | --------------------------------- |
| 🎲 Model randomness   | Coin toss, sensor noise, failures |
| 📈 Make predictions   | Based on known distributions      |
| 🧪 Run simulations    | Monte Carlo methods               |
| 📊 Hypothesis testing | Compare observed vs expected      |
| 🤖 Machine learning   | Priors, likelihoods, sampling     |

## Library Coverage

This library implements the following distributions:

- Normal Distribution (PDF)
- Poisson Distribution (PMF)
- Binomial Distribution (PMF)
- Exponential Distribution (PDF)

## Example Code

See `main.cpp` for example usage of each distribution function.

---

## Would You Like To See:

- A **graph** comparing key distributions?
- Code examples (C++ or Python) that simulate or visualize them?
- How they're used in **embedded systems**, **machine learning**, or **reliability modeling**?

Let me know how deep you'd like to go!
