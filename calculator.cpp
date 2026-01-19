#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

// Function to convert grade letter to grade point
double gradeToPoint(const string& grade) {
    if (grade == "A+" || grade == "a+") return 4.0;
    if (grade == "A"  || grade == "a")  return 4.0;
    if (grade == "A-" || grade == "a-") return 3.7;
    if (grade == "B+" || grade == "b+") return 3.3;
    if (grade == "B"  || grade == "b")  return 3.0;
    if (grade == "B-" || grade == "b-") return 2.7;
    if (grade == "C+" || grade == "c+") return 2.3;
    if (grade == "C"  || grade == "c")  return 2.0;
    if (grade == "C-" || grade == "c-") return 1.7;
    if (grade == "D+" || grade == "d+") return 1.3;
    if (grade == "D"  || grade == "d")  return 1.0;
    if (grade == "F"  || grade == "f")  return 0.0;
    return 0.0; // Invalid grade defaults to 0
}

int main() {
    int numCourses;
    vector<double> gradePoints;
    vector<int> creditHours;
    vector<string> grades;

    cout << "=========================================\n";
    cout << "           CGPA CALCULATOR\n";
    cout << "=========================================\n\n";

    // Input number of courses
    cout << "Enter the number of courses taken: ";
    cin >> numCourses;

    while (numCourses <= 0) {
        cout << "Invalid input! Please enter a positive number: ";
        cin >> numCourses;
    }

    // Input course details
    cout << "\nEnter course details:\n";
    cout << "====================\n";

    for (int i = 0; i < numCourses; i++) {
        string grade;
        int credits;

        cout << "\nCourse " << (i + 1) << ":\n";
        cout << "Enter grade (A+, A, A-, B+, B, B-, C+, C, C-, D+, D, F): ";
        cin >> grade;

        cout << "Enter credit hours: ";
        cin >> credits;

        while (credits <= 0) {
            cout << "Invalid credit hours! Please enter a positive number: ";
            cin >> credits;
        }

        double point = gradeToPoint(grade);

        gradePoints.push_back(point);
        creditHours.push_back(credits);
        grades.push_back(grade);
    }

    // Calculate semester GPA
    double totalGradePoints = 0.0;
    int totalCredits = 0;

    for (int i = 0; i < numCourses; i++) {
        totalGradePoints += gradePoints[i] * creditHours[i];
        totalCredits += creditHours[i];
    }

    double semesterGPA = (totalCredits > 0) ? totalGradePoints / totalCredits : 0.0;

    // Input previous semester data
    int previousTotalCredits;
    double previousCGPA;

    cout << "\n=========================================\n";
    cout << "For Overall CGPA Calculation:\n";
    cout << "=========================================\n";

    cout << "Enter previous total credits earned (if none, enter 0): ";
    cin >> previousTotalCredits;

    cout << "Enter previous CGPA (if none, enter 0): ";
    cin >> previousCGPA;

    // Calculate overall CGPA
    double overallCGPA;
    if (previousTotalCredits + totalCredits > 0) {
        double previousTotalPoints = previousCGPA * previousTotalCredits;
        overallCGPA = (previousTotalPoints + totalGradePoints) / (previousTotalCredits + totalCredits);
    } else {
        overallCGPA = 0.0;
    }

    // Display results
    cout << fixed << setprecision(2);
    cout << "\n=========================================\n";
    cout << "               RESULTS\n";
    cout << "=========================================\n\n";

    cout << left << setw(10) << "Course" 
         << setw(10) << "Grade" 
         << setw(15) << "Credit Hours" 
         << setw(15) << "Grade Points\n";
    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < numCourses; i++) {
        cout << left << setw(10) << i+1
             << setw(10) << grades[i]
             << setw(15) << creditHours[i]
             << setw(15) << gradePoints[i] << "\n";
    }

    cout << "\nSemester GPA: " << semesterGPA << "\n";
    cout << "Overall CGPA: " << overallCGPA << "\n";
    cout << "=========================================\n";

    return 0;
}