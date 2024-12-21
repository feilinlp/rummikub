#include <bits/stdc++.h>
#include "card.h"
#include "bruteforce.h"
#include "dynamicprogramming.h"
#include "astar.h"
#include "commonsort.h"
#include "sequencesort.h"

using namespace std;

vector<Card> cards;

void setColor(string color = "reset") {
    map<string, int> codes;
    codes["reset"] = 0;
    codes["red"] = 31;
    codes["black"] = 30;
    codes["blue"] = 34;
    codes["yellow"] = 33;

    cout << "\033[" << codes[color] << "m";
}

void menu() {
    cout << "---- MENU ----" << endl;
    cout << "1. Add a card" << endl;
    cout << "2. Remove a card" << endl;
    cout << "3. Solve" << endl;
    cout << "4. Display cards (common)" << endl;
    cout << "5. Display cards (sequence)" << endl;
    cout << "6. Exit" << endl;
    cout << "Select Action: ";
}

void display() {
    cout << "Existing Cards: ";
    for (auto card: cards) {
        setColor(card.color);
        cout << card.number << " ";
    }
    cout << endl;

    setColor();
}

void process(int action) {
    if (action == 1) {
        int number;
        string color;

        cout << "Enter the number: ";
        cin >> number;
        cout << "Enter the color (red, black, blue, yellow): ";
        cin >> color;

        cards.push_back({number, color});

        setColor(color);
        cout << number << " ";
        setColor();
        cout << "is added." << endl;
    } else if (action == 2) {
        display();

        int number;
        string color;
        cout << "Card number to remove: ";
        cin >> number;
        cout << "Card color to remove (red, black, blue, yellow): ";
        cin >> color;

        const Card card = {number, color};
        int index = find(cards.begin(), cards.end(), card) - cards.begin();
        if (cards[index] == card) {
            cards.erase(cards.begin() + index);

            setColor(color);
            cout << number << " ";
            setColor();
            cout << "is removed." << endl;
        } else {
            cout << "Card not found." << endl;
        }
    } else if (action == 3) {
        // To solve with Brute Force
        vector< pair<Card, int> > groups = bfSolve(cards);

        // To solve with DP / dynamic programming
        // vector< pair<Card, int> > groups = dpSolve(cards);

        // To solve with A*
        // vector< pair<Card, int> > groups = aSolve(cards);

    } else if (action == 4) {
        sort(cards.begin(), cards.end(), commonSort);
        display();
    } else if (action == 5) {
        sort(cards.begin(), cards.end(), sequenceSort);
        display();
    }
}

int main()
{
	// ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
    int action;
    do {
        menu();
        cin >> action;
        process(action);
        cout << endl;
    } while (action != 6);
}
