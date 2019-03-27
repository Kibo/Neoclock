#include <SoftwareSerial.h>

#define RX 3
#define TX 2
SoftwareSerial hc06( TX, RX );

String cmd="";

void setup(){  
 hc06.begin(9600); 
}

void loop(){  
  readBlueToothCommand();  
  delay(100); 
}

void readBlueToothCommand(){
   //Read data from HC06
 while(hc06.available()>0){
   cmd+=(char)hc06.read();
 }
  
   if(cmd!=""){ 
     Serial.print("Command recieved : ");
     Serial.println(cmd);
  
     if(cmd == "gt"){                                   
        hc06.println( "Now : " + getTime() );            
        
     }else if(cmd.startsWith("st")){                                   
         hc06.println( "Set time: " + cmd );                     
         hc06.println( "Now : " + String(parseHours(cmd)) + ":" + String(parseMinutes(cmd)));            
           
     }else if(cmd.startsWith("sa")){
         hc06.println( "Set alarm: " + cmd );        
         hc06.println( "Alarm : " + String(parseHours(cmd)) + ":" + String(parseMinutes(cmd))); 

     }else if(cmd.startsWith("ss")){                                   
         hc06.println( "Set song: " + cmd );                     
         hc06.println( "Alarm song: " + String(parseCmd(cmd))); 
         
     }else if(cmd.startsWith("ps")){                                   
         hc06.println( "Play song: " + cmd );                     
         hc06.println( "Playing: " + String(parseCmd(cmd))); 

    }else if(cmd.startsWith("sb")){                                   
         hc06.println( "Set brihtness: " + cmd );                     
         hc06.println( "Brightness: " + String(parseCmd(cmd)));
            
    }else{
         Serial.println("Help");
         hc06.println("Commands:");
         hc06.println("gt - get time, show current time");
         hc06.println("st1206 - set time, 4 digit");
         hc06.println("sa0502 - set alarm, 4 digit");    
         hc06.println("ss2 - set alarm song, 0 - songs number");
         hc06.println("ps1 - play song, play alarm song 1");         
         hc06.println("sb100 - set brightness, 0 - 200");
     }
     cmd=""; //reset cmd
  }
}

int parseHours(String cmd){
  return cmd.substring(2).substring(0,2).toInt();
}

int parseMinutes(String cmd){
  return cmd.substring(2).substring(2).toInt();
}

int parseCmd(String cmd){
  return cmd.substring(2).toInt();
}

/**
 * Mock method
 */
String getTime(){
  return String(18) + ":" + String(12) + ":" + String(54);
}
