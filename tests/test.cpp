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
    return canHandleValue;
  }
  
  void setCanHandleValue(bool value)
  {
    canHandleValue = value;
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
  
private:
  bool canHandleValue = true; // изначальное значение
};


void test1() {
  std::stringstream buffer;
  std::streambuf *sbuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());

  ConcreteHandler1 handler1;
  ConcreteHandler2 handler2;
  
  handler1.setHandler( &handler2 );
  handler1.handleRequest();

  std::string output = buffer.str();
  std::cout.rdbuf(sbuf);

  if (output == "Cannot be handled by Handler 1nHandled by Handler 2n") {
    std::cout << "Test 1 passedn";
  } else {
    std::cout << "Test 1 failedn";
  }
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
    
    // Устанавливаем, что handler2 не может обработать запрос
    handler2.setCanHandleValue(false);
    
    handler1.setHandler(&handler2);
    handler1.handleRequest();
    std::cout << "Тест 3 пройден: Ни один из обработчиков не может обработать запрос" << std::endl;
}

int main()
{
    test1();
    test2();
    test3();
    
    return 0;
}
