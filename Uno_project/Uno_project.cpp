
//**
//*
//* Solution to course project # 4
//* Introduction to programming course
//* Faculty of Mathematics and Informatics of Sofia University
//* Winter semester 2025/2026
//*
//* @author Georgi Zdravchev
//* @idnumber 6MI0600558
//* @compiler VC
//*
//* Uno game
//*
//*


#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>

using std::cin, std::cout, std::endl;

/////Constants/////
const int DECK_SIZE = 112;
const int DIFFERENT_CARDS_OF_ONE_COLOUR = 13;
const int NUM_OF_CARDS_PER_COLOUR = 26;
const int MAX_PLAYERS = 4;
const int STARTING_CARDS = 7;
const int MAX_ELEMENTS_IN_DISPLAY_ARRAY = 4;
const int MAX_STRING_SIZE = 100;
const char unoCheck[4] = "uno";

/////Utility functions/////
void shuffleDeck(int deck[], const int number) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(deck, deck + number, gen);
}

void findCardColour(const int card, char* out) {
    //red cards 0-25, green cards 26-51, blue cards 52-77, yellow cards 78-103, wild cards 104-111
    if (!out) {
        return;
    }
    int colour = card / NUM_OF_CARDS_PER_COLOUR;
    switch (colour) {
    case 0:
        out[0] = 'R';
        break;
    case 1:
        out[0] = 'G';
        break;
    case 2:
        out[0] = 'B';
        break;
    case 3:
        out[0] = 'Y';
        break;
    default:
        out[0] = 'W';
        break;
    }
    out[1] = '\0';
}

bool isCardWild(const int card) {
    return (card >= 104);
}

void findCardValue(const int card, char* out) {
    if (!out) {
        return;
    }
    int value = card % DIFFERENT_CARDS_OF_ONE_COLOUR;
    //0-9 numbers, 10 skip, 11 reverse, 12 +2
    if (!isCardWild(card)) {
        if (value < 10) {
            out[0] = '0' + value;
        }
        else if (value == 10) {
            out[0] = 'S';
        }
        else if (value == 11) {
            out[0] = 'R';
        }
        else if (value == 12) {
            out[0] = '+';
            out[1] = '2';
            out[2] = '\0';
            return;
        }
    }
    else {
        //4 is the number of wild cards of each type
        //C stands for card
        if (value < 4) {
            out[0] = 'C';
        }
        else {
            out[0] = 'C';
            out[1] = '+';
            out[2] = '4';
            out[3] = '\0';
            return;
        }
    }
    out[1] = '\0';
}

bool compareStrings(const char* str1, const char* str2) {
    if (!str1 || !str2) {
        return false;
    }

    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        char c1 = str1[i];
        char c2 = str2[i];

        if (c1 >= 'A' && c1 <= 'Z') { 
            c1 += 'a' - 'A';
        }
        if (c2 >= 'A' && c2 <= 'Z') { 
            c2 += 'a' - 'A';
        }

        if (c1 != c2) {
            return false;
        }
        i++;
    }

    return str1[i] == '\0' && str2[i] == '\0';
}


int transformStringToInt(char* input, bool& validNumber) {
    validNumber = true;
    if (!input) {
        return -1;
    }
    int choice = 0;
    int i = 0;
    while (input[i] != '\0') {
        if (input[i] < '0' || input[i] > '9') {
            validNumber = false;
            break;
        }
        choice = choice * 10 + (input[i] - '0');
        i++;
    }
    return choice;
}

bool isNumOfPlayersValid(const int players) {
    return (players >= 2 && players <= 4);
}

int chooseNumOfPlayers() {
    char choice;
    do {
        cout << "Enter number of players (2-4): " << endl;;
        cin >> choice;
        cin.ignore();
    } while (choice < '2' || choice > '4');

    return choice - '0';
}
/////Deck and hand managment/////
void formDeck(int deck[DECK_SIZE]) {
    for (int i = 0; i < DECK_SIZE; i++) {
        deck[i] = i;
    }
    shuffleDeck(deck, DECK_SIZE);
}

void dealCards(int deck[], int hands[][DECK_SIZE], const int players, int& deckIndex, int handSize[]) {
    for (int card = 0; card < STARTING_CARDS; card++) {
        for (int p = 0; p < players; p++) {
            hands[p][handSize[p]] = deck[deckIndex++];
            handSize[p]++;
        }
    }
}

void reshuffleDiscardPileIntoDeck(int deck[], int& deckIndex, int discardPile[], int& discardSize, int& currentDeckSize) {
    int topCard = discardPile[discardSize - 1];
    currentDeckSize = discardSize - 1;
    //put discard cards back in the deck
    for (int i = 0; i < currentDeckSize; i++) {
        deck[i] = discardPile[i];
    }

    shuffleDeck(deck, currentDeckSize);
    deckIndex = 0;

    // Reset discard pile
    discardPile[0] = topCard;
    discardSize = 1;
}

int flipFirstCard(const int deck[], int& deckIndex, int discardPile[], int& discardSize) {
    int card = deck[deckIndex++];
    discardPile[discardSize++] = card;
    return card;
}

void drawCard(const int player, int deck[], int& deckIndex, int discardPile[], int& discardSize,
    int& currentDeckSize, int hands[][DECK_SIZE], int handSize[]) {
        if (deckIndex >= currentDeckSize) {
            reshuffleDiscardPileIntoDeck(deck, deckIndex, discardPile, discardSize, currentDeckSize);
        }
        hands[player][handSize[player]++] = deck[deckIndex++];
}

void showHand(const int player, const int hands[][DECK_SIZE], const int handSize[], char* colour, char* value) {
    if (!colour || !value) {
        return;
    }
    for (int i = 0; i < handSize[player]; i++) {
        findCardColour(hands[player][i], colour);
        findCardValue(hands[player][i], value);
        cout << '[' << i << "] " << colour << value << " ";
    }
    cout << endl;
}

void showTopCard(const int card, char* colour, char* value) {
    if (!colour || !value) {
        return;
    }
    findCardColour(card, colour);
    findCardValue(card, value);
    cout << "Current card: " << colour << value << endl;
}
/////Card checks/effects/////
bool isSkipCard(const int card) {
    return (!isCardWild(card) && (card % DIFFERENT_CARDS_OF_ONE_COLOUR) == 10);
}
bool isReverseCard(const int card) {
    return (!isCardWild(card) && (card % DIFFERENT_CARDS_OF_ONE_COLOUR) == 11);
}
bool isPlusTwoCard(const int card) {
    return (!isCardWild(card) && (card % DIFFERENT_CARDS_OF_ONE_COLOUR) == 12);
}
bool isPlusFourCard(int card) {
    return (isCardWild(card) && (card % DIFFERENT_CARDS_OF_ONE_COLOUR) >= 4);
}

bool canPlayCard(const int card, const char currentColour, const int topCard, char* colour, char* value) {
    char valueTop[MAX_ELEMENTS_IN_DISPLAY_ARRAY];
    findCardColour(card, colour);
    findCardValue(card, value);
    findCardValue(topCard, valueTop);
    return (colour[0] == currentColour || value[0] == valueTop[0] || isCardWild(card));
}

bool hasPlayableCard(const int player, const char currentColour, const int topCard,
    const int hands[][DECK_SIZE], const int handSize[], char* colour, char* value) {
        for (int i = 0; i < handSize[player]; i++) {
            if (canPlayCard(hands[player][i], currentColour, topCard, colour, value)) {
                return 1;
            }
        }
        return 0;
}
/////Player actions/////
void playCard(const int player, int cardIndex, int discardPile[], int& discardSize,
    char& currentColour, int hands[][DECK_SIZE], int handSize[], char* colour, char* value) {
    if (!colour || !value) {
        return;
    }
    int card = hands[player][cardIndex];

    // Add to discard pile
    discardPile[discardSize++] = card;

    // Remove card from hand by shifting remaining cards
    for (int i = cardIndex; i < handSize[player] - 1; i++) {
        hands[player][i] = hands[player][i + 1];
    }
    handSize[player]--;

    // Update current color if wild
    if (isCardWild(card)) {
        do {
            cout << "Choose a color (R/G/B/Y): " << endl;
            cin >> currentColour;
            cin.ignore();
        } while (currentColour != 'R' && currentColour != 'G' &&
            currentColour != 'B' && currentColour != 'Y');
    }
    else {
        findCardColour(card, colour);
        currentColour = colour[0];
    }
    // Display played card
    findCardColour(card, colour);
    findCardValue(card, value);
    cout << ">You used: " << colour << value << endl;
}

int getPlayerChoice(const int player, const char currentColour, const int topCard,
    bool& unoDeclared, const int hands[][DECK_SIZE], const int handSize[], char* colour, char* value) {
    char input[MAX_STRING_SIZE];

    while (true) {
        cout << "Select a card index (0-" << handSize[player] - 1 << ')' << endl;

        cin.getline(input, MAX_STRING_SIZE);
        //check for uno
        if (handSize[player] == 2 && compareStrings(input, unoCheck)) {

            if (unoDeclared) {
                cout << "UNO already declared.\n";
                continue;
            }

            unoDeclared = true;
            cout << "UNO declared!\n";
            continue;
        }
        bool validNumber = true;
        int choice = transformStringToInt(input, validNumber);

        if (validNumber &&
            choice >= 0 && choice < handSize[player] &&
            canPlayCard(hands[player][choice], currentColour, topCard, colour, value)) {
            return choice;
        }

        cout << "Invalid input. Try again.\n";
    }
}

void ifDrawnCardIsPlayable(const int currentPlayer, char& currentColour, const int topCard, char* colour, char* value,
    int& discardSize, int discardPile[], const int drawnIndex, bool& cardPlayed, int hands[][DECK_SIZE], int handSize[]) {
    if (!colour || !value) {
        return;
    }
    char decision;
    do {
        cout << "Play this card? (Y/N): " << endl;
        cin >> decision;
        cin.ignore();
    } while (decision != 'Y' && decision != 'N');

    if (decision == 'Y') {
        playCard(currentPlayer, drawnIndex, discardPile, discardSize, currentColour, hands, handSize, colour, value);
        cardPlayed = true;
    }
}

void automaticDraw(const int currentPlayer, int deck[], int& deckIndex, int discardPile[], int& discardSize, char* colour, char* value,
    int& currentDeckSize, char& currentColour, const int topCard, bool& cardPlayed, int hands[][DECK_SIZE], int handSize[]) {
    if (!colour || !value) {
        return;
    }
    cout << "No playable cards. Drawing a card..." << endl;
    drawCard(currentPlayer, deck, deckIndex, discardPile, discardSize, currentDeckSize, hands, handSize);
    int drawnIndex = handSize[currentPlayer] - 1;
    findCardColour(hands[currentPlayer][drawnIndex], colour);
    findCardValue(hands[currentPlayer][drawnIndex], value);
    cout << "You drew: " << colour << value << endl;

    if (canPlayCard(hands[currentPlayer][drawnIndex], currentColour, topCard, colour, value)) {
        ifDrawnCardIsPlayable(currentPlayer, currentColour, topCard, colour, value, discardSize,
            discardPile, drawnIndex, cardPlayed, hands, handSize);
    }
}
/////Game mechanics////
void nextPlayer(int& currentPlayer, const bool clockwise, const int numPlayers) {
    if (clockwise) {
        currentPlayer = (currentPlayer + 1) % numPlayers;
    }
    else {
        currentPlayer = (currentPlayer - 1 + numPlayers) % numPlayers;
    }
}

void reverseEffect(int& currentPlayer, bool& clockwise, const int players)
{
    clockwise = !clockwise;
    cout << "Direction reversed!" << endl;
}

void skipEffect() {
    cout << "Next player is skipped!" << endl;
}

void plusTwoEffect(int targetPlayer, const bool  clockwise, const int players, int deck[],
    int& deckIndex, int discardPile[], int& discardSize, int& currentDeckSize, int hands[][DECK_SIZE], int handSize[]) {
        cout << "Next player draws 2 cards and is skipped!" << endl;
        drawCard(targetPlayer, deck, deckIndex, discardPile, discardSize, currentDeckSize, hands, handSize);
        drawCard(targetPlayer, deck, deckIndex, discardPile, discardSize, currentDeckSize, hands, handSize);
}

void plusFourEffect(int targetPlayer, const bool  clockwise, const int players, int deck[],
    int& deckIndex, int discardPile[], int& discardSize, int& currentDeckSize, int hands[][DECK_SIZE], int handSize[]) {
    cout << "Next player draws 4 cards and is skipped!" << endl;
    for (int i = 0; i < 4; i++) {
        drawCard(targetPlayer, deck, deckIndex, discardPile, discardSize, currentDeckSize, hands, handSize);
    }
}

void applyCardEffects(const int topCard, int& advanceCount, int currentPlayer, bool& clockwise, const int players,
    int deck[], int& deckIndex, int discardPile[], int& discardSize, int& currentDeckSize, int hands[][DECK_SIZE], int handSize[]) {
    if (isSkipCard(topCard)) {
        skipEffect();
        advanceCount = 2;
        return;
    }
    if (isReverseCard(topCard)) {
        reverseEffect(currentPlayer, clockwise, players);
        if (players == 2) {
            advanceCount = 2; //acts like skip if there are 2 players
        }
        return;
    }
    if (isPlusTwoCard(topCard)) {
        int target = currentPlayer;
        nextPlayer(target, clockwise, players);
        plusTwoEffect(target, clockwise, players, deck, deckIndex, discardPile, discardSize, currentDeckSize, hands, handSize);
        advanceCount = 2;
        return;
    }
    if (isPlusFourCard(topCard)) {
        int target = currentPlayer;
        nextPlayer(target, clockwise, players);
        plusFourEffect(target, clockwise, players, deck, deckIndex, discardPile, discardSize, currentDeckSize, hands, handSize);
        advanceCount = 2;
        return;
    }
}

void determineColourOfFirstCard(const int topCard, char* colour, char* value,
    char& currentColour, const int hands[][DECK_SIZE], const int handSize[]) {
    if (!colour || !value) {
        return;
    }
    if (isCardWild(topCard)) {
        cout << "First card is a Wild!" << endl;
        cout << "Player 1, these are your cards:" << endl;
        showHand(0, hands, handSize, colour, value);
        do {
            cout << "Choose a color (R/G/B/Y): " << endl;
            cin >> currentColour;
            cin.ignore();
        } while (currentColour != 'R' && currentColour != 'G' &&
            currentColour != 'B' && currentColour != 'Y');
    }
    else {
        findCardColour(topCard, colour);
        currentColour = colour[0];
    }
}
/////Save/Load functions/////
void saveGame(int players, int currentPlayer, bool clockwise, char currentColour, int hands[][DECK_SIZE],
    int deck[], int deckIndex, int currentDeckSize, int discardPile[], int discardSize, int handSize[]) {
    std::ofstream file("savegame.txt");
    if (!file) {
        cout << "Failed to save game.\n";
        return;
    }

    file << players << '\n';
    file << currentPlayer << '\n';
    file << clockwise << '\n';
    file << currentColour << "\n\n";

    file << deckIndex << '\n';
    file << currentDeckSize << '\n';
    //deck
    for (int i = 0; i < currentDeckSize; i++)
        file << deck[i] << ' ';

    file << discardSize << '\n';
    //discard pile
    for (int i = 0; i < discardSize; i++)
        file << discardPile[i] << ' ';
    //hand sizes
    for (int i = 0; i < MAX_PLAYERS; i++)
        file << handSize[i] << ' ';
    //hands
    for (int p = 0; p < MAX_PLAYERS; p++) {
        file << p << ": ";
        for (int i = 0; i < handSize[p]; i++)
            file << hands[p][i] << ' ';
        file << '\n';
    }

    file.close();
    cout << "Game saved.\n";
}

bool loadGame(int& players, int& currentPlayer, bool& clockwise, char& currentColour, int hands[][DECK_SIZE],
    int deck[], int& deckIndex, int& currentDeckSize, int discardPile[], int& discardSize, int handSize[]) {
    std::ifstream file("savegame.txt");
    //file doesn't exist
    if (!file) {
        return false;
    }
    
    file >> players;
    file >> currentPlayer;
    file >> clockwise;
    file >> currentColour;

    file >> deckIndex;
    file >> currentDeckSize;

    //deck
    for (int i = 0; i < currentDeckSize; i++)
        file >> deck[i];

    file >> discardSize;
    //discard
    for (int i = 0; i < discardSize; i++)
        file >> discardPile[i];

    //hand sizes
    for (int i = 0; i < MAX_PLAYERS; i++)
        file >> handSize[i];

    //hands
    for (int p = 0; p < MAX_PLAYERS; p++) {
        int index;
        char colon;
        file >> index >> colon;
        for (int i = 0; i < handSize[p]; i++)
            file >> hands[p][i];
    }

    file.close();
    return true;
}
/////UI functions/////
void homeScreen() {
    cout << "---UNO---" << endl << "Choose an action:" << endl;
    cout << "[1] New game " << endl;
    cout << "[2] Load saved game" << endl;
    cout << "[3] Exit" << endl;
}

void gameScreen() {
    cout << "---UNO---" << endl;
    cout << "[1] Save game" << endl;
    cout << "[2] Continue until next turn" << endl;
    cout << "[3] Exit" << endl;
}

bool validateChoice(const char choice) {
    return (choice >= '1' && choice <= '3');
}
/////Game initialisation/////
void newGame(int deck[], int players, int& deckIndex, char& currentColour, int hands[][DECK_SIZE], char* colour, char* value,
    int discardPile[], int& discardSize, int& currentDeckSize, int& currentPlayer, bool& clockwise, int handSize[]) {
    if (!colour) {
        return;
    }
    formDeck(deck);
    dealCards(deck, hands, players, deckIndex, handSize);
    int topCard = flipFirstCard(deck, deckIndex, discardPile, discardSize);

    // Determine starting color
    determineColourOfFirstCard(topCard, colour, value, currentColour, hands, handSize);
}

void gameLoop(int discardPile[], int& discardSize, char& currentColour, const int players, char* colour, char* value,
    int deck[], int& deckIndex, int& currentDeckSize, int& currentPlayer, bool& clockwise, int hands[][DECK_SIZE], int handSize[]) {
    if (!colour || !value) {
        return;
    }
    int topCard = discardPile[discardSize - 1];
    char choice;
    while (true) {
        gameScreen();
        cin >> choice;
        cin.ignore();
        while (!validateChoice(choice)) {
            cout << "Invalid number. Please try again:" << endl;
            cin >> choice;
            cin.ignore();
        }
        if (choice == '1') {
            saveGame(players, currentPlayer, clockwise, currentColour, hands,
                deck, deckIndex, currentDeckSize, discardPile, discardSize, handSize);
            return;
        }
        else if (choice == '3') {
            return;
        }
        else {
            bool cardPlayed = false;
            int advanceCount = 1;
            bool unoDeclared = false;
            showTopCard(topCard, colour, value);
            if (isCardWild(topCard)) {
                cout << "Current colour is: " << currentColour << endl;
            }
            cout << "Player " << currentPlayer + 1 << "'s turn" << endl;
            cout << "Your cards are:" << endl;
            showHand(currentPlayer, hands, handSize, colour, value);
            if (!hasPlayableCard(currentPlayer, currentColour, topCard, hands, handSize, colour, value)) {
                automaticDraw(currentPlayer, deck, deckIndex, discardPile, discardSize, colour, value, currentDeckSize,
                    currentColour, topCard, cardPlayed, hands, handSize);
            }
            else {
                playCard(currentPlayer, getPlayerChoice(currentPlayer, currentColour, topCard, unoDeclared, hands, handSize, colour, value),
                    discardPile, discardSize, currentColour, hands, handSize, colour, value);
                cardPlayed = true;
                // UNO penalty
                if (handSize[currentPlayer] == 1 && !unoDeclared) {
                    cout << "You forgot to say UNO!" << endl;
                    cout << "You drew a card!" << endl;
                    drawCard(currentPlayer, deck, deckIndex,
                        discardPile, discardSize, currentDeckSize, hands, handSize);
                }
            }
            if (handSize[currentPlayer] == 0) {
                cout << "Player " << currentPlayer + 1 << " wins!";
                break;
            }
            if (cardPlayed) {
                topCard = discardPile[discardSize - 1];
                applyCardEffects(topCard, advanceCount, currentPlayer, clockwise, players, deck, deckIndex,
                    discardPile, discardSize, currentDeckSize, hands, handSize);
            }
            for (int i = 0; i < advanceCount; i++) {
                nextPlayer(currentPlayer, clockwise, players);
            }
        }
    }
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
    homeScreen();
    char choice;
    cin >> choice;
    cin.ignore();
    while (!validateChoice(choice)) {
        cout << "Invalid number. Please try again:" << endl;
        cin >> choice;
        cin.ignore();
    }
    if (choice == '3') {
        return 0;
    }
    else if (choice == '2') {

        if (!loadGame(players, currentPlayer, clockwise, currentColour, hands, deck, deckIndex, currentDeckSize,
            discardPile, discardSize, handSize)) {
            cout << "No saved game found, starting new game." << endl;
            players = chooseNumOfPlayers();
            newGame(deck, players, deckIndex, currentColour, hands, colour, value, discardPile, discardSize,
                currentDeckSize, currentPlayer, clockwise, handSize);
        }
        else {
            loadGame(players, currentPlayer, clockwise, currentColour, hands, deck, deckIndex, currentDeckSize, discardPile,
                discardSize, handSize);
            cout << "Game successfully loaded." << endl;
        }
        gameLoop(discardPile, discardSize, currentColour, players, colour, value, deck,
            deckIndex, currentDeckSize, currentPlayer, clockwise, hands, handSize);

    }
    else {
        players = chooseNumOfPlayers();
        newGame(deck, players, deckIndex, currentColour, hands, colour, value, discardPile, discardSize,
            currentDeckSize, currentPlayer, clockwise, handSize);
        gameLoop(discardPile, discardSize, currentColour, players, colour, value, deck, deckIndex,
            currentDeckSize, currentPlayer, clockwise, hands, handSize);
    }
    return 0;
}