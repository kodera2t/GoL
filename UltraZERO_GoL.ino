 /*
  Game of Life for ULTRA Zero
  original setting is 3-4 game (original game of life is 2-3)
  Nov. 2016, kodera2t
  This example code is in the public domain.
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 7
Adafruit_SSD1306 display(OLED_RESET);
  
  boolean new_pix[64][32]; //new pixels
  boolean current_pix[64][32]; //current pixels
  int counter=0;
  
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C                
  randomSeed(analogRead(0));
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(32,32);
  display.clearDisplay();
  display.println("GAME");
  display.setCursor(32,48); 
  display.println("of LIFE"); 
  display.display();
  delay(2000);
  display.clearDisplay();  
  
  for(int i=0;i<64;i++){ // initialize all pixels are off
    for(int j=0;j<32;j++){
      new_pix[i][j]=0;
      current_pix[i][j]=0;
    }    
  }  
  
  reset_randompixel();
  draw_pixel();
  display.display();  
}

void loop() {
    counter++;
    born_or_dead();
    delete_pixel();
    renewal();
    draw_pixel();
    if(counter==500){ //force reset on 300th generation
    reset_randompixel();
    counter=0;
    }
}

void draw_pixel(){
  int xpos,ypos;
  for(int i=0;i<64;i++){
    for(int j=0;j<32;j++){
      xpos=i+32;
      ypos=j+32;
      if(current_pix[i][j]==1){
      display.drawPixel(xpos,ypos,WHITE);
      }  
  }  
}
  display.display();
}

void delete_pixel(){
  int xpos,ypos;
  for(int i=0;i<64;i++){
    for(int j=0;j<32;j++){
      xpos=i+32;
      ypos=j+32;
      if(current_pix[i][j]==1){
      display.drawPixel(xpos,ypos,BLACK);
      }  
  }  
}
}


void renewal(){
   for(int i=0;i<64;i++){ 
     for(int j=0;j<32;j++){
       current_pix[i][j]=new_pix[i][j];
     }
   }
}

void born_or_dead(){
 int live_num;
 for(int i=1;i<64;i++){ //checking point is (i,j)
     //live_num=0;
   for(int j=1;j<32;j++){
     live_num=0;
     
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
     
///////GAME RULE//////////////   
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
    //int j=8;
  for(int i=2;i<63;i++){   //initial pixel 
    for(int j=2;j<31;j++){
      byte pix=random(10);
      if(pix>7){
      current_pix[i][j]=pix;
      new_pix[i][j]=pix;
      }
    }    
  }
}


