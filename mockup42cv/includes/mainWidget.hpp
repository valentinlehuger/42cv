// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mainWidget.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 11:57:08 by troussel          #+#    #+#             //
//   Updated: 2015/03/24 13:28:36 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAINWIDGET_CLASS_H
# define  MAINWIDGET_CLASS_H
# include <IVidFRec.hpp>
# include <QWidget>
# include <QLabel>

# define BASEUNIT 10
# define WIDTH BASEUNIT * 8
# define HEIGHT BASEUNIT * 7

typedef struct	s_ImgBox
{
	QWidget		window;
	QLabel*		label;

	s_ImgBox(void) : label(new QLabel(&this->window)) {
		return ;
	}
	~s_ImgBox(void) {
		delete this->label;
		return ;
	}
}				t_ImgBox;

class mainWidget : public QWidget
{
	Q_OBJECT
	t_ImgBox	_vidFRecBox;
	IVidFRec*	_vidFRec;

	void		initQuitButton(int posX, int posY, int width, int height); /************/
	void		initTrainButton(int posX, int posY, int width, int height); /************/
	void		initVidFRecSwitch(int posX, int posY, int width, int height); /************/

public:
	mainWidget(QWidget *parent = NULL); /************/
	virtual ~mainWidget(void); /************/

private slots:
	void		onTrainRequest(void); /************/
	void		toggleVidFRec(void); /************/
	void		updateFaceRecognition(void); /************/
};

#endif /* MAINWIDGET_CLASS_H */
