#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void Solution01_A() {
    std::ifstream myfile; 
    myfile.open("01/input.txt");

    string s = "";
    int result = 0;
    while(!myfile.eof()) {
        getline(myfile, s);
        bool isFirstDigit = true;
        for(int i=0; i<s.length(); i++) {
            if (s[i] >= 48 && s[i] <= 57) {
                result += (s[i]-48) * 10;
                isFirstDigit = false;
                break;
            }
        }
        for(int i=s.length()-1; i>=0; i--) {
            if (s[i] >= 48 && s[i] <= 57) {
                result += (s[i]-48) * (isFirstDigit ? 10 : 1);
                break;
            }
        }
    }
    cout << result << endl;
}

void Solution01_B() {
    cout << "Day 01 B" << endl;


    vector<string> numbers;
    numbers.push_back("zero");
    numbers.push_back("one");
    numbers.push_back("two");
    numbers.push_back("three");
    numbers.push_back("four");
    numbers.push_back("five");
    numbers.push_back("six");
    numbers.push_back("seven");
    numbers.push_back("eight");
    numbers.push_back("nine");

    std::ifstream myfile; 
    myfile.open("input.txt");

    string s = "";
    int result = 0;

    while(!myfile.eof()) {
        getline(myfile, s);
        for (int i=0; i<numbers.size(); i++) {
            int index = 0;
            vector< vector< int > > map;
            while (index != string::npos) {
                index = s.find(numbers[i]);
                if (index == string::npos) {
                    break;
                } else {
                    map[i].emplace_back(index);
                }
            }
            for(int j=0; j<s.length(); j++) {
                if (s[j] >= 48 && s[j] <= 57) {
                    map[s[j]-48].emplace_back(j);
                    break;
                }
            }
            int minIndex = INT_MAX;
            int minValue = 0;
            int maxIndex = INT_MIN;
            int maxValue = 0;
            for (int j=0; j<map.size(); j++) {
                for(int a : map[j]) {
                    if (a < minIndex) {
                        minIndex = a;
                        minValue = j;
                    }
                    if (a > maxIndex) {
                        maxIndex = a;
                        maxValue = j;
                    }
                }
            }
            result += minValue * 10 + maxValue;
            cout << result << endl;
        }
        cout << result << endl;
    }
    cout << result << endl;
}

int main() {
    
    Solution01_A();
    return 0;
}