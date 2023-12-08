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
    for(int i = 0; i < s.length(); i++) {
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
    if(max >= 4) {
        return max + 2;
    }
    if(has3 && has2) {
        return 5;
    }
    if(max == 3) {
        return 4;
    }
    return pairs + 1;

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
        char charA = a.hand[i] == 'J' ? 'R' : a.hand[i];
        char charB = b.hand[i] == 'J' ? 'R' : b.hand[i];
        if(charA != charB) {
            if(isdigit(charA)) {
                if(isdigit(charB)) {
                    return charA < charB;
                } else {
                    return true;
                }
            } else {
                if(isdigit(charB)) {
                    return false;
                } else {
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