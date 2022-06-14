   // POC-CAR with  DUAL H-BRIDGE L-298N  (2 motors) and BLUETOOTH            MMartin 27Dec2016 final installation of motors and bluetooth
//                                                                         MMartin 11Feb2017 installation of 2 ultrasonic detectors
//                                                                         MMartin 29Marchd2022
//  THIS PROGRAM IS INTENDED For  POCCAR connected to Arduino/Genuino UNO
//The  Arduino compiler options for POCCAR  are:  Arduino / Genuino UNO    controller: avrisp.mkll


//Compiling and Upload  select the following options in  the Tools menu:
//   Board:  Arduino/genuino 1
//   Programmmer:    AVRISP.dll
//select the available port in Menu:
//          Tools / Port  / COM?? Arduino/Genuino Uno


// MOTOR CONFIGURATION in POCCAR
// THE MOTORS ARE CONTROLLED BY ARDUINO's DIGITAL PINS (4 and 5)  and (6 and 7 )
// THE MOTORS AVAILABLE DO NOT HAVE SPEED CONTROL   
// NOTE: JUMPER configuration in H-BRIDGE: The 12V_JUMPER, and the other two  JUMPER of the H-BRIDGE board are present and connected
// Power supply used for H-BRIDGE are 4 bateries of 1.5 V





#include <SoftwareSerial.h>



//Keyboard Controls :
// "y" -stop motor forward/backwards
// "u" -stop motor wheels
// "3" -Avance  non-stop
// "0" -Reverse  non-stop
// "5" -Left   non-stop
// "6" -Right  non-stop
// "t" - stop all motions 
// "a" - AGUA


// "1" -Maneuver-forward-LEFT  90
// "2" -Maneuver-forward-RIGHT 90







// "9" -Center-wheels
// "m" -Luces
// "b" -Avance LONG
// "c" -Reverse LONG
// "d" -Left  LONG
// "e" -Right  LONG
// "f" -active STOP anti-forward
// "g" -active STOP anti-reverse
// "h" -LEFT-FULL
// "i" -RIGHT-FULL
// "r" -Leer sensor humedad
//BLUETOOTH PINS
SoftwareSerial Bluetooth(10, 9); // RX, TX
int delaystability=100;           //Bluetooth delay stability for transmision  100 ms




// Declare L298N Dual H-Bridge Motor Controller directly since there is not a library to load.

// Motor 1   AVANCE/REVERSE
int dir1PinA = 4;
int dir2PinA = 5;
int delayactivestop1=10;



// Motor 2   LEFT/RIGHT
int dir1PinB = 6;
int dir2PinB = 7;
int delayactivestop2=1;




//MANEUBRE LEFT90  
int cyclesmaneubreleft90=2; 
int avancedelay=880;   //delay for avance maneubre LEFT90   calibrated 27Dec2016  
int reversedelay=940;  // delay for reverse maneubre LEFT90    calibrated 27Dec2016

//MANEUBRE RIGHT90  
int cyclesmaneubreright90=2; 
int avancedelay2=920;   //delay for avance maneubre RIGHT90     calibrated 27Dec2016
int reversedelay2=860;  // delay for reverse maneubre RIGHT90  calibrated 27Dec2016




//AGUA
int dirPinagua = 11;  

//////////////////////////////////////////////////////////////////////

void centraruedas()             //calibrated 27Dec2016
{

                              //centering wheels                          //FULL-RIGHT WHEELS
                                      digitalWrite(dir1PinB, HIGH);
                                      digitalWrite(dir2PinB, LOW);
                                      delay(200);                       // wait 0.2s

                                      digitalWrite(dir1PinB, LOW);
                                      digitalWrite(dir2PinB, LOW);
                                      delay(100);        
                                                                        //MIDDLE-LEFT WHEELS
                                      digitalWrite(dir1PinB, LOW);
                                      digitalWrite(dir2PinB, HIGH);
                                      delay(85);                       // wait 

                                      digitalWrite(dir1PinB, LOW);
                                      digitalWrite(dir2PinB, LOW);
                                      delay(100);        

}


void setup() {  // Setup runs once per reset

         
           pinMode(dirPinagua,OUTPUT);           
            Bluetooth.begin(9600);   //Bluetooth conection
 

            
            
            Bluetooth.println("Hello, world Bluetooth.  Send  numbers 1 to 4 to move POC-CAR");
            
            
            
           
            
            //Define L298N Dual H-Bridge Motor Controller Pins
            
            pinMode(dir1PinA,OUTPUT);
            pinMode(dir2PinA,OUTPUT);
            pinMode(dir1PinB,OUTPUT);
            pinMode(dir2PinB,OUTPUT);


            // BLINKING LED 
            pinMode(LED_BUILTIN, OUTPUT);
            digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(500);                       // wait for a second
            digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
            delay(500);                       // wait for a second
           

            pinMode(A2, OUTPUT); /*activación del pin A0 como salida: para el pulso ultrasónico    "TRIG2" */
            pinMode(A3, INPUT); /*activación del pin A1 como entrada: tiempo del rebote del ultrasonido   "ECHO2""*/



}

void loop() {

// Initialize the Serial interface:
    int x;

          if (Bluetooth.available()){ //wait for data received
          int inByte=Bluetooth.read();         
      
    
          switch (inByte) {

                          case 'y':  //stop forward/backward motor
                                      digitalWrite(dir1PinA, LOW);   //stop motor 1
                                      digitalWrite(dir2PinA, LOW);                          
                          break;

                          case 'u':  //stop left/right motor
                                      digitalWrite(dir1PinB, LOW);    //stop motor 2
                                      digitalWrite(dir2PinB, LOW);
                          break;


                          case 't':  //stop motions
                                      digitalWrite(dir1PinA, LOW);   //stop motor 1
                                      digitalWrite(dir2PinA, LOW);                          
                                      digitalWrite(dir1PinB, LOW);    //stop motor 2
                                      digitalWrite(dir2PinB, LOW);
                          break;
                          
                          case '3': // FORWARD non-stop
                                      delay(delaystability);                       // wait for stability
                                      digitalWrite(dir1PinA, HIGH);
                                      digitalWrite(dir2PinA, LOW);                                                                             
                          break;

                          case '0': // REVERSE non-stop
                                      delay(delaystability);                       // wait for stability

                                      digitalWrite(dir1PinA, LOW);
                                      digitalWrite(dir2PinA, HIGH);
    
                          break;


                          case '5': // Motor 2 LEFT non stop
                                  delay(delaystability);                       // wait for stability
                                  digitalWrite(dir1PinB, LOW);
                                  digitalWrite(dir2PinB, HIGH);                                  
                                  
                          break;
                          
                          case '6': // RIGHT 45
                                  delay(delaystability);                       // wait for stability
                                  digitalWrite(dir1PinB, HIGH);
                                  digitalWrite(dir2PinB, LOW);

                          break;

                          case 'a': // Motor H2O                                      
                                  delay(delaystability);                       // wait for stability
                                  Bluetooth.println("agua va");
                                  digitalWrite(dirPinagua, LOW); /* Por cuestión de estabilización del sensor*/
                                  delay(100);
                                  digitalWrite(dirPinagua, HIGH); /* envío del pulso ultrasónico  "TRIG"*/
                                  delay(1000);
                                  digitalWrite(dirPinagua,LOW); /* Por cuestión de estabilización del sensor*/

                                  Bluetooth.println("OK");
                                  delay(100);
                          break;


                          case '1': // Maneuver-LEFT 90
                                      Bluetooth.println("Maneuver-LEFT 90 ");
                                      delay(delaystability);                       // wait for stability


                                     ////CYCLES MANEUBRE LEFT-90//////////////////////
                                      for ( x = 0; x < cyclesmaneubreleft90; x++ ) {
                                                                          //FULL LEFT WHEELS
                                                        digitalWrite(dir1PinB, LOW);
                                                        digitalWrite(dir2PinB, HIGH);
                                                        delay(300);                       // wait 0.1 s
                                                        digitalWrite(dir1PinB, LOW);
                                                        digitalWrite(dir2PinB, LOW);
                                                        delay(100);        
                  
                                                                              //avance//
                                                        digitalWrite(dir1PinA, HIGH);
                                                        digitalWrite(dir2PinA, LOW);
                                                        delay(avancedelay);                       // wait 0.5 s
                  
                                                                                             
                                                        digitalWrite(dir1PinA, LOW);   //stop
                                                        digitalWrite(dir2PinA, LOW);
                                                        delay(100);        
                  
                                                                        // FULL RIGHT WHEELS
                                                        digitalWrite(dir1PinB, HIGH);
                                                        digitalWrite(dir2PinB, LOW);
                                                        delay(300);                       // wait 0.2 s
                                                        digitalWrite(dir1PinB, LOW);
                                                        digitalWrite(dir2PinB, LOW);
                                                        delay(100);        
                  
                  
                                                                   //REVERSE
                                                        digitalWrite(dir1PinA, LOW);
                                                        digitalWrite(dir2PinA, HIGH);
                                                        delay(reversedelay);                       // wait 0.5 s
                  
                                                        digitalWrite(dir1PinA, LOW);   //stop
                                                        digitalWrite(dir2PinA, LOW);
                                                        delay(100);        
                                      }   ///end for loop///////////////////                                        


                                      centraruedas();
                                      centraruedas();

                                      Bluetooth.println("OK");
                                      delay(100);


                          break;




                          case '2': //  Maneuver-RIGHT-90
                                      Bluetooth.println("Maneuver-RIGHT 90 ");
                                      delay(delaystability);                       // wait for stability

                                     ////CYCLES MANEUBRE LEFT-90//////////////////////
                                      for ( x = 0; x < cyclesmaneubreright90; x++ ) {
                                                                      
                                                                      //FULL RIGHT WHEELS
                                                    digitalWrite(dir1PinB, HIGH);
                                                    digitalWrite(dir2PinB, LOW);
                                                    delay(300);                       // wait 
                                                    digitalWrite(dir1PinB, LOW);
                                                    digitalWrite(dir2PinB, LOW);
                                                    delay(100);        
                                                                          //avance//
                                                    digitalWrite(dir1PinA, HIGH);
                                                    digitalWrite(dir2PinA, LOW);
                                                    delay(avancedelay2);                       // wait avance delay
              
                             
              
                                                    digitalWrite(dir1PinA, LOW);   //stop
                                                    digitalWrite(dir2PinA, LOW);
                                                    delay(100);        
              
                                                                     // FULL LEFT WHEELS
                                                    digitalWrite(dir1PinB, LOW);
                                                    digitalWrite(dir2PinB, HIGH);
                                                    delay(300);                       // wait 
                                                    digitalWrite(dir1PinB, LOW);
                                                    digitalWrite(dir2PinB, LOW);
                                                    delay(100);        
              
                                                               //REVERSE
                                                    digitalWrite(dir1PinA, LOW);
                                                    digitalWrite(dir2PinA, HIGH);
                                                    delay(reversedelay2);                       // wait reverse delay
                                                    
                                                    digitalWrite(dir1PinA, LOW);   //stop
                                                    digitalWrite(dir2PinA, LOW);
                                                    delay(100);        
                                      };  //for loop
                                      
                                      centraruedas();
                                      centraruedas();

                                      Bluetooth.println("OK");
                                      delay(100);

                          break;



                          case '9': //    CENTER WHEELS 
                                      Bluetooth.println("Center-wheels");
                                      delay(delaystability);                       // wait for stability

                                      centraruedas();

                                      Bluetooth.println("OK");
                                      delay(100);

                          break;


                          case 'm': //   LIGHTS (6 blinking)
                                      Bluetooth.println("Blinking LIGHT");
                                      delay(delaystability);                       // wait for stability


                                      // BLINKING LED 
                                      pinMode(LED_BUILTIN, OUTPUT);
                                      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
                                      delay(200);                       // wait for a second
                                      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
                                      delay(200);                       // wait for a second
                                      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
                                      delay(200);                       // wait for a second
                                      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
                                      delay(200);                       // wait for a second
                                      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
                                      delay(200);                       // wait for a second
                                      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
                                      delay(200);                       // wait for a second
                                      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
                                      delay(200);                       // wait for a second
                                      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
                                      delay(200);                       // wait for a second
                                      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
                                      delay(200);                       // wait for a second
                                      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
                                      delay(200);                       // wait for a second
                                      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
                                      delay(200);                       // wait for a second
                                      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
                                      delay(200);                       // wait for a second

                                      Bluetooth.println("OK");
                                      delay(100);
                                     
                          break;



                          case 'b': // FORWARD LONG
                                      Bluetooth.println("Forward");
                                      delay(delaystability);                       // wait for stability
                                      digitalWrite(dir1PinA, HIGH);
                                      digitalWrite(dir2PinA, LOW);
                                      delay(1000);                       // wait 0.5 s
 
                                      digitalWrite(dir1PinA, LOW);  //active stop motor 1
                                      digitalWrite(dir2PinA, HIGH);
                                      delay(delayactivestop1);      // wait active  stop motor 1
                                      
                                      
                                      digitalWrite(dir1PinA, LOW);   //stop
                                      digitalWrite(dir2PinA, LOW);

                                      Bluetooth.println("OK");
                                      delay(100);


                          break;

                          case 'c': // REVERSE LONG 
                                      Bluetooth.println("Reverse"); // Prints out “Motor 1 Forward” on the serial monitor
                                      delay(delaystability);                       // wait for stability

                                      digitalWrite(dir1PinA, LOW);
                                      digitalWrite(dir2PinA, HIGH);
                                      delay(1000);                       // wait 0.5 s

                                      digitalWrite(dir1PinA, HIGH);  //active stop motor 1
                                      digitalWrite(dir2PinA, LOW);
                                      delay(delayactivestop1);       // wait active  stop motor 1
                                      
                                      
                                      digitalWrite(dir1PinA, LOW);   //stop
                                      digitalWrite(dir2PinA, LOW);

                                      Bluetooth.println("OK");
                                      delay(100);

                          break;
                          

                          case 'd': // Motor 2 LEFT LONG
                                  Bluetooth.println("LEFT");
                                  delay(delaystability);                       // wait for stability
                                  digitalWrite(dir1PinB, LOW);
                                  digitalWrite(dir2PinB, HIGH);
                                  delay(200);                       // wait 0.1 s

                                  digitalWrite(dir1PinB, HIGH);   //active stop motor 2
                                  digitalWrite(dir2PinB, LOW);
                                  delay(delayactivestop2);       // wait active  stop motor 2
                                  
                                  
                                  digitalWrite(dir1PinB, LOW);    //stop motor 2
                                  digitalWrite(dir2PinB, LOW);

                                  Bluetooth.println("OK");
                                  delay(100);


                          break;
                          
                          case 'e': // RIGHT LONG
                                  Bluetooth.println("RIGHT");
                                  delay(delaystability);                       // wait for stability
                                  digitalWrite(dir1PinB, HIGH);
                                  digitalWrite(dir2PinB, LOW);
                                  delay(200);                       // wait 0.1 s

                                  digitalWrite(dir1PinB, LOW);   //active stop motor 2
                                  digitalWrite(dir2PinB, HIGH);
                                  delay(delayactivestop2);       // wait active  stop motor 2
                                  
                                  
                                  digitalWrite(dir1PinB, LOW);   //stop motor 2
                                  digitalWrite(dir2PinB, LOW);

                                  Bluetooth.println("OK");
                                  delay(100);

                          break;


                          case 'f': //active stop antiforward motor 1
                                      Bluetooth.println("STOP antiforward");
 
                                      digitalWrite(dir1PinA, LOW);  //active stop motor 1
                                      digitalWrite(dir2PinA, HIGH);
                                      delay(delayactivestop1);      // wait active  stop motor 1
                                      
                                      
                                      digitalWrite(dir1PinA, LOW);   //stop
                                      digitalWrite(dir2PinA, LOW);

                                      Bluetooth.println("OK");
                                      delay(100);

                          break;


                          case 'g': //active stop antireverse motor 1
                                      Bluetooth.println("STOP antireverse");
 
                                      digitalWrite(dir1PinA, HIGH);  //active stop motor 1
                                      digitalWrite(dir2PinA, LOW);
                                      delay(delayactivestop1);      // wait active  stop motor 1
                                      
                                      
                                      digitalWrite(dir1PinA, LOW);   //stop
                                      digitalWrite(dir2PinA, LOW);
                                      Bluetooth.println("OK");
                                      delay(100);


                          break;

                          case 'h': // Motor 2 FULL-LEFT
                                  Bluetooth.println("LEFT-full");
                                  delay(delaystability);                       // wait for stability
                                  digitalWrite(dir1PinB, LOW);
                                  digitalWrite(dir2PinB, HIGH);
                                  delay(200);                       // wait 0.2 s

                                  digitalWrite(dir1PinB, HIGH);   //active stop motor 2
                                  digitalWrite(dir2PinB, LOW);
                                  delay(delayactivestop2);        // wait active  stop motor 2
                                      
                                  
                                  
                                  digitalWrite(dir1PinB, LOW);   //stop motor 2
                                  digitalWrite(dir2PinB, LOW);

                                  Bluetooth.println("OK");
                                  delay(100);

                          break;
                          
                          case 'i': // Motor 2 FULL-RIGHT
                                  Bluetooth.println("RIGHT-full");
                                  delay(delaystability);                       // wait for stability
                                  digitalWrite(dir1PinB, HIGH);
                                  digitalWrite(dir2PinB, LOW);
                                  delay(200);                       // wait 0.2 s

                                  digitalWrite(dir1PinB, LOW);   //active stop motor 2
                                  digitalWrite(dir2PinB, HIGH);
                                  delay(delayactivestop2);       // wait active  stop motor 2
                                  
                                  digitalWrite(dir1PinB, LOW);  //stop motor 2
                                  digitalWrite(dir2PinB, LOW);

                                  Bluetooth.println("OK");
                                  delay(100);
                          break;
                                                  
                          case 'r': // Leer sensor humedad

                                 Bluetooth.println(analogRead(A0)); 
                                 delay (100); 

                                 
                          break;

                         
                          
                         

                    }  //switch 
      
        }  //Bluetooth available
   } //loop

   
