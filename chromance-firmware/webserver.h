/*********
 * Superkartoffel derived this from: 

  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-web-server-slider-pwm/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const int output = 2;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

const char* PARAM_INPUT_VALUE = "value";
const char* PARAM_INPUT_INDEX = "param";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Chromance</title>
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 2.3rem;}
    p {font-size: 1.9rem;}
    body {max-width: 400px; margin:0px auto; padding-bottom: 25px;}
    .slider { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}
    .slider::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; } 
  </style>
</head>
<body>
  <h2>Chromance</h2>
  <p>Overall brightness: <span id="brightnessTextValue">%BRIGHTNESS_VALUE%</span></p>
  <p><input type="range" onchange="updateSlider(this.value, 'brightnessTextValue', 'brightnessSlider', 'brightness')" id="brightnessSlider" min=".1" max="1.0" value="%BRIGHTNESS_VALUE%" step=".1" class="slider"></p>
  <p>Load a template:</p>
  <p><select id="templateSelect" onchange="selectTemplate(this)">
    <option value="null" disabled="true" selected="selected">Choose a template</option>
    </select></p>
  <p>Decay: <span id="decayTextValue">%DECAY_VALUE%</span></p>
  <p><input type="range" onchange="updateSlider(this.value, 'decayTextValue', 'decaySlider', 'decay')" id="decaySlider" min=".90" max=".99" value="%DECAY_VALUE%" step=".01" class="slider"></p>
  <p>PulseTime: <span id="pulseTimeTextValue">%PULSE_TIME_VALUE%</span></p>
  <p><input type="range" onchange="updateSlider(this.value, 'pulseTimeTextValue', 'pulseTimeSlider', 'pulseTime')" id="pulseTimeSlider" min="300" max="5000" value="%PULSE_TIME_VALUE%" step="100" class="slider"></p>
  <p>Lifespan: <span id="lifespanTextValue">%LIFESPAN_VALUE%</span></p>
  <p><input type="range" onchange="updateSlider(this.value, 'lifespanTextValue', 'lifespanSlider', 'lifespan')" id="lifespanSlider" min="100" max="5000" value="%LIFESPAN_VALUE%" step="100" class="slider"></p>
  <p>MinSpeed: <span id="minSpeedTextValue">%MIN_SPEED_VALUE%</span></p>
  <p><input type="range" onchange="updateSlider(this.value, 'minSpeedTextValue', 'minSpeedSlider', 'minSpeed')" id="minSpeedSlider" min="0" max="2" value="%MIN_SPEED_VALUE%" step=".1" class="slider"></p>
  <p>Random Speed: <span id="rndSpeedTextValue">%RND_SPEED_VALUE%</span></p>
  <p><input type="range" onchange="updateSlider(this.value, 'rndSpeedTextValue', 'rndSpeedSlider', 'rndSpeed')" id="rndSpeedSlider" min="0" max="1" value="%RND_SPEED_VALUE%" step=".05" class="slider"></p>
  <p>Base Color: <span id="baseColorTextValue">%BASE_COLOR_VALUE%</span></p>
  <p><input type="range" onchange="updateSlider(this.value, 'baseColorTextValue', 'baseColorSlider', 'baseColor')" id="baseColorSlider" min="0" max="65535" value="%BASE_COLOR_VALUE%" step="10" class="slider"></p>
  <p>Color spread: <span id="colorSpreadTextValue">%COLOR_SPREAD_VALUE%</span></p>
  <p><input type="range" onchange="updateSlider(this.value, 'colorSpreadTextValue', 'colorSpreadSlider', 'colorSpread')" id="colorSpreadSlider" min="0" max="65535" value="%COLOR_SPREAD_VALUE%" step="10" class="slider"></p>
<script>
function updateSlider(sliderValue, textElmId, sliderElmId, paramName) {
  document.getElementById(textElmId).innerHTML = sliderValue;
  document.getElementById(sliderElmId).value = sliderValue;
  console.log(sliderValue);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/slider?value="+sliderValue+"&param="+paramName, true);
  xhr.send();
}
var templates = {
// Name,      Decay,  PulseT, Lifesp, MinSp,  RandomSp, BaseColor,Color spread
"Default":    [.95,   1000,   3000,   .5,     .2,       0,        65535],
"Lava":       [0.98,  600,    5000,   .5,     .05,      21200,    100],
"Water":      [.99,   600,    5000,   .3,     .05,      43520,    3350],
"Snakes":     [.9,    4600,   5000,   1.2,    0,        0,        65535],
"Fireworks":  [.9,    300,    800,    0,      .6,       0,        65535],
"Seashore":   [.98,   1000,   5000,   .3,     1,        54680,    1930],
};

function selectTemplate(sender) {
  var template = templates[sender.value];
  updateSlider(template[0], 'decayTextValue', 'decaySlider', 'decay');
  updateSlider(template[1], 'pulseTimeTextValue', 'pulseTimeSlider', 'pulseTime');
  updateSlider(template[2], 'lifespanTextValue', 'lifespanSlider', 'lifespan');
  updateSlider(template[3], 'minSpeedTextValue', 'minSpeedSlider', 'minSpeed');
  updateSlider(template[4], 'rndSpeedTextValue', 'rndSpeedSlider', 'rndSpeed');
  updateSlider(template[5], 'baseColorTextValue', 'baseColorSlider', 'baseColor');
  updateSlider(template[6], 'colorSpreadTextValue', 'colorSpreadSlider', 'colorSpread');
}
var templateSelect = document.getElementById("templateSelect");
for(key in templates)
{
   var opt = document.createElement("option");
   opt.value= key;
   opt.innerHTML = key;
   
   templateSelect.appendChild(opt);
}
</script>
</body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  if (var == "BRIGHTNESS_VALUE"){
    return String(brightness);
  }
  else if (var == "DECAY_VALUE"){
    return String(decay);
  }
  else if (var == "PULSE_TIME_VALUE"){
    return String(randomPulseTime);
  }
  else if (var == "LIFESPAN_VALUE"){
    return String(lifespan);
  }
  else if (var == "MIN_SPEED_VALUE"){
    return String(minSpeed);
  }
  else if (var == "RND_SPEED_VALUE"){
    return String(rndSpeed);
  }
  else if (var == "BASE_COLOR_VALUE"){
    return String(fixedBaseColor);
  }
  else if (var == "COLOR_SPREAD_VALUE"){
    return String(fixedColorSpread);
  }
  return String();
}

void processSliderChange(AsyncWebServerRequest *request) {
  String value;
  String param;

  if (request->hasParam(PARAM_INPUT_VALUE) && request->hasParam(PARAM_INPUT_INDEX)) {
    value = request->getParam(PARAM_INPUT_VALUE)->value();
    param = request->getParam(PARAM_INPUT_INDEX)->value();

    if (param == "brightness") {
      brightness = value.toFloat();
      request->send(200, "text/plain", "OK");
    } 
    else if (param == "decay") {
      decay = value.toFloat();
      request->send(200, "text/plain", "OK");
    }
    else if (param == "pulseTime")
    {
      randomPulseTime = value.toInt();
      request->send(200, "text/plain", "OK");
    }
    else if (param == "lifespan")
    {
      lifespan = value.toInt();
      request->send(200, "text/plain", "OK");
    }
    else if (param == "minSpeed")
    {
      minSpeed = value.toFloat();
      request->send(200, "text/plain", "OK");
    }
    else if (param == "rndSpeed")
    {
      rndSpeed = value.toFloat();
      request->send(200, "text/plain", "OK");
    }
    else if (param == "baseColor")
    {
      fixedBaseColor = value.toInt();
      request->send(200, "text/plain", "OK");
    }
    else if (param == "colorSpread")
    {
      fixedColorSpread = value.toInt();
      request->send(200, "text/plain", "OK");
    }
    else {
      request->send(400, "text/plain", "BAD REQUEST");      
    }
  }
  else 
  {
    request->send(400, "text/plain", "BAD REQUEST");    
  }
}
void setupWebServer(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/slider", HTTP_GET, &processSliderChange);

  server.begin();
}
