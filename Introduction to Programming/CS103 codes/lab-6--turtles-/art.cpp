#include "turtle.h"
#include "draw.h"

int main()
{
  draw::setpenwidth(1000); 
  draw::setrange(-700, 700);
  Turtle top(0,20,80);
  Turtle bottom(0,-20,265);
  Turtle right(20, 0, 340);
  Turtle left(-20,0,100);
  Turtle center (10,10,10);
  top.setColor(draw::TEAL);
  bottom.setColor(draw::MAROON);
  right.setColor(draw::OLIVE);
  left.setColor(draw::MINT);
  center.setColor(draw::ROSE);
  center.circle(1.0,1.0,3.0);
  center.show(110);
  top.ellipse(5.0,10.0,5.0,5.0);
  top.show(200);
  bottom.ellipse(5.0,-36.0,-25.0,-25.0);
  bottom.show(120);
  right.ellipse(6.0,20.0,50.0,25.0);
  right.show(210);
  left.ellipse(3.0,10.0,100.0,50.0);
  left.show(250);

  return 0;
}