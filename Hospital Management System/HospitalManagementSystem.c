#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 10
#define MAX_DEPERTMENT_LENGTH 50
#define MAX_CHAMBER 10
#define MAX_CABIN 30
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_APPOINTMENTS 100

struct User
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int userType;
};

struct Doctor
{
    char name[MAX_NAME_LENGTH];
    char doctorId[MAX_ID_LENGTH];
    char department[MAX_DEPERTMENT_LENGTH];
    char chamberNo[MAX_CHAMBER];
    struct Doctor *next;
};

struct Patient
{
    char name[MAX_NAME_LENGTH];
    char patientId[MAX_ID_LENGTH];
    char illness[MAX_DEPERTMENT_LENGTH];
    char cabinNo[MAX_CABIN];
    struct Patient *next;
    struct Appointment *appointments;
};

struct Appointment
{
    char patientId[MAX_ID_LENGTH];
    char doctorId[MAX_ID_LENGTH];
    char date[20];
    char time[20];
    struct Appointment *next;
};

void bubbleSortDoctors(struct Doctor *head);
void bubbleSortPatients(struct Patient *head);
void swapDoctors(struct Doctor *a, struct Doctor *b);
void swapPatients(struct Patient *a, struct Patient *b);

int login(struct User *users, int numUsers);
int authenticateUser(struct User *users, int numUsers, const char *username, const char *password);

struct Doctor *addDoctor(struct Doctor *head);
void viewDoctorsInfo(struct Doctor *head);
struct Doctor *searchDoctor(const struct Doctor *head, const char searchId[MAX_ID_LENGTH]);
struct Doctor *updateDoctorInfo(struct Doctor *head, char searchId[MAX_ID_LENGTH]);
struct Doctor *deleteDoctorInfo(struct Doctor *head, char searchId[MAX_ID_LENGTH]);

struct Patient *addPatient(struct Patient *head);
void viewPatientsInfo(struct Patient *head);
struct Patient *searchPatient(const struct Patient *head, const char searchId[MAX_ID_LENGTH]);
struct Patient *updatePatientInfo(struct Patient *head, char searchId[MAX_ID_LENGTH]);
struct Patient *deletePatientInfo(struct Patient *head, char searchId[MAX_ID_LENGTH]);

void viewAppointmentsByDoctor(struct Patient *patientHead, const char *doctorId);
struct Appointment *addAppointment(struct Appointment *head, const char *patientId, const char *doctorId, const char *date, const char *time);
void viewAppointments(struct Patient *patientHead, struct Doctor *doctorHead, char searchId[MAX_ID_LENGTH]);

int main()
{
    struct Doctor *doctorHead = NULL;
    struct Patient *patientHead = NULL;
    struct Appointment *appointmentHead = NULL;
    char searchId[MAX_ID_LENGTH];
    int dept;
    char doctorId[MAX_ID_LENGTH];
    char date[20];
    char time[20];

    struct User users[] = {
        {"doc1", "pass1", 1},
        {"doc2", "pass2", 1},
    };

    int numUsers = sizeof(users) / sizeof(users[0]);

    int loggedInUser = login(users, numUsers);

    if (loggedInUser != -1)
    {
        printf("Login successful!\n");

        int choice;
        do
        {
            printf("\nHOSPITAL MANAGEMENT SYSTEM\n\n");
            printf("1. Doctor Depertment\n");
            printf("2. Patient Depertment\n");
            printf("3 .Exit\n");
            printf("Enter the Depertment no: ");
            scanf("%d", &dept);

            if (dept == 1)
            {
                printf("\n1. Add New Doctor\n");
                printf("2. View All Doctors Info\n");
                printf("3. Search Doctor\n");
                printf("4. Update Doctor Info\n");
                printf("5. Delete Doctor Info\n");
                printf("6. View Doctors Appointment\n");

                printf("Enter the option: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    doctorHead = addDoctor(doctorHead);
                    bubbleSortDoctors(doctorHead);
                    break;
                case 2:
                    viewDoctorsInfo(doctorHead);
                    break;
                case 3:
                    printf("Enter doctor ID to search: ");
                    scanf("%s", searchId);
                    struct Doctor *foundDoctor = searchDoctor(doctorHead, searchId);
                    if (foundDoctor != NULL)
                    {
                        printf("\nDoctor found:\n");
                        printf("Name: %s\n", foundDoctor->name);
                        printf("ID: %s\n", foundDoctor->doctorId);
                        printf("Department: %s\n", foundDoctor->department);
                        printf("Chamber No: %s\n", foundDoctor->chamberNo);
                    }
                    else
                    {
                        printf("Invalid. No doctor found with this ID: %s", searchId);
                    }
                    break;
                case 4:
                    printf("Enter doctor ID to update informations: ");
                    scanf("%s", searchId);
                    doctorHead = updateDoctorInfo(doctorHead, searchId);
                    break;
                case 5:
                    printf("Enter doctor Id to delete: ");
                    scanf("%s", searchId);
                    doctorHead = deleteDoctorInfo(doctorHead, searchId);
                    break;
                case 6:
                    printf("Enter doctor ID to view appointments: ");
                    scanf("%s", searchId);
                    viewAppointmentsByDoctor(patientHead, searchId);
                    break;
                default:
                    printf("Invalid. Please Try Again");
                    break;
                }
            }
            else if (dept == 2)
            {
                printf("1. Add New Patient\n");
                printf("2. View All Patients Info\n");
                printf("3. Search Patient\n");
                printf("4. Update Patient Info\n");
                printf("5. Delete Patient Info\n");
                printf("6. Make an Appointment\n");
                printf("7. View appointnment \n");

                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    patientHead = addPatient(patientHead);
                    bubbleSortPatients(patientHead);
                    break;
                case 2:
                    viewPatientsInfo(patientHead);
                    break;
                case 3:
                    printf("Enter patient ID to search: ");
                    scanf("%s", searchId);
                    struct Patient *foundPatient = searchPatient(patientHead, searchId);
                    if (foundPatient != NULL)
                    {
                        printf("Patient found:\n");
                        printf("Name: %s\n", foundPatient->name);
                        printf("ID: %s\n", foundPatient->patientId);
                        printf("Illness: %s\n", foundPatient->illness);
                        printf("Cabin No: %s\n", foundPatient->cabinNo);
                    }
                    else
                    {
                        printf("No patient found with ID: %s\n", searchId);
                    }
                    break;
                case 4:
                    printf("Enter patient ID to update: ");
                    scanf("%s", searchId);
                    patientHead = updatePatientInfo(patientHead, searchId);
                    break;
                case 5:
                    printf("Enter patient ID to delete: ");
                    scanf("%s", searchId);
                    patientHead = deletePatientInfo(patientHead, searchId);
                    break;
                case 6:
                    printf("Enter patient ID for appointment: ");
                    scanf("%s", searchId);

                    struct Patient *foundPatientForAppointment = searchPatient(patientHead, searchId);
                    if (foundPatientForAppointment != NULL)
                    {
                        printf("Enter doctor ID for appointment: ");
                        scanf("%s", doctorId);
                        printf("Enter date for appointment (e.g., DD-MM-YYYY): ");
                        scanf("%s", date);
                        printf("Enter time for appointment (e.g., HH:MM): ");
                        scanf("%s", time);

                        foundPatientForAppointment->appointments = addAppointment(foundPatientForAppointment->appointments, searchId, doctorId, date, time);
                        printf("Appointment added successfully.\n");
                    }
                    else
                    {
                        printf("No patient found with ID: %s\n", searchId);
                    }
                    break;

                case 7:
                    printf("Enter patient ID to view appointments: ");
                    scanf("%s", searchId);
                    viewAppointments(patientHead, doctorHead, searchId);
                    break;

                default:
                    printf("Invalid. Please Try Again.\n");
                    break;
                }
            }
            else if (dept == 3)
            {
                printf("Exiting...\n");
                break;
            }
            else
            {
                printf("Invalid user type. Try again.\n");
            }

        } while (1);
    }
    else
    {
        printf("Login failed. Exiting...\n");
    }

    while (doctorHead != NULL)
    {
        struct Doctor *temp = doctorHead;
        doctorHead = doctorHead->next;
        free(temp);
    }

    while (patientHead != NULL)
    {
        struct Patient *temp = patientHead;
        patientHead = patientHead->next;
        free(temp);
    }

    return 0;
}

int login(struct User *users, int numUsers)
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login your system\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int userIndex = authenticateUser(users, numUsers, username, password);

    return userIndex;
}

int authenticateUser(struct User *users, int numUsers, const char *username, const char *password)
{
    for (int i = 0; i < numUsers; ++i)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            return i;
        }
    }
    return -1;
}

struct Doctor *addDoctor(struct Doctor *head)
{
    struct Doctor *newDoctor = (struct Doctor *)malloc(sizeof(struct Doctor));
    if (newDoctor == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Enter doctor name: ");
    scanf("%s", newDoctor->name);
    printf("Enter doctor ID: ");
    scanf("%s", newDoctor->doctorId);
    printf("Enter doctor Depertment: ");
    scanf("%s", newDoctor->department);
    printf("Enter doctor chamber no: ");
    scanf("%s", newDoctor->chamberNo);

    newDoctor->next = head;
    return newDoctor;
}

void viewDoctorsInfo(struct Doctor *head)
{
    if (head == NULL)
    {
        printf("No doctor found.\n");
        return;
    }
    printf("Doctor List:\n");
    printf("ID\tNAME\tDEPARTMENT\tCHAMBER_NO\n");

    struct Doctor *current = head;
    while (current != NULL)
    {
        printf("%s\t%s\t%s\t%s\n", current->doctorId, current->name, current->department, current->chamberNo);
        current = current->next;
    }
}

struct Doctor *searchDoctor(const struct Doctor *head, const char searchId[MAX_ID_LENGTH])
{
    const struct Doctor *start = head;
    const struct Doctor *end = NULL;

    while (start != end)
    {
        const struct Doctor *mid = start;
        int count = 0;

        while (mid != end)
        {
            mid = mid->next;
            count++;
        }

        mid = head;
        for (int i = 0; i < count / 2; i++)
        {
            mid = mid->next;
        }

        int compare = strcmp(mid->doctorId, searchId);

        if (compare == 0)
        {
            return (struct Doctor *)mid;
        }
        else if (compare < 0)
        {
            start = mid->next;
        }
        else
        {
            end = mid;
        }
    }

    return NULL;
}

struct Doctor *updateDoctorInfo(struct Doctor *head, char searchId[MAX_ID_LENGTH])
{
    struct Doctor *current = head;

    while (current != NULL)
    {
        int compare = strcmp(current->doctorId, searchId);
        if (compare == 0)
        {
            int choice;
            do
            {
                printf("Update Options:\n");
                printf("1. Name\n");
                printf("2. Doctor ID\n");
                printf("3. Department\n");
                printf("4. Chamber No\n");
                printf("5. Done\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    printf("Enter new doctor name: ");
                    scanf("%s", current->name);
                    break;
                case 2:
                    printf("Enter new doctor ID: ");
                    scanf("%s", current->doctorId);
                    break;
                case 3:
                    printf("Enter new doctor department: ");
                    scanf("%s", current->department);
                    break;
                case 4:
                    printf("Enter new doctor chamber no: ");
                    scanf("%s", current->chamberNo);
                    break;
                case 5:
                    printf("Doctor updated successfully\n");
                    break;
                default:
                    printf("Invalid choice. Try again.\n");
                    break;
                }
            } while (choice != 5);

            return head;
        }
        current = current->next;
    }

    printf("No doctor found with ID: %s\n", searchId);
    return head;
}

struct Doctor *deleteDoctorInfo(struct Doctor *head, char searchId[MAX_ID_LENGTH])
{
    struct Doctor *current = head;
    struct Doctor *prev = NULL;

    while (current != NULL)
    {
        int cmp = strcmp(current->doctorId, searchId);
        if (cmp == 0)
        {
            if (prev != NULL)
            {
                prev->next = current->next;
            }
            else
            {
                head = current->next;
            }
            free(current);
            printf("Doctor deleted successfully.\n");
            return head;
        }
        prev = current;
        current = current->next;
    }

    printf("No doctor found with ID: %s\n", searchId);
    return head;
}

struct Patient *addPatient(struct Patient *head)
{
    struct Patient *newPatient = (struct Patient *)malloc(sizeof(struct Patient));
    if (newPatient == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Enter patient name: ");
    scanf("%s", newPatient->name);
    printf("Enter patient ID: ");
    scanf("%s", newPatient->patientId);
    printf("Enter patient illness: ");
    scanf("%s", newPatient->illness);
    printf("Enter patient cabin no: ");
    scanf("%s", newPatient->cabinNo);

    newPatient->appointments = NULL;
    newPatient->next = head;

    return newPatient;
}

void viewPatientsInfo(struct Patient *head)
{
    if (head == NULL)
    {
        printf("No patient found.\n");
        return;
    }
    printf("Patients List:\n");
    printf("ID\tNAME\tILLNESS\tCABIN_NO\n");

    struct Patient *current = head;
    while (current != NULL)
    {
        printf("%s\t%s\t%s\t%s\n", current->patientId, current->name, current->illness, current->cabinNo);
        current = current->next;
    }
}

struct Patient *searchPatient(const struct Patient *head, const char searchId[MAX_ID_LENGTH])
{
    const struct Patient *start = head;
    const struct Patient *end = NULL;

    while (start != end)
    {
        const struct Patient *mid = start;
        int count = 0;

        while (mid != end)
        {
            mid = mid->next;
            count++;
        }

        mid = head;
        for (int i = 0; i < count / 2; i++)
        {
            mid = mid->next;
        }
        int compare = strcmp(mid->patientId, searchId);

        if (compare == 0)
        {
            return (struct Patient *)mid;
        }
        else if (compare < 0)
        {
            start = mid->next;
        }
        else
        {
            end = mid;
        }
    }

    return NULL;
}

struct Patient *updatePatientInfo(struct Patient *head, char searchId[MAX_ID_LENGTH])
{
    struct Patient *current = head;

    while (current != NULL)
    {
        int compare = strcmp(current->patientId, searchId);
        if (compare == 0)
        {
            int choice;
            do
            {
                printf("Update Options:\n");
                printf("1. Name\n");
                printf("2. Patient ID\n");
                printf("3. Illness\n");
                printf("4. Cabin No\n");
                printf("5. Done\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    printf("Enter new patient name: ");
                    scanf("%s", current->name);
                    break;
                case 2:
                    printf("Enter new patient ID: ");
                    scanf("%s", current->patientId);
                    break;
                case 3:
                    printf("Enter new patient illness: ");
                    scanf("%s", current->illness);
                    break;
                case 4:
                    printf("Enter new patient cabin no: ");
                    scanf("%s", current->cabinNo);
                    break;
                case 5:
                    printf("Patient updated successfully\n");
                    break;
                default:
                    printf("Invalid choice. Try again.\n");
                    break;
                }
            } while (choice != 5);

            return head;
        }
        current = current->next;
    }

    printf("No patient found with ID: %s\n", searchId);
    return head;
}

struct Patient *deletePatientInfo(struct Patient *head, char searchId[MAX_ID_LENGTH])
{
    struct Patient *current = head;
    struct Patient *prev = NULL;

    while (current != NULL)
    {
        int cmp = strcmp(current->patientId, searchId);
        if (cmp == 0)
        {
            if (prev != NULL)
            {
                prev->next = current->next;
            }
            else
            {
                head = current->next;
            }
            free(current);
            printf("Patient deleted successfully.\n");
            return head;
        }
        prev = current;
        current = current->next;
    }

    printf("No patient found with ID: %s\n", searchId);
    return head;
}

struct Appointment *addAppointment(struct Appointment *head, const char *patientId, const char *doctorId, const char *date, const char *time)
{
    struct Appointment *newAppointment = (struct Appointment *)malloc(sizeof(struct Appointment));
    if (newAppointment == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newAppointment->patientId, patientId);
    strcpy(newAppointment->doctorId, doctorId);
    strcpy(newAppointment->date, date);
    strcpy(newAppointment->time, time);

    newAppointment->next = NULL;

    if (head == NULL)
    {
        head = newAppointment;
    }
    else
    {
        struct Appointment *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newAppointment;
    }

    return head;
}

void viewAppointments(struct Patient *patientHead, struct Doctor *doctorHead, char searchId[MAX_ID_LENGTH])
{
    struct Patient *foundPatient = searchPatient(patientHead, searchId);

    if (foundPatient != NULL)
    {
        struct Appointment *currentAppointment = foundPatient->appointments;

        if (currentAppointment == NULL)
        {
            printf("No appointments found for patient ID: %s\n", searchId);
            return;
        }

        printf("Appointments for Patient ID: %s\n", searchId);
        printf("Doctor ID\tDate\tTime\n");

        while (currentAppointment != NULL)
        {
            printf("%s\t%s\t%s\n", currentAppointment->doctorId, currentAppointment->date, currentAppointment->time);
            currentAppointment = currentAppointment->next;
        }
    }
    else
    {
        printf("No patient found with ID: %s\n", searchId);
    }
}

void viewAppointmentsByDoctor(struct Patient *patientHead, const char *doctorId)
{
    struct Patient *currentPatient = patientHead;
    int appointmentFound = 0;

    printf("Appointments for Doctor ID: %s\n", doctorId);
    printf("Patient ID\tDate\tTime\n");

    while (currentPatient != NULL)
    {
        struct Appointment *currentAppointment = currentPatient->appointments;

        while (currentAppointment != NULL)
        {
            if (strcmp(currentAppointment->doctorId, doctorId) == 0)
            {
                printf("%s\t%s\t%s\n", currentPatient->patientId, currentAppointment->date, currentAppointment->time);
                appointmentFound = 1;
            }
            currentAppointment = currentAppointment->next;
        }

        currentPatient = currentPatient->next;
    }

    if (!appointmentFound)
    {
        printf("No appointments found for Doctor ID: %s\n", doctorId);
    }
}
void bubbleSortDoctors(struct Doctor *head)
{
    int swapped;
    struct Doctor *ptr1;
    struct Doctor *lptr = NULL;

    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->name, ptr1->next->name) > 0)
            {
                swapDoctors(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void swapDoctors(struct Doctor *a, struct Doctor *b)
{
    struct Doctor temp;
    strcpy(temp.name, a->name);
    strcpy(temp.doctorId, a->doctorId);
    strcpy(temp.department, a->department);
    strcpy(temp.chamberNo, a->chamberNo);

    strcpy(a->name, b->name);
    strcpy(a->doctorId, b->doctorId);
    strcpy(a->department, b->department);
    strcpy(a->chamberNo, b->chamberNo);

    strcpy(b->name, temp.name);
    strcpy(b->doctorId, temp.doctorId);
    strcpy(b->department, temp.department);
    strcpy(b->chamberNo, temp.chamberNo);
}

void bubbleSortPatients(struct Patient *head)
{
    int swapped;
    struct Patient *ptr1;
    struct Patient *lptr = NULL;

    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->name, ptr1->next->name) > 0)
            {
                swapPatients(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void swapPatients(struct Patient *a, struct Patient *b)
{
    struct Patient temp;
    strcpy(temp.name, a->name);
    strcpy(temp.patientId, a->patientId);
    strcpy(temp.illness, a->illness);
    strcpy(temp.cabinNo, a->cabinNo);

    strcpy(a->name, b->name);
    strcpy(a->patientId, b->patientId);
    strcpy(a->illness, b->illness);
    strcpy(a->cabinNo, b->cabinNo);

    strcpy(b->name, temp.name);
    strcpy(b->patientId, temp.patientId);
    strcpy(b->illness, temp.illness);
    strcpy(b->cabinNo, temp.cabinNo);
}