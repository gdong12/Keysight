
#include "mbed.h"
#include "SDFileSystem.h"
#include "wave_player.h"
#include "TextLCD.h"
#include <vector>
#include <string>
#include "PinDetect.h"

vector <string> filenames;
TextLCD lcd(p22, p23, p24, p25, p26, p27); 
SDFileSystem sd(p5, p6, p7, p8, p9, "sd"); //SD card

string fileName;
string wavestring;
const char *input;
vector<string>::iterator it;
bool playing = false;
int volume = 16;
FILE *wave_file;

AnalogOut DACout(p18);

wave_player waver(&DACout);

DigitalOut myLED1(LED1);

PinDetect pb1(p28);
PinDetect pb2(p29);
PinDetect pb3(p30);
PinDetect pb4(p21);

void read_file_names(char *dir) 
{ 
    DIR *dp; 
    struct dirent *dirp; 
    dp = opendir(dir); 
    //read all directory and file names in current directory into filename vector 
    while((dirp = readdir(dp)) != NULL) { 
         filenames.push_back(string(dirp->d_name)); 
    } 
} 

void pb1_hit_callback (void)
{
  if(playing) {
    playing = false;
    waver.stop();
  }
  else {
    playing = true;
  }
}

void pb2_hit_callback (void) //decrease
{
    if(it == filenames.begin()) {
        it = filenames.end()-1;
    }
    
    else
        it--;
}

void pb3_hit_callback (void) //increase
{
    if(it == filenames.end()-1) {
        it = filenames.begin();
    }
    
    else
        it++;
}

void pb4_hit_callback (void)
{
    waver.setVolume();
}



int main()
{
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    pb4.mode(PullUp);
    
    wait(.01);
    // Setup Interrupt callback functions for a pb hit
    pb1.attach_deasserted(&pb1_hit_callback);
    pb2.attach_deasserted(&pb2_hit_callback);
    pb3.attach_deasserted(&pb3_hit_callback);
    pb4.attach_deasserted(&pb4_hit_callback);
    // Start sampling pb inputs using interrupts
    pb1.setSampleFrequency();
    pb2.setSampleFrequency();
    pb3.setSampleFrequency();
    pb4.setSampleFrequency();
       
    while (!sd.SD_inserted())
    {
        lcd.cls();
        lcd.locate(0, 0);
        lcd.printf("Insert SD Card");
        wait(1);
    }
    wait(1);
    sd.disk_initialize();
    
    read_file_names("/sd/myMusic"); 
    it=filenames.begin();
    
    while(1) {
      if(playing) {     
        fileName = (*it).c_str();
        wavestring = "/sd/myMusic/" + fileName;
        input = wavestring.c_str();
        
        lcd.cls();
        lcd.locate(0,0);
        lcd.printf((*it).substr(0, (*it).length()-4).c_str());
        lcd.locate(0,1);
        lcd.printf("Song Playing");
        
        wave_file=fopen(input,"r");
        waver.play(wave_file);
        fclose(wave_file);
      }
      
      else {
        lcd.cls();
        lcd.locate(0,0);
        lcd.printf((*it).substr(0, (*it).length()-4).c_str());
      }
    
      wait(1);
                // heartbeat LED - common debug tool
                // blinks as long as code is running and not locked up
      myLED1=!myLED1;
    }
}