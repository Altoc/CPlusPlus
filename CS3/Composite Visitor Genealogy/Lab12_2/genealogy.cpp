// traversing genealogical tree using Composite and Visitors
// Mikhail Nesterenko
// 10/28/2015

//      Ian Whitesel
//      Lab12
//      Spring 2019

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl;
using std::string;
using std::vector;

class Person{ // component
public:
   Person(string firstName,
          Person *spouse,
          Person *father,
          Person *mother):
      firstName_(firstName), spouse_(spouse),
      father_(father), mother_(mother){}
   string getFirstName(){return firstName_;}
   Person *getSpouse(){return spouse_;}
   void setSpouse(Person *spouse){spouse_=spouse;}
   Person *getFather(){return father_;}
   Person *getMother(){return mother_;}

   virtual void accept(class PersonVisitor *)=0;
   virtual ~Person(){}

private:
   string firstName_;
   Person *spouse_;
   Person *father_;
   Person *mother_;
};

// composites

// man has a last name
class Man: public Person{
public:
   Man(string lastName,
       string firstName,
       Person *spouse,
       Person *father, Person *mother):
      lastName_(lastName),
      Person(firstName, spouse, father, mother){}
   string getLastName(){return lastName_;}
   void accept(class PersonVisitor *visitor) override;
private:
   string lastName_;
};

// woman has a list of children
class Woman: public Person{
public:
   Woman(vector<Person *> children,
       string firstName,
       Person *spouse,
       Person *father, Person *mother):
       children_(children),
       Person(firstName, spouse, father, mother){}
   const vector<Person *> & getChildren()
                          {return children_;}
   void setChildren(const vector<Person *> &children)
                              {children_ = children;}
   void accept(class PersonVisitor *visitor) override;
private:
   vector<Person *> children_;
};

// abstract visitor
class PersonVisitor{
public:
   virtual void visit(Man*)=0;
   virtual void visit(Woman*)=0;
   virtual ~PersonVisitor(){}
};

// composite methods that define traversal
void Man::accept(PersonVisitor *visitor)
                    {visitor->visit(this);}

void Woman::accept(PersonVisitor *visitor){
   // children traversal through mother only
   // father's children are not traversed so as not
   // to traverse them twice: for mother and father

   visitor->visit(this);
   // traversing descendants
   for(auto child : children_)
      child->accept(visitor);
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her
// spouse if she is married
// or by her father if she is not
class MatchMaker: public PersonVisitor{
public:
   MatchMaker(Woman* matron, string f_1, string l_1, string f_2, string l_2){
                matron_ = matron; firstname1_ = f_1; lastname1_ = l_1; firstname2_ = f_2; lastname2_ = l_2;
        }
   void visit(Man *m) override {
        if(firstname1_ == firstname2_ && lastname1_ == lastname2_){
                std::cout<<"People cannot marry themselves!"<<std::endl;
                exit(0);
        } else if(firstname1_ == m->getFirstName() && lastname1_ == m->getLastName()){
                std::cerr<<"I have found candidate 1, it is "<<m->getFirstName()<<" "<<m->getLastName()<<endl;
                if(m->getSpouse() != nullptr){
                        std::cout<<m->getFirstName()<<" "<<m->getLastName()<<" is already married, no match."<<std::endl;
                        exit(0);
                } else if(firstname2_ == m->getFather()->getFirstName()){
                        if(firstname2_ == m->getMother()->getFirstName()){
                                std::cout<<"Canidates cannot marry parents!"<<std::endl;
                                exit(0);
                        }
                        std::cout<<"Canidates cannot marry parents!"<<std::endl;
                        exit(0);
                } else {
                        std::cerr<<"looking for candidate 2..."<<std::endl;
                        MatchMaker *mm = new MatchMaker(matron_, firstname1_, lastname1_, firstname2_, lastname2_);
                        matron_->accept(mm);
                }
        } else if(firstname2_ == m->getFirstName() && lastname2_ == m->getLastName()){
                std::cerr<<"I have found candidate 2, it is "<<m->getFirstName()<<" "<<m->getLastName()<<endl;
                if(m->getSpouse() != nullptr){
                        std::cout<<m->getFirstName()<<" "<<m->getLastName()<<" is already married, no match."<<std::endl;
                        exit(0);
                } else {
                        std::cout<<"These two can be married!"<<std::endl;
                        exit(0);
                }
        }
   }
   void visit(Woman *w) override {
        string first_name, last_name;
        first_name = w->getFirstName();
        if (w->getSpouse() != nullptr){
                last_name = static_cast<Man *>(w->getSpouse())->getLastName();
        }else if (w->getFather() != nullptr){
                last_name = static_cast<Man *>(w->getFather())->getLastName();
        } else {
                last_name = "Doe";
        }
        if(firstname1_ == firstname2_ && lastname1_ == lastname2_){
                std::cout<<"People cannot marry themselves!"<<std::endl;
                exit(0);
        } else if(firstname1_ == first_name && lastname1_ == last_name){
                //std::cerr<<"I have found candidate 1, it is "<<first_name<<" "<<last_name<<endl;
                if(w->getSpouse() != nullptr){
                        std::cout<<first_name<<" "<<last_name<<" is already married, no match."<<std::endl;
                        exit(0);
                } else if(firstname2_ == w->getFather()->getFirstName()){
                        if(firstname2_ == w->getMother()->getFirstName()){
                                std::cout<<"Canidates cannot marry parents!"<<std::endl;
                                exit(0);
                        }
                        std::cout<<"Canidates cannot marry parents!"<<std::endl;
                        exit(0);
                } else {
                //      std::cerr<<"looking for candidate 2..."<<std::endl;
                        MatchMaker *mm = new MatchMaker(matron_, firstname1_, lastname1_, firstname2_, lastname2_);
                        matron_->accept(mm);
                }
        } else if(firstname2_ == first_name && lastname2_ == last_name){
                //std::cerr<<"I have found candidate 2, it is "<<first_name<<" "<<last_name<<endl;
                if(w->getSpouse() != nullptr){
                        std::cout<<first_name<<" "<<last_name<<" is already married, no match."<<std::endl;
                        exit(0);
                } else {
                        std::cout<<"These two can be married!"<<std::endl;
                        exit(0);
                }
        }
   }
private:
        Woman* matron_;
        string firstname1_, lastname1_, firstname2_, lastname2_;
};

class NamePrinter: public PersonVisitor{
public:
   void visit(Man *m) override {
      cout << m->getFirstName() << " "
           << m->getLastName() << endl;
   }
   void visit(Woman *w) override {
      cout << w->getFirstName() << " ";
      if (w->getSpouse() != nullptr && w->getFather() != nullptr){
         cout << "Last name: " << static_cast<Man *>(w->getSpouse())->getLastName();
         cout << " Maiden name: "<< static_cast<Man *>(w->getFather())->getLastName();
      }else if (w->getSpouse() != nullptr && w->getFather() == nullptr){
         cout << "Last name: " << static_cast<Man *>(w->getSpouse())->getLastName();
      }else if (w->getFather() != nullptr)
         cout << static_cast<Man *>
                 (w->getFather())->getLastName();
      else
         cout << "Doe";
      cout << endl;
   }
};

class ChildrenPrinter: public PersonVisitor{
public:
   void visit(Man *m) override {
      cout << m->getFirstName() << ": ";
      Woman *spouse = static_cast<Woman *>
                             (m->getSpouse());
      if(spouse != nullptr)
         printNames(spouse->getChildren());
      cout << endl;
   }
   void visit(Woman *w) override {
      cout << w->getFirstName() << ": ";
      printNames(w->getChildren());
      cout << endl;
   }
private:
   void printNames(const vector<Person *> &children){
      for(const auto c: children)
         cout << c->getFirstName() << ", ";
   }
};

// demonstrating the operation
int main(){

   // setting up the genealogical tree
   // the tree is as follows
   //
   //
   //       James Smith  <--spouse-->   Mary
   //                                     |
   //                                    children -------------------------
   //                                     |              |                |
   //                                     |              |                |
   //      William Johnson <--spouse-> Patricia      Robert Smith       Linda
   //                                     |
   //                                    children------------
   //                                     |                 |
   //                                     |                 |
   //      Jennifer  <--spouse-->  Michael Johnson      Barbara
   //          |
   //        children
   //          |
   //          |
   //        Susan


   // first generation
   Man *js = new Man("Smith", "James",
                     nullptr, nullptr, nullptr);
   Woman *ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
   ms->setSpouse(js); js->setSpouse(ms);

   // second generation
   Woman *ps = new Woman({}, "Patricia",
                         nullptr, js, ms);
   Man *wj = new Man("Johnson", "William",
                     nullptr, nullptr, nullptr);
   ps->setSpouse(wj); wj->setSpouse(ps);

   vector<Person *> marysKids  = {ps,
                                  new Man("Smith", "Robert", nullptr, js, ms),
                                  new Woman({}, "Linda", nullptr, js, ms)};
   ms->setChildren(marysKids);

   // third generation
   Man *mj = new Man("Johnson", "Michael", nullptr, wj, ps);
   vector<Person *> patsKids   = {mj,
                                  new Woman({}, "Barbara", nullptr, wj, ps)};
   ps->setChildren(patsKids);

   Woman *jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
   vector<Person *> jensKids = {new Woman({}, "Susan", nullptr, mj ,jj)};

   jj->setSpouse(mj); mj->setSpouse(jj);
   jj->setChildren(jensKids);


   // defining two visitors
   ChildrenPrinter *cp = new ChildrenPrinter;
   NamePrinter *np = new NamePrinter;

   cout << "\nNAME LIST\n";
   ms->accept(np);

   cout << endl << endl;

   // executing the traversal with the composite
   // and the specific visitor
   cout << "CHILDREN LIST\n";
   ms->accept(cp);

        string candidate_1_first, candidate_2_first;
        cout<<"Enter first candidate: "<<endl; getline(std::cin, candidate_1_first);
        cout<<"Enter second candidate: "<<endl; getline(std::cin, candidate_2_first);
        string candidate_1_last, candidate_2_last;
        std::size_t pos_1 = candidate_1_first.find(" ");
        if(pos_1!=std::string::npos){
                candidate_1_last = candidate_1_first.substr(pos_1 + 1, candidate_1_first.size() - 1);
                candidate_1_first = candidate_1_first.substr(0, pos_1);
        }
        std::size_t pos_2 = candidate_2_first.find(" ");
        if(pos_2!=std::string::npos){
                candidate_2_last = candidate_2_first.substr(pos_2 + 1, candidate_2_first.size() - 1);
                candidate_2_first = candidate_2_first.substr(0, pos_2);
        }

        MatchMaker *mm = new MatchMaker(ms, candidate_1_first, candidate_1_last, candidate_2_first, candidate_2_last);
        ms->accept(mm);
}
