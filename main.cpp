//last names list from: https://www.powershellgallery.com/packages/TelligentCommunitySample/0.1.1/Content/Surnames.txt
//firs names list from: https://www.usna.edu/Users/cs/roche/courses/s15si335/proj1/files.php%3Ff=names.txt.html
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>


using namespace std;

struct Node
{
  Node* next = NULL;
  char firstName[100];
  char lastName[100];
  char gpa[100];
  char id[100];
};

int hashFunction(char* input, int size);
Node* add(char* input, Node* hashTable[], int size);
void print(char* input, Node* hashTable[], int size);
void remove(char* input, Node* hashTable[], int size);
void random(char* input, Node* hashTable[], int size, vector<char*> &firstNames, vector<char*> &lastNames);
vector<char*> createList(const char* fileName);

int main() 
{
  vector<char*> firstNames = createList("firstNames.txt");
  vector<char*> lastNames = createList("lastNames.txt");
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
    if(strcmp(input, "random") == 0)
    {
      
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

Node* add(char* input, Node* hashTable[], int size)
{
  Node* student = new Node();
  cout << "Enter first name" << endl;
  cin.getline(input, 100);
  strcpy(student->firstName, input);
  cout << "Enter last name" << endl;
  cin.getline(input, 100);
  int hashValue = hashFunction(input, size);
  cout << "Enter GPA" << endl;
  cin.getline(input, 100);
  strcpy(student->gpa, input);
  cout << "Enter ID" << endl;
  cin.getline(input, 100);
  strcpy(student->id, input); 

  if(hashTable[hashValue] == NULL)//if index is empty
  {
    hashTable[hashValue] = student;
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
      current->next = student; //new node added to end of linked list
      return NULL;
    }
    else
    {
      //rehash
      size = size*2;
      Node* newHashTable[size] = {NULL};


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

void random(char* input, Node* hashTable, vector<char*> &firstNames, vector<char*> &lastNames)
{
  cout << "How many random students?" << endl;
  cin.getline(input, 100);
  for(int i = 0; i < atoi(input); i++)
  {
    int r;
    srand(time(NULL));
    r = rand()%(firstNames.size() - 1);
    Node* student = new Node();
    strcpy(student->firstName, firstNames[r]); //first name = random first name from list
    r = rand()%(firstNames.size() - 1);
    strcpy(student->lastName, lastNames[r]); //last name = random last name from list
    //do id and gpa
  }
}

vector<char*> createList(const char* fileName)
{
  vector<char*>list;
  ifstream file(fileName);
  string line;
  if(!file.is_open())
  {
    cout << "Could not open file" << endl;
  }
  while (getline(file, line))
  {
    char* c = new char[100];
    line.erase(remove(line.begin(), line.end(), '\r'), line.end()); //remove \r from end of string
    strcpy(c, line.c_str());
    list.push_back(c);
  }
  return list;
}