#include <iostream>
using namespace std;

// Function Declarations
double average(int* arr, int n);
int maximum(int* arr, int n);
int minimum(int* arr, int n);

int main() {
    int n;

    cout << "Enter number of students: ";
    cin >> n;

    // Dynamically allocate array
    int* scores = new int[n];

    // Input scores
    for (int i = 0; i < n; i++) {
        cout << "Enter score " << i + 1 << ": ";
        cin >> scores[i];
    }

    // Output scores
    cout << "\nStudent Scores: ";
    for (int i = 0; i < n; i++)
        cout << scores[i] << " ";
    cout << endl;

    // Display results
    cout << "Average Score: " << average(scores, n) << endl;
    cout << "Maximum Score: " << maximum(scores, n) << endl;
    cout << "Minimum Score: " << minimum(scores, n) << endl;

    // Free memory
    delete[] scores;
    scores = nullptr;

    return 0;
}

// Function Definitions 
double average(int* arr, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum / n;
}

int maximum(int* arr, int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }
    return maxVal;
}

int minimum(int* arr, int n) {
    int minVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal)
            minVal = arr[i];
    }
    return minVal;
}
