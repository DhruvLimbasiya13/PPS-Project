#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_RECORDS 100
#define MAX_ROOMS 50

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char gender;
    char contact[MAX_NAME_LEN];
    char medical_history[MAX_NAME_LEN];
    char address[MAX_NAME_LEN];
} Patient;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char specialty[MAX_NAME_LEN];
    char schedule[MAX_NAME_LEN];
} Doctor;

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int hour;
    int minute;
} Time;

typedef struct {
    int id;
    int patient_id;
    int doctor_id;
    Date date;
    Time time;
    char appointment_time[MAX_NAME_LEN];
} Appointment;

typedef struct {
    int room_number;
    int occupied;
    int patient_id;
} Room;

typedef struct {
    int patient_id;
    float totalCharges;
    float paidAmount;
    float dueAmount;
    float consultation_fee;
    float room_charge;
    float total_amount;
} Billing;


Patient patients[MAX_RECORDS];
Doctor doctors[MAX_RECORDS];
Appointment appointments[MAX_RECORDS];
Room rooms[MAX_ROOMS];
Billing billings[MAX_RECORDS];
int patientCount = 0;
int doctorCount = 0;
int appointmentCount = 0;
int billingCount = 0;


const char *patientFile = "patients.txt";
const char *doctorFile = "doctors.txt";
const char *appointmentFile = "appointments.txt";
const char *roomFile = "rooms.txt";
const char *billingFile = "billing.txt";


void adminMenu();
void patientMenu();
void loginMenu();
void registerPatient();
void managePatientRecords();
void manageAppointments();
void manageDoctors();
void roomManagement();
void financialReports();
void logout();
void writePatientData(Patient p);
void viewAllPatients();
void viewAllAppointments();
void cancelAppointment() ;
void addAppointment() ;
void addDoctor();
void viewAllDoctors();
void updateDoctor();
void deleteDoctor();
void viewPersonalDetails();
void bookAppointment();
void viewVisitHistory();
void viewRoomStatus();
void viewBillingInformation();
void addPatient();
void updatePatientDetails();
void deletePatient();
void viewRoomStatus();
void allocateRoomToPatient();
void freeRoom();

void clearScreen() {
    system("cls || clear");
}

// Main driver function
int main() {
    clearScreen();
    loginMenu();
    return 0;
}

void loginMenu() {
    int choice;
    printf("======== Hospital Management System ========\n");
    printf("1. Login as Admin Staff\n");
    printf("2. Login as Patient\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            adminMenu();
            break;
        case 2:
            patientMenu();
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice. Try again.\n");
            loginMenu();
    }
}

void adminMenu() {
    int choice;
    clearScreen();
    printf("===== Admin Staff Dashboard =====\n");
    printf("1. Manage Patient Records\n");
    printf("2. Manage Appointments\n");
    printf("3. Manage Doctors\n");
    printf("4. Room Management\n");
    printf("5. Financial Reports\n");
    printf("6. Logout\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            managePatientRecords();
            break;
        case 2:
            manageAppointments();
            break;
        case 3:
            manageDoctors();
            break;
        case 4:
            roomManagement();
            break;
        case 5:
            financialReports();
            break;
        case 6:
            logout();
            break;
        default:
            printf("Invalid choice. Try again.\n");
            adminMenu();
    }
    
}

void patientMenu() {
    int choice;
    clearScreen();
    printf("===== Patient Dashboard =====\n");
    printf("1. View Personal Details\n");
    printf("2. Book Appointment\n");
    printf("3. Cancel Appointment\n");
    printf("4. View Visit History\n");
    printf("5. View Room Status\n");
    printf("6. View Billing Information\n");
    printf("7. Logout\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            viewPersonalDetails();

            break;
        case 2:
            bookAppointment();
            
            break;
        case 3:
            cancelAppointment();
            
            break;
        case 4:
            viewVisitHistory();
            
            break;
        case 5:
            viewRoomStatus();
            
            break;
        case 6:
            viewBillingInformation();
            
            break;
        case 7:
            logout();
            break;
        default:
            printf("Invalid choice. Try again.\n");
            patientMenu();
    }
}

void managePatientRecords() {
    int choice;
    clearScreen();
    printf("===== Manage Patient Records =====\n");
    printf("1. Add Patient\n");
    printf("2. Update Patient Details\n");
    printf("3. Delete Patient\n");
    printf("4. View Patient Details\n");
    printf("5. Back to Admin Dashboard\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            registerPatient();
            
            break;
        case 2:
            updatePatientDetails();
            
            break;
        case 3:
            deletePatient();
            
            break;
        case 4:
            viewAllPatients();
            break;
        case 5:
            adminMenu();
            break;
        default:
            printf("Invalid choice. Try again.\n");
            managePatientRecords();
    }
    printf("\nPress Enter to continue...");
    getchar(); getchar();
    managePatientRecords();
}

void viewAllPatients() {
    FILE *f = fopen(patientFile, "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Patient p;
    while (fscanf(f, "%d %s %d %c %s %s\n", &p.id, p.name, &p.age, &p.gender, p.contact, p.medical_history) != EOF) {
        printf("ID: %d, Name: %s, Age: %d, Gender: %c, Contact: %s, Medical History: %s\n",p.id, p.name, p.age, p.gender, p.contact, p.medical_history);
    }
    fclose(f);
    printf("\nPress Enter to continue...");
    getchar(); getchar();
    managePatientRecords();
}

void writePatientData(Patient p) {
    FILE *f = fopen(patientFile, "a");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(f, "%d %s %d %c %s %s\n", p.id, p.name, p.age, p.gender, p.contact, p.medical_history);
    fclose(f);
}

void logout() {
    clearScreen();
    printf("You have successfully logged out.\n");
    loginMenu();
}

void registerPatient() {
    Patient p;
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    printf("Enter Name: ");
    scanf("%s", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Gender (M/F): ");
    scanf(" %c", &p.gender);
    printf("Enter Contact Info: ");
    scanf("%s", p.contact);
    printf("Enter Medical History: ");
    scanf("%s", p.medical_history);

    writePatientData(p);
    printf("Patient registered successfully.\n");

    printf("\nPress Enter to continue...");
    getchar(); getchar();
    managePatientRecords();
}



void manageAppointments() {
    int choice;
    clearScreen();
    printf("===== Manage Appointments =====\n");
    printf("1. Add Appointment\n");
    printf("2. View All Appointments\n");
    printf("3. Cancel Appointment\n");
    printf("4. Back to Admin Dashboard\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addAppointment();
            break;
        case 2:
            viewAllAppointments();
            break;
        case 3:
            cancelAppointment();
            break;
        case 4:
            adminMenu();
            return;
        default:
            printf("Invalid choice. Try again.\n");
    }
    // Recursively call to keep showing the menu
    printf("\nPress Enter to continue...");
    getchar(); getchar();
    manageAppointments();
}
void addAppointment() {
    Appointment a;
    printf("Enter Appointment ID: ");
    scanf("%d", &a.id);
    printf("Enter Patient ID: ");
    scanf("%d", &a.patient_id);
    printf("Enter Doctor ID: ");
    scanf("%d", &a.doctor_id);
    printf("Enter Appointment Time (YYYY-MM-DD_HH:MM): ");
    scanf("%s", a.appointment_time);

    FILE *f = fopen(appointmentFile, "a");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(f, "%d %d %d %s\n", a.id, a.patient_id, a.doctor_id, a.appointment_time);
    fclose(f);

    printf("Appointment added successfully.\n");

    printf("\nPress Enter to continue...");
    getchar(); getchar();
    manageAppointments();
}

void viewAllAppointments() {
    FILE *f = fopen(appointmentFile, "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Appointment a;
    printf("\n===== Appointments List =====\n");
    while (fscanf(f, "%d %d %d %s\n", &a.id, &a.patient_id, &a.doctor_id, a.appointment_time) != EOF) {
        printf("ID: %d, Patient ID: %d, Doctor ID: %d, Time: %s\n", a.id, a.patient_id, a.doctor_id, a.appointment_time);
    }
    fclose(f);

    printf("\nPress Enter to continue...");
    getchar(); getchar();
    manageAppointments();
}

void cancelAppointment() {
    int cancelId;
    printf("Enter Appointment ID to cancel: ");
    scanf("%d", &cancelId);

    FILE *f = fopen(appointmentFile, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Appointment a;
    int found = 0;
    while (fscanf(f, "%d %d %d %s\n", &a.id, &a.patient_id, &a.doctor_id, a.appointment_time) != EOF) {
        if (a.id != cancelId) {
            fprintf(temp, "%d %d %d %s\n", a.id, a.patient_id, a.doctor_id, a.appointment_time);
        } else {
            found = 1;
        }
    }

    fclose(f);
    fclose(temp);

    remove(appointmentFile);
    rename("temp.txt", appointmentFile);

    if (found)
        printf("Appointment canceled successfully.\n");
    else
        printf("Appointment ID not found.\n");

        printf("\nPress Enter to continue...");
        getchar(); getchar();
        manageAppointments();
}

void manageDoctors() {
    int choice;
    clearScreen();
    printf("===== Manage Doctors =====\n");
    printf("1. Add Doctor\n");
    printf("2. View All Doctors\n");
    printf("3. Update Doctor Details\n");
    printf("4. Delete Doctor\n");
    printf("5. Back to Admin Dashboard\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addDoctor();
            break;
        case 2:
            viewAllDoctors();
            break;
        case 3:
            updateDoctor();
            break;
        case 4:
            deleteDoctor();
            break;
        case 5:
            adminMenu();
            return;
        default:
            printf("Invalid choice. Try again.\n");
    }
    printf("\nPress Enter to continue...");
    getchar(); getchar();
    manageDoctors();
}


void addDoctor() {
    Doctor d;
    printf("Enter Doctor ID: ");
    scanf("%d", &d.id);
    printf("Enter Doctor Name: ");
    scanf("%s", d.name);
    printf("Enter Specialty: ");
    scanf("%s", d.specialty);
    printf("Enter Schedule: ");
    scanf("%s", d.schedule);

    FILE *f = fopen(doctorFile, "a");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(f, "%d %s %s %s\n", d.id, d.name, d.specialty, d.schedule);
    fclose(f);

    printf("Doctor added successfully.\n");

    printf("\nPress Enter to continue...");
    getchar(); getchar();
    manageDoctors();
}

void viewAllDoctors() {
    FILE *f = fopen(doctorFile, "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Doctor d;
    printf("\n===== Doctors List =====\n");
    while (fscanf(f, "%d %s %s %s\n", &d.id, d.name, d.specialty, d.schedule) != EOF) {
        printf("ID: %d, Name: %s, Specialty: %s, Schedule: %s\n", d.id, d.name, d.specialty, d.schedule);
    }
    fclose(f);

    printf("\nPress Enter to continue...");
    getchar(); getchar();
    manageDoctors();
}

void updateDoctor() {
    int doctor_id;
    printf("Enter Doctor ID to update: ");
    scanf("%d", &doctor_id);

    FILE *f = fopen(doctorFile, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Doctor d;
    int found = 0;

    while (fscanf(f, "%d %s %s %s\n", &d.id, d.name, d.specialty, d.schedule) != EOF) {
        if (d.id == doctor_id) {
            printf("Enter new Name: ");
            scanf("%s", d.name);
            printf("Enter new Specialty: ");
            scanf("%s", d.specialty);
            printf("Enter new Schedule: ");
            scanf("%s", d.schedule);
            found = 1;
        }
        fprintf(temp, "%d %s %s %s\n", d.id, d.name, d.specialty, d.schedule);
    }

    fclose(f);
    fclose(temp);

    remove(doctorFile);
    rename("temp.txt", doctorFile);

    if (found)
        printf("Doctor details updated successfully.\n");
    else
        printf("Doctor ID not found.\n");

        printf("\nPress Enter to continue...");
        getchar(); getchar();
        manageDoctors();
}

void deleteDoctor() {
    int doctor_id;
    printf("Enter Doctor ID to delete: ");
    scanf("%d", &doctor_id);

    FILE *f = fopen(doctorFile, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Doctor d;
    int found = 0;

    while (fscanf(f, "%d %s %s %s\n", &d.id, d.name, d.specialty, d.schedule) != EOF) {
        if (d.id != doctor_id) {
            fprintf(temp, "%d %s %s %s\n", d.id, d.name, d.specialty, d.schedule);
        } else {
            found = 1;
        }
    }

    fclose(f);
    fclose(temp);

    remove(doctorFile);
    rename("temp.txt", doctorFile);

    if (found)
        printf("Doctor deleted successfully.\n");
    else
        printf("Doctor ID not found.\n");

        printf("\nPress Enter to continue...");
        getchar(); getchar();
        manageDoctors();
}

void roomManagement() {
    int choice;
    clearScreen();
    printf("===== Room Management =====\n");
    printf("1. View Room Status\n");
    printf("2. Allocate Room to Patient\n");
    printf("3. Free Room\n");
    printf("4. Back to Admin Dashboard\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            viewRoomStatus();
            break;
        case 2:
            allocateRoomToPatient();
            break;
        case 3:
            freeRoom();
            break;
        case 4:
            adminMenu();
            break;
        default:
            printf("Invalid choice. Try again.\n");
            roomManagement();
    }
    printf("\nPress Enter to continue...");
    getchar(); getchar();
    roomManagement();
}


void financialReports() {
    
    float totalRevenue = 0.0, totalDue = 0.0;
    for (int i = 0; i < billingCount; i++) {
        totalRevenue += billings[i].paidAmount;
        totalDue += billings[i].dueAmount;
    }
    printf("Total Revenue: %.2f\nTotal Due: %.2f\n", totalRevenue, totalDue);

    printf("\nPress Enter to continue...");
    getchar(); getchar();
    adminMenu();
}

void viewPersonalDetails(){
    int id, found = 0;
    printf("Enter your Patient ID: ");
    scanf("%d", &id);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            found = 1;
            printf("Patient ID: %d\nName: %s\nAge: %d\nGender: %s\nAddress: %s\nContact: %s\n",
                patients[i].id, patients[i].name, patients[i].age, patients[i].gender, patients[i].address, patients[i].contact);
            break;
        }
    }
    if (!found)
        printf("Patient not found.\n");

        printf("\nPress Enter to continue...");
        getchar(); getchar();
        managePatientRecords();
}
void bookAppointment(){
    Appointment a;
    printf("Enter Patient ID: ");
    scanf("%d", &a.patient_id);
    printf("Enter Doctor ID: ");
    scanf("%d", &a.doctor_id);
    printf("Enter Date (DD MM YYYY): ");
    scanf("%d %d %d", &a.date.day, &a.date.month, &a.date.year);
    printf("Enter Time (HH MM): ");
    scanf("%d %d", &a.time.hour, &a.time.minute);

    appointments[appointmentCount++] = a;
    printf("Appointment booked successfully.\n");

    printf("\nPress Enter to continue...");
    getchar(); getchar();
    manageAppointments();
}
void viewVisitHistory(){
    int id, found = 0;
    printf("Enter Patient ID to view visit history: ");
    scanf("%d", &id);

    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].patient_id == id) {
            found = 1;
            printf("Doctor ID: %d | Date: %02d/%02d/%04d | Time: %02d:%02d\n",
                    appointments[i].doctor_id,
                    appointments[i].date.day, appointments[i].date.month, appointments[i].date.year,
                    appointments[i].time.hour, appointments[i].time.minute);
        }
    }
    if (!found)
        printf("No appointments found.\n");

        printf("\nPress Enter to continue...");
        getchar(); getchar();
        patientMenu();
}
void viewRoomStatus(){

}
void viewBillingInformation(){
    int id, found = 0;
    printf("Enter Patient ID for billing info: ");
    scanf("%d", &id);

    for (int i = 0; i < billingCount; i++) {
        if (billings[i].patient_id == id) {
            found = 1;
            printf("Total Charges: %.2f\nAmount Paid: %.2f\nDue Amount: %.2f\n",
                billings[i].totalCharges, billings[i].paidAmount, billings[i].dueAmount);
        }
    }
    if (!found)
        printf("Billing record not found.\n");

        printf("\nPress Enter to continue...");
        getchar(); getchar();
        patientMenu();
}
void addPatient(){
    registerPatient();
}
void updatePatientDetails(){
    int id, found = 0;
    printf("Enter Patient ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            found = 1;
            printf("Enter New Name: ");
            scanf("%s", patients[i].name);
            printf("Enter New Age: ");
            scanf("%d", &patients[i].age);
            printf("Enter New Gender: ");
            scanf("%s", patients[i].gender);
            printf("Enter New Address: ");
            scanf("%s", patients[i].address);
            printf("Enter New Contact Number: ");
            scanf("%s", patients[i].contact);
            printf("Details updated successfully.\n");
            break;
        }
    }
    if (!found)
        printf("Patient not found.\n");

        printf("\nPress Enter to continue...");
        getchar(); getchar();
        managePatientRecords();
}
void deletePatient(){
    int id, found = 0;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            found = 1;
            for (int j = i; j < patientCount - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patientCount--;
            printf("Patient deleted successfully.\n");
            break;
        }
    }
    if (!found)
        printf("Patient not found.\n");

        printf("\nPress Enter to continue...");
        getchar(); getchar();
        managePatientRecords();
}

void allocateRoomToPatient(){
    int patient_id;
    printf("Enter Patient ID: ");
    scanf("%d", &patient_id);

    for (int i = 0; i < MAX_ROOMS; i++) {
        if (!rooms[i].occupied) {
            rooms[i].room_number = i + 1;
            rooms[i].occupied = 1;
            rooms[i].patient_id = patient_id;
            printf("Room %d allocated to patient %d.\n", rooms[i].room_number, patient_id);
            return;
        }
    }
    printf("No available rooms.\n");
    
}
void freeRoom(){
    int room_number;
    printf("Enter Room Number to free: ");
    scanf("%d", &room_number);

    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i].room_number == room_number && rooms[i].occupied) {
            rooms[i].occupied = 0;
            rooms[i].patient_id = -1;
            printf("Room %d is now free.\n", room_number);
            return;
        }
    }
    printf("Room not found or already free.\n");

    printf("\nPress Enter to continue...");
    getchar(); getchar();
    roomManagement();
}