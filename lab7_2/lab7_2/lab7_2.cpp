#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Header
{
public:
    string Head;
    Header(string header)
    {
        this->Head = header;
    };
    void info() {
        cout << this->Head << " Header" << endl;

    }
};

class Block
{
public:
    string SQLresult;
    Block(string result)
    {
        this->SQLresult = result;
    };
    void info() {
        cout << this->SQLresult << " SQLresult" << endl;
    }
};

class Ending
{
public:
    string End;
    Ending(string end)
    {
        this->End = end;
    };
    void info() {
        cout << this->End << " Ending" << endl;
    }
};

class  Report
{
public:
    vector<Header> vi;
    vector<Block> va;
    vector<Ending> vh;
    void info() {
        int i;
        for (i = 0; i < vi.size(); ++i)  vi[i].info();
        for (i = 0; i < va.size(); ++i)  va[i].info();
        for (i = 0; i < vh.size(); ++i)  vh[i].info();
    }
};

class ConcreteBuilder
{
protected:
    Report* p;
public:
    ConcreteBuilder() : p(0) {}
    virtual ~ConcreteBuilder() {}
    virtual void createReport() {}
    virtual void buildHeader() {}
    virtual void buildBlock() {}
    virtual void buildEnding() {}
    virtual  Report* getReport() { return p; }
};


class HtmlBuilder : public ConcreteBuilder
{
public:
    void createReport() { p = new  Report; }
    void buildHeader() { p->vi.push_back(Header("html header")); }
    void buildBlock() { p->va.push_back(Block("htmlresult")); }
    void buildEnding() { p->vh.push_back(Ending("htmlending")); }
};


class TxtBuilder : public ConcreteBuilder
{
public:
    void createReport() { p = new  Report; }
    void buildHeader() { p->vi.push_back(Header("txtheader")); }
    void buildBlock() { p->va.push_back(Block("txtresult")); }
    void buildEnding() { p->vh.push_back(Ending("txtending")); }
};

class XlsBuilder : public ConcreteBuilder
{
public:
    void createReport() { p = new  Report; }
    void buildHeader() { p->vi.push_back(Header("xlsheader")); }
    void buildBlock() { p->va.push_back(Block("xlsresult")); }
    void buildEnding() { p->vh.push_back(Ending("xlsending")); }
};

class DocBuilder : public ConcreteBuilder
{
public:
    void createReport() { p = new  Report; }
    void buildHeader() { p->vi.push_back(Header("docheader")); }
    void buildBlock() { p->va.push_back(Block("docresult")); }
    void buildEnding() { p->vh.push_back(Ending("docending")); }
};


class Director
{
public:
    Report* createReport(ConcreteBuilder& builder)
    {
        builder.createReport();
        builder.buildHeader();
        builder.buildBlock();
        builder.buildEnding();
        return(builder.getReport());
    }
};


int main()
{
    Director dir;
    HtmlBuilder report1_builder;
    TxtBuilder report2_builder;
    XlsBuilder report3_builder;
    DocBuilder report4_builder;

    Report* report1 = dir.createReport(report1_builder);
    Report* report2 = dir.createReport(report2_builder);
    Report* report3 = dir.createReport(report3_builder);
    Report* report4 = dir.createReport(report4_builder);
    cout << "Html Report:" << endl;
    report1->info();
    cout << "\nTxt Report:" << endl;
    report2->info();
    cout << "\nXls Report:" << endl;
    report3->info();
    cout << "\nDoc Report:" << endl;
    report4->info();
    return 0;
}