#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int countSubBolhas(Mat &img,int pix, int back_color);

int main(int argc, char** argv){
  Mat image;
  int width, height, back_color = 127;
  int nObjects = 0, nSubObjects = 0;

  CvPoint P, P_aux; // vai pegar a informação do pixel anterior
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.rows;
  height=image.cols;

  // tirando as bolhas da lateral da imagem
  for(int i = 0; i < width; ++i)
    for (int j = 0; j < height; ++j)
      if(i==0 || j==0 || i==(width - 1) || j==(height - 1)){
        P.x = i;
        P.y = j;
        floodFill(image,P,0);
      }

  P.x = P.y = 0;
  floodFill(image,P,back_color); // pintando o fundo da imagem de cinza

  for (int i = 0; i < width; ++i)
    for (int j = 0; j < height; ++j)
      if (image.at<uchar>(i,j) == 255) {
        nObjects++;
        P.x = j;
        P.y = i;
        floodFill(image,P,back_color);

        if(countSubBolhas(image,0,back_color) != 0)
           nSubObjects++;
      }
  
  std::cout<<"Quantidade de bolhas: "<<nObjects<<"\nQuantidade de bolhas com buracos: "<<nSubObjects<<std::endl;

  imshow("image", image);
  imwrite("labeling.png", image);
  waitKey();
  return 0;
}

int countSubBolhas(Mat &img,int pix, int back_color){
  int count = 0, aux = img.at<uchar>(0,0);
  CvPoint P;

  for (int i = 0; i < img.rows; ++i)
    for (int j = 0; j < img.cols; ++j){
      if (img.at<uchar>(i,j) == pix && aux == back_color){
        count++;
        P.x = j;
        P.y = i;
        floodFill(img,P,back_color);
      }
      aux = img.at<uchar>(i,j);
    }
  std::cout<<count<<std::endl;
  return count;
}





