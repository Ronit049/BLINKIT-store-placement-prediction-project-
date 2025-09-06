#include <bits/stdc++.h>
using namespace std;

void asciiART()
{
//
//    std::cout << R"(
//'########::'##::::'##::'#######::'##::: ##:'########:'########:::'#######:::'#######::'##:::'##:
// ##.... ##: ##:::: ##:'##.... ##: ###:: ##: ##.....:: ##.... ##:'##.... ##:'##.... ##: ##::'##::
// ##:::: ##: ##:::: ##: ##:::: ##: ####: ##: ##::::::: ##:::: ##: ##:::: ##: ##:::: ##: ##:'##:::
// ########:: #########: ##:::: ##: ## ## ##: ######::: ########:: ##:::: ##: ##:::: ##: #####::::
// ##.....::: ##.... ##: ##:::: ##: ##. ####: ##...:::: ##.... ##: ##:::: ##: ##:::: ##: ##. ##:::
// ##:::::::: ##:::: ##: ##:::: ##: ##:. ###: ##::::::: ##:::: ##: ##:::: ##: ##:::: ##: ##:. ##::
// ##:::::::: ##:::: ##:. #######:: ##::. ##: ########: ########::. #######::. #######:: ##::. ##:
//..:::::::::..:::::..:::.......:::..::::..::........::........::::.......::::.......:::..::::..::      
//)" << '\n';
//}
// This is the class for the PhoneBook Data Element.
class Data
{
private:
    string name;
    string number;

public:
    // Constructors
    Data() : name(""), number("") {}                 // NO ARGS
    Data(string a, string b) : name(a), number(b) {} // Parameterised

    // Get Fuctions
    string &getName() { return name; }     // Gets the name of the contact
    string &getNumber() { return number; } // Gets the number of the contact

    // Set Functions
    void setName(string &a) { name = a; }     // Sets the number of the contact
    void setNumber(string &a) { number = a; } // Sets the number of the contact
};

// Doubly Linked List Node Class
class Node
{
private:
    Data elem;  // Stores Data Element
    Node *next; // Stores address to the next Node
    Node *prev; // Stores address to the previous Node

    friend class PhoneBookClass;
};

// Phone Book Class which contains all the fucntions that are required to manupulate a PhoneBook. It is basically a implementation of Doubly Linked List.
class PhoneBookClass
{
public:
    PhoneBookClass();                        // Constructor
    ~PhoneBookClass();                       // Destructor
    bool add(string, string);                // Add a new contact
    bool modify();                           // Modifies the contact
    bool remove(int, string);                // Deletes the contact
    void search();                           // Search for the contact
    void print();                            // Print the PHONEBOOK
    void isEmpty();                          // Checks if phone book is empty
    void numberOfContacts();                 // Prints total number of contacts in the phone book
    bool checkDuplicate(string s, string n); // Checks if the contact already exists
    void resetALL();                         // It deletes all the contacts

private:
    Node *head; // Head Node
};

// Success Message Function
void success(){
    cout << endl;
    cout << "SUCCESS: PHONEBOOK is successfully upadated! Desired changes has been made." << endl;
    
}

// Failure Message Function
void failure()
{
    cout << endl;
    cout << "FAILURE: NO Changes have been made to phone book!" << endl;
    return;
}

// This function takes Input and Validates the number.
string validateAndInputNumber()
{
    string number;
    while (true)
    {
        // Input
        cout << endl;
        cout << "Enter Contact Number:\t";
        cin >> number;

        // Validation
        if (number == "")
        {
            cout << "INVALID INPUT!! A number must contains numeric digits [0-9] only." << endl;
            continue;
        }

        bool ans = true;
        for (char const &c : number) // Validates if all the digits of the number are numeric.
            if (std::isdigit(c) == 0)
            {
                ans = false;
                break;
            }
        if (!ans)
            cout << "INVALID NUMBER!! A number must contains numeric digits [0-9] only." << endl;
        else
            return number;
    }

    // Checks if the length of number is equal to 10 or not.

    // if (str.size() != 10)
    //     ans = false;
    // if (ans == false)
    //     cout << "Invalid Number!! A number must be 10 digits long containting 0-9 digits." << endl;
}

// This function takes input and validates the name.
string validateAndInputName()
{
    // Input and valides the name
    cin.ignore();
    string name;
    while (true)
    {
        cout << endl;
        cout << "Enter Contact Name :\t";
        getline(cin, name);
        if (name == "")
        {
            cout << "INVALID INPUT! NAME CANNOT BE AN EMPTY STRING. TRY AGAIN" << endl;
        }
        else
            break;
    }
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    return name;
}

// Checks if the contact user is trying to insert a contact that is already present.
bool PhoneBookClass::checkDuplicate(string s, string n)
{
    Node *temp = head;
    while (temp != NULL)
    {
        string name = (temp->elem).getName();
        string number = (temp->elem).getNumber();
        if (name == s)
        {
            cout << endl;
            cout << "Contact with similar name already exists." << endl;
            return true;
        }
        if (number == n)
        {
            cout << endl;
            cout << "Contact with similar number already exists." << endl;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// It provides 3 options to the user and they have to choose one of them.
int howDoYouWantFunction(string functionName)
{
    int choice;
    while (true)
    {
        cout << "How do you want to " << functionName << " the contact? Choose one option" << endl;
        cout << "Enter 1: " << functionName << " By Name" << endl;
        cout << "Enter 2: " << functionName << " By Number" << endl;
        cout << "Enter 3: Back to Main Menu" << endl;
        cin >> choice;
        if (choice == 1 || choice == 2 || choice == 3)
            break;
        else
        {
            cout << "INVALID INPUT! PLEASE TRY AGAIN" << endl;
            cout << endl;
            continue;
        }
        cout << endl;
    }
    return choice;
}

// Check if the contact is present in the phone book or not.
void isFound(bool found, int choice, string s, string name, string number)
{
    cout << endl;
    if (!found)
    {
        if (choice == 1)
            cout << "Contact with name " << s << " does not exist." << endl;
        if (choice == 2)
            cout << "Contact with number " << s << " does not exist." << endl;
    }
    else
    {
        cout << "Contact Found!!" << endl;
        cout << "Name\t" << name << endl;
        cout << "Number\t" << number << endl;
    }
}

// This function is for conformation of delete and modifaication number.
bool confirmationDelMod(string functionName)
{
    cout << endl;
    int response;
    cout << "Do you want to " << functionName << " this contact?[Press 1: YES | PRESS 0: NO]" << endl;
    cin >> response;
    return (response == 1);
}

// No Args Constructor
PhoneBookClass::PhoneBookClass() : head(NULL) {}

// Destructor
PhoneBookClass::~PhoneBookClass()
{
    Node *temp = head;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    cout << endl;
    cout << "Destructor Executed Successfully!!" << endl;
}

// This function ADD's new Contact in the PHONEBOOK.
bool PhoneBookClass ::add(string para_Name, string para_Number)
{
    string nam, no;

    if (para_Name == "" && para_Number == "")
    {
        nam = validateAndInputName();
        no = validateAndInputNumber();
    }
    else
        nam = para_Name, no = para_Number;

    // Running Duplicate Check Fucntion
    if (checkDuplicate(nam, no) == true)
    {
        cout << "You cannot create two contact that have same number or name." << endl;
        return false;
    }

    // Creating New Node
    Node *newNode = new Node();
    newNode->elem.setName(nam);
    newNode->elem.setNumber(no);

    Node *temp = head;
    if (head == NULL)
    {
        // At head
        newNode->next = NULL;
        newNode->prev = NULL;
        head = newNode;
    }
    else
    {
        // In between
        string s1;
        Node *tempLast = temp;
        while (temp != NULL)
        {
            s1 = temp->elem.getName();
            if (s1 > nam)
            {
                if (temp->prev != NULL)
                    temp->prev->next = newNode;
                else
                    head = newNode;
                newNode->prev = temp->prev;
                newNode->next = temp;
                temp->prev = newNode;
                return true;
            }
            temp = temp->next;
            if (temp != NULL)
                tempLast = temp;
        }
        // At end
        temp = tempLast;
        newNode->next = NULL;
        newNode->prev = temp;
        temp->next = newNode;
    }
    return true;
}

// This function MODIFIES the Contact in PHONEBOOK.
bool PhoneBookClass ::modify()
{
    int choice = howDoYouWantFunction("Modify");
    string s, name, number;

    if (choice == 1)
        s = validateAndInputName();
    else if (choice == 2)
        s = validateAndInputNumber();
    else if (choice == 3)
        return false;

    bool found = false;
    Node *temp = head;

    while (temp != NULL)
    {
        name = (temp->elem).getName();
        number = temp->elem.getNumber();
        if (choice == 1)
        {
            if (name == s)
            {
                found = true;
                break;
            }
        }
        else if (choice == 2)
        {
            if (number == s)
            {
                found = true;
                break;
            }
        }
        temp = temp->next;
    }
    isFound(found, choice, s, name, number);

    if (found == false)
        return false;
    else
    {
        bool sure = confirmationDelMod("Modify");
        if (sure)
        {

            string newName = validateAndInputName();
            string newNumber = validateAndInputNumber();
            bool deleted = remove(choice, s);
            bool added = add(newName, newNumber);
            if (added)
                return true;
            else
                add(name, number);
        }
        return false;
    }
}

// This function DELETES a Contact in PHONEBOOK.
bool PhoneBookClass ::remove(int mod, string str)
{
    int choice;
    string s, name, number;
    bool found = false;
    if (mod == 0 && str == "")
    {
        choice = howDoYouWantFunction("Delete");
        if (choice == 1)
            s = validateAndInputName();
        else if (choice == 2)
            s = validateAndInputNumber();
        else if (choice == 3)
            return false;
    }
    else
        choice = mod, s = str;

    Node *temp = head;
    while (temp != NULL)
    {
        name = (temp->elem).getName();
        number = temp->elem.getNumber();
        if (choice == 1)
        {
            if (name == s)
            {
                found = true;
                break;
            }
        }
        else if (choice == 2)
        {
            if (number == s)
            {
                found = true;
                break;
            }
        }
        temp = temp->next;
    }

    if (mod == 0)
        isFound(found, choice, s, name, number);
    if (found)
    {
        bool sure = false;
        if (mod == 0)
            sure = confirmationDelMod("Delete");

        else
            sure = true;

        if (sure)
        {
            if (temp->prev != NULL)
                temp->prev->next = temp->next;
            else
                head = temp->next;
            if (temp->next != NULL)
                temp->next->prev = temp->prev;
            delete temp;
        }
        else
        {
            cout << endl
                 << "Contact Not Deleted!" << endl;
            return false;
        }
    }
    else
        return false;

    return true;
}

// This function Searches for the Contact in PHONEBOOK.
void PhoneBookClass ::search()
{
    int choice = howDoYouWantFunction("Search");

    string s, name, number;

    if (choice == 1)
        s = validateAndInputName();
    else if (choice == 2)
        s = validateAndInputNumber();
    else if (choice == 3)
        return;

    Node *temp = head;
    bool found = false;
    while (temp != NULL)
    {
        name = (temp->elem).getName();
        number = temp->elem.getNumber();
        if (choice == 1)
        {
            if (name == s)
            {
                found = true;
                break;
            }
        }
        else if (choice == 2)
        {
            if (number == s)
            {
                found = true;
                break;
            }
        }
        temp = temp->next;
    }
    isFound(found, choice, s, name, number);
    return;
}

// This function Prints PHONEBOOK
void PhoneBookClass::print()
{
    Node *temp = head;
    // cout << "Name\t\t\t\tNumber" << endl;
    cout << setw(6) << left << "SNO." << setw(40) << left << "NAME" << setw(40) << left << "NUMBER" << endl;
    int i = 1;
    while (temp != NULL)
    {
        string name = (temp->elem).getName();
        string number = (temp->elem).getNumber();
        cout << setw(6) << left << i << setw(40) << left << name << setw(40) << left << number << endl;
        // cout << name << "\t\t\t\t" << number << endl;
        temp = temp->next;
        i++;
    }
    cout << endl;
    cout << "PHONEBOOK PRINTED SUCCESSFULLY!" << endl;
}

// This functions checks if the PHONEBOOK is empty or not.
void PhoneBookClass::isEmpty()
{
    if (head == NULL)
        cout << "NO CONTACT FOUND! YOUR PHONE BOOK IS EMPTY. Press 1 to ADD CONTACTS." << endl;
    else
        cout << "CONTACT FOUND! YOUR PHONE BOOK NOT IS EMPTY." << endl;
    return;
}

// This functin prints the Total Number of Contacts present in the PHONEBOOK.
void PhoneBookClass::numberOfContacts()
{
    Node *temp = head;
    int cnt = 0;
    while (temp != NULL)
    {
        cnt++;
        temp = temp->next;
    }
    if (cnt == 0)
        cout << "NO CONTACT FOUND!" << endl;
    if (cnt == 1)
        cout << "ONLY " << cnt << " CONTACT IS PRESENT IN YOUR PHONEBOOK." << endl;
    else
        cout << "Total " << cnt << " CONTACTS ARE PRESENT IN YOUR PHONEBOOK." << endl;
}

// This funcion deletes all the contact present in the contact list.
void PhoneBookClass::resetALL()
{
    int inp;
    cout << "Do you want to delete all the contacts? [Press 1: YES | Press 0: NO]" << endl;
    cin >> inp;
    if (inp != 1)
    {
        cout << endl;
        cout << "Operation Aborted" << endl;
        return;
    }
    Node *temp = head;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    cout << endl;
    cout << "ALL CONTACTS ARE DELETED Successfully!!" << endl;
    head = NULL;
}

// This Function prints the instructions on the screen.
void instructions()
{
    cout << endl;
    cout << "We offer the following services" << endl;
    cout << "Enter 1: ADD CONTACT" << endl;
    cout << "Enter 2: MODIFY CONTACT" << endl;
    cout << "Enter 3: DELETE CONTACT" << endl;
    cout << "Enter 4: SEARCH CONTACT" << endl;
    cout << "Enter 5: PRINT PHONEBOOK" << endl;
    cout << "Enter 6: CHECK IF PHONEBOOK IS EMPTY" << endl;
    cout << "Enter 7: TOTAL NUMBER OF CONTACTS PRESENT IN THE PHONEBOOK" << endl;
    cout << "Enter 8: PRINT INSTRUCTIONS" << endl;
    cout << "Enter 9: DELETE ALL CONTACTS PHONEBOOK" << endl;
    cout << "Enter 0: EXIT PHONEBOOK" << endl;

    return;
}

int main()
{
    PhoneBookClass contactList; // Creating Phone Book Object

    // Some pre-existing contacts
    contactList.add("POLICE", "100");
    contactList.add("AMBULANCE", "108");
    contactList.add("OUR HELPLILNE", "18002005000");
    cout << endl
         << endl;

    // ASCII ART and TEXT
    asciiART();
    cout << "Hi!, I am ANDY, The Tech Bot. I am programmed to serve you as a PhoneBook." << endl;
    char sol = 'a';
    instructions();

    while (sol)
    {
        cout << endl;
        cout << "CHOOSE ONE OPTIONS[Press 8 to see the INSTRUCTIONS]: ";
        cin >> sol;
        cout << endl;
        if (sol == '1')
        {
            bool res = contactList.add("", "");
            if (res)
                success();
            else
                failure();
        }
        else if (sol == '2')
        {
            bool res = contactList.modify();
            if (res)
                success();
            else
                failure();
        }
        else if (sol == '3')
        {
            bool res = contactList.remove(0, "");
            if (res)
                success();
            else
                failure();
        }
        else if (sol == '4')
            contactList.search();
        else if (sol == '5')
            contactList.print();
        else if (sol == '6')
            contactList.isEmpty();
        else if (sol == '7')
            contactList.numberOfContacts();
        else if (sol == '8')
        {
            instructions();
            continue;
        }
        else if (sol == '9')
            contactList.resetALL();
        else if (sol == '0')
        {
            cout << "Thank for using me. I hope you liked me!" << endl;
            cout << "Bye!" << endl;
            break;
        }
        else
        {
            cout << "INVALID INPUT! PLEASE TRY AGAIN" << endl;
            instructions();
            continue;
        }
        cout << endl;
        cout << "You are back in Main Menu!!" << endl;
    }

    return 0;
}
