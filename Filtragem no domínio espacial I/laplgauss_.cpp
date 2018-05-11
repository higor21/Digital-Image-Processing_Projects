#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argvc, char** argv){
  VideoCapture video;
  float gauss[] = {1,2,1, 2,4,2, 1,2,1};
  float laplacian[]={0,-1,0, -1,4,-1, 0,-1,0};

  Mat cap, frame, frame32f, frameFiltered;
  Mat mask_gauss(3,3,CV_32F,gauss), mask_lapl(3,3,CV_32F,laplacian);
  Mat result;
  
  video.open(0); 
  if(!video.isOpened()) 
    return -1;

  namedWindow("filtroespacial",1);

  cout<<"Laplaciano do gaussiano!\n";
  while(true){
    video >> cap; 
    cvtColor(cap, frame, CV_BGR2GRAY);

    imshow("original", frame); 	
    
    frame.convertTo(frame32f, CV_32F);
    filter2D(frame32f, frameFiltered, frame32f.depth(), mask_gauss, Point(1,1), 0); 
    
    frame32f = Mat(frameFiltered);
    filter2D(frame32f, frameFiltered, frame32f.depth(), mask_lapl, Point(1,1), 0); 

    frameFiltered.convertTo(result, CV_8U);
    
    imshow("filtroespacial", result);

    if(waitKey(1) != -1)
      return 0;
  }
}
