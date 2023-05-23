#include <opencv2/opencv.hpp>



cv::Scalar
RED(0, 0, 255),
GREEN(0, 255, 0),
BLUE(255, 0, 0),
WHITE(255, 255, 255);

cv::Scalar
FRAME(0, 202, 202);



void DrowEllipseRing(cv::Mat&, const cv::Point&, const int&, const int&, const cv::Scalar&);
void DrowRing(cv::Mat&, const cv::Point&, const int&, const int&, const cv::Scalar&);
void DrowText(cv::Mat&, const std::string&, const cv::Point&);
void DrowFrame(cv::Mat&, const int&, const cv::Scalar&);
void DrowAtom(cv::Mat&, const cv::Point&, const int&);



int main(int argc, char** argv)
{
    cv::namedWindow("Output", 1);

    cv::Mat output = cv::Mat::zeros(540, 960, CV_8UC3);

    const cv::Size wind_sz = output.size();
    const cv::Point wind_cent(wind_sz.width / 2, wind_sz.height / 2);


    DrowAtom(output, wind_cent, 120);
    DrowEllipseRing(output, wind_cent, 170, 250, RED);
    DrowRing(output, wind_cent, 170, 150, GREEN);
    DrowFrame(output, 19, FRAME);
    DrowText(output, "Hello, World!", { 50, 50 });


    imshow("Output", output);

    cv::waitKey(0);

    cv::imwrite("output.png", output);

    return 0;
}


void DrowAtom(cv::Mat& img, const cv::Point& center, const int& radius)
{
    if (radius < 0) throw 1;

    cv::circle(img, center, radius / 8, RED, -1);
    cv::Size size(radius, radius / 4);

    cv::RotatedRect r_rect(center, size, 0);

    while (r_rect.angle < 360)
    {
        cv::ellipse(img, r_rect, BLUE);
        r_rect.angle += 30;
    }
}

void DrowRing(cv::Mat& img, const cv::Point& center, const int& r1, const int& r2, const cv::Scalar& color)
{
    cv::circle(img, center, r1, color);
    cv::circle(img, center, r2, color);

    cv::Size sz1(r1, r1);
    cv::Size sz2(r2, r2);

    std::vector<std::vector<cv::Point>> conturs(2);

    cv::ellipse2Poly(center, sz1, 0, 0, 360, 1, conturs[0]);
    cv::ellipse2Poly(center, sz2, 0, 0, 360, 1, conturs[1]);

    cv::drawContours(img, conturs, -1, color, -1);
}

void DrowEllipseRing(cv::Mat& img, const cv::Point& center, const int& r1, const int& r2, const cv::Scalar& color)
{
    cv::Size size(r1 * 2, r2 * 2);
    cv::RotatedRect r_rect(center, size, 0);

    while (r_rect.angle < 360) {
        cv::ellipse(img, r_rect, color);
        r_rect.angle += 15;
    }
}

void DrowFrame(cv::Mat& img, const int& size, const cv::Scalar& color)
{
    int width = img.size().width;
    int height = img.size().height;

    std::vector<std::vector<cv::Point>> cont =
    {
        {{0, 0}, {width, 0}, {width, height}, {0, height}},
        {{size, size}, {width - size, size}, {width - size, height - size}, {size, height - size}}
    };

    cv::fillPoly(img, cont, color);
}

void DrowText(cv::Mat& img, const std::string& text, const cv::Point& pos)
{
    cv::putText(img, text, pos, cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
}