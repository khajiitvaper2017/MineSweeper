#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel	//label with the ability to register a mouse click
{
Q_OBJECT

public:
	explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags()): QLabel(parent)
	{
	};

signals:
	void clicked(QMouseEvent* event);

protected:
	void mousePressEvent(QMouseEvent* event) override
	{
		emit clicked(event);
	}
};

#endif // CLICKABLELABEL_H
