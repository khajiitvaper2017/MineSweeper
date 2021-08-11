#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include "minesweeper.h"
#include <QTimer>
#include <QTime>
#include <QMessageBox>
QT_BEGIN_NAMESPACE

namespace Ui
{
	class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow() override;

private slots:
	void slotTimerAlarm() const;
	void on_button_game_clicked();
	void on_game_map_clicked(QMouseEvent* event);

	void on_difficulty_custom_toggled(bool checked) const;

private:
	QTimer* qtimer= nullptr;
	QTime init_time;
	char game_state = 'P'; //P - Playing, W - Won, L - Losed
	void create_ms_image();
	void create_game_image();
	int x = 9, y = 9, mines = 10;
	const int cell_size = 30;
	QPixmap* ms_image = nullptr;
	QPixmap* game_image = nullptr;
	MineSweeper* ms = nullptr;
	Ui::MainWindow* ui;
	void gamestate_update() const;
};
#endif // MAINWINDOW_H
