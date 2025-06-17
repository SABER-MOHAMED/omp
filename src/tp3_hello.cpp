#include <opencv2/opencv.hpp>
#include <omp.h>

int main() {
    cv::Mat img = cv::imread("../docs/images/in.jpg");
    if(img.empty()) {
        printf("Error loading image\n");
        return -1;
    }
    
    cv::Mat gray(img.rows, img.cols, CV_8UC1);
    
    double start = omp_get_wtime();
    
    #pragma omp parallel for collapse(2)
    for(int i=0; i<img.rows; i++) {
        for(int j=0; j<img.cols; j++) {
            auto &c = img.at<cv::Vec3b>(i,j);
            gray.at<uchar>(i,j) = (c[0] + c[1] + c[2]) / 3;
        }
    }
    
    double end = omp_get_wtime();
    printf("Processing time: %f seconds\n", end - start);
    
    cv::imwrite("out_gray.jpg", gray);
    return 0;
}