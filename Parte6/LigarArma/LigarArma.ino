/**
 * Ligar Arma
 *
 */
#include <ESP8266WiFi.h>



const char* ssid = "rfc";
// mínimo de 8 caracteres
const char* password = "testeteste";
// definir porta de comunicação
WiFiServer server(23);


const int Ponte1_cima_esquerda_baixo_direita  = 2;
const int Ponte1_cima_direita_baixo_esquerda = 3;
const int Ponte2_cima_esquerda_baixo_direita  = 4;
const int Ponte2_cima_direita_baixo_esquerda = 5;
const int porta_arma = 12;
int velocidade = 0;
bool arma = 0;

void setup() {
      // declarar pinos
    pinMode(Ponte1_cima_esquerda_baixo_direita, OUTPUT);
    pinMode(Ponte1_cima_direita_baixo_esquerda, OUTPUT);
    pinMode(Ponte2_cima_esquerda_baixo_direita, OUTPUT);
    pinMode(Ponte2_cima_direita_baixo_esquerda, OUTPUT);
    pinMode(porta_arma, OUTPUT);


    Serial.begin(115200);
      // Configurar ip fixo no ESP
    IPAddress ip(192, 168, 1, 5);
    IPAddress gateway(192, 168, 1, 1);
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
  uint8_t i;
  WiFiClient client = server.available();
  // Aplicação tenta se conectar ao servidor
  if (client)
  {
    Serial.println("\n[Cliente conectado]");
    while (client.connected())
    {
      if (client.available())
      {
        char msg = client.read();

        if(msg == 'a'){
          Serial.println("Esquerda");
          analogWrite(Ponte1_cima_esquerda_baixo_direita, velocidade);
          digitalWrite(Ponte1_cima_direita_baixo_esquerda, LOW);
          digitalWrite(Ponte2_cima_esquerda_baixo_direita, LOW);
          analogWrite(Ponte2_cima_direita_baixo_esquerda, velocidade);
        }

        if(msg == 'd'){
          Serial.println("Direita");
          digitalWrite(Ponte1_cima_esquerda_baixo_direita, LOW);
          analogWrite(Ponte1_cima_direita_baixo_esquerda, velocidade);
          digitalWrite(Ponte2_cima_esquerda_baixo_direita, LOW);
          analogWrite(Ponte2_cima_direita_baixo_esquerda, velocidade);

        }
        if(msg == 'x'){
          Serial.println("Stop");
          digitalWrite(Ponte1_cima_esquerda_baixo_direita, LOW);
          digitalWrite(Ponte1_cima_direita_baixo_esquerda, LOW);
          digitalWrite(Ponte1_cima_esquerda_baixo_direita, LOW);
          digitalWrite(Ponte1_cima_direita_baixo_esquerda, LOW);

        }
        if(msg == 'w'){
          Serial.println("Frente");
          analogWrite(Ponte1_cima_esquerda_baixo_direita, velocidade);
          digitalWrite(Ponte1_cima_direita_baixo_esquerda, LOW);
          analogWrite(Ponte2_cima_esquerda_baixo_direita, velocidade);
          digitalWrite(Ponte2_cima_direita_baixo_esquerda, LOW);
        }
        if(msg == 's'){
          Serial.println("Tras");
          digitalWrite(Ponte1_cima_esquerda_baixo_direita, LOW);
          analogWrite(Ponte1_cima_direita_baixo_esquerda, velocidade);
          digitalWrite(Ponte2_cima_esquerda_baixo_direita, LOW);
          analogWrite(Ponte2_cima_direita_baixo_esquerda, velocidade);
        }
        // Colocar do 1 até 5
        if(msg == '1' || msg == '2' || msg == '3'|| msg == '4' ||  msg == '5'){
          Serial.println("Velocidade");
          int vel = msg - '0';
          velocidade = map(vel, 1, 5, 0, 255);
        }

        if(msg == 'l' ){
          Serial.println("Arma");
           arma = !arma;
           digitalWrite(porta_arma, arma);
           Serial.println(arma);
        }




      }
      delay(10);
    }
   }
    delay(1);
}
