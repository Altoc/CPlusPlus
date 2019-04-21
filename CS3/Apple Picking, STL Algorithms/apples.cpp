// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 10/03/2018

/*
*	Ian Whitesel
*	CSIII Lab6
*	02-19-2019
*/

#include <iostream>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using namespace std::placeholders;

struct Apples{
	double weight; // oz
	string color;  // red or green
	void print() const { cout << color << ", " <<  weight << endl; }

	Apples& operator=(const double& inputWeight){weight = inputWeight; return *this;};
	Apples& operator=(const string& inputColor){color = inputColor; return *this;};
	bool operator>(const double& inputWeight){return weight > inputWeight;};
	bool operator<(const double& inputWeight){return weight < inputWeight;};
	int operator+(const Apples& rhs){return(weight + rhs.weight);};
};

class jamFunctor{
public:
	double operator()(double& jamWeight, double& appleWeight) const{
		return jamWeight += appleWeight;
	}
};

bool compareWeight(const Apples& lhs, const Apples& rhs){
	return(lhs.weight < rhs.weight);
}

int main(){	
	srand(time(nullptr));

	const double minWeight = 8.;
	const double maxWeight = 3.;

	cout << "Input crate size: ";
	int size;
	cin >> size;

	vector <Apples> crate(size);
///////////////////////////////////////////////////////////////// w/ generate()

	std::generate(crate.begin(), crate.end(), 
	[minWeight, maxWeight]{
		Apples result;
		result.weight = (minWeight + static_cast<double>(rand()) / RAND_MAX*(maxWeight - minWeight));
		result.color = (rand() % 2 == 1 ? "green" : "red");
		return result;
	});

/*
///////////////////////////////////////////////////////////////// w/o generate()

	for(auto it = crate.begin(); it != crate.end(); ++it){
		it->weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
		it->color = rand() % 2 == 1 ? "green" : "red";
	}

*/

	cout << "Enter weight to find: ";
	double toFind;
	cin >> toFind;

///////////////////////////////////////////////////////////////// w/ count_if()

	int cnt = std::count_if(crate.begin(), crate.end(), 
	[toFind](Apples i){return i > toFind;});

/*
///////////////////////////////////////////////////////////////// w/o count_if()

	int cnt = 0;
	for(auto it = crate.cbegin(); it != crate.cend(); ++it) 
		if(it->weight > toFind) ++cnt;

*/

	cout << "There are " << cnt << " apples heavier than " << toFind << " oz" <<  endl;

///////////////////////////////////////////////////////////////// w/ find_if()

	cout << "at positions ";
	for(int i = 0; i < size; ++i){
		vector<Apples>::iterator findIfItr = std::find_if(crate.begin(), crate.end(), [toFind](Apples i){return i > toFind;});
		if((*findIfItr).weight > toFind)
			cout << i << ' ';
	}
	cout << endl;

/*
///////////////////////////////////////////////////////////////// w/o find_if()

	// find_if()
	cout << "at positions ";
	for(int i=0; i < size; ++i)
		if(crate[i].weight > toFind)
			cout << i << ", ";
	cout << endl;

*/

///////////////////////////////////////////////////////////////// w/ max_element()

	vector<Apples>::iterator maxEleItr = std::max_element(crate.begin(), crate.end(), compareWeight);
	double heaviest = (*maxEleItr).weight;
	cout << "Heaviest apple weighs: " << heaviest << " oz" << endl;

/*
///////////////////////////////////////////////////////////////// w/o max_element()

	// max_element()
	double heaviest = crate[0].weight;
	for(int i=1; i < size; ++i)
		if(crate[i].weight > heaviest) heaviest = crate[i].weight; 
	cout << "Heaviest apple weighs: " << heaviest << " oz" << endl;

*/

///////////////////////////////////////////////////////////////// w/ for_each() or accumulate()

	vector<double> weightVector;
	for(int i = 0; i < size; i++){
		weightVector.push_back(crate[i].weight);;
	}
	double weightAccumulator = std::accumulate(weightVector.begin(), weightVector.end(), 0.0);
	cout << "Total apple weight is: " << weightAccumulator << " oz" << endl;

/*
///////////////////////////////////////////////////////////////// w/o for_each() or accumulate()

	// for_each() or accumulate()
	double sum = 0;
	for(int i=0; i < size; ++i)
		sum += crate[i].weight;
	cout << "Total apple weight is: " << sum << " oz" << endl;
*/

///////////////////////////////////////////////////////////////// w/ transform()

	cout << "How much should they grow: ";
	double toGrow;
	cin >> toGrow;
	std::transform(crate.begin(), crate.end(), crate.begin(), [toGrow](Apples i){return (i.weight + toGrow);});

/*
///////////////////////////////////////////////////////////////// w/o transform()

	cout << "How much should they grow: ";
	double toGrow;
	cin >> toGrow;
	for(int i=0; i < crate.size(); ++i)
		crate[i].weight += toGrow;

*/

///////////////////////////////////////////////////////////////// w/ remove_if()

	cout << "Input minimum acceptable weight: ";
	double minAccept;
	cin >> minAccept;
	crate.erase(remove_if(crate.begin(), crate.end(), [minAccept](Apples i){return(i.weight < minAccept);}), crate.end());
	cout << "removed " << size - crate.size() << " elements" << endl;

/*
///////////////////////////////////////////////////////////////// w/o remove_if()

	cout << "Input minimum acceptable weight: ";
	double minAccept;
	cin >> minAccept;
   
	for(auto it=crate.begin(); it != crate.end(); )
		if(it->weight < minAccept)
			it = crate.erase(it);
		else
			++it;
	 
	cout << "removed " << size - crate.size() << " elements" << endl;

*/

///////////////////////////////////////////////////////////////// w/ sort()

	std::sort(crate.begin(), crate.end(), [](Apples i, Apples j){return(i.weight < j.weight);});

/*
///////////////////////////////////////////////////////////////// w/o sort()

	bool swapped;
	do{
		swapped = false;
		for(int i=0; i < crate.size()-1; ++i)
			if(crate[i].weight > crate[i+1].weight){
				std::swap(crate[i], crate[i+1]);
				swapped = true;
			}
	}while(swapped);

*/

///////////////////////////////////////////////////////////////// w/ remove_copy_if() & front_inserter()

	deque<Apples> peck;
	std::remove_copy_if(crate.begin(), crate.end(), front_inserter(peck), [](Apples i){return i.color == "green";});
	crate.erase(remove_if(crate.begin(), crate.end(), [](Apples i){return(i.color == "red");}), crate.end());

/*
///////////////////////////////////////////////////////////////// w/o remove_copy_if() & front_inserter()

// moving all red apples from crate to peck
// remove_copy_if() with back_inserter()/front_inserter() or equivalents
	deque<Apples> peck;
	for(auto it=crate.begin(); it != crate.end();)
		if(it->color == "red"){
			peck.push_front(std::move(*it));
			it=crate.erase(it);
		}else
			++it;

*/

///////////////////////////////////////////////////////////////// w/ for_each()

	cout << "apples in the crate" << endl;
	for_each(crate.begin(), crate.end(), [](Apples i){cout << i.color << " " << i.weight << endl;});
	cout << endl;

/*
///////////////////////////////////////////////////////////////// w/o for_each()

// for_each() possibly
	cout << "apples in the crate" << endl;
	for(const auto &e: crate) {
		e.print(); 
	}

	cout << endl;

*/

///////////////////////////////////////////////////////////////// w/ for_each()

	cout << "apples in the peck" << endl;	
	for_each(peck.begin(), peck.end(), [](Apples i){cout << i.color << " " << i.weight << endl;});

/*
///////////////////////////////////////////////////////////////// w/o for_each()

// for_each() possibly
	cout << "apples in the peck" << endl;
	for(const auto &e: peck) {
		e.print();
	}

*/

	// prints every "space" apple in the peck 
	const int space=3; 
	cout << "\nevery " << space << "\'d apple in the peck"<< endl;

///////////////////////////////////////////////////////////////// w/ advance()/next()/distance()

	deque<Apples>::iterator printItr = peck.begin();
	cout << (printItr)->color << ' ' << (printItr)->weight << endl;		
	do{
		std::advance(printItr, space);
		cout << (printItr)->color << ' ' << (printItr)->weight << endl;		
	}while(std::distance(printItr, peck.end()) > space);

/*
///////////////////////////////////////////////////////////////// w/o advance()/next()/distance()

// replace with advance()/next()/distance()
// no pointer arithmetic
	auto it=peck.cbegin(); int i = 0;   
	while(it != peck.cend()){
		if(i == space){
			it->print();
			i=0;
		}
		++i; 
		++it;
	}

*/

///////////////////////////////////////////////////////////////// w/ using a binder to create a functor w/ configurable max weight

	const double weightToJam = 10.0;
	double jamWeight = 0;

	int applesToJamCnt = std::count_if(crate.begin(), crate.end(), [weightToJam](Apples i){return(i.weight < weightToJam);});
	cout << "There are " << applesToJamCnt << " apples to be jammed." << endl;

	crate.erase(remove_if(crate.begin(), crate.end(), [weightToJam](Apples i){return(i.weight > weightToJam);}), crate.end());

	std::cerr<<crate.size()<<std::endl;

	for_each(crate.begin(), crate.end(), [&](Apples i){
		auto f1 = std::bind(jamFunctor(), jamWeight, _1);
		f1(i.weight);
		std::cerr<<"jamWeight: "<<jamWeight<<" apple weight: "<<i.weight<<std::endl;
	});

	cout << "Weight of jam is: " << jamWeight << endl;

/*
///////////////////////////////////////////////////////////////// w/o using a binder to create a functor w/ configurable max weight

	// putting all small green apples in a jam
// use a binder to create a functor with configurable max weight
// count_if() then remove_if()
	
	const double weightToJam = 10.0;
	double jamWeight = 0; 
	for(auto it=crate.begin(); it != crate.end();)		//for every apple in crate,
		if(it->weight < weightToJam){			//if apple.weight < weightToJam
			jamWeight += it->weight;			//Increase jamWeight by apple.weight
			it=crate.erase(it);				//and then remove the apple from crate
		}else						//else 
			++it;						//go to the next apple

	cout << "Weight of jam is: " << jamWeight << endl;

*/

}