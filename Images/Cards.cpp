#include "Cards.h"
#include <Windows.h>


inline cv::Size getUsersMetrics()
{
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	return cv::Size(width, height);
}



Cards::Cards(const cv::Size& imgSize, const int& col) :
	maxColls(col),
	maxSize(imgSize)
{
	const auto& window = getUsersMetrics();

	if (maxSize.width > window.width || maxSize.height > window.height || maxColls <= 0)
		throw 1;

	maxColls = (maxColls * maxSize.width > window.width) ? (window.width / maxSize.width) : maxColls;
	maxRows = window.height / maxSize.height;


	imgs.resize(maxRows);
}

Cards::Cards(Cards&& copy) noexcept :
	imgs(std::move(copy.imgs)),
	maxColls(copy.maxColls),
	maxSize(copy.maxSize),
	maxRows(copy.maxRows)
{
}



void Cards::operator=(const Cards& copy) noexcept
{
	imgs = copy.imgs;
	maxColls = copy.maxColls;
	maxRows = copy.maxRows;
	maxSize = copy.maxSize;
}

void Cards::operator=(Cards&& copy) noexcept
{
	imgs = std::move(copy.imgs);
	maxColls = copy.maxColls;
	maxRows = copy.maxRows;
	maxSize = copy.maxSize;
}



Cards& Cards::operator<<(cv::Mat& img)
{
	cv::resize(img, img, maxSize);

	static int curr = 0;

	if (curr > maxRows)
		throw 1;

	if (imgs[curr].size() == maxColls)
		++curr;

	imgs[curr].push_back(img);

	return *this;
}



void Cards::show() noexcept
{
	const auto& window = getUsersMetrics();

	const int rows = imgs.size() < maxRows ? imgs.size() : maxRows;

	int p_x = (window.width - maxColls * maxSize.width) / 2;
	int p_y = (window.height - rows * maxSize.height) / 2;

	int count = 1;


	for (const auto& vec : imgs)
	{
		if (vec.size() < maxColls) {
			p_x = (window.width - vec.size() * maxSize.width) / 2;
		}

		for (const auto& i : vec)
		{
			std::string wind_name = "Window " + std::to_string(count);

			cv::imshow(wind_name, i);
			cv::moveWindow(wind_name, p_x, p_y);

			p_x += maxSize.width;
			++count;
		}
		std::cout << '\n';
		p_x -= maxSize.width * maxColls;
		p_y += maxSize.height;
	}

	cv::waitKey(0);

}
