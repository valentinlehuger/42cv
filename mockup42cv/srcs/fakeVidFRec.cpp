// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   fakeVidFRec.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 12:13:21 by troussel          #+#    #+#             //
//   Updated: 2015/03/24 12:56:49 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fakeVidFRec.hpp>
#include <iostream>
// #include <QtGui>
#include <stdlib.h>

fakeVidFRec::fakeVidFRec(void)
{
	return ;
}

fakeVidFRec::~fakeVidFRec(void)
{
	return ;
}

bool		fakeVidFRec::openCamera(void)
{
	if (this->_cap.isOpened())
		return (true);
	this->_cap.open(0);
	if (!this->_cap.isOpened()) {
		return (false);
	}
	return (true);
}

bool		fakeVidFRec::releaseVideo(void)
{
	if (!this->_cap.isOpened())
		return (true);
	this->_cap.release();
	if (this->_cap.isOpened()) {
		return (false);
	}
	return (true);
}

bool		fakeVidFRec::trainModelFromCsv(std::string const pathToCsv)
{
	std::cout << "I train with " << pathToCsv << std::endl;
	return (true);
}

cv::Mat*	fakeVidFRec::getNextFrameRGB(void)
{
	cv::Mat*	mat = new cv::Mat(0, 0, CV_8UC1);

	if (!this->openCamera())
		return (NULL);
	this->_cap.read(*mat);
	cv::cvtColor(*mat, *mat, CV_BGR2RGB);
	return (mat);
// 	QImage	qimg(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
// 	QPixmap	pixmap = QPixmap::fromImage(qimg);
// 	this->_label->setPixmap(pixmap);
// 	this->_label->resize(pixmap.size());
// 	this->_window.show();
// 	return ;
}
