//last names list from: https://www.powershellgallery.com/packages/TelligentCommunitySample/0.1.1/Content/Surnames.txt
//firs names list from: https://www.usna.edu/Users/cs/roche/courses/s15si335/proj1/files.php%3Ff=names.txt.html
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>
//#include <algorithm>


using namespace std;

struct Node
{
  Node* next = NULL;
  char firstName[100];
  char lastName[100];
  float gpa;
  char id[100];
};

int hashFunction(char* input, int size);
Node** add(char* input, Node** hashTable, int &size);
void print(char* input, Node** hashTable, int size);
void remove(char* input, Node** hashTable, int size);
void random(char* input, Node** hashTable, int size, vector<char*> &firstNames, vector<char*> &lastNames);
vector<char*> createList(const char* fileName);

int main() 
{
  vector<char*> firstNames = createList("firstNames.txt");
  vector<char*> lastNames = createList("lastNames.txt");
  Node** pHashTable = new Node*[100]; //pointer to array of Node pointers
  for(int i = 0; i < 100; i++) pHashTable[i] = NULL;
  char input[100];
  int size = 100;
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
      if(add(input, pHashTable, size) != NULL)
      {
        pHashTable = add(input, pHashTable, size);
      }
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
      random(input, pHashTable, size, firstNames, lastNames);
    }
  }
}

int hashFunction(char* input, int size)
{
  cout << "size:" << size << endl;
  int hashValue = 0;
  for(int i = 0; i < strlen(input); i++)
  {
    //cout << "ascii: " << int(input[i]) << endl; 
    hashValue += int(input[i]); //add ascii values lolol 
  }
  cout << "hash value is: " << hashValue << endl;
  hashValue = hashValue % size; //remainder of hashvalue divided by size of pHashTable
  cout << "hash value is: " << hashValue << endl;
  return hashValue;
}

Node** add(char* input, Node** pHashTable, int &size)
{
  Node* student = new Node();
  cout << "Enter first name" << endl;
  cin.getline(input, 100);
  strcpy(student->firstName, input);
  cout << "Enter last name" << endl;
  cin.getline(input, 100);
  cout << "Enter GPA" << endl;
  cin.getline(input, 100);
  student->gpa = atof(input);
  cout << "Enter ID" << endl;
  cin.getline(input, 100);
  strcpy(student->id, input); 
  int hashValue = hashFunction(input, size);
  cout << "called1" << endl;
  //Node* ht = *pHashTable;
  if(pHashTable[hashValue] == NULL)//if index is empty
  {
    cout << "called2" << endl;
    
    pHashTable[hashValue] = student;
    return NULL;
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
      return NULL;
    }
    else
    {
      //rehash
      size = size*2;
      Node* newpHashTable[size]; //new hashTable twice the size
      for(int i = 0; i < size; i++) //go through entire old HashTable
      {
        if(pHashTable[i] != NULL)
        {
          Node* current = pHashTable[i];
          while(current->next != NULL)
          {
            current = current->next;
          }
          newpHashTable[hashFunction(current->lastName, size)] = current; //add current node to new pHashTable at the new hashvalue index
        }
      }
      return newpHashTable;
    }
    return NULL;
  }
}

void print(char* input, Node** pHashTable, int size)
{
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

void random(char* input, Node** pHashTable, vector<char*> &firstNames, vector<char*> &lastNames)
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
    float f = 5.0;
    f = float(rand())/float(RAND_MAX) * f;
    cout << "gpa: " << f << endl;
    student->gpa = f;
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
    //line.erase(remove(line.begin(), line.end(), '\r'), line.end()); //remove \r from end of string
    strcpy(c, line.c_str());
    list.push_back(c);
  }
  return list;
}