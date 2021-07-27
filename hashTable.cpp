#include "linkedList.cpp"
#include <iostream>

class Hash{
    
    int BUCKET;

    Node** list;

public:

    Hash(int V);

    void insertItem(int x);

    void deleteItem(int key);

    int hashFunction(int x){
        return (x % BUCKET);
    }

    void displayHash();
};


Hash::Hash(int b){
    BUCKET = b;
    list = (Node**)malloc(sizeof(Node)*BUCKET);
}

void Hash::insertItem(int key){
    int index = hashFunction(key);
    append(&list[index], key);

    return;
}

void Hash::deleteItem(int key){

    int index = hashFunction(key);

    Node* aux = new Node();

    deleteValue(&list[index], key);
    
    return;
}

void Hash::displayHash(){
    for(int i=0; i<BUCKET; i++){
        std::cout << i;
        printList(list[i]);
    }

    return;
}



// int main(){

//     int a[] = {15, 11, 27, 8, 12};
//     int n = sizeof(a)/sizeof(a[0]);
//     std::cout << "n = " << n << std::endl;
//     Hash h(n);
//     for (int i = 0; i < n; i++){
//         std::cout << "a[i] = " << a[i] << std::endl;
//         h.insertItem(a[i]);  
//     }
  
//     // delete 12 from hash table
//     h.deleteItem(12);
  
//     // display the Hash table
//     h.displayHash();

//     return 0;
// }