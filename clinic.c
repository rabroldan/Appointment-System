/*
*****************************************************************************
                       
Full Name  : Ronald Roldan

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"
#include "string.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.minutes,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments,data->patients);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments,
                data->patients);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {

        if (patient[i].patientNumber != '\0')
        {
            displayPatientData(&patient[i], FMT_TABLE);

        }

    }
    printf("\n");
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int select;
    char space = 'x';



    do
    {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................");
        printf("\n");
        printf("Selection: ");
        scanf("%d%c", &select, &space);

        if (select == 1)
        {
            searchPatientByPatientNumber(patient, max);
            clearInputBuffer();
            suspend();
        }
        else if (select == 2)
        {
            searchPatientByPhoneNumber(patient, max);
            clearInputBuffer();
            suspend();
        }
    } while (select != 0);


    printf("\n");

}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i, count = 0;

    int numbersdone = 0;


    for (i = 0; i < max; i++)
    {

        if (patient[i].patientNumber != 0)
        {
            count++;

        }
        if (patient[i].patientNumber == 0)
        {

            numbersdone = nextPatientNumber(&patient[i], max);

            patient[i].patientNumber = numbersdone;


            inputPatient(&patient[i]);
            clearInputBuffer();
            printf("*** New patient record added ***\n\n");

            break;

        }

        else if (count == max)
        {

            printf("ERROR: Patient listing is FULL!");
            printf("\n\n");


        }
    }




}



// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientnum;
    int i = 0;
    char spaces = 'x';

    printf("Enter the patient number: ");
    scanf("%d%c", &patientnum, &spaces);
    printf("\n");
    findPatientIndexByPatientNum(patientnum, patient, max);
    if (patientnum == -1)
    {
        printf("\n");
        printf("ERROR: Patient record not found!");


    }

    else
    {
        for (i = 0; i < max; i++)
        {
            if (patientnum == patient[i].patientNumber)
            {
                menuPatientEdit(&patient[i]);

                break;
            }

        }

    }

}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientnum, number;
    int i = 0;
    char space = 'x';
    char yesornow = 'x';

    printf("Enter the patient number: ");
    scanf("%d%c", &patientnum, &space);
    number = findPatientIndexByPatientNum(patientnum, patient, max);
    if (number == -1)
    {
        printf("\n");
        printf("ERROR: Patient record not found!");
        printf("\n\n");

    }

    else
    {
        for (i = 0; i < max; i++)
        {

            if (patientnum == patient[i].patientNumber)
            {
                printf("\n");
                displayPatientData(&patient[i], FMT_FORM);
                printf("\n");
                printf("Are you sure you want to remove this patient record? (y/n): ");

                do
                {
                    yesornow = inputCharOption("yn");



                    if (yesornow == 'y')
                    {

                        patient[i].patientNumber = '\0';
                        printf("Patient record has been removed!");
                        printf("\n");
                        printf("\n");
                        break;

                    }
                    else if (yesornow == 'n')
                    {
                        printf("Operation aborted.");
                        printf("\n");
                        printf("\n");
                        break;
                    }


                } while (yesornow != 'y' || yesornow != 'n');
            }

        }




    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:


void viewAllAppointments(struct ClinicData* data)
{
    int i, j;
    int isAllRecords = 1;


    displayScheduleTableHeader(&data->appointments->date, isAllRecords);
    putchar('\n');

    sortingappointments(data);

    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++)
        {
            if (data->appointments[i].date.year != '\0')
            {
                if (data->appointments[i].patients.patientNumber != '\0' && data->patients[j].patientNumber != '\0')
                {
                    if (data->appointments[i].patients.patientNumber == data->patients[j].patientNumber)
                    {
                        displayScheduleData(&data->patients[j], &data->appointments[i], 1);
                        break;
                    }
                }
            }
            else
            {
                ;
            }
        }
    }




    printf("\n");
}

// View appointment schedule for the user input date
// Todo: 
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i;
    int j = 0;
   
    int years, months, days;

    
    printf("Year        : ");
    years = inputInt();

    printf("Month (1-12): ");
    months = inputIntRange(1, 12);

    if (months == 2)
    {
        if (((years % 4 == 0) && ((years % 400 == 0) || (years % 100 != 0))))
        {
            printf("Day (1-29)  : ");
            days = inputIntRange(1, 29);

        }
        else
        {
            printf("Day (1-28)  : ");
            days = inputIntRange(1, 28);
        }
    }
    else if (months % 2 == 0)
    {
        printf("Day (1-30)  : ");
        days = inputIntRange(1, 30);
    }
    else
    {
        printf("Day (1-31)  : ");
        days = inputIntRange(1, 31);
    }

                sortingappointments(data);

                putchar('\n');
                displayScheduleTableHeader(&data->appointments->date, 0);

                for (j = 0; j <= MAX_APPOINTMENTS; j++)
                {

                    if (data->appointments[j].date.year == years)
                    {

                        if (data->appointments[j].date.month == months)
                        {
                            if (data->appointments[j].date.day == days)
                            {
                                for (i = 0; i < data->maxAppointments; i++)
                                {
                                    
                                        
                                        if (data->appointments[j].patients.patientNumber == data->patients[i].patientNumber)
                                        {
                                            displayScheduleData(&data->patients[i], &data->appointments[j], 0);
                                            break;
                                        }
                                    
                                }
                                
                                            
                            }


                        }

                    }

                }

       
        putchar('\n');

        putchar('\n');


}


// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointments[], struct Patient* patients[])
{
    int i, j;
    int patientnum = 0, years, months, days, hours, minutes;
    int time = 0, notavailable = 0, error = 1;

    printf("Patient Number: ");
    scanf("%d", &patientnum);

    if (findPatientIndexByPatientNum(patientnum, patients, MAX_APPOINTMENTS) != -1)
    {
        findPatientIndexByPatientNum(patientnum, patients, MAX_APPOINTMENTS);


        do
        {
            if (time == 0)
            {
                printf("Year        : ");
                scanf("%d", &years);

                printf("Month (1-12): ");
                scanf("%d", &months);

                if (months == 2)
                {
                    if (((years % 4 == 0) && ((years % 400 == 0) || (years % 100 != 0))))
                    {
                        printf("Day (1-29)  : ");
                        days = inputIntRange(1, 29);

                    }
                    else
                    {
                        printf("Day (1-28)  : ");
                        days = inputIntRange(1, 28);
                    }
                }
                else if (months % 2 == 0)
                {
                    printf("Day (1-30)  : ");
                    days = inputIntRange(1, 30);
                }
                else
                {
                    printf("Day (1-31)  : ");
                    days = inputIntRange(1, 31);
                }

            }

            do
            {
                printf("Hour (0-23)  : ");
                hours = inputIntRange(0, 23);

                printf("Minute (0-59): ");
                minutes = inputIntRange(0, 59);

                
                for (j = 0; j <= MAX_APPOINTMENTS; j++)
                {

                    if (appointments[j]->date.year == years)
                    {

                        if (appointments[j]->date.month == months)
                        {
                            if (appointments[j]->date.day == days)
                            {
                                if (appointments[j]->time.hour == hours)
                                {
                                    if (appointments[j]->time.minutes == minutes)
                                    {
                                        notavailable = 1;
                                        error = 1;
                                    }
                                }
                            }


                        }

                    }

                }

                if (notavailable == 1)
                {
                    printf("\nERROR: Appointment timeslot is not available!\n\n");
                    notavailable = 0;
                    error = 1;
                }
                else if ((hours < opening || hours > closing || (hours == closing && minutes >! 0) || (minutes != 0 && minutes != 30)))
                {
                    printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n");
                    time = 1;
                    error = 1;
                }

                else
                {
                  
                    error = 0;
                }

            } while (error != 0);


        } while (error != 0);

        for (i = 0; i < MAX_APPOINTMENTS; i++)
        {

            
            if (appointments[i]->date.year == 0)
            {
                
                appointments[i]->patients.patientNumber = patientnum;
                appointments[i]->date.year = years;
                appointments[i]->date.month = months;
                appointments[i]->date.day = days;
                appointments[i]->time.hour = hours;
                appointments[i]->time.minutes = minutes;

                printf("*** Appointment scheduled! ***\n");

                break;

            }

        }




    }
    
 
    
    putchar('\n');
}


// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointments[], struct Patient* patients[])
{
    int number;

    char space = 'x';
    char yesornow = 'x';
    int i = 0;
    int j = 0, k = 0;
    int patientnum = 0, years, months, days;
    int error = 1;


    printf("Patient Number:: ");
    scanf("%d%c", &patientnum, &space);

    number = findPatientIndexByPatientNum(patientnum, patients, MAX_APPOINTMENTS);

    if (number == -1)
    {
        printf("\n");
        printf("ERROR: Patient record not found!");
        printf("\n\n");

    }

    else
    {
        printf("Year        : ");
        years = inputInt();

        printf("Month (1-12): ");
        months = inputIntRange(1, 12);

        if (months == 2)
        {
            if (((years % 4 == 0) && ((years % 400 == 0) || (years % 100 != 0))))
            {
                printf("Day (1-29)  : ");
                days = inputIntRange(1, 29);

            }
            else
            {
                printf("Day (1-28)  : ");
                days = inputIntRange(1, 28);
            }
        }
        else if (months % 2 == 0)
        {
            printf("Day (1-30)  : ");
            days = inputIntRange(1, 30);
        }
        else
        {
            printf("Day (1-31)  : ");
            days = inputIntRange(1, 31);
        }
        do
        {
            if (patientnum == &patients[i]->patientNumber)
            {

                for (j = 0; j <= MAX_APPOINTMENTS; j++)
                {

                    if (&appointments[j]->date.year == years)
                    {

                        if (&appointments[j]->date.month == months)
                        {
                            if (&appointments[j]->date.day == days)
                            {
                                putchar('\n');
                                printf("\n");
                                displayPatientData(&patients[i], FMT_FORM);
                                printf("\n");
                                printf("Are you sure you want to remove this appointment (y,n): ");

                                do
                                {
                                    yesornow = inputCharOption("yn");



                                    if (yesornow == 'y')
                                    {
                                        for (k = 0; k < MAX_APPOINTMENTS; k++)
                                        {


                                            if (patientnum == appointments[k]->patients.patientNumber && days == appointments[k]->date.day && months == appointments[k]->date.month && years == appointments[k]->date.year)
                                            {

                                                appointments[k]->patients.patientNumber = '\0';
                                                appointments[k]->date.year = '\0';
                                                appointments[k]->date.month = '\0';
                                                appointments[k]->date.day = '\0';
                                                appointments[k]->time.hour = '\0';
                                                appointments[k]->time.minutes = '\0';

                                                break;

                                            }

                                        }

                                        printf("\n");
                                        printf("Appointment record has been removed!");
                                        printf("\n");
                                        printf("\n");
                                        error = 0;
                                        break;
                                    }
                                    else if (yesornow == 'n')
                                    {
                                        printf("Operation aborted.");
                                        printf("\n");
                                        printf("\n");
                                        break;
                                    }


                                } while (yesornow != 'y' || yesornow != 'n');


                            }

                        }

                    }
                    if (error == 0)
                    {
                        break;
                    }
                }
             
            }
            i++;
        } while (error != 0);

    }
 
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientnumber;
    int i = 0;
    int store;


    printf("\n");
    printf("Search by patient number: ");
    scanf(" %d", &patientnumber);

    printf("\n");






    if (findPatientIndexByPatientNum(patientnumber, patient, max) != -1)
    {
        store = findPatientIndexByPatientNum(patientnumber, patient, max);

        printf("Name  : %s\n", patient[store].name);
        printf("Number: %05d\n", patient[store].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(patient[store].phone.number);
        printf(" (%s)", patient[store].phone.description);
        printf("\n\n");

        i = 1;
    }
    else if (findPatientIndexByPatientNum(patientnumber, patient, max) == -1 && i == 0)
    {

        printf("*** No records found ***\n\n");

    }




}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char numbers[PHONE_LEN + 1];
    int i, x = 0;
    printf("\n");
    printf("Search by phone number: ");
    scanf(" %s", numbers);
    printf("\n");



    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if ((strcmp(patient[i].phone.number, numbers) == 0))
        {
            x = 1;

            printf("%05d %-15s ", patient[i].patientNumber, patient[i].name);
            displayFormattedPhone(patient[i].phone.number);

            printf(" (%s)\n", patient[i].phone.description);


        }

    }
    printf("\n");
    if (x == 0)
    {

        printf("*** No records found ***\n\n");


    }



}


// Get the next highest patient number
int nextPatientNumber(struct Patient patient[], int max)
{
    int i, x = 0;
    int new_number;


    do
    {
        for (i = 0; i < max; i++)
        {
            if (x == 2)
            {
                //
            }

            else if (x == 0)
            {
                if (patient[i].patientNumber == 0)
                {
                    new_number = patient[i - 1].patientNumber + 1;
                    x = 2;
                }
            }
        }
    } while (x == 0);
    return new_number;

}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i, index_return = 0;
    int z = 0;




    for (i = 0; i < max; i++)
    {

        if (patientNumber == patient[i].patientNumber) // find how to scan throu gh i array
        {
            index_return = i;
            z = 1;

        }
    }
    if (z == 0)
    {


        index_return = -1;

    }




    return index_return;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    int x = 0;

    printf("Patient Data Input\n"
        "------------------\n");
    printf("Number: %05d", patient->patientNumber);
    printf("\n");
    printf("Name  : ");
    inputCString(patient[x].name, 10, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone); // fix

}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int x = 0;
    int selecter;




    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");

    selecter = inputIntRange(1, 4);

    if (selecter == 3)

    {

        printf("\n");
        strcpy(phone->description, "WORK");
        x = 1;


    }
    else if (selecter == 1)
    {
        printf("\n");
        strcpy(phone->description, "CELL");
        x = 1;
    }
    else if (selecter == 2)
    {
        printf("\n");
        strcpy(phone->description, "HOME");
        x = 1;

    }
    else if (selecter == 4)
    {

        strcpy(phone->description, "TBD");


    }

    if (x == 1)
    {
        printf("Contact: %s", phone->description);
        printf("\n");
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        printf("\n");

    }
    else
    {
        ;
    }





}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{



    char ch;
    int i = 0;


    FILE* fp = fopen(datafile, "r");

    if (fp != NULL)
    {


        while (fscanf(fp, "%d|%[^|]|%4[^|]|%10[^\n]%c", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number, &ch) >0)
        {
            if (ch != '\n')
            {
                while (fgetc(fp) != '\n');

            }
            i++;

            if (i >= MAX_PETS)
            {
                break;
            }
        }
       

    }
    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{

    int i = 0;

    FILE* fp = fopen(datafile, "r");

    if (fp != NULL)
    {

        while (fscanf(fp, "%d,%04d,%02d,%02d,%02d,%d\n", &appoints[i].patients.patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.minutes) > 0)
        {

            i++;
            if (i >= MAX_PETS)
            {
                break;
            }
        }



        fclose(fp);


    }
    return i;
}

void sortingappointments(struct ClinicData* data)
{
    int i, j;
    
    struct Appointment temp;

    for (i = 1; i < MAX_PETS; i++)
    {

        for (j = 0; j < MAX_PETS - 1; j++)
        {

            if (data->appointments[j].date.year > data->appointments[j + 1].date.year)
            {

                temp = data->appointments[j];
                data->appointments[j] = data->appointments[j + 1];
                data->appointments[j + 1] = temp;
            }
            else if (data->appointments[j].date.year == data->appointments[j + 1].date.year && data->appointments[j].date.month > data->appointments[j + 1].date.month)
            {

                temp = data->appointments[j];
                data->appointments[j] = data->appointments[j + 1];
                data->appointments[j + 1] = temp;
            }
            else if (data->appointments[j].date.year == data->appointments[j + 1].date.year && data->appointments[j].date.month == data->appointments[j + 1].date.month && data->appointments[j].date.day > data->appointments[j + 1].date.day)
            {
                temp = data->appointments[j];
                data->appointments[j] = data->appointments[j + 1];
                data->appointments[j + 1] = temp;
            }
            else if (data->appointments[j].date.year == data->appointments[j + 1].date.year && data->appointments[j].date.month == data->appointments[j + 1].date.month && data->appointments[j].date.day == data->appointments[j + 1].date.day && data->appointments[j].time.hour > data->appointments[j + 1].time.hour)
            {
                temp = data->appointments[j];
                data->appointments[j] = data->appointments[j + 1];
                data->appointments[j + 1] = temp;
            }
            else if (data->appointments[j].date.year == data->appointments[j + 1].date.year && data->appointments[j].date.month == data->appointments[j + 1].date.month && data->appointments[j].date.day == data->appointments[j + 1].date.day && data->appointments[j].time.hour == data->appointments[j + 1].time.hour && data->appointments[j].time.minutes > data->appointments[j + 1].time.minutes)

            {
                temp = data->appointments[j];
                data->appointments[j] = data->appointments[j + 1];
                data->appointments[j + 1] = temp;
            }

        }
    }
}


/*      while(fscanf(fp, "%4d,%4d,%1d,%2d,%2d,%2d,%c", appoints[i].patients.patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.minutes, &ch) != -1)


               fscanf(fp, "%d|%[^\n]%*c|%10[^\n]|%4[^\n]|%c", &patients[i].patientNumber, &patients[i].name, &patients[i].phone.description, &patients[i].phone.number, &ch);

               for (i = 0; i <= MAX_APPOINTMENTS; i++)
    {

        if (data->patients[i].patientNumber == '\0')
        {
            printf("Year        : ");
            data->appointments[i].date.year = inputInt();

            printf("Month (1-12): ");
            data->appointments[i].date.month = inputIntRange(1, 12);

            if (data->appointments[i].date.month == 2)
            {
                if (((data->appointments[i].date.year % 4 == 0) && ((data->appointments[i].date.year % 400 == 0) || (data->appointments[i].date.year % 100 != 0))))
                {
                    printf("Day (1-29)  : ");
                    data->appointments[i].date.day = inputIntRange(1, 29);
                }
                else
                {
                    printf("Day (1-28)  : ");
                    data->appointments[i].date.day = inputIntRange(1, 28);
                }
            }
            else if (data->appointments[i].date.month % 2 == 0)
            {
                printf("Day (1-30)  : ");
                data->appointments[i].date.day = inputIntRange(1, 30);
            }
            else
            {
                printf("Day (1-31)  : ");
                data->appointments[i].date.day = inputIntRange(1, 31);
            }
            putchar('\n');

            number = i;

            displayScheduleTableHeader(&data->appointments[number].date, 0);

            for (i = 0; i <= MAX_APPOINTMENTS; i++)
            {
                if (data->appointments[number].date.year == data->appointments[i].date.year)
                {

                    if (data->appointments[number].date.month == data->appointments[i].date.month)
                    {
                        if (data->appointments[number].date.day == data->appointments[i].date.day)
                        {


                            displayScheduleData(&data->patients[number], &data->appointments[number], 0);

                            break;
                            x = 2;
                        }


                    }

                }
                if (x == 2)
                {
                    break;
                }
            }
            break;
        }


    }

    how to connect patient and appointment data so that in the output it will correct everything
    date
    remove patiens
    Outputs not working
    needs to debug everything
    almost all is working

*/
