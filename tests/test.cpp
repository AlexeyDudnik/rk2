#include <iostream>
#include <sstream>

class Handler {
public:
    virtual ~Handler() {}

    virtual void setHandler(Handler* s) {
        successor = s;
    }

    virtual void handleRequest() {
        if (successor != nullptr) {
            successor->handleRequest();
        }
    }

private:
    Handler* successor = nullptr;
};

/*
 * Concrete Handlers
 * handle requests they are responsible for
 */
class ConcreteHandler1 : public Handler {
public:
    ~ConcreteHandler1() {}

    bool canHandle() {
        // Simulate some logic to determine if this handler can handle the request
        return false;
    }

    virtual void handleRequest() override {
        if (canHandle()) {
            std::cout << "Handled by Concrete Handler 1" << std::endl;
        } else {
            std::cout << "Cannot be handled by Handler 1" << std::endl;
            Handler::handleRequest();
        }
    }
};

class ConcreteHandler2 : public Handler {
public:
    ~ConcreteHandler2() {}

    bool canHandle() {
        return canHandleValue;
    }

    void setCanHandleValue(bool value) {
        canHandleValue = value;
    }

    virtual void handleRequest() override {
        if (canHandle()) {
            std::cout << "Handled by Handler 2" << std::endl;
        } else {
            std::cout << "Cannot be handled by Handler 2" << std::endl;
            Handler::handleRequest();
        }
    }

private:
    bool canHandleValue = true;
};

void test1() {
    std::stringstream buffer;
    std::streambuf* sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    ConcreteHandler1 handler1;
    ConcreteHandler2 handler2;

    handler1.setHandler(&handler2);
    handler1.handleRequest();

    std::string output = buffer.str();
    std::cout.rdbuf(sbuf);

    if (output == "Cannot be handled by Handler 1\nHandled by Handler 2\n") {
        std::cout << "Test 1 passed\n";
    } else {
        std::cout << "Test 1 failed\n";
    }
}

void test2() {
    std::stringstream buffer;
    std::streambuf* sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    ConcreteHandler1 handler1;
    handler1.handleRequest();

    std::string output = buffer.str();
    std::cout.rdbuf(sbuf);

    if (output == "Cannot be handled by Handler 1\n") {
        std::cout << "Test 2 passed\n";
    } else {
        std::cout << "Test 2 failed\n";
    }
}

void test3() {
    std::stringstream buffer;
    std::streambuf* sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    ConcreteHandler2 handler2;
    handler2.handleRequest();

    std::string output = buffer.str();
    std::cout.rdbuf(sbuf);

    if (output == "Handled by Handler 2\n") {
        std::cout << "Test 3 passed\n";
    } else {
        std::cout << "Test 3 failed\n";
    }
}

int main() {
    test1();
    test2();
    test3();

    return 0;
}
