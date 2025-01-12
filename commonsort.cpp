#include <bits/stdc++.h>
#include "commonsort.h"
#include "card.h"

using namespace std;

bool commonSort(Card f, Card s) {
    if (f.number == s.number) {
        return f.color < s.color;
    }
    return f.number < s.number;
}
