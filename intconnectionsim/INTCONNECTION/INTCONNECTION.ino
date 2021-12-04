
#include <GSM.h>
 
// PIN-код
#define PINNUMBER "0000"
 
// Данные точки доступа APN
#define GPRS_APN       "internet" // замените на свою GPRS-точку доступа
#define GPRS_LOGIN     ""    // замените на свой логин для подключения к GPRS
#define GPRS_PASSWORD  "" // замените на свой пароль для подключения к GPRS
 
 
// инициализируем экземпляры классов
GPRS gprs;
GSM gsmAccess;     // для включения режима отладки добавьте параметр 'true'
GSMServer server(80); // порт 80 (по умолчанию для http)
 
// таймаут
const unsigned long __TIMEOUT__ = 10*1000;
 
void setup()
{
  // инициализируем последовательный интерфейс передачи данных
  Serial.begin(9600);
  Serial.println("START");
  // состояние соединения
  boolean notConnected = true;
 
  // запускаем GSM-плату расширения
  // если на вашей SIM-карте установлен PIN-код - укажите его в качестве параметра функции begin()
  while(notConnected)
  {  Serial.println("Connecting...");
    if((gsmAccess.begin(PINNUMBER)==GSM_READY) &
        (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD)==GPRS_READY)){
        notConnected = false;
        Serial.println("In here trying");
        }else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
 
  Serial.println("Connected to GPRS network");
 
  // запускаем сервер
  server.begin();
 
  // получаем IP
  IPAddress LocalIP = gprs.getIPAddress();
  Serial.println("Server IP address=");
  Serial.println(LocalIP);
}
 
void loop() {
 
 
  GSM3MobileClientService client = server.available();
 
 
 
  if (client)
  {  
    while (client.connected())
    {
      if (client.available())
      {
        Serial.println("Receiving request!");
        bool sendResponse = false;
        while(char c=client.read()) {
          if (c == '\n') sendResponse = true;
        }
 
       if (sendResponse)
       {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("");
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(analogRead(analogChannel));
            client.println("<br>");       
          }
          client.println("");
          delay(1000);
          client.stop();
        }
      }
    }
  }
}
