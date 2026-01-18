#include <iostream>
#include <fstream>
#include <cstdio>   // For rename and remove
#include <cstring>  // For string manipulation

using namespace std;

// 1. Define the Structure for the Data
struct Student {
    int id;
    char name[50];
    float marks;
};

// Function Prototypes
bool login();
void adddb();
void seendb();
void Searchdb();
void updb();
void deldb();
// Pointer implementation: Passing a pointer to this function
void printData(Student *s); 

int main() {
    // 2. Security Check first
    if (!login()) {
        cout << "\nAccess Denied. Terminating program.\n";
        return 0;
    }

    int choice;
    char c;

    while (true) {
        // Menu Interface
        cout << "\n=========================\n";
        cout << "   DATABASE MAIN MENU    \n";
        cout << "=========================\n";
        cout << "1. Add Data\n";
        cout << "2. Display All Data\n";
        cout << "3. Search Data\n";
        cout << "4. Update Data\n";
        cout << "5. Delete Data\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Input Validation
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            choice = 0; 
        }

        switch (choice) {
            case 1:
                adddb();
                break;
            case 2:
                seendb();
                break;
            case 3:
                Searchdb();
                break;
            case 4:
                updb();
                break;
            case 5:
                deldb();
                break;
            case 6:
                cout << "Do you want to exit (y/n): ";
                cin >> c;
                // LOGIC FIX: Use == for comparison, not =
                if (c == 'y' || c == 'Y') {
                    cout << "Exiting application. Goodbye!\n";
                    return 0;
                }
                break;
            default:
                cout << "Invalid input! Please select 1-6.\n";
        }
    }
}

// === Logic Implementation ===

// Pointer Logic: Accepts address of a structure
void printData(Student *s) {
    cout << "ID: " << s->id 
         << " | Name: " << s->name 
         << " | Marks: " << s->marks << endl;
}

bool login() {
    string u, p;
    cout << "\n--- SYSTEM LOGIN ---\n";
    cout << "Enter username (admin): ";
    cin >> u;
    cout << "Enter password (1234): ";
    cin >> p;

    // Simple authentication logic
    if (u == "admin" && p == "1234") {
        cout << "Login Successful!\n";
        return true;
    } else {
        cout << "Invalid Credentials.\n";
        return false;
    }
}

void adddb() {
    Student s;
    ofstream outfile("data.dat", ios::binary | ios::app);

    if (!outfile) {
        cout << "Error opening file!\n";
        return;
    }

    cout << "\nEnter Student ID: ";
    cin >> s.id;
    cin.ignore(); // Clear buffer
    cout << "Enter Name: ";
    cin.getline(s.name, 50);
    cout << "Enter Marks: ";
    cin >> s.marks;

    // Write the struct memory block directly to file
    outfile.write((char*)&s, sizeof(s));
    outfile.close();
    cout << "Data added successfully!\n";
}

void seendb() {
    Student s;
    ifstream infile("data.dat", ios::binary);

    if (!infile) {
        cout << "No database found (File does not exist yet).\n";
        return;
    }

    cout << "\n--- Displaying All Records ---\n";
    // Read loop
    while (infile.read((char*)&s, sizeof(s))) {
        // Calling function using argument
        printData(&s);
    }
    infile.close();
}

void Searchdb() {
    int searchId;
    bool found = false;
    Student s;
    ifstream infile("data.dat", ios::binary);

    if (!infile) {
        cout << "Database is empty.\n";
        return;
    }

    cout << "Enter ID to search: ";
    cin >> searchId;

    while (infile.read((char*)&s, sizeof(s))) {
        if (s.id == searchId) {
            cout << "\nRecord Found:\n";
            printData(&s);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Record with ID " << searchId << " not found.\n";
    }
    infile.close();
}

void updb() {
    int updateId;
    bool found = false;
    Student s;
    fstream file("data.dat", ios::binary | ios::in | ios::out);

    if (!file) {
        cout << "Database error.\n";
        return;
    }

    cout << "Enter ID to update: ";
    cin >> updateId;

    // Move pointer to beginning
    file.seekg(0); 

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == updateId) {
            cout << "Current Data: ";
            printData(&s);

            cout << "\nEnter New Name: ";
            cin.ignore();
            cin.getline(s.name, 50);
            cout << "Enter New Marks: ";
            cin >> s.marks;

            // Move write pointer back one struct size to overwrite
            int pos = -1 * static_cast<int>(sizeof(s));
            file.seekp(pos, ios::cur);
            
            file.write((char*)&s, sizeof(s));
            found = true;
            cout << "Record updated successfully.\n";
            break;
        }
    }

    if (!found) cout << "ID not found.\n";
    file.close();
}

void deldb() {
    int delId;
    bool found = false;
    Student s;
    
    ifstream infile("data.dat", ios::binary);
    ofstream outfile("temp.dat", ios::binary);

    if (!infile || !outfile) {
        cout << "File error.\n";
        return;
    }

    cout << "Enter ID to delete: ";
    cin >> delId;

    // Logic: Copy all records EXCEPT the one to delete
    while (infile.read((char*)&s, sizeof(s))) {
        if (s.id != delId) {
            outfile.write((char*)&s, sizeof(s));
        } else {
            found = true;
            cout << "Record deleted.\n";
        }
    }

    infile.close();
    outfile.close();

    // Remove old file and rename temp file
    remove("data.dat");
    rename("temp.dat", "data.dat");

    if (!found) {
        cout << "ID not found, nothing deleted.\n";
    }
}