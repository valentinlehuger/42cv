#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

// Function Headers
void detectAndDisplay(cv::Mat frame);

// Global variables
// Copy this file from opencv/data/haarscascades to target folder
std::string face_cascade_name = "haarcascade_frontalface_alt.xml";
cv::CascadeClassifier face_cascade;
std::string window_name = "Capture - Face detection";
int filenumber; // Number of file to be saved
std::string filename;

// Function main
int main(void)
{
    // Load the cascade
    if (!face_cascade.load(face_cascade_name))
    {
        printf("--(!)Error loading\n");
        return (-1);
    };

    cv::VideoCapture cap(0);

    if ( !cap.isOpened() )  // if not success, exit program
    {
         std::cout << "Cannot open the video file" << std::endl;
         return -1;
    }

    cv::Mat frame;
    bool bSuccess;

    for (;;)
    {
        bSuccess = cap.read(frame);
        if (!bSuccess)
        {
            std::cout << "Error when reading next frame" << std::endl;
            exit(-1);
        }
        bSuccess = cap.read(frame);
        if (!bSuccess)
        {
            std::cout << "Error when reading next frame" << std::endl;
            exit(-1);
        }

        if (!frame.empty())
        {
            detectAndDisplay(frame);
        }
        else
        {
            printf(" --(!) No captured frame -- Break!");
            // break;
        }

        int c = cv::waitKey(10);

        if (27 == char(c))
        {
            break;
        }


    }

    return (0);
}

// Function detectAndDisplay
void detectAndDisplay(cv::Mat frame)
{
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;
    cv::Mat crop;
    cv::Mat res;
    cv::Mat gray;
    std::string text;
    std::stringstream sstm;

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

        crop = frame(roi_b);
        resize(crop, res, cv::Size(128, 128), 0, 0, cv::INTER_LINEAR); // This will be needed later while saving images
        cv::cvtColor(crop, gray, CV_BGR2GRAY); // Convert cropped image to Grayscale

        // Form a filename
        filename = "";
        std::stringstream ssfn;
        ssfn << filenumber << ".png";
        filename = ssfn.str();
        filenumber++;

        imwrite(filename, gray);

        cv::Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
        cv::Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 8, 0);
    }

    // Show image
    sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height << " Filename: " << filename;
    text = sstm.str();

    putText(frame, text, cvPoint(30, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
    imshow("original", frame);

    if (!crop.empty())
    {
        imshow("detected", crop);
    }
    else
        cv::destroyWindow("detected");
}
