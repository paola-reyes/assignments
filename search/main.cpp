#include <iostream>
#include "search.h"
using namespace std;

int main() {
    // // Milestone #1 Tests
    // string ans = "hello";
    // cout << "1. " << (ans == cleanToken(".hello")) << endl;
    // cout << "2. " << (ans == cleanToken("...hello")) << endl;

    // // Milestone #2 Tests
    // set<string> tokens = gatherTokens("to be or not to be");
    // set<string> tokensANS;
    // tokensANS.insert("to");
    // tokensANS.insert("be");
    // tokensANS.insert("or");
    // tokensANS.insert("not");
    // cout << "1. " << (tokens.size() == 4) << endl;
    // cout << "2. " << (tokens == tokensANS) << endl;

    map<string, set<string>> index;
    int i = buildIndex("tiny.txt", index);

    return 0;
}

