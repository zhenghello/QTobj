#include "cmywork.h"
#include <QDebug>

CMyWork::CMyWork(QObject *parent):
QThread(parent)
{
	/*m_mutex     = new QMutex;*/
	m_isRunning = false;

	qDebug()<<"start thread = "<<currentThreadId();
}

CMyWork::~CMyWork()
{
	qDebug()<<"delete work";
	stopWork();
	quit();
	wait();
	/*delete m_mutex;*/
}

void CMyWork::stopWork()
{
	m_isRunning = false;
}

void CMyWork::startWork()
{
	m_isRunning = true;
	this->start();
}

void CMyWork::run()
{
	/*m_isRunning = true;*/
	while(m_isRunning)
	{
		//do something
		qDebug()<<"run thread = "<<currentThreadId();
		sleep(1);

	}
}
