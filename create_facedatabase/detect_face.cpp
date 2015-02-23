#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <dirent.h>
#include <unistd.h>
// #include <stdio.h>

void detectAndSave(cv::Mat frame, std::string fileName, std::string pathToSave);

cv::CascadeClassifier face_cascade;


int         main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Usage : ./detect \"path/to/imageFolder/\"" << std::endl;
        return (EXIT_FAILURE);
    }

    std::string         foldername(av[1]);
    std::string         currentFileName;
    std::string         pathToSave("/Users/valentin/42cv/resource/persoFaces/");
    DIR                 *dir;
    struct dirent       *ent;
    cv::Mat             frame;

    if (!face_cascade.load("haarcascade_frontalface_alt.xml"))
    {
        std::cout << "--(!)Error loading\n" << std::endl;
        return (-1);
    };

    if (foldername[foldername.size() - 1] != '/')
        foldername = foldername + "/";

    if ((dir = opendir (foldername.c_str())) != NULL)
    {
        readdir(dir);
        readdir(dir);
        while ((ent = readdir(dir)) != NULL)
        {
            currentFileName = foldername + ent->d_name;
            std::cout << currentFileName << std::endl;
            frame = cv::imread(currentFileName, CV_LOAD_IMAGE_COLOR);
            imshow("photo", frame);
            sleep(1);
            std::cout << "Before detectAndSave." << std::endl;
            detectAndSave(frame, currentFileName, pathToSave);
            std::cout << "After detectAndSave." << std::endl;
        }
        closedir (dir);
    }
    else
    {
        perror ("Could not open directory");
        return (EXIT_FAILURE);
    }

}


void detectAndSave(cv::Mat frame, std::string fileName, std::string pathToSave)
{
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;
    cv::Mat crop;
    cv::Mat res;
    cv::Mat gray;
    std::string text;
    std::stringstream sstm;
    std::string answer;

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

    std::cout << "Here 1" << std::endl;
    for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)
    {
        std::cout << "Here 2" << std::to_string(ic) << std::endl;
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

        crop = frame(roi_b);
        resize(crop, res, cv::Size(128, 128), 0, 0, cv::INTER_LINEAR); // This will be needed later while saving images
        cv::cvtColor(crop, gray, CV_BGR2GRAY); // Convert cropped image to Grayscale

        imshow("detected", gray);
        std:: cout << "Is it a face ? " << std::endl;
        std::cin >> answer;
        std::cout << std::endl;

        if (answer.compare("y"))
            std::cout << pathToSave + fileName + "_" + std::to_string(ic) + ".png" << std::endl;
        // imwrite(pathToSave + fileName + "_" + toString(i) + ".png", gray);

        cv::Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
        cv::Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 8, 0);
    }

    // // Show image
    // sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height << " Filename: " << filename;
    // text = sstm.str();

    // putText(frame, text, cvPoint(30, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
    // imshow("original", frame);

    // if (!crop.empty())
    // {
    //     imshow("detected", crop);
    // }
    // else
    //     cv::destroyWindow("detected");
}
