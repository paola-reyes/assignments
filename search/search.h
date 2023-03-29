// TODO: remove and replace this file header comment
// This is a .h file you will edit and turn in.

// Remove starter comments and add your own
// comments on each function and on complex code sections.

#pragma once

#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <string>       // For isalpha(), ispunct(), erase(), back()
#include <ctype.h>      // For tolower()
using namespace std;


// Returns a "clean" or raw version of a string: it is all lower case & has no leading or trailing punctiation marks
string cleanToken(string token) {    
    // If string is empty, return empty string. End function here
    if (sizeof(token) < 1) {
        return token;
    }

    bool hasLetter = false;
    // Checks if there is at least 1 letter in the string. 
    for (char element : token) {
        if (isalpha(element)) {
            hasLetter = true;
            break;     // Once it finds the letter, it stops searching
        }
    }

    // If the string doesn't have a letter, send it back. End function here
    if (!hasLetter) {
        return token;
    }

    // If there's punctuation at the front or back, remove it
    while (ispunct(token[0]) || ispunct(token.back())) {
        if (ispunct(token[0])) {        // Checks if first char is punctuation
            token.erase(0, 1);
        }

        if (ispunct(token.back())) {    // Checks if last char is punctuation
            token.erase(token.back());
        }
    }

    // Convert all the letters to lower case
    for (char element : token) {
        element = tolower(element);
    } 

    return token;   // Return the final product
}


// Separates the words of a string and adds each one to the tokens set.
set<string> gatherTokens(string text) {
    set<string> tokens;
    string newToken = "\0";     // Will hold buffer from stringstream
    stringstream divideTokens(text);

    while (divideTokens >> newToken) {
        cleanToken(newToken);       // Filter token so it meets the requirements
        tokens.insert(newToken);    // Add the token to the set
    }
    
    return tokens;  
}


int invertIndex(map<string, set<string>> temp, map<string, set<string>>& index) {
    int totalDocs;

    // Iterate through all the body text words in temp map and add them as keys to index map
    for (auto const& url : temp) {
        for (string text : url.second) {
            // If this word isn't already a key in index, add it
            if (!index.count(text)) {
                //index[text].insert(url);    // Add this url to it's url set
            }
        }
    }
}


int buildIndex(string filename, map<string, set<string>>& index) {
    ifstream inFS(filename);

    if (!inFS.is_open()) {  // If invalid filename, end function here
        return 0;
    }

    map<string, set<string>> temp;      // Will store url + body text pairs as the file is read
    string url = "\0";
    string bodyText = "\0";
    int totalDocs = 0;

    while (getline(inFS, url)) {
        getline(inFS, bodyText);
        temp[url] = gatherTokens(bodyText);
        cout << "url = " << url << endl;
        cout << "\tbody text = " << bodyText << endl << endl;
    }
    
    totalDocs = invertIndex(temp, index);

    return totalDocs;
}


// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    
    
    // TODO:  Write this function.
    
    
    return result;  // TODO:  update this.
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
void searchEngine(string filename) {

    
    // TODO:  Write this function.
    
    
}


