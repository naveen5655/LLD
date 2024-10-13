#include <iostream>
#include <mutex>
using namespace std;

class PaymentGatewayManager
{

private:
    PaymentGatewayManager()
    {
        cout << "Payment Gateway Manager initialized.\n";
    }

    static PaymentGatewayManager *instance;

    static mutex mtx;

public:
    static PaymentGatewayManager *getInstance()
    {
        if (instance == nullptr)
        {
            mtx.lock();
            if (instance == nullptr) // Double checking
            {
                instance = new PaymentGatewayManager();
            }
            mtx.unlock();
        }
        return instance;
    }

    void processPayment(double amount)
    {
        cout << "Processing payment of $" << amount << " through the payment gateway.\n";
    }
};


// Initialize static members.
PaymentGatewayManager *PaymentGatewayManager::instance = nullptr;

mutex PaymentGatewayManager::mtx;

int main()
{

    PaymentGatewayManager *paymentGateway = PaymentGatewayManager::getInstance();

    paymentGateway->processPayment(100.0);

    // Attempt to create another instance (should return the existing instance)
    PaymentGatewayManager *anotherPaymentGateway = PaymentGatewayManager::getInstance();

    // Check if both instances are the same.
    if (paymentGateway == anotherPaymentGateway)
    {
        cout << "Both instances are the same. Singleton pattern is working" << endl;
    }
    else
    {
        cout << "Singleton pattern is not working correctly" << endl;
    }
    return 0;
}

/*
Payment Gateway Manager initialized.
Processing payment of $100 through the payment gateway.
Both instances are the same. Singleton pattern is working

*/