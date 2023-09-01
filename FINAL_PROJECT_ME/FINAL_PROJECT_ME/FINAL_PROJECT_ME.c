// ------------------------------------------------------------------------------------------
// Name: Million Eyassu
// Class: C Programming
// Abstract: Final Project Part 1
// ------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ------------------------------------------------------------------------------------------
// User Defined Types (UDT)
// ------------------------------------------------------------------------------------------
typedef struct  {
    char strDate[20];
    char strState[20];
    char strCounty[20];
    char strRace[20];
    int intNumInHousehold;
    float sngIncome;
} udtHousehold;

// ------------------------------------------------------------------------------------------
// Prototypes
// ------------------------------------------------------------------------------------------
bool isValidDate(const char* strDate);
int getIntRaceInput();
int getIntCountyInput(int intStateChoice);
void writeSurveyDataToCSV(const struct udtHousehold* surveys, int intNumHouseholds);



// ------------------------------------------------------------------------------------------
// Name: main
// Abstract: This is where the program starts
// ------------------------------------------------------------------------------------------

int main() {
    udtHousehold udtSurvey[100]; // Struct array to store survey data
    int intNumHouseholds = 0; // Number of surveys

    char strContinueAdding = 'Y';

    // Loop to gather survey data
    while (strContinueAdding == 'Y' || strContinueAdding == 'y') {
        char strDate[20];

        // Validate and input the survey date
        while (1) {
            printf("Enter Date of the Survey (YYYY-MM-DD): ");
            scanf("%s", strDate);

            if (isValidDate(strDate)) {
                break; // Valid date format
            }
            else {
                printf("Invalid date format. Please enter the date in YYYY-MM-DD format.\n");
            }
        }

        strcpy(udtSurvey[intNumHouseholds].strDate, strDate);

        printf("\nSelect State:\n");
        printf("1. Ohio\n");
        printf("2. Kentucky\n");

        int intStateChoice;
        // Validate and input the state choice
        while (1) {
            printf("Enter your choice: ");
            int intResult = scanf("%d", &intStateChoice);
            if (intResult == 1 && (intStateChoice == 1 || intStateChoice == 2)) {
                break; // Valid input
            }
            else {
                printf("Invalid input. Please enter a valid choice.\n");
                while (getchar() != '\n'); // Clear the input buffer
            }
        }

        if (intStateChoice == 1) {
            strcpy(udtSurvey[intNumHouseholds].strState, "Ohio");
        }
        else if (intStateChoice == 2) {
            strcpy(udtSurvey[intNumHouseholds].strState, "Kentucky");
        }

        int intCountyChoice = getIntCountyInput(intStateChoice);
        // Map county choice to county name
        if (intCountyChoice == 1) {
            strcpy(udtSurvey[intNumHouseholds].strCounty, "Hamilton");
        }
        else if (intCountyChoice == 2) {
            strcpy(udtSurvey[intNumHouseholds].strCounty, "Butler");
        }
        else if (intCountyChoice == 3) {
            strcpy(udtSurvey[intNumHouseholds].strCounty, "Boone");
        }
        else if (intCountyChoice == 4) {
            strcpy(udtSurvey[intNumHouseholds].strCounty, "Kenton");
        }

        // Get race choice
        int intRaceChoice = getIntRaceInput();
        char raceNames[][20] = { "Caucasian", "African American", "Hispanic", "Asian", "Other" };
        strcpy(udtSurvey[intNumHouseholds].strRace, raceNames[intRaceChoice - 1]);

        // Get number in household
        while (1) {
            printf("\nEnter Number in Household: ");
            int intResult = scanf("%d", &udtSurvey[intNumHouseholds].intNumInHousehold);
            if (intResult == 1 && udtSurvey[intNumHouseholds].intNumInHousehold > 0) {
                break; // Valid input
            }
            else {
                printf("Invalid input. Please enter a valid number.\n");
                while (getchar() != '\n'); // Clear the input buffer
            }
        }

        // Get household income
        while (1) {
            printf("\nEnter Household Yearly Income: ");
            int intResult = scanf("%f", &udtSurvey[intNumHouseholds].sngIncome);

            if (intResult == 1 && udtSurvey[intNumHouseholds].sngIncome > 0) {
                char c;
                while ((c = getchar()) != '\n' && c != EOF); // Clear the input buffer
                break; // Valid input
            }
            else {
                printf("Invalid input. Please enter a valid number.\n");
                while (getchar() != '\n'); // Clear the input buffer
            }
        }

        intNumHouseholds++; // Increment the survey count

        // Ask if the user wants to add another survey
        while (1) {
            printf("Do you want to add another survey? (Y/N): ");
            int intResult = scanf(" %c", &strContinueAdding);
            if (intResult == 1 && (strContinueAdding == 'Y' || strContinueAdding == 'y' || strContinueAdding == 'N' || strContinueAdding == 'n')) {
                break; // Valid input
            }
            else {
                printf("Invalid input. Please enter Y or N.\n");
                while (getchar() != '\n'); // Clear the input buffer
            }
        }
        printf("\n");
    }

    printf("\n-----------------------------------------------------------------\n");
    printf("-- Collected Data:\n");
    printf("-----------------------------------------------------------------\n");

    // Call the function to write survey data to the CSV file
    writeSurveyDataToCSV(udtSurvey, intNumHouseholds);

    // Display collected survey data
    for (int intIndex = 0; intIndex < intNumHouseholds; intIndex++) {
        printf("Household %d:\n", intIndex + 1);
        printf("Date: %s\n", udtSurvey[intIndex].strDate);
        printf("State Choice: %s\n", udtSurvey[intIndex].strState);
        printf("County Choice: %s\n", udtSurvey[intIndex].strCounty);
        printf("Race: %s\n", udtSurvey[intIndex].strRace);
        printf("Number in Household: %d\n", udtSurvey[intIndex].intNumInHousehold);
        printf("Income: %.2f\n\n", udtSurvey[intIndex].sngIncome);
    }

    // End of the program
    return 0; // Indicates successful execution
}


// ------------------------------------------------------------------------------------------
// Name: isValidDate
// Abstract: Validates the date format
// ------------------------------------------------------------------------------------------
bool isValidDate(const char* strDate) {
    // Check if the chrDate has the format "YYYY-MM-DD"
    if (strlen(strDate) != 10) {
        return false;
    }

    if (strDate[4] != '-' || strDate[7] != '-') {
        return false;
    }

    // Validate year, month, and day ranges (you can add more specific checks)
    int intYear, intMonth, intDay;
    if (sscanf(strDate, "%4d-%2d-%2d", &intYear, &intMonth, &intDay) != 3) {
        return false;
    }

    if (intYear < 1900 || intYear > 9999 || intMonth < 1 || intMonth > 12 || intDay < 1 || intDay > 31) {
        return false;
    }

    return true;
}

// ------------------------------------------------------------------------------------------
// Name: getIntRaceInput
// Abstract: Gets user input for race
// ------------------------------------------------------------------------------------------
int getIntRaceInput() {
    int intRaceChoice;
    printf("\nSelect Race of Head of Household:\n");
    printf("1. Caucasian\n");
    printf("2. African American\n");
    printf("3. Hispanic\n");
    printf("4. Asian\n");
    printf("5. Other\n");

    // Loop until valid input is received
    while (1) {
        printf("\nEnter your choice: ");
        int intResult = scanf("%d", &intRaceChoice);
        if (intResult == 1 && intRaceChoice >= 1 && intRaceChoice <= 5) {
            break; // Valid input
        }
        else {
            printf("Invalid input. Please enter a valid choice.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    }
    return intRaceChoice;
}

// ------------------------------------------------------------------------------------------
// Name: getIntCountyInput
// Abstract: Gets user input for county based on state
// ------------------------------------------------------------------------------------------
int getIntCountyInput(int intStateChoice) {
    int intCountyChoice;
    if (intStateChoice == 1) {
        printf("\nSelect County:\n");
        printf("1. Hamilton\n");
        printf("2. Butler\n");
    }
    else if (intStateChoice == 2) {
        printf("\nSelect County:\n");
        printf("3. Boone\n");
        printf("4. Kenton\n");
    }

    // Loop until valid input is received
    while (1) {
        printf("Enter your choice: ");
        int intResult = scanf("%d", &intCountyChoice);
        if ((intStateChoice == 1 && (intResult == 1 && (intCountyChoice == 1 || intCountyChoice == 2))) ||
            (intStateChoice == 2 && (intResult == 1 && (intCountyChoice == 3 || intCountyChoice == 4)))) {
            break; // Valid input
        }
        else {
            printf("Invalid input. Please enter a valid choice.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    }

    return intCountyChoice;
}

// ------------------------------------------------------------------------------------------
// Name: writeSurveyDataToCSV
// Abstract: Writes survey data to CSV file
// ------------------------------------------------------------------------------------------
void writeSurveyDataToCSV(const udtHousehold* pudtSurvey, int intNumHouseholds) {
    FILE* pudtFile = fopen("survey_data.csv", "a"); // Open the file in append mode

    if (pudtFile == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    // Check if the file is empty (size is 0) to determine if headers need to be added
    fseek(pudtFile, 0, SEEK_END); // Move to the end of the file
    long lngFileSize = ftell(pudtFile); // Get the current position (which is the size of the file)

    if (lngFileSize == 0) {
        fprintf(pudtFile, "Date,State,County,Race,Number in Household,Income\n"); // Headers
    }

    // Loop through survey data and write to the file
    for (int intIndex = 0; intIndex < intNumHouseholds; intIndex++) {
        fprintf(pudtFile, "%s,%s,%s,%s,%d,%.2f\n", pudtSurvey[intIndex].strDate, pudtSurvey[intIndex].strState, pudtSurvey[intIndex].strCounty, pudtSurvey[intIndex].strRace, pudtSurvey[intIndex].intNumInHousehold, pudtSurvey[intIndex].sngIncome);
    }

    fclose(pudtFile);
}

