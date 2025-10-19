// log_analyzer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define LOG_FILE_NAME "system.log"

// Function Prototypes
void create_dummy_log_file();
void analyze_log_levels();
void search_logs_by_time_range();
void print_menu();

/**
 * @brief Main function that drives the log analyzer tool.
 *
 * It first ensures a dummy log file exists, then enters a menu-driven loop
 * for the user to choose an analysis action.
 */
int main() {
    create_dummy_log_file(); // Ensure the log file exists for analysis

    int choice = 0;
    while (1) {
        print_menu();
        int scan_result = scanf("%d", &choice);
        while (getchar() != '\n'); // Clear input buffer

        if (scan_result != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                analyze_log_levels();
                break;
            case 2:
                search_logs_by_time_range();
                break;
            case 3:
                printf("\nExiting log analyzer. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid option. Please try again.\n");
        }
    }
    return 0;
}

/**
 * @brief Displays the main menu.
 */
void print_menu() {
    printf("\n--- Log Analyzer Menu ---\n");
    printf("1. Count Log Levels (ERROR, WARNING, INFO)\n");
    printf("2. Search Logs by Time Range\n");
    printf("3. Exit\n");
    printf("-------------------------\n");
    printf("Enter your choice: ");
}

/**
 * @brief Reads the log file and counts the occurrences of each log level.
 *
 * Opens the log file, iterates through each line, and uses string searching
 * to identify and count log levels.
 */
void analyze_log_levels() {
    FILE *fp = fopen(LOG_FILE_NAME, "r");
    if (fp == NULL) {
        perror("Error opening log file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int error_count = 0;
    int warning_count = 0;
    int info_count = 0;
    int line_number = 0;

    printf("\nAnalyzing log file for levels...\n");

    // Read the file line by line
    while (fgets(line, sizeof(line), fp) != NULL) {
        line_number++;
        if (strstr(line, "[ERROR]")) {
            error_count++;
        } else if (strstr(line, "[WARNING]")) {
            warning_count++;
        } else if (strstr(line, "[INFO]")) {
            info_count++;
        }
    }

    fclose(fp);

    printf("\n--- Log Level Analysis Summary ---\n");
    printf("Total lines processed: %d\n", line_number);
    printf("Error count:     %d\n", error_count);
    printf("Warning count:   %d\n", warning_count);
    printf("Info count:      %d\n", info_count);
    printf("----------------------------------\n");
}

/**
 * @brief Searches for and prints log entries within a user-specified time range.
 *
 * The time format is assumed to be HH:MM:SS at the start of the log line.
 */
void search_logs_by_time_range() {
    char start_time[10];
    char end_time[10];

    printf("\nEnter start time (HH:MM:SS): ");
    scanf("%9s", start_time);
    printf("Enter end time (HH:MM:SS): ");
    scanf("%9s", end_time);
    while (getchar() != '\n'); // Clear buffer

    // Basic validation
    if (strlen(start_time) != 8 || strlen(end_time) != 8 || strcmp(start_time, end_time) > 0) {
        printf("\nInvalid time format or range. Please use HH:MM:SS and ensure start time is before end time.\n");
        return;
    }

    FILE *fp = fopen(LOG_FILE_NAME, "r");
    if (fp == NULL) {
        perror("Error opening log file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char timestamp[10];
    int found_count = 0;

    printf("\n--- Logs between %s and %s ---\n", start_time, end_time);

    while (fgets(line, sizeof(line), fp) != NULL) {
        // Extract timestamp from the line (assuming it's the first 8 characters)
        strncpy(timestamp, line, 8);
        timestamp[8] = '\0'; // Null-terminate the string

        // Compare timestamps
        if (strcmp(timestamp, start_time) >= 0 && strcmp(timestamp, end_time) <= 0) {
            printf("%s", line);
            found_count++;
        }
    }

    if (found_count == 0) {
        printf("No log entries found in the specified time range.\n");
    }
    printf("---------------------------------------\n");

    fclose(fp);
}

/**
 * @brief Creates a dummy log file for demonstration purposes if it doesn't exist.
 *
 * This function populates a file with sample log data, making the tool
 * runnable out of the box.
 */
void create_dummy_log_file() {
    FILE *fp = fopen(LOG_FILE_NAME, "r");
    if (fp) {
        // File already exists, no need to create it.
        fclose(fp);
        return;
    }

    printf("Log file '%s' not found. Creating a dummy log file.\n", LOG_FILE_NAME);
    fp = fopen(LOG_FILE_NAME, "w");
    if (fp == NULL) {
        perror("Could not create dummy log file");
        exit(1);
    }

    fprintf(fp, "10:01:15 [INFO] - System startup sequence initiated.\n");
    fprintf(fp, "10:01:20 [INFO] - Network service successfully started on port 8080.\n");
    fprintf(fp, "10:02:30 [WARNING] - Disk space is running low (90%% used).\n");
    fprintf(fp, "10:03:05 [INFO] - User 'admin' logged in from 192.168.1.100.\n");
    fprintf(fp, "10:04:45 [ERROR] - Failed to connect to database 'prod_db' at mysql.server.com.\n");
    fprintf(fp, "10:04:46 [INFO] - Retrying database connection...\n");
    fprintf(fp, "10:05:00 [ERROR] - Database connection timed out after 3 attempts.\n");
    fprintf(fp, "10:05:15 [WARNING] - High CPU usage detected: 95%%.\n");
    fprintf(fp, "10:06:00 [INFO] - Performing scheduled backup.\n");
    fprintf(fp, "10:07:22 [INFO] - Backup completed successfully.\n");
    fprintf(fp, "10:08:00 [ERROR] - Unhandled exception: NullPointerException in module 'AuthService'.\n");
    fprintf(fp, "10:09:10 [INFO] - User 'guest' logged in.\n");
    fprintf(fp, "10:10:00 [WARNING] - Deprecated API endpoint '/v1/data' was accessed.\n");

    fclose(fp);
}