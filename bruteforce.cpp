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

void insert(vector<Group> &groups, Card a, Card b, Card c) {
    Group add;
    add.cards.push_back(a);
    add.cards.push_back(b);
    add.cards.push_back(c);
    groups.push_back(add);
}

void merge(vector<Group> &groups) {
    for (int i = 0; i < groups.size(); i++) {
        for (int j = i + 1; j < groups.size(); j++) {
            Group combined = groups[i] + groups[j];
            if (combined.isValid()) {
                groups.erase(groups.begin() + j);
                groups.erase(groups.begin() + i);
                groups.push_back(combined);
            }
        }
    }
}

bool attach(vector<Group> &groups, Card card) {
    for (int i = 0; i < groups.size(); i++) {
        Group attached;
        copy(groups[i].cards.begin(), groups[i].cards.end(), back_inserter(attached.cards));
        attached.cards.push_back(card);
        if (attached.isValid()) {
            groups.erase(groups.begin() + i);
            groups.push_back(attached);
            return true;
        }
    }
    return false;
}

vector<Card> removeFromGroup(vector<Group> &groups, int group, Card card) {
    Group replace = groups[group];
    groups.erase(groups.begin() + group);

    // Check if still a valid group, else need to iterate for the elements.
    pair< vector<Group>, vector<Card> > replaced = replace.remove(card); 

    // If remaining forms any group, leave as it is.
    groups.insert(groups.end(), replaced.first.begin(), replaced.first.end());

    cout << "Groups" << endl;
    for (int k = 0; k < groups.size(); k++) {
        for (int j = 0; j < groups[k].cards.size(); j++) {
            cout << groups[k].cards[j].number << groups[k].cards[j].color << " ";
        }
        cout << endl;
    }

    return replaced.second;
}

pair< bool, pair< vector<Group>, vector<Card> > > attempt(vector<Card> &attempts, vector<Group> &groups, vector<Card> &cards, int index) {  
    // Try to merge groups that can be connected.
    merge(groups);

    // cout << "Attempting" << cards[index].number << cards[index].color << endl;

    // cout << "Groups" << endl;
    // for (int k = 0; k < groups.size(); k++) {
    //     for (int j = 0; j < groups[k].cards.size(); j++) {
    //         cout << groups[k].cards[j].number << groups[k].cards[j].color << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "Cards" << endl;
    // for (int j = 0; j < cards.size(); j++) {
    //     cout << cards[j].number << cards[j].color << " ";
    // }
    // cout << endl;

    // If  card is attachable to a group, return true.
    if (attach(groups, cards[index])) {
        cards.erase(cards.begin() + index);
        return make_pair(true, make_pair(groups, cards));
    }

    vector< pair<Card, Card> > required = cards[index].require();

    // If attempt to place same card, there should be an easier way / it is impossible.
    if (find(attempts.begin(), attempts.end(), cards[index]) != attempts.end()) return make_pair(false, make_pair(groups, cards));

    Card current = cards[index];
    attempts.push_back(current);

    // Remove current card from cards
    cards.erase(cards.begin() + index);

    // for (int i = 0; i < required.size(); i++) {
    //     cout << "Required Cards " << required[i].first.number << required[i].first.color << required[i].second.number << required[i].second.color << endl;
    // }

    // Iterate through all possible required combinations.
    for (int i = 0; i < required.size(); i++) {
        Card first = required[i].first;
        Card second = required[i].second;
        cout << "Cards" << first.number << first.color << second.number << second.color << endl;

        int firstCard = find(cards.begin(), cards.end(), first) - cards.begin();
        vector<int> firstGroup;

        if (firstCard == cards.size()) {
            for (int j = 0; j < groups.size(); j++) {
                if (groups[j].contain(first)) {
                    firstGroup.push_back(j);
                }
            }
        }

        int secondCard = find(cards.begin(), cards.end(), second) - cards.begin();
        vector<int> secondGroup;

        if (secondCard == cards.size()) {
            for (int j = 0; j < groups.size(); j++) {
                if (groups[j].contain(second)) {
                    secondGroup.push_back(j);
                }
            }
        }

        // Swap first and second card if secondCard is on hand but firstCard is on board.
        if (secondCard != cards.size() && firstCard == cards.size()) {
            int tempCard = firstCard;
            firstCard = secondCard;
            secondCard = tempCard;

            vector<int> tempGroup;
            copy(firstGroup.begin(), firstGroup.end(), back_inserter(tempGroup));
            firstGroup.clear();
            copy(secondGroup.begin(), secondGroup.end(), back_inserter(firstGroup));
            secondGroup.clear();
            copy(tempGroup.begin(), tempGroup.end(), back_inserter(secondGroup));

            Card temp = first;
            first = second;
            second = temp;
        }
    
        sort(firstGroup.begin(), firstGroup.end());
        sort(secondGroup.begin(), secondGroup.end());

        cout << "Required " << firstCard << secondCard << endl;
        cout << "First Group " << endl;
        for (int j = 0; j < firstGroup.size(); j++) {
            cout << firstGroup[j] << " ";
        }
        cout << "\nSecond Group " << endl;
        for (int j = 0; j < secondGroup.size(); j++) {
            cout << secondGroup[j] << " ";
        }
        cout << endl;

        // If there is a ready combination from hand.
        if (firstCard != cards.size() && secondCard != cards.size()) {
            insert(groups, current, first, second);
            if (firstCard < secondCard) {
                cards.erase(cards.begin() + secondCard);
                cards.erase(cards.begin() + firstCard);
            } else {
                cards.erase(cards.begin() + firstCard);
                cards.erase(cards.begin() + secondCard);
            }

            // for (int j = 0; j < 3; j++) {
            //     cout << groups[0].cards[j].number << groups[0].cards[j].color << " ";
            // }
            // cout << endl;
            // for (int j = 0; j < cards.size(); j++) {
            //     cout << cards[j].number << cards[j].color << " ";
            // }
            // cout << endl;

            return make_pair(true, make_pair(groups, cards));
        } else if (firstCard != cards.size() && secondCard == cards.size()) {
            // Take first card from the available hand.
            cards.erase(cards.begin() + firstCard);

            // Iterate through the groups that contain the second required card.
            for (int j = 0; j < secondGroup.size(); j++) {
                // cout << "Inner Groups" << endl;
                // for (int k = 0; k < groups.size(); k++) {
                //     for (int l = 0; l < groups[k].cards.size(); l++) {
                //         cout << groups[k].cards[l].number << groups[k].cards[l].color << " ";
                //     }
                //     cout << endl;
                // }
                // cout << "Inner Cards" << endl;
                // for (int l = 0; l < cards.size(); l++) {
                //     cout << cards[l].number << cards[l].color << " ";
                // }
                // cout << endl;

                // Create a copy in case it is not possible to form sets
                vector<Group> groupsCopy;
                vector<Card> cardsCopy;

                copy(groups.begin(), groups.end(), back_inserter(groupsCopy));
                copy(cards.begin(), cards.end(), back_inserter(cardsCopy));

                vector<Card> replaced = removeFromGroup(groupsCopy, secondGroup[j], second);

                // cout << "Inner Groups" << endl;
                // for (int k = 0; k < groups.size(); k++) {
                //     for (int l = 0; l < groups[k].cards.size(); l++) {
                //         cout << groups[k].cards[l].number << groups[k].cards[l].color << " ";
                //     }
                //     cout << endl;
                // }
                // cout << "Inner Cards" << endl;
                // for (int l = 0; l < cards.size(); l++) {
                //     cout << cards[l].number << cards[l].color << " ";
                // }
                // cout << endl;

                pair< bool, pair< vector<Group>, vector<Card> > > result = make_pair(true, make_pair(groupsCopy, cardsCopy));

                // Keep track of the number of each card in hand.
                vector<int> counts(replaced.size());
                for (int k = 0; k < replaced.size(); k++) {
                    counts[k] = count(cardsCopy.begin(), cardsCopy.end(), replaced[k]);
                }

                // Attempt to place the replaced cards on the board.
                for (int k = 0; k < replaced.size(); k++) {
                    cardsCopy.push_back(replaced[k]);
                    result = attempt(attempts, groupsCopy, cardsCopy, cardsCopy.size() - 1); 
                }

                // for (int k = 0; k < groupsCopy.size(); k++) {
                //     for (int l = 0; l < groupsCopy[k].cards.size(); l++) {
                //         cout << groupsCopy[k].cards[l].number << groupsCopy[k].cards[l].color << " ";
                //     }
                // }
                // cout << endl;

                // Make sure that the number of each card in hand is not more than the original.
                for (int k = 0; k < replaced.size(); k++) {
                    if (counts[k] < count(cardsCopy.begin(), cardsCopy.end(), replaced[k])) {
                        result.first = false;
                        break;
                    }
                }

                // cout << "COND" << result.first << endl;

                // If the cards are all successfully placed, update groups and cards, and return true.
                if (result.first) {
                    insert(groupsCopy, current, first, second);
                    groups.clear();
                    cards.clear();
                    copy(groupsCopy.begin(), groupsCopy.end(), back_inserter(groups));
                    copy(cardsCopy.begin(), cardsCopy.end(), back_inserter(cards));
                    return make_pair(true, make_pair(groups, cards));
                }
            }
            // cards.push_back(current);
            cards.push_back(first);
            // return make_pair(false, make_pair(groups, cards));
        } else {            
            for (int f = 0; f < firstGroup.size(); f++) {
                for (int s = 0; s < secondGroup.size(); s++) {
                    vector<Group> groupsCopy;
                    vector<Card> cardsCopy;

                    copy(groups.begin(), groups.end(), back_inserter(groupsCopy));
                    copy(cards.begin(), cards.end(), back_inserter(cardsCopy));

                    vector<Card> replaced, temp;
                    if (firstGroup[f] == secondGroup[s]) {
                        Group replace = groupsCopy[firstGroup[f]];
                        groupsCopy.erase(groupsCopy.begin() + firstGroup[f]);

                        pair< vector<Group>, vector<Card> > replaced = replace.remove(first, second);
                    } else {
                        if (firstGroup[f] > secondGroup[s]) {
                            replaced = removeFromGroup(groupsCopy, firstGroup[f], first);
                            vector<Card> temp = removeFromGroup(groupsCopy, secondGroup[s], second);
                        } else {
                            replaced = removeFromGroup(groupsCopy, secondGroup[s], second);
                            vector<Card> temp = removeFromGroup(groupsCopy, firstGroup[f], first);
                        }
                        replaced.insert(replaced.end(), temp.begin(), temp.end());
                    }
                    
                    pair< bool, pair< vector<Group>, vector<Card> > > result = make_pair(true, make_pair(groupsCopy, cardsCopy));

                    // Keep track of the number of each card in hand.
                    vector<int> counts(replaced.size());
                    for (int k = 0; k < replaced.size(); k++) {
                        counts[k] = count(cardsCopy.begin(), cardsCopy.end(), replaced[k]);
                    }

                    // Attempt to place the replaced cards on the board.
                    for (int k = 0; k < replaced.size(); k++) {
                        cardsCopy.push_back(replaced[k]);
                        result = attempt(attempts, groupsCopy, cardsCopy, cardsCopy.size() - 1); 
                    }

                    // Make sure that the number of each card in hand is not more than the original.
                    for (int k = 0; k < replaced.size(); k++) {
                        if (counts[k] < count(cardsCopy.begin(), cardsCopy.end(), replaced[k])) {
                            result.first = false;
                            break;
                        }
                    }

                    // If the cards are all successfully placed, update groups and cards, and return true.
                    if (result.first) {
                        insert(groupsCopy, current, first, second);
                        groups.clear();
                        cards.clear();
                        copy(groupsCopy.begin(), groupsCopy.end(), back_inserter(groups));
                        copy(cardsCopy.begin(), cardsCopy.end(), back_inserter(cards));
                        return make_pair(true, make_pair(groups, cards));
                    }
                }
            }
        }
    }
    cards.push_back(current);
    return make_pair(false, make_pair(groups, cards));
}

pair< vector<Group>, vector<Card> > bfSolve(vector<Group> groups, vector<Card> cards) {
    bool updated = true;
    while (updated) {
        updated = false;
        for (int i = 0; i < cards.size(); i++) {
            vector<Card> attempts;

            pair< bool, pair< vector<Group>, vector<Card> > > result = attempt(attempts, groups, cards, i);

            cout << "RESULT\n";
            for (int j = 0; j < groups.size(); j++) {
                for (int k = 0; k < groups[j].cards.size(); k++) {
                    cout << groups[j].cards[k].number << groups[j].cards[k].color << " ";
                }
            }
            cout << endl;
            for (int j = 0; j < cards.size(); j++) {
                cout << cards[j].number << cards[j].color << " ";
            }
            cout << endl;

            if (result.first) {
                updated = true;
                break;
            }
        }
    }

    return make_pair(groups, cards);
}
