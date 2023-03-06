#pragma once
#include "preloader_activity.h"


PreloaderActivity::PreloaderActivity(Adafruit_NeoMatrix *pMatrix){
  this->pMatrix = pMatrix;
}

void PreloaderActivity::show(){
  int biglove[8][8] =     //the big "heart"   
  {  
    0,0,0,0,0,0,0,0,  
    0,1,1,0,0,1,1,0,  
    1,1,1,1,1,1,1,1,  
    1,1,1,1,1,1,1,1,  
    1,1,1,1,1,1,1,1,  
    0,1,1,1,1,1,1,0,  
    0,0,1,1,1,1,0,0,  
    0,0,0,1,1,0,0,0,  
  };  
 int smalllove[8][8] = //the small “heart”
  {
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,1,0,0,1,0,0,
    0,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,0,
    0,0,1,1,1,1,0,0,
    0,0,0,1,1,0,0,0,
    0,0,0,0,0,0,0,0,
  };

 pMatrix->fillScreen(0);
	for (unsigned row = 0; row < 8; ++row) {
		for (unsigned col = 0; col < 8; ++col) {
      if(biglove[row][col]){
        pMatrix->drawPixel(col, row, pMatrix->Color(255,0,20));
        }
      }
		}
	
  pMatrix->show();
  delay(1000);
   pMatrix->fillScreen(0);
	for (unsigned row = 0; row < 8; ++row) {
		for (unsigned col = 0; col < 8; ++col) {
      if(smalllove[row][col]){
        pMatrix->drawPixel(col, row, pMatrix->Color(255,0,20));
        }
      }
		}
	
  
    int head[8][8] =     //the big "heart"   
  {  
    0,0,1,0,0,0,0,0,  
    0,1,1,1,0,0,0,0,  
    0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0,   
  };
      int body[8][8] =     //the big "heart"   
  {  
    0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0,  
    1,1,1,1,1,0,0,0,  
    1,1,1,0,1,1,1,0,  
    1,1,1,1,0,0,1,1,  
    1,1,1,1,1,1,0,1,  
    0,1,1,1,1,1,1,1,  
    0,0,1,1,1,1,1,0,   
  };
       int glosy[8][8] =   {  
    0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0,  
    0,0,0,1,0,0,0,0,  
    0,0,0,0,1,1,0,0,  
    0,0,0,0,0,0,1,0,  
    0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0,   
  }; 
 pMatrix->fillScreen(0);
  for (unsigned row = 0; row < 8; ++row) {
		for (unsigned col = 0; col < 8; ++col) {
      if(head[row][col]){
        pMatrix->drawPixel(col, row, pMatrix->Color(45,89,72));
        }
      }
	}
    for (unsigned row = 0; row < 8; ++row) {
		for (unsigned col = 0; col < 8; ++col) {
      if(body[row][col]){
        pMatrix->drawPixel(col, row, pMatrix->Color(38,42,69));
        }
      }
	}
    for (unsigned row = 0; row < 8; ++row) {
		for (unsigned col = 0; col < 8; ++col) {
      if(glosy[row][col]){
        pMatrix->drawPixel(col, row, pMatrix->Color(112,52,104));
        }
      }
	}
 pMatrix->show();
  delay(2000);
}

  void PreloaderActivity::begin()
{
  
}

void PreloaderActivity::stop()
{
}