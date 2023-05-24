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
	maxSize(imgSize),
	curr_col(0)
{
	const auto& window = getUsersMetrics();

	if (maxSize.width > window.width || maxSize.height > window.height || maxColls <= 0)
		throw 1;

	maxColls = (maxColls * maxSize.width > window.width) ? (window.width / maxSize.width) : maxColls;
	
	maxRows = window.height / maxSize.height;
}

Cards::Cards(Cards&& copy) noexcept :
	imgs(std::move(copy.imgs)),
	maxColls(copy.maxColls),
	curr_col(copy.curr_col),
	maxSize(copy.maxSize),
	maxRows(copy.maxRows)	
{
}



void Cards::operator=(const Cards& copy) noexcept
{
	imgs = copy.imgs;
	maxColls = copy.maxColls;
	curr_col = copy.curr_col;
	maxRows = copy.maxRows;
	maxSize = copy.maxSize;
}

void Cards::operator=(Cards&& copy) noexcept
{
	imgs = std::move(copy.imgs);
	maxColls = copy.maxColls;
	curr_col = copy.curr_col;
	maxRows = copy.maxRows;
	maxSize = copy.maxSize;
}



Cards& Cards::operator<<(cv::Mat& img)
{
	cv::resize(img, img, maxSize);

	int curr_row = imgs.size() - 1;
	
	if (curr_row == maxRows) {
		return *this;
	}	
	else if (curr_row < 0) {
		imgs.push_back(std::vector<cv::Mat>());
		curr_row = 0;
	}
	else if (curr_col == maxColls) {
		imgs.push_back(std::vector<cv::Mat>());
		curr_col = 0;
		++curr_row;
	}
	if (curr_row == maxRows) {
		return *this;
	}

	imgs[curr_row].push_back(img);
	++curr_col;

	return *this;
}

Cards& Cards::operator<<(cv::Mat&& img)
{
	cv::resize(img, img, maxSize);

	int curr_row = imgs.size() - 1;
	
	if (curr_row < 0) {
		imgs.push_back(std::vector<cv::Mat>());
		curr_row = 0;
	}
	else if (curr_col == maxColls) {
		imgs.push_back(std::vector<cv::Mat>());
		curr_col = 0;
		++curr_row;
	}
	if (curr_row == maxRows) {
		return *this;
	}
	imgs[curr_row].push_back(std::move(img));
	++curr_col;

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
		if (vec.size() < maxColls) 
			p_x = (window.width - vec.size() * maxSize.width) / 2;
		
		for (const auto& i : vec)
		{
			std::string wind_name = "Window " + std::to_string(count);

			cv::imshow(wind_name, i);
			cv::moveWindow(wind_name, p_x, p_y);

			p_x += maxSize.width;
			++count;
		}

		p_x -= maxSize.width * maxColls;
		p_y += maxSize.height;
	}

	cv::waitKey(0);
}
