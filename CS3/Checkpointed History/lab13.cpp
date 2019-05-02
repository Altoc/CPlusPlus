//Ian Whitesel
//CSIII Lab13
//Spring 2019

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <list>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;

// originator
class Document {
public:
        Document(vector <string> data={}): data_(data){}

        void insert(int line, const string &str) {
                int index = line-1;
                if (index <= data_.size()+1)
                        data_.insert(data_.begin()+index, str);
                else
                        cout << "line out of range" << endl;
        }

   string remove(int line) {
      int index = line-1;
      string deletedLine="";
      if(index < data_.size()){
         deletedLine = data_[index];
         data_.erase(data_.begin() + index);
      }else
         cout << "line out of range" << endl;
      return deletedLine;
   }

        void show() {
                for(int i = 0; i < data_.size(); ++i)
                        cout << i + 1 << ". " << data_[i] << endl;
        }


private:
        vector<string> data_;
};

// abstract command
class Command{
public:
   Command(Document *doc) : doc_(doc){}
   virtual void execute() = 0;
   virtual void unexecute() = 0;
   virtual ~Command(){}
protected:
   Document *doc_;
};

// two concrete commands
class InsertCommand : public Command {
public:
   InsertCommand(Document *doc, int line,
                 const string &str):
      Command(doc), line_(line),
      str_(str) {}
   void execute() {
      doc_->insert(line_, str_);}
   void unexecute() {doc_->remove(line_);}
private:
   int line_;
   string str_;
};

class EraseCommand : public Command {
public:
   EraseCommand(Document *doc, int line):
      Command(doc), line_(line), str_("") {}
   void execute() {str_ = doc_->remove(line_);}
   void unexecute() {doc_-> insert(line_, str_);}
private:
   int line_;
   string str_;
};

// client
class DocumentWithHistory{
public:
   DocumentWithHistory(const vector<string> &
                       text={}) : doc_(text){}

   void insert(int line, string str) {
      Command *com = new InsertCommand(&doc_, line, str);
      com->execute();
      doneCommands_.push(com);
   }

   void erase(int line){
      Command *com = new EraseCommand(&doc_, line);
      com->execute();
      doneCommands_.push(com);
   }

   void undo() {
      if(doneCommands_.size() != 0) {
         Command *com = doneCommands_.top();
         doneCommands_.pop();
         com->unexecute();
         delete com; // don't forget to delete command
      }else
         cout << "no commands to undo" << endl;
   }

   class Memento *createMemento() const;

   void rollBack(class Memento *);

   std::stack<Command*> getDoneCommands(){return doneCommands_;}

   void show() {doc_.show();}

private:
   std::stack<Command*> doneCommands_;
   Document doc_;
};

class Memento {
public:
        Memento(const DocumentWithHistory& doc): doc_(doc) {}
        const DocumentWithHistory& getState() const {return doc_;}
        void addHistory(std::string text){
                history_.push_back(text);
        }
        std::vector<string> getHistory(){return history_;}
private:
        std::vector<string> history_;
        const DocumentWithHistory doc_;
};

Memento *DocumentWithHistory::createMemento() const{
        return new Memento(*this);  // copying the Document itself
}

void DocumentWithHistory::rollBack(Memento *mem){
        *this = mem->getState();  // copying back
}

// invoker
int main() {
   DocumentWithHistory his({
         "Lorem Ipsum is simply dummy text of the printing and typesetting",
         "industry. Lorem Ipsum has been the industry's standard dummy text",
         "ever since the 1500s, when an unknown printer took a galley of",
         "type and scrambled it to make a type specimen book. It has",
         "survived five centuries."});

   int line, chNum=0; string str; char option;

   Memento *checkpoint = nullptr;

   do{
      his.show();
      cout << endl;
        if(chNum != 0){
                string historyRecord = checkpoint->getHistory()[chNum - 1];
                string delimiter = "";
                string redoCommand = historyRecord.substr(0,historyRecord.find(' '));
                if(redoCommand == "Inserted"){
                        string insertLine = historyRecord.substr(historyRecord.find("[") + 1, historyRecord.find("]") - historyRecord.find("[") - 1);
                        his.insert(line + 1, insertLine);
                        checkpoint->addHistory("Inserted [" + insertLine + "] at line " + std::to_string(line + 1));
                } else if (redoCommand == "Erased"){
                        his.erase(line);
                        checkpoint->addHistory("Erased line " + std::to_string(line));
                } else if (redoCommand == "Undid"){
                        his.undo();
                        checkpoint->addHistory("Undid last action");
                };
                //option = ; //i e u c
                chNum = 0;
        }

        cout << "Enter option (i)nsert line, (e)rase line, (u)ndo last command, (c)heckpoint, roll(b)ack, (h)istory, (r)edo ";
        cin >> option;
        cout << endl;


      switch(option) {
              case 'i':
                 cout << "line number to insert: ";
                 cin >> line;
                 cout << "line to insert: ";
                 cin.get();
                 getline(cin, str);
                 his.insert(line, str);
                if(checkpoint != nullptr){
                 checkpoint->addHistory("Inserted [" + str + "] at line " + std::to_string(line));
                }
                 break;

              case 'e':
                 cout << "line number to remove: ";
                 cin >> line;
                 his.erase(line);
                if(checkpoint != nullptr){
                 checkpoint->addHistory("Erased line " + std::to_string(line));
                }
                 break;

              case 'u':
                 his.undo();
                if(checkpoint != nullptr){
                 checkpoint->addHistory("Undid last action");
                }
                 break;

              case 'c':
                 checkpoint = his.createMemento();
                 checkpoint->addHistory("Created Checkpoint");
                 break;

              case 'b':
                 if (checkpoint != nullptr){
                    his.rollBack(checkpoint);
                    delete checkpoint;
                 }
                 break;

              case 'h':
                if(checkpoint != nullptr){
                        for(int i = 0; i < checkpoint->getHistory().size(); i++){
                                cout << std::to_string(i + 1) << ": " << checkpoint->getHistory()[i] << endl;
                        }
                }
                 break;

              case 'r':
                cout << "Enter command history number" << endl;
                cin >> chNum;
                 break;
      }
        cout << endl;
   }while(option == 'i' || option == 'e' || option == 'u' || option == 'c' || option == 'b' || option == 'h' || option == 'r');
}

