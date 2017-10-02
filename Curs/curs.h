#pragma once

#ifndef CURS_H
#define CURS_H

#include <QtGui/QMainWindow>
#include "ui_curs.h"

class Curs : public QMainWindow {
	Q_OBJECT

	public:
		Curs(QWidget *parent = 0, Qt::WFlags flags = 0);
		~Curs();

		Ui::CursClass ui;
	
	private:
		QString CheckZveno (QString);
		QString summ(QString str);
		int Calc(int, QChar, int);
		void LightUpError (QTextCursor *, int, int);
		
		QString text;
		int ForDel;
		int Schet;
		bool Error;
		int fix;
				
	public slots:
		void button_clicked();
};

#endif
