/****************************
 *  graph.h
 * 
 *  puts a class identifier in a graph data structure (uses hashing)
 * 
 * *************************/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <cstring>
#include <list>
#include <stack>
#include <queue>

using namespace std;

class Graph
{
    private:
        int numVertices;
        list<string>* adjacencyList;
        int hashFunction(string arg_string);
        void topologicalTool(string arg_vertice, bool visited[], queue<string> &classQueue);
    
    public:
        Graph(int arg_Vertices);
        ~Graph();
        void insert(string arg_base, string arg_pre);
        int search(string arg_string);
        void topologicalSort(string arg_string);
        void print();
};

//constructor 
Graph::Graph(int arg_Vertices)
{
    this->numVertices = arg_Vertices;
    adjacencyList = new list<string>[numVertices];
}

//destructor
Graph::~Graph()
{
    for(int i = 0; i < numVertices; i++)
    {
        string tempString;
        while(adjacencyList[i].size() != 0)
        {
            adjacencyList[i].pop_front();
        }
    }

    delete adjacencyList;
}

//insert function, inserts based on hashing to make it more effecient 
//for effeciency, i essentially reversed the paths of the graph
void Graph::insert(string arg_base, string arg_pre)
{
    int hashValue = hashFunction(arg_base);
    if(adjacencyList[hashValue].size() == 0 || adjacencyList[hashValue].front() == arg_base)
    {
        if(adjacencyList[hashValue].size() == 0)
        {
            adjacencyList[hashValue].push_back(arg_base);
        }
        if(arg_pre != "NONE")
        {
            adjacencyList[hashValue].push_back(arg_pre);
        }    
    }
    else
    {
        int stopValue = hashValue;
        ++hashValue;
        while(adjacencyList[hashValue].size() != 0 && hashValue != stopValue)
        {
            ++hashValue;
            if(hashValue >= numVertices)
            {
                hashValue = 0;
            }
        }
        if(hashValue == stopValue)
        {
            cout<<"TABLE FULL"<<endl;
        }
        else
        {
            if(adjacencyList[hashValue].size() == 0)
            {
                adjacencyList[hashValue].push_back(arg_base);
            }
            if(arg_pre != "NONE")   
            {
                adjacencyList[hashValue].push_back(arg_pre);
            }
        }
    }
}

//hash function, creates a unique hash based on the sum of the characters in the string
int Graph::hashFunction(string arg_item)
{
    int i = arg_item.length();
    char cArray[i+1];
    strcpy(cArray, arg_item.c_str());
    int sum = 0;
    for(int n = 0; n < i; n++)
    {
        int charVal = abs((char) cArray[n]);
        sum += sum + charVal;
    }
    //had some negative numbers spitting out at some points, using abs() just in case
    return abs(sum % 500);
}

//search funtion, searches for the index of a class
int Graph::search(string arg_string)
{
    int returnVal;
    int hashValue = hashFunction(arg_string);
    if(adjacencyList[hashValue].front() == arg_string)
    {
        returnVal = hashValue;
    }
    else
    {
        int stopValue = hashValue;
        do
        {
            ++hashValue;
            if(hashValue >= numVertices)
            {
                hashValue = 0;
            }
        }while(adjacencyList[hashValue].size() == 0 && hashValue != stopValue && adjacencyList[hashValue].front() != arg_string);
        ++hashValue;

        if(adjacencyList[hashValue].front() == arg_string)
        {
            returnVal = hashValue;
        }
        else
        {
            cout<<"404"<<endl;  //this shouldnt ever happen but i was using it for debugging
            cout<<hashValue<<endl;
            exit(0);
        }
    }

    return returnVal;
}

//searches topologically (uses a queue to accomodate for the tweaking of the insert function)
void Graph::topologicalSort(string arg_string)
{
    queue<string> classQueue;

    bool *visited = new bool[numVertices];
    for(int i = 0; i < numVertices; i++)
    {
        visited[i] = false;
    }

    if(visited[search(arg_string)] == false)
    {
        topologicalTool(arg_string, visited, classQueue);
    }

    while(classQueue.empty() == false)
    {
        cout<<classQueue.front()<<" ";
        classQueue.pop();
    }
    cout<<endl;
}

//recrusion funtion that works with topological sort
void Graph::topologicalTool(string arg_vertice, bool visited[], queue<string> &classQueue)
{
    visited[search(arg_vertice)] = true;

    list<string>::iterator i;
    for(i = adjacencyList[search(arg_vertice)].begin(); i != adjacencyList[search(arg_vertice)].end(); ++i)
    {
        if(!visited[search(*i)])
        {
            topologicalTool(*i, visited, classQueue);
        }
    }

    classQueue.push(arg_vertice);
}

//prints the topological sort of all indexes
void Graph::print()
{
    for(int i = 0; i < numVertices; i++)
    {
        if(adjacencyList[i].size() != 0)
        {
            topologicalSort(adjacencyList[i].front());
        }
    }
}

#endif