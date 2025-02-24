//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Matthew A Keaton
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Project Two
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
 

using namespace std;

// Define structure to hold courses
struct Course {

    string courseNumber;
    string courseName;
    vector<string> coursePreReqs;

};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;


    // Default Construct
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize nodes
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }

};

// Define class to implement BST
class BinarySearchTree {

private:

    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    

public:
    BinarySearchTree();
    void inOrder();
    void Insert(Course course);
    Course Search(string courseNumber);
};

// Default construct
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}


// Traverse the tree inOrder
void BinarySearchTree::inOrder() {
    inOrder(root);
}

// inOrder print traversal
void BinarySearchTree::inOrder(Node* node) {
    if (node == nullptr) {
        return;
    }
    // InOrder left
    inOrder(node->left);
    // Print current node
    cout << node->course.courseNumber << ", " << node->course.courseName;

    // If course has prerequisites
    if (!node->course.coursePreReqs.empty()) {
        cout << "\n Prerequisites: ";
        for (size_t i = 0; i < node->course.coursePreReqs.size(); ++i) {
            cout << node->course.coursePreReqs[i];
            if (i < node->course.coursePreReqs.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    else {
        cout << endl;
    }
    // InOder right
    inOrder(node->right);
}

// Insert a course
void BinarySearchTree::Insert(Course course) {
    // Implement inserting a course into the tree
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}

// Add node to tree
void BinarySearchTree::addNode(Node* node, Course course) {

    // If node is larger then add to left
    if (node->course.courseNumber > course.courseNumber) {

        // If no left node
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            // Recurse down left
            addNode(node->left, course);
        }
    }
    else {

        // If no right node
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            // Recurse down right
            addNode(node->right, course);
        }
    }

}

// Search for a course
Course BinarySearchTree::Search(string courseNumber) {
    // Implement searching the tree for a course
    Node* current = root;

    // loop down until bottom reached or matching course number
    while (current != nullptr) {
        // if match found, return current course
        if (current->course.courseNumber == courseNumber) {
            return current->course;
        }
        // if course number is smaller than current node then traverse left
        if (courseNumber < current->course.courseNumber) {
            current = current->left;
        }
        // else larger so traverse right
        else {
            current = current->right;
        }
    }
    Course course;
    return course;
}

// Read from csv file
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file: " << csvPath << endl;

    ifstream file(csvPath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << csvPath << endl;
        return;
    }

    string line;

    // Read each line from the file
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split by comma
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Ensure there are enough columns in the row
        if (tokens.size() < 2) { // Adjust to CSV columns
            cerr << "Invalid row (missing data): " << line << endl;
            continue;
        }

        // Create a Course object
        Course course;
        course.courseNumber = tokens[0]; 
        course.courseName = tokens[1];  

        // Read any prerequisites
        for (size_t i = 2; i < tokens.size(); i++) {
            course.coursePreReqs.push_back(tokens[i]);
        }

        // Insert into BST
        bst->Insert(course);
    }

    file.close();
}

// Only main method
int main() {

    BinarySearchTree bst;
    int choice = 0;
    string courseNumber;
    string filename;

    while (choice != 9) {

        // Display menu
        cout << "Welcome to the course planner." << endl;
        cout << " 1. Load Data Structure." << endl;
        cout << " 2. Print Course List." << endl;
        cout << " 3. Print Course." << endl;
        cout << " 9. Exit." << endl;
        cout << "What would you like to do?" << endl;
        cin >> choice;

        switch (choice) {

            // Load courses from file
        case 1:
            cout << "Enter file name: " << endl;
            cin.ignore();
            getline(cin, filename);
            loadCourses(filename, &bst);
            break;

            // Call method to print courses inOrder
        case 2:
            cout << "Here is a sample schedule: " << endl;
            bst.inOrder();
            break;

            // Display course name and PreReqs
        case 3:
            cout << "What course do you want to know about?" << endl;
            cin.ignore();
            getline(cin, courseNumber);
            {
                Course course = bst.Search(courseNumber);
                if (!course.courseNumber.empty()) {
                    cout << course.courseNumber << ", " << course.courseName << endl;
                    if (!course.coursePreReqs.empty()) {
                        cout << "Prerequisites: ";
                        for (size_t i = 0; i < course.coursePreReqs.size(); ++i) {
                            cout << course.coursePreReqs[i];
                            if (i < course.coursePreReqs.size() - 1) {
                                cout << ", ";
                            }
                        }
                        cout << endl;
                    }
                }
                else {
                    cout << "Course not found" << endl;
                }
            }
            break;

        }
    }
    cout << "Thank you for using the course planner!" << endl;

    return 0;
}



