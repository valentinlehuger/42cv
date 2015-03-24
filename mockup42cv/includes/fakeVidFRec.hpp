// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   fakeVidFRec.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 12:12:30 by troussel          #+#    #+#             //
//   Updated: 2015/03/24 12:41:04 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FAKEVIDFREC_CLASS_H
# define FAKEVIDFREC_CLASS_H
# include <opencv2/core/core.hpp>
# include <opencv2/highgui/highgui.hpp>
# include <opencv2/imgproc/imgproc.hpp>

class fakeVidFRec : public IVidFRec
{
	Q_OBJECT
	cv::VideoCapture	_cap;

public:
	fakeVidFRec(void);
	virtual ~fakeVidFRec(void);

	bool				openCamera(void);
	bool				releaseVideo(void);
	bool				trainModelFromCsv(std::string const pathToCsv);
	cv::Mat*			getNextFrameRGB(void);
};

#endif /* FAKEVIDFREC_CLASS_H */
