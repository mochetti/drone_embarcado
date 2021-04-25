#include "funcoes.h"

void startCamera() {
  pixy.init();
  pixy.changeProg("line");
}

// Pega o ângulo da linha
void camera() {
  // int8_t i;
  // char buf[128];
  pixy.line.getMainFeatures();

  ang = 0;

  if (pixy.line.numVectors) {
    
    int x0 = pixy.line.vectors[0].m_x0;
    int y0 = pixy.line.vectors[0].m_y0;
    int x1 = pixy.line.vectors[0].m_x1;
    int y1 = pixy.line.vectors[0].m_y1;
    ang = atan2(y1-y0, x1-x0);

    
    
    }
 
//  if (pixy.line.numIntersections)
//    pixy.line.intersections->print();
}

void luzCamera() {
  luz = !luz;
  if(luz) pixy.setLamp(1, 1);
  else pixy.setLamp(0, 0);
}
