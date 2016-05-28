#include <SPI.h> 
#include <Ethernet.h> //Declaración de la direcciones MAC e IP. También del puerto 80 
byte mac[]={0xDE,0xAD,0xBE,0xEF,0xFE,0xED}; //MAC 
IPAddress ip(192,168,1,100); //IP 
char ser[] = "http://localhost/Sybil/Menu.php";
EthernetClient cli;
EthernetServer servidor(80); 
int PIN_LED=8; 
String readString=String(30); //lee los caracteres de una secuencia en una cadena.
//Los strings se representan como arrays de caracteres (tipo char) 
String state=String(3);
void setup() {
Serial.begin(9600);
Ethernet.begin(mac, ip); //Inicializamos con las direcciones asignadas 
servidor.begin(); 
pinMode(PIN_LED,OUTPUT);
digitalWrite(PIN_LED,LOW);
state="OFF";
if(cli.connect(ser, 80)){
  Serial.println("Serial");
}
}
void loop() {
  //EthernetClient Crea un cliente que se puede conectar a 
  //una dirección específica de Internet IP
EthernetClient cliente= servidor.available(); 
if(cliente) {
boolean lineaenblanco=true; 
while(cliente.connected()) {
if(cliente.available()) {
char c=cliente.read(); 
if(readString.length()<30) {
readString.concat(c);
//Cliente conectado
//Leemos petición HTTP caracter a caracter
//Almacenar los caracteres en la variable readString
} 
if(c=='\n' && lineaenblanco) //Si la petición HTTP ha finalizado 
{
int LED = readString.indexOf("LED="); 
if(readString.substring(LED,LED+5)=="LED=T") {
digitalWrite(PIN_LED,HIGH);
state="ON"; 
cli.println("GET ?alarmast=on HTTP/1.1");
cli.println("HOST http://localhost/Sybil/Menu.php");
} 
else if (readString.substring(LED,LED+5)=="LED=F") {
digitalWrite(PIN_LED,LOW); 
state="OFF";
cli.println("GET ?alarmast=off HTTP/1.1");
cli.println("HOST http://localhost/Sybil/Menu.php");
}
if (cli.available()) {
    char c = client.read();
    Serial.print(c);
  }
//Cabecera HTTP estándar
cliente.println("HTTP/1.1 200 OK"); 
cliente.println("Content-Type: text/html"); 
cliente.println(); //Página Web en HTML 
cliente.println("<html>"); 
cliente.println("<head>"); 
cliente.println("<title>ALARMA ON/OFF</title>"); 
cliente.println("</head>");
cliente.println("<body width=100% height=100%>"); 
cliente.println("<center>"); 
cliente.println("<h1>ALARMA ON/OFF</h1>");
cliente.print("<br><br>"); 
cliente.print("Estado de la ALARMA: "); 
cliente.print(state); 
cliente.print("<br><br><br><br>"); 
cliente.println("<input type=submit value=ON style=width:200px;height:75px onClick=location.href='./?LED=T\'>"); 
cliente.println("<input type=submit value=OFF style=width:200px;height:75px onClick=location.href='./?LED=F\'>"); 
cliente.println("</center>"); 
cliente.println("</body>"); 
cliente.println("</html>"); 
cliente.stop();
//Cierro conexión con el cliente 
readString="";
}
}
}
}
}
