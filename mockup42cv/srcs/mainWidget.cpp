// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mainWidget.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 13:19:22 by troussel          #+#    #+#             //
//   Updated: 2015/03/24 13:26:32 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <mainWidget.hpp>
#include <fakeVidFRec.hpp>//////////
#include <QtGui>

mainWidget::mainWidget(QWidget* parent) : QWidget(parent), _vidFRec(new fakeVidFRec()) /////////
{
	return ;
}

mainWidget::~mainWidget(void)
{
	delete this->_vidFRec;
	return ;
}
