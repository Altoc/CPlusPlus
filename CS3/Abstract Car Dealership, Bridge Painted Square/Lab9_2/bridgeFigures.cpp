// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// 2/12/2014

//	Ian Whitesel
//	Lab9.2
//	Spring 2019

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill{
public:
   Fill(char borderChar, char fillChar=' '):fillChar_1(borderChar), fillChar_2(fillChar){}
   virtual char getBorder()=0;
   virtual char getInternal()=0;
   virtual ~Fill() {}
protected:
   char fillChar_1;
   char fillChar_2;
};

// concrete body
class Hollow: public Fill{
public:
   Hollow(char fillChar):Fill(fillChar){}
   char getBorder() override {return fillChar_1;}
   char getInternal() override {return ' ';}
   ~Hollow(){}
};

// another concrete body
class Filled: public Fill {
public:
   Filled(char fillChar):Fill(fillChar){}
   char getBorder() override {return fillChar_1;}
   char getInternal() override {return fillChar_1;}
   ~Filled(){}
};

// another concrete body
class EnhancedFilled: public Fill {
public:
   EnhancedFilled(char fillChar, char borderChar):Fill(fillChar, borderChar){}
   char getBorder() override {return fillChar_1;}
   char getInternal() override {return fillChar_2;}
   ~EnhancedFilled(){}
};

// abstract handle
class Figure {
public:
   Figure(int size, Fill* fill): size_(size), 
				 fill_(fill){}
   virtual void draw() =0;
   virtual ~Figure(){}

   void changeFill(const Fill*){;}
protected:
   int size_;
   Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;
};

void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
	 if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	    cout << fill_ -> getBorder();
	 else
	    cout << fill_ -> getInternal();
      cout << endl;
   }
}

int main(){
   // showcase
	std::cout<<"Here is a display of hollow, filled, and enhancefilled shapes:"<<std::endl<<std::endl;

	Figure *holBox = new Square(10, static_cast<Fill *>(new Hollow('*')));
	holBox -> draw();
	cout << endl;

	Figure *filBox = new Square(10, static_cast<Fill *>(new Filled('*')));
	filBox -> draw();
	cout << endl;

	Figure *eFilBox = new Square(10, static_cast<Fill *>(new EnhancedFilled('*', 'O')));
	eFilBox -> draw();
	cout << endl;

   // ask user for figure parameters
   cout << "Make your own figure!" << endl;
   cout << "Filled or hollow? [f/h] "; 
           char ifFilled; cin >> ifFilled;
   cout << "Enter size: "; int size; cin >> size;
   cout << "Enter fill character: "; char fchar; cin >> fchar;
   if(ifFilled == 'f'){
	cout << "Same or different border character? [s/d]: ";
	char sameOrDiff = '*';
	cin >> sameOrDiff;
	if(sameOrDiff == 'd'){
		cout << "Please enter your fill char: "; char filler; cin >> filler;
		Figure *userBox = new Square(size, static_cast<Fill *>(new EnhancedFilled(fchar, filler)));
		userBox -> draw();
		cout << endl;
	} else {
		Figure *userBox = new Square(size, static_cast<Fill *>(new Filled(fchar)));
		userBox -> draw();
		cout << endl;
	}
  } else if(ifFilled == 'h'){
	Figure *userBox = new Square(size, static_cast<Fill *>(new Hollow(fchar)));
	userBox -> draw();
	cout << endl;
  }
}