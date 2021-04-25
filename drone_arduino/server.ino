// Configura o ESP como ponto de acesso
void startAP() {
  WiFi.mode(WIFI_AP);
  bool result = WiFi.softAP(ssid, password);             // Start the access point
  if (result == true) {

    // Callback quando alguém se conecta
    stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&conexaoCliente);
    // Callback quando alguém se desconecta
    stationDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(&desconexaoCliente);
    Serial.print(ssid);
    Serial.println(" iniciado !\r\n");
    Serial.print("IP address = ");
    Serial.println(WiFi.softAPIP());
    Serial.println("Esperando conexões...");

    // Route for root / web page
    server.on("/", HTTP_GET, handleRoot);

  // Start server
  server.begin();
  }
  else {
    Serial.println("AP falhou!");
  }
}

void handleRoot() {
  server.send(200, "text/html", index_html);
}

void startWS() { // Start a WebSocket server
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("WebSocket server started.");
  //  heartbeat (intervalo de ping, pong máximo, tentativas antes de desconectar)
  webSocket.enableHeartbeat(1000, 500, 3);
}

// evento webSocket como servidor
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // When a WebSocket message is received
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("WS DESCONECTADO - [%u]\n", num);
      break;
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("WS CONECTADO - IP: %d.%d.%d.%d url: %s\n", ip[0], ip[1], ip[2], ip[3], payload);
      // avisa o cliente
      webSocket.sendTXT(num, "oi");
    }
      break;
    case WStype_ERROR:
      Serial.printf("WS ERRO: %s\n", payload);
    case WStype_TEXT:
      Serial.printf("WS TEXTO: %s\n", payload);
      if(payload[0] == 'l') {
        luzCamera();
        }
    break;
  }
}

// Callback quando alguém se conecta no ESP
void conexaoCliente(const WiFiEventSoftAPModeStationConnected& evt) {
  Serial.print("Cliente entrou: ");
  Serial.println(macToString(evt.mac));
}
// Callback quando alguém se desconecta do ESP
void desconexaoCliente(const WiFiEventSoftAPModeStationDisconnected& evt) {
  Serial.print("Cliente saiu: ");
  Serial.println(macToString(evt.mac));
}
// Retorna uma String com o valor do mac address
String macToString(const unsigned char* mac) {
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}

void atualizaPagina() {
  if(millis() - tempo > 100) {
//    ang = ang * 180 / PI;

    sendValue('a', ang*180/PI);
    sendValue('p', pitch*180/PI);
    sendValue('r', roll*180/PI);
    sendValue('d', dist);
    
    tempo = millis();
  }
 }

void sendValue(char comando, float valor) {
    int tam = 50;
    char val[tam];
    char buff[tam];
    for(int i=0; i<tam; i++) {
      val[i] = 0;
      buff[i] = 0;
    }
    val[0] = comando;
    dtostrf(valor, 4, 6, buff);
    strcat(val, buff);
    webSocket.broadcastTXT(val);
  }
