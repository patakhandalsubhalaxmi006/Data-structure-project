#include <iostream>
#include <string>
using namespace std;


struct Customer {
    int token;
    string name;
    Customer* next;

    Customer(int t, const string& n) {
        token = t;
        name = n;
        next = nullptr;
    }
};


class BankQueue {
private:
    Customer* front; 
    Customer* rear;  
    int nextToken;   

public:
    BankQueue() {
        front = nullptr;
        rear = nullptr;
        nextToken = 1;
    }

   
    void addCustomer(const string& name) {
        Customer* newCustomer = new Customer(nextToken, name);

        if (isEmpty()) {
            front = rear = newCustomer;
        } else {
            rear->next = newCustomer;
            rear = newCustomer;
        }

        cout << "Customer added. Name: " << name
             << ", Token: " << nextToken << endl;
        nextToken++;
    }

  
    void serveCustomer() {
        if (isEmpty()) {
            cout << "No customers in the queue.\n";
            return;
        }

        Customer* temp = front;
        cout << "Serving customer: " << temp->name
             << " (Token: " << temp->token << ")\n";

        front = front->next;
        if (front == nullptr) { 
            rear = nullptr;
        }

        delete temp;
    }

    void displayQueue() const {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Current queue:\n";
        Customer* current = front;
        while (current != nullptr) {
            cout << "Token: " << current->token
                 << ", Name: " << current->name << endl;
            current = current->next;
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    ~BankQueue() {
        while (!isEmpty()) {
            serveCustomer();
        }
    }
};

int main() {
    BankQueue bankQueue;
    int choice;
    string name;

    do {
        cout << "\n--- Bank Queue Simulation ---\n";
        cout << "1. Add new customer to queue\n";
        cout << "2. Serve next customer\n";
        cout << "3. Display queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }

        switch (choice) {
        case 1:
            cin.ignore(); 
            cout << "Enter customer name: ";
            getline(cin, name);
            bankQueue.addCustomer(name);
            break;

        case 2:
            bankQueue.serveCustomer();
            break;

        case 3:
            bankQueue.displayQueue();
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
