//last names list from: https://www.powershellgallery.com/packages/TelligentCommunitySample/0.1.1/Content/Surnames.txt
//firs names list from: https://www.usna.edu/Users/cs/roche/courses/s15si335/proj1/files.php%3Ff=names.txt.html
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

void random(int &gpa, char* input, Node** pHashTable, int &size, char** firstNames, char** lastNames);
int hashFunction(char* input, int size);
void add(Node* student, Node** pHashTable, int &size);
void print(char* input, Node** pHashTable, int size);
void remove(char* input, Node** pHashTable, int size);
char** createList(const char* fileName);


int main() 
{
  char** firstNames = createList("firstNames.txt");
  char** lastNames = createList("lastNames.txt");
  Node** pHashTable = new Node*[100]; //pointer to array of Node pointers
  for(int i = 0; i < 100; i++) pHashTable[i] = NULL; //set all pointers in array to null
  char input[100];
  int size = 100;
  int id = 1;
  cout << fixed << setprecision(2);
  while(strcmp(input, "quit") != 0)
  {
    cout << "Enter ADD, PRINT, DELETE, RANDOM, or QUIT" << endl;
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
      add(student, pHashTable, size);
    }
    if(strcmp(input, "print") == 0) //print out all elements in pHashTable
    {
      print(input, pHashTable, size);
    }
    if(strcmp(input, "delete") == 0)
    {
      remove(input, pHashTable, size);
    }
    if(strcmp(input, "random") == 0)
    {
      random(id, input, pHashTable, size, firstNames, lastNames);
    }
  }
}

int hashFunction(char* input, int size)
{
  //cout << "size:" << size << endl;
  int hashValue = 0;
  for(int i = 0; i < strlen(input); i++)
  {
    //cout << "ascii: " << int(input[i]) << endl; 
    hashValue += int(input[i]); //add ascii values lolol 
  }
  //cout << "hash value is: " << hashValue << endl;
  hashValue = hashValue % size; //remainder of hashvalue divided by size of pHashTable
  //cout << "hash value is: " << hashValue << endl;
  return hashValue;
}

void add(Node* student, Node** pHashTable, int &size)
{
  int hashValue = hashFunction(student->lastName, size);
  if(pHashTable[hashValue] == NULL)//if index is empty
  {
    pHashTable[hashValue] = student;
  }
  else
  {
    int count = 0;
    Node* current = pHashTable[hashValue];
    while(current->next != NULL)
    {
      current = current->next;
      count++;
    }
    if(count < 3) //if theres less than 3 nodes already in this index
    {
      current->next = student; //new node added to end of linked list
    }
    else
    {
      //rehash
      size = size*2;
      Node** newpHashTable = new Node*[size]; //new hashTable twice the size
      for(int i = 0; i < size; i++) //go through entire old HashTable
      {
        if(pHashTable[i] != NULL)
        {
          Node* current = pHashTable[i];
          while(current->next != NULL)
          {
            add(current, newpHashTable, size);  //add current node to new pHashTable at the new hashvalue index
            Node* temp = current;
            current = current->next;
            temp->next = NULL; 
          }
          newpHashTable[hashFunction(current->lastName, size)] = current; //add current node to new pHashTable at the new hashvalue index
        }
      }
      pHashTable = newpHashTable;
    }
  }
}

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

void remove(char* input, Node** pHashTable, int size)
{
  cout << "ID of person you want to delete?" << endl;
  cin.getline(input, 100);
  int hashValue = hashFunction(input, size);
  Node* current = pHashTable[hashValue];
  if(current->next == NULL) //if first node is only node at this index
  {
    cout << "1" << endl;
    pHashTable[hashValue] = NULL;
    delete current;
  }
  else
  {
    while(current->next != NULL)
    {
      if(current->id == atoi(input))
      {
        //current->previous->next = NULL;
        delete current;
        break;
      }
      current = current->next;
    }
  } 
}

void random(int &id, char* input, Node** pHashTable, int &size, char** firstNames, char** lastNames)
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
    strcpy(student->firstName, firstNames[r]); //first name = random first name from list
    r = rand()%(299);
    strcpy(student->lastName, lastNames[r]); //last name = random last name from list
    float f = 5.0;
    f = float(rand())/float(RAND_MAX) * f;
    cout << "gpa: " << f << endl;
    student->gpa = f;
    student->id = id;
    add(student, pHashTable, size);
  }
}

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