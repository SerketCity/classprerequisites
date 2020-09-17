/*********************************************
*  Name: John Rice
*  Program 6 - takes a list of classes and their prerequisites 
*  from a file, puts them in a graph and lists all the classes
*  with all of their prerequisites
*
*********************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"

using namespace std;

int main()
{
    string tempString;
    string compareString;
    ifstream inputStream;
    int numOfPre;
    Graph classGraph(500);

    inputStream.open("classes.txt");
    if(!inputStream.is_open())
    {
        cout<<"COULD NOT OPEN 'classes.txt'"<<endl;
        exit(0);
    }

    while(!inputStream.eof())
    {
        numOfPre = 0;  //keeps track of prereqs, in case it has none
        compareString = "0";
        inputStream>>tempString;
        while(compareString != "#")
        {
            inputStream>>compareString;
            if(compareString != "#")
            {
                ++numOfPre;
                classGraph.insert(tempString, compareString);
            }
            if(numOfPre == 0)
            {
                classGraph.insert(tempString, "NONE");
            }
        }
    }

    inputStream.close();

    classGraph.print();
    
    char pause;
    cin>>pause;

    return 0;
}