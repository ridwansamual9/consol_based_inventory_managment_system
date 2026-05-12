#include <iostream>
#include <string>
#include <cctype> // for toupper, tolower
#include <fstream>

/*************************************/
using namespace std;
// Convert string to uppercase
string toUpper(string str) {
    for (char &c : str) c = toupper(c);
    return str;
}
// Convert string to lowercase
string toLower(string str) {
    for (char &c : str) c = tolower(c);
    return str;
}
/*****************************************/

///comuter attribute continer
struct computer {
    string name;
    string brand;
    string comGeneration;
    float price = 0;
    int stock = 0;
    int id = 0;
    computer* next = NULL;
};
//global pointer
computer* start = NULL;

// Function declarations
void saveData();              // Save  data to file
void inputTheSaveData();      // Load inventory data from file
void reCorrectId();           // Reset IDs sequentially
void addComputer();           // Add a new computer record
void upDate();                // Update an existing record
void deleteByID();            // Delete a computer record
void display();               // Display all computer records
void display(computer* temp); // Display a single computer record
void serchTheComp();          // Search for a computer
void totalStock();            // Display total stock
void deveOfThisProg();        // Developer details

/* The following functions were developed with the assistance of ChatGPT.
 Sorting in a linked list can be challenging, and while we considered 
 using bubble sort, it is not efficient.
 Therefore, we utilized ChatGPT's help to implement a more efficient sorting method for the linked list.
*/
void mergeSortingByName(computer** headRef); // Sort computers by name using merge sort
void splitList(computer* source, computer** frontRef, computer** backRef); // Split linked list for merge sort
computer* sortedMerge(computer* a, computer* b); // Merge sorted linked lists
bool getValidatedFloat(float &var, string prompt); // Validate float input
bool getValidatedInt(int &var, string prompt); // Validate integer input
void freeMemory();    //free allocated memory
int main() {
     //Load existing data from the file when the program starts.
    inputTheSaveData();
    cout << "Welcome to the Computer Inventory System"<<endl;
    bool stop = true;
   // Main menu loop. Continues until the user chooses to exit.
    do {cout << "==========================";
        cout << "\n1: Add new computer\n"
             << "==========================\n" 
             << "2: Display all records\n"
             << "==========================\n"
             << "3: Update a computer\n"
             << "==========================\n"
             << "4: Search computer\n"
             << "==========================\n"
             << "5: Delete a computer\n"
             << "==========================\n"
             << "6: Sort computers by name\n"
             << "==========================\n"
             << "7: Show total stock\n"
             << "==========================\n"
             << "8: Save \n"
             << "==========================\n"
             << "9: Exit From The Program \n"
             << "==========================\n";
        int option;
       // Get a validated integer input from the user.
         getValidatedInt(option, "Enter your choice as a number olny: ");
                cout << "==========================\n"
                 << "**************************\n";
      // Main menu loop. Continues until the user chooses to exit.
        switch (option) {
            case 1: addComputer();
             break;
            case 2: display();
             break;
            case 3: upDate();
             break;
            case 4: serchTheComp();
             break;
            case 5: deleteByID();
             break;
            case 6:
                if (start == NULL) {
                    cout << "List is empty. Cannot sort.\n\n\n";
                }
                else {
                  // Sort the list by name and then re-assign IDs.
                    mergeSortingByName(&start);
                    reCorrectId();
                    cout << "Sorted by name.\n\n\n";
                }
                break;
            case 7: totalStock(); 
             break;
            case 8: saveData(); 
             break;
            case 9: {
                // Exit the program: set stop flag to false and free allocated memory
                stop =false; freeMemory();}
             break;
            default: cout << "Invalid option. Try again.\n\n";
             break;
        }
    }while (stop!=false);
    deveOfThisProg();
    return 0;
}

bool getValidatedFloat(float &var, string prompt) {
    cout << prompt;
    while (!(cin >> var)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please " << prompt;
    }
    return true;
}

bool getValidatedInt(int &var, string prompt) {
    cout << prompt;
    while (!(cin >> var)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please "<< prompt;
    }
    return true;
}

void saveData() {
    if (start == NULL) {
        cout << "List is empty. Nothing to save.\n";
        return;
    }
    ofstream fout("computers.txt");
    computer* temp = start;
    while (temp != NULL) {
        fout << temp->name << '\n'
             << temp->brand << '\n'
             << temp->comGeneration << '\n'
             << temp->price << '\n'
             << temp->stock << '\n';
        temp = temp->next;
    }
    fout.close();
   cout << "Data saved.\n\n\n\n";
}

void inputTheSaveData() {
    ifstream fin("computers.txt");
    if (!fin.is_open()) return; // If file can't be opened, exit function
    while (!fin.eof()) { // Read data from file until end
        computer* temp = new computer;
        getline(fin, temp->name);
        getline(fin, temp->brand);
        getline(fin, temp->comGeneration);
        fin >> temp->price;
        fin >> temp->stock;
        fin.ignore();
        if (temp->name.empty()) {
            delete temp;
            break;
        }
        temp->next = NULL;
        if (start == NULL) {
            start = temp;
        } else {
            computer* t = start;
            while (t->next != NULL) t = t->next;
            t->next = temp;
        }
        
    }
    fin.close(); //close reader 
    reCorrectId(); //in this step this function add id number for the save data that input
}
void reCorrectId() {
    int i = 1; //to set id
    computer* temp = start;
    // Traverse the entire linked list
    while (temp != NULL) {
        // Assign sequential IDs starting from 1
        temp->id = i++;
        // Move to next node
        temp = temp->next;
    }
}
void addComputer() {
    // Create new node for the computer
    computer* temp = new computer;
    cin.ignore(); // Clear input buffer
    // Get computer details from user with blank space 
    cout << "Enter computer name: ";
    getline(cin, temp->name); 
    cout << "Enter brand: ";
    getline(cin, temp->brand);
    cout << "Enter generation: ";
    getline(cin, temp->comGeneration); 
    // Get validated numerical inputs
    getValidatedFloat(temp->price, "Enter price: ");
    getValidatedInt(temp->stock, "Enter stock quantity: ");
    // Initialize next pointer
    temp->next = NULL;
    // Add to end of linked list
    
    if (start == NULL) {
        // If list is empty, set as first node
        start = temp;
    } else {
        // Otherwise traverse to end and append
        computer* t = start;
        while (t->next != NULL) t = t->next;
        t->next = temp;
    }
    //  reassign IDs
       reCorrectId();
    cout << "added successfully\n\n" << endl;
}
void display() {
    // Check if inventory is empty
    if (start == NULL) {
        cout << "Inventory is empty.\n\n\n";
        return;
    }
    // Start from the first node
    computer* temp = start;
    // Traverse through the entire linked list
    while (temp != NULL) {
        // Display details of current computer using helper function
        display(temp);
        // Move to next node
        temp = temp->next;
    }
}
// This function displays the details of a single computer node.
void display(computer* temp) {
    cout << "\n-------------------------------------\n";
    cout << "ID: " << temp->id << '\n';                     // Display unique ID
    cout << "Name: " << temp->name << '\n';                 // Display computer name
    cout << "Brand: " << temp->brand << '\n';               // Display brand
    cout << "Generation: " << temp->comGeneration << '\n';  // Display generation info
    cout << "Price: $" << temp->price << '\n';              // Display price
    cout << "Stock: " << temp->stock << '\n';               // Display stock quantity
    cout << "-------------------------------------\n";
}
// This function updates a computer record in the linked list by its ID
void upDate() {
 computer* temp = start;
int id;
    if (start == NULL) { 
        // If the list is empty, inform the user and stop
        cout << "List is empty. Nothing to update.\n\n\n";
        return;
    }
    else if(start->next==NULL)
    { 
    cout << "\nonly one computer is in the inventory\n";
     cout << "the computer name is " <<start->name<< endl;
          temp=start;
             id=1;
    }
    else{
    getValidatedInt(id,"Enter ID to update: ");
    // Search for the computer with the given ID
    while (temp != NULL && temp->id != id)
        temp = temp->next;

    if (temp == NULL) {
        // If not found, show message and return
        cout << "Computer not found.\n\n\n";
        return;
    }
       }
    // If found, show update options
    bool stop = false;
    int opt;
    do {
        cout << "\nUpdate Menu for ID " << id << ":\n"
             << "1. Name\n"
             << "2. Brand\n"
             << "3. Generation\n"
             << "4. Price\n"
             << "5. Stock\n"
             << "6. Exit\n";
        getValidatedInt(opt,"Enter choice: ");
        switch (opt) {
            case 1: {
                cin.ignore();                         // Clear newline from input buffer
                cout << "New name: ";
                getline(cin, temp->name);             // Read new name
            } break;
            case 2: {
                cin.ignore();
                cout << "New brand: ";
                getline(cin, temp->brand);            // Read new brand
            } break;
            case 3: {
                cin.ignore();
                cout << "New generation: ";
                getline(cin, temp->comGeneration);    // Read new generation
            } break;
            case 4:
                // Validate and update price
                getValidatedFloat(temp->price, "New price: ");
                break;
            case 5:
                // Validate and update stock
                getValidatedInt(temp->stock, "New stock: ");
                break;
            case 6:
                // Exit update menu
                stop = true;
                break;
            default:
                cout << "Invalid option.\n\n";         // Handle invalid menu option
        }
    } while (!stop);  // Repeat until user chooses to exit
}
// This function deletes a computer record from the linked list based on the entered ID
void deleteByID() {
    // Check if the list is empty
    if (start == NULL) {
        cout << "List is empty. Nothing to delete.\n\n\n";
        return;
    }
    int id;
    getValidatedInt(id,"Enter ID to delete: ");
    // Initialize pointers for current node and previous node
    computer *temp = start, *prev = NULL;
    // Traverse the list to find the node with the matching ID
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    // If not found, show message and exit
    if (temp == NULL) {
        cout << "Computer not found.\n\n\n";
        return;
    }
    // If the node to delete is the first node
    if (temp == start) {
        start = start->next;
    } else {
        // Skip over the node to remove it from the list
        prev->next = temp->next;
    }
    // Delete the node and update ID counter
    delete temp;
    reCorrectId(); // Update IDs after deletion
    cout << "Computer deleted.\n\n\n";
}
// This function searches the list either by ID or by name and displays the matching computer
void serchTheComp() {
    // Check if the list is empty
    if (start == NULL) {
        cout << "List is empty. Nothing to search.\n\n\n";
        return;
    }
    else if(start->next==NULL)
     { 
      display(start);
      return;
     }
    int option;
     getValidatedInt(option,"Search by 1. ID or 2. Name? ");
    // Search by ID
    if (option == 1) {
        int id; 
       getValidatedInt(id,"Enter ID: ");
        computer* temp = start;
        // Traverse to find the matching ID
        while (temp != NULL && temp->id != id)
            temp = temp->next;

        if (temp != NULL)
            display(temp);  // Found, display the node
        else
            cout << "Not found.\n\n";
    // Search by Name
    } else if (option == 2) {
        string name;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);  // Accept full name with spaces
        computer* temp = start;
        // Traverse to find the matching name
        while (temp != NULL && temp->name != name)
            temp = temp->next;
            
        if (temp != NULL)
            display(temp);  // Found
        else
            cout << "Not found.\n\n";
    }
    else {
        cout << "Invalid choice.\n\n";
    }
}
// This function calculates and displays the total number of all computer units in stock.
void totalStock() {
    if (start == NULL) {
        cout << "List is empty. Stock is 0." << endl << endl;
        return;
    }
    int total = 0;
    computer* temp = start;
    // Traverse the linked list and sum up the stock of each computer
    while (temp != NULL) {
        total += temp->stock;
        temp = temp->next;
    }
    // Output the total stock
    cout << "Total stock: " << total << endl << endl;
}
// This function sorts a linked list alphabetically by computer name using merge sort algorithm.
// It uses recursion to split and merge the list.
void mergeSortingByName(computer** headRef) {
    // Base case: list is empty or has only one element
    if (*headRef == NULL || (*headRef)->next == NULL)
        return;

    computer* a;
    computer* b;
    // Split the list into 'a' and 'b' sublists
    splitList(*headRef, &a, &b);
    // Recursively sort the sublists
    mergeSortingByName(&a);
    mergeSortingByName(&b);
    // Merge the two sorted sublists back into one
    *headRef = sortedMerge(a, b);
}
// This function splits the source linked list into front and back halves
// using the fast/slow pointer strategy. It updates frontRef and backRef.
void splitList(computer* source, computer** frontRef, computer** backRef) {
    computer* slow = source;
    computer* fast = source->next;
    // Move 'fast' two nodes, and 'slow' one node each time
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    // 'slow' is before the midpoint
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL; // Split the list
}
// This function merges two sorted linked lists into one,
// based on alphabetical order of the 'name' field.
computer* sortedMerge(computer* a, computer* b) {
    // Base cases
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;

    computer* result;
      //To remove key sencetivity give the variable lowercase computer name
        string nameA = toLower(a->name);
        string nameB = toLower(b->name);
    // Choose the smaller name and recurse
    if (nameA <= nameB) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}
// This function frees (deletes) all dynamically allocated memory in the linked list
void freeMemory() {
    computer* temp;
    while (start != NULL) {
        temp = start;           // Save current node
        start = start->next;    // Move to the next node
        delete temp;            // Delete the saved node
    }
}
void deveOfThisProg() //display group member of this assignment project
{
cout <<"==========================================" << endl;
    cout << "THIS PROGRAM DEVELOPED BY GROUP " <<endl; 
 cout<< "Member of group               id\n"  
     << "1.Dehnnet Abebe              BDU1512449 \n" 
     << "2.Redwan Samual              BDU1512452 \n"  
     << "3.Hassen Addis               BDU1512438 \n"  
     << "4.Chernet Dessie             BDU1411192 \n" 
     << "5.Melkamu Addis              BDU1700754 \n" 
     << "6.Kidus desalegn             BDU1512411 \n"; 
cout <<"==========================================" << endl;
}