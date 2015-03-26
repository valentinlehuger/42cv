// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 15:03:51 by troussel          #+#    #+#             //
//   Updated: 2015/03/26 14:13:21 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <mainWidget.hpp>
#include <QApplication>
#include <iostream>
#include <stdlib.h>

int		main(int ac, char **av)
{
	QApplication	app(ac, av);
	mainWidget*		box;


	if (ac != 2) {
		std::cout << "arg error" << std::endl;
		return (-1);
	}
	box = new mainWidget(av[1]);
	delete box;
	return app.exec();
}
