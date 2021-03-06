#include <ESP8266WiFi.h>
#include <IRsend.h>



const char* ssid = "i4C";
const char* password = "12345678";

WiFiServer server(80);
IRsend irsend(4);
void setup() {
  irsend.begin();
  Serial.begin(115200);
  delay(10);

  
  pinMode(4, OUTPUT);
  Serial.println();
  Serial.println("Connecting");


  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);



  Serial.print("OK, IP ");

  server.begin();

  Serial.println(WiFi.softAPIP());
}

void loop() {
  //Jika tidak ada yang menghubungi, kembali
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  //Jika tidak ada koneksi, kembali
  while (!client.available()) {
    delay(1);
  }

  //Baca permintaan di baris pertama dan flush selebihnya
  String req = client.readStringUntil('\r');
  client.flush();

  //cek perintah (request)
  if (req.indexOf("/onoff") != -1)
  {
     irsend.sendNEC(0xC31E0700, 32);
  }
  else if (req.indexOf("/suhu16") != -1)
 {
     irsend.sendNEC(0xC3E20700, 32);
  }
   else if (req.indexOf("/suhu18") != -1)
 {
     irsend.sendNEC(0xC3EA0700, 32);
  }
  else if (req.indexOf("/suhu20") != -1)
 {
     irsend.sendNEC(0xC3E60700, 32);
  }
  else if (req.indexOf("/suhu22") != -1)
 {
     irsend.sendNEC(0xC3EE0700, 32);
  }
  else if (req.indexOf("/suhu24") != -1)
 {
     irsend.sendNEC(0xC3E10700, 32);
  }
  else if (req.indexOf("/suhu26") != -1)
 {
     irsend.sendNEC(0xC3E90700, 38);
  }
  else if (req.indexOf("/suhu28") != -1)
 {
     irsend.sendNEC(0xC3E50700, 38);
  }
  else if (req.indexOf("/suhu30") != -1)
 {
     irsend.sendNEC(0xC3ED0700, 38);
  }

  //siapkan respon balik (HTML)
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nStatus : ";
  s += " <a href=\"onoff\">ONOFF</a> <a href=\"suhu16\">SUHU16</a> <a href=\"suhu18\">SUHU18</a> <a href=\"suhu20\">SUHU20</a> <a href=\"suhu22\">SUHU22</a> <a href=\"suhu24\">SUHU24</a> <a href=\"suhu26\">SUHU26</a> <a href=\"suhu28\">SUHU28</a> <a href=\"suhu30\">SUHU30</a> </html>\n";

  //kirim respon ke client
  client.print(s);
 
  delay(1);
}

