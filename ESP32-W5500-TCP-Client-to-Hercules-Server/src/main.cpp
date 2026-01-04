#include <SPI.h>
#include <Ethernet.h>

#define W5500_CS 4
#define W5500_MOSI 18
#define W5500_MISO 17
#define W5500_SCK 8

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Her cihaz için değişecek
IPAddress esp_ip(169, 254, 10, 1);  // Her cihaz için değişecek
IPAddress dns(8, 8, 8, 8);
IPAddress subnet(255, 255, 0, 0);

IPAddress serverIP(169, 254, 83, 33); // Buraya Server IP si gelecek
int serverPort = 5000;
EthernetClient client;

unsigned long lastSendTime = 0;
int sayac = 0;

void setup() 
{
  Serial.begin(115200);
  delay(250);
  SPI.begin(W5500_SCK, W5500_MISO, W5500_MOSI);
  Ethernet.init(W5500_CS);
  Ethernet.begin(mac, esp_ip, dns, serverIP, subnet);

  Serial.println("Ethernet Başlatıldı!");
  Serial.print("ESP IP: ");
  Serial.println(Ethernet.localIP());
}

void loop() 
{
  // Kablo durumu kontrol
  if (Ethernet.linkStatus() != LinkON) { 
    Serial.println("Ethernet kablosu yok!");
    client.stop();
    delay(2000);
    return;
  }

  // TCP bağlantısı yoksa yeniden bağlan
  if (!client.connected()) 
  {
    Serial.println("⚠️ Servere bağlanılıyor...");
    
    if (client.connect(serverIP, serverPort)) 
    {
      Serial.println("Server bağlı!");
    } 
    else 
    {
      Serial.println("Bağlantı reddedildi! Server açık mı?");
      delay(1000);
      return;
    }
  }

  // Server bağlıysa sürekli veri gönder
  if (millis() - lastSendTime > 1000)
  {
    lastSendTime = millis();
    sayac++;
    client.print("DATA: ");
    client.println(sayac);
    Serial.print("Gönderildi: ");
    Serial.println(sayac);
  }

  // Gelen veri varsa oku
  if (client.available()) 
  {
    String rx = client.readStringUntil('\n');
    Serial.print("PC’den Gelen: ");
    Serial.println(rx);
  }
}
