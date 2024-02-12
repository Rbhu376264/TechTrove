//This file also starts out empty.
//Implement the Turtle class here.

#include "turtle.h"
// #include "draw.h"




Turtle::Turtle(double x0, double y0, double dir0){

  direction = dir0;
  x = x0;
  y = y0;
  C = draw::BLACK;
  draw::setcolor(C);
  signal = true;

  

}

void Turtle::turn(double deg){

  direction += deg;

}


void Turtle::move(double dist)
{
  travel = dist;
  if(signal)
  {
    draw::setcolor(C);
    draw::line(x,y,x+travel*cos(direction*(M_PI/180.0)),y+travel*sin(direction*(M_PI/180.0)));
  }
  
  x += travel*cos(direction*(M_PI/180.0));
  y += travel*sin(direction*(M_PI/180.0));

  
  // That looks good! Alright good luck.
  // also better code convention is to use names like X1,Y1, and Y1,Y2
  // Basically you are recomputing X and Y twice in the draw::line and again in x= and y=, but it shouldn't matter
}

void Turtle::setColor(Color c)
{

  // signal = true;
  // draw::setcolor(c);
  C = c;
  // cout<<"Color change"<<c.red<<" "<<c.green<<" "<<c.blue<<endl;

  
  
}

void Turtle::off()
{
  signal = false;
}

void Turtle::on()
{

  signal = true;
  

}

void Turtle::show(int milliseconds)
{
  draw::show(milliseconds);
}
void Turtle::ellipse(double cx,double cy,double rx,double ry)
{
  draw::ellipse(cx,cy,rx,ry);
}

void Turtle::circle(double cx,double cy,double r)
{
  ellipse(cx,cy,r,r);
} 