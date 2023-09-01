# Household Income Survey Analysis (C Program)

This project is a two-part C application designed for the Census Bureau to obtain, validate, and analyze household income survey data within the Cincinnati area, including Northern Kentucky.

## Table of Contents

- [Overview](#overview)
- [Part 1: Data Collection and Validation](#part-1-data-collection-and-validation)
- [Part 2: Data Analysis](#part-2-data-analysis)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Overview

The project consists of two main parts:

### Part 1: Data Collection and Validation

- Accepts and validates survey data, including:
  - Date of the survey
  - State (Ohio or Kentucky)
  - County (limited to specific counties)
  - Race of head of household
  - Number in Household (greater than 0)
  - Yearly income of the household (numeric, greater than 0)
- Saves validated data as a comma-delimited text file, appending new data to the existing data.

### Part 2: Data Analysis

- Reads the most recent text file containing survey data.
- Loads data into a structure array.
- Processes the data based on user-selected actions:
  - A. Total Households Surveyed
  - B. Total Households Surveyed per County and State
  - C. Total Households Surveyed per Race
  - D. Average Household Income
  - E. Average Household Income by County and State
  - F. Average Household Income by Race
  - G. Percentage below Poverty (based on predefined criteria)
  - H. Percentage below Poverty by County and State
  - I. Percentage below Poverty by Race

## Usage

To use the C application, follow these steps:

1. Clone the repository to your local machine:

   ```bash
   git clone https://github.com/your-username/household-income-survey-c.git

2. Navigate to the project directory
   cd household-income-survey-c

3. Part 1: Data Collection and Validation
  - Compile and execute Part 1 of the application to collect and validate survey data.
  - Follow on-screen prompts for data input.
    
  gcc part1.c -o part1
  ./part1

4. Part 2: Data Analysis
  - Compile and execute Part 2 of the application to analyze the survey data.
  - Follow on-screen prompts to select an action (A to I) for data analysis.
    
    gcc part2.c -o part2
    ./part2

 
