#include <iostream>
class Handler
{
public:
  virtual ~Handler() {}
  
  virtual void setHandler( Handler *s )
  {
    successor = s;
  }
  
  virtual void handleRequest()
  {
    if (successor != 0)
    {
      successor->handleRequest();
    }
  }
  // ...
private:
  Handler *successor;
};

/*
 * Concrete Handlers
 * handle requests they are responsible for
 */
class ConcreteHandler1 : public Handler
{
public:
  ~ConcreteHandler1() {}
  
  bool canHandle()
  {
    // ...
    return false;
  }
  
  virtual void handleRequest()
  {
    if ( canHandle() )
    {
      std::cout << "Handled by Concrete Handler 1" << std::endl;
    }
    else
    {
      std::cout << "Cannot be handled by Handler 1" << std::endl;
      Handler::handleRequest();
    }
    // ...
  }
  // ...
};

class ConcreteHandler2 : public Handler
{
public:
  ~ConcreteHandler2() {}
  
  bool canHandle()
  {
    // ...
    return true;
  }
  
  virtual void handleRequest()
  {
    if ( canHandle() )
    {
      std::cout << "Handled by Handler 2" << std::endl;
    }
    else
    {
      std::cout << "Cannot be handled by Handler 2" << std::endl;
      Handler::handleRequest();
    }
    // ...
  }
  
  // ...
};


void test1()
{
    ConcreteHandler1 handler1;
    ConcreteHandler2 handler2;
    
    handler1.setHandler(&handler2);
    handler1.handleRequest();
std::cout << "Тест 1 пройден: ConcreteHandler1 передал запрос ConcreteHandler2" << std::endl;
}

void test2()
{
    ConcreteHandler1 handler1;
    ConcreteHandler2 handler2;
    
    handler1.setHandler(&handler2);
    handler2.handleRequest();
std::cout << "Тест 2 пройден: ConcreteHandler2 обработал запрос" << std::endl;
}

void test3()
{
    ConcreteHandler1 handler1;
    ConcreteHandler2 handler2;
    
   handler1.canHandle = [](/* параметры */) { return true; };
    
    handler1.setHandler(&handler2);
    handler1.handleRequest();
    std::cout << "Тест 3 пройден: ConcreteHandler1 обработал запрос сам" << std::endl;
}

int main()
{
    test1();
    test2();
    test3();
    
    return 0;
}
