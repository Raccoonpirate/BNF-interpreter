#include "curs.h"
#include "GlobalVars.h"
#include "Shuntingyard.h"

Curs::Curs(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags) {
	ui.setupUi(this);
	connect(ui.Compile, SIGNAL(clicked()), this, SLOT(button_clicked()));
}

Curs::~Curs() {

}

QString Curs::CheckZveno(QString str) {
     QString Argument;
     QString withoutSpace = str;
     int i = 0, SRO = 0,	//Количество открытых круглых скобок
	    j = 0, SCO = 0;	//Количество открытых квадратных скобок
	withoutSpace += '\0';
	str.clear();
	while((withoutSpace.at(j) != ';') && (withoutSpace.at(j) != '\0')) {
		if ((withoutSpace.at(j) == ' ')) {
			;
		}
		else { 
			str += withoutSpace.at(j);
		}
		j++;
	}
	str += withoutSpace.at(j);
	
	QVector <char> Opening;
     while((str.at(i) != ';') && (str.at(i) != '\0')) {
		if (str.at(i) == '(') {
			Argument += str.at(i);
			Opening.append('r');
			SRO++;
		}
		else if (str.at(i) == '[') {
			Argument += str.at(i);		
			Opening.append('s');
			SCO++;
		}
		else if (str.at(i) == ')' && (SRO==0)) {
			Error = true;
			Schet = i;		
			return "Круглая скобка нигде не открывалась";
		}
		else if (str.at(i) == ')') {
			if (Opening.at(Opening.count()-1)=='s') {
				Error = true;
				Schet = i;
				return "Неправильная последовательность скобок или круглая скобка нигде не открывалась";
			}
			Opening.erase(Opening.end() - 1);
			Argument += str.at(i);
			SRO--;
		}
		else if (str.at(i) == ']' && (SCO == 0)) {
			Error = true;
			Schet = i;
			return "Квадратная скобка нигде не открывалась";
		}
		else if (str.at(i) == ']') {
			if (Opening.at(Opening.count()-1) == 'r') {
				Error = true;
				Schet = i;
				return "Неправильная последовательность скобок или квадратная скобка нигде не открывалась";
			}
			Opening.erase(Opening.end() - 1);
			Argument += str.at(i);
			SCO--;
		}
		else if (((str.at(i) >= '0') && (str.at(i) <= '7'))) {
			Argument += str.at(i);	     	     
		}
		else if ((str.at(i) != '+') && (str.at(i) != '-') &&
			    (str.at(i) != '*') && (str.at(i) != '/') &&
			    (str.at(i) != '&') && (str.at(i) != '|') &&
			    (str.at(i) != ' ')) {
			bool find = false;
			if (((str.at(i) >= 'а') && (str.at(i) <= 'я')) || ((str.at(i) >= 'А') && (str.at(i) <= 'Я'))) {
				QString str1 = 0;
				str1.replace(0, 4, str.mid(i,4));
				if ((str1.isNull()) || (Ident.size() == 0)) {
					Error = true;
					Schet = i;
					return "Неопределенный идентификатор";
				}
				else {
					for (int j = 0; j < Ident.size(); j++)
						if (!str1.compare(Ident[j].Perem)) {
							find = true;
							str1 = Ident.at(j).Value;
							str1.replace('\0',' ');
							str1.remove(' ');
							break;
						}
					if (find) {
						str.replace(i, 4, str1);
						for (int j = 0; j < str1.count(); j++)
							Argument += str.at(i++);
						i--;
					}
					else {
						Error = true;
						Schet = i;
						return "Неопределенный идентификатор";
					}
				}
			}
			else {
				Error = true;
				Schet = i;
				return "Допустимы цифры только от 0 до 7, знаки '+' '-' '*' '/' '&' '|' и переменные";
			}
		}
		else if ((str.at(i) == ' ')) {
			;
		}
		else {
			Argument+=str.at(i);
		}
		
		i++;
     }
     
     if (SRO != 0) {
		Error = true;
		Schet = 0;
		return "Не закрыта круглая скобка";
	}
     if (SCO != 0) {
		Error = true;
		Schet = 0;
		return "Не закрыта квадратная скобка";
	}
     
     ForDel = 0;
     str = Argument;
     str = ' ' + str + '\0';	
     Argument += '\0';
	i = 0;
	
	while(str.at(i) != '\0') {
		if ((str.at(i) == '(') || (str.at(i) == '[')) {
			if ((str.at(i + 1) == ')') || (str.at(i + 1) == ']')){
				Error = true;
				Schet = i;
				return "Скобки не могут быть пустыми";
			}
			if (((str.at(i - 1) >= '0') && (str.at(i - 1) <= '9')) || (str.at(i - 1) == ')')) {
				Error = true;
				Schet = i;
				return "Перед открывающей скобкой может стоять либо знак операции либо ничего";
			}
		}
		if ((str.at(i) == ')') || (str.at(i) == ']')) {
			if (((str.at(i + 1) >= '0') && (str.at(i + 1) <= '9')) || (str.at(i + 1) == '(')) {
				Error = true;
				Schet = i;
				return "После закрывающей скобки может стоять либо знак операции либо ничего";
			}
		}
		if ((str.at(i) == '+') || (str.at(i) == '-') ||
		    (str.at(i) == '*') || (str.at(i) == '/') ||
		    (str.at(i) == '&') || (str.at(i) == '|')) {
			if ((str.at(i + 1) == '+') || (str.at(i + 1) == '*') || (str.at(i + 1) == '/') || (str.at(i + 1) == '&') || (str.at(i + 1) == '|')) {
				Error = true;
				Schet = i;
				return "Два знака подрят идти не могут, вторым знаком может быть минус только если второй операнд отрицательный";
			}
			if ((str.at(i) != '-') && !((str.at(i - 1) >= '0') && (str.at(i - 1) <= '9') || (str.at(i - 1) == ')') || (str.at(i - 1) == ']'))) {
				Error = true;
				Schet = i - 1;
				return "Знак должен иметь левый операнд";
			}
			if (!((str.at(i + 1) >= '0') && (str.at(i + 1) <= '9') || (str.at(i + 1) == '-') || (str.at(i + 1) == '(') || (str.at(i + 1) == '['))  ){
				Error = true;
				Schet = i - 1;
				return "Знак должен иметь правый операнд";
			}
		}	
		if (str.at(i) == '/'){
			if (str.at(i + 1) == '0') {
				Error = true;
				Schet = i;
				return "Деление на 0 невозможно!";	
			}
		}
		i++;
     }
     
	
     
     return Defragmentation(Argument);
}

void Curs::LightUpError(QTextCursor* cursor, int place, int until){
	cursor->setPosition(place, QTextCursor::MoveAnchor);
	cursor->movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, until);
	QString s = cursor->selectedText();
	cursor->insertHtml("<FONT color=black  style=\"BACKGROUND-COLOR: yellow\">" + s + "</FONT>");
	ui.ResultWindow->clear();
}

void Curs::button_clicked() {

     text = ui.EnterWindow->toPlainText();
     QString ResultString = text;
     QString AnswerString = 0;
     QString ErrorString = 0;
     ResultString = ResultString.simplified();
     QStringList leksems = ResultString.split(" ", QString::SkipEmptyParts);
     Error = false;
	QTextCursor cursor(ui.EnterWindow->document());
	
	int mas = 0;

     if (leksems.isEmpty()) {
		ui.ResultWindow->clear();
		ui.ResultWindow->setText("Ничего не введено. Код начинается со слова ""Программа"" ");
		return;
     }
     
     if ( leksems[0].compare("Программа",Qt::CaseInsensitive) ) {
		LightUpError (&cursor, 0, text.indexOf(' ',0));
		ui.ResultWindow->clear();
     	ui.ResultWindow->setText("Слово ""Программа"" введено с ошибками или не поставлен пробел после него");
		return;
     }
     
     ResultString = ResultString.right(ResultString.length() - ResultString.indexOf(' '));
     //Цикл до безконечности, в конце делаем проверку на слово "конец" и брейк. Перед концом обрезаем строку по символу ";" начиная с "ввода"
     Ident.clear();
     
     mas += 10;
     while(ResultString.compare("Конец",Qt::CaseInsensitive)) {
		cursor.movePosition(QTextCursor::Start);
		cursor.movePosition(QTextCursor::End,QTextCursor::KeepAnchor,text.count());
		QString s = cursor.selectedText();
		cursor.insertHtml("<FONT color=black  style=\"BACKGROUND-COLOR: white\">" + s + "</FONT>");
		
		leksems.clear();
		leksems = ResultString.split(" ", QString::SkipEmptyParts);
		if ( leksems.count() <= 1 ) {
			ui.ResultWindow->clear();
			ui.ResultWindow->setText("Звено должно начинатся со слова ""Ввод"" ");
			return;
		}
		else if (leksems[0].compare("Ввод",Qt::CaseInsensitive)) {
			LightUpError(&cursor, mas, 1);
			ui.ResultWindow->clear();
			ui.ResultWindow->setText("Звено должно начинатся со слова ""Ввод"" или же оно введено с ошибками или не поставлен пробел");
			return;
		}
	     mas += 5;
		//Проверка метки и пробела после неё
		int place = ResultString.indexOf('д') + 2;
		if (!((ResultString.at(place) >= '0') && (ResultString.at(place) <= '7'))) {
			LightUpError(&cursor, mas, 1);
			ui.ResultWindow->setText("Метка должна быть цифрой от 0 до 7");
			return;
		}
	     mas += 2;
	     if (ResultString.contains(':')) {
			if (ResultString.indexOf(':',0) > 9) {
				LightUpError(&cursor, mas, 1);
				ui.ResultWindow->setText("После метки должен через пробел стоять символ ':' ");
				return;
			}
		}
		else {
			LightUpError(&cursor, mas, 1);
			ui.ResultWindow->setText("Отсутствует знак ':' после метки ");
			return;
		}
		
		if ((ResultString.at(ResultString.indexOf(':') + 1) != ' ') ||
		    (ResultString.at(ResultString.indexOf(':') - 1) != ' ')) {
			LightUpError(&cursor, text.indexOf(':', mas - 2), 1);
			ui.ResultWindow->setText("После и перед знаком ':' должен стоять пробел");
			return;
		}
		//Проверка переменной
		mas += 2;
		int i = ResultString.indexOf(':') + 2, j = 0;
		while(ResultString.at(i)!=' ') {
			if (!(((ResultString.at(i) >= 'а') && (ResultString.at(i) <= 'я')) ||
			      ((ResultString.at(i) >= 'А') && (ResultString.at(i) <= 'Я'))) &&
			      (j == 0)) {
			      
				LightUpError (&cursor, mas, 1);
				ui.ResultWindow->setText("Переменная должна начинаться с буквы русского алфавита");
				return;
			}

			if (!((ResultString.at(i) >= '0') && (ResultString.at(i) <= '7'))&& (j >= 1) || (j == 4)) {
				LightUpError (&cursor, mas + 1, 3);
				ui.ResultWindow->setText("Переменная состоит из одной буквы и 3 цифр от 0 до 7. Или не поставлен пробел после переменной");
				return;
			}
			j++;
			i++;
		}
		mas += 4;
		if (ResultString.contains('=')) {
			if (ResultString.indexOf('=', 0) > 15) {
				LightUpError (&cursor, mas + 1, 1);
				ui.ResultWindow->setText("После переменной должен через пробел стоять символ '=' ");
				return;
			}
		}
		else {
			LightUpError (&cursor, mas, 1);
			ui.ResultWindow->setText("Отсутствует знак '=' после переменной");
			return;
		}

		if ((ResultString.at(ResultString.indexOf('=') + 1) != ' ') || (ResultString.at(ResultString.indexOf('=') - 1) != ' ')) {
			LightUpError (&cursor, text.indexOf('=', mas), 1);
			ui.ResultWindow->setText("После и перед знаком '=' должен стоять пробел");
			return;
		}
		//Начало середины конца
	     
		if (ResultString.contains(';')) {
			if ((ResultString.indexOf("ввод", mas) != -1) && ResultString.at(ResultString.indexOf("ввод", mas) - 2) != ';') {
				LightUpError (&cursor, text.indexOf("ввод", mas), 2);
				ui.ResultWindow->setText("Звено должно заканчиваться символом ';' ");
				return;
			}
			else	if ((ResultString.indexOf("конец",mas) != -1) && (ResultString.at(ResultString.indexOf("конец", mas) - 2) == ';')) {
				LightUpError (&cursor, text.indexOf("ввод", mas) - 3, 3);
				ui.ResultWindow->setText("Последнее звено не должно заканчиваться символом ';' ");
				return;
			}
		}
		else {
			if (ResultString.indexOf("ввод", 4) == -1) {
				;
			}
			else {
				LightUpError (&cursor, mas, 1);
				ui.ResultWindow->setText("Звено должно начинаться словом ""ввод"" и заканчиваться символом ';' ");
				return;
			}
		}
		
		AnswerString = AnswerString + leksems[3] + '=';
		Schet = 0;
		mas += 3;
		QString ForOcasion;
		//Последнее звено или нет, последнее НЕ оканчивается ";"
		if (ResultString.contains(';')) {
			ForOcasion = CheckZveno(ResultString.mid(ResultString.indexOf('=',0) + 2, ResultString.indexOf(';',0) - ResultString.indexOf('=', 0) ));
		}
		else {
			ForOcasion = CheckZveno(ResultString.mid(ResultString.indexOf('=',0) + 2, ResultString.indexOf("конец",0) - ResultString.indexOf('=',0) - 2 ));
		}
		
		if (Error) {
			int i = mas+Schet;
			LightUpError (&cursor, mas + Schet, 1);
			AnswerString = ForOcasion;
			break;
		}
		else {
			Identifier InMas;
			
			InMas.Perem = leksems[3];
			InMas.Value = ForOcasion;
			Ident.push_back(InMas);
		
			ForOcasion.replace('\0',' ');
			ForOcasion.remove(' ');
			if (ForOcasion.at(0) == '-') {
				ForOcasion.remove(0,1);
				ForOcasion = QString::number(ForOcasion.toShort(), 8);
				AnswerString += '-';
			}
			else {
				ForOcasion = QString::number(ForOcasion.toShort(), 8);
			}
			AnswerString += ForOcasion;
		}
		
		mas = mas + ForDel + 8;

		AnswerString += '\n';
		
		if (ResultString.contains(';')){
			ResultString = ResultString.right((ResultString.length() - ResultString.indexOf(';', 0)) - 1);
		}
		else {
			ResultString = ResultString.right((ResultString.length() - ResultString.indexOf("конец", 0)));
		}
		ResultString = ResultString.simplified();
		
		if (leksems[leksems.length()-1].compare("Конец",Qt::CaseInsensitive)) {
			LightUpError(&cursor, text.count() - 5, 5);
			ui.ResultWindow->setText("Программа должна заканчиваться словом ""Конец"", либо в нем допущена ошибка или перед ним не стоит пробел");
			return;
		}
     }

     ui.ResultWindow->setText(AnswerString);
}