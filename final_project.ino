#include <SPI.h>
  #include <Ethernet.h>
  #include <SD.h>
  char data;
  String from_bl;
  int i = 0;
  int j = 0;
  boolean park1=false;
  boolean park2=false;
  boolean park3;
  boolean wrong_park;
  int trigPin1 = 22;    
  int echoPin1 = 23; 
  int trigPin2 = 24;
  int echoPin2 = 25; 
  int trigpin3 = 26;
  int echopin3 = 27;
  //int trigpin4 = 28;
  //int echopin4 = 29;
  long duration, duration2, duration3; //, duration4;
  int cm,cm2,cm3; //s,cm4;
  String amt;
  static int int_amt;
  boolean remove_f;
  //boolean space_1=false, space_2=false;
  File myFile;
  byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
  };
  IPAddress ip(10, 20, 23, 46);
  EthernetServer server(80);
  
  void setup() {
  Serial.begin(9600);
    while (!Serial) {
      ; 
    }
   pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigpin3, OUTPUT);
    pinMode(echopin3, INPUT);
/*    pinMode(trigpin4, OUTPUT);
    pinMode(echopin4, INPUT);
  */  Serial.print("Initializing SD card...");
    if (!SD.begin(4)) {
      Serial.println("initialization failed!");
      return;
    }
    Serial.println("initialization done.");
  
  myFile = SD.open("11111.txt", FILE_WRITE);
  if (myFile) {
      Serial.print("11111.txt FILE CREATED...");
      myFile.println(1000);
      myFile.close();
      Serial.println("done.");
    } else {
     Serial.println("error opening 11111.txt");
    }
  myFile = SD.open("22222.txt", FILE_WRITE);
  if (myFile) {
      Serial.print("22222.txt FILE CREATED...");
      myFile.println(1000);
      myFile.close();
      Serial.println("done.");
    } else {
      Serial.println("error opening 22222.txt");
    }
  myFile = SD.open("33333.txt", FILE_WRITE);
  if (myFile) {
      Serial.print("33333.txt FILE CREATED ...");
      myFile.println(1000);
      myFile.close();
      Serial.println("done.");
    } else {
      Serial.println("error opening 33333.txt");
    }
  myFile = SD.open("44444.txt", FILE_WRITE);
  if (myFile) {
      Serial.print("44444.txt FILE CREATED...");
      myFile.println(1000);
      myFile.close();
      Serial.println("done.");
    } else {
      Serial.println("error opening 44444.txt");
    }
  myFile = SD.open("55555.txt", FILE_WRITE);
  if (myFile) {
      Serial.print("55555.txt FILE CREATED...");
      myFile.println(1000);
      myFile.close();
      Serial.println("done.");
    } else {
      Serial.println("error opening 55555.txt");
    }
  
  
    Ethernet.begin(mac, ip);
    server.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
  
    
  }
  
  int deduct_bal(int int_amt)
   {
    int_amt = int_amt - 30;
    Serial.println(int_amt);
    return int_amt;
   }

   int fine_bal(int int_amt)
   {
    int_amt = int_amt - 50;
    return int_amt;
   }
  void loop() {
  from_bl = "";
  i = 0;
    digitalWrite(trigPin1, LOW);                        
    delayMicroseconds(5);
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(5);
    digitalWrite(trigpin3, LOW);
    delayMicroseconds(5);
    //digitalWrite(trigpin4, LOW);
    //delayMicroseconds(5);
    
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin3, HIGH);
    delayMicroseconds(10);
    //digitalWrite(trigpin4, HIGH);
    //delayMicroseconds(10);
    
    digitalWrite(trigPin1, LOW);
    pinMode(echoPin1, INPUT);
    duration = pulseIn(echoPin1, HIGH);
   Serial.print("DISTANCE 1:");
   Serial.println(cm);
    cm = (duration/2) / 29.1;
    digitalWrite(trigPin2, LOW);
    pinMode(echoPin2, INPUT);
    duration2 = pulseIn(echoPin2, HIGH);
    cm2 = (duration2/2) / 29.1;
    
   Serial.print("DISTANCE 2:");
   Serial.println(cm2);
    digitalWrite(trigpin3, LOW);
    pinMode(echopin3, INPUT);
    duration3 = pulseIn(echopin3, HIGH);
    cm3 = (duration3/2) / 29.1;
    Serial.print("Distance 3: ");
    Serial.println(cm3);
    
    /*digitalWrite(trigpin4, LOW);
    pinMode(echopin4, INPUT);
    duration4 = pulseIn(echopin4, HIGH);
    cm4 = (duration4/2) / 29.1;*/
 
    if(cm <= 12 || cm2 <= 12)
    {
      park1 = true;
      Serial.println("Space - 1 full");
      //Turn Led ON
      digitalWrite(44,LOW);
      
    }
    else
    {
      park1 = false;
      i++;
      digitalWrite(44, HIGH);
    }
   if(cm3 <= 10)
   {
      park2 = true;
      Serial.println("Space - 2 full");
      //Turn Led ON
      digitalWrite(45, LOW);
   }
   else
   {
      park2 = false; 
      i++; 
      digitalWrite(45, HIGH);  
   }
  
    //delay(5000);

    if(park1 == true)
    {
      while(Serial.available() > 0)
      {
      data = Serial.read();
      from_bl += data;
      Serial.println("FROM BLUETOOTH");
      Serial.print(from_bl);
      }
    delay(500);
  if(from_bl == "11111.txt")
  {
    myFile = SD.open("11111.txt");
    if(myFile)
    {
       while (myFile.available())
      {
         int_amt = myFile.parseInt();
         int_amt = deduct_bal(int_amt);
         Serial.println(int_amt);
         myFile.close();
      }
     
      SD.remove("11111.txt");
      
      myFile = SD.open("11111.txt", FILE_WRITE);
    
      
      myFile.println(int_amt);
      Serial.print("YOUR NEW BALANCE IS");
      Serial.println(int_amt);
      myFile.close();
    }
  
    else 
    {
       Serial.println("error opening 11111.txt");
    }
  }
    if(from_bl == "22222.txt")
  {
    myFile = SD.open("22222.txt");
    if(myFile)
    {
       while (myFile.available())
      {
         int_amt = myFile.parseInt();
         int_amt = deduct_bal(int_amt);
         myFile.close();
      }
     
      SD.remove("22222.txt");
      myFile = SD.open("22222.txt", FILE_WRITE);
      myFile.println(int_amt);
      Serial.print("YOUR NEW BALANCE IS");
      Serial.println(int_amt);
      myFile.close();
    }
    else 
    {
       Serial.println("error opening 22222.txt");
    }
  }
  
    if(from_bl == "33333.txt")
  {
    myFile = SD.open("33333.txt");
    if(myFile)
    {
       while (myFile.available())
      {
         int_amt = myFile.parseInt();
         int_amt = deduct_bal(int_amt);
         myFile.close();
      }
     
      SD.remove("33333.txt");
      myFile = SD.open("33333.txt", FILE_WRITE);
      myFile.println(int_amt);
      Serial.print("YOUR NEW BALANCE IS");
      Serial.println(int_amt);
      myFile.close();
        }
  
      else 
    {
       Serial.println("error opening 33333.txt");
    }
  }
  
    if(from_bl == "44444.txt")
  {
    myFile = SD.open("44444.txt");
    if(myFile)
    {
       while (myFile.available())
      {
         int_amt = myFile.parseInt();
         int_amt = deduct_bal(int_amt);
         myFile.close();
      }
     
      SD.remove("44444.txt");
      myFile = SD.open("44444.txt", FILE_WRITE);
      myFile.println(int_amt);
      Serial.print("YOUR NEW BALANCE IS");
      Serial.println(int_amt);
      myFile.close();
    }
     else 
    {
       Serial.println("error opening 44444.txt");
    }
  }
    if(from_bl == "55555.txt")
  {
    myFile = SD.open("55555.txt");
    if(myFile)
    {
       while (myFile.available())
      {
         int_amt = myFile.parseInt();
         int_amt = deduct_bal(int_amt);
         myFile.close();
      }
     
      SD.remove("55555.txt");
      myFile = SD.open("55555.txt", FILE_WRITE);
      myFile.println(int_amt);
      Serial.print("YOUR NEW BALANCE IS");
      Serial.println(int_amt);
      myFile.close();
      }
  
      else 
      {
        Serial.println("error opening 55555.txt");
      }
      }
    }
    else
    {
      Serial.println("Space-1 is Empty...!!");
    }

 // delay(1000);

    if(park2 == true)
      Serial.println("Space-2 is Full...!!");
    else
      Serial.println("Space-2 is Empty...!!");

      
    if(park1 == true)
    {
      if(cm >= 11 || cm2>=11)
      {
        wrong_park = true;
        Serial.println("WRONG PARKING AT SPACE-1");
        for(j = 0; j < 5; j++)
        {
          digitalWrite(44, HIGH);
          delay(250);
          digitalWrite(44, LOW);
          delay(250);
        }
      }
      /*if(cm - cm2 >= 8 || cm2 - cm >= 8)
      {
       wrong_park = true;
       Serial.println("WRONG PARKING AT SPACE-1");
      }*/
    }
    else
      Serial.println("Space-1 is Empty!");

if(wrong_park==true)
{
  if(from_bl == "11111.txt")
  {
    myFile = SD.open("11111.txt");
    if(myFile)
    {
       while (myFile.available())
      {
         int_amt = myFile.parseInt();
         int_amt = fine_bal(int_amt);
         myFile.close();
      }
     
      SD.remove("11111.txt");
      
      myFile = SD.open("11111.txt", FILE_WRITE);
      myFile.println(int_amt);
      myFile.close();
    }
  
      else 
    {
       Serial.println("error opening 11111.txt");
    }
  }
    if(from_bl == "22222.txt")
  {
    myFile = SD.open("22222.txt");
    if(myFile)
    {
       while (myFile.available())
      {
         int_amt = myFile.parseInt();
         int_amt = fine_bal(int_amt);
         myFile.close();
      }
     
      SD.remove("22222.txt");
      myFile = SD.open("22222.txt", FILE_WRITE);
      myFile.println(int_amt);
      myFile.close();
    }
  
      else 
    {
       Serial.println("error opening 22222.txt");
    }
  }
  
    if(from_bl == "33333.txt")
  {
    myFile = SD.open("33333.txt");
    if(myFile)
    {
       while (myFile.available())
      {
         int_amt = myFile.parseInt();
         int_amt = fine_bal(int_amt);
         myFile.close();
    }
     
      SD.remove("33333.txt");
      myFile = SD.open("33333.txt", FILE_WRITE);
      myFile.println(int_amt);
      myFile.close();
    }
  
    else 
    {
       Serial.println("error opening 33333.txt");
    }
  }
  
    if(from_bl == "44444.txt")
  {
    myFile = SD.open("44444.txt");
    if(myFile)
    {
       while (myFile.available())
      {
         int_amt = myFile.parseInt();
         int_amt = fine_bal(int_amt);
         myFile.close();
      }
     
      SD.remove("44444.txt");
      myFile = SD.open("44444.txt", FILE_WRITE);
      myFile.println(int_amt);
      myFile.close();
    }
  
    else 
    {
       Serial.println("error opening 44444.txt");
    }
  }
    if(from_bl == "55555.txt")
  {
    myFile = SD.open("55555.txt");
    if(myFile)
    {
       while (myFile.available())
      {
         int_amt = myFile.parseInt();
         int_amt = fine_bal(int_amt);
         myFile.close();
      }
     
      SD.remove("55555.txt");
      if(SD.exists("55555.txt"))
      {
        Serial.println("not removed");
      }
     else
     {
      Serial.println("removed");
     }
      myFile = SD.open("55555.txt", FILE_WRITE);
      myFile.println(int_amt);
      myFile.close();
     }
  
      else 
    {
       Serial.println("error opening 55555.txt");
    }
  }
}
     
     
  
    EthernetClient client = server.available();
    if (client) {
      Serial.println("new client");
      boolean currentLineIsBlank = true;
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          Serial.write(c);
          if (c == '\n' && currentLineIsBlank) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println("Refresh: 0.5");  
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<body>");
            if(park1 == true)
            {
            client.println("<div style='width:25px; height=25px; background=color:Red;'> ");
            client.println("</div>");
            }
            else
            {
              client.println("<div style='width:25px; height=25px; background=color:Green;'> ");
              client.println("</div>");
            }

            if(park2 == true)
            {
            client.println("<div style='width:25px; height=25px; background=color:Red;'> ");
            client.println("</div>");
            }
            else
            {
              client.println("<div style='width:25px; height=25px; background=color:Green;'> ");
              client.println("</div>");
            }

         
            if(i > 0)
            {
            client.println("<b>");
            client.println("<font color='green'; size= '+ 2'>");
            client.println("TOTAL PARKING SPACES LEFT ARE: ");
            client.println(i);
            client.println("</font>");
            client.println("</b>");
            }
            if(i==0)
            {
              client.println("<b>");
            client.println("<font color='red'>");
            client.println("TOTAL PARKING SPACES LEFT ARE: ");
            client.println(i);
            client.println("</font>");
            client.println("</b>");
            }
            client.println("</body>");
            client.println("</html>");
            break;
          }
          if (c == '\n') {
            currentLineIsBlank = true;
          } else if (c != '\r') {
            currentLineIsBlank = false;
          }
        }
      }
       delay(1);
  
     
      client.stop();
      Serial.println("client disconnected");
    }
    
  }
