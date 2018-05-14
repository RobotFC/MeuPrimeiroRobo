/**
 * Configurar cliente
 *
 */
#include <ESP8266WiFi.h>

const char* ssid = "rfc";
// mínimo de 8 caracteres
const char* password = "testeteste";
// definir porta de comunicação
WiFiServer server(23);


void setup() {
    Serial.begin(115200);
      // Configurar ip fixo no ESP
    IPAddress ip(192, 168, 1, 5); // where xx is the desired IP Address
    IPAddress gateway(192, 168, 1, 1); // set gateway to match your network
    Serial.print(F("Setting static ip to : "));
    Serial.println(ip);
    IPAddress subnet(255, 255, 255, 0);
    // set subnet mask to match your network
    bool configAP = WiFi.softAPConfig(ip, gateway, subnet);
    if(!configAP){
      Serial.print("Config AP falhou");
    }

    // WiFi.softAP(ssid, password, channel, hidden)
    // Se problema com muitas APs trocar channel. Channel vai de 1-13
    bool softAP = WiFi.softAP(ssid, password);
    if(!softAP){
      Serial.print("Criacao AP falhou");
    }

  server.begin();
  server.setNoDelay(true);

  Serial.print("Ready! Use 'telnet ");
  Serial.print(WiFi.softAPIP());
  Serial.println(" 23' to connect");
}

void loop() {

  WiFiClient client = server.available();
  // Aplicação tenta se conectar ao servidor
  if (client)
  {
    Serial.println("\n[Client conectado]");
    while (client.connected())
    {
      if (client.available())
      {
      
        char msg = client.read();
        Serial.println(msg);

      }
      delay(10);
    }
   }
    delay(1); 



}
