// figures: object adapter pattern
// Mikhail Nesterenko
// 2/16/2014

//	Ian Whitesel
//	Lab10.1
//	Spring 2019

#include <iostream>

using std::cout; using std::endl;

// base interface
class Figure {
public:
   virtual void draw()=0;
   virtual ~Figure(){}
};

// implementer/adaptee
class LegacyRectangle{
public:
   LegacyRectangle(int topLeftX, int topLeftY, 
		   int bottomRightX, int bottomRightY): 
      topLeftX_(topLeftX), 
      topLeftY_(topLeftY), 
      bottomRightX_(bottomRightX), 
      bottomRightY_(bottomRightY){}

   void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY){
	topLeftX_ = topLeftX; topLeftY_ = topLeftY;
	bottomRightX_ = bottomRightX; bottomRightY_ = bottomRightY;
   }
   int getTopLeftX(){return topLeftX_;}
   int getTopLeftY(){return topLeftY_;}
   int getBottomRightX(){return bottomRightX_;}
   int getBottomRightY(){return bottomRightY_;}

   void oldDraw(){
      for(int i=0; i < bottomRightY_; ++i){
         for(int j=0; j < bottomRightX_; ++j)
            if( i >= topLeftY_ && j>= topLeftX_ )
               cout << '*';
            else
               cout << ' ';
         cout << endl;
      }
   }
private: // defining top/left and bottom/right coordinates 
   int topLeftX_;
   int topLeftY_;
   int bottomRightX_;
   int bottomRightY_;
};

// adapter uses composition to delegate requests to adaptee
class SquareAdapter: public Figure{
public:
   SquareAdapter(int size){
      size_ = size;
      adaptee_= new LegacyRectangle(0,0,size,size);
   }
   void draw() override {
      adaptee_->oldDraw();
   }
   int size(){return size_;}
   void resize(int newSize){
      size_ = newSize;
      adaptee_ = new LegacyRectangle(0,0,size_,size_);
   }
private:
   int size_;
   LegacyRectangle *adaptee_;
};


int main(){
   /*
   Figure *square = new SquareAdapter(10);
   square->draw();
   */
	int sqSize = 0;
	std::cout<<"Input square size: "; std::cin>>sqSize;
	SquareAdapter sa(sqSize);
	sa.draw();
	std::cout<<"Input new square size: "; std::cin>>sqSize;
	sa.resize(sqSize);
	sa.draw();
}
