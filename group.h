#ifndef GROUP_H
#define GROUP_H

#include <bits/stdc++.h>
#include "card.h"
#include "sequencesort.h"

using namespace std;

struct Group {
    vector<Card> cards;
    
    bool contain(Card card) {
        for (int i = 0; i < cards.size(); i++) {
            if (cards[i] == card) {
                return true;
            }
        }
        return false;
    }

    bool isValid() {
        if (cards.size() < 3) return false;

        if (cards[0].number == cards[1].number) {
            set<string> colors;
            for (int i = 0; i < cards.size(); i++) {
                if (cards[i].number != cards[0].number) return false;
                if (colors.find(cards[i].color) != colors.end()) return false;
                colors.insert(cards[i].color);
            }
            return true;
        }

        if (cards[0].color == cards[1].color) {
            sort(cards.begin(), cards.end(), sequenceSort);
            for (int i = 1; i < cards.size(); i++) {
                if (cards[i].color != cards[0].color) return false;
                if (cards[i].number != cards[0].number + i) return false;
            }
            return true;
        }

        return false;
    }

    pair< vector<Group>, vector<Card> > remove(Card card) {
        vector<Group> groups;
        vector<Card> remaining;

        int index = find(cards.begin(), cards.end(), card) - cards.begin();

        if (cards[0].number == cards[1].number && cards.size() > 3) {
            cards.erase(cards.begin() + index);
            groups.push_back(*this);
            return make_pair(groups, remaining);
        } else if (cards[0].number == cards[1].number && cards.size() <= 3) {
            cards.erase(cards.begin() + index);
            return make_pair(groups, cards);
        }
        else {
            sort(cards.begin(), cards.end(), sequenceSort);
            if (cards.size() - index - 1 >= 3) {
                Group right;
                for (int i = cards.size() - 1; i > index; i--) {
                    right.cards.push_back(cards[i]);
                    cards.erase(cards.begin() + i);
                }
                groups.push_back(right);
            }

            cards.erase(cards.begin() + index);

            if (index >= 3) {
                Group left;
                for (int i = 0; i < index; i++) {
                    left.cards.push_back(cards[i]);
                    cards.erase(cards.begin() + i);
                }
                groups.push_back(left);
            }
            return make_pair(groups, cards);
        }
    }

    Group operator+(const Group &other) const {
        Group combined;
        combined.cards.insert(combined.cards.end(), this->cards.begin(), this->cards.end());
        combined.cards.insert(combined.cards.end(), other.cards.begin(), other.cards.end());
        return combined;
    }
};

#endif // GROUP_H

