
#include <WiFi.h>
#include <HTTPClient.h>

//SENSORES
const int s1_trigPin = 5;
const int s1_echoPin = 18;
const int s2_trigPin = 19;
const int s2_echoPin = 21;

const int s3_trigPin = 12;
const int s3_echoPin = 14;
const int s4_trigPin = 22;
const int s4_echoPin = 23;
const float mind = 9.50;

int espacio;
//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
float s1_distanceCm;
float s2_distanceCm;
float s3_distanceCm;
float s4_distanceCm;

//Disponibilidad
int s1_disponibilidad;
int s2_disponibilidad;
int s3_disponibilidad;
int s4_disponibilidad;

// Replace with your network credentials
const char* ssid     = "RED JALISCO PRIVADA";
const char* password = "RedJalisco";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://10.145.134.26/db_esin/post-esp-data.php";

 

void setup() {
 Serial.begin(115200); // Starts the serial communication
  pinMode(s1_trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(s1_echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(s2_trigPin, OUTPUT); 
  pinMode(s2_echoPin, INPUT); 
  pinMode(s3_trigPin, OUTPUT); 
  pinMode(s3_echoPin, INPUT); 
  pinMode(s4_trigPin, OUTPUT); 
  pinMode(s4_echoPin, INPUT); 
  

  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
     // Clears the trigPin1
  digitalWrite(s1_trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(s1_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(s1_trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(s1_echoPin, HIGH);
  // Calculate the distance
  s1_distanceCm = duration * SOUND_SPEED/2;
  
 
  // Prints the distance in the Serial Monitor
  Serial.print("Distance1 (cm): ");
  Serial.println(s1_distanceCm);

  delay(1000);

    // Clears the trigPin2
  digitalWrite(s2_trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(s2_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(s2_trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(s2_echoPin, HIGH);
  // Calculate the distance
  s2_distanceCm = duration * SOUND_SPEED/2;
  
 
  // Prints the distance in the Serial Monitor
  Serial.print("Distance2 (cm): ");
  Serial.println(s2_distanceCm);

  delay(1000);

   // Clears the trigPin3
  digitalWrite(s3_trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(s3_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(s3_trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(s3_echoPin, HIGH);
  // Calculate the distance
  s3_distanceCm = duration * SOUND_SPEED/2;
  
 
  // Prints the distance in the Serial Monitor
  Serial.print("Distance3 (cm): ");
  Serial.println(s3_distanceCm);

  delay(1000);

   // Clears the trigPin4
  digitalWrite(s4_trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(s4_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(s4_trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(s4_echoPin, HIGH);
  // Calculate the distance
  s4_distanceCm = duration * SOUND_SPEED/2;
  
 
  // Prints the distance in the Serial Monitor
  Serial.print("Distance4 (cm): ");
  Serial.println(s4_distanceCm);

  delay(1000);

//Delimitar el sensor
if(s1_distanceCm< mind){
   s1_disponibilidad = 1;
Serial.println(s1_disponibilidad);
}else{
    s1_disponibilidad = 0;
    Serial.println(s1_disponibilidad);
}

if(s2_distanceCm<mind){
   s2_disponibilidad = 1; 
   Serial.println(s2_disponibilidad);
}else{
    s2_disponibilidad = 0;
    Serial.println(s2_disponibilidad);
}
if(s3_distanceCm<mind){
   s3_disponibilidad = 1; 
}else{
    s3_disponibilidad = 0;
}
if(s4_distanceCm<mind){
   s4_disponibilidad = 1; 
}else{
    s4_disponibilidad = 0;
}

  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String dis1String;
    String dis2String; 
    String dis3String;
    String dis4String;
    //parseo
    dis1String = String(s1_disponibilidad);
    dis2String = String(s2_disponibilidad);
    dis3String = String(s3_disponibilidad);
    dis4String = String(s4_disponibilidad);
    String httpRequestData ="s1=" +dis1String
                          + "&s2="+dis2String
                          + "&s3="+dis3String
                          + "&s4="+dis4String+ "";
                         
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
  
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(15000);  
}
