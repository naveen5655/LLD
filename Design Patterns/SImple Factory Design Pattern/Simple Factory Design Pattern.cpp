#include <iostream>
#include <string>

using namespace std;

enum class LogLevel {
    DEBUG,
    INFO,
    ERROR
};

class ILogger {
public:
    virtual void log(string msg) = 0;
    virtual ~ILogger() {}
};

class DebugLogger : public ILogger {
public:
    void log(string msg) override {
        cout << "DEBUG : " << msg << "\n";
    }
};

class InfoLogger : public ILogger {
public:
    void log(string msg) override {
        cout << "INFO : " << msg << "\n";
    }
};

class ErrorLogger : public ILogger {
public:
    void log(string msg) override {
        cout << "ERROR : " << msg << "\n";
    }
};

class LoggerFactory {
public:
    ILogger* createLogger(LogLevel pLogLevel) {
        if (pLogLevel == LogLevel::DEBUG)
            return new DebugLogger();
        if (pLogLevel == LogLevel::INFO)
            return new InfoLogger();
        if (pLogLevel == LogLevel::ERROR)
            return new ErrorLogger();
        throw invalid_argument("Invalid LogLevel");
    }
};

int main() {
    
    LoggerFactory factory;

    ILogger* debugLogger = factory.createLogger(LogLevel::DEBUG);
    ILogger* infoLogger = factory.createLogger(LogLevel::INFO);
    ILogger* errorLogger = factory.createLogger(LogLevel::ERROR);

    debugLogger->log("This is a debug log msg");
    infoLogger->log("This is an info log msg");
    errorLogger->log("This is an error log msg");

    delete debugLogger;
    delete infoLogger;
    delete errorLogger;

    return 0;
}

/*
Output:

DEBUG : This is a debug log msg
INFO : This is an info log msg
ERROR : This is an error log msg

*/