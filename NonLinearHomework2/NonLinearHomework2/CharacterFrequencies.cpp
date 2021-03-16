#include "CharacterFrequencies.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;


// Initialize empty instance with no characters
CharacterFrequencies::CharacterFrequencies() {}
// Initialize instance with character frequencies from line
CharacterFrequencies::CharacterFrequencies(string line) {
    readString(line);
}
// Read line and add character frequencies to already stored frequencies
void CharacterFrequencies::readString(string line) {
    //Loop through the string, check if the letter exists in frequencies, if not add it and set count to 1
    for (int i = 0; i < line.length(); i++) {
        if (frequencies.size() != 0) {
            for (int j = 0; j < frequencies.size(); j++) {
                if (line.at(i) == frequencies[j].first) {
                    frequencies[j].second++;
                    break;
                }
                else if (j == frequencies.size() - 1) {
                    pair<char, int> addNew(line.at(i), 1);

                    frequencies.push_back(addNew);
                    break;
                }
            }
        }
        else {

            pair<char, int> addNew(line.at(i), 1);

            frequencies.push_back(addNew);
        }
    }
}
// Reset all character frequencies to 0
void CharacterFrequencies::reset() {
    frequencies.clear();
}
// Return the frequency of character c
int CharacterFrequencies::getFrequency(char c) {
    for (int i = 0; i < frequencies.size(); i++) {
        if (frequencies[i].first == c) {
            return frequencies[i].second;
        }
    }

   return 0;
}
// Print the frequencies of all characters with non-zero frequencies to
// the console in the following format:
// r: 4
// o: 8
// w: 2
// n: 2
void CharacterFrequencies::printFrequencies() {
    for (int i = 0; i < frequencies.size(); i++) {
        cout << frequencies[i].first << ": " << frequencies[i].second << endl;
    }
}

int main(){
    string line2 = "Twinkle twinkle little star, how I wonder what you are.";
    cout << line2 << endl;
    CharacterFrequencies line2CharFreq(line2);
    line2CharFreq.printFrequencies();
    line2CharFreq.readString(line2);
    line2CharFreq.printFrequencies();

}