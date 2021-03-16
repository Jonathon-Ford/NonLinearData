/*
Jonathon Ford
NonLinear Data Structors
Professor Kevin Zu
Homework 1

This program reads in a file named input.txt and counts how many times a user specified character appears in the line of text, then tells the user what the idices ofthe positios of the characters

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    fstream inputFile;
    string textLine;
    char character;
    int count = 0;
    vector<int> locations;

    inputFile.open("input.txt");
  
    if (!inputFile.is_open()) {
        cout << "The input file input.txt could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    //Save the line of text to a string
    getline(inputFile, textLine);
    inputFile.close();

    //Recive user letter wanted
    cout << "Enter the character to search for:" << endl;
    cin >> character;

    //Search the line of text for the user specified character
    for (int i = 0; i < textLine.length(); i++) {
        //If the caracter at any i matches the user specifed character, incriment the count and add its location to a vector
        if (textLine.at(i) == character) {
            count++;
            locations.push_back(i);
        }
    }

    if (count != 0) { //if the count is non zero print the occourance of the character and its positions
        cout << "The number of occurrences of the character " << character << " is " << count << endl;
        cout << "The indices of the character positions are ";
        for (int i = 0; i < locations.size(); i++) {
            cout << locations.at(i) << " ";
        }
    }
    else { //Print that the character does not occur
        cout << "The number of occurrences of the character " << character << " is 0" << endl;
    }

}