#include <WiFi.h>
#include <DHT.h>  

#define DHTPIN 4
#define DHTTYPE DHT11
#define MQPIN 34
#define SWITCH_PIN 14
#define BUZZER_PIN 25

DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "vivo";
const char* password = "12345678";

unsigned long buttonPressStart = 0;
bool buttonPressed   = false;
unsigned long buzzerStartTime = 0;
bool buzzerOn        = false;

WiFiServer server(80);

// ── helper: send CORS + no-cache headers ──────────────────────────────────────
void sendHeaders(WiFiClient& client, const String& contentType, int len) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: " + contentType);
  client.println("Connection: close");
  client.println("Cache-Control: no-cache, no-store, must-revalidate");
  client.println("Access-Control-Allow-Origin: *");
  client.print("Content-Length: ");
  client.println(len);
  client.println();
}

// ── the full HTML page (served once, JS polls /data every second) ─────────────
const char PAGE_HTML[] PROGMEM = R"rawhtml(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>ESP32 Live Dashboard</title>
<link href="https://fonts.googleapis.com/css2?family=Share+Tech+Mono&family=Rajdhani:wght@500;700&display=swap" rel="stylesheet">
<style>
  :root {
    --bg:     #080c10;
    --panel:  #0d1520;
    --border: #1a2d45;
    --cyan:   #00e5ff;
    --green:  #00ff88;
    --red:    #ff3c5a;
    --yellow: #ffd600;
    --muted:  #3a5068;
    --text:   #cde8ff;
  }
  * { box-sizing: border-box; margin: 0; padding: 0; }

  body {
    background: var(--bg);
    font-family: 'Share Tech Mono', monospace;
    color: var(--text);
    min-height: 100vh;
    display: flex;
    flex-direction: column;
    align-items: center;
    padding: 36px 16px 48px;
  }

  /* scanline overlay */
  body::before {
    content: '';
    position: fixed; inset: 0;
    background: repeating-linear-gradient(
      0deg,
      transparent,
      transparent 3px,
      rgba(0,0,0,0.08) 3px,
      rgba(0,0,0,0.08) 4px
    );
    pointer-events: none;
    z-index: 999;
  }

  header {
    text-align: center;
    margin-bottom: 40px;
  }
  header h1 {
    font-family: 'Rajdhani', sans-serif;
    font-size: clamp(1.8rem, 5vw, 3rem);
    font-weight: 700;
    color: var(--cyan);
    letter-spacing: 6px;
    text-transform: uppercase;
    text-shadow: 0 0 20px rgba(0,229,255,0.5);
  }
  header p {
    font-size: 0.72rem;
    color: var(--muted);
    letter-spacing: 2px;
    margin-top: 4px;
  }

  /* status bar */
  #status-bar {
    display: flex;
    align-items: center;
    gap: 8px;
    font-size: 0.7rem;
    color: var(--muted);
    margin-bottom: 32px;
    letter-spacing: 1px;
  }
  #dot {
    width: 8px; height: 8px;
    border-radius: 50%;
    background: var(--green);
    box-shadow: 0 0 8px var(--green);
    animation: pulse 1.4s ease-in-out infinite;
  }
  #dot.err { background: var(--red); box-shadow: 0 0 8px var(--red); animation: none; }
  @keyframes pulse {
    0%,100% { opacity:1; } 50% { opacity:0.3; }
  }

  /* grid */
  .grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    gap: 20px;
    width: 100%;
    max-width: 860px;
  }

  .card {
    background: var(--panel);
    border: 1px solid var(--border);
    border-radius: 12px;
    padding: 24px 20px 20px;
    position: relative;
    overflow: hidden;
    transition: border-color 0.3s, box-shadow 0.3s;
  }
  .card::before {           /* accent top bar */
    content: '';
    position: absolute;
    top: 0; left: 0; right: 0;
    height: 2px;
    background: var(--accent, var(--cyan));
    box-shadow: 0 0 12px var(--accent, var(--cyan));
    transition: background 0.3s, box-shadow 0.3s;
  }
  .card.alert {
    border-color: var(--red);
    box-shadow: 0 0 24px rgba(255,60,90,0.2);
    --accent: var(--red);
  }
  .card.good {
    border-color: var(--border);
    --accent: var(--cyan);
  }

  .card-label {
    font-size: 0.65rem;
    letter-spacing: 3px;
    text-transform: uppercase;
    color: var(--muted);
    margin-bottom: 12px;
  }
  .card-icon {
    font-size: 1.4rem;
    margin-bottom: 6px;
  }
  .card-value {
    font-family: 'Rajdhani', sans-serif;
    font-size: 3rem;
    font-weight: 700;
    line-height: 1;
    color: var(--accent, var(--cyan));
    text-shadow: 0 0 16px var(--accent, var(--cyan));
    transition: color 0.3s, text-shadow 0.3s;
    letter-spacing: 1px;
  }
  .card-unit {
    font-size: 0.8rem;
    color: var(--muted);
    margin-top: 6px;
    letter-spacing: 1px;
  }

  /* bar for gas */
  .bar-wrap {
    margin-top: 14px;
    background: #111e2a;
    border-radius: 4px;
    height: 6px;
    overflow: hidden;
  }
  .bar-fill {
    height: 100%;
    border-radius: 4px;
    background: var(--accent, var(--cyan));
    box-shadow: 0 0 6px var(--accent, var(--cyan));
    transition: width 0.6s ease, background 0.3s;
  }

  /* badge for button/buzzer */
  .badge {
    display: inline-block;
    font-size: 0.75rem;
    padding: 4px 14px;
    border-radius: 99px;
    letter-spacing: 2px;
    font-weight: bold;
    margin-top: 10px;
    border: 1px solid currentColor;
    transition: all 0.2s;
  }
  .badge.on  { color: var(--red);   box-shadow: 0 0 10px rgba(255,60,90,0.4); }
  .badge.off { color: var(--green); box-shadow: 0 0 10px rgba(0,255,136,0.3); }

  /* last update timestamp */
  #last-update {
    margin-top: 32px;
    font-size: 0.65rem;
    color: var(--muted);
    letter-spacing: 1px;
  }

  /* number flip animation */
  @keyframes flipIn {
    from { opacity:0; transform: translateY(-6px); }
    to   { opacity:1; transform: translateY(0); }
  }
  .flip { animation: flipIn 0.25s ease; }
</style>
</head>
<body>

<header>
  <h1>&#9641; ESP32 Live</h1>
  <p>REAL-TIME SENSOR DASHBOARD</p>
</header>

<div id="status-bar">
  <div id="dot"></div>
  <span id="status-text">CONNECTING...</span>
</div>

<div class="grid">

  <!-- Temperature -->
  <div class="card good" id="card-temp">
    <div class="card-label">Temperature</div>
    <div class="card-icon">🌡</div>
    <div class="card-value" id="val-temp">--</div>
    <div class="card-unit">DEGREES CELSIUS</div>
  </div>

  <!-- Humidity -->
  <div class="card good" id="card-hum">
    <div class="card-label">Humidity</div>
    <div class="card-icon">💧</div>
    <div class="card-value" id="val-hum">--</div>
    <div class="card-unit">PERCENT RELATIVE</div>
  </div>

  <!-- Gas -->
  <div class="card good" id="card-gas">
    <div class="card-label">Gas / Air Quality</div>
    <div class="card-icon">🧪</div>
    <div class="card-value" id="val-gas">--</div>
    <div class="card-unit" id="unit-gas">RAW ADC (0–4095)</div>
    <div class="bar-wrap">
      <div class="bar-fill" id="bar-gas" style="width:0%"></div>
    </div>
  </div>

  <!-- Button -->
  <div class="card good" id="card-btn">
    <div class="card-label">Button / Switch</div>
    <div class="card-icon">🔘</div>
    <div class="card-value" id="val-btn" style="font-size:1.6rem">RELEASED</div>
    <div><span class="badge off" id="badge-btn">OFF</span></div>
  </div>

  <!-- Buzzer -->
  <div class="card good" id="card-buz">
    <div class="card-label">Buzzer</div>
    <div class="card-icon">🔔</div>
    <div class="card-value" id="val-buz" style="font-size:1.6rem">IDLE</div>
    <div><span class="badge off" id="badge-buz">OFF</span></div>
  </div>

</div>

<div id="last-update">LAST UPDATE: --</div>

<script>
  function animateValue(el, newText) {
    if (el.textContent === newText) return;
    el.classList.remove('flip');
    void el.offsetWidth; // reflow
    el.textContent = newText;
    el.classList.add('flip');
  }

  function setAlert(cardId, isAlert) {
    const c = document.getElementById(cardId);
    c.classList.toggle('alert', isAlert);
    c.classList.toggle('good',  !isAlert);
    // update CSS variable for accent
    c.style.setProperty('--accent', isAlert ? 'var(--red)' : 'var(--cyan)');
  }

  async function fetchData() {
    try {
      const res = await fetch('/data', { cache: 'no-store' });
      if (!res.ok) throw new Error('bad response');
      const d = await res.json();

      // Status bar
      document.getElementById('dot').className = '';
      document.getElementById('status-text').textContent = 'LIVE · ESP32';

      // Temperature
      const tempOk = d.temp !== null;
      animateValue(document.getElementById('val-temp'), tempOk ? d.temp.toFixed(1) : 'ERR');
      setAlert('card-temp', tempOk && d.temp > 38);

      // Humidity
      const humOk = d.hum !== null;
      animateValue(document.getElementById('val-hum'), humOk ? d.hum.toFixed(1) : 'ERR');
      setAlert('card-hum', humOk && d.hum > 80);

      // Gas
      animateValue(document.getElementById('val-gas'), d.gas);
      const gasPct = Math.min(100, Math.round(d.gas / 4095 * 100));
      document.getElementById('bar-gas').style.width = gasPct + '%';
      const gasHigh = d.gas > 2000;
      document.getElementById('unit-gas').textContent = gasHigh ? '⚠ HIGH LEVEL' : 'NORMAL';
      setAlert('card-gas', gasHigh);

      // Button
      const btn = d.button;
      animateValue(document.getElementById('val-btn'), btn ? 'PRESSED' : 'RELEASED');
      document.getElementById('badge-btn').textContent = btn ? 'ON' : 'OFF';
      document.getElementById('badge-btn').className = 'badge ' + (btn ? 'on' : 'off');
      setAlert('card-btn', btn);

      // Buzzer
      const buz = d.buzzer;
      animateValue(document.getElementById('val-buz'), buz ? 'ACTIVE' : 'IDLE');
      document.getElementById('badge-buz').textContent = buz ? 'ON' : 'OFF';
      document.getElementById('badge-buz').className = 'badge ' + (buz ? 'on' : 'off');
      setAlert('card-buz', buz);

      // Timestamp
      document.getElementById('last-update').textContent =
        'LAST UPDATE: ' + new Date().toLocaleTimeString();

    } catch (e) {
      document.getElementById('dot').className = 'err';
      document.getElementById('status-text').textContent = 'CONNECTION LOST — RETRYING...';
    }
  }

  // Poll every 1 second
  fetchData();
  setInterval(fetchData, 1000);
</script>
</body>
</html>
)rawhtml";

// ── build JSON string from current sensor readings ────────────────────────────
String buildJSON() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();
  int   gas  = analogRead(MQPIN);
  bool  btn  = digitalRead(SWITCH_PIN);

  String json = "{";
  json += "\"temp\":"   + (isnan(temp) ? String("null") : String(temp, 2)) + ",";
  json += "\"hum\":"    + (isnan(hum)  ? String("null") : String(hum, 2))  + ",";
  json += "\"gas\":"    + String(gas)  + ",";
  json += "\"button\":" + String(btn ? "true" : "false") + ",";
  json += "\"buzzer\":" + String(buzzerOn ? "true" : "false");
  json += "}";
  return json;
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  dht.begin();
  pinMode(MQPIN,      INPUT);
  pinMode(SWITCH_PIN, INPUT_PULLDOWN);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  // ---------- BUTTON & BUZZER LOGIC ----------
  bool switchState = digitalRead(SWITCH_PIN);

  if (switchState) {
    if (!buttonPressed) {
      buttonPressed    = true;
      buttonPressStart = millis();
    } else if ((millis() - buttonPressStart >= 3000) && !buzzerOn) {
      buzzerOn        = true;
      buzzerStartTime = millis();
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.println("Buzzer ON");
    }
  } else {
    buttonPressed    = false;
    buttonPressStart = 0;
  }

  if (buzzerOn && (millis() - buzzerStartTime >= 5000)) {
    buzzerOn = false;
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Buzzer OFF");
  }

  // ---------- HANDLE CLIENT ----------
  WiFiClient client = server.available();
  if (!client) return;

  // Read request with timeout
  unsigned long t0 = millis();
  String request = "";
  while (client.connected() && millis() - t0 < 2000) {
    if (client.available()) {
      char c = client.read();
      request += c;
      if (request.endsWith("\r\n\r\n")) break;
    }
  }

  // Route: GET /data  → JSON
  // Route: GET /      → full HTML page
  if (request.indexOf("GET /data") >= 0) {
    String json = buildJSON();
    sendHeaders(client, "application/json", json.length());
    client.print(json);

  } else {
    // Serve the HTML page
    int pageLen = strlen_P(PAGE_HTML);
    sendHeaders(client, "text/html; charset=UTF-8", pageLen);
    // Send in chunks to avoid large stack allocation
    const int CHUNK = 512;
    char buf[CHUNK + 1];
    int sent = 0;
    while (sent < pageLen) {
      int sz = min(CHUNK, pageLen - sent);
      memcpy_P(buf, PAGE_HTML + sent, sz);
      buf[sz] = 0;
      client.print(buf);
      sent += sz;
    }
  }

  delay(1);
  client.stop();
}
