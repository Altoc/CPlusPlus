/*
*	Ian Whitesel
*	Project 3 pt. 2
*	Summer 2018
*/

#include <iostream>
#include <vector>
#include "utilities.hpp"



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////FREE FUNCTIONS

//Free Function to convert infix expr to POSTfix expr
String convertExprPost(const String& infix){
	std::vector<String> expr = infix.split(' ');	//initialize a vector of Strings to the passed String, split at spaces
	Stack<String> converter;			//create a Stack of Strings that holds Strings from expr while they are evaluated to postfix

	int i = 0;						
	while(i < expr.size() - 1){				//while expr at index i does not equal ';',
		if(expr[i] == ")"){				//check if expr at index i is ')',
			String right = converter.pop();		//initialize a string that holds the right operand to the popped element from stack,
			String op = converter.pop();		//initialize a string that holds the operator to the popped element from stack,
			String left = converter.pop();		//initialize a string that holds the right operand to the popped element from stack,

			String combination = (left + " " + right + " " + op);	//initialize a string that holds the converted expr to postfix, operator last,

			converter.push(combination);		//push combination to the top of the converter stack

		}else{						//if expr at index i is NOT ')',	
			if(expr[i] != "(")			//check if expr at index i is NOT '(', as we want to ignore open brackets,
				converter.push(expr[i]);	//and if it is NOT, then push the variable or operator to the stack
		}
		i++;
	}
	return converter.pop();					//return the final item from stack while popping it, as pop returns a value
}

//Free Function to convert infix expr to PREfix expr
String convertExprPre(const String& infix){
	std::vector<String> expr = infix.split(' ');	//initialize a vector of Strings to the passed String, split at spaces
	Stack<String> converter;			//create a Stack of Strings that holds Strings from expr while they are evaluated to prefix

	int i = 0;						
	while(i < expr.size() - 1){				//while expr at index i does not equal ';',
		if(expr[i] == ")"){				//check if expr at index i is ')',
			String right = converter.pop();		//initialize a string that holds the right operand to the popped element from stack,
			String op = converter.pop();		//initialize a string that holds the operator to the popped element from stack,
			String left = converter.pop();		//initialize a string that holds the right operand to the popped element from stack,

			String combination = (op + " " + left + " " + right);	//initialize a string that holds the converted expr to prefix, operator first,

			converter.push(combination);		//push combination to the top of the converter stack

		}else{						//if expr at index i is NOT ')',	
			if(expr[i] != "(")			//check if expr at index i is NOT '(', as we want to ignore open brackets,
				converter.push(expr[i]);	//and if it is NOT, then push the variable or operator to the stack
		}
		i++;
	}
	return converter.pop();					//return the final item from stack while popping it, as pop returns a value
}

//Free function that evaluates expr from convert to assembly functions, returns TMPn
String evaluate(const String& lOperand, const String& op, const String& rOperand, int N, const int& args, std::ostream& file){
	String result("TMP");
	String evalOp;
	char num = N + '0';

	if(op == "+")
		evalOp = "AD";
	else if(op == "-")
		evalOp = "SB";
	else if(op == "/")
		evalOp = "DV";
	else if(op == "*")
		evalOp = "ML";
	
	result += num;

	if(args == 2){
		std::cout<<"LD\t"<<lOperand<<std::endl;
		std::cout<<evalOp<<"\t"<<rOperand<<std::endl;
		std::cout<<"ST\t"<<result<<std::endl;
	}else if(args == 3){
		file<<"LD\t"<<lOperand<<"\n";
		file<<evalOp<<"\t"<<rOperand<<"\n";
		file<<"ST\t"<<result<<"\n";
	}
			
	return result;
}

//Free function to convert POSTfix expr to assembly
String convertPostToAssembly(const String& postfix, const int& args, std::ostream& file){
	std::vector<String> postfixExpr = postfix.split(' ');		//create a vector of Strings to hold postfix operation
	Stack<String> assembler;					//create a stack to hold assembler evaluations
	int tmpN = 0;							//create a counter to track TMPn
	
	int i = 0;
	while(i < postfixExpr.size()){					//iterate through postfixExpr while i is less than the size of postfix Expr
		if((postfixExpr[i] == '+') || (postfixExpr[i] == '-') || (postfixExpr[i] == '/') || (postfixExpr[i] == '*')){	//if the String in postfixExpr IS a operator
			assembler.push(postfixExpr[i]);			//add the operator to the stack

			String op = assembler.pop();			//pop the operator and save it to String 'operator'
			String right = assembler.pop();			//pop the right operand and save it to String 'right'
			String left = assembler.pop();			//pop the left operand and save it to String 'left'

			++tmpN;

			assembler.push(evaluate(left, op, right, tmpN, args, file));//push to the stack the evaluated left, operator, right
		}else{							//if postfixExpr is NOT an operator,
			assembler.push(postfixExpr[i]);			//push it to the assembler stack
		}
		
		i++;		
	}

	return 0;
}

//Free function to convert PREfix expr to assembly
String convertPreToAssembly(const String& prefix, const int& args, std::ostream& file){
	std::vector<String> prefixExpr = prefix.split(' ');		//create a vector of Strings to hold postfix operation
	Stack<String> assembler;					//create a stack to hold assembler evaluations
	int tmpN = 0;							//create a counter to track TMPn
	int operatorCount = 0;
	
	for(int j = 0; j < prefixExpr.size(); j++){			//fill stack with prefix elements
		if((prefixExpr[j] == '+') || (prefixExpr[j] == '-') || (prefixExpr[j] == '/') || (prefixExpr[j] == '*'))	//if the String in prefixExpr IS a operator
			operatorCount++;				//increment operator count

		assembler.push(prefixExpr[j]);				//push the element to the assembler stack
	}

	int i = 0;
	while(i < operatorCount){					//iterate through prefixExpr while i is less than the amount of operators in the expression
		String right = assembler.pop();
		String left = assembler.pop();
		String op = assembler.pop();

		++tmpN;

		assembler.push(evaluate(left, op, right, tmpN, args, file));
				
		i++;
	}
	
	return 0;
}

//when an operator is enountered, check if the next two vars are operands followed by an operator
//if so, evaluate,
//else if next two vars are not operands or end of stack,
//evaluate current operator with preceding two operands
/*
*String convertPreToAssembly(const String& prefix){		//Free function to convert PREfix expr to assembly
*	std::vector<String> prefixExpr = prefix.split(' ');
*	Stack<String> assembler;
*	int tmpN = 0;
*	int operatorCount;
*	
*	for(int j = 0; j < prefixExpr.size(); j++){
*		assembler.push(prefixExpr[j]);
*	}
*	
*	int i = 0;
*	while(i < operatorCount){
*		if(assembler.)
*	}
*}
*/