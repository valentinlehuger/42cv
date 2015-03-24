// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 15:03:51 by troussel          #+#    #+#             //
//   Updated: 2015/03/24 15:05:53 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <mainWidget.hpp>
#include <QApplication>

int		main(int ac, char **av)
{
	QApplication	app(ac, av);
	mainWidget		box;

	return app.exec();
}
