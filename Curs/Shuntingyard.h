#include "GlobalVars.h"

QVector <QString>	OutPut;
QVector <QChar>	Stack;
QVector <double>	Result;

double Calc(int oper1, QChar sign, int oper2){
	switch(sign.toAscii()) {
		case '+': return oper1+oper2;
		break;
		case '-': return oper1-oper2;
		break;
		case '*': return oper1*oper2;
		break;
		case '/': return oper1/oper2;
		break;
		case '&': return oper1&oper2;		
		break;
		case '|': return oper1|oper2;		
		break;
	}
	return 0;
}

int Calculate(){
	Result.clear();
	for (; !OutPut.isEmpty() ;){
		if (OutPut.first().at(0) < '0' || OutPut.first().at(0) > '9'){
			if (OutPut.first().at(0) == '-' || OutPut.first().at(0) == '+' || OutPut.first().at(0) == '*' || OutPut.first().at(0) == '/' || OutPut.first().at(0) == '&' || OutPut.first().at(0) == '|'){
				if (OutPut.first().at(0) == '-'){
					if (OutPut.first().length() >= 2){
						Result.push_back(OutPut.first().toInt());
						OutPut.pop_front();
						continue;
					}
				}
				Result.push_back(Calc(Result.at(Result.count() - 2), OutPut.first().at(0), Result.at(Result.count()-1)));
				Result.remove(Result.count() - 2);
				Result.remove(Result.count() - 2);
			}
		}
		else {
			Result.push_back(OutPut.first().toInt());
		}
		
		OutPut.pop_front();
	}

	return Result.first();
}

int GetPriority(QChar sign){
	switch (sign.toAscii()){
		case '+': return  1; break;
		case '-': return  1; break;
		case '*': return  2; break;
		case '/': return  2; break;
		case '&': return  2; break;
		case '|': return  2; break;
		case '(': return -1; break;
		case '[': return -1; break;
	}
	return 0;
}

void Priority(QChar sign){
	if (!Stack.isEmpty()){
		for (;!Stack.isEmpty();){
			if (GetPriority(sign) < GetPriority(Stack.first())){
				OutPut.push_back(Stack.first());
				Stack.pop_front();
			} else {
				break;
			}
		}
	}	
}

void Parentesis(QChar skobka){
	for (; Stack.first() != skobka; ){
		OutPut.push_back(Stack.first());
		Stack.pop_front();
	}
	Stack.pop_front();
}

QString Defragmentation(QString str){
	QString value;
	for (int i = 0; i <= str.length() - 1; i++){
		if (str.at(i) == '(' || str.at(i) == '['){
			Stack.push_front(str.at(i));
		}
		else
		if (str.at(i) == ')' || str.at(i) == ']'){
			if (!value.isEmpty()){
				OutPut.push_back(value);
				value.clear();
			}
			Parentesis(str.at(i).mirroredChar());
		}
		else
		if (str.at(i).isDigit()) {
			value += str.at(i);	     	     
		}
		else		
		if ((str.at(i) == '+') || (str.at(i) == '-') || (str.at(i) == '*') || (str.at(i) == '/') || (str.at(i) == '&') || (str.at(i) == '|')) {
			if (!value.isEmpty()){
				OutPut.push_back(value);
				value.clear();
			}
						
			if (str.at(i) == '-'){
				if ((i == 0) || ( ((str.at(i - 1) == '-') || (str.at(i - 1) == '+') || 
							    (str.at(i - 1) == '*') || (str.at(i - 1) == '/') || 
							    (str.at(i - 1) == '(') || (str.at(i - 1) == '[') ||
							    (str.at(i - 1) == '&') || (str.at(i - 1) == '|')) 
				   )){
					value += str.at(i);
					continue;
				}
			}
			Priority(str.at(i));
			Stack.push_front(str.at(i));
		}
     }
     
     if (!value.isEmpty()){
		OutPut.push_back(value);
     }
     
     for (; !Stack.isEmpty() ;){
		OutPut.push_back(Stack.first());
		Stack.pop_front();
     }
          
     return QString::number(Calculate(), 10);    
}