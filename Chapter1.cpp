#include <iostream>
#include "linkedList.cpp"
#include "hashTable.cpp"
#include "graphics.cpp"
#include <string>
#include <vector>
#include <bitset>
#include <stdlib.h>
#include <time.h>
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
    int n_char = 1000;
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
        y[i] = (avarage + time)/i;
        // y[i] = time;
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
        // y[i] = (avarage + time)/i;
        y[i] = time;
        x[i] = (double)i;
    }
    saveImage("question_1_2.png", x, y);
}

int main(){
    // question1_1();
    question_1_2();
    return 0;
}

