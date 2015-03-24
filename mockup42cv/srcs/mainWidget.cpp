// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mainWidget.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 13:19:22 by troussel          #+#    #+#             //
//   Updated: 2015/03/24 14:53:58 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <mainWidget.hpp>
#include <iostream>//////////
#include <fakeVidFRec.hpp>//////////
#include <QtApplication>
#include <QtGui>
#include <QPushButton>

mainWidget::mainWidget(QWidget* parent) : QWidget(parent), _vidFRec(new fakeVidFRec()) /////////
{
	this->resize(WIDTH, HEIGHT);
	this->initTrainButton(PBUTX, PBUTY * 1, PBUTWIDTH, PBUTHEIGHT);
	this->initVidFRecSwitch(PBUTX, PBUTY * 3, PBUTWIDTH, PBUTHEIGHT);
	this->initQuitButton(PBUTX, PBUTY * 5, PBUTWIDTH, PBUTHEIGHT);
	return ;
}

mainWidget::~mainWidget(void)
{
	delete this->_vidFRec;
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
	std::cout << "Train request clicked" << std::endl;
	return ;
}

void		mainWidget::toggleVidFRec(void)
{
	std::cout << "Toggle Video Face Rec clicked" << std::endl;
	return ;
}

void		mainWidget::updateFaceRecognition(void)
{
	std::cout << "Updt FR" << std::endl;
	return ;
}
