// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mainWidget.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 13:19:22 by troussel          #+#    #+#             //
//   Updated: 2015/03/26 14:30:14 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <mainWidget.hpp>
#include <VidFRec.hpp>
#include <QApplication>
#include <QtGui>
#include <QPushButton>
#include <QTimer>
#include <QFileDialog>
#include <unistd.h>
#include <iostream>

mainWidget::mainWidget(std::string const pathToXmlHCascade, QWidget* parent) : QWidget(parent), _vidFRec(new VidFRec(pathToXmlHCascade)), _timer(new QTimer(this))
{
	this->resize(WIDTH, HEIGHT);
	this->initTrainButton(PBUTX, PBUTY * 1, PBUTWIDTH, PBUTHEIGHT);
	this->initVidFRecSwitch(PBUTX, PBUTY * 3, PBUTWIDTH, PBUTHEIGHT);
	this->initQuitButton(PBUTX, PBUTY * 5, PBUTWIDTH, PBUTHEIGHT);
	this->_timer->start(10);
	this->show();
	return ;
}

mainWidget::~mainWidget(void)
{
	delete this->_vidFRec;
	delete this->_timer;
	return ;
}

void		mainWidget::initTrainButton(int posX, int posY, int width, int height)
{
	QPushButton	*trainButton = new QPushButton("Train Face Recognition", this);

	trainButton->setGeometry(posX, posY, width, height);
	connect(trainButton, SIGNAL(clicked()), this, SLOT(onTrainRequest()));
	return ;
}

void		mainWidget::initVidFRecSwitch(int posX, int posY, int width, int height)
{
	QPushButton	*vidFRecButton = new QPushButton("Face Recognition", this);

	vidFRecButton->setGeometry(posX, posY, width, height);
	connect(vidFRecButton, SIGNAL(clicked()), this, SLOT(toggleVidFRec()));
	return ;
}

void		mainWidget::initQuitButton(int posX, int posY, int width, int height)
{
	QPushButton	*quitButton = new QPushButton("Quit", this);

	quitButton->setGeometry(posX, posY, width, height);
	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
	return ;
}

void		mainWidget::onTrainRequest(void)
{
	QString		file;

	file = QFileDialog::getOpenFileName(this, "Select Files to sned in term...", QDir::homePath(), tr("CSV Files (*.csv)"));
	if (file.isEmpty())
		return ;
	this->_vidFRec->trainModelFromCsv(file.toLocal8Bit().constData());
	return ;
}

void		mainWidget::toggleVidFRec(void)
{
	if (!this->_vidFRecBox.toggle) {
		connect(this->_timer, SIGNAL(timeout()), this, SLOT(updateFaceRecognition()));
		this->_vidFRecBox.toggle = true;
	} else {
		disconnect(this->_timer, 0, this, 0);
		this->_vidFRecBox.toggle = false;
		this->_vidFRecBox.window.close();
		this->_vidFRec->releaseVideo();
	}
	return ;
}

void		mainWidget::updateFaceRecognition(void)
{
	cv::Mat*	mat = this->_vidFRec->getNextFrameRGB();

	if (mat == NULL)
		return ;

	QImage		qimg(mat->data, mat->cols, mat->rows, mat->step, QImage::Format_RGB888);
	QPixmap		pixmap = QPixmap::fromImage(qimg);

	this->_vidFRecBox.label->setPixmap(pixmap);
	this->_vidFRecBox.label->resize(pixmap.size());
	this->_vidFRecBox.window.show();
	delete mat;
	return ;
}
