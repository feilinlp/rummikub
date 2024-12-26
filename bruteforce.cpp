#include <bits/stdc++.h>
#include "bruteforce.h"
#include "card.h"
#include "group.h"
#include "commonsort.h"
#include "sequencesort.h"

using namespace std;


// Inclusive-Exclusive
void insertCards(vector<Group> &groups, vector<Card> &cards, int start, int end) {
    Group add;
    for (int i = end - 1; i >= start; i--) {
        add.cards.push_back(cards[i]);
        cards.erase(cards.begin() + i);
    }
    groups.push_back(add);
}

vector<Group> bfSolve(vector<Card> cards) {
    vector<Group> groups;
    sort(cards.begin(), cards.end(), commonSort);

    // Create groups by number
    int count = 1;
    for (int i = cards.size() - 2; i >= 0; i--) {
        if (cards[i].number == cards[i + 1].number && cards[i].color != cards[i + 1].color) {
            count += 1;
        } else {
            if (count >= 3) {
                insertCards(groups, cards, i, i + count);
            }
            count = 1;
        }
    }

    if (count >= 3) {
        insertCards(groups, cards, 0, count);
    }

    sort(cards.begin(), cards.end(), sequenceSort);

    // Create groups by color / sequential numbers
    count = 1;
    for (int i = cards.size() - 2; i >= 0; i--) {
        if (cards[i].color == cards[i + 1].color && cards[i].number + 1 == cards[i+1].number) {
            count += 1;
        } else {
            if (count >= 3) {
                insertCards(groups, cards, i, i + count);
            }
            count = 1;
        }
    }

    if (count >= 3) {
        insertCards(groups, cards, 0, count);
    }

    return groups;
}
