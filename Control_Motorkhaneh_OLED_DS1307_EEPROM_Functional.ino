// Barname Control Motorkhaneh ---- Khoroji roye OLED ba protocol I2C--- WithOut Timer.
#include <Wire.h> 
#include "U8glib.h"
#include "RTClib.h"
#include <EEPROM.h>

RTC_DS1307 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C > SCL = A5 , SDA = A4

byte Roz = 1;        //Roze Mahe jari.
byte Day = 0;        //Roze hafte jari.
byte Hour = 0;       //Saate jari.
byte Min = 0;        //Daghigheh jari. 
byte s = 0;          //Sanieh.
byte set = 2;        //Payeh Vorodi Set.
byte up = 3;         //Payeh Vorodi UP.
byte down = 4;       //Payeh Vorodi Down.
byte s_c = 0;        //Shomareshgare teadad dafaate feshordeh shodane Set.
byte u_c = 0;        //Shomarandeh tedad dafaate feshordeh shodane UP.
byte d_c = 0;        //Shomarandeh tedad dafaate feshordeh shodane DOWN.
byte FC1 = 0;        // Bite first chek Set.
byte FC2 = 0;        // Bite first cheke UP.
byte FC3 = 0;        // Bite first cheke DOWN.
byte T1 = 5;         //Trmostate 1
byte T2 = 6;         //Trmostate 2
byte T3 = 7;         //Trmostate 3
byte T4 = 8;         //Trmostate 4
byte Boiler = 9;     // Farmane Boiler;
int T[7][4][4];     //Moteghayere Zakhireh tanzimate Termostatha;
byte T1_Day = 0 ;    //Moteghayer Roze T1
byte T2_Day = 0 ;    //Moteghayer Roze T2
byte T3_Day = 0 ;    //Moteghayer Roze T3
byte T4_Day = 0 ;    //Moteghayer Roze T4
byte T1_H_on = 0 ;    //Moteghayer saate on T1
byte T2_H_on = 0 ;    //Moteghayer saate on T2
byte T3_H_on = 0 ;    //Moteghayer saate on T3
byte T4_H_on = 0 ;    //Moteghayer saate on T4
byte T1_M_on = 0 ;    //Moteghayer Daghigheh on T1
byte T2_M_on = 0 ;    //Moteghayer Daghigheh on T2
byte T3_M_on = 0 ;    //Moteghayer Daghigheh on T3
byte T4_M_on = 0 ;    //Moteghayer Daghigheh on T4
byte T1_H_of = 0 ;    //Moteghayer saate off T1
byte T2_H_of = 0 ;    //Moteghayer saate off T2
byte T3_H_of = 0 ;    //Moteghayer saate off T3
byte T4_H_of = 0 ;    //Moteghayer saate off T4
byte T1_M_of = 0 ;    //Moteghayer Daghigheh off T1
byte T2_M_of = 0 ;    //Moteghayer Daghigheh off T2
byte T3_M_of = 0 ;    //Moteghayer Daghigheh off T3
byte T4_M_of = 0 ;    //Moteghayer Daghigheh off T4
int ti = 0;          //Moteghayer Moghayeseh zamane jari ba zamane ON va OFF.
int Boiler_on1 = 0;   //Moteghayer zamane ON Boiler.
int Boiler_of1 = 0;   //Moteghayer zamane OFF Boiler.
int Boiler_on2 = 0;   //Moteghayer zamane ON Boiler.
int Boiler_of2 = 0;   //Moteghayer zamane OFF Boiler.
int Boiler_on3 = 0;   //Moteghayer zamane ON Boiler.
int Boiler_of3 = 0;   //Moteghayer zamane OFF Boiler.
int Boiler_on4 = 0;   //Moteghayer zamane ON Boiler.
int Boiler_of4 = 0;   //Moteghayer zamane OFF Boiler.
int TimerOut_of = 0; //Faal va ghyare faal kardane namayesh timer dar namayeshgare Seryal.
byte pc = 0;           // chek kardane taghyyir baraye sabt dar port seryal.
int Sal = 0;
int Mah = 0;
String Date;
char  day[7][12]={"1 Shanbeh","2 Shanbeh","3 Shanbeh","4 Shanbeh","5 Shanbeh","Jomee","Shanbeh"};
String watch;
byte bc = 0; //Bounce Countting;
int bc_chek = 0;
int ex = 0;
int ex1 = 0;
int Timeout = 150; // Hadaksar Zamani ke kelidi feshordeh nemishavad
//----------------------------------------------
void setup() {
  u8g.setFont(u8g_font_unifont);
  pinMode(set,INPUT_PULLUP);
  pinMode(up,INPUT_PULLUP);
  pinMode(down,INPUT_PULLUP);
  pinMode(T1,INPUT);
  pinMode(T2,INPUT);
  pinMode(T3,INPUT);
  pinMode(T4,INPUT);
  pinMode(Boiler,OUTPUT);
   if (! rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   }
   EEPROM.get(0,T);
}
//----------------------------------------------

void loop() {

    DateTime now = rtc.now();
    Sal = now.year();
    Mah = now.month();
    Roz = now.day();
    Day = now.dayOfTheWeek();
    Hour = now.hour();
    Min = now.minute();
    s = now.second();
    if (String(Hour).length()==1){
      watch="0"+String(Hour)+":";
    }else{
      watch=String(Hour)+":"; 
    }
    if (String(Min).length()==1){
      watch+="0"+String(Min)+":";
    }else{
      watch+=String(Min)+":"; 
    }
    if (String(s).length()==1){
      watch+="0"+String(s);
    }else{
      watch+=String(s); 
    }

   
    Date=String(Sal)+"-";   
    if (String(Mah).length()==1){
      Date+="0"+String(Mah)+"-";
    }else{
      Date+=String(Mah)+"-"; 
    }
    if (String(Roz).length()==1){
      Date+="0"+String(Roz);
    }else{
      Date+=String(Roz); 
    }
    if(TimerOut_of==0){
      u8g.firstPage();  
      do {
        u8g.drawStr( 30, 11,day[now.dayOfTheWeek()]);
        u8g.setPrintPos(30, 60); 
        u8g.print(Date); 
        u8g.setScale2x2();
        u8g.setPrintPos(0, 20);
        u8g.print(watch);
        u8g.undoScale();
       } while( u8g.nextPage() );
    }
    
  if(digitalRead(set)== LOW && FC1 == 0){  // Brrasi feshorde shodane set be manzore vorod be bekhshe tanzimat.
    s_c = 1;
    FC1 = 1;
    TimerOut_of = 1;
    }
    // ************Halghe bakhshe tanzimat - Dar sorate feshordeh shodane set********
    while(s_c>0){
      if(d_c == 0){
        if(pc==0){
          u8g.firstPage();  
          do {
            u8g.drawStr( 40, 11,"Setting");
            u8g.setScale2x2();
            u8g.setPrintPos(5, 22); 
            u8g.print("Time");
            u8g.undoScale();
           } while( u8g.nextPage() );
          pc=1;
        }
        ex++;
        if (ex>=10000){
          ex1++;
          ex = 0;
        }
        if (ex1>=Timeout){
          s_c = 0;
          FC1 = 1;
          d_c = 0;
          TimerOut_of = 0;
          pc = 0;
          }
       }
      if(d_c == 1){
        if(pc==0){
          u8g.firstPage();  
          do {
            u8g.drawStr( 40, 11,"Setting");
            u8g.setScale2x2();
            u8g.setPrintPos(25, 22); 
            u8g.print("T1");
            u8g.undoScale();
           } while( u8g.nextPage() );
          pc=1;
         }
         ex++;
        if (ex>=10000){
          ex1++;
          ex = 0;
        }
        if (ex1>=Timeout){
          s_c = 0;
          FC1 = 1;
          d_c = 0;
          TimerOut_of = 0;
          pc = 0;
          }
        }
      if(d_c == 2){
        if(pc==0){
          u8g.firstPage();  
          do {
            u8g.drawStr( 40, 11,"Setting");
            u8g.setScale2x2();
            u8g.setPrintPos(25, 22); 
            u8g.print("T2");
            u8g.undoScale();
           } while( u8g.nextPage() );
          pc=1;
         }
         ex++;
        if (ex>=10000){
          ex1++;
          ex = 0;
        }
        if (ex1>=Timeout){
          s_c = 0;
          FC1 = 1;
          d_c = 0;
          TimerOut_of = 0;
          pc = 0;
          }
       }
      if(d_c == 3){
        if(pc==0){
          u8g.firstPage();  
          do {
            u8g.drawStr( 40, 11,"Setting");
            u8g.setScale2x2();
            u8g.setPrintPos(25, 22); 
            u8g.print("T3");
            u8g.undoScale();
           } while( u8g.nextPage() );
          pc=1;
         }
         ex++;
        if (ex>=10000){
          ex1++;
          ex = 0;
        }
        if (ex1>=Timeout){
          s_c = 0;
          FC1 = 1;
          d_c = 0;
          TimerOut_of = 0;
          pc = 0;
          }
       }
      if(d_c == 4){
        if(pc==0){
          u8g.firstPage();  
          do {
            u8g.drawStr( 40, 11,"Setting");
            u8g.setScale2x2();
            u8g.setPrintPos(25, 22); 
            u8g.print("T4");
            u8g.undoScale();
           } while( u8g.nextPage() );
          pc=1;
        }
        ex++;
        if (ex>=10000){
          ex1++;
          ex = 0;
        }
        if (ex1>=Timeout){
          s_c = 0;
          FC1 = 1;
          d_c = 0;
          TimerOut_of = 0;
          pc = 0;
          }
       }
      if(d_c == 5){
        if(pc==0){
          u8g.firstPage();  
          do {
            u8g.drawStr( 40, 11,"Setting");
            u8g.setScale2x2();
            u8g.setPrintPos(15, 22); 
            u8g.print("Save");
            u8g.undoScale();
           } while( u8g.nextPage() );
          pc=1;
         }
         ex++;
        if (ex>=10000){
          ex1++;
          ex = 0;
        }
        if (ex1>=Timeout){
          s_c = 0;
          FC1 = 1;
          d_c = 0;
          TimerOut_of = 0;
          pc = 0;
          }
        }
      if(digitalRead(set)== HIGH){ FC1=0;}
      if(digitalRead(set)== LOW && FC1 == 0 && d_c < 5){  // Brrasi feshorde shodane set be manzore vorod be tanzimate har bakhsh.
        s_c = 2;
        FC1 = 1;
        pc = 0;
        ex = 0;
        ex1 = 0;
      }
      
      if(digitalRead(down)== LOW && FC3 == 0){  // Brrasi feshorde shodane DOWN be manzore vorod be tanzimate Koli.
        if(d_c<5){d_c++;}
        FC3 = 1;
        pc = 0;
        ex = 0;
        ex1 = 0;
      }
      if(digitalRead(down)== HIGH){ FC3=0;}

      if(digitalRead(up)== LOW && FC2 == 0){  // Brrasi feshorde shodane DOWN be manzore vorod be tanzimate Koli.
        if(d_c>0){d_c--;}
        FC2 = 1;
        pc = 0;
        ex = 0;
        ex1 = 0;
      }
      if(digitalRead(up)== HIGH){ FC2=0;}

      
      //>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Halgheh TANZIME ZAMAN  <<<<<<<<<<<<<<<<<<<<<<<<
      while(s_c>1 && d_c == 0){                
      // -------- Tanzime sal ------------
        while(s_c == 2){
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 30, 11,"Time Setting");
              u8g.drawStr( 10, 28,"Year:");
              u8g.setScale2x2();
              u8g.setPrintPos(1, 30); 
              u8g.print(Sal);
              u8g.undoScale();
            } while( u8g.nextPage() );            
            pc = 1; 
          }
          ex++;
          if (ex>=10000){
            ex1++;
            ex = 0;
          }
          if (ex1>=Timeout){
            s_c = 0;
            FC1 = 1;
            d_c = 0;
            TimerOut_of = 0;
            pc = 0;
           }
          if(digitalRead(up)==LOW && FC2 == 0){
            Sal++;
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            if(Sal>2022){
              Sal--;
            } 
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 3;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
        }
        // -------- Tanzime Mah ------------
    
        while(s_c == 3){
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 30, 11,"Time Setting");
              u8g.drawStr( 10, 28,"Month:");
              u8g.setScale2x2();
              u8g.setPrintPos(25, 30); 
              u8g.print(Mah);
              u8g.undoScale();
            } while( u8g.nextPage() );              
            pc = 1;
            }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
            }          
          if(digitalRead(up)==LOW && FC2 == 0){
            if(Mah<11){
              Mah++;
            }
            else{
              Mah = 1;
            }
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            if(Mah>1){
              Mah--;
            }
            else{
              Mah = 12;
            }
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 4;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
           } 
        }
        // -------- Tanzime Roz ------------
    
        while(s_c == 4){
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 30, 11,"Time Setting");
              u8g.drawStr( 10, 28,"Day:");
              u8g.setScale2x2();
              u8g.setPrintPos(25, 30); 
              u8g.print(Roz);
              u8g.undoScale();
            } while( u8g.nextPage() );              
            pc = 1;
          }
          ex++;
          if (ex>=10000){
            ex1++;
            ex = 0;
          }
          if (ex1>=Timeout){
            s_c = 0;
            FC1 = 1;
            d_c = 0;
            TimerOut_of = 0;
            pc = 0;
           }          
          if(digitalRead(up)==LOW && FC2 == 0){
            if(Roz<30){
              Roz++;
            }
            else{
              Roz = 1;
            }
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            if(Roz>1){
              Roz--;
            }
            else{
              Roz = 31;
            }
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 5;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
           } 
        }
    // -------- Tanzime Hour ------------
    
        while(s_c == 5){
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 30, 11,"Time Setting");
              u8g.drawStr( 10, 28,"Hour:");
              u8g.setScale2x2();
              u8g.setPrintPos(25, 30); 
              u8g.print(Hour);
              u8g.undoScale();
            } while( u8g.nextPage() );              
            pc = 1;
           }
           ex++;
           if (ex>=10000){
            ex1++;
            ex = 0;
            }
           if (ex1>=Timeout){
            s_c = 0;
            FC1 = 1;
            d_c = 0;
            TimerOut_of = 0;
            pc = 0;
            }
          if(digitalRead(up)==LOW && FC2 == 0){
            Hour = Hour_Up(Hour);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            Hour = Hour_Down(Hour);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 6;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
           } 
        }
   // -------- Tanzime Min ------------
   
        while(s_c == 6){
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 30, 11,"Time Setting");
              u8g.drawStr( 10, 28,"Minute:");
              u8g.setScale2x2();
              u8g.setPrintPos(25, 30); 
              u8g.print(Min);
              u8g.undoScale();
            } while( u8g.nextPage() );            
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            Min = Min_Up(Min);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            Min = Min_Down(Min);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;} 
          if(digitalRead(set)== LOW && FC1 == 0){
            s_c = 1;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
        }
      }
      // >>>>>>>>>> Entehaye Halgheh Tanzime Zaman <<<<<<<<<<<<<<
      //>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Halgheh TANZIME T1  <<<<<<<<<<<<<<<<<<<<<<<<
      while(s_c>1 && d_c == 1){
        // -------- Tanzime Day T1------------ 
        while(s_c == 2){
          if (pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T1 Setting");
              u8g.drawStr( 10, 28,"Day:");
              u8g.setScale2x2();
              u8g.setPrintPos(1, 30); 
              u8g.print(day[T1_Day]);
              u8g.undoScale();
            } while( u8g.nextPage() );                 
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T1_Day = Day_Up(T1_Day);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T1_Day = Day_Down(T1_Day);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 3;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
        }
    // -------- Tanzime Hour ON T1------------
    
        while(s_c == 3){
          T1_H_on = T[T1_Day][0][0];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T1 Setting");
              u8g.drawStr( 10, 28,"ON Hour:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T1_Day][0][0]);
              u8g.undoScale();
            } while( u8g.nextPage() );              
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T1_H_on = Hour_Up(T1_H_on);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T1_H_on = Hour_Down(T1_H_on);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T1_Day][0][0]=T1_H_on;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 4;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
           } 
        }
   // -------- Tanzime Min ON T1------------
   
        while(s_c == 4){
          T1_M_on = T[T1_Day][0][1];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T1 Setting");
              u8g.drawStr( 10, 28,"ON Minute:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T1_Day][0][1]);
              u8g.undoScale();
            } while( u8g.nextPage() );              
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T1_M_on = Min_Up(T1_M_on);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T1_M_on = Min_Down(T1_M_on);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T1_Day][0][1]=T1_M_on;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;} 
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 5;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
        } 
        // -------- Tanzime Hour OFF T1------------
    
        while(s_c == 5){
         T1_H_of =  T[T1_Day][0][2];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T1 Setting");
              u8g.drawStr( 10, 28,"OFF Hour:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T1_Day][0][2]);
              u8g.undoScale();
            } while( u8g.nextPage() ); 
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T1_H_of = Hour_Up(T1_H_of);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T1_H_of = Hour_Down(T1_H_of);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T1_Day][0][2]=T1_H_of;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 6;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
           } 
        }
   // -------- Tanzime Min OFF T1------------
   
        while(s_c == 6){
          T1_M_of = T[T1_Day][0][3];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T1 Setting");
              u8g.drawStr( 10, 28,"OFF Minute:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T1_Day][0][3]);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T1_M_of = Min_Up(T1_M_of);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T1_M_of = Min_Down(T1_M_of);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T1_Day][0][3]=T1_M_of;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;} 
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 1;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
        }                                  
      }
      // >>>>>>>>>> Entehaye Halgheh Tanzime T1 <<<<<<<<<<<<<<
      
      //>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Halgheh TANZIME T2  <<<<<<<<<<<<<<<<<<<<<<<<
      while(s_c>1 && d_c == 2){
        // -------- Tanzime Day T2------------
        while(s_c == 2){
          if(pc == 0) {
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T2 Setting");
              u8g.drawStr( 10, 28,"Day:");
              u8g.setScale2x2();
              u8g.setPrintPos(1, 30); 
              u8g.print(day[T2_Day]);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T2_Day = Day_Up(T2_Day);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T2_Day = Day_Down(T2_Day);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 3;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
        }
    // -------- Tanzime Hour ON T2------------
    
        while(s_c == 3){
          T2_H_on = T[T2_Day][1][0];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T2 Setting");
              u8g.drawStr( 10, 28,"ON Hour:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T2_Day][1][0]=T2_H_on);
              u8g.undoScale();
            } while( u8g.nextPage() ); 
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T2_H_on = Hour_Up(T2_H_on);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T2_H_on = Hour_Down(T2_H_on);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T2_Day][1][0]=T2_H_on;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 4;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
           } 
        }
   // -------- Tanzime Min ON T2------------
   
        while(s_c == 4){
          T2_M_on = T[T2_Day][1][1];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T2 Setting");
              u8g.drawStr( 10, 28,"ON Minute:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T2_Day][1][1]);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T2_M_on = Min_Up(T2_M_on);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T2_M_on = Min_Down(T2_M_on);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T2_Day][1][1]=T2_M_on;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;} 
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 5;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
        } 
        // -------- Tanzime Hour OFF T2------------
    
        while(s_c == 5){
          T2_H_of = T[T2_Day][1][2];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T2 Setting");
              u8g.drawStr( 10, 28,"OFF Hour:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T2_Day][1][2]=T2_H_of);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T2_H_of = Hour_Up(T2_H_of);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T2_H_of = Hour_Down(T2_H_of);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T2_Day][1][2]=T2_H_of;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 6;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
           } 
        }
   // -------- Tanzime Min OFF T2------------
   
        while(s_c == 6){
         T2_M_of = T[T2_Day][1][3];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T2 Setting");
              u8g.drawStr( 10, 28,"OFF Minute:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T2_Day][1][3]);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T2_M_of = Min_Up(T2_M_of);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T2_M_of = Min_Down(T2_M_of);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T2_Day][1][3]=T2_M_of;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;} 
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 1;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
        }                   
      }
      // >>>>>>>>>> Entehaye Halgheh Tanzime T2 <<<<<<<<<<<<<<
      //>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Halgheh TANZIME T3  <<<<<<<<<<<<<<<<<<<<<<<<
      while(s_c>1 && d_c == 3){ 
        // -------- Tanzime Day T3------------
        while(s_c == 2){
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T3 Setting");
              u8g.drawStr( 10, 28,"Day:");
              u8g.setScale2x2();
              u8g.setPrintPos(1, 30); 
              u8g.print(day[T3_Day]);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T3_Day = Day_Up(T3_Day);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T3_Day = Day_Down(T3_Day);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 3;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
        }
    // -------- Tanzime Hour ON T3------------
    
        while(s_c == 3){
          T3_H_on = T[T3_Day][2][0];
          if(pc==0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T3 Setting");
              u8g.drawStr( 10, 28,"ON Hour:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T3_Day][2][0]);
              u8g.undoScale();
            } while( u8g.nextPage() ); 
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T3_H_on = Hour_Up(T3_H_on);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T3_H_on = Hour_Down(T3_H_on);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T3_Day][2][0]=T3_H_on;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 4;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
           } 
        }
   // -------- Tanzime Min ON T3------------
   
        while(s_c == 4){
          T3_M_on = T[T3_Day][2][1];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T3 Setting");
              u8g.drawStr( 10, 28,"ON Minute:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T3_Day][2][1]);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T3_M_on = Min_Up(T3_M_on);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T3_M_on = Min_Down(T3_M_on);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T3_Day][2][1]=T3_M_on;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;} 
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 5;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
        } 
        // -------- Tanzime Hour OFF T3------------
    
        while(s_c == 5){
         T3_H_of = T[T3_Day][2][2];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T3 Setting");
              u8g.drawStr( 10, 28,"OFF Hour:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T3_Day][2][2]);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T3_H_of = Hour_Up(T3_H_of);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T3_H_of = Hour_Down(T3_H_of);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T3_Day][2][2]=T3_H_of;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 6;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
           } 
        }
   // -------- Tanzime Min OFF T3------------
   
        while(s_c == 6){
          T3_M_of = T[T3_Day][2][3];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T3 Setting");
              u8g.drawStr( 10, 28,"OFF Minute:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T3_Day][2][3]);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T3_M_of = Min_Up(T3_M_of);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T3_M_of = Min_Down(T3_M_of);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T3_Day][2][3]=T3_M_of;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;} 
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 1;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
        }                    
      }
      // >>>>>>>>>> Entehaye Halgheh Tanzime T3 <<<<<<<<<<<<<<
      //>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Halgheh TANZIME T4  <<<<<<<<<<<<<<<<<<<<<<<<
      while(s_c>1 && d_c == 4){
        // -------- Tanzime Day T4------------
        while(s_c == 2){
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T4 Setting");
              u8g.drawStr( 10, 28,"Day:");
              u8g.setScale2x2();
              u8g.setPrintPos(1, 30); 
              u8g.print(day[T4_Day]);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T4_Day = Day_Up(T4_Day);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T4_Day = Day_Down(T4_Day);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 3;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
        }
    // -------- Tanzime Hour ON T4------------
    
        while(s_c == 3){
          T4_H_on = T[T4_Day][3][0];
          if (pc == 0) {
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T4 Setting");
              u8g.drawStr( 10, 28,"ON Hour:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T4_Day][3][0]);
              u8g.undoScale();
            } while( u8g.nextPage() ); 
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T4_H_on = Hour_Up(T4_H_on);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T4_H_on = Hour_Down(T4_H_on);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T4_Day][3][0]=T4_H_on;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 4;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
           } 
        }
   // -------- Tanzime Min ON T4------------
   
        while(s_c == 4){
          T4_M_on = T[T4_Day][3][1];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T4 Setting");
              u8g.drawStr( 10, 28,"ON Minute:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T4_Day][3][1]);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T4_M_on = Min_Up(T4_M_on);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T4_M_on = Min_Down(T4_M_on);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T4_Day][3][1]=T4_M_on;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;} 
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 5;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
        } 
        // -------- Tanzime Hour OFF T4------------
    
        while(s_c == 5){
          T4_H_of = T[T4_Day][3][2];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T4 Setting");
              u8g.drawStr( 10, 28,"OFF Hour:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T4_Day][3][2]);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T4_H_of = Hour_Up(T4_H_of);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T4_H_of = Hour_Down(T4_H_of);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T4_Day][3][2]=T4_H_of;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;}
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 6;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
           } 
        }
   // -------- Tanzime Min OFF T4------------
   
        while(s_c == 6){
          T4_M_of = T[T4_Day][3][3];
          if(pc == 0){
            u8g.firstPage();  
            do {
              u8g.drawStr( 35, 11,"T4 Setting");
              u8g.drawStr( 10, 28,"OFF Minute:");
              u8g.setScale2x2();
              u8g.setPrintPos(30, 30); 
              u8g.print(T[T4_Day][3][3]);
              u8g.undoScale();
            } while( u8g.nextPage() );
            pc = 1;
          }
            ex++;
            if (ex>=10000){
              ex1++;
              ex = 0;
            }
            if (ex1>=Timeout){
              s_c = 0;
              FC1 = 1;
              d_c = 0;
              TimerOut_of = 0;
              pc = 0;
             }
          if(digitalRead(up)==LOW && FC2 == 0){
            T4_M_of = Min_Up(T4_M_of);
            FC2 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          if(digitalRead(up)==HIGH ){ FC2 = 0;}
          if(digitalRead(down)==LOW && FC3 == 0){
            T4_M_of = Min_Down(T4_M_of);
            FC3 = 1;
            pc = 0;
            ex = 0;
            ex1 = 0;
          }
          T[T4_Day][3][3]=T4_M_of;
          if(digitalRead(down)==HIGH ){ FC3 = 0;}
          if(digitalRead(set)== HIGH){ FC1=0;} 
          if(digitalRead(set)== LOW && FC1 == 0){ 
            s_c = 1;
            FC1 = 1;
            FC2 = 0;
            FC3 = 0;
            pc = 0;
            ex = 0;
            ex1 = 0;
          } 
        }                   
      }
      // >>>>>>>>>> Entehaye Halgheh Tanzime T4 <<<<<<<<<<<<<<
      if(digitalRead(set)== HIGH){ FC1=0;} 
      // ----- Barrasi sharte khoroj az tanzimat ----------------
      
        if(digitalRead(set)== LOW && FC1 == 0 && d_c == 5){  // Brrasi feshorde shodane set be manzore Khoroj az tanzimate.
          s_c = 0;
          FC1 = 1;
          d_c = 0;
          TimerOut_of = 0;
          pc = 0;
          ex = 0;
          ex1 = 0;
          rtc.adjust(DateTime(Sal, Mah, Roz, Hour, Min, 0));
          EEPROM.put(0,T);

        }
        
    }
    
  //************Entehaye Halgheh Tanzimat************
  
  //*********Routine Barnameh- Faal Kardane khoroji Boiler*********
  if(digitalRead(set)== HIGH){ FC1=0;}
  ex = 0;
  ex1 = 0;
  
  // ----------- Faal kardane Khoroji Boiler -------------------
  ti = (Hour*100)+(Min);
   Boiler_on1 = (T[Day][0][0]*100)+(T[Day][0][1]);
   Boiler_of1 = (T[Day][0][2]*100)+(T[Day][0][3]);
   Boiler_on2 = (T[Day][1][0]*100)+(T[Day][1][1]);
   Boiler_of2 = (T[Day][1][2]*100)+(T[Day][1][3]);
   Boiler_on3 = (T[Day][2][0]*100)+(T[Day][2][1]);
   Boiler_of3 = (T[Day][2][2]*100)+(T[Day][2][3]);
   Boiler_on4 = (T[Day][3][0]*100)+(T[Day][3][1]);
   Boiler_of4 = (T[Day][3][2]*100)+(T[Day][3][3]);
   if(ti>=Boiler_on1 && ti<Boiler_of1){
      if(digitalRead(5)==LOW){
        bc = 0;
        bc_chek = 0;
        digitalWrite(Boiler,HIGH);
      }
      else{
        if(digitalRead(5)==HIGH && bc_chek == 0){bc++;}
        if(bc >= 20){
          digitalWrite(Boiler,LOW);
          bc_chek = 1; 
        }
      }
    }
    else if(ti>=Boiler_on2 && ti<Boiler_of2){
      if(digitalRead(6)==LOW){
        bc = 0;
        bc_chek = 0;
        digitalWrite(Boiler,HIGH);
      }
      else{
        if(digitalRead(6)==HIGH && bc_chek == 0){bc++;}
        if(bc >= 20){
          digitalWrite(Boiler,LOW);
          bc_chek = 1;
        } 
      }
    }
    else if(ti>=Boiler_on3 && ti<Boiler_of3){
      if(digitalRead(7)==LOW){
        bc = 0;
        bc_chek = 0;
        digitalWrite(Boiler,HIGH);
      }
      else{
        if(digitalRead(7)==HIGH && bc_chek == 0){bc++;}
        if(bc >= 20){
          digitalWrite(Boiler,LOW); 
          bc_chek = 1;
        }
      }
    }
    else if(ti>=Boiler_on4 && ti<Boiler_of4){
      if(digitalRead(8)==LOW){
        bc = 0;
        bc_chek = 0;
        digitalWrite(Boiler,HIGH);
      }
      else{
        if(digitalRead(8)==HIGH && bc_chek == 0){bc++;}
        if(bc >= 20){
          digitalWrite(Boiler,LOW); 
          bc_chek = 1;
        }
      }
    }
    else{
      digitalWrite(Boiler,LOW);
    }
}

byte Day_Up(byte d_u){
  if(d_u<6){
     d_u++;
  }
  else{
     d_u = 0;
            }
  return d_u;
}

byte Day_Down(byte d_d){
  if(d_d>0){
     d_d--;
  } 
  else{
     d_d = 6;
  }
  return d_d;
}

byte Hour_Up(byte h_u){
  if(h_u<23){
     h_u++;
  }
  else{
     h_u = 0;
  }
  return h_u;
}

byte Hour_Down(byte h_d){
  if(h_d>0){
    h_d--;
  }
  else{
    h_d = 23;
  }
  return h_d;
}

byte Min_Up(byte m_u){
  if(m_u<59){
     m_u++;
  }
  else{
     m_u = 0;
  } 
  return m_u;
}

byte Min_Down(byte m_d){
            if(m_d>0){
              m_d--;
            }
            else{
              m_d = 59;
            }  
            return m_d;
}
