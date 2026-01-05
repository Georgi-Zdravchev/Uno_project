


#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>

/////Constants/////
const int DECK_SIZE = 112;
const int DIFFERENT_CARDS_OF_ONE_COLOUR = 13;
const int NUM_OF_CARDS_PER_COLOUR = 26;
const int MAX_PLAYERS = 4;
const int STARTING_CARDS = 7;
const int MAX_ELEMENTS_IN_DISPLAY_ARRAY = 4;
const int MAX_STRING_SIZE = 100;

/////Utility functions/////
void shuffleDeck(int deck[], const int number) {

}

void findCardColour(const int card, char* out) {

}

bool isCardWild(const int card) {

}

void findCardValue(const int card, char* out) {

}

int transformStringToInt(char* input, bool& validNumber) {

}

bool isNumOfPlayersValid(const int players) {

}

int chooseNumOfPlayers() {

}
/////Deck and hand managment/////
void formDeck(int deck[DECK_SIZE]) {

}

void dealCards(int deck[], int hands[][DECK_SIZE], const int players, int& deckIndex, int handSize[]) {

}

void reshuffleDiscardPileIntoDeck(int deck[], int& deckIndex, int discardPile[], int& discardSize, int& currentDeckSize) {

}

int flipFirstCard(const int deck[], int& deckIndex, int discardPile[], int& discardSize) {

}

void drawCard(const int player, int deck[], int& deckIndex, int discardPile[], int& discardSize,
    int& currentDeckSize, int hands[][DECK_SIZE], int handSize[]) {

}

void showHand(const int player, const int hands[][DECK_SIZE], const int handSize[], char* colour, char* value) {

}

void showTopCard(const int card, char* colour, char* value) {

}
/////Card checks/effects/////
bool isSkipCard(const int card) {

}

bool isReverseCard(const int card) {

}
bool isPlusTwoCard(const int card) {

}
bool isPlusFourCard(int card) {

}

bool canPlayCard(const int card, const char currentColour, const int topCard, char* colour, char* value) {

}

bool hasPlayableCard(const int player, const char currentColour, const int topCard,
    const int hands[][DECK_SIZE], const int handSize[], char* colour, char* value) {

}
/////Player actions/////
void playCard(const int player, int cardIndex, int discardPile[], int& discardSize,
    char& currentColour, int hands[][DECK_SIZE], int handSize[], char* colour, char* value) {

}

int getPlayerChoice(const int player, const char currentColour, const int topCard,
    bool& unoDeclared, const int hands[][DECK_SIZE], const int handSize[], char* colour, char* value) {

}

void ifDrawnCardIsPlayable(const int currentPlayer, char& currentColour, const int topCard, char* colour, char* value,
    int& discardSize, int discardPile[], const int drawnIndex, bool& cardPlayed, int hands[][DECK_SIZE], int handSize[]) {

}

void automaticDraw(const int currentPlayer, int deck[], int& deckIndex, int discardPile[], int& discardSize, char* colour, char* value,
    int& currentDeckSize, char& currentColour, const int topCard, bool& cardPlayed, int hands[][DECK_SIZE], int handSize[]) {

}
/////Game mechanics////
void nextPlayer(int& currentPlayer, const bool clockwise, const int numPlayers) {

}

void reverseEffect(int& currentPlayer, bool& clockwise, const int players)
{

}

void skipEffect() {

}

void plusTwoEffect(int targetPlayer, const bool  clockwise, const int players, int deck[],
    int& deckIndex, int discardPile[], int& discardSize, int& currentDeckSize, int hands[][DECK_SIZE], int handSize[]) {


}

void plusFourEffect(int targetPlayer, const bool  clockwise, const int players, int deck[],
    int& deckIndex, int discardPile[], int& discardSize, int& currentDeckSize, int hands[][DECK_SIZE], int handSize[]) {

}

void applyCardEffects(const int topCard, int& advanceCount, int currentPlayer, bool& clockwise, const int players,
    int deck[], int& deckIndex, int discardPile[], int& discardSize, int& currentDeckSize, int hands[][DECK_SIZE], int handSize[]) {

}

void determineColourOfFirstCard(const int topCard, char* colour, char* value,
    char& currentColour, const int hands[][DECK_SIZE], const int handSize[]) {

}
/////Save/Load functions/////
void saveGame(int players, int currentPlayer, bool clockwise, char currentColour, int hands[][DECK_SIZE],
    int deck[], int deckIndex, int currentDeckSize, int discardPile[], int discardSize, int handSize[]) {

}

bool loadGame(int& players, int& currentPlayer, bool& clockwise, char& currentColour, int hands[][DECK_SIZE],
    int deck[], int& deckIndex, int& currentDeckSize, int discardPile[], int& discardSize, int handSize[]) {

}
/////UI functions/////
void homeScreen() {

}

void gameScreen() {

}

bool validateChoice(const char choice) {

}
/////Game initialisation/////
void newGame(int deck[], int players, int& deckIndex, char& currentColour, int hands[][DECK_SIZE], char* colour, char* value,
    int discardPile[], int& discardSize, int& currentDeckSize, int& currentPlayer, bool& clockwise, int handSize[]) {

}

void gameLoop(int discardPile[], int& discardSize, char& currentColour, const int players, char* colour, char* value,
    int deck[], int& deckIndex, int& currentDeckSize, int& currentPlayer, bool& clockwise, int hands[][DECK_SIZE], int handSize[]) {

}

int main()
{
    int currentPlayer = 0;
    bool clockwise = true;
    int players;
    int deck[DECK_SIZE];
    int deckIndex = 0;
    int currentDeckSize = DECK_SIZE;
    int discardPile[DECK_SIZE];
    int discardSize = 0;
    char currentColour;
    int hands[MAX_PLAYERS][DECK_SIZE];
    int handSize[MAX_PLAYERS] = { 0 };
    char colour[MAX_ELEMENTS_IN_DISPLAY_ARRAY], value[MAX_ELEMENTS_IN_DISPLAY_ARRAY];

    return 0;
}