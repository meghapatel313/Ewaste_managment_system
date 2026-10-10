#include <iostream> // for general input/output operations
#include <fstream> // for file input/output operations
#include <vector> // for using the vector container
#include <string> // for using the string class
#include <iomanip> // for formatting output (ex. setting precision)
#include <algorithm> // to use stl algorithms like sort, find, etc.
using namespace std;

// Base Class 1
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
    Component() : componentID(0), componentName("Unknown"), weight(0), condition(0), quantity(1), hazardous(false), recoveryValuePerKg(0) {}

    Component(int id, string name, double w, double c, int q, bool h, double value) {
        componentID = id;
        componentName = name;
        weight = w;
        condition = c;
        quantity = q;
        hazardous = h;
        recoveryValuePerKg = value;
    }

    // Pure virtual function that defines an interface that concrete derived classes must implement
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
    RAM(int id, double w, double c, int q) : Component(id, "RAM", w, c, q, false, 500) {}

    // The override keyword tells the compiler that this function is intended to override a virtual function from the base class.
    string getComponentType() override {
        return "RAM";
    }
};

class ROM : public Component {
public:
    ROM(int id, double w, double c, int q) : Component(id, "ROM", w, c, q, false, 400) {}

    string getComponentType() override {
        return "ROM";
    }
};

class Battery : public Component {
public:
    Battery(int id, double w, double c, int q) : Component(id, "Battery", w, c, q, true, 150) {}

    string getComponentType() override {
        return "Battery";
    }

    string getRecoveryMethod() override {
        return "Specialized Battery Recycling";
    }
};

class Charger : public Component {
public:
    Charger(int id, double w, double c, int q) : Component(id, "Charger", w, c, q, false, 250) {}

    string getComponentType() override {
        return "Charger";
    }
};

class Screen : public Component {
public:
    Screen(int id, double w, double c, int q) : Component(id, "Screen", w, c, q, false, 300) {}

    string getComponentType() override {
        return "Screen";
    }
};

// Base Class 2
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
    EWaste() : productID(0), productName("Unknown"), company("Unknown"), weight(0), quantity(1), damagePercentage(0) {}

    EWaste(int id, string name, string comp, double w, int q, double damage) : productID(id), productName(name), company(comp), weight(w), quantity(q), damagePercentage(damage) {}

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
    Laptop(int id, string name, string company, double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage) {}

    string getProductType() override {
        return "Laptop";
    }
};

class Mobile : public EWaste {
public:
    Mobile(int id, string name, string company, double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage) {}

    string getProductType() override {
        return "Mobile";
    }
};

class TV : public EWaste {
public:
    TV(int id, string name, string company, double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage) {}

    string getProductType() override {
        return "TV";
    }
};

class Tablet : public EWaste {
public:
    Tablet(int id, string name, string company, double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage) {}

    string getProductType() override {
        return "Tablet";
    }
};

class WasteClassifier {
public:
    string classify(double damage) {
        if (damage < 30)
            return "Reuse";
        else if (damage < 50)
            return "Repair";
        else if (damage < 70)
            return "Donate/Sell";
        else if (damage < 90)
            return "Component Recovery";
        else
            return "Material Recycling";
    }
};

class RecoveryPlanner {
public:
    void generateRecoveryPlan(EWaste* product) {
        WasteClassifier classifier;
        cout << "\n========================================";
        cout << "\n        RECOVERY PLAN";
        cout << "\n========================================";
        cout << "\nProduct: " << product->getProductName();

        string decision = classifier.classify(product->getDamage());

        cout << "\nOverall Decision: " << decision << "\n";

        if (decision == "Repair") {
            cout << "\nAction: Send product for repair.\n";
            return;
        }
        if (decision == "Donate/Sell") {
            cout << "\nAction: Inspect and donate/resell.\n";
            return;
        }
        if (decision == "Reuse") {
            cout << "\nAction: Product can be reused directly.\n";
            return;
        }
        cout << "\nComponent Recovery Analysis:\n";

        for (Component* c : product->getComponents()) {
            cout << "\n----------------------------------------";
            cout << "\nComponent: " << c->getComponentName();
            cout << "\nCondition: " << c->getCondition() << "%";
            cout << "\nRecovery Method: " << c->getRecoveryMethod();
            cout << "\nEstimated Value: Rs. " << fixed << setprecision(2) << c->calculateRecoveryValue();
            if (c->isHazardous())
                cout << "\nWARNING: Hazardous Component";
        }
        cout << "\n";
    }
};

class CSVManager {
public:
    void saveProduct(EWaste* product) {

        ofstream file("products.csv", ios::app);

        if (!file) {
            cout << "\nError opening products.csv\n";
            return;
        }

        WasteClassifier classifier;

        file << product->getProductID() << ","
             << product->getProductType() << ","
             << product->getProductName() << ","
             << product->getCompany() << ","
             << product->getWeight() << ","
             << product->getQuantity() << ","
             << product->getDamage() << ","
             << classifier.classify(product->getDamage())
             << "\n";

        file.close();
    }

    void saveComponents(EWaste* product) {

        // ios is the file opening mode : Opens the file for appending. New data is written at the end, preserving existing contents.
        // ofstream is for file outptut stream, used to write data to files.
        ofstream file("components.csv", ios::app);

        if (!file) {
            cout << "\nError opening components.csv\n";
            return;
        }

        for (Component* c : product->getComponents()) {
            file << c->getComponentID() << ","
                 << product->getProductID() << ","
                 << c->getComponentName() << ","
                 << c->getWeight() << ","
                 << c->getQuantity() << ","
                 << c->getCondition() << ","
                 << (c->isHazardous() ? "Yes" : "No") << ","
                 << c->getRecoveryMethod() << ","
                 << c->calculateRecoveryValue()
                 << "\n";
        }
        file.close();
    }
};

class ReportGenerator {
public:

    void generateReport(vector<EWaste*>& products) {

        ofstream file("ewaste_report.txt");

        if (!file) {
            cout << "\nUnable to create report.\n";
            return;
        }

        WasteClassifier classifier;

        int reuse = 0;
        int repair = 0;
        int donate = 0;
        int recovery = 0;
        int recycling = 0;

        double totalWeight = 0;
        double totalRecoveryValue = 0;

        int hazardousCount = 0;

        for (EWaste* product : products) {
            string decision =
                classifier.classify(product->getDamage());

            if (decision == "Reuse")
                reuse++;
            else if (decision == "Repair")
                repair++;
            else if (decision == "Donate/Sell")
                donate++;
            else if (decision == "Component Recovery")
                recovery++;
            else
                recycling++;

            totalWeight += product->getWeight() * product->getQuantity();

            for (Component* c : product->getComponents()) {
                if (decision == "Component Recovery" || decision == "Material Recycling") {
                    totalRecoveryValue += c->calculateRecoveryValue();
                }
                if (c->isHazardous())
                    hazardousCount++;
            }
        }

        file << "========================================\n";
        file << "       E-WASTE MANAGEMENT REPORT\n";
        file << "========================================\n\n";

        file << "Total Products          : "
             << products.size() << "\n";

        file << "Total E-Waste Weight    : "
             << totalWeight << " kg\n\n";

        file << "----------------------------------------\n";
        file << "WASTE CLASSIFICATION\n";
        file << "----------------------------------------\n";

        file << "Reuse                   : "
             << reuse << "\n";

        file << "Repair                  : "
             << repair << "\n";

        file << "Donate/Sell             : "
             << donate << "\n";

        file << "Component Recovery      : "
             << recovery << "\n";

        file << "Material Recycling      : "
             << recycling << "\n\n";

        file << "----------------------------------------\n";
        file << "RECOVERY INFORMATION\n";
        file << "----------------------------------------\n";

        file << "Estimated Recovery Value : ";

        if (recovery > 0 || recycling > 0) {
            file << "Rs. " << fixed << setprecision(2)
                << totalRecoveryValue << "\n";
        }
        else {
            file << "No value as per the decision.\n";
        }

        file << "Hazardous Components     : " << hazardousCount << "\n\n";

        file << "\n========================================\n";

        file.close();

        cout << "\nReport generated successfully!";
        cout << "\nFile: ewaste_report.txt\n";
    }
};

// input functions
Component* createComponent(int componentID) {

    int choice;
    double weight;
    double condition;
    int quantity;

    cout << "\nSelect Component Type";
    cout << "\n1. RAM";
    cout << "\n2. ROM";
    cout << "\n3. Battery";
    cout << "\n4. Charger";
    cout << "\n5. Screen";

    cout << "\nEnter choice: ";
    cin >> choice;

    cout << "Enter weight of ONE component (kg): ";
    cin >> weight;

    cout << "Enter condition - How good is it (0-100%): ";
    cin >> condition;

    cout << "Enter quantity: ";
    cin >> quantity;

    // We use the new keyword here because we want to create an object dynamically and return its address (pointer).
    if (choice == 1)
        return new RAM(componentID, weight, condition, quantity);
    else if (choice == 2)
        return new ROM(componentID, weight, condition, quantity);
    else if (choice == 3)
        return new Battery(componentID, weight, condition, quantity);
    else if (choice == 4)
        return new Charger(componentID, weight, condition, quantity);
    else if (choice == 5)
        return new Screen(componentID, weight, condition, quantity);
    else
        return nullptr;
}

EWaste* createProduct() {

    int type;
    int id;
    string name;
    string company;
    double weight;
    int quantity;
    double damage;

    cout << "\n========================================";
    cout << "\n          ADD E-WASTE PRODUCT";
    cout << "\n========================================";

    cout << "\n1. Laptop";
    cout << "\n2. Mobile";
    cout << "\n3. TV";
    cout << "\n4. Tablet";

    cout << "\nEnter product type: ";
    cin >> type;

    cout << "Enter Product ID: ";
    cin >> id;

    cout << "Enter Product Name: ";
    cin >> name;

    cout << "Enter Company: ";
    cin >> company;

    cout << "Enter Weight (kg): ";
    cin >> weight;

    cout << "Enter Quantity: ";
    cin >> quantity;

    cout << "Enter Damage Percentage (0-100): ";
    cin >> damage;

    EWaste* product = nullptr;

    if (type == 1)
        product = new Laptop(id, name, company, weight, quantity, damage);
    else if (type == 2)
        product = new Mobile(id, name, company, weight, quantity, damage);
    else if (type == 3)
        product = new TV(id, name, company, weight, quantity, damage);
    else if (type == 4)
        product = new Tablet(id, name, company, weight, quantity, damage);
    else
        return nullptr;

    int numberOfComponents;

    cout << "\nHow many components does this product have? ";
    cin >> numberOfComponents;

    for (int i = 1; i <= numberOfComponents; i++) {
        cout << "\n========== COMPONENT " << i << " ==========\n";
        Component* component = createComponent(i);
        product->addComponent(component);
    }

    return product;
}

int main() {

    vector<EWaste*> products;
    CSVManager csvManager;
    RecoveryPlanner recoveryPlanner;
    ReportGenerator reportGenerator;

    int choice;

    do {
        cout << "\n\n========================================";
        cout << "\n      E-WASTE COLLECTION & RECOVERY";
        cout << "\n              PLANNER";
        cout << "\n========================================";

        cout << "\n1. Add E-Waste Product";
        cout << "\n2. Display All Products";
        cout << "\n3. Generate Recovery Plan";
        cout << "\n4. Generate TXT Report";
        cout << "\n5. Exit";

        cout << "\n\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            EWaste* product =createProduct();
            products.push_back(product);
            csvManager.saveProduct(product);
            csvManager.saveComponents(product);
            cout << "\nProduct successfully added!";
            cout << "\nData saved to CSV files.";
        }

        else if (choice == 2) {
            if (products.empty()) {
                cout << "\nNo products available.";
            }
            else {
                for (EWaste* product : products) {
                    product->display();
                }
            }
        }

        else if (choice == 3) {
            if (products.empty()) {
                cout << "\nNo products available.";
            }
            else {
                int id;
                cout << "\nEnter Product ID: ";
                cin >> id;
                bool found = false;
                for (EWaste* product : products) {
                    if (product->getProductID() == id) {
                        recoveryPlanner.generateRecoveryPlan(product);
                        found = true;
                        break;
                    }
                }
                if (!found)
                    cout << "\nProduct not found.";
            }
        }

        else if (choice == 4) {
            reportGenerator.generateReport(products);
        }

        else if (choice == 5) {
            cout << "\nGenerating final report...";
            reportGenerator.generateReport(products);
            cout << "\nProgram terminated.";
        }

        else {
            cout << "\nInvalid choice.";
        }

    } while (choice != 5);

    for (EWaste* product : products)
        delete product;

    return 0;
}
