#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_ROOMS 50

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    char appointmentDate[20];
    int roomNumber;
    int billPaid;
} Patient;

Patient patients[MAX_PATIENTS];
int patientCount = 0;

int rooms[MAX_ROOMS] = {0}; // 0 = empty, 1 = occupied

// Utility functions
void clear() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls"); // or use "clear" for Linux/Mac
}

int findEmptyRoom() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i] == 0)
            return i + 1;
    }
    return -1;
}

int findPatientById(int id) {
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id)
            return i;
    }
    return -1;
}

// Admin Functions
void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient capacity full!\n");
        return;
    }

    Patient p;
    p.id = patientCount + 1;

    printf("Enter patient name: ");
    scanf("%s", p.name);
    printf("Enter age: ");
    scanf("%d", &p.age);
    printf("Enter gender: ");
    scanf("%s", p.gender);
    printf("Enter disease: ");
    scanf("%s", p.disease);
    printf("Enter appointment date (DD/MM/YYYY): ");
    scanf("%s", p.appointmentDate);
    p.roomNumber = 0;
    p.billPaid = 0;

    patients[patientCount++] = p;

    printf("Patient registered successfully. ID: %d\n", p.id);
}

void viewPatients() {
    if (patientCount == 0) {
        printf("No patient records found.\n");
        return;
    }

    for (int i = 0; i < patientCount; i++) {
        Patient p = patients[i];
        printf("\nID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nAppointment: %s\nRoom: %d\nBill Paid: %s\n",
               p.id, p.name, p.age, p.gender, p.disease, p.appointmentDate,
               p.roomNumber, p.billPaid ? "Yes" : "No");
    }
}

void allocateRoom() {
    int id;
    printf("Enter patient ID: ");
    scanf("%d", &id);

    int index = findPatientById(id);
    if (index == -1) {
        printf("Patient not found.\n");
        return;
    }

    if (patients[index].roomNumber != 0) {
        printf("Patient already has a room allocated.\n");
        return;
    }

    int room = findEmptyRoom();
    if (room == -1) {
        printf("No empty rooms available.\n");
        return;
    }

    rooms[room - 1] = 1;
    patients[index].roomNumber = room;
    printf("Room %d allocated to %s.\n", room, patients[index].name);
}

void dischargePatient() {
    int id;
    printf("Enter patient ID: ");
    scanf("%d", &id);

    int index = findPatientById(id);
    if (index == -1) {
        printf("Patient not found.\n");
        return;
    }

    if (patients[index].roomNumber != 0)
        rooms[patients[index].roomNumber - 1] = 0;

    printf("Patient %s discharged. Room %d freed.\n",
           patients[index].name, patients[index].roomNumber);

    for (int i = index; i < patientCount - 1; i++)
        patients[i] = patients[i + 1];
    patientCount--;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
struct Patient {
    int id;
    char name[100];
    int age;
    char gender[10];
    char disease[100];
};

struct Appointment {
    int patientId;
    char date[20];
    char time[20];
    char doctor[100];
};

struct Room {
    int roomNumber;
    int isOccupied;
    int patientId;
};

struct Bill {
    int patientId;
    float consultationFee;
    float roomCharge;
    float medicineCost;
};

// Global variables
struct Patient patients[100];
struct Appointment appointments[100];
struct Room rooms[10];
struct Bill bills[100];

int patientCount = 0, appointmentCount = 0, billCount = 0;

// Function declarations
void adminMenu();
int loginAdmin();
void addPatient();
void viewPatients();
void scheduleAppointment();
void viewAppointments();
void manageRooms();
void viewRooms();
void generateBill();
void viewBills();

int main() {
    for (int i = 0; i < 10; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isOccupied = 0;
        rooms[i].patientId = -1;
    }

    int choice;
    while (1) {
        printf("\n--- Hospital Management System ---\n");
        printf("1. Admin Login\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (loginAdmin()) {
                adminMenu();
            } else {
                printf("Login failed. Try again.\n");
            }
        } else if (choice == 2) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}

int loginAdmin() {
    char user[20], pass[20];
    printf("Enter admin username: ");
    scanf("%s", user);
    printf("Enter admin password: ");
    scanf("%s", pass);

    // Simple username-password check
    if (strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0) {
        return 1;
    }
    return 0;
}

void adminMenu() {
    int choice;
    while (1) {
        printf("\n--- Admin Menu ---\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Schedule Appointment\n");
        printf("4. View Appointments\n");
        printf("5. Manage Rooms\n");
        printf("6. View Rooms\n");
        printf("7. Generate Bill\n");
        printf("8. View Bills\n");
        printf("9. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: scheduleAppointment(); break;
            case 4: viewAppointments(); break;
            case 5: manageRooms(); break;
            case 6: viewRooms(); break;
            case 7: generateBill(); break;
            case 8: viewBills(); break;
            case 9: return;
            default: printf("Invalid choice.\n");
        }
    }
}

void addPatient() {
    struct Patient p;
    printf("Enter patient ID: ");
    scanf("%d", &p.id);
    printf("Enter patient name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter age: ");
    scanf("%d", &p.age);
    printf("Enter gender: ");
    scanf("%s", p.gender);
    printf("Enter disease: ");
    scanf(" %[^\n]", p.disease);

    patients[patientCount++] = p;
    printf("Patient added successfully.\n");
}

void viewPatients() {
    printf("\n--- Patient List ---\n");
    for (int i = 0; i < patientCount; i++) {
        printf("ID: %d, Name: %s, Age: %d, Gender: %s, Disease: %s\n",
               patients[i].id, patients[i].name, patients[i].age,
               patients[i].gender, patients[i].disease);
    }
}

void scheduleAppointment() {
    struct Appointment a;
    printf("Enter patient ID: ");
    scanf("%d", &a.patientId);
    printf("Enter appointment date (dd/mm/yyyy): ");
    scanf("%s", a.date);
    printf("Enter time (hh:mm): ");
    scanf("%s", a.time);
    printf("Enter doctor name: ");
    scanf(" %[^\n]", a.doctor);

    appointments[appointmentCount++] = a;
    printf("Appointment scheduled successfully.\n");
}

void viewAppointments() {
    printf("\n--- Appointment List ---\n");
    for (int i = 0; i < appointmentCount; i++) {
        printf("Patient ID: %d, Date: %s, Time: %s, Doctor: %s\n",
               appointments[i].patientId, appointments[i].date,
               appointments[i].time, appointments[i].doctor);
    }
}

void manageRooms() {
    int roomNumber, patientId;
    printf("Enter room number (1-10): ");
    scanf("%d", &roomNumber);
    if (roomNumber < 1 || roomNumber > 10) {
        printf("Invalid room number.\n");
        return;
    }

    if (rooms[roomNumber - 1].isOccupied) {
        printf("Room is already occupied by patient ID: %d\n", rooms[roomNumber - 1].patientId);
        return;
    }

    printf("Enter patient ID to assign to this room: ");
    scanf("%d", &patientId);
    rooms[roomNumber - 1].isOccupied = 1;
    rooms[roomNumber - 1].patientId = patientId;

    printf("Room assigned successfully.\n");
}

void viewRooms() {
    printf("\n--- Room Status ---\n");
    for (int i = 0; i < 10; i++) {
        printf("Room %d: %s", rooms[i].roomNumber, rooms[i].isOccupied ? "Occupied" : "Available");
        if (rooms[i].isOccupied) {
            printf(" (Patient ID: %d)", rooms[i].patientId);
        }
        printf("\n");
    }
}

void generateBill() {
    struct Bill b;
    printf("Enter patient ID: ");
    scanf("%d", &b.patientId);
    printf("Enter consultation fee: ");
    scanf("%f", &b.consultationFee);
    printf("Enter room charges: ");
    scanf("%f", &b.roomCharge);
    printf("Enter medicine cost: ");
    scanf("%f", &b.medicineCost);

    bills[billCount++] = b;
    printf("Bill generated successfully.\n");
}

void viewBills() {
    printf("\n--- Bills ---\n");
    for (int i = 0; i < billCount; i++) {
        printf("Patient ID: %d, Consultation: ₹%.2f, Room: ₹%.2f, Medicine: ₹%.2f, Total: ₹%.2f\n",
               bills[i].patientId, bills[i].consultationFee,

               bills[i].roomCharge, bills[i].medicineCost,
               bills[i].consultationFee + bills[i].roomCharge + bills[i].medicineCost);
    }
}


void generateBill() {
    int id;
    printf("Enter patient ID: ");
    scanf("%d", &id);

    int index = findPatientById(id);
    if (index == -1) {
        printf("Patient not found.\n");
        return;
    }

    int days;
    printf("Enter number of days stayed: ");
    scanf("%d", &days);

    int roomCharge = 500; // per day
    int total = days * roomCharge;

    printf("Total bill for %s: ₹%d\n", patients[index].name, total);
    patients[index].billPaid = 1;
}

// Admin Panel
void adminPanel() {
    char password[20];
    printf("Enter admin password: ");
    scanf("%s", password);

    if (strcmp(password, "admin123") != 0) {
        printf("Incorrect password.\n");
        return;
    }

    int choice;
    do {
        printf("\n--- Admin Panel ---\n");
        printf("1. Add Patient\n2. View Patients\n3. Allocate Room\n4. Discharge Patient\n5. Generate Bill\n6. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: allocateRoom(); break;
            case 4: dischargePatient(); break;
            case 5: generateBill(); break;
            case 6: return;
            default: printf("Invalid choice.\n");
        }
        clear();
    } while (choice != 6);
}

// Patient Panel
void patientPanel() {
    int id;
    printf("Enter your patient ID: ");
    scanf("%d", &id);

    int index = findPatientById(id);
    if (index == -1) {
        printf("Patient not found.\n");
        return;
    }

    Patient p = patients[index];
    printf("\n--- Patient Info ---\n");
    printf("Name: %s\nAge: %d\nGender: %s\nDisease: %s\nAppointment: %s\nRoom: %d\nBill Paid: %s\n",
           p.name, p.age, p.gender, p.disease, p.appointmentDate,
           p.roomNumber, p.billPaid ? "Yes" : "No");
}

// Main Menu
int main() {
    int choice;
    do {
        printf("\n===== Hospital Management System =====\n");
        printf("1. Admin Login\n2. Patient Portal\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: adminPanel(); break;
            case 2: patientPanel(); break;
            case 3: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
        clear();
    } while (choice != 3);

    return 0;
}
