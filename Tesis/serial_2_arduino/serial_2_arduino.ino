  char val,ibyte;

  int data[17];
  

  
  void setup(){
    
    Serial2.begin(9600);
  }
  
  void loop(){
    
    if(Serial2.available()>0){
       val=Serial2.read();
       if(val=='x'){
         while(Serial2.available()==0){};
         int i=0;
         for(i=0;i<17;i=i+1){
           data[i]=Serial2.read();
           while(Serial2.available()==0 && (char)data[i]!='y'){
           };
         } 
       } 
       
     for(int j=0; j< 17; j++){
       Serial2.print(data[j]);
       Serial2.print("  ");
     }
     
    }

    
  }
  

