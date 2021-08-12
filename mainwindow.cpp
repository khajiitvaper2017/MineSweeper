#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>
#include <omp.h>
MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	  , ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	const QSize size = qApp->screens()[0]->size();
	ui->x_count->setMaximum((size.width() - 70) / cell_size);
	ui->y_count->setMaximum((size.height() - 400) / cell_size);
	ui->mines_count->setMaximum(ui->x_count->maximum() * ui->y_count->maximum() - 1);
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_button_game_clicked()
{
	if (ui->difficulty_1->isChecked())
	{
		x = 9;
		y = 9;
		mines = 10;
	}
	else if (ui->difficulty_2->isChecked())
	{
		x = 16;
		y = 16;
		mines = 40;
	}
	else if (ui->difficulty_3->isChecked())
	{
		x = 30;
		y = 16;
		mines = 99;
	}
	else if (ui->difficulty_custom->isChecked())
	{
		x = ui->x_count->value();
		y = ui->y_count->value();
		mines = ui->mines_count->value();
		if (mines >= x * y)
		{
			QMessageBox::warning(this, "Error!", "Too many mines for this area!");
			return;
		}
	}


	delete qtimer;

	qtimer = new QTimer();

	connect(qtimer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
	game_state = 'P';
	gamestate_update();


	delete ms;


	delete ms_image;


	ms = new MineSweeper(x, y, mines);
	ui->label_mines->display(mines);


	setMinimumSize(400, 400);
	setMaximumSize(x * cell_size + 30, y * cell_size + 250);

	ui->game_map->setMinimumSize(x * cell_size + 1, y * cell_size + 1);
	ui->game_map->setMaximumSize(x * cell_size + 1, y * cell_size + 1);

	resize(100000, 1000000);
	this->setFixedSize(size());
	std::thread ms_thread(&MainWindow::create_ms_image, this);
	std::thread game_thread(&MainWindow::create_game_image, this);
	/*create_ms_image();
	create_game_image();*/

	ms_thread.join();
	QPixmap ret(*ms_image);
	QPainter retP(&ret);

	game_thread.join();
	retP.drawPixmap(0, 0, *game_image);
	ui->game_map->setPixmap(ret);
	qtimer->start(1000);
	init_time = QTime::currentTime();
}

void MainWindow::slotTimerAlarm() const
{
	const auto el = QTime::currentTime().addSecs(
		-init_time.hour() * 60 * 60 - init_time.minute() * 60 - init_time.second());
	ui->label_time->display(el.minute() * 60 + el.hour() * 60 * 60 + el.second());
}

void MainWindow::create_ms_image()
{
	ms_image = new QPixmap(x * cell_size + 1, y * cell_size + 1);
	ms_image->fill();
	QPainter qp(ms_image);

#pragma omp parallel for collapse(2)
	for (int i = 0; i < x; i++)
	{
		qp.drawLine(i * cell_size, 0, i * cell_size, y * cell_size);
		for (int j = 0; j < y; j++)
		{
			qp.drawLine(0, j * cell_size, x * cell_size, j * cell_size);
			const char ch = ms->field(i, j);
			qp.drawImage(QPointF(i * cell_size + 1, j * cell_size + 1),
			             QImage(":/resources/img/" + QString::number(ch) + ".png"));
		}
	}
	qp.drawLine(x * cell_size, 0, x * cell_size, y * cell_size);
	qp.drawLine(0, y * cell_size, x * cell_size, y * cell_size);
}

void MainWindow::create_game_image()
{
	delete game_image;

	game_image = new QPixmap(x * cell_size + 1, y * cell_size + 1);
	game_image->fill(Qt::transparent);

	QPainter qp_game(game_image);

#pragma omp parallel for collapse(2)
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			{
				const char cell = ms->play_field[i][j];
				const auto color = cell == '*' ? Qt::red : cell == '=' ? Qt::green : Qt::lightGray;
				if (cell == 'O') continue;
#pragma omp critical
				{
					qp_game.fillRect(i * cell_size, j * cell_size, cell_size, cell_size, color);
					if (cell == 'F')
						qp_game.drawImage(QPointF(i * cell_size + 2, j * cell_size), QImage(":/resources/img/flag.png"));

					else if (cell == '*'|| cell == '=')
					{
						qp_game.drawImage(QPointF(i * cell_size, j * cell_size), QImage(":/resources/img/mine.png"));
					}
				}
			}

			qp_game.drawLine(0, j * cell_size, x * cell_size, j * cell_size);
		}
		qp_game.drawLine(i * cell_size, 0, i * cell_size, y * cell_size);
	}
	qp_game.drawLine(x * cell_size, 0, x * cell_size, y * cell_size);
	qp_game.drawLine(0, y * cell_size, x * cell_size, y * cell_size);
}

void MainWindow::on_game_map_clicked(QMouseEvent* mouse_event)
{
	gamestate_update();
	if (game_state == 'L' || game_state == 'W')return;
	if (ms == nullptr)return;
	const auto mouse_pos = mouse_event->position();
	const QPoint cell(mouse_pos.x() / cell_size, mouse_pos.y() / cell_size);
	if (cell.x() == x || cell.y() == y)
		return;

	switch (const auto mouse_button = mouse_event->button(); mouse_button)
	{
	case Qt::MouseButton::LeftButton:
		ms->openCell(cell.x(), cell.y());
		break;
	case Qt::MouseButton::RightButton:
		if (ms->play_field[cell.x()][cell.y()] == 'F')
			ms->removeFlag(cell.x(), cell.y());
		else
			ms->setFlag(cell.x(), cell.y());
		break;
	default:
		break;
	}

	std::thread game_thread(&MainWindow::create_game_image, this);
	QPixmap ret(*ms_image);
	QPainter retP(&ret);
	game_thread.join();
	retP.drawPixmap(0, 0, *game_image);
	ui->game_map->setPixmap(ret);

	mines = ms->getMines();
	ui->label_mines->display(mines);
	if (!ms->getGameState())
		game_state = 'L';
	if (ms->checkWon())
		game_state = 'W';
	gamestate_update();
}

void MainWindow::gamestate_update() const
{
	switch (game_state)
	{
	case 'L':
		ui->button_game->setStyleSheet("QPushButton {background-color: #FFFFFF; color: red; font-weight: bold;}");
		ui->button_game->setText("GAME OVER");
		qtimer->stop();
		break;
	case 'W':
		ui->button_game->setStyleSheet("QPushButton {background-color: #FFFFFF; color: green; font-weight: bold;}");
		ui->button_game->setText("YOU WON!");
		qtimer->stop();
		break;
	default:
		ui->button_game->setStyleSheet("QPushButton {background-color: #FFFFFF; color: black;}");
		ui->button_game->setText("Start New Game");
	}
}


void MainWindow::on_difficulty_custom_toggled(const bool checked) const
{
	ui->x_count->setEnabled(checked);
	ui->y_count->setEnabled(checked);
	ui->mines_count->setEnabled(checked);
}
