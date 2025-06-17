#include <opencv2/opencv.hpp>
#include <omp.h>

int main() {
    cv::Mat in = cv::imread("in.jpg", cv::IMREAD_GRAYSCALE);
    if(in.empty()) {
        printf("Error loading image\n");
        return -1;
    }
    
    cv::Mat out = in.clone();
    int kernel[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
    
    double start = omp_get_wtime();
    
    #pragma omp parallel for collapse(2)
    for(int i=1; i<in.rows-1; i++) {
        for(int j=1; j<in.cols-1; j++) {
            int sum = 0;
            for(int di=-1; di<=1; di++) {
                for(int dj=-1; dj<=1; dj++) {
                    sum += in.at<uchar>(i+di,j+dj) * kernel[di+1][dj+1];
                }
            }
            out.at<uchar>(i,j) = sum / 16;
        }
    }
    
    double end = omp_get_wtime();
    printf("Processing time: %f seconds\n", end - start);
    
    cv::imwrite("out_gauss.jpg", out);
    return 0;
}