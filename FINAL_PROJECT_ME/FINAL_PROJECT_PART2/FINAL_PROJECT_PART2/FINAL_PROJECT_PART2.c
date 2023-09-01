// ------------------------------------------------------------------------------------------
// Name: Million Eyassu
// Class: C Programming
// Abstract: Final Project Part 2
// ------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// ------------------------------------------------------------------------------------------
// Constants
// ------------------------------------------------------------------------------------------
#define MAX_FILENAME_LENGTH 256
#define MAX_FIELD_LENGTH 100
#define MAX_ENTRIES 100

// ------------------------------------------------------------------------------------------
// User Defined Types (UDT)
// ------------------------------------------------------------------------------------------
typedef struct {
    char strDate[MAX_FIELD_LENGTH];
    char strState[MAX_FIELD_LENGTH];
    char strCounty[MAX_FIELD_LENGTH];
    char strRace[MAX_FIELD_LENGTH];
    int intNumberInHousehold;
    float sngIncome;
} udtSurvey;

// ------------------------------------------------------------------------------------------
// Prototypes
// ------------------------------------------------------------------------------------------
void ProcessData(udtSurvey* udtData, size_t intNumEntries, char action);
float CalculatePovertyThreshold(int intNumberInHousehold);
int CalculateTotalHouseholds(udtSurvey* udtData, size_t intNumEntries);
void TotalHouseholdsSurveyedByCounty(udtSurvey* udtData, size_t intNumEntries);
void TotalHouseholdsSurveyedByRace(udtSurvey* udtData, size_t intNumEntries);
float CalculateAverageIncome(udtSurvey* udtData, size_t intNumEntries);
void AverageIncomeByCountyAndState(udtSurvey* udtData, size_t intNumEntries);
void AverageIncomeByRace(udtSurvey* udtData, size_t intNumEntries);
float CalculatePercentageBelowPoverty(udtSurvey* udtData, size_t intNumEntries);
void PercentageBelowPovertyByCountyAndState(udtSurvey* udtData, size_t intNumEntries); 
void PercentageBelowPovertyByRace(udtSurvey* udtData, size_t intNumEntries);

// ------------------------------------------------------------------------------------------
// Name: main
// Abstract: This is where the program starts
// ------------------------------------------------------------------------------------------
int main()
{
    // Define the path to the folder containing the CSV file
    const char* strFolderPath = "C:\\Users\\Eyass\\Desktop\\no hard drive\\C Programming\\FINAL_PROJECT_ME\\FINAL_PROJECT_ME";

    // Construct the full path to the CSV file
    char strCsvFilePath[MAX_FILENAME_LENGTH];
    snprintf(strCsvFilePath, sizeof(strCsvFilePath), "%s\\%s", strFolderPath, "survey_data.csv");

    // Open the CSV file
    FILE* csvFile = fopen(strCsvFilePath, "r");
    if (!csvFile) {
        perror("Error opening CSV file");
        return 1;
    }

    // Skip the header line
    char strHeaderLine[MAX_FIELD_LENGTH];
    if (fgets(strHeaderLine, sizeof(strHeaderLine), csvFile) == NULL) {
        perror("Error reading header line");
        fclose(csvFile);
        return 1;
    }

    // Read and store data into the structure array
    udtSurvey csvData[MAX_ENTRIES];
    size_t intNumEntries = 0;
    while (intNumEntries < MAX_ENTRIES && fscanf(csvFile, "%[^,],%[^,],%[^,],%[^,],%d,%f\n",
        csvData[intNumEntries].strDate,
        csvData[intNumEntries].strState,
        csvData[intNumEntries].strCounty,
        csvData[intNumEntries].strRace,
        &csvData[intNumEntries].intNumberInHousehold,
        &csvData[intNumEntries].sngIncome) == 6) {
        intNumEntries++;
    }

    fclose(csvFile);

    char strContinue;
    do {
        // prints the options for the user 
        printf("\nA. Total Households Surveyed:\n");
        printf("B. Total Households Surveyed per County:\n");
        printf("C. Total Households Surveyed per Race:\n");
        printf("D. Average Household Income:\n");
        printf("E. Average Household Income by county and state:\n");
        printf("F. Average Household Income by race:\n");
        printf("G. Percentage below Poverty:\n");
        printf("H. Percentage below Poverty by county and state:\n");
        printf("I. Percentage below Poverty by race:\n");
        printf("\nEnter the action (A through I): ");
        char strAction;
        scanf(" %c", &strAction);
        strAction = toupper(strAction); // Convert the input to uppercase

        switch (strAction) {
        case 'A':
            printf("Total Households Surveyed: %d\n", CalculateTotalHouseholds(csvData, intNumEntries));
            break;
        case 'B':
            TotalHouseholdsSurveyedByCounty(csvData, intNumEntries);
            break;
        case 'C':
            TotalHouseholdsSurveyedByRace(csvData, intNumEntries);
            break;
        case 'D':
            printf("Average Household Income: %.2f\n", CalculateAverageIncome(csvData, intNumEntries));
            break;
        case 'E':
            AverageIncomeByCountyAndState(csvData, intNumEntries);
            break;
        case 'F':
            AverageIncomeByRace(csvData, intNumEntries);
            break;
        case 'G':
            printf("Percentage below Poverty: %.2f%%\n", CalculatePercentageBelowPoverty(csvData, intNumEntries));
            break;
        case 'H':
            PercentageBelowPovertyByCountyAndState(csvData, intNumEntries);
            break;
        case 'I':
            PercentageBelowPovertyByRace(csvData, intNumEntries);
            break;
        default:
            printf("Invalid action.\n");
            break;
        }

        printf("\nDo you want to continue (Y/N)? ");
        scanf(" %c", &strContinue);
        strContinue = toupper(strContinue); // Convert the input to uppercase
    } while (strContinue == 'Y'); 
    
    return 0;
}


// ------------------------------------------------------------------------------------------
// Name: ProcessData
// Abstract: Process data based on user input
// ------------------------------------------------------------------------------------------
void ProcessData(udtSurvey* data, size_t intNumEntries, char action) {
    // Loop through each entry in the data array
    for (size_t i = 0; i < intNumEntries; i++) {
        printf("Entry %zu:\n", i + 1); // Display the entry number

        // Display various data fields of the current entry
        printf("Date: %s\n", data[i].strDate);
        printf("State: %s\n", data[i].strState);
        printf("County: %s\n", data[i].strCounty);
        printf("Race: %s\n", data[i].strRace);
        printf("Number in Household: %d\n", data[i].intNumberInHousehold);
        printf("Income: %.2f\n", data[i].sngIncome);

        printf("\n"); // Add a newline for separation between entries
    }
}


// ------------------------------------------------------------------------------------------
// Name: CalculatePovertyThreshold
// Abstract: Calculate poverty threshold based on the number of people in the household
// ------------------------------------------------------------------------------------------
float CalculatePovertyThreshold(int intNumberInHousehold) {
    if (intNumberInHousehold == 1) {
        return 12000.0;  // Household of 1
    }
    else if (intNumberInHousehold == 2) {
        return 18000.0;  // Household of 2
    }
    else if (intNumberInHousehold == 3) {
        return 25000.0;  // Household of 3
    }
    else if (intNumberInHousehold == 4) {
        return 30000.0;  // Household of 4
    }
    else {
        return 40000.0;  // Household of 5 or more
    }
}


// ------------------------------------------------------------------------------------------
// Name: CalculateTotalHouseholds
// Abstract: Calculate the total number of households surveyed
// ------------------------------------------------------------------------------------------
int CalculateTotalHouseholds(udtSurvey* data, size_t intNumEntries) {
    
    return intNumEntries; // return the amount of entries (households) in the file
}


// ------------------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedByCounty
// Abstract: Calculate and display the total households surveyed by county
// ------------------------------------------------------------------------------------------
void TotalHouseholdsSurveyedByCounty(udtSurvey* udtData, size_t intNumEntries) {
    int intTotalHamilton = 0;   // Counter for total households in Hamilton county
    int intTotalButler = 0;     // Counter for total households in Butler county
    int intTotalBoone = 0;      // Counter for total households in Boone county
    int intTotalKenton = 0;     // Counter for total households in Kenton county

    // Iterate through each entry in the dataset
    for (size_t i = 0; i < intNumEntries; i++) {
        // Check the state of the current entry
        if (strcmp(udtData[i].strState, "Ohio") == 0) {
            // Check the county for Ohio entries
            if (strcmp(udtData[i].strCounty, "Hamilton") == 0) {
                intTotalHamilton++;   // Increment Hamilton county counter
            }
            else if (strcmp(udtData[i].strCounty, "Butler") == 0) {
                intTotalButler++;     // Increment Butler county counter
            }
        }
        // Check the state of the current entry
        else if (strcmp(udtData[i].strState, "Kentucky") == 0) {
            // Check the county for Kentucky entries
            if (strcmp(udtData[i].strCounty, "Boone") == 0) {
                intTotalBoone++;      // Increment Boone county counter
            }
            else if (strcmp(udtData[i].strCounty, "Kenton") == 0) {
                intTotalKenton++;     // Increment Kenton county counter
            }
        }
    }

    // Display the total households surveyed for each county
    printf("Total Households Surveyed by County:\n");
    printf("Ohio - Hamilton: %d\n", intTotalHamilton);
    printf("Ohio - Butler: %d\n", intTotalButler);
    printf("Kentucky - Boone: %d\n", intTotalBoone);
    printf("Kentucky - Kenton: %d\n", intTotalKenton);
}


// ------------------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedByRace
// Abstract: Calculate and display the total households surveyed by race
// ------------------------------------------------------------------------------------------
void TotalHouseholdsSurveyedByRace(udtSurvey* udtData, size_t intNumEntries) {
    int intTotalCaucasian = 0;        // Counter for total Caucasian households
    int intTotalAfricanAmerican = 0;  // Counter for total African American households
    int intTotalHispanic = 0;         // Counter for total Hispanic households
    int intTotalAsian = 0;            // Counter for total Asian households
    int intTotalOther = 0;            // Counter for total households of other races

    // Iterate through each entry in the dataset
    for (size_t i = 0; i < intNumEntries; i++) {
        // Check the race of the current entry and increment the respective counter
        if (strcmp(udtData[i].strRace, "Caucasian") == 0) {
            intTotalCaucasian++;
        }
        else if (strcmp(udtData[i].strRace, "African American") == 0) {
            intTotalAfricanAmerican++;
        }
        else if (strcmp(udtData[i].strRace, "Hispanic") == 0) {
            intTotalHispanic++;
        }
        else if (strcmp(udtData[i].strRace, "Asian") == 0) {
            intTotalAsian++;
        }
        else {
            intTotalOther++;
        }
    }

    // Display the total households surveyed for each race
    printf("Total Households Surveyed by Race:\n");
    printf("Caucasian: %d\n", intTotalCaucasian);
    printf("African American: %d\n", intTotalAfricanAmerican);
    printf("Hispanic: %d\n", intTotalHispanic);
    printf("Asian: %d\n", intTotalAsian);
    printf("Other: %d\n", intTotalOther);
}


// ------------------------------------------------------------------------------------------
// Name: CalculateAverageIncome
// Abstract: Calculate the average household income
// ------------------------------------------------------------------------------------------
float CalculateAverageIncome(udtSurvey* udtData, size_t intNumEntries) {
    float sngTotalIncome = 0.0;  // Initialize the sum of incomes to 0

    // Iterate through each entry in the dataset
    for (size_t i = 0; i < intNumEntries; i++) {
        sngTotalIncome += udtData[i].sngIncome;  // Accumulate the income of each entry
    }

    // Calculate and return the average income by dividing the total income by the number of entries
    return sngTotalIncome / intNumEntries;
}


// ------------------------------------------------------------------------------------------
// Name: AverageIncomeByCountyAndState
// Abstract: Calculate and display the average income by county and state
// ------------------------------------------------------------------------------------------
void AverageIncomeByCountyAndState(udtSurvey* udtData, size_t intNumEntries) {
    // Variables for state level calculations
    float sngSumOhio = 0.0;
    int intCountOhio = 0;

    float sngSumKentucky = 0.0;
    int intCountKentucky = 0;

    // Variables for county level calculations
    float sngSumHamilton = 0.0;
    int intCountHamilton = 0;

    float sngSumButler = 0.0;
    int intCountButler = 0;

    float sngSumBoone = 0.0;
    int intCountBoone = 0;

    float sngSumKenton = 0.0;
    int intCountKenton = 0;

    // Iterate through each entry in the dataset
    for (size_t i = 0; i < intNumEntries; i++) {
        // Check the state
        if (strcmp(udtData[i].strState, "Ohio") == 0) {
            sngSumOhio += udtData[i].sngIncome;  // Accumulate income for Ohio
            intCountOhio++;  // Increment count of Ohio households

            // Check the county within Ohio
            if (strcmp(udtData[i].strCounty, "Hamilton") == 0) {
                sngSumHamilton += udtData[i].sngIncome;  // Accumulate income for Hamilton, Ohio
                intCountHamilton++;  // Increment count of Hamilton households
            }
            else if (strcmp(udtData[i].strCounty, "Butler") == 0) {
                sngSumButler += udtData[i].sngIncome;  // Accumulate income for Butler, Ohio
                intCountButler++;  // Increment count of Butler households
            }
        }
        // Check the state
        else if (strcmp(udtData[i].strState, "Kentucky") == 0) {
            sngSumKentucky += udtData[i].sngIncome;  // Accumulate income for Kentucky
            intCountKentucky++;  // Increment count of Kentucky households

            // Check the county within Kentucky
            if (strcmp(udtData[i].strCounty, "Boone") == 0) {
                sngSumBoone += udtData[i].sngIncome;  // Accumulate income for Boone, Kentucky
                intCountBoone++;  // Increment count of Boone households
            }
            else if (strcmp(udtData[i].strCounty, "Kenton") == 0) {
                sngSumKenton += udtData[i].sngIncome;  // Accumulate income for Kenton, Kentucky
                intCountKenton++;  // Increment count of Kenton households
            }
        }
    }

    // Display average income for each state and county
    printf("Average Household Income\n\n");

    if (intCountOhio > 0) {
        printf("Ohio:\t$%.2f\n", sngSumOhio / intCountOhio);

        if (intCountHamilton > 0) {
            printf("   Hamilton:\t$%.2f\n", sngSumHamilton / intCountHamilton);
        }
        if (intCountButler > 0) {
            printf("   Butler:\t$%.2f\n", sngSumButler / intCountButler);
        }
    }
    if (intCountKentucky > 0) {
        printf("Kentucky:\t$%.2f\n", sngSumKentucky / intCountKentucky);

        if (intCountBoone > 0) {
            printf("   Boone:\t$%.2f\n", sngSumBoone / intCountBoone);
        }
        if (intCountKenton > 0) {
            printf("   Kenton:\t$%.2f\n", sngSumKenton / intCountKenton);
        }
    }
}


// ------------------------------------------------------------------------------------------
// Name: AverageIncomeByRace
// Abstract: Calculate and display the average income by race
// ------------------------------------------------------------------------------------------
void AverageIncomeByRace(udtSurvey* udtData, size_t intNumEntries) {
    // Variables to store sum and count of income for each race
    float sngSumCaucasian = 0.0;
    int intCountCaucasian = 0;

    float sngSumAfricanAmerican = 0.0;
    int intCountAfricanAmerican = 0;

    float sngSumHispanic = 0.0;
    int intCountHispanic = 0;

    float sngSumAsian = 0.0;
    int intCountAsian = 0;

    float sngSumOther = 0.0;
    int intCountOther = 0;

    // Iterate through each entry in the dataset
    for (size_t intIndex = 0; intIndex < intNumEntries; intIndex++) {
        // Check the race and accumulate income and count for each race
        if (strcmp(udtData[intIndex].strRace, "Caucasian") == 0) {
            sngSumCaucasian += udtData[intIndex].sngIncome;  // Accumulate income for Caucasians
            intCountCaucasian++;  // Increment count of Caucasians
        }
        else if (strcmp(udtData[intIndex].strRace, "African American") == 0) {
            sngSumAfricanAmerican += udtData[intIndex].sngIncome;  // Accumulate income for African Americans
            intCountAfricanAmerican++;  // Increment count of African Americans
        }
        else if (strcmp(udtData[intIndex].strRace, "Hispanic") == 0) {
            sngSumHispanic += udtData[intIndex].sngIncome;  // Accumulate income for Hispanics
            intCountHispanic++;  // Increment count of Hispanics
        }
        else if (strcmp(udtData[intIndex].strRace, "Asian") == 0) {
            sngSumAsian += udtData[intIndex].sngIncome;  // Accumulate income for Asians
            intCountAsian++;  // Increment count of Asians
        }
        else if (strcmp(udtData[intIndex].strRace, "Other") == 0) {
            sngSumOther += udtData[intIndex].sngIncome;  // Accumulate income for Other
            intCountOther++;  // Increment count of Other
        }
    }

    // Display average income for each race
    printf("Average Income by Race\n\n");

    if (intCountCaucasian > 0) {
        printf("Caucasian:\t$%.2f\n", sngSumCaucasian / intCountCaucasian);
    }
    if (intCountAfricanAmerican > 0) {
        printf("African American:\t$%.2f\n", sngSumAfricanAmerican / intCountAfricanAmerican);
    }
    if (intCountHispanic > 0) {
        printf("Hispanic:\t$%.2f\n", sngSumHispanic / intCountHispanic);
    }
    if (intCountAsian > 0) {
        printf("Asian:\t$%.2f\n", sngSumAsian / intCountAsian);
    }
    if (intCountOther > 0) {
        printf("Other:\t$%.2f\n", sngSumOther / intCountOther);
    }
}


// ------------------------------------------------------------------------------------------
// Name: CalculatePercentageBelowPoverty
// Abstract: Calculate the percentage of households below the poverty threshold
// ------------------------------------------------------------------------------------------
float CalculatePercentageBelowPoverty(udtSurvey* udtData, size_t intNumEntries) {
    int intCountBelowPoverty = 0;  // Variable to count households below poverty

    // Iterate through each entry in the dataset
    for (size_t intIndex = 0; intIndex < intNumEntries; intIndex++) {
        // Check the number of people in the household and their income to determine poverty status
        if (udtData[intIndex].intNumberInHousehold == 1 && udtData[intIndex].sngIncome < 12000) {
            intCountBelowPoverty++;  // Increment count if household is below poverty threshold
        }
        else if (udtData[intIndex].intNumberInHousehold == 2 && udtData[intIndex].sngIncome < 18000) {
            intCountBelowPoverty++;  
        }
        else if (udtData[intIndex].intNumberInHousehold == 3 && udtData[intIndex].sngIncome < 25000) {
            intCountBelowPoverty++; 
        }
        else if (udtData[intIndex].intNumberInHousehold == 4 && udtData[intIndex].sngIncome < 30000) {
            intCountBelowPoverty++; 
        }
        else if (udtData[intIndex].intNumberInHousehold >= 5 && udtData[intIndex].sngIncome < 40000) {
            intCountBelowPoverty++;  
        }
    }

    // Calculate the percentage of households below poverty
    float sngPercentageBelowPoverty = (float)intCountBelowPoverty / intNumEntries * 100.0;

    return sngPercentageBelowPoverty;  // Return the calculated percentage
}


// ------------------------------------------------------------------------------------------
// Name: PercentageBelowPovertyByCountyAndState
// Abstract: Calculate and display the percentage of households below poverty by county and state
// ------------------------------------------------------------------------------------------
void PercentageBelowPovertyByCountyAndState(udtSurvey* udtData, size_t intNumEntries) {
    // Variables to count households below poverty in each county and state
    int intCountHamiltonOhio = 0;
    int intCountButlerOhio = 0;
    int intCountBooneKentucky = 0;
    int intCountKentonKentucky = 0;

    // Variables to count total households in each county and state
    int intTotalHamiltonOhio = 0;
    int intTotalButlerOhio = 0;
    int intTotalBooneKentucky = 0;
    int intTotalKentonKentucky = 0;

    // Iterate through each entry in the dataset
    for (size_t intIndex = 0; intIndex < intNumEntries; intIndex++) {
        // Check if the state is Ohio
        if (strcmp(udtData[intIndex].strState, "Ohio") == 0) {
            // Check if the county is Hamilton
            if (strcmp(udtData[intIndex].strCounty, "Hamilton") == 0) {
                intTotalHamiltonOhio++;  // Increment total households in Hamilton, Ohio
                // Check if the household income is below the poverty threshold
                if (udtData[intIndex].sngIncome < CalculatePovertyThreshold(udtData[intIndex].intNumberInHousehold)) {
                    intCountHamiltonOhio++;  // Increment households below poverty in Hamilton, Ohio
                }
            }
            // Check if the county is Butler
            else if (strcmp(udtData[intIndex].strCounty, "Butler") == 0) {
                intTotalButlerOhio++;  // Increment total households in Butler, Ohio
                // Check if the household income is below the poverty threshold
                if (udtData[intIndex].sngIncome < CalculatePovertyThreshold(udtData[intIndex].intNumberInHousehold)) {
                    intCountButlerOhio++;  // Increment households below poverty in Butler, Ohio
                }
            }
        }
        // Check if the state is Kentucky
        else if (strcmp(udtData[intIndex].strState, "Kentucky") == 0) {
            // Check if the county is Boone
            if (strcmp(udtData[intIndex].strCounty, "Boone") == 0) {
                intTotalBooneKentucky++;  // Increment total households in Boone, Kentucky
                // Check if the household income is below the poverty threshold
                if (udtData[intIndex].sngIncome < CalculatePovertyThreshold(udtData[intIndex].intNumberInHousehold)) {
                    intCountBooneKentucky++;  // Increment households below poverty in Boone, Kentucky
                }
            }
            // Check if the county is Kenton
            else if (strcmp(udtData[intIndex].strCounty, "Kenton") == 0) {
                intTotalKentonKentucky++;  // Increment total households in Kenton, Kentucky
                // Check if the household income is below the poverty threshold
                if (udtData[intIndex].sngIncome < CalculatePovertyThreshold(udtData[intIndex].intNumberInHousehold)) {
                    intCountKentonKentucky++;  // Increment households below poverty in Kenton, Kentucky
                }
            }
        }
    }

    // Display the results
    printf("Percentage Below Poverty by County and State:\n");
    if (intTotalHamiltonOhio > 0) {
        printf("Ohio - Hamilton:\t%.2f%%\n", (float)intCountHamiltonOhio / intTotalHamiltonOhio * 100);
    }
    if (intTotalButlerOhio > 0) {
        printf("Ohio - Butler:\t%.2f%%\n", (float)intCountButlerOhio / intTotalButlerOhio * 100);
    }
    if (intTotalBooneKentucky > 0) {
        printf("Kentucky - Boone:\t%.2f%%\n", (float)intCountBooneKentucky / intTotalBooneKentucky * 100);
    }
    if (intTotalKentonKentucky > 0) {
        printf("Kentucky - Kenton:\t%.2f%%\n", (float)intCountKentonKentucky / intTotalKentonKentucky * 100);
    }


}


// ------------------------------------------------------------------------------------------
// Name: PercentageBelowPovertyByRace
// Abstract: Calculate and display the percentage of households below poverty by race
// ------------------------------------------------------------------------------------------
void PercentageBelowPovertyByRace(udtSurvey* udtData, size_t intNumEntries) {
    // Variables to count households below poverty for each race
    int intCountCaucasian = 0;
    int intCountAfricanAmerican = 0;
    int intCountHispanic = 0;
    int intCountAsian = 0;
    int intCountOther = 0;

    // Variables to count total households for each race
    int intTotalCaucasian = 0;
    int intTotalAfricanAmerican = 0;
    int intTotalHispanic = 0;
    int intTotalAsian = 0;
    int intTotalOther = 0;

    // Iterate through each entry in the dataset
    for (size_t intIndex = 0; intIndex < intNumEntries; intIndex++) {
        // Check the race of the household in the current entry
        if (strcmp(udtData[intIndex].strRace, "Caucasian") == 0) {
            intTotalCaucasian++;  // Increment total households of Caucasian race
            // Check if the household income is below the poverty threshold
            if (udtData[intIndex].sngIncome < CalculatePovertyThreshold(udtData[intIndex].intNumberInHousehold)) {
                intCountCaucasian++;  // Increment households below poverty of Caucasian race
            }
        }
        else if (strcmp(udtData[intIndex].strRace, "African American") == 0) {
            intTotalAfricanAmerican++;  // Increment total households of African American race
            // Check if the household income is below the poverty threshold
            if (udtData[intIndex].sngIncome < CalculatePovertyThreshold(udtData[intIndex].intNumberInHousehold)) {
                intCountAfricanAmerican++;  // Increment households below poverty of African American race
            }
        }
        else if (strcmp(udtData[intIndex].strRace, "Hispanic") == 0) {
            intTotalHispanic++;  // Increment total households of Hispanic race
            // Check if the household income is below the poverty threshold
            if (udtData[intIndex].sngIncome < CalculatePovertyThreshold(udtData[intIndex].intNumberInHousehold)) {
                intCountHispanic++;  // Increment households below poverty of Hispanic race
            }
        }
        else if (strcmp(udtData[intIndex].strRace, "Asian") == 0) {
            intTotalAsian++;  // Increment total households of Asian race
            // Check if the household income is below the poverty threshold
            if (udtData[intIndex].sngIncome < CalculatePovertyThreshold(udtData[intIndex].intNumberInHousehold)) {
                intCountAsian++;  // Increment households below poverty of Asian race
            }
        }
        else {
            intTotalOther++;  // Increment total households of other race
            // Check if the household income is below the poverty threshold
            if (udtData[intIndex].sngIncome < CalculatePovertyThreshold(udtData[intIndex].intNumberInHousehold)) {
                intCountOther++;  // Increment households below poverty of other race
            }
        }
    }

    // Display the results
    printf("Percentage Below Poverty by Race:\n");
    if (intTotalCaucasian > 0) {
        printf("Caucasian:\t%.2f%%\n", (float)intCountCaucasian / intTotalCaucasian * 100);
    }
    if (intTotalAfricanAmerican > 0) {
        printf("African American:\t%.2f%%\n", (float)intCountAfricanAmerican / intTotalAfricanAmerican * 100);
    }
    if (intTotalHispanic > 0) {
        printf("Hispanic:\t%.2f%%\n", (float)intCountHispanic / intTotalHispanic * 100);
    }
    if (intTotalAsian > 0) {
        printf("Asian:\t%.2f%%\n", (float)intCountAsian / intTotalAsian * 100);
    }
    if (intTotalOther > 0) {
        printf("Other:\t%.2f%%\n", (float)intCountOther / intTotalOther * 100);
    }
}


