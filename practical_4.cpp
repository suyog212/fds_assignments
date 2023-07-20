#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Structure to store employee information
struct Employee {
    int empId;
    string empName;
    string empDesignation;
    double empSalary;
};

// Function to add records to the file
void addRecord(fstream& file) {
    Employee employee;

    cout << "Enter Employee ID: ";
    cin >> employee.empId;
    cin.ignore(); // Ignore the newline character left in the buffer

    cout << "Enter Employee Name: ";
    getline(cin, employee.empName);

    cout << "Enter Employee Designation: ";
    getline(cin, employee.empDesignation);

    cout << "Enter Employee Salary: ";
    cin >> employee.empSalary;

    // Move the file pointer to the end to append the record
    file.seekp(0, ios::end);

    // Write the employee record to the file
    file.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
}

// Function to display all records from the file
void displayRecords(fstream& file) {
    Employee employee;

    // Move the file pointer to the beginning
    file.seekg(0, ios::beg);

    cout << "Employee Records:\n";

    // Read and display each record until the end of the file is reached
    while (file.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
        cout << "ID: " << employee.empId << ", Name: " << employee.empName
             << ", Designation: " << employee.empDesignation << ", Salary: " << employee.empSalary << "\n";
    }
}

// Function to search for a record by employee ID
void searchRecord(fstream& file, int searchId) {
    Employee employee;

    // Move the file pointer to the beginning
    file.seekg(0, ios::beg);

    // Read each record until the end of the file is reached
    while (file.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
        if (employee.empId == searchId) {
            cout << "Record Found:\n";
            cout << "ID: " << employee.empId << ", Name: " << employee.empName
                 << ", Designation: " << employee.empDesignation << ", Salary: " << employee.empSalary << "\n";
            return; // Record found, exit the function
        }
    }

    cout << "Record not found for ID: " << searchId << "\n";
}

// Function to modify a record by employee ID
void modifyRecord(fstream& file, int searchId) {
    Employee employee;

    // Move the file pointer to the beginning
    file.seekg(0, ios::beg);

    // Position to keep track of the record's position in the file
    streampos position = file.tellg();

    // Read each record until the end of the file is reached
    while (file.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
        if (employee.empId == searchId) {
            cout << "Record Found:\n";
            cout << "ID: " << employee.empId << ", Name: " << employee.empName
                 << ", Designation: " << employee.empDesignation << ", Salary: " << employee.empSalary << "\n";

            // Move the file pointer to the position of the record
            file.seekp(position);

            cout << "Enter new Employee Name: ";
            cin.ignore(); // Ignore the newline character left in the buffer
            getline(cin, employee.empName);

            cout << "Enter new Employee Designation: ";
            getline(cin, employee.empDesignation);

            cout << "Enter new Employee Salary: ";
            cin >> employee.empSalary;

            // Write the modified employee record back to the file
            file.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
            cout << "Record updated successfully.\n";
            return; // Record updated, exit the function
        }

        // Update the position to the next record
        position = file.tellg();
    }

    cout << "Record not found for ID: " << searchId << "\n";
}

// Function to delete a record by employee ID
void deleteRecord(fstream& file, int searchId) {
    Employee employee;

    // Move the file pointer to the beginning
    file.seekg(0, ios::beg);

    // Position to keep track of the record's position in the file
    streampos position = file.tellg();

    // File stream to hold temporary records
    fstream tempFile("temp.dat", ios::out | ios::binary);

    // Read each record until the end of the file is reached
    while (file.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
        if (employee.empId == searchId) {
            cout << "Record Found and Deleted:\n";
            cout << "ID: " << employee.empId << ", Name: " << employee.empName
                 << ", Designation: " << employee.empDesignation << ", Salary: " << employee.empSalary << "\n";
        } else {
            // Write the record to the temporary file if it does not match the given ID
            tempFile.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
        }

        // Update the position to the next record
        position = file.tellg();
    }

    // Close both files
    file.close();
    tempFile.close();

    // Delete the original file and rename the temporary file to the original file's name
    remove("employees.dat");
    rename("temp.dat", "employees.dat");

    cout << "Record not found for ID: " << searchId << "\n";
}

int main() {
    fstream file("employees.dat", ios::in | ios::out | ios::binary | ios::app);

    if (!file) {
        cout << "Error in opening the file.\n";
        return 1;
    }

    int choice;
    int searchId;

    do {
        cout << "\nEmployee Database Menu:\n";
        cout << "1. Add Record\n";
        cout << "2. Display Records\n";
        cout << "3. Search Record\n";
        cout << "4. Modify Record\n";
        cout << "5. Delete Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord(file);
                break;
            case 2:
                displayRecords(file);
                break;
            case 3:
                cout << "Enter Employee ID to search: ";
                cin >> searchId;
                searchRecord(file, searchId);
                break;
            case 4:
                cout << "Enter Employee ID to modify: ";
                cin >> searchId;
                modifyRecord(file, searchId);
                break;
            case 5:
                cout << "Enter Employee ID to delete: ";
                cin >> searchId;
                deleteRecord(file, searchId);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 6);

    // Close the file before exiting
    file.close();

    return 0;
}
