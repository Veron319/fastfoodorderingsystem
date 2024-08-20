#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>
using namespace std;

struct FoodNode
{
    string name;
    float price;
    FoodNode *next;
};

struct OrderNode
{
    string name;
    float price;
    int quantity;
    OrderNode *next;
};

struct AccountNode
{
    string identify, password;
    AccountNode *next;
};

class FoodLinkedList
{
private:
    FoodNode *head, *tail, *temp, *prev, *arr;
    int count;

public:
    FoodLinkedList()
    {
        count = 0;

        ifstream infile;
        infile.open("food.txt");
        head = NULL;

        if (infile.is_open())
        {
            while (infile.peek() != EOF)
            {
                if (head == NULL)
                {
                    head = new FoodNode;
                    tail = head;
                }
                else
                {
                    tail->next = new FoodNode;
                    tail = tail->next;
                }

                getline(infile, tail->name, ',');
                infile >> tail->price;
                infile.ignore(256, '\n');
                tail->next = NULL;
                count++;
            }

            infile.close();
        }
    }

    ~FoodLinkedList()
    {
        ofstream outfile;
        outfile.open("food.txt");

        if (outfile.is_open())
        {
            temp = head;

            while (temp != NULL)
            {
                outfile << temp->name << "," << temp->price << endl;
                temp = temp->next;
            }

            outfile.close();
        }
    }

    void selection()
    {
        temp = head;
        cout << fixed << setprecision(2);

        for (int i = 1; temp != NULL; i++)
        {
            cout << "\t\t\t\t ";
            cout << i << ". " << temp->name << " ......................... RM" << temp->price << endl
                 << endl;
            temp = temp->next;
        }
    }

    void selection(int index)
    {
        temp = head;
        cout << fixed << setprecision(2);

        for (int i = 1; temp != NULL && i < index; i++)
        {
            temp = temp->next;
        }

        if (temp != NULL)
        {
            cout <<"\n\t\t\t\t\t\t"<< index << ". " << temp->name << ", RM" << temp->price << endl;
        }
    }

    void selection(int index, string *name, float *price)
    {
        temp = head;
        cout << fixed << setprecision(2);

        for (int i = 1; temp != NULL && i < index; i++)
        {
            temp = temp->next;
        }

        if (temp != NULL)
        {
            *name = temp->name;
            *price = temp->price;
        }
    }

    void insertion(string name, float price)
    {
        if (head == NULL)
        {
            head = new FoodNode;
            tail = head;
        }
        else
        {
            tail->next = new FoodNode;
            tail = tail->next;
        }

        tail->name = name;
        tail->price = price;
        tail->next = NULL;
        count++;
    }

    void updation(int index, string name, float price)
    {
        temp = head;

        for (int i = 1; temp != NULL && i < index; i++)
        {
            temp = temp->next;
        }

        if (temp != NULL)
        {
            temp->name = name;
            temp->price = price;
        }
    }

    void deletion(int index)
    {
        temp = head;

        if (index == 1)
        {
            head = head->next;
            delete temp;
        }
        else
        {
            for (int i = 1; temp != NULL && i < index; i++)
            {
                prev = temp;
                temp = temp->next;
            }

            if (temp != NULL)
            {
                prev->next = temp->next;
                delete temp;
            }
        }
    }

    void toArray()
    {
        arr = new FoodNode[count];
        temp = head;

        for (int i = 0; i < count; i++)
        {
            arr[i].name = temp->name;
            arr[i].price = temp->price;
            temp = temp->next;
        }
    }

    void toLinkedList()
    {
        temp = head;

        for (int i = 0; i < count; i++)
        {
            temp->name = arr[i].name;
            temp->price = arr[i].price;
            temp = temp->next;
        }
    }

    void shellSortAsc()
    {
        toArray();

        FoodNode temp;

        for (int gap = count / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < count; i++)
            {
                temp = arr[i];

                int j;
                for (j = i; j >= gap && arr[j - gap].price > temp.price; j -= gap)
                {
                    arr[j] = arr[j - gap];
                }

                arr[j] = temp;
            }
        }

        toLinkedList();
    }

    void shellSortDesc()
    {
        toArray();

        FoodNode temp;

        for (int gap = count / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < count; i++)
            {
                temp = arr[i];

                int j;
                for (j = i; j >= gap && arr[j - gap].price < temp.price; j -= gap)
                {
                    arr[j] = arr[j - gap];
                }

                arr[j] = temp;
            }
        }

        toLinkedList();
    }

    bool jumpSearchPrice(float price)
    {
        shellSortAsc();

        int step = sqrt(count);
        int prev = 0;

        while (arr[min(step, count) - 1].price < price)
        {
            prev = step;
            step += sqrt(count);

            if (prev >= count)
                return false;
        }

        while (arr[prev].price < price)
        {
            prev++;

            if (prev == min(step, count))
                return false;
        }

        if (arr[prev].price == price)
        {
            while (arr[prev].price == price)
            {
                selection(prev + 1);
                prev++;
            }

            return true;
        }
        else
        {
            return false;
        }
    }

    void jumpSearchIndex(int index)
    {
        int found = 0;
        int tempindex = 1;
        int start = 1;

        int end = sqrt(count);
        while (tempindex < index && end < count)
        {
            start = end;
            end += sqrt(count);
            
            if (end >= tempindex)
            {
                tempindex = start;
            }
            if (end >= count )
            {
                tempindex = count;
            }
        }

        for (int i = 0; i < sqrt(count); i++)
        {
            if (tempindex == index)
            {
                found++;
            }
            else
            {
                tempindex--;
            }
        }

        if (found != 0)
        {
            cout << "\n\t\t\t\t\t\t The code you search is:" << index;
            cout << "\n\t\t\t\t\t\t Found as below " << endl;
            selection(tempindex);
        }
        else
        {
            cout << "\n\t\t\t\t\t\tThe code you search could not be found!!" << endl;
        }
    }
};

class FoodInterface : public FoodLinkedList
{
private:
    int index;
    string name;
    float price;

public:
    void selection()
    {
        cout << endl
             << endl
             << "\t\t\t\t ..............FOOD MENU ............\t\t\t\t" << endl
             << endl;
        FoodLinkedList::selection();
        cout << endl
             << endl;
    }

    void insertion()
    {
        cout << "\n\t\t\t\t\t      -------Add New Burger-------" << endl
             << endl;
        cout << "\t\t\t\t\t      Burger Name  : ";
        getline(cin, name);

        cout << "\t\t\t\t\t      Burger Price : RM ";
        cin >> price;
        cin.sync();

        FoodLinkedList::insertion(name, price);
        cout << "\n\n\t\t\t\t\t    New Burger Added Successfully..." << endl;
    }

    void updation()
    {
        cout << "\n\n\n\t\t\t      ........................................................" << endl;
        cout << "\t\t\t\t\t\t EDITING FOOD NAME " << endl;
        cout << "\t\t\t      ........................................................" << endl;
        cout << "\t\t\t      Enter burger number that you wanna edit : ";
        cin >> index;
        cin.sync();

        cout << "\n\n\n\t\t\t      Below was the preview of burger detail." << endl;
        cout << "\t\t\t\t\t\t  ";
        FoodLinkedList::selection(index);
        cout << "\t\t\t      ........................................................" << endl
             << endl;

        cout << "\n\t\t\t      Burger Name    : ";
        getline(cin, name);

        cout << "\t\t\t      Burger Price   : RM ";
        cin >> price;
        cin.sync();

        FoodLinkedList::updation(index, name, price);
        cout << "\n\n\t\t\t\t\t\tEdit successfully....." << endl
             << endl;
    }

    void deletion()
    {
        cout << "\n\n\n\t\t\t      ........................................................" << endl;
        cout << "\t\t\t\t\t\t   DELETING FOOD " << endl;
        cout << "\t\t\t      ........................................................" << endl;
        cout << "\t\t\t      Enter the burger number that you wanna delete : ";
        cin >> index;
        cin.sync();

        FoodLinkedList::deletion(index);
        cout << "\n\n\t\t\t\t\t\tDelete successfully....." << endl
             << endl;
    }

    void sortAsc()
    {
        cout << "\n\t\t\t      ........................................................" << endl;
        cout << "\n\t\t\t\t\tSORTING FOOD PRICE IN ASSCENDING ORDER " << endl;
        cout << "\n\t\t\t      ........................................................" << endl
             << endl;
        FoodLinkedList::shellSortAsc();
        FoodLinkedList::selection();
    }

    void sortDesc()
    {
        cout << "\n\t\t\t      ........................................................" << endl;
        cout << "\n\t\t\t\t\tSORTING FOOD PRICE IN DESCENDING ORDER " << endl;
        cout << "\n\t\t\t      ........................................................" << endl
             << endl;
        FoodLinkedList::shellSortDesc();
        FoodLinkedList::selection();
    }

    void search()
    {
        int choice;

        do
        {
            cout << "\n\t\t\t      ........................................................" << endl;
            cout << "\n\t\t\t\t\t\tSEARCHING BURGER " << endl;
            cout << "\n\t\t\t      ........................................................" << endl;
            cout << "\t\t\t\t\t\t 1.Search by Index" << endl;
            cout << "\t\t\t\t\t\t 2.Search by Price" << endl;
            cout << "\t\t\t\t\t\t 3.Back" << endl;
            cout << "\n\n\n\t\t\t\t\t         ENTER YOUR CHOICE -> \t";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "\n\n\t\t\t      Enter the burger code that you wanna search : ";
                cin >> index;
                cin.sync();
                FoodLinkedList::jumpSearchIndex(index);
                break;

            case 2:
                cout << "\n\n\t\t\t      Enter the burger price that you wanna search : ";
                cin >> price;
                cin.sync();

                if (FoodLinkedList::jumpSearchPrice(price))
                    cout << "\n\t\t\t\t\t\tThe price you search found " << endl;
                else
                    cout << "\n\t\t\t\t\t\tThe price you search could not be found!!" << endl;

                break;

            case 3:
                break;

            default:
                cout << "\n\n\n\n\t\t\t\t       WRONG INPUT, PLEASE ENTER THE CORRECT INPUT" << endl;
                break;
            }

        } while (choice != 3);
    }
};

class Order
{
private:
    OrderNode *head, *tail, *temp;

public:
    Order()
    {
        head = NULL;
    }

    void selection()
    {
        float amount;

        temp = head;
        amount = 0;
        cout << fixed << setprecision(2);

        while (temp != NULL)
        {
            cout << "\n\t\t\t\t             ";
            cout << temp->name << endl;
            cout << "\n\t\t\t\t             ";
            cout << temp->quantity << " * RM " << temp->price << "\tRM " << temp->quantity * temp->price << endl;
            amount += temp->quantity * temp->price;
            temp = temp->next;
        }

        cout << "\n\n\t\t\t        --------------------------------------------------------" << endl;
        cout << " \t\t\t\t       TOTAL PAYMENT \t\t\tRM " << amount << endl;
        cout << "\t\t\t        --------------------------------------------------------" << endl;
    }

    void insertion(string name, float price, int quantity)
    {
        if (head == NULL)
        {
            head = new OrderNode;
            tail = head;
        }
        else
        {
            tail->next = new OrderNode;
            tail = tail->next;
        }

        tail->name = name;
        tail->price = price;
        tail->quantity = quantity;
        tail->next = NULL;
    }
};

class OrderInterface : public Order
{
private:
    FoodLinkedList *FLL;
    int number, index, quantity;
    string name;
    float price;

public:
    void selection()
    {
        system("CLS");
        cout << "\n\n\t\t\t\t<<<<<<<     <<<<<<<<   ORDER DETAIL   >>>>>>>>   >>>>>>>" << endl;
        Order::selection();
        cout << "\n\n\n\t\t\t\t\t\t       THANK YOU!" << endl;
        cout << "\n\t\t\t\t\t        WE HOPE TO SEE YOU SOON! :)" << endl;
        cout << "\n\t\t          YOU WILL BE REDIRECT TO THE MENU PAGE SHORTLY. PLEASE BE PATIENT. :)" << endl;
        cout << "\n\n\n\t\t\t        --------------------------------------------------------" << endl;
        sleep(3);
    }

    void insertion(string identify)
    {
        FLL = new FoodLinkedList;

        cout << "\n\n\n\t\t\t\tENTER THE NUMBER OF ORDER YOU WANT TO MAKE : \t";
        cin >> number;
        cin.sync();
        for (int i = 0; i < number; i++)
        {
            cout << "\n\n\t\t\t\tWHICH BURGER YOU WANT ? [ENTER NUMBER ONLY!] \t";
            cin >> index;
            cin.sync();
            cout << "\n\n\t\t\t\tENTER THE QUANTITY THAT YOU WOULD LIKE TO TAKE : \t";
            cin >> quantity;
            cin.sync();

            FLL->selection(index, &name, &price);
            Order::insertion(name, price, quantity);

            ofstream writeRec;
            writeRec.open("Customer_Receipt.txt", ios::in | ios::out | ios::app);
            writeRec << identify << ',' << name << ',' << price << ',' << quantity << endl;
        }

        delete FLL;
    }
};

class Account
{
private:
    AccountNode *head, *tail, *temp;
    string fileName;

public:
    Account(string fileName)
    {
        this->fileName = fileName;
        head = NULL;

        ifstream infile;
        infile.open(fileName.c_str());

        if (infile.is_open())
        {
            while (infile.peek() != EOF)
            {
                if (head == NULL)
                {
                    head = new AccountNode;
                    tail = head;
                }
                else
                {
                    tail->next = new AccountNode;
                    tail = tail->next;
                }

                getline(infile, tail->identify, ',');
                getline(infile, tail->password, '\n');
                tail->next = NULL;
            }

            infile.close();
        }
    }

    ~Account()
    {
        ofstream outfile;
        outfile.open(fileName.c_str());

        if (outfile.is_open())
        {
            temp = head;

            while (temp != NULL)
            {
                outfile << temp->identify << "," << temp->password << endl;
                temp = temp->next;
            }

            outfile.close();
        }
    }

    bool selection(string identify, string password)
    {
        bool result;

        temp = head;
        result = false;

        while (temp != NULL && !result)
        {
            if (temp->identify == identify && temp->password == password)
            {
                result = true;
            }

            temp = temp->next;
        }

        return result;
    }

    void insertion(string identify, string password)
    {

        if (head == NULL)
        {
            head = new AccountNode;
            tail = head;
        }
        else
        {
            tail->next = new AccountNode;
            tail = tail->next;
        }

        tail->identify = identify;
        tail->password = password;
        tail->next = NULL;
    }
};

class AdminInterface : public Account
{
private:
    string identify, password, seckey;
    int choice;
    bool result;

public:
    AdminInterface() : Account("admin.txt") {}

    void registration()
    {
        system("CLS");
        cout << "\n\n\n\n\t\t\t\t<<<<<<<     <<<<<<<<   Admin Registration   >>>>>>>>   >>>>>>>" << endl;
        cout << "\n\n\n\t\t\t\t\t           ADMIN NAME    :    ";
        getline(cin, identify);
        cout << "\n\n\n\t\t\t\t\t           PASSWORD    :    ";
        getline(cin, password);

        insertion(identify, password);
        cout << "\n\n\n\n\t\t\t\t         <---- ACCOUNT HAS BEEN REGISTERED ---->" << endl;
        cout << "\n\n\n\n\t\t\t\t      YOU WILL BE REDIRECT TO THE SAME PAGE SHORTLY" << endl;
        sleep(3);
        login();
    }

    void login()
    {
        system("CLS");
        cout << "\n\n\n\n\t\t\t\t    <<<<<<<     <<<<<<<<   Admin Login   >>>>>>>>   >>>>>>>" << endl;
        cout << "\n\n\n\t\t\t\t\t           ADMIN NAME    :    ";
        getline(cin, identify);
        cout << "\n\n\n\t\t\t\t\t           PASSWORD    :    ";
        getline(cin, password);

        result = selection(identify, password);

        if (result)
        {
            cout << "\n\n\n\n\t\t\t\t\t\t     LOGGING-IN      " << endl;
            for (int load = 0; load <= 1000; load++)
            {
                cout << "\rLoading... : " << load / 10; // loading screen structure;
            }
        }
        else
        {
            cout << "\n\n\n\n\t\t\t\t     INVALID ADMIN NAME OR PASSWORD! PLEASE TRY AGAIN :( " << endl;
            cout << "\n\n\n\n\t\t\t\t      YOU WILL BE REDIRECT TO THE SAME PAGE SHORTLY" << endl;
            sleep(3);
            login();
        }
    }

    void menu()
    {
        result = false;

        do
        {
            system("CLS");
            cout << "\n\n\n\t\t\t\t\t     STAFF SECURITY KEY -> \t";
            getline(cin, seckey);

            if (seckey == "admin")
            {
                system("CLS");
                cout << "\n\n\n\t\t\t\t<<<<<<<     <<<<<<<<  NAVIGATION  >>>>>>>>   >>>>>>>" << endl;
                cout << "\n\n\n\t\t\t\t\t\t    1. ADMIN LOGIN " << endl;
                cout << "\n\t\t\t\t\t\t    2. ADMIN REGISTRATION " << endl;
                cout << "\n\n\n\t\t\t\t\t         ENTER YOUR CHOICE -> \t";
                cin >> choice;
                cin.sync();

                switch (choice)
                {
                case 1:
                    system("CLS");
                    login();
                    break;

                case 2:
                    system("CLS");
                    registration();
                    break;

                default:
                    cout << "\n\n\n\n\t\t\t\t       WRONG INPUT, PLEASE ENTER THE CORRECT INPUT" << endl;
                    cout << "\n\n\n\n\t\t\t\t      YOU WILL BE REDIRECT TO THE SAME PAGE SHORTLY" << endl;
                    sleep(3);
                    break;
                }
            }
            else
            {
                cout << "\n\n\n\n\t\t\t\t         Wrong Security Key. Please Try Again. " << endl;
                cout << "\n\n\n\n\t\t\t\t      YOU WILL BE REDIRECT TO THE SAME PAGE SHORTLY" << endl;
                sleep(3);
                menu();
            }

        } while (!result);

        FoodInterface *FI;

        do
        {
            FI = new FoodInterface;
            system("CLS");

            printf("\n\n\t\t\t\t\t\t *** ONLY FOR STAFF ** \t\t\n");
            cout << "\t\t\t\t\t ======================================" << endl;
            cout << "\t\t\t\t\t ----------------Admin-----------------" << endl;
            cout << "\t\t\t\t\t ======================================" << endl;
            cout << "\t\t\t\t\t\t 1.Add New Burger" << endl;
            cout << "\t\t\t\t\t\t 2.Display The Burger" << endl;
            cout << "\t\t\t\t\t\t 3.Edit The Burger" << endl;
            cout << "\t\t\t\t\t\t 4.Delete The Burger" << endl;
            cout << "\t\t\t\t\t\t 5.Search The Burger" << endl;
            cout << "\t\t\t\t\t\t 6.Sort The Burger Asscending" << endl;
            cout << "\t\t\t\t\t\t 7.Sort The Burger Descending" << endl;
            cout << "\t\t\t\t\t\t 8.Exit" << endl;

            cout << "\n\n\t\t\t\t\t\t Enter Your choice ->\t";
            cin >> choice;
            cin.sync();
            cout << endl;

            system("CLS");

            switch (choice)
            {
            case 1:

                FI->insertion();
                break;

            case 2:
                FI->selection();
                break;

            case 3:
                FI->selection();
                FI->updation();
                break;

            case 4:
                FI->selection();
                FI->deletion();
                break;

            case 5:
                FI->search();
                break;

            case 6:
                FI->sortAsc();
                break;

            case 7:
                FI->sortDesc();
                break;

            case 8:
                break;

            default:
                cout << "\n\n\n\n\t\t\t\t       WRONG INPUT, PLEASE ENTER THE CORRECT INPUT" << endl;
                break;
            }

            delete FI;

            system("PAUSE");

        } while (choice != 8);
    }
};

class UserInterface : public Account
{
private:
    string identify, password;
    int choice;
    bool result;

public:
    UserInterface() : Account("user.txt") {}

    void registration()
    {
        cout << "\n\n\n\n\t\t\t\t<<<<<<<     <<<<<<<<   User Registration   >>>>>>>>   >>>>>>>" << endl;
        cout << "\n\n\n\t\t\t\t\t        USERNAME    : ";
        getline(cin, identify);
        cout << "\n\n\n\t\t\t\t\t        PASSWORD    : ";
        getline(cin, password);

        insertion(identify, password);
        cout << "\n\n\n\t\t\t\t        <---- ACCOUNT HAS BEEN REGISTERED ---->" << endl
             << endl;
        for (int load = 0; load <= 1000; load++)
        {
            cout << "\rLoading... : " << load / 10; // loading screen structure;
        }
        cout << "\n\n\n\n\t\t\t    YOU WILL BE REDIRECT TO THE LOGIN PAGE SHORTLY. PLEASE BE PATIENT. :) " << endl;
        sleep(3);
        login();
    }

    void login()
    {
        system("CLS");
        cout << "\n\n\n\n\t\t\t\t<<<<<<<     <<<<<<<<   User Login   >>>>>>>>   >>>>>>>" << endl;
        cout << "\n\n\n\t\t\t\t\t        USERNAME    : ";
        getline(cin, identify);
        cout << "\n\n\n\t\t\t\t\t        PASSWORD    : ";
        getline(cin, password);

        result = selection(identify, password);

        if (result)
        {
            cout << "\n\n\n\n\t\t\t\t\t\t   LOGGING-IN      " << endl
                 << endl;
            for (int load = 0; load <= 1000; load++)
            {
                cout << "\rLoading... : " << load / 10; // loading screen structure;
            }
        }
        else
        {
            cout << "\n\n\n\t\t\t\t    INVALID USERNAME AND PASSWORD! PLEASE TRY AGAIN :( " << endl
                 << endl;
            cout << "\n\n\n\n\t\t\t    YOU WILL BE REDIRECT TO THE SAME PAGE SHORTLY. PLEASE BE PATIENT. :) " << endl;
            sleep(3);
            login();
        }
    }

    void menu()
    {
        result = false;

        do
        {
            system("CLS");
            cout << "\n\n\n\t\t\t\t<<<<<<<     <<<<<<<<  NAVIGATION  >>>>>>>>   >>>>>>>" << endl;
            cout << "\n\n\n\t\t\t\t\t\t    1. USER LOGIN " << endl;
            cout << "\n\t\t\t\t\t\t    2. USER REGISTRATION " << endl;
            cout << "\n\n\n\t\t\t\t\t     ENTER YOUR CHOICE -> \t";
            cin >> choice;
            cin.sync();

            switch (choice)
            {
            case 1:
                system("CLS");
                login();
                break;

            case 2:
                system("CLS");
                registration();
                break;

            default:
                cout << "\n\n\n\t\t\t\t     WRONG INPUT, PLEASE ENTER THE CORRECT INPUT" << endl;
                cout << "\n\n\n\t\t\t\t    YOU WILL BE REDIRECT TO THE SAME PAGE SHORTLY" << endl;
                sleep(3);
                system("CLS");
                menu();
                break;
            }

        } while (!result);

        do
        {
            system("CLS");
            cout << "\n\n\t\t\t        ----------------------------------------------------------" << endl;
            cout << "\n\t\t\t                   WELCOME TO FAST FOOD ORDERING SYSTEM           " << endl;
            cout << "\n\n\t\t\t        ----------------------------------------------------------" << endl;
            cout << "\n\t\t\t                            --- WELCOME --                          " << endl;
            cout << "\n\t\t\t        ----------------------------------------------------------" << endl;
            cout << "\n \t\t\t\t\t            YOU WANT TO --> \n\n\t\t\t\t\t            1. ORDER FOOD >>> \n\t\t\t\t\t            2. BACK TO MAIN MENU >>>\n\n\n"
                 << endl;
            cout << "\t\t\t\t           ENTER YOUR CHOICE --> \t";
            cin >> choice;
            cin.sync();

            switch (choice)
            {
            case 1:
                system("CLS");
                for (int load = 0; load <= 1000; load++)
                {
                    cout << "\rLoading... : " << load / 10; // loading screen structure;
                }
                FoodInterface *FI;
                OrderInterface *OI;
                FI = new FoodInterface;
                OI = new OrderInterface;
                FI->selection();
                OI->insertion(identify);
                OI->selection();
                delete OI;
                delete FI;
                break;

            case 2:
                for (int load = 0; load <= 1000; load++)
                {
                    cout << "\rLoading... : " << load / 10; // loading screen structure;
                }
                break;

            default:
                cout << "\n\n\n\t\t\t\t\t WRONG INPUT, PLEASE ENTER THE CORRECT INPUT" << endl
                     << endl;
                cout << "\n\n\n\t\t\t\t        YOU WILL BE REDIRECT TO THE SAME PAGE SHORTLY" << endl;
                sleep(3);
                break;
            }

        } while (choice != 2);
    }
};

int main()
{
    int choice;

    do
    {
        system("CLS");
        cout << "\n\n\t\t\t\t----------------------------------------------------------" << endl;
        cout << "\n\t\t\t\t           WELCOME TO FAST FOOD ORDERING SYSTEM           " << endl;
        cout << "\n\t\t\t\t----------------------------------------------------------" << endl;

        cout << "\n\t\t\t\t\t\t1. CUSTOMER SECTION >>> \n \t\t\t\t\t\t2. ABOUT THIS PROJECT >>> \n \t\t\t\t\t\t3. STAFF SECTION >>> \n \t\t\t\t\t\t4. EXIT >>> " << endl
             << endl;

        cout << "\n\t\t\t\t\t   ENTER YOUR CHOICE --> \t";
        cin >> choice;
        cin.sync();

        switch (choice)
        {
        case 1:
            system("CLS");
            for (int load = 0; load <= 1000; load++)
            {
                cout << "\rLoading... : " << load / 10; // loading screen structure;
            }
            UserInterface *UI;
            UI = new UserInterface;
            UI->menu();
            delete UI;
            break;

        case 2:
            for (int load = 0; load <= 1000; load++)
            {
                cout << "\rLoading... : " << load / 10; // loading screen structure;
            }
            system("CLS");
            cout << "\n\n\n\t\t\t      ====     THIS IS OUR GROUP ASSIGNMENT WITH TITLE     === " << endl;
            cout << "\n\t\t\t          ===      <<FAST FOOD ORDERING SYSTEM >>    ===" << endl;
            cout << "\n                      ===      BY USING C++ LANGUAGE AND COMBINATION OF DATA STRUCTURE        ===" << endl;

            cout << "\n";
            cout << "________________________________________________________________________________________________________________________" << endl;
            cout << "\n\n";

            cout << "\t\t\t   ---->> CAN THIS ORDERING SYSTEM RUN NEATLY AND FLUENTLY? <<---   " << endl;
            cout << "\n\t\t            >>> IF THERE SOME INCONVINIENT, PLEASE FORGIVE & FORGAVE <<< " << endl;
            cout << "\n\t\t\t     ---->>           THANK YOU VERY MUCH!!! :)          <<---- \n"
                 << endl;
            system("PAUSE");
            break;

        case 3:
            system("CLS");
            for (int load = 0; load <= 1000; load++)
            {
                cout << "\rLoading... : " << load / 10; // loading screen structure;
            }
            AdminInterface *AI;
            AI = new AdminInterface;
            AI->menu();
            delete AI;
            break;

        case 4:
            for (int load = 0; load <= 1000; load++)
            {
                cout << "\rLoading... : " << load / 10; // loading screen structure;
            }
            system("CLS");
            cout << "\n\n\n";
            cout << "\n\t\t\t         -----------------------------------------------------------" << endl;
            cout << "\n\t\t\t                           FAST FOOD ORDERING SYSTEM                 " << endl;
            cout << "\n\t\t\t\t\t                 THANK YOU!                                           " << endl;
            cout << "\n\t\t\t\t                  WE HOPE TO SEE YOU SOON! :)                            " << endl;
            cout << "\n\t\t\t         -----------------------------------------------------------" << endl;
            sleep(3);
            break;

        default:
            cout << "\n\n\t\t\t              WRONG INPUT, PLEASE ENTER THE CORRECT INPUT" << endl;
            cout << "\n\n\t\t\t    YOU WILL BE REDIRECT TO THE SAME PAGE SHORTLY. PLEASE BE PATIENT. :)" << endl;
            sleep(3);
            main();
            break;
        }

    } while (choice != 4);

    return 0;
}
