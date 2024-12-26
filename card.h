#ifndef CARD_H
#define CARD_H

#include <bits/stdc++.h>

using namespace std;

struct Card {
    char number;
    string color;

    bool operator==(const Card& r) const {
        return (this->number == r.number) && (this->color == r.color);
    }
};

#endif // CARD_H

