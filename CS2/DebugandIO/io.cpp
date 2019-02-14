#include <iostream>
#include <fstream>

void getWord(char word[], std::ifstream& fileWriteTo);

void getline(char line[], std::ifstream& fileWriteTo);

int main(int argc, char* argv[]){	//this will read any file, not just a specifically named one: ./a.out anyTextFile.txt
	std::ifstream in(argv[1]);	//opens argv[1] which is a file name
	std::ofstream out(argv[2]);	//opens argv[2] which is a file name we want to write to
	char word[200];			//create a word character array with enough space
	char line[200];
	
	if(in.is_open()){			//check if in file is open,
		while(!in.eof()){		//while is has not ended,
			out<<"getWord: "<<std::endl;
			getWord(word, in);	//use getWord to read words,
			out<<word;		//write the words to argv2
			
			
			out<<'\n'<<'\n'<<"getline: "<<std::endl;	
			std::ifstream in(argv[1]);
			getline(line, in);
			getline(line, in);
			getline(line, in);
			out<<line;
		}
	}else{
		std::cerr<<"cant open file!"<<std::endl;
	}
	in.close();				//close file
}

void getWord(char word[], std::ifstream& in){
	char ch = '\0';			//a ch to read ch's from file
	int counter;
	
	if(in.is_open()){		//if in file is opened,
		if(!in.eof()){		//and if it hasnt reached end,
			in.get(ch);		//read a ch from the file,
		}

		int i = 0;
		while(!in.eof()){	//and while the file hasnt ended,
			word[i] = ch;	//assign the ch that was read from file to the ith index of word argument,
			in.get(ch);	//read the next ch,
			i++;		//and iterate
		}
	}else{
		std::cout<<"getWord UNABLE TO OPEN FILE"<<std::endl;
	}
	in.close();
}

void getline(char line[], std::ifstream& in){
	char ch = '\0';
	
	if(in.is_open()){
		if(!in.eof())
			in.get(ch);
		
		int i = 0;
		while((!in.eof()) && (ch != '\n')){
			line[i] = ch;
			in.get(ch);
			i++;
		}
	}else{
		std::cout<<"getline UNABLE TO OPEN FILE"<<std::endl;;
	}
	in.close();
}
