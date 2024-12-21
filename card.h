#ifndef CARD_H
#define CARD_H

#include <bits/stdc++.h>

struct Card {
    int number;
    std::string color;

    bool operator==(const Card& r) const {
        return (this->number == r.number) && (this->color == r.color);
    }
};

#endif // CARD_H

