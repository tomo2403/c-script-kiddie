
#include "DmxSimple.h"

enum action {huhn, world};

void setup() {
  DmxSimple.usePin(3);
  DmxSimple.maxChannel(44);
}

void loop() {
  
  //DmxSimple.write(1,255);
  //DmxSimple.write(2,255);  
 

  DmxSimple.write(9,255);
  DmxSimple.write(11,255);  
}
