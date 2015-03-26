// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VidFRec.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/26 13:39:10 by troussel          #+#    #+#             //
//   Updated: 2015/03/26 14:05:13 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef VIDFREC_CLASS_H
# define VIDFREC_CLASS_H
# include <IVidFRec.hpp>
# include <QWidget>
# include <string>
# include <opencv2/core/core.hpp>
# include <opencv2/highgui/highgui.hpp>
# include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/contrib.hpp>

class VidFRec : public IVidFRec
{
	cv::Ptr<cv::FaceRecognizer>	_model;
	cv::CascadeClassifier		_face_cascade;

	cv::VideoCapture			_cap;

	VidFRec(void);

	void				read_csv(const std::string& filename, cv::vector<cv::Mat>& images, cv::vector<int>& labels, char separator);
	cv::Mat*			detect(cv::Mat* frame); /***********/

public:
	VidFRec(std::string const pathToXmlHCascade);
	virtual ~VidFRec(void);

	bool				openCamera(void);
	bool				releaseVideo(void);
	bool				trainModelFromCsv(std::string const pathToCsv);
	cv::Mat*			getNextFrameRGB(void); /*******/
};

#endif /* VIDFREC_CLASS_H */
