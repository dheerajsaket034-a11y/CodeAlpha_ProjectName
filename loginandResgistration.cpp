#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

// Function to load users from file into memory
unordered_map<string, string> loadUsers(const string& filename) {
    unordered_map<string, string> users;
    ifstream file(filename);
    string username, password;

    while (file >> username >> password) {
        users[username] = password;
    }
    file.close();
    return users;
}

// Function to save a new user to file
void saveUser(const string& filename, const string& username, const string& password) {
    ofstream file(filename, ios::app); // append mode
    file << username << " " << password << endl;
    file.close();
}

// Registration function
void registerUser(const string& filename) {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    if (username.empty() || password.empty()) {
        cout << "Error: Username and password cannot be empty!" << endl;
        return;
    }

    unordered_map<string, string> users = loadUsers(filename);

    if (users.find(username) != users.end()) {
        cout << "Error: Username already exists. Please choose another." << endl;
        return;
    }

    saveUser(filename, username, password);
    cout << "Registration successful!" << endl;
}

// Login function
void loginUser(const string& filename) {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    unordered_map<string, string> users = loadUsers(filename);

    if (users.find(username) != users.end() && users[username] == password) {
        cout << "Login successful! Welcome, " << username << "." << endl;
    } else {
        cout << "Error: Invalid username or password." << endl;
    }
}

int main() {
    const string filename = "users.txt";
    int choice;

    cout << "======================================" << endl;
    cout << "      LOGIN & REGISTRATION SYSTEM     " << endl;
    cout << "======================================" << endl;

    do {
        cout << "\n1. Register\n2. Login\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser(filename);
                break;
            case 2:
                loginUser(filename);
                break;
            case 3:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}