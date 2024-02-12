//This file starts out empty!
//Define the Turtle class here.
#include<cmath>
#include "draw.h"
class Turtle{
  private:
  double direction = 0.0;
  double x = 0.0;
  double y = 0.0;
  double travel = 0.0;
  Color C,c;
  bool signal;
  public:
  void move(double dist); // move the Turtle forward dist steps
  void turn(double deg); // turn the Turtle counterclockwise/left deg degrees
  Turtle(double x0, double y0, double dir0); // construct new Turtle with this state
  void setColor(Color c); // change line color that this Turtle draws from now on
  void off(); // make this Turtle stop drawing lines when it moves
  void on(); // make this Turtle resume drawing lines when it moves
  void show(int milliseconds);
  void ellipse(double cx,double cy,double rx,double ry);
  void circle(double cx,double cy,double r);

};
// Turtle::Turtle(double x0, double y0, double dir0){

//   direction = dir0;
//   x = x0;
//   y = y0;

// }

// void turn(double deg){

//   direction += deg;

// }


// void Turtle::move(double dist)
// {
//   draw::line(x,y,dist*cos(direction*(M_PI/180)),dist*sin(direction*(M_PI/180)));
//   x = dist*cos(direction*(M_PI/180));
//   y = dist*sin(direction*(M_PI/180));
  
// }