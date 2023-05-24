
#include "Cards.h"
#include <exception>


inline cv::Size getUsersMetrics();

void setColorMask(cv::Mat&, cv::Scalar &lowbound = cv::Scalar(50, 50, 50), cv::Scalar& uppbound = cv::Scalar(255, 255, 255));



int main()
{
	Cards cards({ 500, 350 }, 10);

	std::string path = "D:/Prog/C++ prog/OpenCVTutorial/media/Bla-bla-car.png";


	cv::Mat img1 = cv::imread(path);
	cv::Mat img2 = cv::imread(path);
	cv::Mat img3 = cv::imread(path);
	cv::Mat img4 = cv::imread(path);
	cv::Mat img5 = cv::imread(path);
	cv::Mat img6 = cv::imread(path);
	cv::Mat img7 = cv::imread(path);
	cv::Mat img8 = cv::imread(path);
	



	cv::Matx33f sepia
	(
		0.272, 0.534, 0.131,
		0.349, 0.686, 0.168,
		0.393, 0.769, 0.189
	);

	setColorMask(img2);

	cv::cvtColor(img3, img3, cv::COLOR_BGR2GRAY);		// B-W

	cv::cvtColor(img4, img4, cv::COLOR_BGR2RGB);		// Negativ | Reverse BGR -> RGB

	cv::blur(img5, img5, cv::Size(5, 3));				// Blur (получилось DLSS сглаживание)

	cv::transform(img6, img6, sepia);					// Sepia

	
	cv::medianBlur(img7, img7, 15);
	cv::Mat texture(img7.size(), CV_8UC3);
	cv::randn(texture, cv::Scalar(20, 20, 20), cv::Scalar(50, 50, 50));		// Durka
	cv::multiply(img7, texture, img7, 1.0 / 255.0);

	cv::cvtColor(img8, img8, cv::COLOR_BGR2GRAY);		// Border!
	cv::Canny(img8, img8, 0, 350);


	cards << img1 << img2 << img3 << img4 << img5 << img6 << img7 << img8;
	

	Cards card = std::move(cards);
	card.show();

	cv::waitKey(0);
	return 0;
}


void setColorMask(cv::Mat &img, cv::Scalar &lowbound, cv::Scalar &uppbound)
{
	cv::inRange(img, lowbound, uppbound, img);
}
