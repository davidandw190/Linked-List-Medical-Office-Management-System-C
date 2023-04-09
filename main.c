//
// Created by 40787 on 4/9/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


#define MAX_NAME_LENGTH 50
#define MAX_DIAGNOSIS_LENGTH 250
#define MAX_TAG_LENGTH 20
#define MAX_HISTORY_LENGTH 500
#define MAX_USERNAME_LENGTH 25
#define MAX_PASSWORD_LENGTH 25
#define FILE_NAME "patients.txt"
#define CREDENTIALS_FILE "credentials.txt"



// Defines the patient struct
typedef struct patient {
    char name[MAX_NAME_LENGTH];
    char diagnosis[MAX_DIAGNOSIS_LENGTH];
    char tag[MAX_TAG_LENGTH];
    char history[MAX_HISTORY_LENGTH];
    char appointment_date[30];
    char appointment_time[30];
    struct patient* next;
} Patient;

typedef struct user {
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
    Patient* patient_list;
    struct user* next;
} User;



void println(){
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
}
void println_equal(){
    printf("=======================================================================================================================\n");
}

// Dispalys a personalised header for each menu
void display_header(const char title[]){

    int title_len = strlen(title);
    int total_len = 118;
    int padding = (total_len - title_len) / 2;
    system("cls");
    println_equal();
    printf("|                                                  MY MEDICAL OFFICE                                                  |\n");
    println_equal();
    printf("|%*s%s%*s|\n", padding, "", title, padding, "");
    println();
}




// Reads the patient data from a file
Patient* read_data(void) {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Could not open file %s\n", FILE_NAME);
        getchar();
        return NULL;
    }
    Patient* head = NULL;
    Patient* current = NULL;
    char line[1000];
    while (fgets(line, sizeof(line), file)) {
        Patient* node = malloc(sizeof(Patient));
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],\n", node->name, node->diagnosis, node->tag, node->history, node->appointment_date, node->appointment_time);
        node->next = NULL;
        if (!head) {
            head = node;
        } else {
            current->next = node;
        }
        current = node;
    }
    fclose(file);
    return head;
}

// Writes the patient data to a file
void write_data(Patient* head) {
    FILE* file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("\nCould not open file %s!\n", FILE_NAME);
        getchar();
        return;
    }
    for (Patient* current = head; current; current = current->next) {
        fprintf(file, "%s,%s,%s,%s,%s,%s\n", current->name, current->diagnosis, current->tag, current->history, current->appointment_date, current->appointment_time);
    }
    fclose(file);
    getchar();
    printf("\nPatient data saved to %s!\n", FILE_NAME);
    getchar();
}





void display_patient(Patient* current) {
    // Display patient information in a table
    println_equal();
    printf("\n|| Current information for patient '%s':  ||\n", current->name);
    println();
    printf("|| 1. | Diagnosis       | %s\n", current->diagnosis);
    printf("|| 2. | Tag             | %s\n", current->tag);
    printf("|| 3. | Medical history | %s\n", current->history);
    printf("|| 4. | Appointment     | %s at %s\n", current->appointment_date, current->appointment_time);
    println();
    printf("\n");
}

//User* login(User* head) {
//    display_header("LOGIN");
//
//    char username[MAX_NAME_LENGTH], password[MAX_NAME_LENGTH];
//
//    printf("Enter username: ");
//    scanf("%s", username);
//    printf("Enter password: ");
//    scanf("%s", password);
//
//    for (User* current = head; current; current = current->next) {
//        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
//            return current;
//        }
//    }
//
//    printf("\nInvalid username or password. Please try again.\n");
//    getchar();
//    return NULL;
//}


// Deletes a patient by name
void delete_patient(Patient** head_ref) {
    display_header("DELETE PATIENT");

    char name[MAX_NAME_LENGTH];
    printf("Enter name of patient to delete: ");
    scanf("%s", name);
    Patient* current = *head_ref;
    Patient* previous = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("Are you sure you want to delete patient %s? (y/n)", name);
            char choice;
            scanf(" %c", &choice);
            if (choice == 'y') {
                if (previous) {
                    previous->next = current->next;
                } else {
                    *head_ref = current->next;
                }
                printf("Patient %s deleted successfully!\n", name);
                getchar();
                free(current);
            } else {
                printf("Patient %s was not deleted.\n", name);
            }
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Patient %s not found!\n", name);
    getchar();
    getchar();
}


// Searches for a patient by name
void search_patient(Patient* head) {
    display_header("SEARCH PATIENT");
    char name[MAX_NAME_LENGTH];
    getchar();
    printf("Enter name of patient to search for: ");
    scanf("%s", name);
    getchar();
    bool found = false;
    for (Patient* current = head; current; current = current->next) {
        if (strcmp(current->name, name) == 0) {
            printf("Name: %s\n", current->name);
            printf("Diagnosis: %s\n", current->diagnosis);
            printf("Tag: %s\n", current->tag);
            printf("Medical History: %s\n", current->history);
            printf("Appointment Date: %s\n", current->appointment_date);
            printf("Appointment Time: %s\n", current->appointment_time);
            found = true;
            break;
        }
    }
    if (!found) {
        printf("Patient %s not found\n", name);
        getchar();
        getchar();
    }
}

// Generates a report of the patients in the system   !!PLACEHOLDER
void report_status(Patient* head) {
    display_header("PATIENT REPORT");
    for (Patient* current = head; current; current = current->next) {
        printf("Name: %s\n", current->name);
        printf("Diagnosis: %s\n", current->diagnosis);
        printf("Tag: %s\n", current->tag);
        printf("Medical History: %s\n", current->history);
        printf("Appointment Date: %s\n", current->appointment_date);
        printf("Appointment Time: %s\n", current->appointment_time);
        println();
    }

    getchar();
    getchar();
}

void display_all_patients(Patient* head) {
    int counter = 1;

    display_header("PATIENTS");

    if (head == NULL) {
        printf("No patients found.\n\n");
        getchar();
        getchar();
        return;
    }

    printf("| %-4s | %-25s | %-15s | %-17s | %-23s | %-15s |\n",
           "ID", "NAME", "TAG", "DIAGNOSIS", "APPOINTMENT DATE", "APPOINTMENT TIME");
    println();

    Patient* current = head;
    while (current != NULL) {

        printf("| %-4d | %-25s | %-15s | %-17s | %-23s | %-15s |\n",
               counter, current->name, current->tag, current->diagnosis,
               current->appointment_date, current->appointment_time);

        println();
        printf("| %-114s |\n", "MEDICAL HISTORY:");
        printf("| %-114s |\n", current->history);
        println();

        current = current->next;
        counter++;
    }

    printf("\nPress Enter to return to the main menu.");
    getchar();
    getchar();
    while (getchar() != '\n');
}

void display_todays_patients(Patient* head) {
    // Get today's date and time
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char today[30];
    char current_time[10];
    strftime(current_time, sizeof(current_time), "%I:%M %p", tm);
    snprintf(today, sizeof(today), "%02d-%02d-%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);

    if (head == NULL) {
        printf("No patients found. You are free today!!\n\n");
        getchar();
        getchar();
        return;
    }

    // Create a new linked list to store the patients of today's date
    Patient *today_patients = NULL;

    // Iterate over the linked list of patients
    for (Patient *current = head; current != NULL; current = current->next) {
        // Check if the appointment date matches today's date
        if (strcmp(current->appointment_date, today) == 0) {
            // Adds the patient to the new linked list
            Patient *new_patient = malloc(sizeof(Patient));
            if (new_patient == NULL) {
                printf("Error: Memory allocation failed.");
                exit(EXIT_FAILURE);
            }
            *new_patient = *current;
            new_patient->next = today_patients;
            today_patients = new_patient;
        }
    }

    // Sort the linked list of patients by appointment hour
    for (Patient *i = today_patients; i != NULL; i = i->next) {
        for (Patient *j = i->next; j != NULL; j = j->next) {
            int hour_i = atoi(strtok(i->appointment_time, ":"));
            int hour_j = atoi(strtok(j->appointment_time, ":"));
            if (hour_j < hour_i) {
                // Swap the patients
                Patient temp = *i;
                *i = *j;
                *j = temp;
            }
        }
    }

    // Display the sorted list of patients
    printf("CURRENT DATE: %s\n", today);
    printf("CURRENT TIME: %s\n", current_time);
    display_header("TODAY'S PATIENTS");
    printf("| %-20s | %-4s | %-25s | %-15s | %-17s |\n",
           "APPOINTMENT TIME", "ID", "NAME", "TAG", "DIAGNOSIS" );
    println();
    int counter = 1;
    for (Patient *current = today_patients; current != NULL; current = current->next) {
        printf("| %-20s | %-4d | %-25s | %-15s | %-17s |\n",
               current->appointment_time, counter, current->name, current->tag, current->diagnosis );
        println();
        printf("| %-114s |\n", "MEDICAL HISTORY:");
        printf("| %-114s |\n", current->history);
        println();
        counter++;
    }
    getchar();
    printf("\nPress any key to return to the main menu.");
    getchar();


    // Free the memory used by the new linked list of patients
    while (today_patients != NULL) {
        Patient *temp = today_patients;
        today_patients = today_patients->next;
        free(temp);
    }
}


// Validates the patient appointment date from the user
bool validate_date(char* date) {

    // Check date format (DD-MM-YYYY)
    if (strlen(date) != 10 || date[2] != '-' || date[5] != '-') {
        printf("Invalid date format. Please use the format DD-MM-YYYY.\n");
        return false;
    }

    // Check day
    int day = atoi(date);
    if (day < 1 || day > 31) {
        printf("Invalid day. Please enter a day between 1 and 31.\n");
        return false;
    }

    // Check month
    int month = atoi(date + 3);
    if (month < 1 || month > 12) {
        printf(" Invalid month. Please enter a month between 1 and 12.\n");
        return false;
    }

    // Check year
    int year = atoi(date + 6);
    if (year < 1900 || year > 9999) {
        printf(" Invalid year. Please enter a year between 1900 and 9999.\n");
        return false;
    }

    return true;
}


// Validates the patient appointment time from the user
bool validate_time(char* time) {

    // Check time format (HH:MM)
    if (strlen(time) != 5 || time[2] != ':') {
        printf(" Invalid time format. Please use the format HH:MM.\n");
        return false;
    }

    // Check hours
    int hours = atoi(time);
    if (hours < 0 || hours > 23) {
        printf("Invalid hour. Please enter an hour between 0 and 23.\n");
        return false;
    }

    // Check minutes
    int minutes = atoi(time + 3);
    if (minutes < 0 || minutes > 59) {
        printf("Invalid minute. Please enter a minute between 0 and 59.\n");
        return false;
    }

    return true;
}

// Authentication for the user  !!PLACEHOLDER
bool authenticate() {
    display_header("LOGIN");

    char username[20], password[20];

    printf("\n|| Enter your username: ");
    scanf("%s", username);
    printf("|| Enter your password: ");
    scanf("%s", password);

    if (strcmp(username, "david") == 0 && strcmp(password, "123") == 0) {
        return true;
    } else {
        return false;
    }
}

// Authentication for the user
//bool authenticate(User* users, int num_users) {
//    display_header("LOGIN");
//
//    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
//
//    printf("\nEnter username: ");
//    scanf("%s", username);
//    printf("Enter password: ");
//    scanf("%s", password);
//
//    for (int i = 0; i < num_users; i++) {
//        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
//            return true;
//        }
//    }
//    return false;
//}


//// Creates a new user account
//void create_user(User** users, int* num_users) {
//    display_header("NEW USER");
//
//    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
//
//    printf("Enter new username: ");
//    scanf("%s", username);
//
//    // Check if username already exists
//    for (int i = 0; i < *num_users; i++) {
//        if (strcmp(username, (*users)[i].username) == 0) {
//            printf("Username already exists. Please choose another one.\n");
//            getchar();
//            getchar();
//            return;
//        }
//    }
//
//    printf("Enter new password: ");
//    scanf("%s", password);
//
//    // Reallocate memory for the users array
//    *users = realloc(*users, (*num_users + 1) * sizeof(User));
//
//    // Add new user to the end of the array
//    User* new_user = &(*users)[*num_users];
//    strncpy(new_user->username, username, MAX_USERNAME_LENGTH);
//    strncpy(new_user->password, password, MAX_PASSWORD_LENGTH);
//
//    (*num_users)++;
//    printf("\nUser account created successfully!\n");
//    getchar();
//    getchar();
//}
//
//User* read_users(void) {
//    FILE* file = fopen("users.txt", "r");
//    if (!file) {
//        printf("Could not open file users.txt\n");
//        return NULL;
//    }
//    User* head = NULL;
//    User* current = NULL;
//    char line[1000];
//    while (fgets(line, sizeof(line), file)) {
//        User* node = malloc(sizeof(User));
//        sscanf(line, "%[^,],%[^,],\n", node->username, node->password);
//        node->patient_list = read_data();
//        node->next = NULL;
//        if (!head) {
//            head = node;
//        } else {
//            current->next = node;
//        }
//        current = node;
//    }
//    fclose(file);
//    return head;
//}
//
//void write_users(User* head) {
//
//    FILE* file = fopen("users.txt", "w");
//
//    if (!file) {
//        printf("Could not open file users.txt\n");
//        return;
//    }
//
//    for (User* current = head; current; current = current->next) {
//        fprintf(file, "%s,%s,\n", current->username, current->password);
//        write_data(current->patient_list);
//    }
//    fclose(file);
//    printf("User data saved to users.txt\n");
//}

// Searches for and edits a pacient
void edit_patient(Patient** head_ref) {
    display_header("EDIT PATIENT");

    char new_date[20];
    char new_time[20];
    char name[MAX_NAME_LENGTH];
    printf("\nEnter name of patient to edit: ");
    scanf("%s", name);

    Patient *current = *head_ref;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            // Display patient information in a table
            display_header("EDITING PATIENT");
            printf("\nCurrent information for patient '%s':\n", name);
            println();
            printf("|| 1. | Diagnosis       | %s\n", current->diagnosis);
            printf("|| 2. | Tag             | %s\n", current->tag);
            printf("|| 3. | Medical history | %s\n", current->history);
            printf("|| 4. | Appointment     | %s at %s\n", current->appointment_date, current->appointment_time);
            println();
            // Ask the user which field to edit
            printf("\nEnter the row number of the field you wish to edit (1-4): ");
            int row;
            scanf("%d", &row);

            // Ask the user for the new value of the selected field
            char new_value[2000];
            printf("Enter the new value for this field: ");
            scanf("%s", new_value);

            // Update the selected field
            switch (row) {
                case 1:
                    strcpy(current->diagnosis, new_value);
                    break;
                case 2:
                    strcpy(current->tag, new_value);
                    break;
                case 3:
                    strcpy(current->history, new_value);
                    break;
                case 4:
                    // Ask the user for the new appointment date and time separately

                    printf("\nEnter the new appointment date (DD-MM-YYYY): ");
                    scanf("%s", new_date);
                    if (!validate_date(new_date)) {
                        printf("\nInvalid date format.\n");
                        getchar();
                        getchar();
                        return;
                    }
                    printf("\nEnter the new appointment time (HH:MM): ");
                    scanf("%s", new_time);
                    if (!validate_time(new_time)) {
                        printf("Invalid time format.\n");
                        getchar();
                        getchar();
                        return;
                    }
                    strcpy(current->appointment_date, new_date);
                    strcpy(current->appointment_time, new_time);
                    break;
                default:
                    printf("Invalid row number.\n");
                    break;
            }

            system("cls");
            display_header("PATIENT EDITED SUCCESSFULLY!");
            printf("\nPatient '%s' has been updated:\n", name);
            println();
            printf("|| 1. | Diagnosis       | %s\n", current->diagnosis);
            printf("|| 2. | Tag             | %s\n", current->tag);
            printf("|| 3. | Medical history | %s\n", current->history);
            printf("|| 4. | Appointment     | %s at %s\n", current->appointment_date, current->appointment_time);
            println();
            getchar();
            printf("\nPress any key to continue..");
            getchar();
            return;
        }
        current = current->next;
    }

    // Patient not found
    printf("\nPatient '%s' not found\n", name);
    getchar();
    printf("\nPress any key to continue..");

    getchar();
}


// Swaps two patients
void swap_patients(Patient* a, Patient* b) {
    char temp_name[MAX_NAME_LENGTH];
    char temp_date[50];
    char temp_time[50];
    int temp_age;

    strcpy(temp_name, a->name);
    strcpy(temp_date, a->appointment_date);
    strcpy(temp_time, a->appointment_time);


    strcpy(a->name, b->name);
    strcpy(a->appointment_date, b->appointment_date);
    strcpy(a->appointment_time, b->appointment_time);


    strcpy(b->name, temp_name);
    strcpy(b->appointment_date, temp_date);
    strcpy(b->appointment_time, temp_time);
}


//// Sorts patients by appointment date and time
//void sort_patients(Patient** head_ref) {
//    int swapped;
//    Patient* ptr1;
//    Patient* lptr = NULL;
//
//    /* Checking for empty list */
//    if (*head_ref == NULL) {
//        return;
//    }
//
//    do {
//        swapped = 0;
//        ptr1 = *head_ref;
//
//        while (ptr1->next != lptr) {
//            if (strcmp(ptr1->appointment_date, ptr1->next->appointment_date) > 0
//            || (strcmp(ptr1->appointment_date, ptr1->next->appointment_date) == 0
//            && strcmp(ptr1->appointment_time, ptr1->next->appointment_time) > 0)) {
//                swap_patients(ptr1, ptr1->next);
//                swapped = 1;
//            }
//            ptr1 = ptr1->next;
//        }
//        lptr = ptr1;
//    } while (swapped);
//
//    display_all_patients(*head_ref);
//}

void add_patient(Patient** head_ref) {
    display_header("NEW PATIENT");

    char appointment_date[50];
    char appointment_time[50];
    char *pdate = appointment_date;
    char *ptime = appointment_time;

    do {
        printf("Enter appointment date (DD-MM-YYYY): ");
        scanf("%s", appointment_date);
    } while (!validate_date(pdate));

    do {
        printf("Enter appointment time (HH:MM): ");
        scanf("%s", appointment_time);
    } while (!validate_time(ptime));

    // Create a new patient and add it to the list
    Patient* new_patient = (Patient*)malloc(sizeof(Patient));
    printf("\nEnter patient name: ");
    scanf("%s", new_patient->name);
    printf("Enter diagnosis: ");
    scanf("%s", new_patient->diagnosis);
    printf("Enter tag: ");
    scanf("%s", new_patient->tag);
    printf("Enter medical history: ");
    scanf("%s", new_patient->history);
    strcpy(new_patient->appointment_date, appointment_date);
    strcpy(new_patient->appointment_time, appointment_time);
    new_patient->next = *head_ref;
    *head_ref = new_patient;
    getchar();

    display_header("PREVIEW OF THE PACIENT");
    printf("\n|| Name: %s ||\n", new_patient->name);
    println();
    printf("|| 1. | Diagnosis       | %s\n", new_patient->diagnosis);
    printf("|| 2. | Tag             | %s\n", new_patient->tag);
    printf("|| 3. | Medical history | %s\n", new_patient->history);
    printf("|| 4. | Appointment     | %s at %s\n", new_patient->appointment_date, new_patient->appointment_time);
    println();
    printf("\n\nDo you want to add patient %s to your database?\n", new_patient->name);
    getchar();

    // Save the patient data to file
    write_data(*head_ref);

    display_header("PATIENT ADDED SUCCESSFULLY");

    printf("\nPress any key to continue..");
    getchar();
}

// Deletes all pacients but does not currently saves the new state to a file
void delete_all_patients(Patient **head) {
    Patient *current = *head;
    getchar();
    display_header("DELETE ALL PACIENTS");
    printf("\n Are you sure you want to DELETE ALL PACIENTS? The operation cannot be undone! (y/n)\n");
    char choice;
    scanf(" %c", &choice);
    if (choice == 'n') {
        return;
    }

    while (current != NULL) {
        Patient *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
    printf("All patients have been deleted.\n\n");
    getchar();
    getchar();
    while (getchar() != '\n');
}

// Displays the main menu
void main_menu(Patient* head) {
    while (true) {
        display_header("MAIN MENU");

        printf("|| 1. | Add new patient                                                                                              ||\n");
        printf("|| 2. | Edit existing patient                                                                                        ||\n");
        printf("|| 3. | Delete existing patient                                                                                      ||\n");
        printf("|| 4. | Search for patient                                                                                           ||\n");
        printf("|| 5. | Display today's pacients                                                                                     ||\n");
        printf("|| 6. | Generate patient report                                                                                      ||\n");
        printf("|| 7. | View all patients                                                                                            ||\n");
        printf("|| 8. | Delete all patients                                                                                          ||\n");
        printf("|| 9. | Exit program                                                                                                 ||\n");
        println();

        printf("\nPlease enter your choice (1-9): ");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_patient(&head);
                break;
            case 2:
                edit_patient(&head);
                break;
            case 3:
                delete_patient(&head);
                break;
            case 4:
                search_patient(head);
                break;
            case 5:
                display_todays_patients(head);
                break;
            case 6:
                report_status(head);
                break;
            case 7:
                display_all_patients(head);
                break;
            case 8:
                delete_all_patients(&head);
                break;
            case 9:
                write_data(head);
                system("cls");
                display_header("EXIT");
                printf("\n Thank you for using my Medical Office Management System! :)\n");
                getchar();
                printf("\n My name was Nan Andrei David!");
                getchar();
                return;
            default:
                system("clr");
                printf("\n  Invalid choice! \n");
                getchar();
                getchar();
                break;
        }
    }
}

//The main function, of course
int main() {
    Patient* head = read_data();
    if (!head) {
        head = malloc(sizeof(Patient));
        head->next = NULL;
    }
    bool authenticated = authenticate();
    if (!authenticated) {
        system("cls");
        printf("Invalid username or password\n");
        getchar();
        return 0;
    }

    main_menu(head);
    return 0;
}



//// Writes the patient data to a file
//void write_data(Patient* head) {
//    FILE* file = fopen(FILE_NAME, "w");
//    if (!file) {
//        printf("Could not open file %s\n", FILE_NAME);
//        getchar();
//        return;
//    }
//    for (Patient* current = head; current; current = current->next) {
//        fprintf(file, "%s,%s,%s,%s,%s,%s\n", current->name, current->diagnosis, current->tag, current->history, current->appointment_date, current->appointment_time);
//    }
//    fclose(file);
//    getchar();
//    printf("Patient data saved to %s\n", FILE_NAME);
//    getchar();
//}