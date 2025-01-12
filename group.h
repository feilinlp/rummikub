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

    template<typename... Cards>
    pair<vector<Group>, vector<Card>> remove(Cards... cardsToRemove) {
        vector<Group> groups;
        vector<Card> remaining;

        // Helper lambda to remove a single card
        auto removeCard = [this](const Card& card) {
            auto it = find(cards.begin(), cards.end(), card);
            if (it != cards.end()) {
                cards.erase(it);
            }
        };

        // Remove each card in the variadic arguments
        (removeCard(cardsToRemove), ...);

        if (cards[0].number == cards[1].number) {
            if (this->isValid()) {
                Group add;
                copy(cards.begin(), cards.end(), back_inserter(add.cards));
                groups.push_back(add);
                return make_pair(groups, remaining);
            }
            return make_pair(groups, cards);
        } else {
            sort(cards.begin(), cards.end(), sequenceSort);
            int count = 1;
            for (int i = cards.size() - 2; i >= 0; i--) {
                if (cards[i].number == cards[i+1].number - 1) {
                    count += 1;
                } else {
                    if (count >= 3) {
                        Group insert;
                        for (int j = i + count; j > i; j--) {
                            insert.cards.push_back(cards[j]);
                        }
                        count = 1;
                        groups.push_back(insert);
                    } else {
                        for (int j = i + count; j > i; j--) {
                            remaining.push_back(cards[j]);
                        }
                        count = 1;
                    }
                } 
            }

            if (count >= 3) {
                Group insert;
                for (int j = count - 1; j >= 0; j--) {
                    insert.cards.push_back(cards[j]);
                }
                count = 1;
                groups.push_back(insert);
            } else {
                for (int j = count - 1; j >= 0; j--) {
                    remaining.push_back(cards[j]);
                }
                count = 1;
            }

            return make_pair(groups, remaining);
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

