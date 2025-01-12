#include <bits/stdc++.h>
#include "sequencesort.h"
#include "card.h"

using namespace std;

bool sequenceSort(Card f, Card s) {
    if (f.color == s.color) {
        return f.number < s.number;
    } 
    return f.color < s.color;
}
