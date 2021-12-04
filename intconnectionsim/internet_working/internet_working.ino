void setup() {

  char http_cmd[] = "GET /home/ivddorrka/trdir/hello.txt HTTP/1.0\r\n\r\n";
  char num[4];
  int len = sizeof(http_cmd)-1;
  itoa(len, num, 10);
  Serial.begin(9600);
  Serial.print("AT+CIPSEND=");
  Serial.print(num);
  Serial.print("\r\n");
  
  

  Serial.print("AT+CSTT=\"internet\",\"\",\"\"\r\n");
  delay(200);
  Serial.print("AT+CIICR\r\n");
  delay(200);
  
  
  //connect
  Serial.print("AT+CIPSTART=\"TCP\",\"google.com\",80\r\n");
  delay(200);

  Serial.print("AT+CIPSEND=48\r\n");
  delay(500);
  Serial.print("GET /home/ivddorrka/trdir/hello.txt HTTP/1.0\r\n\r\n");
  Serial.write((char)26);
  delay(120000);
  
  //close TCP
  Serial.print("AT+CIPCLOSE\r\n");
  
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
