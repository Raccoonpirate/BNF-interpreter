#include "curs.h"
#include "GlobalVars.h"
#include <QtGui/QApplication>
#include <QTextCodec>

vector <Identifier> Ident;

int main(int argc, char *argv[]) {
	QTextCodec *codec = QTextCodec::codecForName("CP1251");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	
	
	QApplication a(argc, argv);
	Curs w;
	w.ui.EnterWindow->setText("программа \n ввод 5 : у111 = [((7&3)+[3+4])*5+5]/2  ; \n ввод 1 : а543 = ((у111+7)*4)/2 \n  конец");
	w.ui.HelpWindow->setText("Язык = ""Программа"" Звенья ""Конец""\nЗвенья = Звено "";""... Звено \nЗвено = ""Ввод"" Слово...Слово \nСлово = метка "":"" Перем =Прав.часть \nПрав.часть = Блок Зн1...Блок \nЗн1 = ""+"" ! ""-"" \nБлок = Блочек Зн2...Блочек \nЗн2 = ""*"" ! ""/"" \nБлочек = Часть Зн3...Часть \nЗн3 = ""&"" ! ""~"" ! ""~""\nЧасть = Пер!Цел!""(""Прав.часть "")"" ! ""[""Прав.часть""]"" \nПер = Букв Цифр</Цифр/></Цифр/> \nЦел = Цифр...Цифр \nБукв = ""А""!...""Я""!""а""!...""я"" \nЦифр = ""0""!...""7"" ");
	w.show();
	
	return a.exec();
}
