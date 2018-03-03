#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
int i = 0;
String from_bl;
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

/*
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
*/
  
}

int deduct_bal(int int_amt)
 {
  int_amt = int_amt - 30;
  Serial.println(int_amt);
  return int_amt;
 }
void loop() {



from_bl = "11111.txt";

Serial.println(from_bl);

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
       int_amt = deduct_bal(int_amt);
       Serial.println("After deducting");
       Serial.println(int_amt);
      
    }
    myFile.close();
    SD.remove("11111.txt");
    if(SD.exists("example.txt"))
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
     Serial.println("locha");
  }
  
}
/*
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
          client.println("TOTAL PARKING SPACES LEFT ARE: ");
          client.println(i);
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
  }*/
  
}

