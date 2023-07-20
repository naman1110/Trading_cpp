# Trading Strategy
This project implements an crossover trading strategy to generate buy and sell signals for a market for testing purposes.
Uses Multithreading concept for faster result.

# Overview
* Calculates EMA and MA for multiple periods (like 50, 200) using historical closing prices
* Identifies potential crossover points when a shorter period EMA crosses a longer period EMA
* EMA crossover is a popular trading strategy used by market technicians
* Typically used on daily data, but can be applied to any timeframe (intraday, weekly etc)
  
# Implementation
* C++ is used for faster backtesting of strategy
* Prices stored in a vector
* EMA calculated using variable window sizes
* Threading used to speed up EMA calculation
* Golden crossover (50 crossing above 200) indicates buy signal
* Death crossover (50 crossing below 200) indicates sell signal
  
# Moving Averages
* EMA is a type of moving average that places more weight on recent prices
* Responds faster to price changes than simple moving average (SMA)
* 50 and 200 period EMAs are commonly used for crossovers
* Other popular periods are 9, 21 for short term and 100 for medium term

  
# Usage
* Backtest crossover strategy on historical market data
* Optimize EMA periods and confirm signals with other indicators
* Automate strategy for live trading with stop losses etc
  
# Enhancements
* Add more EMA periods and optimization
* Confirm signals with volume, breakouts etc
* Visualize signals and improve output
* Improve threading and performance

# Note: SMA is a lagging indicator.
