  #include <SPI.h>
  #include <Ethernet.h>
  #include <SD.h>
  char data;
  String from_bl;
  int done = 0;
  int i;
  boolean park1;
  boolean park2;
  boolean park3;
  boolean wrong_park;
  int trigPin1 = 22;    
  int echoPin1 = 23; 
  int trigPin2 = 24;
  int echoPin2 = 25; 
  int trigpin3 = 26;
  int echopin3 = 27;
  int trigpin4 = 28;
  int echopin4 = 29;
  long duration, duration2, duration3, duration4;
  int cm,cm2,cm3,cm4;
  String amt;
  static int int_amt;
  boolean remove_f;
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
    pinMode(trigpin4, OUTPUT);
    pinMode(echopin4, INPUT);
    Serial.print("Initializing SD card...");
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
    digitalWrite(trigPin1, LOW);                        
    delayMicroseconds(5);
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(5);
    /*digitalWrite(trigpin3, LOW);
    delayMicroseconds(5);
    digitalWrite(trigpin4, LOW);
    delayMicroseconds(5);
    */
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    
    
    digitalWrite(trigPin1, LOW);
    pinMode(echoPin1, INPUT);
    duration = pulseIn(echoPin1, HIGH);
   
     
    cm = (duration/2) / 29.1;
  
    digitalWrite(trigPin2, LOW);
    pinMode(echoPin2, INPUT);
    duration2 = pulseIn(echoPin2, HIGH);
   
    cm2 = (duration2/2) / 29.1;
  
    digitalWrite(trigpin3, LOW);
    pinMode(echopin3, INPUT);
    duration3 = pulseIn(echopin3, HIGH);
   
    cm3 = (duration3/2) / 29.1;
  
    digitalWrite(trigpin4, LOW);
    pinMode(echopin4, INPUT);
    duration4 = pulseIn(echopin4, HIGH);
   
    cm4 = (duration4/2) / 29.1;
  
  
   
  delay(1000);
  
      while(Serial.available() > 0)
      {
      data = Serial.read();
      from_bl += data;
      Serial.println("FROM BLUETOOTH");
      Serial.print(from_bl);
      }
    
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
      if(int_amt >= 30)
      
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
         int_amt = deduct_bal(int_amt);
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
         int_amt = deduct_bal(int_amt);
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
         int_amt = deduct_bal(int_amt);
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
         int_amt = deduct_bal(int_amt);
         myFile.close();
      }
     
      SD.remove("55555.txt");
      myFile = SD.open("55555.txt", FILE_WRITE);
      myFile.println(int_amt);
      myFile.close();
      }
  
      else 
      {
        Serial.println("error opening 55555.txt");
      }
  }

  delay(7500);
    digitalWrite(trigPin1, LOW);                        
    delayMicroseconds(5);
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(5);
    
    
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    
    
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
    /*digitalWrite(trigpin3, LOW);
    pinMode(echopin3, INPUT);
    duration3 = pulseIn(echopin3, HIGH);
    cm3 = (duration3/2) / 29.1;
    digitalWrite(trigpin4, LOW);
    pinMode(echopin4, INPUT);
    duration4 = pulseIn(echopin4, HIGH);
    cm4 = (duration4/2) / 29.1;
      */
    if(cm >= 8 && cm2>=8)
    {
      wrong_park = true;
      Serial.println("WRONG PARKING");
    }
    if(cm - cm2 >= 8 || cm2 - cm >= 8)
    {
       wrong_park = true;
       Serial.println("WRONG PARKING");
    }
    done = 1;

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
         Serial.println("parse:");
         Serial.println(int_amt);
         int_amt = fine_bal(int_amt);
         Serial.println("After deducting");
         Serial.println(int_amt);
         myFile.close();
      }
     
      SD.remove("11111.txt");
      if(SD.exists("11111.txt"))
      {
        Serial.println("not removed");
      }
     else
     {
      Serial.println("removed");
     }
      myFile = SD.open("11111.txt", FILE_WRITE);
      myFile.println(int_amt);
        //delay(1000);
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
         Serial.println("parse:");
         Serial.println(int_amt);
         int_amt = fine_bal(int_amt);
         Serial.println("After deducting");
         Serial.println(int_amt);
         myFile.close();
      }
     
      SD.remove("22222.txt");
      if(SD.exists("22222.txt"))
      {
        Serial.println("not removed");
      }
     else
     {
      Serial.println("removed");
     }
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
         Serial.println("parse:");
         Serial.println(int_amt);
         int_amt = fine_bal(int_amt);
         Serial.println("After deducting");
         Serial.println(int_amt);
         myFile.close();
      }
     
      SD.remove("33333.txt");
      if(SD.exists("33333.txt"))
      {
        Serial.println("not removed");
      }
     else
     {
      Serial.println("removed");
     }
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
         Serial.println("parse:");
         Serial.println(int_amt);
         int_amt = fine_bal(int_amt);
         Serial.println("After deducting");
         Serial.println(int_amt);
         myFile.close();
      }
     
      SD.remove("44444.txt");
      if(SD.exists("44444.txt"))
      {
        Serial.println("not removed");
      }
     else
     {
      Serial.println("removed");
     }
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
         Serial.println("parse:");
         Serial.println(int_amt);
         int_amt = fine_bal(int_amt);
         Serial.println("After deducting");
         Serial.println(int_amt);
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
            client.println("Refresh: 1");  
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<body>");
            if(park1)
            {
            client.println("<div style=\"width:25px; height=25px; background=color:Red;\"> ");
            }
            else
            {
              client.println("<div style=\"width:25px; height=25px; background=color:Green;\"> ");
            }

            if(park2)
            {
            client.println("<div style=\"width:25px; height=25px; background=color:Red;\"> ");
            }
            else
            {
              client.println("<div style=\"width:25px; height=25px; background=color:Green;\"> ");
            }

            if(park3)
            {
            client.println("<div style=\"width:25px; height=25px; background=color:Red;\"> ");
            }
            else
            {
              client.println("<div style=\"width:25px; height=25px; background=color:Green;\"> ");
            }
            client.println("</div>");
            client.println("<b>");
            client.println("TOTAL PARKING SPACES LEFT ARE: ");
            client.println(i);
            client.println("</b>");
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
