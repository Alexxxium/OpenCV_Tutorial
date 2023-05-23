
#include "Cards.h"
#include <exception>


inline cv::Size getUsersMetrics();




int main()
{
	Cards cards({ 100, 100 }, 5);

	cv::Mat img1 = cv::imread("D:/Prog/C++ prog/OpenCVTutorial/media/Bla-bla-car.png");
	cv::Mat img2 = cv::imread("../media/Bla-bla-car.png");
	cv::Mat img3 = cv::imread("../media/Bla-bla-car.png");
	cv::Mat img4 = cv::imread("../media/Bla-bla-car.png");
	cv::Mat img5 = cv::imread("../media/Bla-bla-car.png");
	cv::Mat img6 = cv::imread("../media/Bla-bla-car.png");
	cv::Mat img7 = cv::imread("../media/Bla-bla-car.png");
	cv::Mat img8 = cv::imread("../media/Bla-bla-car.png");
	cv::Mat img9 = cv::imread("../media/Bla-bla-car.png");
	cv::Mat img10 = cv::imread("../media/Bla-bla-car.png");
	cv::Mat img11 = cv::imread("../media/Bla-bla-car.png");

	try
	{
		cv::resize(img1, img1, { 500, 350 });
	}
	catch (std::exception exc)
	{
		std::cout << exc.what();
	}
	int count = 0;


	//std::cout << cards.maxLenght()
	cards << img1;

	//cards.show();
	// 
	Cards card = std::move(cards);
	card.show();
	//cards.show();
	return 0;
}

