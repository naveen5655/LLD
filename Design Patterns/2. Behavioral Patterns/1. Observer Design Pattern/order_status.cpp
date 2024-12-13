#include <iostream>
#include <vector>
using namespace std;

// Forward declaration of Order class
class Order;

// Observer interface
class Observer
{
public:
    virtual void update(Order *order) = 0; 
};

// Subject: Order
class Order
{
private:
    int id;
    string status;
    vector<Observer *> observers;

public:
    Order(int id)
    {
        this->id = id;
        this->status = "Order Placed";
    }

    int getId() const
    {
        return id;
    }

    string getStatus()
    {
        return status;
    }

    void setStatus(string newStatus)
    {
        this->status = newStatus;
        notifyObservers();
    }

    void attach(Observer *observer)
    {
        observers.push_back(observer);
    }

    void detach(Observer *observer)
    {
        for (auto it = observers.begin(); it != observers.end(); ++it)
        {
            if (*it == observer)
            {
                observers.erase(it);
                break; // Assuming each observer can be attached only once
            }
        }
    }

    void notifyObservers()
    {
        for (Observer *observer : observers)
        {
            observer->update(this);
        }
    }
};

// Concrete Observer: Customer
class Customer : public Observer
{
private:
    string name;

public:
    Customer(string name)
    {
        this->name = name;
    }
    void update(Order *order)
    {
        cout << "Hello, " << name << "! Order #" << order->getId() << " is now " << order->getStatus() << "\n";
    }
};

// Concrete Observer: Restaurant
class Restaurant : public Observer
{
private:
    string restaurantName;

public:
    Restaurant(string name)
    {
        this->restaurantName = name;
    }

    void update(Order *order)
    {
        cout << "Restaurant " << restaurantName << ": Order #" << order->getId() << " is now " << order->getStatus() << "\n";
    }
};

// Concrete Observer: DeliveryDriver
class DeliveryDriver : public Observer
{
private:
    string driverName;

public:
    DeliveryDriver(string name)
    {
        this->driverName = name;
    }

    
    void update(Order *order)
    {
        cout << "Driver " << driverName << ": Order #" << order->getId() << " is now " << order->getStatus() << "\n";
    }
};

// Concrete Observer: CallCenter
class CallCenter : public Observer
{
public:
    
    void update(Order *order)
    {
        cout << "Call center: Order #" << order->getId() << " is now " << order->getStatus() << "\n";
    }
};

int main()
{
     // Create an order
    Order order1(123);

    // Create customers, restaurants, drivers, and a call center to track the order
    Customer customer1("Customer 1");
    Restaurant restaurant1("Rest 1");
    DeliveryDriver driver1("Driver 1");
    CallCenter callCenter;

    // Attach observers to the order
    order1.attach(&customer1);
    order1.attach(&restaurant1);
    order1.attach(&driver1);
    order1.attach(&callCenter);

    // Simulate order status updates
    order1.setStatus("Out for Delivery");

    // Detach an observer (if needed)
    order1.detach(&callCenter);

    // Simulate more order status updates
    order1.setStatus("Delivered");

    return 0;
}

/*
Hello, Customer 1! Order #123 is now Out for Delivery
Restaurant Rest 1: Order #123 is now Out for Delivery
Driver Driver 1: Order #123 is now Out for Delivery
Call center: Order #123 is now Out for Delivery
Hello, Customer 1! Order #123 is now Delivered
Restaurant Rest 1: Order #123 is now Delivered
Driver Driver 1: Order #123 is now Delivered

*/