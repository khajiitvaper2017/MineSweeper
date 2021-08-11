#ifndef QLABELMOUSEEVENT_H
#define QLABELMOUSEEVENT_H
#include <QLabel>
class QLabelMouseEvent: public QLabel{

	Q_OBJECT
public:
	QLabelMouseEvent(QWidget* q=0):QLabel(q){

	}
	~QLabelMouseEvent(){
	}

protected:
	void mousePressEvent(QMouseEvent *);


signals :
	void labelClicked();

private:

};

#endif // QLABELMOUSEEVENT_H
