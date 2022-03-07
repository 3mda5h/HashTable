#include <iostream>
#include <cstring>

using namespace std;

struct Node
{
  Node* next = NULL;
  char* value;
};

int main() 
{
  Node* hashTable[100] = {NULL}; //array of node pointers
  char input[100];
  while(strcmp(input, "quit") != 0)
  {
    cout << "Enter ADD, PRINT, DELETE, or QUIT" << endl;
    cin.getline(input, 100);
    for(int i = 0; i < strlen(input); i++)
    {
      input[i] = tolower(input[i]);
    }
    if(strcmp(input, "add") == 0)
    {
      cout <<"Enter name" << endl;
      cin.getline(input, 100);
      //hash function
      int hashValue;
      for(int i = 0; i < strlen(input); i++)
      {
        cout << "ascii: " 
        hashValue += int(input[i]); //add ascii values lolol 
      }
      cout << "hash value is: " << hashValue << endl;
      hashValue = 100 % hashValue; //remainder of 100 divided by hashValue?
      cout << "hash value is: " << hashValue << endl;
      Node* newNode = new Node();
      newNode->value = input;
      if(hashTable[hashValue] == NULL)//if index is empty
      {
        hashTable[hashValue] = newNode;
      }
      else
      {
        Node* current = hashTable[hashValue];
        while(current->next != NULL)
        {
          current = current->next;
        }
        current->next = newNode; //new node added to end of linked list
      }
    }
    if(strcmp(input, "print") == 0)
    {
      for(int i = 0; i < sizeof(hashTable); i++)
      {
        Node* current = hashTable[i];
        while(current->next != NULL)
        {
          cout << current->value << ", ";
          current = current->next;
        }
        cout << current->value << endl;
      }
    }
    if(strcmp(input, "delete") == 0)
    {
      cout << "Name of person you want to delete?" << endl;
      cin.getline(input, 100);
      int hashValue;
      for(int i = 0; i < strlen(input); i++)
      {
        hashValue += int(input[i]); //add ascii values lolol 
      }
      hashValue = 100 % hashValue; //remainder of 100 divided by hashValue?
      Node* current = hashTable[hashValue];
      while(current->next != NULL)
      {
        if(strcmp(current->value, input) == 0)
        {
          delete current;
          break;
        }
        current = current->next;
      }
    }
  }
}