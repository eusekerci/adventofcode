#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void Solution01_A() {
    std::ifstream myfile; 
    myfile.open("01/input.txt");

    int64_t left = 0;
    int64_t right = 0;
    int64_t result = 0;
    vector<int64_t> lefts;
    vector<int64_t> rights;
    while(!myfile.eof()) {
        myfile >> left >> right;
        lefts.push_back(left);
        rights.push_back(right);
    }

    sort(lefts.begin(), lefts.end());
    sort(rights.begin(), rights.end());

    for (int64_t i=0; i<lefts.size(); i++) {
            result += std::abs(lefts[i] - rights[i]);
    }

    cout << result << endl;
}

void Solution01_B() {
    std::ifstream myfile;
    myfile.open("01/input.txt");

    int64_t left = 0;
    int64_t right = 0;
    int64_t result = 0;
    vector<int64_t> lefts;
    vector<int64_t> rights;
    int64_t greatestRightNumber = 0;
    while(!myfile.eof()) {
        myfile >> left >> right;
        lefts.push_back(left);
        rights.push_back(right);
        greatestRightNumber = std::max(greatestRightNumber, right);
    }

    greatestRightNumber++;
    vector<int64_t> rightOccurance(greatestRightNumber, 0);
    for (int64_t i=0; i<rights.size(); i++) {
        rightOccurance[rights[i]]++;
    }

    for (int64_t i=0; i<lefts.size(); i++) {
        result += lefts[i] * rightOccurance[lefts[i]];
    }

    cout << result << endl;
}

int isSafeVector(vector<int> vec) {
    bool isIncreasing = vec[0] < vec[1];
    int brokenIndex = -1;
    for (int j=0; j<vec.size()-1; j++) {
        if (isIncreasing) {
            if (vec[j] >= vec[j+1] || vec[j+1] - vec[j] > 3 || vec[j] - vec[j+1] == 0) {
                brokenIndex = j;
                break;
            }
        } else {
            if (vec[j] <= vec[j+1]  || vec[j] - vec[j+1] > 3 || vec[j] - vec[j+1] == 0) {
                brokenIndex = j;
                break;
            }
        }
    }
    return brokenIndex;

}

void Solution02_A() {
    std::ifstream myfile;
    myfile.open("02/input.txt");

    vector< vector<int> > matrix;
    vector<int> row;
    string line;

    int64_t result = 0;

    while (std::getline(myfile, line)) {
        std::istringstream iss(line);
        int number;
        row.clear();
        while (iss >> number) {
            row.push_back(number);
        }
        matrix.push_back(row);
    }
    for (int i=0; i<matrix.size(); i++) {
        int isSafe = isSafeVector(matrix[i]);
        result += isSafe == -1 ? 1 : 0;
    }

    cout << result << endl;
}

void Solution02_B() {
    std::ifstream myfile;
    myfile.open("02/input.txt");

    vector< vector<int> > matrix;
    vector<int> row;
    string line;

    int64_t result = 0;

    while (std::getline(myfile, line)) {
        std::istringstream iss(line);
        int number;
        row.clear();
        while (iss >> number) {
            row.push_back(number);
        }
        matrix.push_back(row);
    }
    for (int i=0; i<matrix.size(); i++) {
        int isSafe = isSafeVector(matrix[i]);
        if (isSafe != -1) {
            vector<int> planA = matrix[i];
            vector<int> planB = matrix[i];
            vector<int> planC = matrix[i];
            planA.erase(planA.begin()+isSafe);
            planB.erase(planB.begin()+(isSafe+1));
            planC.erase(planC.begin());
            if (isSafeVector(planA) == -1 || isSafeVector(planB) == -1 || isSafeVector(planC) == -1) {
                cout << isSafe << endl;
                isSafe = -1;
            }
        }
        result += isSafe == -1 ? 1 : 0;
    }

    cout << result << endl;
}

int main() {
    
    Solution02_B();
    return 0;
}