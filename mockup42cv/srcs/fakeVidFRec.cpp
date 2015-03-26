// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   fakeVidFRec.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: troussel <troussel@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 12:13:21 by troussel          #+#    #+#             //
//   Updated: 2015/03/24 12:56:49 by troussel         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fakeVidFRec.hpp>
#include <iostream>
#include <fstream>
// #include <QtGui>
#include <stdlib.h>

fakeVidFRec::fakeVidFRec(void)
{
    if (!face_cascade.load("haarcascade_frontalface_alt.xml"))
    {
        std::cerr << "--(!)Error loading" << std::endl;
        exit(-1);
    };
 	model = cv::createFisherFaceRecognizer();
	return ;
}

fakeVidFRec::~fakeVidFRec(void)
{
	return ;
}

bool		fakeVidFRec::openCamera(void)
{
	if (this->_cap.isOpened())
		return (true);
	this->_cap.open(0);
	if (!this->_cap.isOpened()) {
		return (false);
	}
	return (true);
}

bool		fakeVidFRec::releaseVideo(void)
{
	if (!this->_cap.isOpened())
		return (true);
	this->_cap.release();
	if (this->_cap.isOpened()) {
		return (false);
	}
	return (true);
}

static void read_csv(const std::string& filename, cv::vector<cv::Mat>& images, cv::vector<int>& labels, char separator)
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
}

bool		fakeVidFRec::trainModelFromCsv(std::string const pathToCsv)
{
	read_csv(pathToCsv, trainImages, labels, ';');
	return (true);
}

cv::Mat*	fakeVidFRec::getNextFrameRGB(void)
{
	cv::Mat*	mat = new cv::Mat(0, 0, CV_8UC1);

	if (!this->openCamera())
		return (NULL);
	this->_cap.read(*mat);
	cv::cvtColor(*mat, *mat, CV_BGR2RGB);

	// *mat = detectAndDisplay(*mat);
	return (mat);
}

void          fakeVidFRec::trainModelFromCsv(int ac, const char **av, cv::vector<cv::Mat> &images, cv::vector<int> &labels)
{
    if (ac != 2)
    {
        std::cout << "usage: " << av[0] << " <csv.ext>" << std::endl;
        exit (-1);
    }
    try
    {
        read_csv(std::string(av[1]), images, labels, ';');
    } catch (cv::Exception& e)
    {
        std::cerr << "Error opening file \"" << std::string(av[1]) << "\". Reason: " << e.msg << std::endl;
        exit(1);
    }
    model->train(images, labels);
}

cv::Mat 				fakeVidFRec::detectAndDisplay(cv::Mat frame)
{
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;
    cv::Mat crop;
    cv::Mat res;
    cv::Mat gray;
    std::string text;
    std::stringstream sstm;
	int predicted;
	std::string name;

    cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);

    // Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 5, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));


    // Set Region of Interest
    cv::Rect roi_b;
    cv::Rect roi_c;

    size_t ic = 0; // ic is index of current element
    int ac = 0; // ac is area of current element

    size_t ib = 0; // ib is index of biggest element
    int ab = 0; // ab is area of biggest element

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

        crop = frame(roi_c);

        resize(crop, crop, cv::Size(200, 200)); // This will be needed later while saving images
        cv::cvtColor(crop, crop, CV_BGR2GRAY); // Convert cropped image to Grayscale

        predicted = -1;
        double confidence = 0.0;
       	model->predict(crop, predicted, confidence);
        if (confidence < 3000)
		{
			if (predicted == 0)
				name = "Florent";
			else if (predicted == 1)
				name = "Valentin";
			else if (predicted == 2)
				name = "Tony";
        }        else
            name = "Nobody";

       	std::cout << name << " is detected at " << confidence << std::endl;

        cv::Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
        cv::Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 8, 0);

        cv::Point ptTxt(faces[ic].x, faces[ic].y - 5);
		putText(frame, name, ptTxt, cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
    }

    // Show image
    // sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height << " Filename: " << filename;
    // text = sstm.str();

    // putText(frame, text, cvPoint(30, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
    // imshow("original", frame);
    return (frame);
}

