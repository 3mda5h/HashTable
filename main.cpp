//student list but the students are stored in a hashtable and random students can be generated
//Emily MacPherson 3/13/22
//last names list from: https://www.powershellgallery.com/packages/TelligentCommunitySample/0.1.1/Content/Surnames.txt
//first names list from: https://www.usna.edu/Users/cs/roche/courses/s15si335/proj1/files.php%3Ff=names.txt.html
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Node
{
  Node* next = NULL;
  char firstName[100];
  char lastName[100];
  float gpa;
  int id;
};

Node** random(int &gpa, char* input, Node** pHashTable, int &size, char** firstNames, char** lastNames);
unsigned int hashFunction(unsigned int h, int &size);
Node** add(Node* student, Node** pHashTable, int &size);
void print(char* input, Node** pHashTable, int size);
void remove(char* input, Node** pHashTable, int size);
char** createList(const char* fileName);

int main() 
{
  int size = 100;
  char** firstNames = createList("firstNames.txt");
  char** lastNames = createList("lastNames.txt");
  Node** pHashTable = new Node*[size]; //pointer to array of Node pointers
  for(int i = 0; i < size; i++) pHashTable[i] = NULL; //set all pointers in array to null
  char input[100];
  int id = 1;
  cout << fixed << setprecision(2); //show 2 decimal places
  while(strcmp(input, "quit") != 0)
  {
    cout << "Enter ADD, RANDOM, PRINT, DELETE, or QUIT" << endl;
    cin.getline(input, 100);
    for(int i = 0; i < strlen(input); i++)
    {
      input[i] = tolower(input[i]);
    }
    if(strcmp(input, "add") == 0)
    {
      Node* student = new Node();
      cout << "Enter first name" << endl;
      cin.getline(input, 100);
      strcpy(student->firstName, input);
      cout << "Enter last name" << endl;
      cin.getline(input, 100);
      strcpy(student->lastName, input);
      cout << "Enter GPA" << endl;
      cin.getline(input, 100);
      student->gpa = atof(input);
      cout << "Enter ID" << endl;
      cin.getline(input, 100);
      student->id = atoi(input);
      pHashTable = add(student, pHashTable, size);
    }
    if(strcmp(input, "print") == 0) 
    {
      print(input, pHashTable, size);
    }
    if(strcmp(input, "delete") == 0)
    {
      cout << "ID of person you want to delete?" << endl;
      cin.getline(input, 100);
      remove(input, pHashTable, size);
    }
    if(strcmp(input, "random") == 0)
    {
      pHashTable = random(id, input, pHashTable, size, firstNames, lastNames);
    }
  }
}

//https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
unsigned int hashFunction(unsigned int x, int &size)
{
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = (x >> 16) ^ x;
  x = x%size;
  return x;
}

//adds student node to hashtable
Node** add(Node* student, Node** pHashTable, int &size)
{
  student->next = NULL;
  int hashValue = hashFunction(student->id, size);
  if(pHashTable[hashValue] == NULL)//if index is empty
  {
    pHashTable[hashValue] = student;
    return pHashTable;
  }
  else
  {
    int count = 1;
    Node* current = pHashTable[hashValue];
    while(current->next != NULL)
    {
      current = current->next;
      count++;
    }
    if(count < 3) //if theres less than 3 nodes already in this index
    {
      current->next = student; //new node added to end of linked list
      return pHashTable;
    }
    else
    {
      //rehash
      size = size*2;
      Node** newpHashTable = new Node*[size]; //new hashTable twice the size
      for(int i = 0; i < size; i++) newpHashTable[i] = NULL; //set all pointers in array to null
      for(int i = 0; i < size/2; i++) //go through entire old HashTable
      {
        if(pHashTable[i] != NULL)
        {
          Node* current = pHashTable[i];
          add(current, newpHashTable, size); //add current node to new pHashTable at the new hashvalue index
          while(current->next != NULL)
          {
            add(current, newpHashTable, size); 
            current = current->next;
          }
        }
      }
      return newpHashTable;
    }
  }
}

//prints out all students in the hashtable
void print(char* input, Node** pHashTable, int size)
{
  cout << endl;
  for(int i = 0; i < size; i++)
  {
    if(pHashTable[i] != NULL)
    {
      Node* current = pHashTable[i];
      while(current->next != NULL)
      {
        cout << current->firstName << " " << current->lastName << ", " << current->gpa << ", " << current->id << endl;
        current = current->next;
      }
      cout << current->firstName << " " << current -> lastName << ", " << current->gpa << ", " << current->id << endl;
    }
  }
  cout << endl;
}

//removes student with given id
void remove(char* input, Node** pHashTable, int size)
{
  int hashValue = hashFunction(atoi(input), size);
  Node* current = pHashTable[hashValue];
  if(current != NULL)
  {
    if(current->next == NULL) //if first node is only node at this index
    {
      pHashTable[hashValue] = NULL;
      delete current;
      return;
    }
    else
    {
      Node* previous;
      while(current != NULL)
      {
        if(current->id == atoi(input)) 
        {
          previous->next = NULL;
          delete current;
          return;
        }
        previous = current;
        current = current->next;
      }
    }    
  }
  cout << "this ID is not in the list" << endl;
}

//generates certain amount of random students and puts them in the hashtable
Node** random(int &id, char* input, Node** pHashTable, int &size, char** firstNames, char** lastNames)
{
  cout << "How many random students?" << endl;
  cin.getline(input, 100);
  srand(time(NULL));
  for(int i = 0; i < atoi(input); i++)
  {
    id++;
    int r;
    r = rand()%(299);
    Node* student = new Node();
    strcpy(student->firstName, firstNames[r]); //student first name = random first name from list
    r = rand()%(299);
    strcpy(student->lastName, lastNames[r]); //student last name = random last name from list
    float f = 5.0;
    f = float(rand())/float(RAND_MAX) * f;
    student->gpa = f;
    student->id = id;
    pHashTable = add(student, pHashTable, size);
  }
  return pHashTable;
}

//reads file and creates a char pointer array containting the names in the file
char** createList(const char* fileName)
{
  char** list = new char*[300];
  ifstream file(fileName);
  string line;
  if(!file.is_open())
  {
    cout << "Could not open file" << endl;
  }
  int i = 0;
  while (getline(file, line))
  {
    char* c = new char[100];
    strcpy(c, line.c_str());
    list[i] = c;
    i++;
  }
  return list;
}