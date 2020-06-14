/***************************************************
 * TODO:
 *      in enterBook() erase data if user does not confirm
 *          possible solution change newBook to pointer
 *      implement sorting
 *      clear cin after getlines
 * **************************************************/





#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

struct Book {
    string authorSurname;
    string authorGiven;
    string title;
    bool inSeries;
    string series;
    int placeInSeries;
};

vector<Book> library;

/*
std::string split implementation by using delimiter as a character.
*/
std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

string getBook(Book entry) {
    string fullEntry = entry.authorSurname;
    fullEntry += ", ";
    fullEntry += entry.authorGiven;
    fullEntry += ", ";
    fullEntry += entry.title;
    if (entry.inSeries) {
        fullEntry += ", ";
        fullEntry += entry.series;
        fullEntry += " ";
        fullEntry += entry.placeInSeries;
    }
    return fullEntry;
}

void displayBook(Book entry) {
    cout << getBook(entry) << endl;
}

Book enterBook() {
    Book newBook;
    char confirm;
    
    do {
    //Get Author
    cout << "Author Surname: ";
    cin >> newBook.authorSurname;
    cin.clear();

    cout << "Author Given Names: ";
    getline(cin, newBook.authorGiven);
    cin.clear();

    //Get title
    cout << "Title: ";
    getline(cin, newBook.title);
    cin.clear();

    //Get series
    cout << "Series Placement: ";
    cin >> newBook.placeInSeries;
    cin.clear();
    newBook.inSeries = newBook.placeInSeries;

    if (newBook.inSeries) {
        cout << "Series Name: ";
        getline(cin, newBook.series);
        cin.clear();
    }

    cout << "About to save:\n";
    displayBook(newBook);
    cout << "Are you sure (y/n): ";
    cin >> confirm;
    cin.clear();

    } while (confirm != 'y');

    return newBook;
}

void writeToHTML() {
    ofstream htmlOut("./library/book_List_HTML_Format.txt");

    if (htmlOut.fail())
        cout << "ERROR: Could not find ./library/book_List_HTML_Format.txt\n";
    assert(!htmlOut.fail());

    htmlOut << endl;

    //SORT VECTOR HERE

    for (auto it = library.begin(); it < library.end(); it++) {
        htmlOut << "<li> " << getBook(*it) << " </li>" << endl;
    }
}

void writeToSave() {
    //clear file
    std::ofstream ofs;
    ofs.open("./library/library.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    ofstream saveOut ("./library/library.txt");
    if (saveOut.fail())
        cout << "ERROR: Could not find ./library/library.txt\n";
    assert(!saveOut.fail());

    //SORT VECTOR HERE

    for(auto it = library.begin(); it < library.end(); it++) {
        saveOut << it->authorSurname << "|" << it->authorGiven << "|"
               << it->title;
       if(it->inSeries) 
           saveOut << "|" << it->series << "|" << it->placeInSeries;
        saveOut << endl;
   }
}

void readSaved() {
    ifstream savedIn("./library/library.txt");
    if(savedIn.fail()) {
        cout << "No saved data found.\n";
        return;
    }

    while(!savedIn.eof()) {
        string savedEntry;
        Book entry;
        vector<string> entryVector;
        getline(savedIn, savedEntry);

        entryVector = split(savedEntry, '|');
        
        entry.authorSurname = entryVector[0];
        entry.authorGiven   = entryVector[1];
        entry.title         = entryVector[2];

        if (entryVector.size() > 3) {
            entry.inSeries = 1;
            entry.series = entryVector[3];
            entry.placeInSeries = stoi(entryVector[4]);
        }
        else 
            entry.inSeries = 0;

        library.push_back(entry);
    }
}

void displayPrompt() {
    cout << "Enter N to enter new book.\n"
         << "Enter W to write data to HTML format.\n"
         << "Enter Q to save and quit.\n"
         << "Enter H to display instructions again.\n";
}

int main()
{
    //readSaved();
    char prompt;
    displayPrompt(); 
    do
    {
        cout << ">" ;
        cin >> prompt;
        cin.clear();
        prompt = toupper(prompt);
        switch (prompt)
        {
        case 'N':
            library.push_back(enterBook());
            break;
        case 'W':
            writeToHTML();
            break;
        case 'H':
            displayPrompt();
            break;
        case 'Q':
            writeToSave();
            break;
        default:
            break;
        }
    }while(prompt != 'Q');

    return 0;
}