#include <WiFi.h>
#include <WebServer.h>

// =====================================================
//                   WIFI SETTINGS
// =====================================================
const char* ssid = "divya";
const char* password = "divya123";

// =====================================================
//                 GLOBAL VARIABLES
// =====================================================
WebServer server(80);

bool isAuthenticated = false;
bool wifiConnected = false;
bool simulationMode = true;

String correctPassword = "1234";

int servoAngle = 90;
String motorState = "STOP";

unsigned long lastGPSUpdate = 0;
unsigned long lastSafetyCheck = 0;
unsigned long lastAutoDemo = 0;

float gpsLat = 17.3850;
float gpsLon = 78.4867;

// =====================================================
//               FUNCTION PROTOTYPES
// =====================================================
void connectWiFi();
void setupServer();

void handleRoot();
void handleStatus();
void handleCommand();
void handleBLEAuth();
void handleGPS();
void handleCamera();

void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopMotors();

void laserLeft();
void laserRight();
void laserCenter();

void updateGPS();
void safetyCheck();
void autoDemo();

void printSystemHeader();
void printHelp();

// =====================================================
//                        SETUP
// =====================================================
void setup() {
  Serial.begin(115200);
  delay(1200);

  printSystemHeader();

  Serial.println("[SYSTEM] Starting ESP32 bot simulation...");
  Serial.println("[CAMERA] Camera module initialized (simulation mode)");
  Serial.println();

  connectWiFi();
  setupServer();
  printHelp();

  Serial.println("[SYSTEM] Initialization complete.");
  Serial.println("[SYSTEM] Simulation mode active.");
  Serial.println("[SYSTEM] Waiting for browser commands...\n");
}

// =====================================================
//                         LOOP
// =====================================================
void loop() {
  server.handleClient();

  updateGPS();
  safetyCheck();

  // Auto demo every 20 seconds
  if (millis() - lastAutoDemo > 20000) {
    lastAutoDemo = millis();
    autoDemo();
  }
}

// =====================================================
//                  WIFI CONNECTION
// =====================================================
void connectWiFi() {
  Serial.println("[WIFI] Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 15) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;
    Serial.println("\n[WIFI] Wi-Fi connected successfully.");
    Serial.print("[WIFI] IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    wifiConnected = false;
    Serial.println("\n[WIFI] Wi-Fi connection failed.");
    Serial.println("[WIFI] Project will continue in simulation mode.");
  }

  Serial.println();
}

// =====================================================
//                  WEB SERVER SETUP
// =====================================================
void setupServer() {
  server.on("/", handleRoot);
  server.on("/status", handleStatus);
  server.on("/auth", handleBLEAuth);
  server.on("/cmd", handleCommand);
  server.on("/gps", handleGPS);
  server.on("/camera", handleCamera);

  server.begin();
  Serial.println("[SERVER] Web server started.");
}

// =====================================================
//                      ROOT PAGE
// =====================================================
void handleRoot() {
  String html = "";
  html += "<html><head><title>ESP32 Bot Simulation</title></head><body>";
  html += "<h2>ESP32 Bot Simulation Server</h2>";
  html += "<p>Available routes:</p>";
  html += "<ul>";
  html += "<li>/status</li>";
  html += "<li>/auth?pass=1234</li>";
  html += "<li>/cmd?move=forward</li>";
  html += "<li>/cmd?move=backward</li>";
  html += "<li>/cmd?move=left</li>";
  html += "<li>/cmd?move=right</li>";
  html += "<li>/cmd?move=stop</li>";
  html += "<li>/cmd?move=laser_left</li>";
  html += "<li>/cmd?move=laser_right</li>";
  html += "<li>/cmd?move=laser_center</li>";
  html += "<li>/gps</li>";
  html += "<li>/camera</li>";
  html += "</ul>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

// =====================================================
//                     STATUS PAGE
// =====================================================
void handleStatus() {
  String response = "";
  response += "========== BOT STATUS ==========\n";
  response += "Simulation Mode : " + String(simulationMode ? "YES" : "NO") + "\n";
  response += "Wi-Fi Connected : " + String(wifiConnected ? "YES" : "NO") + "\n";
  response += "Authenticated   : " + String(isAuthenticated ? "YES" : "NO") + "\n";
  response += "Motor State     : " + motorState + "\n";
  response += "Servo Angle     : " + String(servoAngle) + "\n";
  response += "GPS Latitude    : " + String(gpsLat, 6) + "\n";
  response += "GPS Longitude   : " + String(gpsLon, 6) + "\n";
  response += "Camera State    : SIMULATED STREAM READY\n";
  response += "================================\n";

  server.send(200, "text/plain", response);
  Serial.println("[STATUS] Status requested from browser.");
}

// =====================================================
//               BLE AUTH SIMULATION
// =====================================================
void handleBLEAuth() {
  if (!server.hasArg("pass")) {
    server.send(400, "text/plain", "Missing parameter: pass");
    Serial.println("[AUTH] Failed -> password parameter missing.");
    return;
  }

  String enteredPassword = server.arg("pass");

  Serial.println("\n[AUTH] BLE authentication request received.");
  Serial.print("[AUTH] Entered password: ");
  Serial.println(enteredPassword);

  if (enteredPassword == correctPassword) {
    isAuthenticated = true;
    server.send(200, "text/plain", "BLE Authentication SUCCESS");
    Serial.println("[AUTH] Authentication SUCCESS.\n");
  } else {
    isAuthenticated = false;
    server.send(403, "text/plain", "BLE Authentication FAILED");
    Serial.println("[AUTH] Authentication FAILED.\n");
  }
}

// =====================================================
//                   COMMAND HANDLER
// =====================================================
void handleCommand() {
  if (!isAuthenticated) {
    server.send(403, "text/plain", "Access Denied: Authenticate first using /auth?pass=1234");
    Serial.println("[CMD] Command rejected. User not authenticated.");
    return;
  }

  if (!server.hasArg("move")) {
    server.send(400, "text/plain", "Missing parameter: move");
    Serial.println("[CMD] Command rejected. 'move' parameter missing.");
    return;
  }

  String cmd = server.arg("move");
  Serial.print("[CMD] Received command: ");
  Serial.println(cmd);

  if (cmd == "forward") {
    moveForward();
  }
  else if (cmd == "backward") {
    moveBackward();
  }
  else if (cmd == "left") {
    turnLeft();
  }
  else if (cmd == "right") {
    turnRight();
  }
  else if (cmd == "stop") {
    stopMotors();
  }
  else if (cmd == "laser_left") {
    laserLeft();
  }
  else if (cmd == "laser_right") {
    laserRight();
  }
  else if (cmd == "laser_center") {
    laserCenter();
  }
  else {
    server.send(400, "text/plain", "Invalid command");
    Serial.println("[CMD] Invalid command.\n");
    return;
  }

  server.send(200, "text/plain", "Command executed: " + cmd);
  Serial.println("[CMD] Command executed successfully.\n");
}

// =====================================================
//                     GPS PAGE
// =====================================================
void handleGPS() {
  String response = "";
  response += "GPS DATA\n";
  response += "Latitude  : " + String(gpsLat, 6) + "\n";
  response += "Longitude : " + String(gpsLon, 6) + "\n";

  server.send(200, "text/plain", response);
  Serial.println("[GPS] GPS data requested from browser.");
}

// =====================================================
//                   CAMERA PAGE
// =====================================================
void handleCamera() {
  Serial.println("[CAMERA] Camera stream requested from browser.");

  String html = "";
  html += "<html><head><title>ESP32 Camera Simulation</title></head><body>";
  html += "<h2>ESP32 Camera Simulation</h2>";
  html += "<p>Camera Stream Active (Simulation Mode)</p>";
  html += "<p>No physical ESP32-CAM hardware connected.</p>";
  html += "<p>This endpoint represents live surveillance stream architecture.</p>";
  html += "<hr>";
  html += "<p><b>Frame Status:</b> Simulated Video Feed Ready</p>";
  html += "<p><b>Mode:</b> HTTP Camera Simulation</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

// =====================================================
//                 MOTOR SIMULATION
// =====================================================
void moveForward() {
  motorState = "FORWARD";
  Serial.println("[MOTOR] Robot moving FORWARD");
}

void moveBackward() {
  motorState = "BACKWARD";
  Serial.println("[MOTOR] Robot moving BACKWARD");
}

void turnLeft() {
  motorState = "LEFT";
  Serial.println("[MOTOR] Robot turning LEFT");
}

void turnRight() {
  motorState = "RIGHT";
  Serial.println("[MOTOR] Robot turning RIGHT");
}

void stopMotors() {
  motorState = "STOP";
  Serial.println("[MOTOR] Robot STOPPED");
}

// =====================================================
//              LASER / SERVO SIMULATION
// =====================================================
void laserLeft() {
  servoAngle -= 15;
  if (servoAngle < 0) servoAngle = 0;

  Serial.print("[SERVO] Laser moved LEFT | Angle: ");
  Serial.println(servoAngle);
}

void laserRight() {
  servoAngle += 15;
  if (servoAngle > 180) servoAngle = 180;

  Serial.print("[SERVO] Laser moved RIGHT | Angle: ");
  Serial.println(servoAngle);
}

void laserCenter() {
  servoAngle = 90;

  Serial.print("[SERVO] Laser moved CENTER | Angle: ");
  Serial.println(servoAngle);
}

// =====================================================
//                  GPS SIMULATION
// =====================================================
void updateGPS() {
  if (millis() - lastGPSUpdate > 5000) {
    lastGPSUpdate = millis();

    gpsLat += 0.0001;
    gpsLon += 0.0001;

    Serial.println("[GPS] 5-second GPS update sent to server.");
    Serial.print("[GPS] Latitude  : ");
    Serial.println(gpsLat, 6);
    Serial.print("[GPS] Longitude : ");
    Serial.println(gpsLon, 6);
    Serial.println();
  }
}

// =====================================================
//                   SAFETY CHECK
// =====================================================
void safetyCheck() {
  if (millis() - lastSafetyCheck > 3000) {
    lastSafetyCheck = millis();

    if (WiFi.status() == WL_CONNECTED) {
      wifiConnected = true;
    } else {
      if (wifiConnected == true) {
        Serial.println("[SAFETY] Wi-Fi lost detected.");
      }
      wifiConnected = false;
      stopMotors();
      Serial.println("[SAFETY] Motors stopped for safety due to Wi-Fi disconnect.\n");
    }
  }
}

// =====================================================
//                  AUTO DEMO MODE
// =====================================================
void autoDemo() {
  Serial.println("=========== AUTO DEMO START ===========");

  if (!isAuthenticated) {
    Serial.println("[AUTO] Not authenticated. Performing automatic auth simulation.");
    if (correctPassword == "1234") {
      isAuthenticated = true;
      Serial.println("[AUTO] Authentication success.");
    }
  }

  moveForward();
  delay(700);

  turnLeft();
  delay(700);

  turnRight();
  delay(700);

  moveBackward();
  delay(700);

  stopMotors();
  delay(700);

  laserLeft();
  delay(700);

  laserRight();
  delay(700);

  laserCenter();
  delay(700);

  Serial.println("[CAMERA] Simulated surveillance stream active.");
  delay(700);

  Serial.println("=========== AUTO DEMO END =============\n");
}

// =====================================================
//              SERIAL OUTPUT HELPERS
// =====================================================
void printSystemHeader() {
  Serial.println("=======================================");
  Serial.println("      ESP32 BOT FULL FINAL SIMULATION  ");
  Serial.println("=======================================");
  Serial.println("Features included:");
  Serial.println("1. Wi-Fi connection");
  Serial.println("2. Web command handling");
  Serial.println("3. BLE authentication simulation");
  Serial.println("4. Motor control simulation");
  Serial.println("5. Laser servo simulation");
  Serial.println("6. GPS data simulation");
  Serial.println("7. Safety stop logic");
  Serial.println("8. Camera endpoint simulation");
  Serial.println("=======================================\n");
}

void printHelp() {
  Serial.println("Use these browser routes after upload:");
  Serial.println("/");
  Serial.println("/status");
  Serial.println("/auth?pass=1234");
  Serial.println("/cmd?move=forward");
  Serial.println("/cmd?move=backward");
  Serial.println("/cmd?move=left");
  Serial.println("/cmd?move=right");
  Serial.println("/cmd?move=stop");
  Serial.println("/cmd?move=laser_left");
  Serial.println("/cmd?move=laser_right");
  Serial.println("/cmd?move=laser_center");
  Serial.println("/gps");
  Serial.println("/camera\n");
}
