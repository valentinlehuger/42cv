#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


cv::Mat         absolute_difference(cv::Mat mat1, cv::Mat mat2)
{
    if (mat1.size() != mat2.size())
    {
        std::cout << "mat1 and mat2 have not the same dimensions" << std::endl;
        std::exit(-1);
    }

    cv::Mat         result = cv::Mat::zeros(mat1.size(), CV_32S);

    for (int i = 0; i < mat1.size().height; i++)
    {
        for (int j = 0; j < mat1.size().width; j++)
            result.at<int>(i,j) = (mat1.at<int>(i,j) == mat2.at<int>(i,j)) ? 0 : 1;
    }

    return (result);
}

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: ./tracking video.mp4" << std::endl;
        return (-1);
    }

    VideoCapture cap(argv[1]); // open the video file for reading

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the video file" << endl;
         return -1;
    }

    double fps = cap.get(CV_LOAD_IMAGE_GRAYSCALE); //get the frames per seconds of the video

    cout << "Frame per seconds : " << fps << endl;

    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

    Mat frame1;

    bool bSuccess = cap.read(frame1); // read a new frame from video
    cvtColor(frame1, frame1, CV_BGR2GRAY);
    while(1)
    {
        Scalar color = Scalar(255,0,255);

        Mat frame2;
        Mat frameBW;
        Mat frame_thr;



        bSuccess = cap.read(frame2); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
                        cout << "Cannot read the frame from video file" << endl;
                       break;
        }

        cv::vector<cv::vector<cv::Point> >   contours;
        vector<Vec4i>                       hierarchy;

        Mat copy2;
        frame2.copyTo(copy2);
        cvtColor(copy2, copy2, CV_BGR2GRAY);

        absdiff(copy2, frame1, frameBW);

        threshold(frameBW, frame_thr, 10, 255, THRESH_BINARY);
        GaussianBlur(frame_thr, frame_thr, Size(15, 15), 5, 4);
        threshold(frame_thr, frame_thr, 50, 255, THRESH_BINARY);

        Mat copy;
        frame_thr.copyTo(copy);
        findContours(copy, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    
        rectangle(frame2, boundingRect(contours.at(contours.size() - 1)), color, 2); 

        imshow("MyVideoThresholded", frame_thr);
        imshow("MyVideoWithBound", frame2); //show the frame in "MyVideo" window


        if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
       {
                cout << "esc key is pressed by user" << endl; 
                break; 
       }
       frame1 = copy2;
    }

    return (0);
}
