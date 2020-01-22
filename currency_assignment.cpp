#include <iostream>
using namespace std;

struct Node{

    int value_input;
    int value_notes;
    int value_amount;
    Node *next;
};

void createArray(Node *&value, int input[], int n);
void deleteArray(Node *&value, int n);
void display(Node *&value, int input[], int n, int amount);
void createNode(Node *&value, int input[], int n, int amount);
void processNode(Node *&value, int input[], int n, int amount);

int main(){

    int n = 7;
    int input[7] = {1,2,5,10,20,25,50};
    int amount = 40;

    Node *value;

    createArray(value,input,n);
    createNode(value,input,n,amount);
    processNode(value,input,n,amount);

    display(value,input,n,amount);
    deleteArray(value,n);

    return 0;
}

void createArray(Node *&value, int input[], int n){

    value = new Node[n];
}

void deleteArray(Node *&value, int n){

    delete [] value;
}

void createNode(Node *&value, int input[], int n, int amount){

    for(int i=0;i<n;++i){
        value[i].value_input = input[i];
        value[i].value_notes = 0;
        value[i].value_amount = amount;
        value[i].next = NULL;
    }
}

void processNode(Node *&value, int input[], int n, int amount){

    Node *prevNode;
    Node *newNode;
    int temp_i;

    for(int i = n-1; i>=0; --i){
        prevNode = new Node;
        prevNode->value_input = value[i].value_input;
        prevNode->value_notes = value[i].value_notes;
        prevNode->value_amount = value[i].value_amount;
        prevNode->next = value[i].next;

        value[i].next = prevNode;

        temp_i = i;
        while(temp_i >= 0){
            if(prevNode->value_amount >= prevNode->value_input){
                prevNode->value_amount = prevNode->value_amount - prevNode->value_input;
                prevNode->value_notes++;
            }
            else if(prevNode->value_amount < prevNode->value_input){
                temp_i = temp_i - 1;
                if(temp_i > -1){
                    newNode = new Node;
                    newNode->value_input = value[temp_i].value_input;
                    newNode->value_notes = 0;
                    newNode->value_amount = prevNode->value_amount;
                    newNode->next = NULL;

                    prevNode->next = newNode;
                    prevNode = prevNode->next;
                }
            }
        }
    }
}

void display(Node *&value, int input[], int n, int amount){

    Node *tempNode;
    int *notes = new int[n];
    for(int i = 0; i<n; ++i){
        notes[i] = 0;
    }

    for(int i = 0; i<n; ++i){
        tempNode = value[i].next;
        notes[i] = notes[i] + tempNode->value_notes;
        while(tempNode->next != NULL){
            tempNode = tempNode->next;
            notes[i] = notes[i] + tempNode->value_notes;
        }
    }

    int min_val = -1;
    int temp_val;
    int smallest_index;
    for(int i = 0; i<n; ++i){
        temp_val = notes[i];
        if(min_val == -1){
            min_val = temp_val;
            smallest_index = i;
        }
        else if(temp_val < min_val){
            min_val = temp_val;
            smallest_index = i;
        }
    }

    cout<<"Currency exchange :- "<<amount<<endl<<endl;

    tempNode = value[smallest_index].next;
    cout<<"Currency number = "<<tempNode->value_input<<" x "<<tempNode->value_notes<<" = "<<tempNode->value_input * tempNode->value_notes<<endl;
    while(tempNode->next != NULL){
        tempNode = tempNode->next;
        cout<<"Currency number = "<<tempNode->value_input<<" x "<<tempNode->value_notes<<" = "<<tempNode->value_input * tempNode->value_notes<<endl;
    }

    if(tempNode->next == NULL){
        if(tempNode->value_amount != 0){
            cout<<"Remaining amount that cannot be changed = "<<tempNode->value_amount<<endl;
        }
    }
    cout<<"Total notes = "<<notes[smallest_index]<<endl;

    delete [] notes;
}
