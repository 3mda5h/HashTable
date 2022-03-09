#include <iostream>
#include <cstring>

using namespace std;

struct Node
{
  Node* next = NULL;
  char value[100];
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
      int hashValue = 0;
      for(int i = 0; i < strlen(input); i++)
      {
        cout << "ascii: " << int(input[i]) << endl; 
        hashValue += int(input[i]); //add ascii values lolol 
      }
      cout << "hash value is: " << hashValue << endl;
      hashValue = hashValue % 100; //remainder of hashvalue divided by 100?
      cout << "hash value is: " << hashValue << endl;
      Node* newNode = new Node();
      strcpy(newNode->value, input); 
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
    if(strcmp(input, "print") == 0) //print out all elements in hashtable
    {
      for(int i = 0; i < sizeof(hashTable)/sizeof(hashTable[0]); i++)
      {
        if(hashTable[i] != NULL)
        {
          Node* current = hashTable[i];
          while(current->next != NULL)
          {
            cout << current->value << ", ";
            current = current->next;
          }
          cout << current->value << ", ";
        }
      }
      cout << endl;
    }
    if(strcmp(input, "delete") == 0)
    {
      cout << "Name of person you want to delete?" << endl;
      cin.getline(input, 100);
      int hashValue = 0;
      for(int i = 0; i < strlen(input); i++)
      {
        cout << "ascii: " << int(input[i]) << endl; 
        hashValue += int(input[i]); //add ascii values lolol 
      }
      cout << "hash value is: " << hashValue << endl;
      hashValue = hashValue % 100; //remainder of 100 divided by hashValue
      cout << hashValue << endl;
      Node* current = hashTable[hashValue];
      if(current->next == NULL) //if first node is only node at this index
      {
        cout << "1" << endl;
        hashTable[hashValue] = NULL;
        delete current;
      }
      else
      {
        while(current->next != NULL)
        {
          if(strcmp(current->value, input) == 0)
          {
            //current->previous->next = NULL;
            delete current;
            break;
          }
          current = current->next;
        }
      }
    }
  }
}