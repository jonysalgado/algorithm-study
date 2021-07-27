#include <iostream>
#include "linkedList.cpp"
#include "hashTable.cpp"
#include <string>
#include <vector>
using namespace std;

bool unique_char_bool(string &s){

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

void question1_1(){
    vector<string> words = {"abcde", "hello", "apple", "kite", "padle"};
	for (auto word : words){
			cout << word << string(": ") << boolalpha << unique_char_bool(word) <<endl;
		}

}


int main(){
    question1_1();
    return 0;
}

