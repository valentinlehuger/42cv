// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mainWidget.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 11:57:08 by troussel          #+#    #+#             //
//   Updated: 2015/03/26 14:18:29 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAINWIDGET_CLASS_H
# define  MAINWIDGET_CLASS_H
# include <IVidFRec.hpp>
# include <QWidget>
# include <QTimer>
# include <QLabel>

# define BASEUNIT 100
# define WIDTH BASEUNIT * 7
# define HEIGHT BASEUNIT * 7

# define PBUTWIDTH BASEUNIT * 4
# define PBUTHEIGHT BASEUNIT * 1
# define PBUTX (WIDTH - PBUTWIDTH) / 2
# define PBUTY PBUTHEIGHT

typedef struct	s_ImgBox
{
	QWidget		window;
	QLabel*		label;
	bool		toggle;

	s_ImgBox(void) : label(new QLabel(&this->window)), toggle(false) {
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
	QTimer*		_timer;

	void		initQuitButton(int posX, int posY, int width, int height);
	void		initTrainButton(int posX, int posY, int width, int height);
	void		initVidFRecSwitch(int posX, int posY, int width, int height);

public:
	mainWidget(std::string const pathToXmlHCascade, QWidget *parent = NULL);
	virtual ~mainWidget(void);

private slots:
	void		onTrainRequest(void);
	void		toggleVidFRec(void);
	void		updateFaceRecognition(void);
};

#endif /* MAINWIDGET_CLASS_H */
