#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <sstream>


static void read_csv(const std::string& filename, cv::vector<cv::Mat>& images, cv::vector<int>& labels, char separator = ';');
static void detectAndDisplay(cv::Mat frame);

cv::Ptr<cv::FaceRecognizer> model = cv::createFisherFaceRecognizer();
std::string face_cascade_name = "haarcascade_frontalface_alt.xml";
cv::CascadeClassifier face_cascade;


int main(int ac, const char **av) 
{
	if (ac != 2)
	{
        std::cout << "usage: " << av[0] << " <csv.ext>" << std::endl;
        return (-1);
	}

    cv::vector<cv::Mat> 		images;
    cv::vector<int> 			labels;

    try
    {
        read_csv(std::string(av[1]), images, labels);
    } catch (cv::Exception& e)
    {
        std::cerr << "Error opening file \"" << std::string(av[1]) << "\". Reason: " << e.msg << std::endl;
        exit(1);
    }

    model->train(images, labels);

    // Load the cascade
    if (!face_cascade.load(face_cascade_name))
    {
        std::cerr << "--(!)Error loading" << std::endl;
        return (-1);
    };

    cv::VideoCapture cap(0);

    if ( !cap.isOpened() )  // if not success, exit program
    {
         std::cerr << "Cannot open the video file" << std::endl;
         return -1;
    }

    cv::Mat frame;
    bool bSuccess;

    for (;;)
    {
        bSuccess = cap.read(frame);
        if (!bSuccess)
        {
            std::cerr << "Error when reading next frame" << std::endl;
            exit(-1);
        }
        bSuccess = cap.read(frame);
        if (!bSuccess)
        {
            std::cerr << "Error when reading next frame" << std::endl;
            exit(-1);
        }

        if (!frame.empty())
            detectAndDisplay(frame);
        else
        {
            std::cerr << " --(!) No captured frame -- Break!" << std::endl;
            break;
        }

        int c = cv::waitKey(10);
        if (27 == char(c))
            break;
    }

    return (0);
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

static void detectAndDisplay(cv::Mat frame)
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
       	text = "Nobody";
       	predicted = model->predict(crop);

       	if (predicted == 0)
			name = "Florent";
       	else if (predicted == 1)
       		name = "Valentin";
        else if (predicted == 2)
            name = "Tony";

       	std::cout << name << " is detected" << std::endl;

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
    imshow("original", frame);

}
