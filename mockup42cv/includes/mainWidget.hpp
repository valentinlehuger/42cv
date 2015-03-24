#ifndef MAINWIDGET_CLASS_H
# define  MAINWIDGET_CLASS_H
# include <IVidFRec.hpp>
# include <QWidget>
# include <QLabel>

typedef struct	s_ImgBox
{
  QWidget	window;
  QLabel*	label;	
}		t_ImgBox;

class mainWidget : public QWidget
{
  Q_OBJECT
  t_ImgBox	_vidFRecBox;
  IVidFRec*	_vidFRec;

  void		initQuitButton(int posX, int posY, int width, int height);
  void		initVidFRecSwitch(int posX, int posY, int width, int height);


public:
  mainWidget(QWidget *parent = NULL);
  virtual ~mainWidget(void);

private slots:
  void		updateFaceRecognition(void);
};

#endif /* MAINWIDGET_CLASS_H */
