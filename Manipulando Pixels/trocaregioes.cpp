#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;	
using namespace std;

int main(int argc, char** argv){
  	Mat image;  

    image = imread("bolhas.png", CV_LOAD_IMAGE_GRAYSCALE); // lendo a image
    
    if(!image.data)
      cout<<"Imagem não abriu\n";    

    Mat imaAux = Mat(image.rows , image.cols , (int) CV_8UC1);

    int half_rows = image.rows/2;
    int half_cols = image.cols/2;

    for (int i = 0; i < image.rows; ++i)
    {
      for (int j = 0;j < image.cols; ++j)
      { 
        if(i<half_rows && j<half_cols)
          imaAux.at<uchar>(i + half_rows,j + half_cols) = image.at<uchar>(i,j);
        if(i<half_rows && j>=half_cols)
          imaAux.at<uchar>(i+half_rows,j - half_cols) = image.at<uchar>(i,j);
        if(i>=half_rows && j>=half_cols)
          imaAux.at<uchar>(i - half_rows,j - half_cols) = image.at<uchar>(i,j);
        if(i>=half_rows && j<half_cols)
          imaAux.at<uchar>(i - half_rows, j + half_cols) = image.at<uchar>(i,j);
      }
    }

    image = imaAux;

    imshow("image", image);
    waitKey();
    return 0;
} 