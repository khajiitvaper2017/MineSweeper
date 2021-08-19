#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include "minesweeper.h"
#include <QTimer>
#include <QTime>
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
	void on_timer_alarm() const;
	void on_button_game_clicked();
	void on_game_map_clicked(const QMouseEvent*);
	void on_difficulty_custom_toggled(bool checked) const;

private:
	QTimer* qtimer= nullptr;		//timer
	QTime init_time;				//timer initialization time
	
	QPixmap* ms_image = nullptr;	//image that contains info about mines
	QPixmap* game_image = nullptr;	//mask that covers ms_image from player and allows to set flags

	void create_ms_image();
	void create_game_image();
	
	MineSweeper* ms = nullptr;		//main game object	
	int x = 9, y = 9, mines = 10;	//default values for game field 
	const int cell_size = 30;		//cell size is equal to assets resolution

	char game_state = 'P';			//P - Playing, W - Won, L - Losed
	void gamestate_update() const;	//updates new game button
	
	Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
