/*
  Game of Life by Arduino (ATMega1284P with 16x16 LED matrix)
  April 2017, kodera2t
  This example code is in the public domain.
 */
 
// column mapping
  byte col[16]={21,20,22,19,23,18,31,17,30,16,29,15,28,14,27,13};
// line mapping
  byte lin[16]={4,3,2,1,0,24,25,26,7,6,5,8,9,10,11,12};
  
  boolean new_pix[18][18]; //new pixels, positive logic
  boolean current_pix[18][18]; //current pixels, positive logic
  
void setup() {                
// All of pins (including A/D) are assigned to LED drive
  randomSeed(analogRead(0));
  for(int i=0;i<32;i++){
  pinMode(i, OUTPUT);
  }
  
  for(int i=0;i<18;i++){ // initialize all pixels are off
    for(int j=0;j<18;j++){
      new_pix[i][j]=0;
      current_pix[i][j]=0;
    }    
  }  
  
  reset_randompixel();
  init_pixel();
}

void loop() {
  byte n=0;
    while(n<50){
    pixeldisplay();
    n++;
    }
    born_or_dead();
    renewal();
  if(active_number()==0){
    reset_randompixel();
  }
}

void pixelmapping(byte x, byte y){ // LED defined by position (x,y) turns on, else off
  init_pixel();
  digitalWrite(lin[x-1],HIGH);
  digitalWrite(col[y-1],LOW);
}

void pixeldisplay(){
  byte i,j;
  for(i=1;i<17;i++){
    for(j=1;j<17;j++){
      if(current_pix[i][j]==1){
        pixelmapping(i,j);
      }
    }
  }
}

void init_pixel(){ //initialize all LED to off
  for(int i=0;i<16;i++){
  digitalWrite(lin[i], LOW);
  digitalWrite(col[i], HIGH);
  }  
}

void renewal(){
   for(int i=1;i<17;i++){ 
     for(int j=1;j<17;j++){
       current_pix[i][j]=new_pix[i][j];
     }
   }
}

void born_or_dead(){
 int live_num;
 for(int i=1;i<17;i++){ //checking point is (i,j)
   for(int j=1;j<17;j++){
     live_num=0;
     {
     for(int k=-1;k<2;k++){
       if(current_pix[i-1][j-k]==1){
         live_num++;
       }
       if(current_pix[i+1][j-k]==1){
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
     switch(live_num){
     case 0:
       new_pix[i][j]=0;
       break;
     case 1:  
       new_pix[i][j]=0;
       break;
     case 2:
       new_pix[i][j]=1;
       break;
     case 3:
       new_pix[i][j]=1;
       break;
     default:
       new_pix[i][j]=0;
     }
   }   
 }
}

void reset_randompixel(){
  for(int i=1;i<17;i++){   //initial pixel 
    for(int j=1;j<17;j++){
      byte pix=random(2);
      current_pix[i][j]=pix;
    }    
  }
}

int active_number(){
  int active_num=0;
   for(int i=1;i<17;i++){ 
     for(int j=1;j<17;j++){
       if(current_pix[i][j]==1){
         active_num++;
       }
     }
   }
   return active_num;
}

