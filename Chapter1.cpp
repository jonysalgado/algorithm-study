//------------------------------------------------------------------------------
// Setup
#include <iostream>
#include "linkedList.cpp"
#include "hashTable.cpp"
#include "graphics.cpp"
#include <string>
#include <vector>
#include <bitset>
#include <stdlib.h>
#include <time.h>
#include <cmath>
using namespace std;


//------------------------------------------------------------------------------
// Question 1.1

bool isUnique_char_bool(string &s){

    if(s.length() > 128){
        return false;
    }
    vector<bool> char_set(128);
    for (int i=0; i < s.length(); i++){
        int val = s[i];
        if (char_set[val]){
            return false;
        }

        char_set[val] = true;
    }
    return true;
}

bool isUnique_char_bitvector(string &s){
    bitset<256> bits(0);
    for(int i=0; i < s.length(); i++){
        int val = s[i];
        if(bits.test(val) > 0){
            return false;
        }
        bits.set(val);
    }
    return true;
}

bool isUnique_char_noDS(string &s){
    for(int i=0; i < s.length(); i++){
        for(int j=i+1; j < s.length(); j++){
            if(s[i] == s[j]){
                return false;
            }
        }
    }
    return true;
}

void question1_1(){
    srand( (unsigned)time(NULL));
    vector<string> words = {"abcde", "hello", "apple", "kite", "padle"};
	for (auto word : words){
			cout << word << string(": ") << boolalpha << isUnique_char_bool(word) <<endl;
		}

    cout <<endl << "Using bit vector" <<endl<<endl;

    for (auto word : words){
        cout << word << string(": ") << boolalpha << isUnique_char_bitvector(word) <<endl;
    }

    cout <<endl << "Using no Data Structure" <<endl<<endl;

    for (auto word : words){
        cout << word << string(": ") << boolalpha << isUnique_char_noDS(word) <<endl;
    }

    cout << endl;
    int n_char = 50000;
    vector<double> x(n_char, 0);
    vector<double> y(n_char, 0);
    for(int i=1; i<n_char; i++){
        string word = randomWord(i);
        clock_t tStart = clock();
        isUnique_char_bool(word);
        double time = (double)(clock() - tStart)/CLOCKS_PER_SEC;
        double avarage = 0;
        for(int j=0; j<i; j++){
            avarage = avarage + y[j];
        }
        // y[i] = (avarage + time)/i;
        y[i] = time;
        x[i] = (double)i;
    }
    saveImage("question_1_1.png", x, y);


    
}

//------------------------------------------------------------------------------
// Question 1.2

bool isPermutation(string s1, string s2){
    if (s1.length() != s2.length()){
        return false;
    }
    vector<int> count_char(128);
    for(char &c: s1){
        count_char[(int)c] ++;
    }

    for(char &c: s2){
        count_char[(int)c] --;
        if (count_char[(int)c] < 0){
            return false;
        }
    }

    int sum = 0;
    for(int &i: count_char){
        sum += abs(i);
    }

    if (sum == 0){
        return true;
    }
    return false;
}

void question_1_2(){
    vector<string> words = {"abcde", "abced", "abced", "abcvdf", "padlee"};
    for (int i=0; i < words.size() - 1; i++){
        cout << words[i] << string(": ") << words[i+1] << string(" --> ") 
         << boolalpha << isPermutation(words[i], words[i+1]) <<endl;
    }

    cout << endl;
    int n_char = 50000;
    vector<double> x(n_char, 0);
    vector<double> y(n_char, 0);
    for(int i=1; i<n_char; i++){
        string s1 = randomWord(i);
        string s2 = randomWord(i);
        clock_t tStart = clock();
        isPermutation(s1, s2);
        double time = (double)(clock() - tStart)/CLOCKS_PER_SEC;
        double avarage = 0;
        for(int j=0; j<i; j++){
            avarage = avarage + y[j];
        }
        y[i] = (avarage + time)/i;
        // y[i] = time;
        x[i] = (double)i;
    }
    saveImage("question_1_2.png", x, y);
}

//------------------------------------------------------------------------------
// Question 1.3

string repleceSpace(string s, int length){
    int n_spaces = (s.length() - length)/2;
    int spaceCount = 0, charCount = 0;
    string result(s.length(), 0);

    for(char &c: s){
        if (c == ' '){
            result[charCount] = '%';
            result[charCount+1] = '2';
            result[charCount+2] = '0';
            charCount += 3;
            spaceCount ++;
        }
        else{
            result[charCount] = c;
            charCount ++;
        }
        if (charCount == result.length()){
            return result;
        }
    }
    return result;

}

void replaceSpaceSolution(string* s, int trueLength){
    int spaceCount = (s->length() - trueLength)/2;
    int index, i = 0;
    
    index = s->length() - 1;
    if (trueLength < s->length())
        s[trueLength] = '\0';
    for (i = trueLength - 1; i >= 0; i--){
        if (s->at(i) == ' '){
            s->at(index - 1) = '0';
            s->at(index - 2) = '2';
            s->at(index - 3) = '%';
            index -= 3;
        }
        else{
            s->at(index - 1) = s->at(i);
            index --;
        }
    }
}

void question_1_3(){
    string words = {"Mr John Smith    "};
    string result = repleceSpace(words, 13);
    cout << "Replace all spaces:" << endl;
    cout << result << endl << endl;

    cout << "Replace all spaces (book solution):" << endl;
    replaceSpaceSolution(&words, 13);
    cout << words << endl << endl;
}


//------------------------------------------------------------------------------
// Question 1.4

bool isValidChar(char c){
    if ((int)c <= (int)'z' && (int)c >= (int)'a')
        return true;
    return false;
}

char putLowerCase(char c){
    if ((int)c <= (int)'Z' && (int)c >= (int)'A'){
        int lower = c - (int)'A' + (int)'a';
        return (char)lower;
    }
    return c;

}

bool isPalindromePermutation(string s){
    bool isOdd;
    int nChars = (int)'z' - (int)'a' + 1;
    int count = 0;
    vector<int> countChars(nChars, 0);
    char aux;
    for(char &c: s){
        aux = putLowerCase(c);
        if(isValidChar(aux)){
            count += 1;
            countChars.at(((int)aux - (int)'a')) += 1;
        }
    }   
    isOdd = (bool)(count % 2);
    bool findNoPair = false;
    for(int i = 0; i < nChars; i++){
        if(countChars.at(i)%2 == 1){
            if(!isOdd)
                return false;
            if(findNoPair){
                return false;
            }
            findNoPair = true;
        }
    }
    return true;
}

int toggle(int bitVector, char c){
    if(!isValidChar(c))
        return bitVector;
    
    int mask = 1 << (int)c;
    if((bitVector & mask) == 0){
        bitVector |= mask;
    }
    else{
        bitVector &= ~mask;
    }
    return bitVector;
}

int createBitVector(string s){
    int bitVector = 0;
    for(char &c: s){
        bitVector = toggle(bitVector, putLowerCase(c));
    }
    return bitVector;
}


bool isPalindromePermutationSolution(string s){
    int bitVector = createBitVector(s);
    return (bitVector & (bitVector - 1)) == 0;
}

void question_1_4(){
    vector<string> words = {"Tact Coa", "asfdsf dsvsfv _ arefw", "abcabcabcd", "abcaBC"};
    cout << "Is Palindrome Permutation?" << endl;
    for(auto &word: words){
        cout << word << string(": ") << boolalpha <<  isPalindromePermutation(word) <<endl;
    }

    cout << endl << "Is Palindrome Permutation? (book solution):" << endl;

    for(auto &word: words){
        cout << word << string(": ") << boolalpha <<  isPalindromePermutationSolution(word) <<endl;
    }
}

//------------------------------------------------------------------------------
// Question 1.5

bool hasOnlyOneWay(string first, string second){
    if(abs((long)(first.length()-second.length())) > 1)
        return false;
    
    string s1 = first.length() < second.length() ? first: second;
    string s2 = first.length() < second.length() ? second: first;

    int idx1 = 0, idx2 = 0;
    bool foundDifference = false;
    while(idx2 < s2.length() && idx1 < s1.length()){
        if(s1[idx1] != s2[idx2]){
            if(foundDifference)
                return false;
            foundDifference = true;
            if(s1.length() == s2.length())
                idx1 ++;
        }
        else
            idx1 ++;
        idx2 ++;
    }
    
    return true;
    
}

void question_1_5(){
    vector<string> words = {"pale", "ple", "pales", "pale", "pale", "bale", "pale", "bake"};

    cout << "Is there only one difference (insert, delete or replace character)?" << endl;
    for(int i=0; i < words.size() - 1; i++){
        cout << words[i] << string(", ") << words[i+1] << string(" --> ") 
            << boolalpha <<  hasOnlyOneWay(words[i], words[i+1]) <<endl;
    }
}

int main(){
    // question1_1();
    // question_1_2();
    // question_1_3();
    // question_1_4();
    question_1_5();
    
    return 0;
}

