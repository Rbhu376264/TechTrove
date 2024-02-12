#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width) {

  for(int i = 0; i<=height; i++)
  {
    if(i+top >= 0 && i+top<=255 && left>= 0 && left<=255)
    {
      image[i+top][left] = 0;
    }

    if(i+top>=0 && i+top<=255 && width+left>=0 && width+left<=255)
    {
      image[i+top][width+left] = 0;
    }
  }

  for(int i = 0; i<=width; i++)
  {
    if(i+left>=0 && i+left<=255 && top>=0 && top<= 255)
    {
      image[top][i+left] = 0;
    }

    if(i+left>=0 && i+left<=255 && top+height>=0 && top+height<=255)
    {
      image[top+height][i+left] = 0;
    }
  }

}

// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width) {
  double x = 0;
  double y = 0;
  for(double i = 0; i<=2*M_PI; i += 0.01)
  {

    x = (width/2)*cos(i) + cx;

    y = (height/2)*sin(i) + cy;
    
    if(x>=0 && x<= 255 && y>=0 && y<=255)
    {
      image[(int)y][(int)x] = 0;
    }


  }

}


int main() {
   // initialize the image to all white pixels
   for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
         image[i][j] = 255;
      }
   }
   
   // Main program loop here
    int top, left, height, width, cy, cx, option;

    cout<<"To draw a rectangle, enter: 0 top left height width"<<endl;
    cout<<"To draw an ellipse, enter: 1 cy cx height width"<<endl;
    cout<<"To save your drawing as ""output.bmp"" and quit, enter: 2"<<endl;
    cin>>option;

    while(option != 2)
    {
      if(option==0)
      {
        cin>>top>>left>>height>>width;
        draw_rectangle(top,left,height,width);
      }

      if(option==1)
      {
        cin>>cy>>cx>>height>>width;
        draw_ellipse(cy,cx,height,width);
      }
      cout<<"To draw a rectangle, enter: 0 top left height width"<<endl;
      cout<<"To draw an ellipse, enter: 1 cy cx height width"<<endl;
      cout<<"To save your drawing as ""output.bmp"" and quit, enter: 2"<<endl;
      cin>>option;

    }

    
   
   
   // Write the resulting image to the .bmp file
   writeGSBMP("output.bmp", image);
   
   return 0;
}
