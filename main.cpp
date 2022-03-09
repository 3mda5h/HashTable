#include <iostream>
#include <cstring>

using namespace std;

struct Node
{
  Node* next = NULL;
  char name[100];
  char gpa[100];
  char id[100];
};

int hashFunction(char* input, int size);
Node* hashTable add(char* input, Node* hashTable[], int size);
void print(char* input, Node* hashTable[], int size);
void remove(char* input, Node* hashTable[], int size);

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
      if(add(input, hashTable, sizeof(hashTable)/sizeof(hashTable[0])) != NULL)
      {
        hashTable = add(input, hashTable, sizeof(hashTable)/sizeof(hashTable[0]));
      }
    }
    if(strcmp(input, "print") == 0) //print out all elements in hashtable
    {
      print(input, hashTable, sizeof(hashTable)/sizeof(hashTable[0]));
    }
    if(strcmp(input, "delete") == 0)
    {
      remove(input, hashTable, sizeof(hashTable)/sizeof(hashTable[0]));
    }
  }
}

int hashFunction(char* input, int size)
{
  cout << "size: " << size << endl;
  int hashValue = 0;
  for(int i = 0; i < strlen(input); i++)
  {
    cout << "ascii: " << int(input[i]) << endl; 
    hashValue += int(input[i]); //add ascii values lolol 
  }
  cout << "hash value is: " << hashValue << endl;
  hashValue = hashValue % size; //remainder of hashvalue divided by size of hashtable
  return hashValue;
}

Node* hashTable[] add(char* input, Node* hashTable[], int size)
{
  cout << "Enter name" << endl;
  cin.getline(input, 100);
  int hashValue = hashFunction(input, size);
  Node* newNode = new Node();
  strcpy(newNode->name, input); 
  cout << "Enter GPA" << endl;
  strcpy(newNode->gpa, input);
  cout << "Enter ID" << endl;
  strcpy(newNode->id, input); 

  if(hashTable[hashValue] == NULL)//if index is empty
  {
    hashTable[hashValue] = newNode;
  }
  else
  {
    int count = 0;
    Node* current = hashTable[hashValue];
    while(current->next != NULL)
    {
      current = current->next;
      count++;
    }
    if(count < 3) //theres less than 3 nodes already in this index
    {
      current->next = newNode; //new node added to end of linked list
      return NULL;
    }
    else
    {
      //rehash
      Node* newHashTable[size*2] = {NULL};


      //return new hashtable
    }
  }
}

void print(char* input, Node* hashTable[], int size)
{
  for(int i = 0; i < size; i++)
  {
    if(hashTable[i] != NULL)
    {
      Node* current = hashTable[i];
      while(current->next != NULL)
      {
        cout << current->name << ", " << current->gpa << ", " << current->id << endl;
        current = current->next;
      }
      cout << current->name << ", " << current->gpa << ", " << current->id << endl;
    }
  }
  cout << endl;
}

void remove(char* input, Node* hashTable[], int size)
{
  cout << "ID of person you want to delete?" << endl;
  cin.getline(input, 100);
  int hashValue = hashFunction(input, size);
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
      if(strcmp(current->id, input) == 0)
      {
        //current->previous->next = NULL;
        delete current;
        break;
      }
      current = current->next;
    }
  }
}