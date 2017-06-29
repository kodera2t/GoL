/*
  Game of Life for NameCard (ATMega88AP with 8x8 LED matrix)
  April 2017, kodera2t
  This example code is in the public domain.
 */
#define xsiz  8
#define ysiz  8 
// column mapping
//  byte col[16]={21,20,22,19,23,18,31,17,30,16,29,15,28,14,27,13};
  byte col[8]={14,15,16,17,18,19,4,5};
// line mapping
//  byte lin[16]={4,3,2,1,0,24,25,26,7,6,5,8,9,10,11,12};
  byte lin[8]={6,7,8,9,10,11,12,13};
//  boolean new_pix[18][18]; //new pixels, positive logic
//  boolean current_pix[18][18]; //current pixels, positive logic
  boolean new_pix[11][11]; //new pixels, positive logic
  boolean current_pix[11][11]; //current pixels, positive logic
  byte flag=0;
void setup(){
  int q;
 //   Serial.begin(9600);                
// All of pins (including A/D) are assigned to LED drive
  pinMode(A7, INPUT);
  randomSeed(analogRead(A7));
  for(int i=4;i<20;i++){
  pinMode(i, OUTPUT);
  }
  attachInterrupt(0,reset_randompixel, CHANGE); //push D2 (S2) will reset pixel to random

  
  for(int i=0;i<xsiz+2;i++){ // initialize all pixels are off
    for(int j=0;j<ysiz+2;j++){
      new_pix[i][j]=0;
      current_pix[i][j]=0;
    }    
  }  
  
  reset_randompixel();
  init_pixel();


}

void loop() {
    int n;
    flag++;      
    n=0;
    born_or_dead();
    renewal();  
    while(n<80){
    pixeldisplay();
    n++;
    }
    if(flag==50){ //force reset on 50th generation
    reset_randompixel();
    flag=0;
    }
    if(active_number()==1){
    reset_randompixel();      
    }
}

void pixelmapping(byte x, byte y){ // LED defined by position (x,y) turns on, else off
  init_pixel();
  digitalWrite(lin[y-1],HIGH);
  digitalWrite(col[x-1],HIGH);
  delay(1);
}

void pixeldisplay(){
  int i,j;
  for(i=1;i<xsiz+1;i++){
    for(j=1;j<ysiz+1;j++){
      if(current_pix[i][j]==1){
        pixelmapping(i,j);
      }
      //delay(1);
    }
  }
}

void init_pixel(){ //initialize all LED to off
  for(int i=0;i<xsiz;i++){
  digitalWrite(col[i], LOW);
  digitalWrite(lin[i], LOW);
  }  
}

void renewal(){
   for(int i=1;i<xsiz+1;i++){ 
     for(int j=1;j<ysiz+1;j++){
       current_pix[i][j]=new_pix[i][j];
     }
   }
}

void born_or_dead(){
 int live_num,i,j,k;
 for(i=1;i<xsiz+1;i++){ //checking point is (i,j)
     live_num=0;
   for(j=1;j<ysiz+1;j++){
     live_num=0;
     {
        for(int k=-1;k<2;k++){
          if(current_pix[i-1][j+k]==1){
            live_num++;
          }
       
          if(current_pix[i+1][j+k]==1){
            live_num++;
          } 
       
        }
     
     
     
        if(current_pix[i][j+1]==1){
          live_num++;  
        }
        if(current_pix[i][j-1]==1){
        live_num++;
      }
     
   }

     if(current_pix[i][j]==0){
        if(live_num==3){
              new_pix[i][j]=1;
        }
     }else{
     switch(live_num){
     case 0:
       new_pix[i][j]=0;
       break;
     case 1:  
       new_pix[i][j]=0;
         //     goto hoge;
       break;
     case 2:
       new_pix[i][j]=1;
         //     goto hoge;
       break;
     case 3:
       new_pix[i][j]=1;
        //      goto hoge;
       break;
     case 4:
       new_pix[i][j]=0;
        //      goto hoge;
       break;
     case 5:
       new_pix[i][j]=0;
        //      goto hoge;
       break;
     case 6:
       new_pix[i][j]=0;
        //      goto hoge;
       break;
     case 7:
       new_pix[i][j]=0;
        //      goto hoge;
       break;
     case 8:
       new_pix[i][j]=0;
        //      goto hoge;
       break;
     default:
      break;
     }
     }
   }   
 }
}

void reset_randompixel(){
    for(int i=0;i<xsiz+2;i++){   //initialize pixel 
    for(int j=0;j<ysiz+2;j++){
      current_pix[i][j]=0;
      new_pix[i][j]=0;
    }    
  }
  for(int i=1;i<xsiz+1;i++){   //initialize pixel 
    for(int j=1;j<ysiz+1;j++){
      byte pix=random(2); //random 0 or 1
      current_pix[i][j]=pix;
      new_pix[i][j]=pix;
        //Serial.println(pix);
    }    
  }
}

int active_number(){
  int active_num=0;
   for(int i=1;i<xsiz+1;i++){ 
     for(int j=1;j<ysiz+1;j++){
       if(current_pix[i][j]==1){
         active_num++;
       }
     }
   }
   return active_num;
}

