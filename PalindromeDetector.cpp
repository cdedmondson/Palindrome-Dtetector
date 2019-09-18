/*******************************************************************
*
*   file: PalindromeDetector.cpp
*   author: Cameron Edmondson
*   class: CS 2560–C++
*   assignment: program 2
*   date last modified: 09/09/2019
*
*   purpose: This program will read in data from a file given by the
*   user and write output to a separate file also specified by the user.
*   The program will then read in the information from the file,
*   line by line, and determine if the line is a palindrome. A palindrome
*   is any word, phrase, or sentence that reads the same forwards and backwards.
*   Here are some well known palindromes(notice we are ignore casing spacing, and commas ‘,’):
*
*   Example:
*
*   Palindrome Detector:
*   ---------------------------------------------------
*   Enter a file for input to test for palindromes: Input1.txt
*   Enter a file for output to write the results: Output1.txt
*   Processing completed! Check the output file for results.
*
* *****************************************************************/

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>

using namespace std;

bool isPalindrome(char *, int, int);

bool doesFileExist(const string &);

void userInput();

void readDataFromFile(string, string);

//###################################### Is Palindrome Function Begin ############################################
/*
 * Function: isPalindrome
 * Purpose: Takes in each line of file as an array of characters and compares
 * each character from front and back of array and returns true if
 * line is a palindrome and false if line is not a palindrome.
 */
bool isPalindrome(char line[], int j, int i) {

    // Assume line is not palindrome unless proven otherwise
    // Use "j" to point to end of array

    // recursively loop through entire array with "i" pointing to beginning
    // and "j" pointing to end of array, compare each character
    // for equality the moment any character is not equal
    // return false i.e. not a palindrome
    if (line[i] != line[j]) {
        return false;
    }
    if (j == 0) {
        return true;
    }

    return isPalindrome(line, --j, ++i);
}
//###################################### Is Palindrome Function End ##############################################

//####################################### Does File Exist Function Begin##########################################
/*
 * Function: doesFileExist
 * Purpose: Takes file name as parameter and returns
 * true if the file exists else it returns false.
 */
bool doesFileExist(const string &FILENAME) {
    ifstream file(FILENAME.c_str());
    return file.good();
}
//#########################################Does File Exist Function End##########################################

//###########################################User Input Function Begin###########################################
/*
 * Function: userInput
 * Purpose: Prompts user for an input and output name
 */
void userInput() {

    //**************** Variable Declaration Begin **************************

    string inputFileName;    // Create space in memory to hold input file name
    string outputFileName;  // Create space to hold output file name

    //**************** Variable Declaration End **************************

    //**************** Prompt User Begin **************************

    cout << "\n\nPalindrome Detector:";
    cout << "\n----------------------------------------------\n";

    cout << "[+] Provide input file name: "; // Prompt user for file path
    getline(cin, inputFileName);    // Read file as a string from user

    cout << "[+] Please provide file name to write output: ";
    getline(cin, outputFileName);

    //**************** Prompt User End ***************************

    do {
        // If input file does not exist print warning
        // Else file does exist set valid path equal to true
        if (!doesFileExist(inputFileName)) {
            cout << "\n----------------------------------------------";
            cout << "\n[!] unable to open file " + inputFileName;
            cout << "\nPlease provide a valid input file: \n->"; // Prompt user for file name
            cin >> inputFileName;    // Read file as a string from user
        } else {
            readDataFromFile(inputFileName, outputFileName);
        }
    } while (!doesFileExist(inputFileName));

}
//###########################################User Input Function End############################################

//######################################Read Data From File Function Begin#######################################
/*
 * Function: readDataFromFile
 * Purpose: Takes and input file name and output file name as parameters
 * and reads each line of input file checks if it's a palindrome then
 * writes out put to output file.
 */
void readDataFromFile(string inputFileName, string outputFileName) {

    ifstream inputFileStream;    // Create input file stream
    ofstream outputFileStream;    // Create output file stream
    string line;    // Create line variable to hold string input from user

    inputFileStream.open(inputFileName);    // Open input file for reading
    outputFileStream.open(outputFileName.c_str());  // Create output file for writing

    while (getline(inputFileStream, line)) {
        static int count = 0;   // Keep track of line
        transform(line.begin(), line.end(), line.begin(), ::tolower); // Convert all upper case letters to lowercase
        line.erase(remove_if(line.begin(), line.end(), [](unsigned char ch) { return isspace(ch) || ispunct(ch); }),
                   line.end()); // Strip line of all punctuation and spacing
        char char_array[line.size() + 1];   // Create an array of characters for each line
        strcpy(char_array, line.c_str());    // Copy each line into character array
        count++;
        int j = strlen(char_array + 1);
        int i = 0;
        // If line is a palindrome write line count and "is a palindrome" to file
        // else write line count and "is not a palindrome" to file
        if (isPalindrome(char_array, j, i)) {
            outputFileStream << "Line " << count << " is a palindrome" << endl;
        } else {
            outputFileStream << "Line " << count << " is not a palindrome" << endl;
        };

    }

    // Close file streams
    inputFileStream.close();
    outputFileStream.close();

    cout << "[+] Processing complete! Check the output file for results\n\n";

}
//###################################### Read Data From File Function End ########################################


//############################################# Main Function Begin ##############################################
int main() {

    userInput();

    return 0;
}
//############################################# Main Function End ##############################################