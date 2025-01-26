#include <bits/stdc++.h>
#include "card.h"
#include "group.h"
#include "bruteforce.h"
#include "commonsort.h"
#include "sequencesort.h"

using namespace std;

vector<Card> cards;
vector<Group> groups;

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
    cout << "1. Add a card (hand cards)" << endl;
    cout << "2. Add a group (table cards)" << endl;
    cout << "3. Remove a card from hand" << endl;
    cout << "4. Remove a group from table" << endl;
    cout << "5. Solve" << endl;
    cout << "6. Display cards (common)" << endl;
    cout << "7. Display cards (sequence)" << endl;
    cout << "8. Exit" << endl;
    cout << "Select Action: ";
}

void display(vector<Card> cards) {
    for (auto card: cards) {
        setColor(card.color);
        cout << card.number << " ";
    }
    cout << endl;

    setColor();
}

void showResult(vector<Group> groups) {
    for (int i = 0; i < groups.size(); i++) {
        cout << i+1 << ". ";
        display(groups[i].cards);
    }
}

Card readCard() {
    int number;
    string color;

    cout << "Enter the number: ";
    cin >> number;
    cout << "Enter the color (red, black, blue, yellow): ";
    cin >> color;

    Card ret = {number, color};
    return ret;
}

void process(int action) {
    if (action == 1) {
        Card added = readCard();
        cards.push_back(added);

        setColor(added.color);
        cout << added.number << " ";
        setColor();
        cout << "is added." << endl;
    } else if (action == 2) {
        Group add;
        int count;
        cout << "Enter the number of cards in the group: ";
        cin >> count;
        for (int i = 0; i < count; i++) {
            add.cards.push_back(readCard());
        }
        
        if (add.isValid()) {
            groups.push_back(add);
            cout << "Group is successfully added." << endl;
        } else {
            cout << "Group is not valid." << endl;
        }
    } else if (action == 3) {
        display(cards);

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
    } else if (action == 4) {
        showResult(groups);
        int index;
        cout << "Enter the group number to remove: ";
        cin >> index;
        groups.erase(groups.begin() + index - 1);
        cout << "Group " << index << " is successfully removed." << endl;
    } else if (action == 5) {
        pair< vector<Group>, vector<Card> > result = bfSolve(groups, cards);
        showResult(result.first);
        display(result.second);
    } else if (action == 6) {
        sort(cards.begin(), cards.end(), commonSort);
        display(cards);
    } else if (action == 7) {
        sort(cards.begin(), cards.end(), sequenceSort);
        display(cards);
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
    } while (action != 8);
}
