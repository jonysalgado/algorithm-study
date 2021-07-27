
#ifndef LINKED_LIST

#define LINKED_LIST
#include <iostream>

class Node {
    public:
        int data;
        Node* next;
};

/* Given a reference (pointer to pointer)
to the head of a list and an int,
inserts a new node on the front of the list. */
void push(Node** head_ref, int new_data){
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
    
    return;
}

void deleteValue(Node** head_ref, int data){

    Node* last = *head_ref;
    Node* aux = new Node();
    if (last->next == NULL){
        *head_ref = NULL;
        return;
    }
    while(last->next != NULL){
        if(last->data == data){
            aux->next = last->next;
            return;
        }
        aux = last;
        last = last->next;
    }
    std::cout << "data was not found." << std::endl;
    return;
}

void insertAfter(Node* prev_node, int new_data){
    if (prev_node == NULL){
        std::cout << "the previous node cannot be NULL";
        return;
    }

    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;

    return;
}

void append(Node** head_ref, int new_data){

    Node* new_node = new Node();

    Node* last = *head_ref;

    new_node->data = new_data;

    new_node->next = NULL;

    if (*head_ref == NULL){
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = new_node;

    return;
}

void printList(Node *node)
{
    while (node != NULL)
    {
        std::cout<<" --> "<<node->data;
        node = node->next;
    }
    std::cout<<std::endl;
}


#endif