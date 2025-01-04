#ifndef CARD_H
#define CARD_H

#include <bits/stdc++.h>

using namespace std;

struct Card {
    int number;
    string color;

    bool operator==(const Card &other) const {
        return (this->number == other.number) && (this->color == other.color);
    }

    vector< pair<Card, Card> > require() {
        vector< pair<Card, Card> > ret;

        int number = this->number;
        string color = this->color;

        vector<string> colors = {"red", "blue", "black", "yellow"};
        colors.erase(remove(colors.begin(), colors.end(), color), colors.end());

        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                Card first = {number, colors[i]};
                Card second = {number, colors[j]};
                ret.push_back(make_pair(first, second));
            }
        }

        if (this->number < 12) {
            Card first = {number + 1, color};
            Card second = {number + 2, color};
            ret.push_back(make_pair(first, second));
        } 
        
        if (this->number > 2) {
            Card first = {number - 2, color};
            Card second = {number - 1, color};
            ret.push_back(make_pair(first, second));
        }

        if (this->number > 1 && this-> number < 13) {
            Card first = {number - 1, color};
            Card second = {number + 1, color};
            ret.push_back(make_pair(first, second));
        }

        return ret;
    }
};

#endif // CARD_H

