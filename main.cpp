# include <opencv2/core.hpp>
# include <opencv2/imgcodecs.hpp>
# include <opencv2/highgui.hpp>
# include <opencv2/imgproc/imgproc.hpp>
# include <iostream>
# include <opencv2/core/matx.hpp>

int main(int, char**) {
    /*
        Alternating horizontal stripes (red, green, blue, red, green ...)
        Each stripe is six pixels thick
        Offset by three pixels at the top
        Image size is 640 x 480
    */

    cv::Mat image(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));
    
    int rows = image.rows;
    int cols = image.cols;
    int thickness = 6;
    int offset = 3;

    for (int row = offset; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            /*
                Determine the color of the horizontal stripe
                Dependent only on row
                If row%3 = 0 -> Red
                If row%3 = 1 -> Green
                If row%3 = 2 -> Blue
            */

            int row_num = (int)(row-offset)/6;
            if (row_num%3==0) {
                image.at<cv::Vec3b>(row, col) = {0, 0, 255}; // Red
            } else if(row_num%3==1) {
                image.at<cv::Vec3b>(row, col) = {0, 255, 0}; // Green
            } else if(row_num%3==2) {
                image.at<cv::Vec3b>(row, col) = {255, 0, 0}; // Blue
            }
        }
    }

    cv::imwrite("stripes1.png", image);

    /*
        Twelve circles drawn over top of the stripes
        Coordinates of centers given in xy.txt file on Schoology
        Solid color hex C8 B0 A5 => RGB(165,200,176)
        Radius is fourty
    */

   int radius = 40;
   int centers[12][2] = {
        {280, 75},
        {560, 200},
        {160, 300},
        {380, 340},
        {150, 75},
        {360, 180},
        {75, 400},
        {220, 420},
        {500, 60},
        {75, 200},
        {280, 280},
        {520, 380}
   };

    for (int circle_num = 0; circle_num < 12; circle_num++) {
        // draw the circle
        cv::circle(image, cv::Point(centers[circle_num][0], centers[circle_num][1]), radius, cv::Scalar(176,200,165), -1);
    }

    cv::imwrite("stripes2.png", image);


    for (int row = offset; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            
           int row_num = (int)(row-offset)/6;
           //std::cout << row_num << std::endl;
           if (row_num%3==0 && row_num <= rows/18) {
                //std::cout << "red" << std::endl;
                image.at<cv::Vec3b>(row, col) = {0, 0, 255}; // Red
           } else if (row_num%3==1 && (rows/12 >= row_num) && (row_num >= rows/18)) {
                //std::cout << "blue" << std::endl;
                image.at<cv::Vec3b>(row, col) = {0, 255, 0}; // Red
           } else if (row_num%3==2 && (rows/12 < row_num)) {
                //std::cout << "green" << std::endl;
                image.at<cv::Vec3b>(row, col) = {255, 0, 0}; // Red
           }
        }
    }
    
    cv::imwrite("stripes3.png", image);

    return -1;
}