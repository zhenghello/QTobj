#ifndef CMYWORK_H
#define CMYWORK_H

#include <QThread>
#include <QMutex>

class CMyWork : public QThread
{
	Q_OBJECT
public:
	explicit CMyWork(QObject *parent = 0);
	virtual ~CMyWork();
	void stopWork();
	void startWork();
signals:
	void data_ready(void);
protected:
	virtual void run();
private:
	/*QMutex *m_mutex;*/
	volatile bool m_isRunning;
};

#endif // CMYWORK_H