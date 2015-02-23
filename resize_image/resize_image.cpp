#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

std::string		getFileName(std::string path)
{
	return path.substr(path.find_last_of("/\\") + 1);
}

int				main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "Usage ./resize img1.jpg impg2.jpg ..." << std::endl;
		return (-1);
	}

	cv::Mat			img;
	cv::Mat			dst;
	std::string		filename;

	for (int i = 1; i < ac ; i++)
	{
		img = cv::imread(av[i], CV_LOAD_IMAGE_GRAYSCALE);
		cv::imshow(av[i], img);
		cv::resize(img, dst, cv::Size(200, 200));
		cv::imwrite("resizeImages/" + getFileName(av[i]), dst);
	}


	return (0);
}