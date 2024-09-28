/*

 **Single Responsibility Principle**

// Definition: A class should have one and only one reason to change, meaning that a class should have only one job.

// Example: Imagine a restaurant where the chef also serves as the waiter, cashier and dishwasher.

 While it's possible for one person to do all these tasks, it's inefficient and prone to errors.
 In an ideal restaurant, each person has a specific role: the chef cooks, the waiter serves and the cashier handles payments.
 Each person has a single responsibility, making the whole operation more efficient and manageable.
*/

// Bad
#include <iostream>
#include <string>

using namespace std;

class UserSettings_bad {
public:
    string user;

    UserSettings_bad(const string& userInput) {
        user = userInput;
    }

    void changeSettings(const string& settings) {
        if (verifyCredentials()) {
            // Change the settings
        }
    }

private:
    bool verifyCredentials() {
        // Verification logic
        return true;
    }
};


// Good

#include <iostream>
#include <string>

using namespace std;

class UserAuth {
public:
    string user;

    UserAuth(const string& userInput) {
        user = userInput;
    }

    bool verifyCredentials() {
        // Verification logic
        return true;
    }
};

class UserSettings {
public:
    string user;
    UserAuth auth;

    UserSettings(const string& userInput) : auth(userInput) {
        user = userInput;
    }

    void changeSettings(const string& settings) {
        if (auth.verifyCredentials()) {
            // Change the settings
        }
    }
}; 