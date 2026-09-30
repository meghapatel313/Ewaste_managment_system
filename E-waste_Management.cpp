#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
using namespace std;

class Component {
protected:
    int componentID;
    string componentName;
    double weight;
    double condition;
    int quantity;
    bool hazardous;
    double recoveryValuePerKg;

public:
    Component() {
        componentID = 0;
        componentName = "Unknown";
        weight = 0;
        condition = 0;
        quantity = 1;
        hazardous = false;
        recoveryValuePerKg = 0;
    }

    Component(int id, string name, double w, double c, int q, bool h, double value) {
        componentID = id;
        componentName = name;
        weight = w;
        condition = c;
        quantity = q;
        hazardous = h;
        recoveryValuePerKg = value;
    }

    virtual string getComponentType() = 0;

    virtual string getRecoveryMethod() {
        if (condition >= 70)
            return "Reuse";
        else if (condition >= 40)
            return "Repair/Reuse";
        else
            return "Material Recovery";
    }

    virtual double calculateRecoveryValue() {
        double recoveryEfficiency = (100 - condition) / 100.0;

        if (recoveryEfficiency < 0)
            recoveryEfficiency = 0;

        return weight * quantity * recoveryValuePerKg * recoveryEfficiency;
    }

    virtual void display() {
        cout << "\nComponent ID       : " << componentID;
        cout << "\nComponent Name     : " << componentName;
        cout << "\nWeight             : " << weight << " kg";
        cout << "\nCondition          : " << condition << "%";
        cout << "\nQuantity           : " << quantity;
        cout << "\nHazardous          : " << (hazardous ? "Yes" : "No");
        cout << "\nRecovery Method    : " << getRecoveryMethod();
        cout << "\nEstimated Value    : Rs. "
             << fixed << setprecision(2)
             << calculateRecoveryValue() << "\n";
    }

    int getComponentID() {
        return componentID;
    }

    string getComponentName() {
        return componentName;
    }

    double getWeight() {
        return weight;
    }

    double getCondition() {
        return condition;
    }

    int getQuantity() {
        return quantity;
    }

    bool isHazardous() {
        return hazardous;
    }
    virtual ~Component() {}
};

class RAM : public Component {
public:
    RAM(int id, double w, double c, int q)
        : Component(id, "RAM", w, c, q, false, 500) {}

    string getComponentType() override {
        return "RAM";
    }
};

class ROM : public Component {
public:
    ROM(int id, double w, double c, int q)
        : Component(id, "ROM", w, c, q, false, 400) {}

    string getComponentType() override {
        return "ROM";
    }
};

class Battery : public Component {
public:
    Battery(int id, double w, double c, int q)
        : Component(id, "Battery", w, c, q, true, 150) {}

    string getComponentType() override {
        return "Battery";
    }

    string getRecoveryMethod() override {
        return "Specialized Battery Recycling";
    }
};

class Charger : public Component {
public:
    Charger(int id, double w, double c, int q)
        : Component(id, "Charger", w, c, q, false, 250) {}

    string getComponentType() override {
        return "Charger";
    }
};

class Screen : public Component {
public:
    Screen(int id, string name, double w, double c, int q, bool h, double value)
       : Component(id, name, w, c, q, h, value) {}

    string getComponentType() override {
        return "Sceen";
    }
};

class EWaste {
protected:
    int productID;
    string productName;
    string company;
    double weight;
    int quantity;
    double damagePercentage;

    vector<Component*> components;

public:
    EWaste() {
        productID = 0;
        productName = "Unknown";
        company = "Unknown";
        weight = 0;
        quantity = 1;
        damagePercentage = 0;
    }

    EWaste(int id, string name, string comp, double w,
           int q, double damage) {
        productID = id;
        productName = name;
        company = comp;
        weight = w;
        quantity = q;
        damagePercentage = damage;
    }

    virtual string getProductType() = 0;

    void addComponent(Component* component) {
        components.push_back(component);
    }

    vector<Component*>& getComponents() {
        return components;
    }

    virtual void display() {
        cout << "\n========================================";
        cout << "\nProduct ID       : " << productID;
        cout << "\nProduct Type     : " << getProductType();
        cout << "\nProduct Name     : " << productName;
        cout << "\nCompany          : " << company;
        cout << "\nWeight           : " << weight << " kg";
        cout << "\nQuantity         : " << quantity;
        cout << "\nDamage           : " << damagePercentage << "%";
        cout << "\n========================================";

        cout << "\n\nComponents:\n";

        for (Component* c : components) {
            c->display();
        }
    }

    int getProductID() {
        return productID;
    }

    string getProductName() {
        return productName;
    }

    string getCompany() {
        return company;
    }

    double getWeight() {
        return weight;
    }

    int getQuantity() {
        return quantity;
    }

    double getDamage() {
        return damagePercentage;
    }

    virtual ~EWaste() {
        for (Component* c : components)
            delete c;
    }
};


class Laptop : public EWaste {
public:
    Laptop(int id, string name, string company,
           double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage) {}

    string getProductType() override {
        return "Laptop";
    }
};

class Mobile : public EWaste {
public:
    Mobile(int id, string name, string company,
           double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage) {}

    string getProductType() override {
        return "Mobile";
    }
};

class TV : public EWaste {
public:
    TV(int id, string name, string company,
       double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage) {}

    string getProductType() override {
        return "TV";
    }
};

class Tablet : public EWaste {
public:
    Tablet(int id, string name, string company,
       double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage) {}

    string getProductType() override {
        return "Tablet";
    }
};