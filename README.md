#42-cpp-09

# Bitcoin Exchange Project

## Overview
This project calculates the value of a given amount of Bitcoin using historical exchange rates stored in a CSV file.

## Requirements
- **Program Name:** `btc`
- **Input Format:** `"date | value"`
- **Valid Date Format:** `YYYY-MM-DD`
- **Valid Value Range:** `0 to 1000 BTC`
- **Database:** A CSV file containing historical exchange rates.

## Example Input (`input.txt`)
2011-01-03 | 2 <br/>
2012-01-11 | 1.5 <br/>
2005-05-20 | 3 <br/>

## Expected Output
2011-01-03 => 1 = 10.00 <br/>
2012-01-11 => 10.50 = 25 <br/>
Error: No date for 2005-05-33 <br/>
