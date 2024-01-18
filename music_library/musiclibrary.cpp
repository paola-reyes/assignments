/*--------------------------
    Paola Reyes
    2/14/23
    UIC CS 251, Wed 4pm Lab
    Prof. Adam Koehler
----------------------------    
Project 1 - Music Library

/// Assignment details and provided code are 
/// created and owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

This project implements a music library by storing album, artist, and song data into sets within maps.

There are 2 main maps storing the library data: 
    1) map<string, set<string>> albums, where the key is the album and the set is its songs
    2) map<string, set<string>> artists, where the key is the artist and the set their albums

The data for the library is read from .txt files that are formatted as [Album] [Artist] [Song]...[Song] [Title Again]
For example:
    Sweetener
    Ariana Grnade
    01 Raindrops (An Angel Cried)
    02 Blazed
    03 The Light Is Coming
    04 R.E.M.
    05 God Is a Woman
    06 Successful
    07 Everytime
    08 No Tears Left to Cry
    Sweetener

In this case, we insert "Sweetener" and {"01 Raindrops (An Angel Cried)"..."08 No Tears Left to Cry"} 
to the albums map. We also add "Ariana Grande" and "Sweetener" to the artists map.

The functions for this project include:
    help(): Print out the instructions
    load(): Read a .txt file and add the data to the library
    stats(): Print out how many albums, unique artists, and songs the library has in total
    exportLibrary(): Write the library data into a .txt file
    search(): Allows the user to search for albums associated with given keywords
    clear(): Delete all the library's contents
    exit(): End the program
*/
#include <iostream>
#include <fstream>      
#include <string>
#include <set>
#include <map>
#include "helpers.cpp"  // Helper functions
using namespace std;

/// @brief Keeps track of the library storage stats
struct Music {
    int records = 0;
    int uniqueArtists = 0;
    int songs = 0;
};


/// @brief Adds music data from a .txt file into our library
/// @param file .txt file to read from
/// @param albums Set in main() that has key = album title and value = set of the album songs
/// @param artists Set in main() that has key = artist name and value = all their albums
/// @param library Object in main() that will update library storage stats as we add new data
void load(string file, map<string, set<string>> &albums, map<string, set<string>> &artists, Music &library) 
{
    ifstream inFS(file);

    if (!inFS.is_open()) {
        cout << "Error: Could not open music library file - " << file << endl;
    }

    // The file is formatted as [Album] [Artist] [Song]...[Song] [Album Again] [Next Album] [Next Artist]....
    string album = "\0";
    string data = "\0";
    bool readingAlbum = true;   // We're reading the beginning of the format cycle, or the album
    bool repeatEntry = false;   // Skip repeat entries 

    while (getline(inFS, data))  
    {
        if (readingAlbum && albums.count(data)) {   // Invalid album >:(
            repeatEntry = true;
            album = data;           // We'll remember the album's name so we know where to stop skipping lines
        }
        else if (repeatEntry && data == album) {    // Invalid album >:(
            repeatEntry = false;    // We'll stop skipping lines here
        }
        else if (readingAlbum && !repeatEntry) {    // Valid album entry :)
            album = data;           // Remember the name for when we start/stop reading songs
            library.records++;      // Update corresponding library stat
            readingAlbum = false;   // We're now either reading the artists or songs
        }
        else if (!readingAlbum && data == album) {  // We reach the end of the format cycle
            readingAlbum = true;    // Skip this line and prepare for the next album
        }
        else if (!readingAlbum && !isdigit(data[0])) {  // Reading artists
            if (!artists.count(data)) {     // Repeat artists are allowed but library doesn't count repeats
                library.uniqueArtists++;    
            }

            artists[data].insert(album);    
        }
        else if (!readingAlbum && isdigit(data[0])) {   // Reading songs
            albums[album].insert(data);
            library.songs++;
        }
    }

    inFS.close();
} // end of load()


/// @brief Copy one set's elements to the end of another set
/// @param source Where the elements will come from
/// @param destination Set that will inherit the elements 
void appendSet(const set<string> &source, set<string> &destination) 
{
    for (const auto &element : source) {
        destination.insert(element);
    }
} // enf of appentSet()


/// @brief Find all the artists associated with an album. Helper function to fullStats() and exportLibrary()
/// @param album Title of the album
/// @param artists Set in main() that has key = artist name and value = all their albums
/// @return A set of all the artists found for that album
set<string> getArtistsFromAlbum(string album, const map<string, set<string>> &artists) 
{
    set<string> group;

    for (const auto &artist : artists) {
        if (artist.second.count(album)) {   // If album found among this artist's albums
            group.insert(artist.first);
        }
    }

    return group;
} // end of getArtistsFromAlbum()


/// @brief Find all the albums associated with an artist. Helper function to search()
/// @param name Person's name
/// @param artists Set in main() that has key = artist name and value = all their albums
/// @return A set of all that person's albums
set<string> getAlbumsFromArtist(string name, const map<string, set<string>> &artists) {
    set<string> result;
    for (const auto& artist : artists) {
        if (artist.first == name) {
            result = artist.second;
            break;
        }
    }

    return result;
} // end of getAlbumsFromArtist()


/// @brief Print all the data loaded into the library
/// @param albums Set in main() that has key = album title and value = set of the album songs
/// @param artists Set in main() that has key = artist name and value = all their albums
void fullStats(const map<string, set<string>> &albums, const map<string, set<string>> &artists) 
{
    cout << "Your Current Music Library Includes\n"
         << "===================================\n";

    set<string> albumArtists;   // To catch getArtistsFromAlbum() return value

    for (const auto &album : albums) {
        cout << album.first << endl;

        albumArtists = getArtistsFromAlbum(album.first, artists);   
        for (const auto artist : albumArtists) {    // Print the album's artists
            cout << " " << artist << endl;
        }

        for (const auto &song : album.second) {     // Print the album's songs
            cout << "   " << song << endl;
        }
    }

    cout << endl;
} // end of fullSats()


/// @brief Print out the data members of the Music struct
/// @param library Object in main() that will update library storage stats as we add new data
void stats(const Music library) 
{
    cout << "Overall Music Library Stats\n" 
         << "===========================\n" 
         << "Total Records: " << library.records << endl
         << "Total Unique Artists: " << library.uniqueArtists << endl
         << "Total Songs: " << library.songs << endl << endl;
} // end of stats()


/// @brief Write the library data into a .txt file
/// @param file Name of the file we'll write into
/// @param albums Set in main() that has key = album title and value = set of the album songs
/// @param artists Set in main() that has key = artist name and value = all their albums
void exportLibrary(string file, const map<string, set<string>> &albums, const map<string, set<string>> &artists) 
{
    ofstream outFS(file);

    if (!outFS.is_open()) {
        cout << "error :( \n";
    }

    set<string> albumArtists;   // To catch getArtistsFromAlbum() return value
    for (const auto &album : albums) {
        outFS << album.first << endl;

        albumArtists = getArtistsFromAlbum(album.first, artists);
        for (string artist : albumArtists) {        // Write the album's artists
            outFS << artist << endl;
        }
        
        for (const string &song : album.second) {   // Write the album's songs
            outFS << song << endl;
        }

        outFS << album.first << endl;
    }

    outFS.close();
} // end of exportLibrary()


/// @brief Check if a string with no spaces contains multiple words
/// @param word 
/// @return True/false
bool noSpaces(string word) {
    int capitals = 0;

    for (char i : word) {
        if (isupper(i)) {
            capitals++;     
        }                   
    }

    // Differentiate from titles w/ only one word + no spaces (ex: "Fearless" vs. "SexyBack")
    return (word.find(" ") == string::npos) && (capitals >= 2);
} // end of noSpaces


/// @brief splits a string into two pieces, the first word and the rest
        // Extension of splitFirstWord() from helpers.cpp, but the words separated by capital letters or 
        // special characters (i.e. "V(Deluxe)", "FutureSex/LoveSounds")
/// @param s the string to split
/// @param front a string reference to store the first word in
/// @param remains a string reference to store everything else from s
void splitFirstWord2(string s, string &front, string &remains) 
{
    // Looks for first instance of a char not within lowercase range nor a space
    front = s.substr(0, s.find_first_not_of("abcdefghijklmnopqrstuvwxyz", 1));  // Start looking at pos 1, not 0
    
    // If there are more words and more unwanted lower case/special characters
    if ((s.size() != front.size()) && s.find_first_not_of("abcdefghijklmnopqrstuvwxyz !\"#$%&'()*+-,./:;<=>?@", 1) != string::npos) {
        remains = s.substr(s.find_first_not_of("abcdefghijklmnopqrstuvwxyz !\"#$%&'()-*+-,./:;<=>?@", 1)); // Exclude those characters
    }
    else {
        remains = "";
    }
} // end of splitFirstWord2()


/// @brief Checks if the keyword is in the album title
/// @param keyword String chosen by user
/// @param data Data from the library
/// @return True/False
bool containsWord(string keyword, string data) {

    string front, remains = "\0";
    bool hasSpecialChar = data.find_first_not_of("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos;

    // Search through the words separated by capital letters/special characters (i.e. V(Deluxe), FutureSex/LoveSounds)
    if (noSpaces(data) || hasSpecialChar) {   // Uses splitFirstWord2()
        splitFirstWord2(data, front, remains);
        tolower(front);

        if (data.size() == front.size()) {  // For strings with 1 word
            return front == keyword || front.find(keyword) != string::npos;
        }
        else {  // For strings with > 1 words
            while (!front.empty()) {
                if (front == keyword || front.find(keyword) != string::npos) {
                    return true;
                }

                splitFirstWord2(remains, front, remains);
                tolower(front);
            }
        }
    
        return false;
    }
    else {  // Search through the words sepearated by spaces. Uses splitFirstWord()
        splitFirstWord(data, front, remains);
        tolower(front);     // Here we don't have to keep the capital letters

        if (data.size() == front.size()) {  // For strings with 1 word
            return front == keyword || front.find(keyword) != string::npos;
        }
        else {  // For strings with > 1 words
            while (!front.empty()) {
                if (front == keyword || front.find(keyword) != string::npos) {
                    return true;
                }

                splitFirstWord(remains, front, remains);
                tolower(front);
            }
        }

        return false;
    }
} // end of containsWord()


/// @brief Extract and organize the search commands from user input. Helper function to search()
/// @param remains String of search commands
/// @param keywords Set of words in search() to include in the search
/// @param exclude Set of words in search() to exclude in the search
void extractKeywords(string remains, set<string> &keywords, set<string> &include, set<string> &exclude) 
{
    string keyword = "\0";

    while (!remains.empty()) {
        splitFirstWord(remains, keyword, remains);  // Get next section of the commands string

        if (keyword[0] == '-') {        // User wants to exclude this word
            keyword.erase(keyword.begin());
            exclude.insert(keyword);
        }
        else if (keyword[0] == '+') {   // Include this keyword
            keyword.erase(keyword.begin());
            include.insert(keyword);
        }
        else {
            keywords.insert(keyword);   // Include this keyword
        }        
    }
} // extractKeywords()


/// @brief Check if album title contains the keywords. Helper function to search()
/// @param data One key from the albums or artists maps. This function is within a for-loop in search()
/// @param keywords Set of words in search() to include in the search
/// @param exclude Set of words in search() to exclude in the search
/// @param results Set of search results
void searchHelper(string data, set<string> keywords, set<string> include, set<string> exclude, set<string> &results) 
{  
    if (include.empty()) {
        for (string word : keywords) {
            if (containsWord(word, data)) {    // If the keyword is found in the data
                results.insert(data);          // Add it to the results
            }
        }
    }
    else {
        set<string> matches;

        for (string word : keywords) {
            for (string i : include) {      // Check if the data also contains the include words
                if (containsWord(word, data) && containsWord(i, data)) {
                    matches.insert(data);   // Keep track of the results so far
                }
            }

            if (matches.size() == include.size()) {     // These ressults are correct
                appendSet(matches, results);
            }
            else {
                matches.clear();    // Throw them away
            }
        }
    }

    for (string word : exclude) {
        if (containsWord(word, data)) {    // If exlusion word is found in the data
            results.erase(data);           // Remove it from the results
        }
    }
} // end of searchHelper()


/// @brief Like searchHelper(), but specifically for songs and has an extra parameter. Helper function to search()
/// @param song Each song in the album. This function is within a for-loop in search()
/// @param album The album we're looping through
/// @param keywords Set of words in search() to include in the search
/// @param exclude Set of words in search() to exclude in the search
/// @param results Set of search results 
void searchHelper(string song, string album, set<string> keywords, set<string> include, set<string> exclude, set<string> &results) 
{   
    if (include.empty()) {
        for (string word : keywords) {
            if (containsWord(word, song)) {    // If the keyword is found in the data
                results.insert(album);         // Add it to the results
            }
        }
    }
    else {
        for (string word : keywords) {
            for (string i : include) {      // Check if the data also contains the include words
                if (containsWord(word, song) && containsWord(i, song)) {
                    results.insert(album);  
                }
            }
        }
    }

    for (string word : exclude) {
        if (containsWord(word, song)) {    // If exlusion word is found in the data
            results.erase(album);          // Remove it from the results
        }
    }
} // end of searchHelper()


/// @brief Allows the user to search for albums associated with given keywords
/// @param command Which aspect (album, artist, or song) the user is search for
/// @param remains String of search commands
/// @param data Set in main() of albums or artists
void search(string command, string remains, const map<string, set<string>> &data) 
{
    set<string> keywords;
    set<string> include;
    set<string> exclude;
    set<string> results;
    extractKeywords(remains, keywords, include, exclude);
    
    if (command == "album") {
        for (const auto &album : data) {    // Loop through all the albums looking for keywords
            searchHelper(album.first, keywords, include, exclude, results);
        }
    }
    else if (command == "artist") { 
        set<string> associatedArtists;

        for (const auto &artist : data) {   // Make a list of all the artists with the keyword at least one album
            searchHelper(artist.first, keywords, include, exclude, associatedArtists);
        }

        for (string person : associatedArtists) {
            appendSet(getAlbumsFromArtist(person, data), results);
        }
    }
    else if (command == "song") {
        for (const auto &album : data) {    // Loop through every song of the album
            for (const auto &song : album.second) {
                searchHelper(song.substr(3), album.first, keywords, include, exclude, results);
            }
        }
    }

    if (!results.empty()) {
        cout << "Your search results exist in the following albums: \n";

        for (string result : results) {
            cout << result << endl;
        }        
    }
    else {
        cout << "No results found." << endl;
    }    

    cout << endl;
} // end of search()


int main()
{
    string userEntry;
    string command, remains;

    // Display welcome message once per program execution
    cout << "Welcome to the Music Library App" << endl;
    cout << "--------------------------------" << endl;

    Music library;
    map<string, set<string>> albums;
    map<string, set<string>> artists;

    // Stay in menu until exit command
    do
    {
        cout << endl;
        cout << "Enter a command (help for help): " << endl;
        getline(cin, userEntry);
        cout << endl;

        // Split the user entry into two pieces
        splitFirstWord(userEntry, command, remains);
        tolower(command);

        // take an action, one per iteration, based on the command
        if (command == "help") {
            helpCommand();
        }
        else if (command == "clear") {
            albums.clear();
            artists.clear();

            library.records = 0;
            library.uniqueArtists = 0;
            library.songs = 0;
        }
        else if (command == "export") {
            if (!remains.empty()) {
                exportLibrary(remains, albums, artists);
            }
            else {
                exportLibrary("musicdatabase.txt", albums, artists);
            }
        }
        else if (command == "load") {
            if (!remains.empty()) {
                load(remains, albums, artists, library);
            }
        }
        else if (command == "stats") {
            stats(library);

            if (!remains.empty() && trimWhiteSpace(remains) == "-d") {
                fullStats(albums, artists);
            }
        }          
        else if (command == "search") {
            string searchCommand = "\0";
            
            if (remains.empty()) {
                cout << "Error: Search terms cannot be empty.\nNo results found.\n\n";
            }
            else {
                tolower(remains);
                splitFirstWord(remains, searchCommand, remains);
                trimWhiteSpace(remains);

                if (searchCommand == "album" || searchCommand == "song") { 
                    search(searchCommand, remains, albums);
                }
                else {
                    search(searchCommand, remains, artists);
                }
            }
        }

    } while(command != "exit");    

    cout << "Thank you for using the Music Library App" << endl;

    return 0;
}
