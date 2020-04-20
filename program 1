/* -----------------------------------------------------------
  Program 1: Building
  Class: CS 141, Spring 2020. Tues 1pm lab
  System: Zybooks
  Author: Paola Reyes

  Running the program looks like:
    Choose from among the following options:
      1. Display original graphic
      2. Display building
      3. Exit the program
      Your choice -> 1

      <><><><><><><><><><><><><><><><><>
      <>         ____________         <>
      <>        /\  /\  /\  /\        <>
      <>       /__\/__\/__\/__\       <>
      <>       \  \        /  /       <>
      <>        \  \      /  /        <>
      <>         \__\____/__/         <>
      <>        .-'  ____  '-.        <>
      <>       /  .-'    '-.  \       <>
      <>      /  /          \  \      <>
      <>     |  |            |  |     <>
      <>     |  |            |  |     <>
      <>      \  \          /  /      <>
      <>       \  '-.____.-'  /       <>
      <>        '-.________.-'        <>
      <>                              <>
      <><><><><><><><><><><><><><><><><>
  
  Or it could go like this:
    Choose from among the following options:
      1. Display original graphic
      2. Display building
      3. Exit the program
      Your choice -> 2

      Number of building sections -> 3    // example answer

          /\ 
          ||  
          ||  
          --  
         |++| 
         ==== 
         |\/|
         |/\|
         /--\
        |\::/|
        |:\/:|
        |:/\:|
        |/::\|
        /----\
       |\::::/|
       |:\::/:|
       |::\/::|
       |::/\::|
       |:/::\:|
       |/::::\|
       /------\
     ............
    ++++++++++++++  
                                                                  |\/|
    Where there are some number of building sections starting the |/\| section based on user input
    
----------------------------------------------------------*/
#include <iostream>   // for cin and cout
#include <iomanip>    // for setw() and setfill()
using namespace std;  // so that we don't need to preface every cin and cout with std::


int main() {
    int menuOption = 0;
    
    // Display menu options for user and take input their choice
    cout << "Choose from among the following options:  \n"
         << "1. Display original graphic  \n"
         << "2. Display building          \n"
         << "3. Exit the program          \n"
         << "Your choice -> ";
    cin >> menuOption;
    cout << endl;   // Leave a blank line after getting the user input for the menu option.

    // See if exit was chosen
    if( menuOption == 3) {
        exit( 0);
    }

    // Menu option to display custom graphic
    else if( menuOption == 1) {

      // Print out multiple "<>" to create the top line
      for ( int i = 0; i < 17; i++) {
        cout << "<>";
      }

      // My own custom graphic which displays a ring with a vertical line of "<>" on its left & right
      cout << endl
           << "<>         ____________         <>     \n"
              "<>        /\\  /\\  /\\  /\\        <> \n"
              "<>       /__\\/__\\/__\\/__\\       <> \n"
              "<>       \\  \\        /  /       <>   \n"
              "<>        \\  \\      /  /        <>   \n"
              "<>         \\__\\____/__/         <>   \n"
              "<>        .-'  ____  '-.        <>     \n"
              "<>       /  .-'    '-.  \\       <>    \n"
              "<>      /  /          \\  \\      <>   \n"
              "<>     |  |            |  |     <>     \n"
              "<>     |  |            |  |     <>     \n"
              "<>      \\  \\          /  /      <>   \n"
              "<>       \\  '-.____.-'  /       <>    \n"
              "<>        '-.________.-'        <>     \n"
              "<>                              <>     \n";

      // Print out multiple "<>" again for the bottom line        
      for ( int i = 0; i < 17; i++) {
        cout << "<>";
      }
    } //end if( menuOption == 1)  

    // Menu option to display building graphic
    else if ( menuOption == 2) {
      int numSections;
      int sectionHeight = 2;   // The minimum section height consisting of 2 rows 

      // The building graphic is based on user's input of the number of building sections 
      cout << "Number of building sections -> ";
      cin >> numSections;

      // How far to the right each section will be. It is the number of sections + the 2 lines that form the 
      // bottom-most base of the entire builiding. Each section is closer to the left by 1 space
      int shiftSize = numSections + 2;    

      // The top peak of the building is in all variations of the building, even if user chooses 0 sections
      cout << endl
           << setfill(' ') << setw( shiftSize + 3) << "/\\\n"
           << setfill(' ') << setw( shiftSize + 3) << "||\n"
           << setfill(' ') << setw( shiftSize + 3) << "||\n"
           << setfill(' ') << setw( shiftSize + 3) << "--\n"
           << setfill(' ') << setw( shiftSize + 4) << "|++|\n"
           << setfill(' ') << setw( shiftSize + 4) << "====\n";

      // Repeat a design for each building section
      for ( int section = 0; section < numSections; section++) {

        /* Each row consists of a series of 1) "|", 2) left side ":", 3) "\", 4) middle ":", 5) "/", 6) right 
        side ":", and 7) "|". Altogether the slashes are meant to form a big X, the "|" are the edges, and the 
        ":" are space filler characters. The "/" and "\" characters may switch sides and the number of ":" 
        changes with each row 
        An example of a section looks like this:  |\::::/|
                                                  |:\::/:|
                                                  |::\/::|
                                                  |::/\::|
                                                  |:/::\:|
                                                  |/::::\| */
        for ( int row = 0; row < sectionHeight; row++) {
          cout << setfill(' ') << setw( shiftSize) << "|";  // Shifts row to the right

          /* The backslash '\' character is a signal to the system that the next character is something
          special.  When we want the backslash character itself to be displayed, we must put two
          backslash characters in a row, as illustrated below.  */ 
          if ( row < sectionHeight / 2) {   // The upper half of the X has "\" followed by "/"

            // All the equations in following setw() are formulas derived for the pattern. They give us the 
            // correct number of spaces to fill per row and section
            cout << setfill(':') << setw( row + 1)
                 << "\\"
                 << setfill(':') << setw( sectionHeight - (2 * row) - 1)
                 << "/"
                 << setfill(':') << setw( row + 1);
          } 
          else {   // The lower half of the X  has "/" followed by "\"
            cout << setfill(':') << setw( sectionHeight - row)
                 << "/"
                 << setfill(':') << setw( (2 * row) - sectionHeight + 1)
                 << "\\"
                 << setfill(':') << setw( sectionHeight - row);
          }

          cout << "|" << endl;
        } // end inner for loop( each row in section)

        // The base of the section
        cout << setfill(' ') << setw( shiftSize)       
             << "/"
             << setfill('-') << setw( sectionHeight + 1)   // Equation for number of spaces to fill with '-'
             << "\\" << endl;

        sectionHeight += 2;  // The next section's height gets taller by 2 rows
        shiftSize--;         // The next section is shifted to the left 1 space
      } // end outer for loop ( each section in building)

      // The final base for the entire building has 2 unique rows
      cout << setfill(' ') << setw( shiftSize);
      for (int i = 0; i <= sectionHeight + 1; i++) {    
        cout << ".";  
      } 
      cout << endl;

      for (int i = 0; i <= sectionHeight + 3; i++) {      
        cout << "+";    
      }
      cout << endl;
    } //end if( menuOption == 2) 
    
    cout << endl;
    return 0;
}
