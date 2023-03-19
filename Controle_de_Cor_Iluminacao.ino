#include <WiFi.h>

#define azul 5
#define verde 18
#define vermelho 19

const char* ssid = "suaredewifi";
const char* password = "senhadowifi";

WiFiServer server(80);


void setup() {
  Serial.begin(115200);

  pinMode(azul, OUTPUT);      //Define a variável azul como saída
  pinMode(verde, OUTPUT);     //Define a variável verde como saída
  pinMode(vermelho, OUTPUT);  //Define a variável vermelho como saída

  delay(10);

  // Conectando ao WiFi

  Serial.println();
  Serial.println();
  Serial.print("Conectando à ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  IPAddress ip(192, 168, x, xxx);      //endereço ip para conectar à página web
  IPAddress gateway(192, 168, x, 1);   //Gateway padrão
  IPAddress subnet(255, 255, 255, 0);  //máscara de rede

  WiFi.config(ip, gateway, subnet);

  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("Endereço IP: ");
  Serial.println(ip);

  server.begin();
}

int value = 0;

void loop() {

  WiFiClient client = server.available();  // listen for incoming clients

  if (client) {                     // if you get a client,
    Serial.println("New Client.");  // print a message out the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        if (c == '\n') {            // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();


            client.println("<center>");
            client.println("<br>");
            client.println("<a href=\"/azul\"\"><button>Azul</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/verde\"\"><button>Verde</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/vermelho\"\"><button>Vermelho</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/branco\"\"><button>Branco</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/roxo\"\"><button>Roxo</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/amarelo\"\"><button>Amarelo</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/desliga\"\"><button>Desliga</button></a>");
            client.println("<br>");
            client.println("<br>");

            client.println("</center>");


            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }


        if (currentLine.endsWith("GET /azul")) {
          Azul();
        }

        if (currentLine.endsWith("GET /verde")) {
          Verde();
        }

        if (currentLine.endsWith("GET /vermelho")) {
          Vermelho();
        }

        if (currentLine.endsWith("GET /branco")) {
          Branco();
        }

        if (currentLine.endsWith("GET /roxo")) {
          Roxo();
        }

        if (currentLine.endsWith("GET /amarelo")) {
          Amarelo();
        }

        if (currentLine.endsWith("GET /desliga")) {
          Desliga();
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
  delay(10);
}

void Vermelho() {
  digitalWrite(azul, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, HIGH);
}

void Verde() {
  digitalWrite(azul, LOW);
  digitalWrite(verde, HIGH);
  digitalWrite(vermelho, LOW);
}

void Azul() {
  digitalWrite(azul, HIGH);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, LOW);
}

void Branco() {
  digitalWrite(azul, HIGH);      //Coloca azul em nível alto
  digitalWrite(vermelho, HIGH);  //Coloca vermelho em nível alto
  digitalWrite(verde, HIGH);     //Coloca verde em nível alto, ligando-o
}

void Roxo() {
  digitalWrite(azul, HIGH);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, HIGH);
}

void Amarelo() {
  digitalWrite(azul, LOW);
  digitalWrite(verde, HIGH);
  digitalWrite(vermelho, HIGH);
}

void Desliga() {
  digitalWrite(azul, LOW);      //Coloca azul em nível baixo
  digitalWrite(vermelho, LOW);  //Coloca vermelho em nível baixo
  digitalWrite(verde, LOW);     //Coloca verde em nível baixo
}
