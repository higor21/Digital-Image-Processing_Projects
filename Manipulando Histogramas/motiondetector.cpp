#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector> 

using namespace cv;
using namespace std;

void imHist(const Mat imageGray, vector<int>& histogram);
bool calcDifference(const vector<int> histogram, const vector<int> histogramBefore);

int main(int argc, char** argv){
  Mat imageRGB, imageGray, imageAnt;
  Mat histAcum();
  VideoCapture cap;
  
  vector<int> histogram (256);
  vector<int> histogramBefore (256);
  int aux = 1;

  cap.open(0);
  
  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
  }
  
  while(1){
    cap >> imageRGB;
    cvtColor(imageRGB,imageGray,CV_RGB2GRAY);

    histogram = vector<int>(256,0);
    
    imHist(imageGray,histogram);

    if (calcDifference(histogram,histogramBefore) && aux == 0){
      break;
    }

    histogramBefore = histogram;
    
    aux = 0;
  }
  cout<<"\n\nALARME ATIVADO !!\n\n";
  return 0;
}

void imHist(const Mat imageGray, vector<int>& histogram){
  for (int i = 0; i < imageGray.cols; ++i)
    for (int j = 0; j < imageGray.rows; ++j)
       histogram[(int)imageGray.at<uchar>(i,j)]++;
}

bool calcDifference(const vector<int> histogram, const vector<int> histogramBefore){
  for (int i = 0, sum = 0; i < (signed)histogram.size(); ++i){
    sum += abs(histogram[i] - histogramBefore[i]);
    if (sum > 100384){
      return true;
    }
  }
  return false;
}