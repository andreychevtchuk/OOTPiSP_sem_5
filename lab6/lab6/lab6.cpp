#include <iostream>
/**
 * Каждый отдельный продукт семейства продуктов должен иметь базовый интерфейс.
 * Все вариации продукта должны реализовывать этот интерфейс.
 */
class AbstractProductRect {
public:
    virtual ~AbstractProductRect() {};
    virtual std::string UsefulFunctionRect() const = 0;
    virtual AbstractProductRect* clone() const = 0; //добавление паттерна prototype
};

/**
 * Конкретные продукты создаются соответствующими Конкретными Фабриками.
 */
class ConcreteProductRect1 : public AbstractProductRect {
public:
    std::string UsefulFunctionRect() const override {
        return "Нарисован Прямоугольник1.";
    }
    ConcreteProductRect1* clone() const { return new ConcreteProductRect1(*this); } //добавление функционала паттерна prototype
};

class ConcreteProductRect2 : public AbstractProductRect {
public:
    std::string UsefulFunctionRect() const override {
        return "Нарисован Прямоугольник2.";
    }
    ConcreteProductRect2* clone() const { return new ConcreteProductRect2(*this); } //добавление функционала паттерна prototype
};

class AbstractProductLine {
public:
    virtual ~AbstractProductLine() {};
    virtual std::string UsefulFunctionLine() const = 0;
    virtual AbstractProductLine* clone() const = 0; //добавление паттерна prototype
};

/**
 * Конкретные Продукты создаются соответствующими Конкретными Фабриками.
 */
class ConcreteProductLine1 : public AbstractProductLine {
public:
    std::string UsefulFunctionLine() const override {
        return "Нарисована линия B1.";
    }
    ConcreteProductLine1* clone() const { return new ConcreteProductLine1(*this); } //добавление функционала паттерна prototype
};

class ConcreteProductLine2 : public AbstractProductLine {
public:
    std::string UsefulFunctionLine() const override {
        return "Нарисована линия B2.";
    }
    ConcreteProductLine2* clone() const { return new ConcreteProductLine2(*this); } //добавление функционала паттерна prototype
};

class AbstractProductEllipse {
public:
    virtual ~AbstractProductEllipse() {};
    virtual std::string UsefulFunctionEllipse() const = 0;
    virtual AbstractProductEllipse* clone() const = 0; //добавление паттерна prototype
};
class ConcreteProductEllipse1 : public AbstractProductEllipse {
public:
    std::string UsefulFunctionEllipse() const override {
        return "Нарисован Овал1.";
    }
    ConcreteProductEllipse1* clone() const { return new ConcreteProductEllipse1(*this); } //добавление функционала паттерна prototype
};
class ConcreteProductEllipse2 : public AbstractProductEllipse {
public:
    std::string UsefulFunctionEllipse() const override {
        return "Нарисован Овал2.";
    }
    ConcreteProductEllipse2* clone() const { return new ConcreteProductEllipse2(*this); } //добавление функционала паттерна prototype
};

class AbstractProductText {
public:
    virtual ~AbstractProductText() {};
    virtual std::string UsefulFunctionText() const = 0;
    virtual AbstractProductText* clone() const = 0; //добавление паттерна prototype
};

/**
 * Конкретные продукты создаются соответствующими Конкретными Фабриками.
 */
class ConcreteProductText1 : public AbstractProductText {
public:
    std::string UsefulFunctionText() const override {
        return "Написан Текст1.";
    }
    ConcreteProductText1* clone() const { return new ConcreteProductText1(*this); } //добавление функционала паттерна prototype
};

class ConcreteProductText2 : public AbstractProductText {
public:
    std::string UsefulFunctionText() const override {
        return "Написан Текст2.";
    }
    ConcreteProductText2* clone() const { return new ConcreteProductText2(*this); } //добавление функционала паттерна prototype
};
/**
 * Интерфейс Абстрактной Фабрики объявляет набор методов, которые возвращают
 * различные абстрактные продукты. Эти продукты называются семейством и связаны
 * темой или концепцией высокого уровня. Продукты одного семейства обычно могут
 * взаимодействовать между собой. Семейство продуктов может иметь несколько
 * вариаций, но продукты одной вариации несовместимы с продуктами другой.
 */
class AbstractFactory {
public:
    virtual AbstractProductRect* CreateProductRect() const = 0;
    virtual AbstractProductLine* CreateProductLine() const = 0;
    virtual AbstractProductEllipse* CreateProductEllipse() const = 0;
    virtual AbstractProductText* CreateProductText() const = 0;
};
/**
 * Конкретная Фабрика производит семейство продуктов одной вариации. Фабрика
 * гарантирует совместимость полученных продуктов. Обратите внимание, что
 * сигнатуры методов Конкретной Фабрики возвращают абстрактный продукт, в то
 * время как внутри метода создается экземпляр конкретного продукта.
 */
class ConcreteFactory1 : public AbstractFactory {
public:
    AbstractProductRect* CreateProductRect() const override {
        return new ConcreteProductRect1();
    }
    AbstractProductLine* CreateProductLine() const override {
        return new ConcreteProductLine1();
    }
    AbstractProductEllipse* CreateProductEllipse() const override {
        return new ConcreteProductEllipse1();
    }
    AbstractProductText* CreateProductText() const override {
        return new ConcreteProductText1();
    }
};

/**
 * Каждая Конкретная Фабрика имеет соответствующую вариацию продукта.
 */
class ConcreteFactory2 : public AbstractFactory {
public:
    AbstractProductRect* CreateProductRect() const override {
        return new ConcreteProductRect2();
    }
    AbstractProductLine* CreateProductLine() const override {
        return new ConcreteProductLine2();
    }
    AbstractProductEllipse* CreateProductEllipse() const override {
        return new ConcreteProductEllipse2();
    }
    AbstractProductText* CreateProductText() const override {
        return new ConcreteProductText2();
    }
};

/**
 * Клиентский код работает с фабриками и продуктами только через абстрактные
 * типы: Абстрактная Фабрика и Абстрактный Продукт. Это позволяет передавать
 * любой подкласс фабрики или продукта клиентскому коду, не нарушая его.
 */

void ClientCode(const AbstractFactory& factory) {
    const AbstractProductRect* product_r = factory.CreateProductRect();
    const AbstractProductLine* product_l = factory.CreateProductLine();
    const AbstractProductEllipse* product_e = factory.CreateProductEllipse();
    const AbstractProductText* product_t = factory.CreateProductText();
    const AbstractProductText* product_t2 = product_t->clone();
    std::cout << product_r->UsefulFunctionRect() << "\n";
    std::cout << product_l->UsefulFunctionLine() << "\n";
    std::cout << product_e->UsefulFunctionEllipse() << "\n";
    std::cout << product_t->UsefulFunctionText() << "\n";
    std::cout << product_t2->UsefulFunctionText() << "\n";
    delete product_r;
    delete product_l;
    delete product_e;
    delete product_t;
    delete product_t2;
}

int main() {
    setlocale(LC_ALL, "russian");
    std::cout << "Клиент: Тестирование кода клиента с первым типом фабрики:\n";
    ConcreteFactory1* f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Клиент: Тестирование кода клиента со вторым типом фабрики:\n";
    ConcreteFactory2* f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
    return 0;
}