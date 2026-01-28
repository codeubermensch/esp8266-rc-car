/******** WiFi Robot Control – L298N (NO EN PINS) ********/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// ===== MOTOR PINS (SAFE GPIOs) =====
int in1 = D1;   // GPIO5
int in2 = D2;   // GPIO4
int in3 = D5;   // GPIO14
int in4 = D6;   // GPIO12

ESP8266WebServer server(80);
String command;

// ===== WiFi AP Credentials =====
String sta_ssid = "Metal Mavericks";
String sta_password = "987654321";

void setup() {
  Serial.begin(115200);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Stop();  // motors OFF initially

  // WiFi AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP(sta_ssid.c_str(), sta_password.c_str());

  Serial.println("WiFi Started");
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
  command = server.arg("State");

  if (command == "F") Forward();
  else if (command == "B") Backward();
  else if (command == "L") TurnLeft();
  else if (command == "R") TurnRight();
  else if (command == "G") ForwardLeft();
  else if (command == "I") ForwardRight();
  else if (command == "H") BackwardLeft();
  else if (command == "J") BackwardRight();
  else if (command == "S") Stop();
}

void HTTP_handleRoot() {
  server.send(200, "text/html", "");
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
}

// ===== MOTOR FUNCTIONS =====

void Forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void TurnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void TurnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void ForwardLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void ForwardRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void BackwardLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void BackwardRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
