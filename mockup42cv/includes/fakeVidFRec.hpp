// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   fakeVidFRec.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 12:12:30 by troussel          #+#    #+#             //
//   Updated: 2015/03/24 15:03:25 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FAKEVIDFREC_CLASS_H
# define FAKEVIDFREC_CLASS_H
# include <IVidFRec.hpp>
# include <QWidget>
# include <string>
# include <opencv2/core/core.hpp>
# include <opencv2/highgui/highgui.hpp>
# include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/contrib.hpp>

class fakeVidFRec : public IVidFRec
{
	cv::VideoCapture		_cap;
	cv::CascadeClassifier face_cascade;
	cv::Ptr<cv::FaceRecognizer> model;
	cv::vector<cv::Mat>		trainImages;
	cv::vector<int>			labels;

public:
	fakeVidFRec(void);
	virtual ~fakeVidFRec(void);

	bool				openCamera(void);
	bool				releaseVideo(void);
	bool				trainModelFromCsv(std::string const pathToCsv);
	cv::Mat*			getNextFrameRGB(void);
	cv::Mat				detectAndDisplay(cv::Mat frame);
	void          		trainModelFromCsv(int ac, const char **av, cv::vector<cv::Mat> &images, cv::vector<int> &labels);
};

#endif /* FAKEVIDFREC_CLASS_H */
