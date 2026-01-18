//data base management project of college 
//library
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// Global Declaration
#define MAX 100
//Structure means a custom data type
struct Student {
    int id;
    char name[50];
    int age;
    char department[50];
};
//Array in a structure
struct Student students[MAX];
int count = 0;

//The function to add students
void addStudent() {
    // check for space
    if (count >= MAX) {
        printf("Database is full!\n");
        return;
    }
    //get info and add to structure
    struct Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Department: ");
    scanf("%s", s.department);
    students[count++] = s;

    // data add to i/o file database and the file is in the pointer form
    // FILE *fptr;
    // fptr = fopen("students.txt", "w");
    // if (fptr == NULL) {
    //     printf("Error opening file!\n");
    //     return;
    // }
    // fprintf(fptr, "%d\t%s\t%d\t%s\n", s.id, s.name, s.age, s.department);
    // fclose(fptr);
    printf("Student added successfully!\n");
}

// display the student record
void displayStudents() {
    if (count == 0) {
        printf("No students in the database.\n");
        return;
    }
    printf("ID\tName\tAge\tDepartment\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%d\t%s\n", students[i].id, students[i].name, students[i].age, students[i].department);
    }
}

// search the record of student in the file data base
void searchStudent() {
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Student found: %d\t%s\t%d\t%s\n", students[i].id, students[i].name, students[i].age, students[i].department);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

// update data in the database
void updateStudent(){
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Enter new Name: ");
            scanf("%s", students[i].name);
            printf("Enter new Age: ");
            scanf("%d", &students[i].age);
            printf("Enter new Department: ");
            scanf("%s", students[i].department);
            printf("Student with ID %d updated successfully.\n", id);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

//Delete the data base of student
void deleteStudent() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            printf("Student with ID %d deleted successfully.\n", id);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

// the security system of this system
void login(){
    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    if (strcmp(username, "Saumya_Panwar") == 0 && strcmp(password, "Dev_Sam@18") == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid credentials!\n");
        exit(0);
    }
}

// the center of these project the main function link all the functions
int main() {
    int choice;
    login();
    while (1) {
        printf("\nStudent Database Management\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
