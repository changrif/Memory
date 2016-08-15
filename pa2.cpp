//  pa2.cpp
//  Created by Chandler Griffin on 3/20/16.

#include "pa2.hpp"

//Initialize the List Object
List list;
List::List()    {
    start = NULL;
    now = NULL;
    temp = NULL;
}

int main(int argc, char** argv)  {
    //If-Else Statement to test for valid command-line input
    string arg;
    if(argv[1] != NULL) {
        arg = argv[1];
        if(!(arg.compare("best") == 0 || arg.compare("worst") == 0))  {
            cout << "Error, Invalid fit type." << endl;
            return 0;
        }
             
        if(argv[2] != NULL)  {
            cout << "Error, Too many input types given." << endl;
            return 0;
        }
    }
    else   {
        cout << "Error, No fit type given." << endl;
        return 0;
    }
    
    //Create the 32 continuous pages of free space
    int i = 0;
    while(i < 32)   {
        list.CreateList("Free");
        i++;
    }
    
    //Create basic menu
    cout << endl << "1. Add program" << endl
    << "2. Kill program" << endl
    << "3. Fragmentation" << endl
    << "4. Print memory" << endl
    << "5. Exit" << endl;
    
    //Deals with navigating different menu options
    int menuOption = 0;
    while(menuOption != 5)  {
        menuOption = menu();
        
        if(menuOption == 1) {
            list.ReplaceData(argv[1]);
        }
        else if(menuOption == 2)    {
            list.DeleteNode();
        }
        else if(menuOption == 3)    {
            list.Fragment();
        }
        else if(menuOption == 4)    {
            list.PrintList();
        }
    }
    
    return 0;
}

/*
 *  The menu function deals with the "choice" input and applying the correct List function based on user specification
 */
int menu() {
    int choice = 0;
    int counter = 0;
    
    while(choice < 1 || choice > 5) {
        if(counter > 0)    {
            cout << endl << "Please enter a valid menu option (1-5)\n";
        }
        
        cout << endl << "choice - ";
        cin >> choice;
        
        //Checking invalid character input
        if(cin.fail())  {
            cin.clear();
            //numeric_limits<streamsize>::max() to indicate the largest number possible
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        counter++;
        cin.clear();
    }
    
    return choice;
}

/*
 *  List functions that create, edit, and print the list simulating 32 pages of memory. See pa2.hpp file for function descriptions
 */
void List::CreateList(string space) {
    //Initialize node pointer, pointer to the next node, and the node's data
    node* nod = new node;
    nod->next = NULL;  //The Linked List should always end in NULL
    nod->data = space;
    
    //Iterates through the Linked List to input 'space' in the next NULL spot
    if(start != NULL)    {
        now = start;
        //loops through until the end of the list
        while(now->next != NULL)   {
            now = now->next;
        }
        now->next = nod;
    }
    else    {
        //If the first node is empty, 'space' is inputted at the head
        start = nod;
    }
}

bool List::CheckExist(string check)  {
    int num = 0;
    bool exist = false;
    
    now = start;
    while(num < 32) {
        //Checking if the data referenced in the node is equivalent to the 'check' program
        if((now->data).compare(check) == 0)  {
            exist = true;
        }
        
        //Traversing through the array
        if((now->next) != NULL)  {
            now = now->next;
        }
        num++;
    }
    now = start;
    
    return exist; //returns true if check is in the Linked List
}

void List::DeleteNode()  {
    //Prompts user for program to delete
    string delData;
    cout << "Program name - ";
    cin >> delData;
    cout << endl;
    
    //Checks is user-specified program exists, and if so loops through the list to find each instance of the program and replace it with "Free" space
    int counter = 0;
    int num = 0;
    if(list.CheckExist(delData))   {
        now = start;
        while(num < 32) {
            if(now->data.compare(delData) == 0)    {
                now->data = "Free";
                counter++;
            }
            if(now->next != NULL)  {
                now = now->next;
            }
            num++;
        }
        cout << "Program " << delData << " successfully killed, " << counter << " page(s) reclaimed." << endl;
    }
    else    {
        cout << "Error, Program " << delData << " isn't running." << endl;
    }
}

void List::Fragment()   {
    int num = 0;
    int counter = 0;
    bool free = false;
    
    //Loops through to find open fragments of free space
    now = start;
    while(num < 31) {
        //Checks if first instance is free space
        if(start->data.compare("Free") == 0) {
            free = true;
        }
        
        //Checks if the current ('now') node is different from the next node
        if((now->data.compare("Free") != 0) && ((now->next)->data.compare("Free") == 0))   {
            counter++;
        }
        now = now->next;
        num++;
    }
    
    //Checks whether or not the whole Linked List is a free fragment
    if(counter == 0 && free)    {
        counter = 1;
    }
    
    cout << endl << "There are " << counter << " fragment(s)." << endl;
}

void List::PrintList()   {
    int counter = 1;
    cout << endl;
    
    //Loops through the Linked List
    now = start;
    while(now != NULL) {
        cout << now->data << "\t";
        now = now->next;    //
        
        //Each line of memory consists of eight pages in four rows
        if(counter % 8 == 0)  {
            cout << endl;
        }
        counter++;
    }
}

void List::ReplaceData(string fitType) {
    int size = 0;
    int div = 0;
    int pages = 0;
    double mod = 0;
    string program;
    
    //User Input
    cout << "Program name - ";
    cin >> program;
    cin.clear();
    cout << "Program size (KB) - ";
    cin >> size;
    //Checking invalid character input
    if(cin.fail())  {
        cout << endl << "Error, Invalid program size." << endl;
        cin.clear();
        //numeric_limits<streamsize>::max() to indicate the largest number possible
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        return;
    }
    cout << endl;
    
    //Algorithm to find the number of pages needed based on KB size
    mod = size%4;
    div = size/4;
    if(mod == 0)   {
        pages = div;
    }
    else    {
        pages = div + 1;
    }
    
    int counter = 1;
    int maxNumber = 0;
    int minNumber = 1000;
    int number = 0;
    int freeNum = 0;
    int freeIndex = 0;
    int firstIndex = 0;
    
    //Checks if the program exists, fit-type algorithm, and inputs the specified program in a specified number of pages as long as that program is not already in the list and there is enough room to input it.
    if(!(list.CheckExist(program)))    {
        now = start;
        //Worst Fit Algorithm
        if(fitType.compare("worst") == 0) {
            while(counter <= 32) {
                //Checks if the node is free
                if(now->data.compare("Free") != 0)    {
                    now = now->next;
                    counter++;
                }
                else    {
                    freeNum = 0;
                    firstIndex = counter-1;
                    //Loops through data that is free
                    while((now->data.compare("Free") == 0) && (now->next != NULL || counter == 32)) {
                        freeNum++;
                        if(counter != 32)   {
                            now = now->next;
                        }
                        counter++;
                    }
                    //Finds largest open fragment
                    if(maxNumber < freeNum)   {
                        maxNumber = freeNum;
                        freeIndex = firstIndex;
                    }
                }
            }
            number = maxNumber;
        }
        
        //Best-Fit Algorithm
        else if(fitType.compare("best") == 0)   {
            while(counter <= 32) {
                //Checks if the node is free
                if(now->data.compare("Free") != 0)    {
                    now = now->next;
                    counter++;
                }
                else    {
                    freeNum = 0;
                    firstIndex = counter-1;
                    //Loops through data that is free
                    while((now->data.compare("Free") == 0) && (now->next != NULL || counter == 32)) {
                        freeNum++;
                        if(counter != 32)   {
                            now = now->next;
                        }
                        counter++;
                    }
                    //Finds smallest open fragment that will fit the program
                    if(minNumber > freeNum && freeNum >= pages)   {
                        minNumber = freeNum;
                        freeIndex = firstIndex;
                    }
                }
            }
            number = minNumber;
        }
        
        //Loops through the List until the needed freeIndex
        now = start;
        for(int i = 0; i < freeIndex; i++)   {
            if(now->next != NULL)  {
                now = now->next;
            }
        }
        
        //Checks to make sure there are enough pages for the program
        if(pages <= number && number != 1000)   {
            cout << "Program " << program << " added successfully: " << pages << " page(s) used." << endl;
            //Replaces free space with the new program for a user-specified number of pages
            while(pages > 0) {
                now->data = program;
                if(now->next != NULL)  {
                    now = now->next;
                }
                pages--;
            }
        }
        else    {
            cout << "Error, Not enough memory for Program " << program << "." << endl;
        }
    }
    else    {
        cout << "Error, Program " << program << " is already running." << endl;
    }
}
