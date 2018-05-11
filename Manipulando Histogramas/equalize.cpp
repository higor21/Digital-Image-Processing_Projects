#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector> 

using namespace cv;
using namespace std;

void equalizedImg(Mat &histOut, const vector<int> vet);
void imHist(const Mat imageGray, vector<int>& histogram);
void calcProbHist(const vector<int> histogram, vector<float>& probHist, const int amountPix);
void calcProbCumHist(const vector<float> probHist, vector<float>& probHistCum);
void calcEqualizedHist(const vector<float> probHistCum, vector<int>& equalizedHist, const float maxIntensity);

int main(int argc, char** argv){
  Mat imageRGB, imageGray, imageAux;
  Mat histAcum();
  VideoCapture cap;
  
  vector<int> histogram (256, 0);
  float maxIntensity = 255.0;

  vector<float> probHist (256);
  vector<float> probHistCum (256);

  vector<int> equalizedHist(256);

  cap.open(0);
  
  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
  }
  

  int width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  int amountPix = width*height;

  while(1){

    cap >> imageRGB;
    
    cvtColor(imageRGB,imageGray,CV_RGB2GRAY);

    imHist(imageGray,histogram);
    calcProbHist(histogram,probHist,amountPix);
    calcProbCumHist(probHist,probHistCum);
    calcEqualizedHist(probHistCum,equalizedHist,maxIntensity);

    imageAux = imageGray.clone();

    equalizedImg(imageAux,equalizedHist);
    
    imshow("equalized_image", imageAux);
    imshow("original_image", imageGray);

    if(waitKey(30) >= 0)
      break;
  }
  return 0;
}

void imHist(const Mat imageGray, vector<int>& histogram){
  for (int i = 0; i < imageGray.cols; ++i)
    for (int j = 0; j < imageGray.rows; ++j)
       histogram[(int)imageGray.at<uchar>(i,j)]++;
}

void calcProbHist(const vector<int> histogram, vector<float>& probHist, const int amountPix){
  for (int i = 0; i < histogram.size(); ++i){
    probHist[i] = histogram[i]/((float)amountPix);
  }
}

void calcProbCumHist(const vector<float> probHist, vector<float>& probHistCum){
  probHistCum[0] = probHist[0];
  for (int i = 1; i < probHist.size(); ++i){
    probHistCum[i] = probHistCum[i-1] + probHist[i];
  }
}

void calcEqualizedHist(const vector<float> probHistCum, vector<int>& equalizedHist, const float maxIntensity){
  for (int i = 0; i < probHistCum.size(); ++i){
    equalizedHist[i] = cvRound(probHistCum[i]*maxIntensity);
  }
}

void equalizedImg(Mat &histOut, const vector<int> vet){
  for (int y = 0; y < histOut.cols; ++y){
    for (int x = 0; x < histOut.rows; ++x){
      histOut.at<uchar>(x,y) = vet[(int)histOut.at<uchar>(x,y)];
    }
  }
}