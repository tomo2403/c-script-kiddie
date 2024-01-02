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
  //DmxSimple.write(20,255);
  DmxSimple.write(13,0); 
  DmxSimple.write(9,255);
  delay(5000);
  DmxSimple.write(9,0);
  //DmxSimple.write(11,128);
  //DmxSimple.write(14,239);
  //DmxSimple.write(15,255);
  //DmxSimple.write(16,255);  
  //DmxSimple.write(19,120);  
}
