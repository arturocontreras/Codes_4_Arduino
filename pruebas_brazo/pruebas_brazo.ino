#include <Servo.h> 
 
Servo base;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
Servo hombro;  
Servo hombroc;  
Servo codo;  
Servo muneca;
Servo gripper;

int ibyte;
int velocidades[6];
int pos1=0,pos2=0,pos1_ant=0,pos2_ant=0,pos=0;
//variables articulares: q1,q2,q3,q4,q5(gripper)
int q1,q2,q2s,q3,q4,q5;
int q1_ant,q2_ant,q2s_ant,q3_ant,q4_ant,q5_ant;
///////////////////////////////////////////

void setup() {
  // initialize both serial ports:
//    Serial.begin(9600);
//    Serial1.begin(9600);
  //pines de servo
    base.attach(1);  // attaches the servo on pin 9 to the servo object 
    hombro.attach(2);
    hombroc.attach(3);
    codo.attach(4);
    muneca.attach(5);
    gripper.attach(6);
}

void loop() {
  analogWrite(9,0);
  analogWrite(10,150);
  analogWrite(12,0);
  analogWrite(11,150);
  delay(5000);
  analogWrite(9,0);
 analogWrite(10,200);
 analogWrite(12,200);
 analogWrite(11,0);
  delay(2500);
  analogWrite(9,0);
  analogWrite(10,150);
  analogWrite(12,0);
  analogWrite(11,150);
    delay(2500);

  analogWrite(9,150);
  analogWrite(10,0);
  analogWrite(12,0);
  analogWrite(11,100);
  delay(5000);  

q1=90;
q2=90;
q2s=180-q2;
q3=50;
q4=60;
q5=80;

//   base.write(q1);
//   hombro.write(q2);
//   hombroc.write(q2s);
//   codo.write(q3);
//   muneca.write(q4);
//   gripper.write(q5);
//   if(q1>=q1_ant){
//                for(pos = q1_ant; pos < q1; pos += 1)  // goes from 0 degrees to 180 degrees 
//                {                                  // in steps of 1 degree 
//                   base.write(pos);              // tell servo to go to position in variable 'pos' 
//                  delay(30);                       // waits 15ms for the servo to reach the position 
//                } 
//     }
//     else{
//                for(pos = q1_ant; pos > q1; pos -= 1)  // goes from 0 degrees to 180 degrees 
//                {                                  // in steps of 1 degree 
//                  base.write(pos);              // tell servo to go to position in variable 'pos' 
//                  delay(30);                       // waits 15ms for the servo to reach the position 
//                } 
//               
//     }
//  
// 
//         if(q2>=q2_ant){
//                for(pos = q2_ant; pos < q2; pos += 1)  // goes from 0 degrees to 180 degrees 
//                {                                  // in steps of 1 degree 
//                   muneca.write(pos);              // tell servo to go to position in variable 'pos' 
//                   codo.write(pos);
//                  delay(30);                       // waits 15ms for the servo to reach the position 
//                } 
//     }
//     else{
//                for(pos = q2_ant; pos > q2; pos -= 1)  // goes from 0 degrees to 180 degrees 
//                {                                  // in steps of 1 degree 
//                    muneca.write(pos);              // tell servo to go to position in variable 'pos' 
//                   codo.write(pos);             // tell servo to go to position in variable 'pos' 
//                  delay(30);                       // waits 15ms for the servo to reach the position 
//                } 
//               
//     }
//   delay(2000);
//  q1_ant=q1;
//  q2_ant=q2;
//  q3_ant=q3;
//  q4_ant=q4;
//  q5_ant=q5;
//  
//q1=150;
//q2=90;
//q2s=180-q2;
//q3=90;
//q4=100;
//q5=20;
////   base.write(q1);
////   hombro.write(q2);
////   hombroc.write(q2s);
////   codo.write(q3);
////   muneca.write(q4);
////   gripper.write(q5);
////q5=80;   
////   delay(2000);
////   gripper.write(q5); 
//delay(2000);
////   delay(2000); 
////   myservo1.write(60);
////   myservo2.write(120);
////   delay(2000); 
////     
//     if(q1>=q1_ant){
//                for(pos = q1_ant; pos < q1; pos += 1)  // goes from 0 degrees to 180 degrees 
//                {                                  // in steps of 1 degree 
//                   base.write(pos);              // tell servo to go to position in variable 'pos' 
//                  delay(30);                       // waits 15ms for the servo to reach the position 
//                } 
//     }
//     else{
//                for(pos = q1_ant; pos > q1; pos -= 1)  // goes from 0 degrees to 180 degrees 
//                {                                  // in steps of 1 degree 
//                  base.write(pos);              // tell servo to go to position in variable 'pos' 
//                  delay(30);                       // waits 15ms for the servo to reach the position 
//                } 
//               
//     }
//  
// 
//         if(q2>=q2_ant){
//                for(pos = q2_ant; pos < q2; pos += 1)  // goes from 0 degrees to 180 degrees 
//                {                                  // in steps of 1 degree 
//                    muneca.write(pos);              // tell servo to go to position in variable 'pos' 
//                   codo.write(pos);
//                  delay(30);                       // waits 15ms for the servo to reach the position 
//                } 
//     }
//     else{
//                for(pos = q2_ant; pos > q2; pos -= 1)  // goes from 0 degrees to 180 degrees 
//                {                                  // in steps of 1 degree 
//                  muneca.write(pos);              // tell servo to go to position in variable 'pos' 
//                   codo.write(pos);             // tell servo to go to position in variable 'pos' 
//                  delay(30);                       // waits 15ms for the servo to reach the position 
//                } 
//               
//     }
////              if(q2>=q2_ant){
////                for(pos = q2_ant; pos < q2; pos += 1)  // goes from 0 degrees to 180 degrees 
////                {                                  // in steps of 1 degree 
////                   myservo2.write(pos);              // tell servo to go to position in variable 'pos' 
////                  delay(30);                       // waits 15ms for the servo to reach the position 
////                } 
////     }
//////     else{
//////                for(pos = q2_ant; pos > q2; pos -= 1)  // goes from 0 degrees to 180 degrees 
//////                {                                  // in steps of 1 degree 
//////                  myservo2.write(pos);              // tell servo to go to position in variable 'pos' 
//////                  delay(30);                       // waits 15ms for the servo to reach the position 
//////                } 
//////               
//////     }
////              if(q2>=q2_ant){
////                for(pos = q2_ant; pos < q2; pos += 1)  // goes from 0 degrees to 180 degrees 
////                {                                  // in steps of 1 degree 
////                   myservo2.write(pos);              // tell servo to go to position in variable 'pos' 
////                  delay(30);                       // waits 15ms for the servo to reach the position 
////                } 
////     }
////     else{
////                for(pos = q2_ant; pos > q2; pos -= 1)  // goes from 0 degrees to 180 degrees 
////                {                                  // in steps of 1 degree 
////                  myservo2.write(pos);              // tell servo to go to position in variable 'pos' 
////                  delay(30);                       // waits 15ms for the servo to reach the position 
////                } 
////               
////     }
////              if(q2>=q2_ant){
////                for(pos = q2_ant; pos < q2; pos += 1)  // goes from 0 degrees to 180 degrees 
////                {                                  // in steps of 1 degree 
////                   myservo2.write(pos);              // tell servo to go to position in variable 'pos' 
////                  delay(30);                       // waits 15ms for the servo to reach the position 
////                } 
////     }
////     else{
////                for(pos = q2_ant; pos > q2; pos -= 1)  // goes from 0 degrees to 180 degrees 
////                {                                  // in steps of 1 degree 
////                  myservo2.write(pos);              // tell servo to go to position in variable 'pos' 
////                  delay(30);                       // waits 15ms for the servo to reach the position 
////                } 
////               
////     }
//        
//  q1_ant=q1;
//  q2_ant=q2;
//  q3_ant=q3;
//  q4_ant=q4;
//  q5_ant=q5;
////  
////  delay(1000);

//}
}
