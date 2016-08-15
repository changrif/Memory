//  pa2.h
//  Created by Charles "Chandler" Griffin on 3/20/16
//  Turned in March 20th, 2016.

#ifndef pa1_h
#define pa1_h

#include <iostream>
#include <string>
#include <cmath>
#include <string>

using namespace std;

//This function deals with the functionality of the main menu and choices
int menu();

/*
 *  This class deals with initializing the variables dealing with traversing, replacing, and creating nodes.
 */
class node  {
    public:
        string data;
        node* next;
};

/*
 *  This class deals with initializing the nodes in the Linked List and the functions that alter the data within it.
 */
class List  {
    private:
        node* start;
        node* now;
        node* temp;
    
    public:
        List();
        //This function initializes the base Linked List with 32 free pages
        void CreateList(string space);
    
        //This function returns whether "check" is currently in the list
        bool CheckExist(string check);
    
        //This function deletes a user-specified program from the list
        void DeleteNode();
    
        //This function prints the number of open fragments
        void Fragment();
    
        //This function prints the current Linked List
        void PrintList();
    
        //This function replaces "Free" with a user-specified program
        void ReplaceData(string fitType);
};

#endif /* pa2_h */