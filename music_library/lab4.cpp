#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>   // for substr()
using namespace std;


void readInput(map<string, vector<string>> &data) {
    ifstream inFS("lab4.txt");
    string input = "\0";
    string item = "\0";
    string country = "\0";
    int i = 0;

    if (!inFS.is_open()) {
        cout << "Cannot open file :(" << endl;
        return ;
    }

    while (getline(inFS, input)) {
        if (inFS.fail()) {
            cout << "Bad input :(" << endl;
            break;
        }

        i = input.find(';');
        item = input.substr(0, i);
        country = input.substr(i + 1);

        data[item].push_back(country);
    }
} // end readInput()


void printVector(const vector<string> countries) {
    for (const auto &country : countries) {
        cout << country << ", ";
    }
}


void printExports(const map<string, vector<string>> data) {
    for (const auto &item : data) {
        cout << item.first << " ==> ";
        printVector(item.second);
        cout << endl;
    }
}


int main() {
    map<string, vector<string>> data;

    readInput(data);
    printExports(data);

    return 0;
}