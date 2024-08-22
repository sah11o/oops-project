#include <bits/stdc++.h>
using namespace std;
#include "rdb.h"


//methods for Record class
Record::Record(){}  

Record::Record(const vector<Attr *> &attrs)
{
    attrptr = attrs;
}

// Size method
int Record::size() const
{
    return attrptr.size();
}

// PushAttr method
void Record::pushAttr(Attr *attr)
{
    if(attr==NULL) return;
    attrptr.push_back(attr);
}


// removeAttr method
void Record::removeAttr(const int i)
{
    delete attrptr[i];
    attrptr.erase(attrptr.begin() + i);
}


// ClearAttrs method
void Record::clearAttrs()
{
    for (auto &attr : attrptr)
    {
        delete attr;
    }
    attrptr.clear();
}


// Getters and Setters
vector<Attr *> Record::getAttr() const
{
    return attrptr;
}

Attr *Record::getAttrbyindex(const int i)
{
    return attrptr[i];
}


void Record::setAttr(const int i, Attr *attr)
{
    if(i<attrptr.size())
    attrptr[i] = attr;
    else cout<<"not possible to set "<<endl;
}


bool Record::operator==(const Record &right) const
{
    // Compare each attribute in the records
    if (attrptr.size() != right.attrptr.size())
    {
        return false;
    }
    for (int i = 0; i < attrptr.size(); i++)
    {
        if (*attrptr[i] != *right.attrptr[i])
        {
            return false;
        }
    }
    return true;
}


ostream &operator<<(ostream &os, const Record &record)
{
    for (const auto &attr : record.getAttr())
    {
        os << attr << "\t";
    }
    return os;
}

void Record::printrecord(){
    for (const auto &attr : this->getAttr())
    {
        attr->printattritube();
        cout<<"\t";
    }
    // return os;

}


Record::~Record()
{
    for (auto &attr : attrptr)
    {
        delete attr;
    }
}


//Methods for Relation class
Relation::Relation() : nattrs_(0), nrecs_(0) {}

Relation::Relation(const string &name, const vector<string> &attrnames, const vector<int> &attrinds)
    : nattrs_(attrnames.size()), nrecs_(0), attrnames_(attrnames), attrinds_(attrinds), name_(name) {}

int Relation::nattrs() const { return nattrs_; }

int Relation::nrecs() const { return nrecs_; }

// GetName method
string Relation::getName() const
{
    return name_;
}

// SetName method
void Relation::setName(const string &name)
{
    name_ = name;
}


// GetAttrNames method
vector<string> Relation::getAttrNames() const
{
    return attrnames_;
}

// SetAttrNames method
void Relation::setAttrNames(const vector<string> &attrnames)
{
    attrnames_ = attrnames;
    nattrs_ = attrnames.size();
}

void Relation::addAttr(const string& attrname)
{
    attrnames_.push_back(attrname);
    ++nattrs_;
}


// SetAttrInds method
void Relation::setAttrInds(const vector<int> &attrinds)
{
    attrinds_ = attrinds;
}

void Relation::addAttrInd(const int& attrindex)
{
    attrinds_.push_back(attrindex);
}

// GetAttrInds method
vector<int> Relation::getAttrInds() const
{
    return attrinds_;
}


void Relation::clearRecords()
{
    for (auto &rec : recs_)
    {
        delete rec;
    }
    recs_.clear();
    nrecs_ = 0;
}

// AddRecord method
void Relation::addRecord(Record *rec)
{
    recs_.push_back(rec);
    ++nrecs_;
}


// RemoveRecord method
void Relation::removeRecord(const int i)
{
    auto it = recs_.begin();
    advance(it, i);
    delete *it;
    recs_.erase(it);
    --nrecs_;
}

list<Record *> Relation::getRecords()
{
    return recs_;
}

void Relation::printrelation(){
    for(auto &it:attrnames_) cout<<(it)<<"\t";
    cout<<endl;
    for(auto &it:recs_) cout<<(*it)<<endl;
}

// 1. Union: All records of both R1 and R2.
Relation* union_(Relation *R1, Relation *R2)
{ // Check if the schemas are the same
    if (R1->getAttrNames() != R2->getAttrNames())
    {
        cerr << "Error: Cannot perform union operation on relations with different schemas\n";
        return NULL;
    }

    Relation *result = new Relation();
    result->setName("Union ("+R1->getName() + " , "+ R2->getName()+")"); // Use the name of the first relation

    // Add attribute names and indices
    result->setAttrNames(R1->getAttrNames());
    result->setAttrInds(R1->getAttrInds());

    // Add records from R1
    for (Record *rec : R1->getRecords())
    {
        result->addRecord(new Record(*rec));
    }

    // Add records from R2 that are not already in R1
    for (Record *rec : R2->getRecords())
    {
        bool found = false;
        for (Record *r : result->getRecords())
        {
            if (*r == *rec)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            result->addRecord(new Record(*rec));
        }
    }
    return result;
}



// 2. Difference: Records in R1 but not in R2.
Relation* difference(Relation *R1, Relation *R2)
{ // Check if R1 and R2 have the same schema
    if (R1->getAttrNames() != R2->getAttrNames() || R1->getAttrInds() != R2->getAttrInds())
    {
        cout << "Error: schemas of R1 and R2 are not the same." << endl;
        return NULL;
    }

    // Create a new relation with the same schema as R1 and R2
    vector<string> attrnames = R1->getAttrNames();
    vector<int> attrinds = R1->getAttrInds();
    string name = "Difference ("+R1->getName() + " , "+ R2->getName()+")";
    Relation *result = new Relation(name, attrnames, attrinds);

    // Add records from R1 that are not in R2
    for (Record *rec : R1->getRecords())
    {
        bool found = false;
        for (Record *r : R2->getRecords())
        {
            if (*r == *rec)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            result->addRecord(new Record(*rec));
        }
    }

    return result;
}



Relation* cartesianProduct(Relation *r1, Relation *r2)
{
    // Create a new relation
    Relation *res = new Relation();

    // Set the name of the new relation to the concatenation of the names of r1 and r2
    res->setName("CartesianProduct ("+r1->getName() + " , "+ r2->getName()+")");

    // Set the attribute names and indices of the new relation
    vector<string> attrnames;
    vector<int> attrinds;
    for (int i = 0; i < r1->nattrs(); i++)
    {
        attrnames.push_back(r1->getAttrNames()[i]);
        attrinds.push_back(i);
    }
    for (int i = 0; i < r2->nattrs(); i++)
    {
        attrnames.push_back(r2->getAttrNames()[i]);
        attrinds.push_back(i + r1->nattrs());
    }
    res->setAttrNames(attrnames);
    res->setAttrInds(attrinds);

    // Add the cartesian product of the records of r1 and r2 to the new relation
    for (auto r1rec : r1->getRecords())
    {
        for (auto r2rec : r2->getRecords())
        {
            vector<Attr *> attrs;
            for (auto attr : r1rec->getAttr())
            {
                attrs.push_back(attr);
            }
            for (auto attr : r2rec->getAttr())
            {
                attrs.push_back(attr);
            }
            Record *rec = new Record(attrs);
            res->addRecord(rec);
        }
    }

    return res;
}


// 4. Projection: New relation with a subset of columns.
Relation* projection(Relation *r1, list<string> &projectattrs)
{
        int i;
    vector<int> projIndices;
    for (auto attrName : projectattrs)
    {
        i=0;
        // auto it = find(r1->getAttrNames().begin(), r1->getAttrNames().end(), attrName);
        for(auto it:r1->getAttrNames()){
            if(attrName==r1->getAttrNames()[i]) break;
            else i++;
        }
        if(i==r1->getAttrNames().size()) {
             cerr << "Error: Attribute " << attrName << " not found in relation.\n";
            return NULL;

        }
       int index=i;
        // cout<<*it<<endl;
        // if (it == r1->getAttrNames().end())
        // {
        //     cerr << "Error: Attribute " << attrName << " not found in relation.\n";
        //     return NULL;
        // }
        // int index = distance((r1->getAttrNames()).begin(), it);
        // cout<<"index found"<<index<<endl;
        projIndices.push_back(index);
    }

    vector<string> projAttrNames;
    for (auto index : projIndices)
    {
        cout<<(r1->getAttrNames())[index]<<endl;
        projAttrNames.push_back((r1->getAttrNames())[index]);
    }

    vector<int> projAttrInds;
    for (auto index : projIndices)
    {
        projAttrInds.push_back(r1->getAttrInds()[index]);
    }

    Relation *projRelation = new Relation("Projection("+r1->getName()+")", projAttrNames, projAttrInds);

     vector<Attr *> projAttrs;
    for (auto rec : r1->getRecords())
    {
        // vector<Attr *> projAttrs;
        for (auto index : projIndices)
        {
            projAttrs.push_back(rec->getAttrbyindex(index));
        }
        projRelation->addRecord(new Record(projAttrs));
        projAttrs.clear();
    }

    return projRelation;
}


// 6. Rename: rename an attribute in schema
Relation* rename_(Relation *r1, string s1, string s2)
{
    vector<string> attrnames = r1->getAttrNames();
    for (int i = 0; i < attrnames.size(); i++)
    {
        if (attrnames[i] == s1)
        {
            attrnames[i] = s2;
        }
    }
    r1->setAttrNames(attrnames);
    return r1;
}



//should include selection method

// 5. Selection: New relation with a subset of records matching a boolean expression in DNF form.

Relation* selection(Relation *r1, DNFformula *f)
{ 
    // Create a new relation with the same schema as the input relation
    vector<string> attrnames = r1->getAttrNames();
    vector<int> attrinds = r1->getAttrInds();
    Relation *result = new Relation("Selection("+r1->getName()+")", attrnames, attrinds);

    // Iterate through each record in the relation
    for (Record *rec : r1->getRecords())
    {
        bool satisfiesDNF = false;

        // Check if the record satisfies the DNF formula
        for (list<tuple<string, char, Attr *>> conjuncts : f->ops)
        {
            bool satisfiesCNF = true;

            // Check if the record satisfies the CNF conjunction
            for (tuple<string, char, Attr *> conjunct : conjuncts)
            {
                string attrname = get<0>(conjunct);
                char op = get<1>(conjunct);
                Attr *value = get<2>(conjunct);

                // Find the index of the attribute
                int attrindex = -1;
                for (int i = 0; i < attrnames.size(); i++)
                {
                    if (attrnames[i] == attrname)
                    {
                        attrindex = i;
                        break;
                    }
                }
                if (attrindex == -1)
                {
                    cerr << "Error: Attribute " << attrname << " not found." << endl;
                    return nullptr;
                }

                // Check the comparison operator and apply the comparison
                Attr *recordAttr = rec->getAttrbyindex(attrindex);
                if (recordAttr == nullptr)
                {
                    cerr << "Error: Record attribute is null." << endl;
                    return nullptr;
                }

                bool comparisonResult = false;
                if (op == '=')
                {
                    comparisonResult = (*value == *recordAttr);
                    //if(*value == *recordAttr) cout<<comparisonResult<<attrname<<endl;

                }
                else if (op == '<')
                {
                    comparisonResult = (*recordAttr < *value);
                }
                else if (op == '>')
                {
                    comparisonResult = (*recordAttr > *value);
                }
                else if (op == 'l')
                {
                    comparisonResult = (*recordAttr <= *value);
                }
                else if (op == 'g')
                {
                    comparisonResult = (*recordAttr >= *value);
                }
                else if (op == 'n')
                {
                    comparisonResult = (*value != *recordAttr);
                }
                else
                {
                    cerr << "Error: Invalid comparison operator: " << op << endl;
                    return nullptr;
                }

                satisfiesCNF &= comparisonResult;
            }

            satisfiesDNF |= satisfiesCNF;
            if (satisfiesDNF)
            {
                break;
            }
        }

        // If the record satisfies the DNF formula, add it to the result relation
        if (satisfiesDNF)
        {
            result->addRecord(new Record(*rec));
        }
    }

    return result;
}