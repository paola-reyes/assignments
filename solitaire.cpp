#include <iostream>
#include <cstring>               // For storing + printing card values
#include <ctime>                 // For random card order
using namespace std;


// Global constants
const char CARD_DESIGN = '#';
const int DECK_SIZE = 13;
const int NUM_DECKS = 8;
const int NUM_PILES = 10;


// Class for storing individual card values
class Card {
    public:      
        // Create a new card given a character value
        Card(char cardValue) {            
            this->value = cardValue;
            this->hidden = true; 
            this->nextCard = NULL;
        };
    
        char value;
        bool hidden;
        Card *nextCard;
};


// Class for gameplay
class Solitaire {
    public:
        Solitaire();

        // Functions for game setup
        void shuffle(char *allCards);
        void setCards();
        void setPile(Card* &pile, int pileNum, char *allCards, int &position);
        void printPile(Card *pile);
        void printTableau();

        void printAllPiles();    // for debugging
                         
        // Functions for gameplay
        void addCard(Card* newCard, Card* &pile);
        void moveCard(Card* &oldPile, Card* &newPile);
        void previousCard(Card* card);

        void deal();
        void move();
        void undo();
        void check(Card* set);
        void lookForSet();
        
    private:
        Card *pile1, *pile2, *pile3, *pile4, *pile5, *pile6, *pile7, *pile8, *pile9, *pile10, *hand;    
};  


// for debugging
void Solitaire::printAllPiles() {
    cout << endl << "PILE 1 --> ";
    printPile(pile1);
    cout << "PILE 2 --> ";
    printPile(pile2);
    cout << "PILE 3 --> ";
    printPile(pile3);
    cout << "PILE 4 --> ";
    printPile(pile4);
    cout << "PILE 5 --> ";
    printPile(pile5);
    cout << "PILE 6 --> ";
    printPile(pile6);
    cout << "PILE 7 --> ";
    printPile(pile7);
    cout <<"PILE 8 --> ";
    printPile(pile8);
    cout << "PILE 9 --> ";
    printPile(pile9);
    cout << "PILE 10 -> ";
    printPile(pile10);
    cout << "hand   --> ";
    printPile(hand);  
}


// Initial set up for the solitaire game
Solitaire::Solitaire() {
    // So far they each point to nothing
    pile1 = NULL;
    pile2 = NULL;
    pile3 = NULL;
    pile4 = NULL;
    pile5 = NULL;
    pile6 = NULL;
    pile7 = NULL;
    pile8 = NULL;
    pile9 = NULL;
    pile10 = NULL;
    hand = NULL;    

    setCards();     // Distribute the cards    
}


// For adding brand new cards to piles during the game setup  
void Solitaire::addCard(Card* newCard, Card* &pile) {   
    if (newCard->nextCard == NULL) {
        newCard->nextCard = pile;          // The new card points to the top of the pile
        pile = newCard;                    // The new card becomes the top card in the pile
    }
} // end of addCard()


// Moves cards from one pile to another
void Solitaire::moveCard(Card* &oldPile, Card* &newPile) {

    // Don't move anything if the oldPile is empty
    if (oldPile != NULL) {    
        // For moving a single card from the hand to another pile
        if (oldPile == hand) {
            Card *temp = oldPile;              // Hold on to the value of the newCard 
            oldPile = oldPile->nextCard;       // Make the next card of the old pile its top card
            temp->nextCard = newPile;          // Make the stored newCard point to the new pile
            newPile = temp;                    // Put the newCard on top of the new pile
        }
        // For moving a row of cards from one pile to another
        else {
            

        }
    }
} // end of moveCard()


void Solitaire::previousCard(Card* card) {} // end previousCard()


// Print out all the card values in the pile linked list
void Solitaire::printPile(Card *pile) {
    // If the pile is empty, print a newline
    if (pile == NULL) {
        cout << endl;
    }
    else {
        // Go through the whole list and print each item
        while (pile != NULL) {
            cout << pile->value << " ";
            pile = pile->nextCard;
        }
    }

    cout << endl;
} // end of printPile()


// Shuffle the deck of cards
void Solitaire::shuffle(char *allCards) { 
    int randomNum;
    int temp;
    srand(time(0));     // So rand() can generate a different number every time

    for (int i = 0; i < DECK_SIZE * NUM_DECKS; i++) {
        randomNum = rand() % (DECK_SIZE * NUM_DECKS);   // Choose a random card
  
        // Swap the values of the random card and the current iteration card
        temp = allCards[i];
        allCards[i] = allCards[randomNum];
        allCards[randomNum] = temp;
    }
} // end of shuffle()


// Helper function to setCards(). Distributes card values to a pile
void Solitaire::setPile(Card* &pile, int pileNum, char *allCards, int &position) {
    // The first 4 piles get 6 cards
    if (pileNum >= 1 && pileNum <= 4) {
        for (int i = 0; i < 6; i++) {                     
            Card *newCard = new Card(allCards[position]);     // Make a new card     
            addCard(newCard, pile);                           // Add card to the pile
            position++;                                       // Increment to the next card position in allCards
        }              
    }
    // The next 6 piles get 5 cards
    else if (pileNum >= 5 && pileNum <= 10) {
        for (int i = 0; i < 5; i++) {
            Card *newCard = new Card(allCards[position]);     // Make a new card
            addCard(newCard, pile);                           // Add card to the pile 
            position++;                                       // Increment to the next card position in allCards
        }     
    }
    // The unused cards go to the hand pile
    else {
        int remainder = (DECK_SIZE * NUM_DECKS) - position;

        for (int i = 0; i < remainder; i++) {
            Card *newCard = new Card(allCards[position]);     // Make a new card
            addCard(newCard, pile);                           // Add card to the pile
            position++;                                       // Increment to the next card position in allCards
        }   
    } // end of if-else statement
} // end of setPile()


// Do the card setup for the initial tableau. Randomly distrubte the cards into the piles 
void Solitaire::setCards() {
    // + 1 to include the null at the end of the C string
    char deckOrder[DECK_SIZE + 1] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'};
    char allCards[DECK_SIZE * NUM_DECKS + 1] = {'\0'};    
    int position = 0;       // Keeps track of the card setPile() left off on as it distribtes cards to the next pile. 
                            // position increments inside setPile()    
    
    // Append the deck characters into the empty allCards array for the # of decks we will use
    for (int i = 0; i < NUM_DECKS; i++) {                
        strcat(allCards, deckOrder);
    } 
    
    int x[4] = {1, 2, 3, 4};

    shuffle(allCards);

    // Distribute the cards to each pile
    setPile(pile1, 1, allCards, position);
    setPile(pile2, 2, allCards, position);
    setPile(pile3, 3, allCards, position);
    setPile(pile4, 4, allCards, position);
    setPile(pile5, 5, allCards, position);
    setPile(pile6, 6, allCards, position);
    setPile(pile7, 7, allCards, position);
    setPile(pile8, 8, allCards, position);
    setPile(pile9, 9, allCards, position);
    setPile(pile10, 10, allCards, position);
    setPile(hand, 0, allCards, position);
}


// Distributes a card from the hand pile to each of the other piles
void Solitaire::deal() {
    moveCard(hand, pile1);    // Take a card from the hand pile and put it in pile1
    moveCard(hand, pile2);
    moveCard(hand, pile3);
    moveCard(hand, pile4);
    moveCard(hand, pile5);
    moveCard(hand, pile6);
    moveCard(hand, pile7);
    moveCard(hand, pile8);
    moveCard(hand, pile9);
    moveCard(hand, pile10);
} // end deal()


void Solitaire::lookForSet() {}


int main() {
    Solitaire newGame;

    return 0;
}