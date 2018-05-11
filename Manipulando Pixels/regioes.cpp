#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;	
using namespace std;

int main(int argc, char** argv){
  	Mat image;  

  	image = imread("bolhas.png", CV_LOAD_IMAGE_GRAYSCALE); // lendo a image

  	int width = image.cols;
  	int height = image.rows;

  	CvPoint P1, P2;

  	if(!image.data){
  		cout << "image não abriu" << endl;
  		return 1;
  	}

  	cout<<"Tamanho da image: "<<height<<"x"<<width<<endl;
  	cout<<"Coordenadas do ponto 1: ";
  	cin >> P1.x >> P1.y;
    	cout<<"Coordenadas do ponto 2: ";
  	cin >> P2.x >> P2.y;

  	for (int i = P1.x; i <= P2.x; ++i)
  	{
  		for (int j = P1.y;j <= P2.y; ++j)
  		{
  			image.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
  		}
  	}

  	//namedWindow("image", WINDOW_AUTOSIZE); // desnecessário
  	imshow("image", image);
  	waitKey();

    return 0;
}