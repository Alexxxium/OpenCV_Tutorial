#pragma once
#include <vector>
#include <opencv2/opencv.hpp>


class Cards
{
private:

	int maxColls, maxRows;
	cv::Size maxSize;
	std::vector<std::vector<cv::Mat>> imgs;


public:

	explicit Cards(const cv::Size& sz = { 500, 350 }, const int& col = 3);

	Cards(const Cards&) = default;
	Cards(Cards&&) noexcept;

	void operator=(Cards&&) noexcept;
	void operator=(const Cards&) noexcept;

	~Cards() = default;

	Cards& operator<<(cv::Mat&);

	const size_t& maxLenght() const noexcept { return size_t(maxColls) * maxRows; };

	void show() noexcept;
};