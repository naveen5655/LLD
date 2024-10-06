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
        void log(string msg) {
            cout << "DEBUG : " << msg << "\n";
        }
};

class InfoLogger : public ILogger {
    public:
        void log(string msg) {
            cout << "INFO : " << msg << "\n";
        }
};

class ErrorLogger : public ILogger {
    public:
        void log(string msg) {
            cout << "ERROR : " << msg << "\n";
        }
};

class ILoggerFactory {
    public:
        virtual ILogger* createLogger() = 0;
};

class DebugLoggerFactory : public ILoggerFactory {
    public:
        ILogger* createLogger() {
            return new DebugLogger();
        }
};

class InfoLoggerFactory : public ILoggerFactory {
    public:
        ILogger* createLogger() {
            return new InfoLogger();
        }
};

class ErrorLoggerFactory : public ILoggerFactory {
    public:
        ILogger* createLogger() {
            return new ErrorLogger();
        }
};

int main() {
    ILoggerFactory* loggerFactory1 = new InfoLoggerFactory;
    ILogger* infoLogger = loggerFactory1->createLogger();

    ILoggerFactory* loggerFactory2 = new ErrorLoggerFactory;
    ILogger* errorLogger = loggerFactory2->createLogger();

    ILoggerFactory* loggerFactory3 = new DebugLoggerFactory;
    ILogger* debugLogger = loggerFactory3->createLogger();

    debugLogger->log("This is a debug log msg");
    infoLogger->log("This is an info log msg");
    errorLogger->log("This is an error log msg");

    delete debugLogger;
    delete infoLogger;
    delete errorLogger;

    return 0;
}

/*

DEBUG : This is a debug log msg
INFO : This is an info log msg
ERROR : This is an error log msg

*/