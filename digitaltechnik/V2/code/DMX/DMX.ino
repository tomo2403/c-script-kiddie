#include "DmxSimple.h"


void setup() {
  DmxSimple.usePin(3);
  DmxSimple.maxChannel(44);
}

void loop() {
  
  //DmxSimple.write(1,255);
  //DmxSimple.write(2,255);  
 

  //DmxSimple.write(9,255);
  //DmxSimple.write(15,0);
  //DmxSimple.write(16,0);
  //DmxSimple.write(17,0);
  //DmxSimple.write(17,0);
  DmxSimple.write(21,128);  
}
