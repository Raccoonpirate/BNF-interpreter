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
	w.ui.EnterWindow->setText("��������� \n ���� 5 : �111 = [((7&3)+[3+4])*5+5]/2  ; \n ���� 1 : �543 = ((�111+7)*4)/2 \n  �����");
	w.ui.HelpWindow->setText("���� = ""���������"" ������ ""�����""\n������ = ����� "";""... ����� \n����� = ""����"" �����...����� \n����� = ����� "":"" ����� =����.����� \n����.����� = ���� ��1...���� \n��1 = ""+"" ! ""-"" \n���� = ������ ��2...������ \n��2 = ""*"" ! ""/"" \n������ = ����� ��3...����� \n��3 = ""&"" ! ""~"" ! ""~""\n����� = ���!���!""(""����.����� "")"" ! ""[""����.�����""]"" \n��� = ���� ����</����/></����/> \n��� = ����...���� \n���� = ""�""!...""�""!""�""!...""�"" \n���� = ""0""!...""7"" ");
	w.show();
	
	return a.exec();
}
