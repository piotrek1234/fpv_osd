

#include "config.h"
#include "ascii.h"
#include "output.h"
#include "variables.h"

#include <avr/delay.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>


extern unsigned char align_text;
extern unsigned char flight_timer[];

extern unsigned char show_plane_pos;
extern unsigned char show_mah_km;
extern unsigned char mahkmr[];
extern int mah_alarm;

extern int homehead_r[];

extern long los;
extern int los_alarm;

extern long altitude_num2;
extern int alt_alarm;
extern unsigned char show_decimals;
extern int arrowd;;
extern int volt_alarm;

extern int menuon;
extern char move_arrow_count;
extern unsigned char menupos;
extern unsigned char menu;
extern unsigned char altitude_offset_on;
extern char GPSbuffer[100];
extern char homepos;
extern unsigned char satellitesr[3];
extern char GPSfix;
extern int homeposcount;
extern unsigned char test;
extern unsigned char loadbar[];
extern unsigned char time[14];
extern unsigned char landed;
extern unsigned char max_altr[];
extern unsigned char max_speedr[];
extern unsigned char max_losr[];
extern unsigned char total_distancer[];
extern int current_num;
extern unsigned char arrowr[];
extern int altitude_negative;
extern unsigned char avg_speedr[];
extern int latitude[15];
extern unsigned char latitude_dir;
extern unsigned char longitude_dir;
extern int longitude[15];
extern unsigned char losr[];
extern unsigned char speedkmw[5];
extern unsigned char altitude2[10];
extern unsigned char altituder[10];





void detectframe() {
         line=0;       
}



void detectline() {
         little_delay // This is used to adjust to timing when using SimpleOSD instead of Arduino


////////////////////////////////////////////
// Flight timer and mah/km
////////////////////////////////////////////

/*
       if (line > 75  && line < (75 +17)) {  
         temp = line - (76);
           _delay_loop_1(align_text);         
           SPDR = 0b11111110;
           _delay_loop_1(20);        
           for (unsigned char j =0; j<5;j++) {
           SPDR = letters[toptext[j]<<3+temp];
           delay14;    
             
           }
           delay15;
           SPDR = letters[(toptext[4]<<3)+(temp)];
            
           
       }

*/
#if defined(timer_line)
       if (line > timer_line  && line < (timer_line +17)) {  

         // Used to align the text
           _delay_loop_1(align_text);         
           
           
            temp = line - (timer_line +1);
  
            // On first line we update the buffer
            if (line == timer_line+1) {
         buffer2[0]=(flight_timer[0])<<5;   
         buffer2[1]=(flight_timer[1])<<5;   
         buffer2[2]=(flight_timer[2])<<5;          
         buffer2[3]=(flight_timer[3])<<5;  
         
         
          if  (show_mah_km == 1 || show_rssi == 1) {
            
            if (show_rssi == 1) {
             mahkmr[0]=3;
             mahkmr[1]=rssir[0];
             mahkmr[2]=rssir[1];
             mahkmr[3]=rssir[2];          
             
           }
                
              if (mahkmr[0]==3 && mahkmr[1]==3 && mahkmr[2]==3) {
              mahkm_buf[0]=14<<5;   
              mahkm_buf[1]=14<<5;   
              mahkm_buf[2]=14<<5;   
              mahkm_buf[3]=(mahkmr[3])<<5; 
              }   
              
             else if (mahkmr[0]==3 && mahkmr[1]==3) {
              mahkm_buf[0]=14<<5;   
              mahkm_buf[1]=14<<5;   
              mahkm_buf[2]=(mahkmr[2])<<5;          
              mahkm_buf[3]=(mahkmr[3])<<5; 
              }             
            
             else if (mahkmr[0]==3) {
              mahkm_buf[0]=14<<5;   
              mahkm_buf[1]=(mahkmr[1])<<5;   
              mahkm_buf[2]=(mahkmr[2])<<5;          
              mahkm_buf[3]=(mahkmr[3])<<5; 
              }                  
              
              else {
              mahkm_buf[0]=(mahkmr[0])<<5;   
              mahkm_buf[1]=(mahkmr[1])<<5;   
              mahkm_buf[2]=(mahkmr[2])<<5;          
              mahkm_buf[3]=(mahkmr[3])<<5;  
              }
              
             if (rssi_negative==1 && show_rssi==1) {
              mahkm_buf[0]=13<<5; 
            }   
     
              }
                   //SPDR = 0b11111110;     
            
            }

        
         else {
              _delay_loop_1(6);
              SPDR = LargeNumbers[buffer2[0]+2*temp];
              DimOn;
               delay13

              SPDR = LargeNumbers[buffer2[0]+2*temp+1];
               delay8
               
              SPDR = LargeNumbers[buffer2[1]+2*temp];
               delay15           

              SPDR = LargeNumbers[buffer2[1]+2*temp+1];
               delay15
               
               SPDR = LargeNumbers[64+2*temp];
               delay8

               
              SPDR = LargeNumbers[buffer2[2]+2*temp];
               delay15
               
              SPDR = LargeNumbers[buffer2[2]+2*temp+1];
               delay8
               
              SPDR = LargeNumbers[buffer2[3]+2*temp];
               delay15
               
              SPDR = LargeNumbers[buffer2[3]+2*temp+1];
               delay15             
               DimOff;
               

              if (show_plane_pos == 1) {
                _delay_loop_1(20);
               SPDR = LargeNumbers[homehead_r[0]+2*temp];
              DimOn;
              delay13

              SPDR = LargeNumbers[homehead_r[0]+2*temp+1];
              delay8
               
              SPDR = LargeNumbers[homehead_r[1]+2*temp];
               delay15        

              SPDR = LargeNumbers[homehead_r[1]+2*temp+1];
               delay8
               
              SPDR = LargeNumbers[homehead_r[2]+2*temp];
               delay15
               
              SPDR = LargeNumbers[homehead_r[2]+2*temp+1];
               delay15

              DimOff; 
 
              }

              else                {
              _delay_loop_1(40);       
              delay1         
              }
               
               
            if  (show_mah_km == 1 || show_rssi == 1 ) {
              
                 _delay_loop_1(20); // 126
                 delay1
              SPDR = LargeNumbers[mahkm_buf[0]+2*temp];
              DimOn;
              delay13

              SPDR = LargeNumbers[mahkm_buf[0]+2*temp+1];
              delay8
               
              SPDR = LargeNumbers[mahkm_buf[1]+2*temp];
               delay15        

              SPDR = LargeNumbers[mahkm_buf[1]+2*temp+1];
               delay8
               
              SPDR = LargeNumbers[mahkm_buf[2]+2*temp];
               delay15
               
              SPDR = LargeNumbers[mahkm_buf[2]+2*temp+1];
               delay8
                
              SPDR = LargeNumbers[mahkm_buf[3]+2*temp];
               delay15
               
              SPDR = LargeNumbers[mahkm_buf[3]+2*temp+1];
               delay15

              DimOff;            
            }             
         }
       }
#endif

////////////////////////////////////////////
// Flight timer END
////////////////////////////////////////////

////////////////////////////////////////////
// Top line big numbers
////////////////////////////////////////////

#if defined(timer_line)
else
#endif

#if defined(toplinenumbers)
if (line > toplinenumbers  && line < (toplinenumbers +17)) {
        
        // Used to align the text
         _delay_loop_1(align_text);
         _delay_loop_1(1);
         
         temp = line - (toplinenumbers +1);
                
         if (line == toplinenumbers+1) {
           
         if (los > los_alarm && flight_timer[3]%2 == 0 && los_alarm != 0) {
           
         buffer3[5]=14<<5;
         buffer3[6]=14<<5;
         buffer3[7]=14<<5;    
         buffer3[8]=14<<5;             
         }
         if (altitude_num2 > alt_alarm*10 && flight_timer[3]%2 == 0 && alt_alarm != 0) {
           
         buffer3[9]=14<<5;
         buffer3[10]=14<<5;
         buffer3[11]=14<<5;    
         buffer3[12]=14<<5;    
         buffer3[13]=14<<5;                      
         buffer3[14]=14<<5;              
         }
         }
         else {
           _delay_loop_1(3);
           
// Writes Speed

        if (show_decimals == 1) {
              SPDR = LargeNumbers[buffer3[0]+2*temp];
              DimOn;
              delay13

              SPDR = LargeNumbers[buffer3[0]+2*temp+1];
              delay8
               
              SPDR = LargeNumbers[buffer3[1]+2*temp];
               delay15        

              SPDR = LargeNumbers[buffer3[1]+2*temp+1];
               delay8
                              
              SPDR = LargeNumbers[buffer3[2]+2*temp];
               delay15
               
              SPDR = LargeNumbers[buffer3[2]+2*temp+1];

                if (buffer3[3] != 448) {
               delay2
              SPDR = LargeNumbers[buffer3[3]+2*temp];
               delay15
                
              SPDR = LargeNumbers[buffer3[3]+2*temp+1];
               delay4
                }
                
                else {
                  DimOff;
                _delay_loop_1(10);
                delay1
                }
                
              if (buffer3[4] != 448) {
              SPDR = LargeNumbers[buffer3[4]+2*temp];
              delay15
               
              SPDR = LargeNumbers[buffer3[4]+2*temp+1];
               delay15
               DimOff;
              }
              
               else {
               DimOff;                 
               _delay_loop_1(13);
               }
        }
        
        else {
              SPDR = LargeNumbers[buffer3[0]+2*temp];
              DimOn;
              delay13

              SPDR = LargeNumbers[buffer3[0]+2*temp+1];
              delay8
               
              SPDR = LargeNumbers[buffer3[1]+2*temp];
               delay15        

              SPDR = LargeNumbers[buffer3[1]+2*temp+1];
               delay8
                       
              SPDR = LargeNumbers[buffer3[2]+2*temp];
               delay15
               
              SPDR = LargeNumbers[buffer3[2]+2*temp+1];
               delay15
               
              DimOff;  
               _delay_loop_1(25);
        }
  
  // Here should be time to update the buffer for the arrow
  buffer2[11]=arrowd<<5;   
  
  // Skriver LOS tal
                 if (buffer3[5] != 448) {
              SPDR = LargeNumbers[buffer3[5]+2*temp];
              DimOn;
              delay13

              SPDR = LargeNumbers[buffer3[5]+2*temp+1];
               delay4
              }
              
              else {
             _delay_loop_1(12);
              }
               
              SPDR = LargeNumbers[buffer3[6]+2*temp];
               DimOn;  
               delay13        

              SPDR = LargeNumbers[buffer3[6]+2*temp+1];
               delay8
                              
               
              SPDR = LargeNumbers[buffer3[7]+2*temp];
               delay15
               
              SPDR = LargeNumbers[buffer3[7]+2*temp+1];
                delay8
                
               if (buffer3[8] != 448) {
              SPDR = LargeNumbers[buffer3[8]+2*temp];
               delay15
               
              SPDR = LargeNumbers[buffer3[8]+2*temp+1];
               delay15
              DimOff;                       
               }
               
               else {
             DimOff;
             _delay_loop_1(14);
              }
               
               
         
              
        // Let's draw the arrow. 
              
        SPDR = HomeArrow[buffer2[11]+2*temp];
        DimOn;
         delay13              
        SPDR = HomeArrow[buffer2[11]+2*temp+1]; 
         delay15             
        DimOff; 
        
        
// Writes ALT              

        /*  if (show_decimals == 1) {
//              _delay_loop_1(13);
              
              if (buffer3[9] !=448) {
              SPDR = LargeNumbers[buffer3[9]+2*temp];
              DimOn;
               delay13

              SPDR = LargeNumbers[buffer3[9]+2*temp+1];
//               delay4
              }

              else {
             _delay_loop_1(10);
              }              
              
              if (buffer3[10] != 448) {
              SPDR = LargeNumbers[buffer3[10]+2*temp];
              DimOn;
               delay13            

              SPDR = LargeNumbers[buffer3[10]+2*temp+1];
//               delay4
              }
              
              else {
             _delay_loop_1(10);
              }              

            if (buffer3[11] != 448) {
              SPDR = LargeNumbers[buffer3[11]+2*temp];
             DimOn;
               delay13
               
              SPDR = LargeNumbers[buffer3[11]+2*temp+1];
               delay8
            }

              else {
             _delay_loop_1(10);
             delay4
              }            

              SPDR = LargeNumbers[buffer3[12]+2*temp];
              DimOn;
              delay13
               
              SPDR = LargeNumbers[buffer3[12]+2*temp+1];
              delay8
               
               
              SPDR = LargeNumbers[buffer3[13]+2*temp];
              delay15
              
              SPDR = LargeNumbers[buffer3[13]+2*temp+1];
               delay8 


              SPDR = LargeNumbers[buffer3[14]+2*temp];
              delay15
              
              SPDR = LargeNumbers[buffer3[14]+2*temp+1];
               delay15               
               DimOff;
          }
          
          else {
                _delay_loop_1(37);
              SPDR = LargeNumbers[buffer3[9]+2*temp];
              DimOn;
               delay13

              SPDR = LargeNumbers[buffer3[9]+2*temp+1];
               delay8
              

              SPDR = LargeNumbers[buffer3[10]+2*temp];
               delay15            

              SPDR = LargeNumbers[buffer3[10]+2*temp+1];
               delay8
                              

              SPDR = LargeNumbers[buffer3[11]+2*temp];
               delay15
               
              SPDR = LargeNumbers[buffer3[11]+2*temp+1];
               delay8
                

              SPDR = LargeNumbers[buffer3[12]+2*temp];
              delay15
               
              SPDR = LargeNumbers[buffer3[12]+2*temp+1];
              delay15 
              DimOff;
          }*/
          
               
         }
}  
#endif

////////////////////////////////////////////
// Top line big numbers END
////////////////////////////////////////////







////////////////////////////////////////////
// Buttom line big numbers
////////////////////////////////////////////
#if defined(toplinenumbers)
else
#endif
#if defined(butlinenumbers)
if (line > butlinenumbers && line < (butlinenumbers +17)) {

            // Used to align the text
             _delay_loop_1(align_text);
  
              temp = line - (butlinenumbers +1);

               
 if (line == butlinenumbers+1) {
         if (bat_volt < volt_alarm && flight_timer[3]%2 == 0 && volt_alarm !=0) {
           
         buffer2[0]=14<<5;
         buffer2[1]=14<<5;
         buffer2[2]=14<<5;              
           
         }
     }
     
     else {
         //     _delay_loop_1(3);               
             /*if (temp > 8) {          
                  delay5
         SPDR = letters[(3<<3)+(temp-8)];
         DimOn;
                  delay12                 
                  
         SPDR = letters[(21<<3)+(temp-8)]; 
                  delay13
         
         SPDR = letters[(18<<3)+(temp-8)];
                  delay2        
             }
             
           else {        
         _delay_loop_1(19); 
         delay3         
           }  
         
              SPDR = LargeNumbers[buffer2[0]+2*temp];
              DimOn;
               delay13

              SPDR = LargeNumbers[buffer2[0]+2*temp+1];
               delay8
               
              SPDR = LargeNumbers[buffer2[1]+2*temp];
               delay15           

              SPDR = LargeNumbers[buffer2[1]+2*temp+1];
               delay15
               
               SPDR = LargeNumbers[480+2*temp];
               delay8
//               SPDR = LargeNumbers[32+2*temp+1];
//               delay13        
               
              SPDR = LargeNumbers[buffer2[2]+2*temp];
               delay15
               
              SPDR = LargeNumbers[buffer2[2]+2*temp+1];
               delay15
              DimOff;
              
   
              
                _delay_loop_1(8);   */    
//              ==================================================

            /* if (temp > 8) {       //VLT   
                  delay5
         SPDR = letters[(22<<3)+(temp-8)];
         DimOn;
                  delay12                 
                  
         SPDR = letters[(0<<3)+(temp-8)]; 
                  delay13
         
         SPDR = letters[(1<<3)+(temp-8)];
                  delay5        
             }
             
           else {        
         _delay_loop_1(18);
         delay8    
            
           }  */

              SPDR = LargeNumbers[buffer2[0]+2*temp];
              DimOn;
               delay13

              SPDR = LargeNumbers[buffer2[0]+2*temp+1];
               delay8
               SPDR = LargeNumbers[480+2*temp];
               delay8 
              SPDR = LargeNumbers[buffer2[1]+2*temp];
               delay15   

              SPDR = LargeNumbers[buffer2[1]+2*temp+1];
               delay15
               delay2

              SPDR = LargeNumbers[buffer2[2]+2*temp];
               delay15
               
              SPDR = LargeNumbers[buffer2[2]+2*temp+1];
               delay15
              DimOff;
// ======================================================
            _delay_loop_1(18);

              /*if (temp > 8) {       //VLT2   
                  delay5
         SPDR = letters[(22<<3)+(temp-8)];
         DimOn;
                  delay12                 
                  
         SPDR = letters[(0<<3)+(temp-8)]; 
                  delay13
         
         SPDR = letters[(2<<3)+(temp-8)];
                  delay5        
             }
             
           else {        
         _delay_loop_1(18);
         delay8   
                
           }  */

              SPDR = LargeNumbers[buffer2[3]+2*temp];
              DimOn;
               delay13

              SPDR = LargeNumbers[buffer2[3]+2*temp+1];
               delay8
               SPDR = LargeNumbers[480+2*temp];
               delay8 
              SPDR = LargeNumbers[buffer2[4]+2*temp];
               delay15   

              SPDR = LargeNumbers[buffer2[4]+2*temp+1];
               delay15
               delay2

              SPDR = LargeNumbers[buffer2[5]+2*temp];
               delay15
               
              SPDR = LargeNumbers[buffer2[5]+2*temp+1];
               delay15
              DimOff;
 //-----------------------------------------
              _delay_loop_1(18);
              
             /* if (temp > 8) {       //VLT 3  
                  delay5
         SPDR = letters[(22<<3)+(temp-8)];
         DimOn;
                  delay12                 
                  
         SPDR = letters[(0<<3)+(temp-8)]; 
                  delay13
         
         SPDR = letters[(3<<3)+(temp-8)];
                  delay5        
             }
             
           else {        
         _delay_loop_1(18);
         delay8         
           }  */

              SPDR = LargeNumbers[buffer2[6]+2*temp];
              DimOn;
               delay13

              SPDR = LargeNumbers[buffer2[6]+2*temp+1];
               delay8
               SPDR = LargeNumbers[480+2*temp];
               delay8 
              SPDR = LargeNumbers[buffer2[7]+2*temp];
               delay15   

              SPDR = LargeNumbers[buffer2[7]+2*temp+1];
               delay15
               delay2

              SPDR = LargeNumbers[buffer2[8]+2*temp];
               delay15
               
              SPDR = LargeNumbers[buffer2[8]+2*temp+1];
               delay15
              DimOff;

        /* _delay_loop_1(20);   
                        
        if (temp > 7) {                        
         SPDR = letters[(13<<3)+(temp-8)];
         DimOn;
                  delay13                 
            
         SPDR = letters[(1<<3)+(temp-8)]; 
                  delay15
         
         SPDR = letters[(8<<3)+(temp-8)];                        
                  delay11
        }
        else {
          _delay_loop_1(19);
          delay1
        }
                
              
          SPDR = LargeNumbers[buffer2[4]+2*temp];
          DimOn;
           delay15

          SPDR = LargeNumbers[buffer2[4]+2*temp+1];
           delay8 
           
           
          SPDR = LargeNumbers[buffer2[5]+2*temp];
           delay15          

          SPDR = LargeNumbers[buffer2[5]+2*temp+1];
           delay8  
           
           
          SPDR = LargeNumbers[buffer2[6]+2*temp];
           delay15
           
          SPDR = LargeNumbers[buffer2[6]+2*temp+1];
           delay8  


          SPDR = LargeNumbers[buffer2[7]+2*temp];
           delay15
           
          SPDR = LargeNumbers[buffer2[7]+2*temp+1];             
           delay15            
           DimOff;
*/
          }
          
          
       
}
#endif

////////////////////////////////////////////
// Buttom line big numbers END
////////////////////////////////////////////









////////////////////////////////////////////
// Top line text
////////////////////////////////////////////
#if defined(butlinenumbers)
else 
#endif

#if defined(toplinetext)
if (line > toplinetext  && line < (toplinetext +9)) {
         
       // Used to align the text
       _delay_loop_1(align_text);
         
         temp = line - (toplinetext+1);
         
          //_delay_loop_1(13);
          

         // Writes SPEED, which is the first 5 characters in the toptext array
         buffer[0]=(toptext[0])<<3;
         buffer[1]=(toptext[1])<<3;
         buffer[2]=(toptext[2])<<3;   
         buffer[3]=(toptext[3])<<3;   
         buffer[4]=(toptext[4])<<3;   

 
         // Updates SPDR (SPI buffer)
         SPDR = letters[(buffer[0])+(temp)];
         DimOn;
                 // Adds delay before the SPI buffer can be updated again. 
                 delay12   
            
         SPDR = letters[(buffer[1])+(temp)]; 
                 delay12 
         
         SPDR = letters[(buffer[2])+(temp)];
                delay13                   
                  
         SPDR = letters[(buffer[3])+(temp)];
                delay13
         
         SPDR = letters[(buffer[4])+(temp)];
                delay13
         DimOff;
         
         
         // Writes LOS (The delay loop is used to place the LOS in the middle)
          _delay_loop_1(69);
           
         buffer[0]=(toptext[5])<<3;
         buffer[1]=(toptext[6])<<3;
         buffer[2]=(toptext[7])<<3;   
         

         SPDR = letters[(buffer[0])+(temp)];
        DimOn;
                delay12   
            
         SPDR = letters[(buffer[1])+(temp)]; 
                delay13 
         
         SPDR = letters[(buffer[2])+(temp)];
                delay13
        DimOff;
         
         // Writes ALT;
          _delay_loop_1(70);
          
         buffer[0]=(toptext[8])<<3;
         buffer[1]=(toptext[9])<<3;
         buffer[2]=(toptext[10])<<3;   
         
          SPDR = letters[(buffer[0])+(temp)];
          DimOn;
                  delay13  
            
         SPDR = letters[(buffer[1])+(temp)]; 
                  delay13
         
         SPDR = letters[(buffer[2])+(temp)];
                  delay13       
         DimOff;  
       }
#endif       
       
 ////////////////////////////////////////////
// Top line text END
////////////////////////////////////////////      
       
#if defined(toplinetext)
     else
#endif
#if defined(summaryline)
if (line > summaryline  && line < (summaryline +90)) {  
       
     // Used to align the text
     _delay_loop_1(align_text);
       
      
       if (menuon==1) {
         

         
         if (line == summaryline+1) {
         move_arrow_count++;
         if (move_arrow_count== 30) {
          move_arrow_count=0;
           
           menupos++;
           if (menupos >7) {
            menupos=1; 
           }
         }
         }
         
         if (menu==1) {
           
           temp = line - (summaryline +1);
           _delay_loop_1(13);        
           
           if (temp < 8) {


        if (temp == 0)    {
         buffer[0]=('M'-64)<<3;   
         buffer[1]=('A'-64)<<3;   
         buffer[2]=('H'-64)<<3;   
         buffer[3]=(0)<<3;   
         buffer[4]=('K'-64)<<3;   
         buffer[5]=('M'-64)<<3;   
         buffer[6]=(0)<<3;
        }
        
        else {
            _delay_loop_1(40);   
          if (menupos == 1) {
        SPDR = 0b11111100; numbers[0+(temp)];
           _delay_loop_1(3);       
          }
          else {
        SPDR = 0b00000000;
           _delay_loop_1(3);       
          }       
                            
        DimOn;                    
        for (unsigned char ij=0;ij<6;ij++) {
        SPDR = letters[buffer[ij]+(temp)];       
        _delay_loop_1(2);  
        }  

         _delay_loop_1(45);          
        buffer[8]=(show_mah_km+3)<<3;
        SPDR = numbers[buffer[8]+(temp)];
           _delay_loop_1(3);   

        DimOff;
        }
         
       }
       
     else if (temp > 10 && temp < 19) {
         temp = line - (summaryline +12);
           _delay_loop_1(27);     
           
           
         buffer[0]=('D'-64)<<3;   
         buffer[1]=('E'-64)<<3;   
         buffer[2]=('C'-64)<<3;   
         buffer[3]=('I'-64)<<3;   
         buffer[4]=('M'-64)<<3;   
         buffer[5]=('A'-64)<<3;   
         buffer[6]=('L'-64)<<3;   
         buffer[7]=('S'-64)<<3;   
         buffer[8]=(0)<<3;
         buffer[9]=(0)<<3;

          if (menupos == 2) {
        SPDR = 0b11111100; //numbers[0+(temp)];
           _delay_loop_1(3);       
          }
          else {
        SPDR = 0b00000000;
           _delay_loop_1(3);       
          }       
                            
        DimOn;                    
        for (unsigned char ij=0;ij<8;ij++) {
        SPDR = letters[buffer[ij]+(temp)];       
        _delay_loop_1(2);  
        }  
        
         _delay_loop_1(31);          
        buffer[8]=(show_decimals+3)<<3;
        SPDR = numbers[buffer[8]+(temp)];
        delay14   
        
        DimOff;
           
           
           
     }


     else if (temp > 20 && temp < 29) {
         temp = line - (summaryline +22);
           _delay_loop_1(24);     
           
           
         buffer[0]=('A'-64)<<3;   
         buffer[1]=('L'-64)<<3;   
         buffer[2]=('T'-64)<<3;   
         buffer[3]=(0)<<3;   
         buffer[4]=('O'-64)<<3;   
         buffer[5]=('F'-64)<<3;   
         buffer[6]=('F'-64)<<3;   
         buffer[7]=('S'-64)<<3;   
         buffer[8]=('E'-64)<<3;   
         buffer[9]=('T'-64)<<3;   

          if (menupos == 3) {
        SPDR = 0b11111100; //numbers[0+(temp)];
           _delay_loop_1(3);       
          }
          else {
        SPDR = 0b00000000;
           _delay_loop_1(3);       
          }       
                            
        DimOn;                    
        for (unsigned char ij=0;ij<10;ij++) {
        SPDR = letters[buffer[ij]+(temp)];    
        _delay_loop_1(2);          
        }  

        _delay_loop_1(19);  
        buffer[8]=(altitude_offset_on+3)<<3;
        SPDR = numbers[buffer[8]+(temp)];
        delay14   
        
        DimOff;
           
           
           
           
     }      
     
     
     
          else if (temp > 30 && temp < 39) {
         temp = line - (summaryline +32);

           if (temp == 0) {
         buffer[10]=((align_text/10)+3)<<3;   
         buffer[11]=((align_text%10)+3)<<3;             
           }
           
          
           else {
           _delay_loop_1(19);    
           
         buffer[0]=('T'-64)<<3;   
         buffer[1]=('E'-64)<<3;   
         buffer[2]=('X'-64)<<3;   
         buffer[3]=('T'-64)<<3;   
         buffer[4]=(0)<<3;   
         buffer[5]=('A'-64)<<3;   
         buffer[6]=('L'-64)<<3;   
         buffer[7]=('I'-64)<<3;   
         buffer[8]=('G'-64)<<3;   
         buffer[9]=('N'-64)<<3;   

          if (menupos == 4) {
        SPDR = 0b11111100; //numbers[0+(temp)];
           _delay_loop_1(3);       
          }
          else {
        SPDR = 0b00000000;
           _delay_loop_1(3);       
          }       
                            
        DimOn;                    
        for (unsigned char ij=0;ij<10;ij++) {
        SPDR = letters[buffer[ij]+(temp)];       
        _delay_loop_1(2);  
        }  
        

         _delay_loop_1(15);  
        SPDR = numbers[buffer[10]+(temp)];
        delay15
        SPDR = numbers[buffer[11]+(temp)];
        delay14
        
        DimOff;
           
          }
           
     }


     else if (temp > 40 && temp < 49) {
         temp = line - (summaryline +42);
           _delay_loop_1(18);     
           
         buffer[0]=('P'-64)<<3;   
         buffer[1]=('L'-64)<<3;   
         buffer[2]=('A'-64)<<3;   
         buffer[3]=('N'-64)<<3;   
         buffer[4]=('E'-64)<<3;   
         buffer[5]=('P'-64)<<3;   
         buffer[6]=('O'-64)<<3;   
         buffer[7]=('S'-64)<<3;   
         buffer[8]=(0)<<3;   
         buffer[9]=(0)<<3;   

          if (menupos == 5) {
        SPDR = 0b11111100; //numbers[0+(temp)];
           _delay_loop_1(3);       
          }
          else {
        SPDR = 0b00000000;
           _delay_loop_1(3);       
          }       
                            
        DimOn;                    
        for (unsigned char ij=0;ij<8;ij++) {
        SPDR = letters[buffer[ij]+(temp)];       
        _delay_loop_1(2);          
        }  

         _delay_loop_1(32);          
        buffer[8]=(show_plane_pos+3)<<3;
        SPDR = numbers[buffer[8]+(temp)];
        delay14           
        DimOff
           
           
           
     }



     else if (temp > 50 && temp < 59) {
         temp = line - (summaryline +52);
           _delay_loop_1(16);     

         buffer[0]=('S'-64)<<3;   
         buffer[1]=('E'-64)<<3;   
         buffer[2]=('T'-64)<<3;   
         buffer[3]=(0)<<3;   
         buffer[4]=('A'-64)<<3;   
         buffer[5]=('L'-64)<<3;   
         buffer[6]=('A'-64)<<3;   
         buffer[7]=('R'-64)<<3;   
         buffer[8]=('M'-64)<<3;   
         buffer[9]=('S'-64)<<3;   

          if (menupos == 6) {
        SPDR = 0b11111100; //numbers[0+(temp)];
           _delay_loop_1(3);       
          }
          else {
        SPDR = 0b00000000;
           _delay_loop_1(3);       
          }       
                            
        DimOn;                    
        for (unsigned char ij=0;ij<10;ij++) {
        SPDR = letters[buffer[ij]+(temp)];       
        _delay_loop_1(2);          
        }  
        _delay_loop_1(2);              
        DimOff
           
           
     }


     else if (temp > 60 && temp < 69) {
         temp = line - (summaryline +62);
           _delay_loop_1(18);     
           
           
         buffer[0]=('E'-64)<<3;   
         buffer[1]=('X'-64)<<3;   
         buffer[2]=('I'-64)<<3;   
         buffer[3]=('T'-64)<<3;   
         buffer[4]=(0)<<3;            


          if (menupos == 7) {
        SPDR = 0b11111100; //numbers[0+(temp)];
           _delay_loop_1(3);       
          }
          else {
        SPDR = 0b00000000;
           _delay_loop_1(3);       
          }       
                            
        DimOn;                    
        for (unsigned char ij=0;ij<4;ij++) {
        SPDR = letters[buffer[ij]+(temp)];       
        _delay_loop_1(5);          
        }  
        DimOff;
           
           
           
     }            
       
       
       }
       
       if (menu == 2) {
         
         
         
         
         
temp = line - (summaryline +1);  
           
           if (temp < 8) {



if (temp == 0) {

         buffer[0]=('A'-64)<<3;   
         buffer[1]=('L'-64)<<3;   
         buffer[2]=('T'-64)<<3;   
         buffer[3]=(0)<<3;   
         buffer[4]=('A'-64)<<3;   
         buffer[5]=('L'-64)<<3;   
         buffer[6]=('A'-64)<<3;   
         buffer[7]=('R'-64)<<3;   
         buffer[8]=('M'-64)<<3;   
         buffer[9]=(0)<<3; 
}

      else {
         _delay_loop_1(50);   
          if (menupos == 1) {
        SPDR = 0b11111100; //numbers[0+(temp)];
           _delay_loop_1(3);       
          }
          else {
        SPDR = 0b00000000;
           _delay_loop_1(3);       
          }       
                            
        DimOn;                    
        for (unsigned char ij=0;ij<10;ij++) {
        SPDR = letters[buffer[ij]+(temp)];       
        _delay_loop_1(2);               
        }  

        _delay_loop_1(10);  
        for (unsigned char ij=0;ij<4;ij++) {
        SPDR = numbers[GPSbuffer[ij]+(temp)];       
        _delay_loop_1(4);                  
        }
        _delay_loop_1(3);  
        DimOff;
      }
          
         
       }
       
     else if (temp > 10 && temp < 19) {
         temp = line - (summaryline +12);
           _delay_loop_1(37);     
           
           
         buffer[0]=('L'-64)<<3;   
         buffer[1]=('O'-64)<<3;   
         buffer[2]=('S'-64)<<3;   
         buffer[3]=(0)<<3;   
         buffer[4]=('A'-64)<<3;   
         buffer[5]=('L'-64)<<3;   
         buffer[6]=('A'-64)<<3;   
         buffer[7]=('R'-64)<<3;   
         buffer[8]=('M'-64)<<3;   
         buffer[9]=(0)<<3;

          if (menupos == 2) {
        SPDR = 0b11111100; //numbers[0+(temp)];
           _delay_loop_1(3);       
          }
          else {
        SPDR = 0b00000000;
           _delay_loop_1(3);       
          }       
                            
        DimOn;                    
        for (unsigned char ij=0;ij<9;ij++) {
        SPDR = letters[buffer[ij]+(temp)];       
           _delay_loop_1(2);               
        }  
        
        _delay_loop_1(16);  
        for (unsigned char ij=4;ij<8;ij++) {
        SPDR = numbers[GPSbuffer[ij]+(temp)];
            _delay_loop_1(4);              
        }
        _delay_loop_1(3);  
        DimOff;
           
           
           
     }


     else if (temp > 20 && temp < 29) {
         temp = line - (summaryline +22);
           _delay_loop_1(34);     
           
           
         buffer[0]=('V'-64)<<3;   
         buffer[1]=('O'-64)<<3;   
         buffer[2]=('L'-64)<<3;   
         buffer[3]=('T'-64)<<3;   
         buffer[4]=(0)<<3;   
         buffer[5]=('A'-64)<<3;   
         buffer[6]=('L'-64)<<3;   
         buffer[7]=('A'-64)<<3;   
         buffer[8]=('R'-64)<<3;   
         buffer[9]=('M'-64)<<3;   

          if (menupos == 3) {
        SPDR = 0b11111100; //numbers[0+(temp)];
           _delay_loop_1(3);       
          }
          else {
        SPDR = 0b00000000;
           _delay_loop_1(3);       
          }       
                            
        DimOn;                    
        for (unsigned char ij=0;ij<10;ij++) {
        SPDR = letters[buffer[ij]+(temp)];   
        _delay_loop_1(2);               
        }  

        _delay_loop_1(18);  
        for (unsigned char ij=9;ij<12;ij++) {
        SPDR = numbers[GPSbuffer[ij]+(temp)];       
        _delay_loop_1(4);               
        }
        _delay_loop_1(3);  
        DimOff;
           
           
           
           
     }      
     
     
     
          else if (temp > 30 && temp < 39) {
         temp = line - (summaryline +32);

           if (temp == 0) {
         buffer[9]=((align_text/10)+3)<<3;   
         buffer[10]=((align_text%10)+3)<<3;             
           }
           
          
           else {
           _delay_loop_1(31);    
           
         buffer[0]=('M'-64)<<3;   
         buffer[1]=('A'-64)<<3;   
         buffer[2]=('H'-64)<<3;   
         buffer[3]=(0)<<3;   
         buffer[4]=('A'-64)<<3;   
         buffer[5]=('L'-64)<<3;   
         buffer[6]=('A'-64)<<3;   
         buffer[7]=('R'-64)<<3;   
         buffer[8]=('M'-64)<<3;   

          if (menupos == 4) {
        SPDR = 0b11111100; //numbers[0+(temp)];
           _delay_loop_1(3);       
          }
          else {
        SPDR = 0b00000000;
           _delay_loop_1(3);       
          }       
                            
        DimOn;                    
        for (unsigned char ij=0;ij<9;ij++) {
        SPDR = letters[buffer[ij]+(temp)];       
           _delay_loop_1(2);               
        }  

        _delay_loop_1(17);  
        for (unsigned char ij=12;ij<16;ij++) {
        SPDR = numbers[GPSbuffer[ij]+(temp)];       
           _delay_loop_1(4);               
        }
        _delay_loop_1(3);
        DimOff;
           
          }
           
     }




     else if (temp > 60 && temp < 69) {
         temp = line - (summaryline +62);
           _delay_loop_1(33);     
           
           
         buffer[0]=('E'-64)<<3;   
         buffer[1]=('X'-64)<<3;   
         buffer[2]=('I'-64)<<3;   
         buffer[3]=('T'-64)<<3;   
         buffer[4]=(0)<<3;            


          if (menupos == 5) {
        SPDR = 0b11111100; //numbers[0+(temp)];
           _delay_loop_1(3);       
          }
          else {
        SPDR = 0b00000000;
           _delay_loop_1(3);       
          }       
                            
        DimOn;                    
        for (unsigned char ij=0;ij<4;ij++) {
        SPDR = letters[buffer[ij]+(temp)];              
           _delay_loop_1(4);               
        }  
        DimOff;
           
           
           
     }         
         
         


         
         
         
       }
       
       
       
       
       }

       else if (homepos ==0) {
           
            temp = line - (summaryline +1);
           _delay_loop_1(17);        
           if (temp < 8) {

           _delay_loop_1(65);                     

         buffer[0]=('S'-64)<<3;   
         buffer[1]=('A'-64)<<3;   
         buffer[2]=('T'-64)<<3;          
         
         buffer[3]=satellitesr[0]<<3;
         buffer[4]=satellitesr[1]<<3;

        DimOn;
        for (unsigned char ij=0;ij<3;ij++) {
        SPDR=letters[buffer[ij]+(temp)];
        _delay_loop_1(5);        
      }  
        
        // Writes ':'
        SPDR = numbers[104+temp];
        _delay_loop_1(10);
        
      for (unsigned char ij=3;ij<5;ij++) {
      SPDR=numbers[buffer[ij]+(temp)];
      _delay_loop_1(5);              
      }            
      _delay_loop_1(2);
        DimOff;      
        
         }
         
         
     if (temp > 10 && temp < 19) {
         temp = line - (summaryline +12);
        _delay_loop_1(45);           
       
         buffer[0]=('G'-64)<<3;   
         buffer[1]=('P'-64)<<3;   
         buffer[2]=('S'-64)<<3;          
         buffer[3]=(0)<<3;
         buffer[4]=('F'-64)<<3;   
         buffer[5]=('I'-64)<<3;   
         buffer[6]=('X'-64)<<3;           
         
         DimOn;
        for (unsigned char ij=0;ij<7;ij++) {
        SPDR=letters[buffer[ij]+(temp)];
        _delay_loop_1(2);                
        }     
        
        SPDR = numbers[104+temp];
        _delay_loop_1(6);              

       if (GPSfix > '0') {
         buffer[0]=('Y'-64)<<3;   
         buffer[1]=('E'-64)<<3;   
         buffer[2]=('S'-64)<<3;          

       }         
       
       else {
         buffer[0]=('N'-64)<<3;   
         buffer[1]=('O'-64)<<3;   
         buffer[2]=('@'-64)<<3;          

         
       }

        for (unsigned char ij=0;ij<3;ij++) {
        SPDR=letters[buffer[ij]+(temp)];
        _delay_loop_1(4);                
        }     
         _delay_loop_1(3);
        DimOff;   
         
           }
  
  
         if  (temp == 19) {
           
       test = (homeposcount *10) / set_home_delay;
       for (i=0;i<test;i++) {
       loadbar[i]=26;
        }
      // SPDR=0b11111110;        
           
         }
         
      if (temp == 20) {
        
        
       for (unsigned char ij=0;ij<9;ij++) {
         buffer[ij]=(loadbar[ij])<<3;   
        }

         buffer[9]=(28)<<3;         
       
       
         buffer[10]=('D'-64)<<3;    
         buffer[11]=('E'-64)<<3;   
         buffer[12]=('L'-64)<<3;   
         buffer[13]=('A'-64)<<3;    
         buffer[14]=('Y'-64)<<3;             
      }  
  
  
  
         if (temp > 31 && temp < 40) {
         temp = line - (summaryline +33);
         _delay_loop_1(60);  

DimOn;
for (unsigned char ij=10;ij<15;ij++) {
        SPDR = letters[buffer[ij]+(temp)];  
           _delay_loop_1(2);                
  
}
_delay_loop_1(3);


        // Writes ':'
        SPDR = numbers[104+temp];
        _delay_loop_1(9);        

        DimOff;
        

        
           }

           if (temp > 42 && temp < 51) {
             
         _delay_loop_1(37);               
         temp = line - (summaryline +44);           


        for (unsigned char ij=0;ij<10;ij++) {
        SPDR=letters[buffer[ij]+(temp)];
        DimOn;           
        _delay_loop_1(3);                     
        }     
         _delay_loop_1(1);               
        DimOff;

         }
         
         
           if (temp > 64 && temp < 73) {
         temp = line - (summaryline +66);
         _delay_loop_1(35);                  
         
// Stores all the time-numbers in a temporary buffer.   
  if (temp == 0) {
        for (unsigned char ij=0;ij<11;ij++) {
        buffer[ij]=time[ij]<<3;
        }     
  }

   
   else {      
         // Shift out first 8 bit
        
        DimOn;         
        for (unsigned char ij=0;ij<2;ij++) {
        SPDR=numbers[buffer[ij]+(temp)];
         _delay_loop_1(3);            
        }     
        


         _delay_loop_1(3);                       
         SPDR = numbers[(104)+(temp)];  

        _delay_loop_1(4);    
        for (unsigned char ij=2;ij<4;ij++) {
        SPDR=numbers[buffer[ij]+(temp)];
        _delay_loop_1(4);    
        }     
        

                  
         _delay_loop_1(3);                      
         SPDR = numbers[(104)+(temp)];
        _delay_loop_1(4);    
        for (unsigned char ij=4;ij<9;ij++) {
        SPDR=numbers[buffer[ij]+(temp)];
         _delay_loop_1(2);            
        }     


         _delay_loop_1(3);              
         DimOff;   
          }
           }   
        
        
           if (temp > 80 && temp < 89) {
         temp = line - (summaryline +82);
         _delay_loop_1(20);                 
         
         buffer[0]=('V'-64)<<3;   
         buffer[1]=('E'-64)<<3;   
         buffer[2]=('R'-64)<<3;    
         buffer[3]=('S'-64)<<3;    
         buffer[4]=('I'-64)<<3;   
         buffer[5]=('O'-64)<<3;    
         buffer[6]=('N'-64)<<3; 

         buffer[7]=(0+3)<<3;    
         buffer[8]=(1+3)<<3;   
         buffer[9]=(8+3)<<3;    

        DimOn;
        for (unsigned char ij=0;ij<7;ij++) {
        SPDR=letters[buffer[ij]+(temp)];
         _delay_loop_1(2);            
        }     
         _delay_loop_1(6);               

    
         SPDR = numbers[(buffer[7])+(temp)];
         delay15             
         SPDR = numbers[8+(temp)]; 
         delay15      
         SPDR = numbers[(buffer[8])+(temp)];
         delay15             
         SPDR = numbers[(buffer[9])+(temp)]; 
         delay15                  
         DimOff             
              
       
           }  
                 
         
         
         
         
         
        }
         
         else {
         
         if (landed == 1) {
         _delay_loop_1(25);                 
               temp = line - (summaryline +1);
               
           if (temp < 8) {
         _delay_loop_1(30);      
         buffer[0]=('M'-64)<<3;   
         buffer[1]=('A'-64)<<3;   
         buffer[2]=('X'-64)<<3;          
         
         buffer[3]=('A'-64)<<3;   
         buffer[4]=('L'-64)<<3;   
         buffer[5]=('T'-64)<<3;           
         
        
        SPDR = letters[buffer[0]+(temp)];
        DimOn;
        delay14        
        SPDR = letters[buffer[1]+(temp)];
        delay13
        SPDR = letters[buffer[2]+(temp)];
 
        
        _delay_loop_1(10);      
        SPDR = letters[buffer[3]+(temp)];
        delay15
        SPDR = letters[buffer[4]+(temp)];
        delay15
        SPDR = letters[buffer[5]+(temp)];
        delay13     

         buffer[0]=(max_altr[0])<<3;   
         buffer[1]=(max_altr[1])<<3;   
         buffer[2]=(max_altr[2])<<3;          
         buffer[3]=(max_altr[3])<<3;                
         buffer[4]=(max_altr[4])<<3;                
             
             
        SPDR = numbers[buffer[0]+(temp)];
        delay13 
        SPDR = numbers[buffer[1]+(temp)];
        delay13
        SPDR = numbers[buffer[2]+(temp)];
        delay13   
        SPDR = numbers[buffer[3]+(temp)];
        delay13         
        
        SPDR = numbers[8+(temp)];
        delay13         
        
        SPDR = numbers[buffer[4]+(temp)];
        delay13              
        DimOff; 
        
         }
           
           if (temp > 10 && temp < 19) {
         temp = line - (summaryline +11);
        _delay_loop_1(23);           

 
         buffer[0]=('M'-64)<<3;   
         buffer[1]=('A'-64)<<3;   
         buffer[2]=('X'-64)<<3;          
         
         buffer[3]=('S'-64)<<3;   
         buffer[4]=('P'-64)<<3;   
         buffer[5]=('D'-64)<<3;           
         
        
        SPDR = letters[buffer[0]+(temp)];
        DimOn;       
        delay13
        SPDR = letters[buffer[1]+(temp)];
        delay13
        SPDR = letters[buffer[2]+(temp)];
 
        
        _delay_loop_1(10);      
        SPDR = letters[buffer[3]+(temp)];
        delay15
        SPDR = letters[buffer[4]+(temp)];
        delay15
        SPDR = letters[buffer[5]+(temp)];
        delay13 
        
        
         buffer[0]=(max_speedr[0])<<3;   
         buffer[1]=(max_speedr[1])<<3;   
         buffer[2]=(max_speedr[2])<<3;          
         buffer[3]=(max_speedr[3])<<3;                
             
        _delay_loop_1(2);                                 
        delay1
        
        SPDR = numbers[buffer[0]+(temp)];
        delay13
        SPDR = numbers[buffer[1]+(temp)];
        delay13
        SPDR = numbers[buffer[2]+(temp)];
        delay15
        SPDR = numbers[8+(temp)];   
        delay13        
        SPDR = numbers[buffer[3]+(temp)];
        delay13  
        DimOff;       
         
           }
           
           if (temp > 20 && temp < 29) {
         temp = line - (summaryline +21);
         _delay_loop_1(19);  


         buffer[0]=('M'-64)<<3;   
         buffer[1]=('A'-64)<<3;   
         buffer[2]=('X'-64)<<3;          
         
         buffer[3]=('L'-64)<<3;   
         buffer[4]=('O'-64)<<3;   
         buffer[5]=('S'-64)<<3;           
         
        
        SPDR = letters[buffer[0]+(temp)];
        DimOn;        
        delay13
        SPDR = letters[buffer[1]+(temp)];
        delay13
        SPDR = letters[buffer[2]+(temp)];
 
        
        _delay_loop_1(10);      
        SPDR = letters[buffer[3]+(temp)];
        delay15
        SPDR = letters[buffer[4]+(temp)];
        delay15
        SPDR = letters[buffer[5]+(temp)];
        delay13         
             
         buffer[0]=(max_losr[0])<<3;   
         buffer[1]=(max_losr[1])<<3;   
         buffer[2]=(max_losr[2])<<3;          
         buffer[3]=(max_losr[3])<<3;                
             
        _delay_loop_1(2);                    
        delay2
        
        SPDR = numbers[buffer[0]+(temp)];
        delay13
        SPDR = numbers[buffer[1]+(temp)];
        delay13
        SPDR = numbers[buffer[2]+(temp)];
        delay13   
        SPDR = numbers[buffer[3]+(temp)];
        delay13             
        DimOff; 
        
           }           

           if (temp > 31 && temp < 40) {
         temp = line - (summaryline +32);
         _delay_loop_1(15);
         delay1
         
         buffer[0]=('T'-64)<<3;   
         buffer[1]=('O'-64)<<3;   
         buffer[2]=('T'-64)<<3;          
         
         buffer[3]=('D'-64)<<3;   
         buffer[4]=('I'-64)<<3;   
         buffer[5]=('S'-64)<<3;           
         
        
        SPDR = letters[buffer[0]+(temp)];
        DimOn;        
        delay9
        SPDR = letters[buffer[1]+(temp)];
        delay15
        SPDR = letters[buffer[2]+(temp)];
 
        
        _delay_loop_1(10);      
        SPDR = letters[buffer[3]+(temp)];
        delay15      
        SPDR = letters[buffer[4]+(temp)];
        delay15
        SPDR = letters[buffer[5]+(temp)];
        delay13 


         buffer[0]=(total_distancer[0])<<3;   
         buffer[1]=(total_distancer[1])<<3;   
         buffer[2]=(total_distancer[2])<<3;          
         buffer[3]=(total_distancer[3])<<3;                
         buffer[4]=(total_distancer[4])<<3;          
             
        _delay_loop_1(1);                    
        delay1
        
        SPDR = numbers[buffer[0]+(temp)];
        delay13
        SPDR = numbers[buffer[1]+(temp)];
        delay13

        SPDR = numbers[buffer[2]+(temp)];
        delay13   
        SPDR = numbers[buffer[3]+(temp)];
        delay14     
        SPDR = numbers[buffer[4]+(temp)];
        delay13             
        DimOff; 

      
           }           
           
           if (temp > 42 && temp < 51) {
         temp = line - (summaryline +43);
         _delay_loop_1(14);                  

         
         buffer[0]=('T'-64)<<3;   
         buffer[1]=('I'-64)<<3;   
         buffer[2]=('M'-64)<<3;          
         buffer[3]=('E'-64)<<3;   
          
         
        
        SPDR = letters[buffer[0]+(temp)];
        DimOn;        
        delay13
        SPDR = letters[buffer[1]+(temp)];
        delay13
        SPDR = letters[buffer[2]+(temp)];
        delay15   
        SPDR = letters[buffer[3]+(temp)];
        delay13

         buffer[0]=(flight_timer[0])<<3;   
         buffer[1]=(flight_timer[1])<<3;   
         buffer[2]=(flight_timer[2])<<3;          
         buffer[3]=(flight_timer[3])<<3;                
             
        _delay_loop_1(20);
        delay2        

        
        SPDR = numbers[buffer[0]+(temp)];
        delay13
        SPDR = numbers[buffer[1]+(temp)];
        delay13
        
        SPDR = numbers[104+(temp)];
        delay13
        
        
        SPDR = numbers[buffer[2]+(temp)];
        delay13   
        SPDR = numbers[buffer[3]+(temp)];
        delay13      
        DimOff; 

           }           
           
           if (temp > 53 && temp < 62) {
         temp = line - (summaryline +54);
         _delay_loop_1(9);                  
         
         buffer[0]=('A'-64)<<3;   
         buffer[1]=('V'-64)<<3;   
         buffer[2]=('G'-64)<<3;          
         
         buffer[3]=('S'-64)<<3;   
         buffer[4]=('P'-64)<<3;   
         buffer[5]=('D'-64)<<3;           
         
        
        SPDR = letters[buffer[0]+(temp)];
        DimOn;        
        delay11
        SPDR = letters[buffer[1]+(temp)];
        delay15
        SPDR = letters[buffer[2]+(temp)];
 
        
        _delay_loop_1(10);      
        SPDR = letters[buffer[3]+(temp)];
        delay15
        SPDR = letters[buffer[4]+(temp)];
        delay15
        SPDR = letters[buffer[5]+(temp)];
        delay13 
        
        
         buffer[0]=(avg_speedr[0])<<3;   
         buffer[1]=(avg_speedr[1])<<3;   
         buffer[2]=(avg_speedr[2])<<3;          
         buffer[3]=(avg_speedr[3])<<3;                
             
        _delay_loop_1(1);                    
        delay2
        
        SPDR = numbers[buffer[0]+(temp)];
        delay13
        SPDR = numbers[buffer[1]+(temp)];
        delay13
        
        SPDR = numbers[buffer[2]+(temp)];
        delay13
        
        SPDR = numbers[8+(temp)];
        delay13        
        
        SPDR = numbers[buffer[3]+(temp)];
        delay13      
        DimOff;         
        
           }

           if (temp > 64 && temp < 73 && 1==0) {
         temp = line - (summaryline +65);
         _delay_loop_1(4);         
                  
         buffer[0]=('@'-64)<<3;   
         buffer[1]=('@'-64)<<3;   
         buffer[2]=('@'-64)<<3;          
         
         buffer[3]=('@'-64)<<3;   
         buffer[4]=('@'-64)<<3;   
         buffer[5]=('@'-64)<<3;           
         
        
        SPDR = letters[buffer[0]+(temp)];
        DimOn;        
        delay13
        SPDR = letters[buffer[1]+(temp)];
        delay13
        SPDR = letters[buffer[2]+(temp)];
 
        
        _delay_loop_1(10);      
        SPDR = letters[buffer[3]+(temp)];
        delay13
        SPDR = letters[buffer[4]+(temp)];
        delay15
        SPDR = letters[buffer[5]+(temp)];
        delay13 
        DimOff;         

           }           
           
           if (temp > 75 && temp < 84 && 1==0) {
         temp = line - (summaryline +76);
         
         buffer[0]=('@'-64)<<3;   
         buffer[1]=('@'-64)<<3;   
         buffer[2]=('@'-64)<<3;          
         
         buffer[3]=('@'-64)<<3;   
         buffer[4]=('@'-64)<<3;   
         buffer[5]=('@'-64)<<3;           
         
        
        SPDR = letters[buffer[0]+(temp)];
        DimOn;        
        delay13
        SPDR = letters[buffer[1]+(temp)];
        delay13
        SPDR = letters[buffer[2]+(temp)];
 
        
        _delay_loop_1(10);      
        SPDR = letters[buffer[3]+(temp)];
        delay15
        SPDR = letters[buffer[4]+(temp)];
        delay15
        SPDR = letters[buffer[5]+(temp)];
        delay13 
        DimOff; 
        
           }             
           
         }
         
         
        }
       }      
 #endif     
#if defined(summaryline)      
else
#endif
#if defined(gps_nmea_line)
   if (line > gps_nmea_line  && line < (gps_nmea_line +9)) {

     // Used to align the text
     _delay_loop_1(align_text);     
       
     
     if (line == (gps_nmea_line+1)) {
     if (altitude_num2 < show_gps_coordinates_altitude*10  | flight_timer[3] % show_gps_coordinates_second == 0) {

    // _delay_loop_1(22);
         showcoordinates=1;         
     }
     
     else {
         showcoordinates=0; 
     }
  
     }
     
     else if (showcoordinates == 1) {
           _delay_loop_1(5);
         buffer[0]=(latitude[0]-45)<<3;
         buffer[1]=(latitude[1]-45)<<3;
         buffer[2]=(latitude[2]-45)<<3;
         buffer[3]=(latitude[3]-45)<<3;
         buffer[4]=(latitude[4]-45)<<3;         
         buffer[5]=(latitude[5]-45)<<3;
         buffer[6]=(latitude[6]-45)<<3;
         buffer[7]=(latitude[7]-45)<<3;         
         buffer[8]=(latitude[8]-45)<<3;                  
         buffer[9]=(latitude[9]-45)<<3;        
         
         temp = line - (gps_nmea_line+1);
         
         DimOn;
for (unsigned char ij = 0; ij < 10; ij++) {
         SPDR = numbers[(buffer[ij])+(temp)];
           _delay_loop_1(2);
}  

         buffer[10]=(latitude_dir)<<3;     
         SPDR = letters[(buffer[10])+(temp)];
                delay13      
          DimOff;


//     _delay_loop_1(8);
         buffer[0]=(longitude[0]-45)<<3;
         buffer[1]=(longitude[1]-45)<<3;
         buffer[2]=(longitude[2]-45)<<3;
         buffer[3]=(longitude[3]-45)<<3;
         buffer[4]=(longitude[4]-45)<<3;         
         buffer[5]=(longitude[5]-45)<<3;
         buffer[6]=(longitude[6]-45)<<3;
         buffer[7]=(longitude[7]-45)<<3;         
         buffer[8]=(longitude[8]-45)<<3;                  
         buffer[9]=(longitude[9]-45)<<3;                                  

   DimOn;  
for (unsigned char ij = 0; ij < 10; ij++) {
         SPDR = numbers[(buffer[ij])+(temp)];
           _delay_loop_1(2);
}           
       
         buffer[10]=(longitude_dir)<<3;       
         SPDR = letters[(buffer[10])+(temp)];
                delay13                
             DimOff;
             
     
             
     }
   }
#endif

#if defined(gps_nmea_line)
else
#endif

#if defined(toplinenumbers)
if (line == toplinenumbers) {
         
         
         if (speedkmw[0]==3 && speedkmw[1]==3) {
         buffer3[0]=speedkmw[2]<<5;   
         buffer3[1]=1<<5;
         buffer3[2]=speedkmw[3]<<5;    
         buffer3[3]=14<<5;
         buffer3[4]=14<<5;
          
         }
         
         else if (speedkmw[0]==3) {
         buffer3[0]=speedkmw[1]<<5;
         buffer3[1]=speedkmw[2]<<5;   
         buffer3[2]=1<<5;
         buffer3[3]=speedkmw[3]<<5;  
         buffer3[4]=14<<5;
         
         if (show_decimals == 0) {
         buffer3[2]=14<<5;
           }
  
         }
         
         else {
         buffer3[0]=speedkmw[0]<<5;
         buffer3[1]=speedkmw[1]<<5;
         buffer3[2]=speedkmw[2]<<5;   
         buffer3[3]=1<<5;
         buffer3[4]=speedkmw[3]<<5;          
         }
         
         
         buffer3[5]=losr[0]<<5;
         buffer3[6]=losr[1]<<5;
         buffer3[7]=losr[2]<<5;   
         buffer3[8]=losr[3]<<5;
         
        if (losr[0] == 3 && losr[1] == 3) {
         buffer3[5]=14<<5;
         buffer3[6]=losr[2]<<5;
         buffer3[7]=losr[3]<<5;   
         buffer3[8]=14<<5;
        }       
        
        else if (losr[0] == 3) {
         buffer3[5]=14<<5;
         buffer3[6]=losr[1]<<5;
         buffer3[7]=losr[2]<<5;   
         buffer3[8]=losr[3]<<5;
        }

  if (altitude_offset_on ==0) {
        if (altitude2[3] == 14) {
         buffer3[9] =14<<5;    
         buffer3[10]=14<<5;         
         buffer3[11]=14<<5;        
         buffer3[12]=altitude2[0]<<5;                
         buffer3[13]=altitude2[1]<<5;
         buffer3[14]=altitude2[2]<<5;   
        }
        
        else if (altitude2[4] == 14) {
         buffer3[9] =14<<5;    
         buffer3[10]=14<<5;         
         buffer3[11]=altitude2[0]<<5;        
         buffer3[12]=altitude2[1]<<5;                
         buffer3[13]=altitude2[2]<<5;
         buffer3[14]=altitude2[3]<<5;   
        }       
       
         else if (altitude2[5] == 14) {
         buffer3[9] =14<<5;    
         buffer3[10]=altitude2[0]<<5;         
         buffer3[11]=altitude2[1]<<5;        
         buffer3[12]=altitude2[2]<<5;                
         buffer3[13]=altitude2[3]<<5;
         buffer3[14]=altitude2[4]<<5;   
        }  
        
         else  {
         buffer3[9] =altitude2[0]<<5;    
         buffer3[10]=altitude2[1]<<5;         
         buffer3[11]=altitude2[2]<<5;        
         buffer3[12]=altitude2[3]<<5;                
         buffer3[13]=altitude2[4]<<5;
         buffer3[14]=altitude2[5]<<5;
        }
        
  }
  else {


        if (altituder[0] == 3 && altituder[1] == 3 && altituder[2]==3 ) {
         buffer3[9] =14<<5;    
         buffer3[10]=14<<5;         
         buffer3[11]=14<<5;        
         buffer3[12]=altituder[3]<<5;                
    //     buffer3[13]=altituder[3]<<5;
         buffer3[14]=altituder[4]<<5;   
        }
        
        else if (altituder[0] == 3 && altituder[1] == 3) {
         buffer3[9] =14<<5;    
         buffer3[10]=14<<5;         
         buffer3[11]=altituder[2]<<5;        
         buffer3[12]=altituder[3]<<5;                
   //      buffer3[13]=altituder[3]<<5;
         buffer3[14]=altituder[4]<<5;   
        }       
       
         else if (altituder[0] == 3) {
         buffer3[9] =14<<5;    
         buffer3[10]=altituder[1]<<5;         
         buffer3[11]=altituder[2]<<5;        
         buffer3[12]=altituder[3]<<5;                
  //       buffer3[13]=altituder[3]<<5;
         buffer3[14]=altituder[4]<<5;   
        }  
        
         else  {
         buffer3[9] =altituder[0]<<5;    
         buffer3[10]=altituder[1]<<5;         
         buffer3[11]=altituder[2]<<5;        
         buffer3[12]=altituder[3]<<5;                
//       buffer3[13]=altituder[4]<<5;
         buffer3[14]=altituder[4]<<5;
        }
       
         buffer3[13]=1<<5;
         
       if (altitude_negative ==1) {
         buffer3[9] =13<<5;              
        }         
         
  }
}
 #endif        
// ============================================================
// Buttom line text
// ============================================================

#if defined(toplinenumbers)
else
#endif

#if defined(update_buffers)
if (line == update_buffers ) {   
         
         buffer2[0]=voltager[0]<<5;
         buffer2[1]=voltager[2]<<5;
         buffer2[2]=voltager[3]<<5;  

         buffer2[3]=voltager2[0]<<5;
         buffer2[4]=voltager2[2]<<5;
         buffer2[5]=voltager2[3]<<5; 

         buffer2[6]=voltager3[0]<<5;
         buffer2[7]=voltager3[2]<<5;
         buffer2[8]=voltager3[3]<<5; 

         temp = (arrowr[0]-3)*100+(arrowr[1]-3)*10+(arrowr[0]-3);      

// Determine what way the arrow should point
           for (i=0;i<8;i++) {
            if (temp < (23+45*i)) {
              arrowd = i;
              break;
            } 
           }
            
            if ( temp > 360-23) { arrowd =0;}     
}
#endif

        
// ============================================================
// Buttom line text END
// ============================================================
          
       
       
// As a quick and dirty implementation the timing from the video-signal
// is used to calculate the power consumption (mAh). But if it looses sync you
// wan't even be able to see any text - so this should de fine.
// Maybe not the best way to do it, but this way I know when it does what. 
// ============================================================
// Current sensor
// ============================================================ 

// As the calculations takes quite a while they will be done after last line with text. 
// Otherwise the text will "jump a bit". We might miss a line or two - but as it is in
// the buttom of the screen where we don't need text, it doesn't really matter. 
#if defined(updatebuffers)
else
#endif
      if (line == current_calc_line) {
        loopcount++;

// With 50 FPS, this will give an update-rate of 5 hz. (with odd/even lines 10 hz)        
        if (loopcount == 10) {
          loopcount=0;
        } 
        
     
         // with 10 bit ADC and 5 volt ref coltage we have;
         // (with 50 A current sensor)
         // 1024/5 = 205 = 1 volt = 10 A
         // First the ADC is set to take a reading;
         
        if (loopcount == 0) {
      ADCtemp=ADCL; 
      ADCtemp2=ADCH;
      ADCreal=ADCtemp+(ADCtemp2<<8);
      bat_volt=ADCreal*voltage_1s;
         }

         if (loopcount == 1) {
           voltager[0]= (bat_volt / 100)+3;
           voltager[1]= 1; // Writes the dot. Should only be done once. 
           voltager[2]= ((bat_volt % 100) / 10)+3;
           voltager[3]= ((bat_volt % 100) % 10)+3; 
         }         
     
         if (loopcount == 2) {
            mux_batVoltage2
            ADCSRA|=(1<<ADSC); 
         }
         
        if (loopcount == 3) {
      ADCtemp=ADCL; 
      ADCtemp2=ADCH;
      ADCreal=ADCtemp+(ADCtemp2<<8);
      bat_volt2=ADCreal*voltage_2s-bat_volt;
         }

         if (loopcount == 4) {
           voltager2[0]= (bat_volt2 / 100)+3;
           voltager2[1]= 1; // Writes the dot. Should only be done once. 
           voltager2[2]= ((bat_volt2 % 100) / 10)+3;
           voltager2[3]= ((bat_volt2 % 100) % 10)+3; 
         }         
     
         if (loopcount == 5) {
            mux_batVoltage3
            ADCSRA|=(1<<ADSC); 
         }
            if (loopcount == 6) {
      ADCtemp=ADCL; 
      ADCtemp2=ADCH;
      ADCreal=ADCtemp+(ADCtemp2<<8);
      bat_volt3=ADCreal*voltage_3s-bat_volt2-bat_volt;
         }

         if (loopcount == 7) {
           voltager3[0]= (bat_volt3 / 100)+3;
           voltager3[1]= 1; // Writes the dot. Should only be done once. 
           voltager3[2]= ((bat_volt3 % 100) / 10)+3;
           voltager3[3]= ((bat_volt3 % 100) % 10)+3; 
         }         
     
         if (loopcount == 8) {
            mux_batVoltage
            ADCSRA|=(1<<ADSC); 
         }
                    
           if (loopcount == 9) {
           //na razie nic
         }                  
         
            
       }
// ============================================================
// Current sensor END

      // Increase line count..
   line++;

   // Let's make sure SPI is not idling high.
   SPDR=0b00000000;      
          
}


