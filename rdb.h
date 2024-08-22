#include <bits/stdc++.h>
using namespace std;

class Attr
{protected: string dtype;
public:
    // Base class for attributes
     Attr(string s);
     string getvalue()const;
     virtual void printattritube() const=0;
    virtual bool operator==(const Attr &right) const = 0;
    virtual bool operator!=(const Attr &right) const = 0;
    virtual bool operator<(const Attr &right) const = 0;
    virtual bool operator<=(const Attr &right) const = 0;
    virtual bool operator>(const Attr &right) const = 0;
    virtual bool operator>=(const Attr &right) const = 0;
    friend ostream& operator<<(ostream &os,  Attr* attr) ;
    virtual ~Attr() {}
};



class IntAttr : public Attr
{
private:
    int value_;
public:
    IntAttr(int value,string d="int");

    IntAttr(IntAttr &t); //copy constructor

    void printattritube()const override;

    int getvalue()const;

    bool operator==(const Attr &right) const override;
 

    bool operator!=(const Attr &right) const override;
  

    bool operator<(const Attr &right) const override;
  

    bool operator<=(const Attr &right) const override;
  

    bool operator>(const Attr &right) const override;
 
    bool operator>=(const Attr &right) const override;
   

   
};









class StringAttr : public Attr
{
private:
    string value_;
public:
    StringAttr(string value,string d="string");

    StringAttr(StringAttr &t);

    
    void printattritube()const override;

    string getvalue()const;

     bool operator==(const Attr &right) const override;
 
    bool operator!=(const Attr &right) const override;
  

    bool operator<(const Attr &right) const override;
   

    bool operator<=(const Attr &right) const override;
   
    bool operator>(const Attr &right) const override;
 
    bool operator>=(const Attr &right) const override;
  

    // StringAttr* clone() const override;
  
//    ~StringAttr();
};


class FloatAttr : public Attr
{
private:
    float value_;
public:
    FloatAttr(float value,string d="float");

    FloatAttr(FloatAttr &t); //copy constructor

    void printattritube()const override;

    float getvalue() const;

    bool operator==(const Attr &right) const override;
   
    bool operator!=(const Attr &right) const override;
  
    bool operator<(const Attr &right) const override;
  

    bool operator<=(const Attr &right) const override;
  

    bool operator>(const Attr &right) const override;
  

    bool operator>=(const Attr &right) const override;
  
    // FloatAttr* clone() const override ;
     

    // ~FloatAttr();
};


struct DNFformula
{
    list<list<tuple<string, char, Attr *>>> ops;
};






class Record{
private:
    vector<Attr *> attrptr;
public:
    Record();
    Record(const vector<Attr*>& attrs);
    int size() const;
    void pushAttr(Attr *attr);
    void removeAttr(const int i);
    void clearAttrs();
    vector<Attr*> getAttr() const;
    Attr* getAttrbyindex(const int i);
    void setAttr(const int i, Attr *attr);
    bool operator==(const Record &right) const;
     friend ostream& operator<<(ostream &os, const Record& record) ;
    void printrecord();
    ~Record();
    friend class Relation;
};




class Relation{
private:
    int nattrs_, nrecs_;
    vector<string> attrnames_;
    vector<int> attrinds_;
    list<Record *> recs_;
    string name_;
public:
    Relation();
    Relation(const string &name, const vector<string> &attrnames, const vector<int> &attrinds);
    int nattrs() const;
    int nrecs() const; 
    void setName(const string &name);
    string getName() const;
    void setAttrNames(const vector<string> &attrnames);
    void addAttr(const string& attrname);
    vector<string> getAttrNames() const;
    void setAttrInds(const vector<int> &attrinds);
    void addAttrInd(const int& attrindex);
    vector<int> getAttrInds() const;
    void clearRecords();
    void addRecord(Record *rec);
    void removeRecord(const int i);
    list<Record *> getRecords();
    void printrelation();
    friend Relation *union_(Relation *r1, Relation *r2);
    friend Relation *difference(Relation *r1, Relation *r2);
    friend Relation *cartesianProduct(Relation *r1, Relation *r2);
    friend Relation *projection(Relation *r1, list<string> &projectattrs);
    friend Relation *selection(Relation *r1, DNFformula *f);
    friend Relation *rename_(Relation *r1, string s1, string s2);
    friend Relation *naturalJoin(Relation *r1, Relation *r2, list<string> joinattrs);
    friend ostream &operator<<(ostream &out, const Relation &r);
};
