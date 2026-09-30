#include <iostream>
#include <cstring>
#include <fstream> // for file handling
#include <vector>
using namespace std;

// Base Class - Component
class Component{
    protected:
    string componentName;
    int quantity;
};

// Base Class - E-waste
class EWaste
{
protected:
    int itemID;
    string brand;
    double weight;
    string condition;
    int quantity;
    vector<Component*> components;

public:
    // Default constructor
    EWaste()
    {
        itemID = 0;
        brand = "Unknown";
        weight = 0.0;
        condition = "Unknown";
        quantity = 0;
    }

    // Parameterized constructor
    EWaste(int id, string b, double w, string c, int qty)
    {
        itemID = id;
        brand = b;
        weight = w;
        condition = c;
        quantity = qty;
    }

    // Display common information
    void display()
    {
        cout << "Item ID   : " << itemID << endl;
        cout << "Brand     : " << brand << endl;
        cout << "Weight    : " << weight << " kg" << endl;
        cout << "Condition : " << condition << endl;
        cout << "Quantity : " << quantity << endl;
    }

    // Destructor
    ~EWaste()
    {
        cout << "EWaste destructor called : Memory Clean Up..." << endl;
    }
};

// Smartphone
class Smartphone : public EWaste
{
private:
    string model;

public:
    Smartphone(int id, string b, double w, string c, string m)
        : EWaste(id, b, w, c)
    {
        model = m;
    }

    void displaySmartphone()
    {
        display();

        cout << "Device    : Smartphone" << endl;
        cout << "Model     : " << model << endl;
    }
};

// Tablet
class Tablet : public EWaste
{
private:
    string model;

public:
    Tablet(int id, string b, double w, string c, string m)
        : EWaste(id, b, w, c)
    {
        model = m;
    }

    void displayTablet()
    {
        display();

        cout << "Device    : Tablet" << endl;
        cout << "Model     : " << model << endl;
    }
};

// Laptop
class Laptop : public EWaste
{
private:
    int RAM;
    int storage;

public:
    Laptop(int id, string b, double w, string c, int r, int s)
        : EWaste(id, b, w, c)
    {
        RAM = r;
        storage = s;
    }

    void displayLaptop()
    {
        display();

        cout << "Device    : Laptop" << endl;
        cout << "RAM       : " << RAM << " GB" << endl;
        cout << "Storage   : " << storage << " GB" << endl;
    }
};

// Desktop / PC
class Desktop : public EWaste
{
private:
    int RAM;
    int storage;

public:
    Desktop(int id, string b, double w, string c, int r, int s)
        : EWaste(id, b, w, c)
    {
        RAM = r;
        storage = s;
    }

    void displayDesktop()
    {
        display();

        cout << "Device    : Desktop PC" << endl;
        cout << "RAM       : " << RAM << " GB" << endl;
        cout << "Storage   : " << storage << " GB" << endl;
    }
};

// Television
class Television : public EWaste
{
private:
    string screenType;
    double screenSize;

public:
    Television(int id, string b, double w, string c,
               string st, double ss)
        : EWaste(id, b, w, c)
    {
        screenType = st;
        screenSize = ss;
    }

    void displayTelevision()
    {
        display();

        cout << "Device    : Television" << endl;
        cout << "Screen    : " << screenType << endl;
        cout << "Size      : " << screenSize << " inches" << endl;
    }
};



int main()
{
    return 0;
}