#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Pair {
    string hand;
    int score;
    int bid;
    Pair(string h, int s, int b) : hand(h), score(s), bid(b) {}
};

int findType(string s) {
    map<char, int> occurances;
    int jokers = 0;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == 'J') {
            jokers++;
            continue;
        }
        if(!occurances[s[i]]) {
            occurances[s[i]] = 1;
        } else {
            occurances[s[i]]++;
        }
    }
    int max = 0;
    int pairs = 0;
    bool has3 = false;
    bool has2 = false;
    for(map<char,int>::iterator it = occurances.begin(); it != occurances.end(); ++it) {
        
        int number = it->second;
        if(number > max) {
            max = number;
        }
        if(number == 2) {
            has2 = true;
        }
        if(number == 3) {
            has3 = true;
        }
        if(number >= 2) {
            pairs++;
        }
    }
    if(max + jokers >= 4) {
        return max + jokers + 2;
    }
    if((has3 && has2) || (has3 && jokers >= 1) || (has2 && jokers >= 2) || (pairs == 2 && jokers >= 1)) {
        return 5;
    }
    if(max + jokers == 3) {
        return 4;
    }
    return pairs + jokers <= 2 ? pairs + jokers + 1 : 3;

}

vector<Pair> readPairs() {
    vector<Pair> pairs;
    ifstream file("input.txt");
    string line;
    while(getline(file, line)) {
        pairs.push_back(Pair(line.substr(0, 5), findType(line.substr(0, 5)), stoi(line.substr(6))));
    }
    return pairs;
}

bool isSmaller(Pair a, Pair b) {
    if(a.score != b.score) {
        return a.score < b.score;
    }
    for(int i = 0; i < a.hand.size(); i++) {
        char charA = a.hand[i];
        char charB = b.hand[i];
        if(charA != charB) {
            if(isdigit(charA)) {
                if(isdigit(charB)) {
                    return charA < charB;
                } else {
                    return charB != 'J';
                }
            } else {
                if(isdigit(charB)) {
                    return charA == 'J';
                } else {
                    if(charA == 'J' || charB == 'J') {
                        return charA == 'J';
                    }
                    return charA > charB;
                }
            }
        }
    }
    return false;
}

// insertion sort
void sort(vector<Pair> &vec) {
    for(int i = 1; i < vec.size(); i++) {
        for(int j = i; j > 0; j--) {
            if(isSmaller(vec[j - 1], vec[j])) {
                break;
            }
            Pair tmp = vec[j - 1];
            vec[j - 1] = vec[j];
            vec[j] = tmp;
        }
    }
}

int main() {
    vector<Pair> pairs = readPairs();
    sort(pairs);
    int winnings = 0;
    for(int i = 0; i < pairs.size(); i++) {
       winnings += (i + 1) * pairs[i].bid;
    }
    cout << winnings << endl;
    return 0;
}