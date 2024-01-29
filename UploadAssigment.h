#ifndef OOP_NEW_PROJECT_UPLOADASSIGMENT_H
#define OOP_NEW_PROJECT_UPLOADASSIGMENT_H

#include <windows.h>
#include <commdlg.h>
#include <fstream>
using namespace std;

#include <windows.h>
#include <commdlg.h>
#include <fstream>

using namespace std;

class UploadAssignment {
public:
    void uploadFile(const string& enrollment) {
        string courses[10]; // Assuming a student can enroll in a maximum of 10 courses
        int numCourses = 0;

        // Read the file to get all the enrolled courses
        ifstream file(enrollment + "_enrolledCourses.txt");
        string line;
        while (getline(file, line)) {
            if (line.find("Course Code: ") != string::npos) {
                courses[numCourses] = line.substr(13); // Extract the course code
                numCourses++;
            }
        }

        // Display all the enrolled courses and ask the student to select one
        cout << "Courses enrolled by student:\n";
        for (int i = 0; i < numCourses; i++) {
            cout << i + 1 << ". " << courses[i] << "\n";
        }
        int choice;
        cout << "Choose a course to upload assignment: ";
        while(!(cin >> choice) || choice < 1 || choice > numCourses) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and " << numCourses << ": ";
        }
        string courseCode = courses[choice - 1];

        // Upload the assignment for the selected course
        OPENFILENAME ofn; // Declare a structure of type OPENFILENAME. This structure contains information the system needs to initialize an Open or Save As dialog box.
        char fileName[MAX_PATH] = ""; // Declare a character array to store the file name.
        ZeroMemory(&ofn, sizeof(ofn)); // Initialize all members of the ofn structure to 0.
        ofn.lStructSize = sizeof(OPENFILENAME); // Set the size of the OPENFILENAME structure.
        ofn.hwndOwner = NULL; // No owner window for the dialog box.
        ofn.lpstrFilter = "All Files\0*.*\0\0"; // Set the types of files that the dialog box displays.
        ofn.lpstrFile = fileName; // Set the file name used in the dialog box.
        ofn.nMaxFile = MAX_PATH; // Set the maximum length for the file name.
        ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY; // Set flags to specify how the dialog box functions.
        ofn.lpstrDefExt = ""; // No default extension.

        if (GetOpenFileName(&ofn)) // Display the Open dialog box. If the user selects a file and clicks OK, the function returns true.
        {
            ifstream srcFile(fileName, ios::binary); // Open the selected file in binary mode for reading.
            char buffer[MAX_PATH]; // Declare a buffer to store the path of the current module (executable file).
            GetModuleFileName(NULL, buffer, MAX_PATH); // Retrieve the full path and file name of the current module.
            string::size_type pos = string(buffer).find_last_of("\\/"); // Find the last occurrence of a slash in the path.
            string assignmentPath = string(buffer).substr(0, pos) + "/" + enrollment + "_" + courseCode + "_Assignment"; // Construct the path for the new file.
            ofstream dstFile(assignmentPath, ios::binary); // Open the new file in binary mode for writing.

            cout << "Uploading"; // Print a message to indicate the start of the upload process.
            for(int i = 0; i < 5; i++) {
                cout << ".";
                Sleep(500); // Delay for 500 milliseconds.
            }
            cout << "\n";

            dstFile << srcFile.rdbuf(); // Copy the contents of the source file to the destination file.

            srcFile.close(); // Close the source file.
            dstFile.close(); // Close the destination file.

            cout << "Assignment uploaded successfully." << endl; // Print a message to indicate the successful completion of the upload process.
            system("pause"); // Pause the program execution.
        }
        else
        {
            cout << "No file selected." << endl; // Print a message if no file was selected in the dialog box.
        }
        }
};
#endif //OOP_NEW_PROJECT_UPLOADASSIGMENT_H