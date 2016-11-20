#include <parpadeo.h>

parpadeo flash1;
int dutty=0;

void setup(){}
void loop(){
for(int i=0;i<10;i++){
flash1.parpadear(13,1000,100);
dutty=map(i,9,0,0,200);
flash1.state(12,dutty);
}
delay(1000);
for(int i=0;i<10;i++){
flash1.parpadear(13,100,100);
dutty=map(i,0,9,0,200);
flash1.state(12,dutty);
}
delay(1000);
}
