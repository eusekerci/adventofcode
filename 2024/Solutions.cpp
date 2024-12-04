#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <string.h>

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

void Solution03_A() {
    std::ifstream myfile;
    myfile.open("03/input.txt");

    string line;
    int64_t result = 0;

    std::getline(myfile, line);

    std::regex pattern("mul\\(\\d+,\\d+\\)");

    std::sregex_iterator currentMatch(line.begin(), line.end(), pattern);
    std::sregex_iterator lastMatch;

    while (currentMatch != lastMatch) {
        std::smatch match = *currentMatch;
        std::cout << "Match found: " << match.str() << std::endl;

        string numbers = match.str();
        numbers = numbers.substr(4, numbers.size()-5);

        vector<std::string> parts;
        stringstream ss(numbers);
        string item;
        while (std::getline(ss, item, ',')) {
            parts.push_back(item);
        }
        cout << numbers << endl;
        cout << parts[0] << " " << parts[1] << endl;

        result += std::stoi(parts[0]) * std::stoi(parts[1]);

        ++currentMatch;
    }

    cout << result << endl;
}

void Solution03_B() {
    std::ifstream myfile;
    myfile.open("03/input.txt");

    string line;
    int64_t result = 0;

    std::getline(myfile, line);

    std::regex pattern("mul\\(\\d+,\\d+\\)|do\\(\\)|don't\\(\\)");

    std::sregex_iterator currentMatch(line.begin(), line.end(), pattern);
    std::sregex_iterator lastMatch;

    bool isEnabled = true;

    while (currentMatch != lastMatch) {
        std::smatch match = *currentMatch;
        std::cout << "Match found: " << match.str() << std::endl;

        string numbers = match.str();

        if (numbers == "do()") {
            isEnabled = true;
        } else if (numbers == "don't()") {
            isEnabled = false;
        } else {
            if (isEnabled) {
                numbers = numbers.substr(4, numbers.size()-5);

                vector<std::string> parts;
                stringstream ss(numbers);
                string item;
                while (std::getline(ss, item, ',')) {
                    parts.push_back(item);
                }
                cout << numbers << endl;
                cout << parts[0] << " " << parts[1] << endl;

                result += std::stoi(parts[0]) * std::stoi(parts[1]);
            }
        }

        ++currentMatch;
    }

    cout << result << endl;
}

enum class Direction {
    HORIZONTAL,
    VERTICAL,
    DIAGONALX,
    DIAGONALY
};

bool isXMAS(vector<string>& matrix, int x, int y, Direction direction) {
    if (direction == Direction::HORIZONTAL) {
        if (x+3 >= matrix[y].size()) {
            return false;
        }
        if (matrix[y][x] == 'X' && matrix[y][x+1] == 'M' && matrix[y][x+2] == 'A' && matrix[y][x+3] == 'S') {
            return true;
        }
        if (matrix[y][x] == 'S' && matrix[y][x+1] == 'A' && matrix[y][x+2] == 'M' && matrix[y][x+3] == 'X') {
            return true;
        }
    } else if (direction == Direction::VERTICAL) {
        if (y+3 >= matrix.size()) {
            return false;
        }
        if (matrix[y][x] == 'X' && matrix[y+1][x] == 'M' && matrix[y+2][x] == 'A' && matrix[y+3][x] == 'S') {
            return true;
        }
        if (matrix[y][x] == 'S' && matrix[y+1][x] == 'A' && matrix[y+2][x] == 'M' && matrix[y+3][x] == 'X') {
            return true;
        }

    } else if (direction == Direction::DIAGONALX) {
        if (x+3 >= matrix[y].size() || y+3 >= matrix.size()) {
            return false;
        }
        if (matrix[y][x] == 'X' && matrix[y+1][x+1] == 'M' && matrix[y+2][x+2] == 'A' && matrix[y+3][x+3] == 'S') {
            return true;
        }
        if (matrix[y][x] == 'S' && matrix[y+1][x+1] == 'A' && matrix[y+2][x+2] == 'M' && matrix[y+3][x+3] == 'X') {
            return true;
        }
    } else if (direction == Direction::DIAGONALY) {
        if (x-3 < 0 || y+3 >= matrix.size()) {
            return false;
        }
        if (matrix[y][x] == 'X' && matrix[y+1][x-1] == 'M' && matrix[y+2][x-2] == 'A' && matrix[y+3][x-3] == 'S') {
            return true;
        }
        if (matrix[y][x] == 'S' && matrix[y+1][x-1] == 'A' && matrix[y+2][x-2] == 'M' && matrix[y+3][x-3] == 'X') {
            return true;
        }
    }
    return false;
}

bool isMASMAS(vector<string>& matrix, int x, int y) {
    if (x-1 < 0 || x+1 >= matrix[y].size() || y-1 < 0 || y+1 >= matrix.size()) {
        return false;
    }
    if ((matrix[y][x] == 'A' && matrix[y-1][x-1] == 'M' && matrix[y+1][x+1] == 'S') || (matrix[y][x] == 'A' && matrix[y-1][x-1] == 'S' && matrix[y+1][x+1] == 'M')) {
        if ((matrix[y-1][x+1] == 'M' && matrix[y+1][x-1] == 'S') || (matrix[y-1][x+1] == 'S' && matrix[y+1][x-1] == 'M')) {
            return true;
        }
    }
    return false;
}

void Solution04_A() {
    std::ifstream myfile;
    myfile.open("04/input.txt");

    vector< string > matrix;
    string line;

    int64_t result = 0;

    while (std::getline(myfile, line)) {
        std::istringstream iss(line);
        matrix.push_back(line);
    }

    for (int i=0; i<matrix.size(); i++) {
        for (int j=0; j<matrix[i].size(); j++) {
            if (isXMAS(matrix, j, i, Direction::HORIZONTAL)) {
                result++;
            }
            if (isXMAS(matrix, j, i, Direction::VERTICAL)) {
                result++;
            }
            if (isXMAS(matrix, j, i, Direction::DIAGONALX)) {
                result++;
            }
            if (isXMAS(matrix, j, i, Direction::DIAGONALY)) {
                result++;
            }
        }
    }

    cout << result << endl;
}

void Solution04_B() {
    std::ifstream myfile;
    myfile.open("04/input.txt");

    vector< string > matrix;
    string line;

    int64_t result = 0;

    while (std::getline(myfile, line)) {
        std::istringstream iss(line);
        matrix.push_back(line);
    }

    for (int i=0; i<matrix.size(); i++) {
        for (int j=0; j<matrix[i].size(); j++) {
            if (isMASMAS(matrix, j, i)) {
                result++;
            }
        }
    }

    cout << result << endl;
}


int main() {
    
    Solution04_B();
    return 0;
}