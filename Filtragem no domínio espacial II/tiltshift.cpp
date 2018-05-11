#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>

#define Max_size_name 51

using namespace cv;
using namespace std; //isso é coisa de gente preguiçosa


int top_slider_max = 100;
int h_slider = 0, v_slider = 0, p_slider = 0;

int width, height; // dimensões da imagem

Mat orige_image, blurry_image, blended;

char TrackbarName[Max_size_name]; // nome das labels
float l1 = 0, l2 = 0; // linhas de mudança

void on_trackbar_blend(int, void*);
void on_trackbar_line(int , void*);
float tiltShift(const int pos);

int main(int argvc, char** argv){
  char name[Max_size_name];
  cout<<"Informe o arquivo.jpg: ";
  cin.getline(name, Max_size_name);

  orige_image = imread(name);

  width = orige_image.rows;
  height = orige_image.cols;
  // blurry_image.copyTo(imageTop);
  float media[] = {0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0};
  Mat mask = Mat(5, 5, CV_32F, media);
  scaleAdd(mask, 1/9.0, Mat::zeros(5,5,CV_32F), mask);
  filter2D(orige_image, blurry_image, orige_image.depth(), mask, Point(2,2), 0); 
  
  // imshow("Higor",blurry_image);

  namedWindow("addweighted", 1);
  
  sprintf( TrackbarName, "Height:\t %d", top_slider_max ); 
  createTrackbar( TrackbarName, "addweighted", &h_slider, top_slider_max, on_trackbar_line );

  sprintf( TrackbarName, "Variability: %d", top_slider_max );
  createTrackbar( TrackbarName, "addweighted", &v_slider, top_slider_max, on_trackbar_line);

  sprintf( TrackbarName, "Position: %d", top_slider_max );
  createTrackbar( TrackbarName, "addweighted", &p_slider, top_slider_max, on_trackbar_line);

  on_trackbar_line(0 , 0 );

  waitKey(0);

  cout<<"Do you want to save the final image: (Y = yes or N = not)\n";
  char op;
  cin>>op;
  if(op == 'Y')
    imwrite("./final_img.jpg", blended);
  return 0;
}

void on_trackbar_line(int , void*){
  // fazer atribuições a l1,l2 e d apartir dos dados coletados por '*_slider'
  float h_focus = ((h_slider/100.0)*width)/2.0;
  float p_real = ((p_slider/100.0)*width);
  l1 = p_real - h_focus;
  l2 = p_real + h_focus;
  on_trackbar_blend(0,0);
}

void on_trackbar_blend(int, void*){
  orige_image.convertTo(orige_image, CV_32F);
  blurry_image.convertTo(blurry_image,CV_32F);
  blurry_image.convertTo(blended,CV_32F);
  
  for (int i = 0; i < width; ++i){
    float pix = tiltShift(i);
    for (int j = 0; j < 3*height; ++j){
      blended.at<float>(i,j) = orige_image.at<float>(i,j)*pix + blurry_image.at<float>(i,j)*(1-pix);
    }
  }

  blended.convertTo(blended,CV_8U);
  imshow("addweighted", blended);
}

float tiltShift(const int pos){
  return 0.5*(tanh((pos-l1)/v_slider) - tanh((pos-l2)/v_slider));
}

