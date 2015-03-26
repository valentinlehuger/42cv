// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VidFRec.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/26 13:49:41 by troussel          #+#    #+#             //
//   Updated: 2015/03/26 14:30:34 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <VidFRec.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

VidFRec::VidFRec(std::string const pathToXmlHCascade) : _model(cv::createFisherFaceRecognizer())
{
    // Load the cascade
    if (!this->_face_cascade.load(pathToXmlHCascade))
    {
        std::cerr << "--(!)Error loading HCascade" << std::endl;
		exit(1);
    };
	return ;
}

VidFRec::~VidFRec(void)
{
	return ;
}

bool		VidFRec::openCamera(void)
{
	if (this->_cap.isOpened())
		return (true);
	this->_cap.open(0);
	if (!this->_cap.isOpened()) {
		return (false);
	}
	return (true);
}

bool		VidFRec::releaseVideo(void)
{
	if (!this->_cap.isOpened())
		return (true);
	this->_cap.release();
	if (this->_cap.isOpened()) {
		return (false);
	}
	return (true);
}

void		VidFRec::read_csv(const std::string& filename, cv::vector<cv::Mat>& images, cv::vector<int>& labels, char separator)
{
    std::ifstream file(filename.c_str(), std::ifstream::in);
    if (!file) {
        std::string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    std::string line, path, classlabel;
    while (getline(file, line))
    {
        std::stringstream liness(line);
        std::getline(liness, path, separator);
        std::getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty())
        {
            images.push_back(cv::imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
	return ;
}

bool		VidFRec::trainModelFromCsv(std::string const pathToCsv)
{
    cv::vector<cv::Mat> 		images;
    cv::vector<int> 			labels;

	std::cout << "I train with " << pathToCsv << std::endl;
    try
    {
        this->read_csv(pathToCsv, images, labels, ';');
    } catch (cv::Exception& e)
    {
        std::cerr << "Error opening file \"" << pathToCsv << "\". Reason: " << e.msg << std::endl;
		return (false);
    }
    this->_model->train(images, labels);
	return (true);
}

cv::Mat*	VidFRec::getNextFrameRGB(void)
{
	cv::Mat*	mat = new cv::Mat(0, 0, CV_8UC1);

	if (!this->openCamera())
		return (NULL);
	this->_cap.read(*mat);
	if (mat->empty())
		return (NULL);
	detect(mat);
	cv::cvtColor(*mat, *mat, CV_BGR2RGB);
	return (mat);
}

cv::Mat*	VidFRec::detect(cv::Mat* frame)
{
    std::vector<cv::Rect>	faces;
    cv::Mat					frame_gray;
    cv::Mat					crop;
    cv::Mat					res;
    cv::Mat					gray;
    std::string				text;
    std::stringstream		sstm;
	int						predicted;
	std::string				name;

    cv::cvtColor(*frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);

    // Detect faces
    this->_face_cascade.detectMultiScale(frame_gray, faces, 1.1, 5, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));


    // Set Region of Interest
    cv::Rect				roi_b;
    cv::Rect				roi_c;

    size_t					ic = 0; // ic is index of current element
    int						ac = 0; // ac is area of current element

    size_t					ib = 0; // ib is index of biggest element
    int						ab = 0; // ab is area of biggest element

    for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)
    {
        std::cout << faces[ic].size() << std::endl;
        roi_c.x = faces[ic].x;
        roi_c.y = faces[ic].y;
        roi_c.width = (faces[ic].width);
        roi_c.height = (faces[ic].height);

        ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

        roi_b.x = faces[ib].x;
        roi_b.y = faces[ib].y;
        roi_b.width = (faces[ib].width);
        roi_b.height = (faces[ib].height);

        ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

        if (ac > ab)
        {
            ib = ic;
            roi_b.x = faces[ib].x;
            roi_b.y = faces[ib].y;
            roi_b.width = (faces[ib].width);
            roi_b.height = (faces[ib].height);
        }

        crop = frame[0](roi_c);

        resize(crop, crop, cv::Size(200, 200)); // This will be needed later while saving images
        cv::cvtColor(crop, crop, CV_BGR2GRAY); // Convert cropped image to Grayscale

        predicted = -1;
        double confidence = 0.0;
       	this->_model->predict(crop, predicted, confidence);
        if (confidence < 3000)
		{
			if (predicted == 0)
				name = "Florent";
			else if (predicted == 1)
				name = "Valentin";
			else if (predicted == 2)
				name = "Tony";
        }
		else
            name = "Nobody";

       	std::cout << name << " is detected at " << confidence << std::endl;

        cv::Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
        cv::Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        rectangle(*frame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 8, 0);

        cv::Point ptTxt(faces[ic].x, faces[ic].y - 5);
		putText(*frame, name, ptTxt, cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
    }
	return (frame);
}
