const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Drone</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
  }
  .tab1cards {
  display: flex;
  flex-direction: row;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 30px;
    max-width: 600px;
    margin: 0 auto;
  }
  .card {
    background-color: #F8F7F9;;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    padding-top:10px;
    padding-bottom:20px;
  }
  .button {
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: #0f8b8d;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .state {
     font-size: 1.5rem;
     color:#8c8c8c;
     font-weight: bold;
   }
  </style>
<title>Drone</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="topnav">
    <h1>Drone</h1>
  </div>
  <div class="content">
    <div class="card">
      <h2>Sensores</h2>
      <p class="ang">ang: <span id="ang">%ang%</span></p>
      <p class="pitch">angX: <span id="pitch">%angX%</span></p>
      <p class="roll">angY: <span id="roll">%angY%</span></p>
      <p class="dist">dist: <span id="dist">%dist%</span></p>
    </div>
    <div class="card">
      <p><button id="luz" class="button">Luz</button></p>
      <p><button id="sobe" class="button">Sobe</button></p>
      <p><button id="desce" class="button">Desce</button></p>
      <p><button id="frente" class="button">Frente</button></p>
      <p><button id="tras" class="button">Trás</button></p>
      <p><button id="esq" class="button">Esquerda</button></p>
      <p><button id="dir" class="button">Direita</button></p>
    </div>
  </div>
<script>
  var gateway = `ws://${window.location.hostname}:81`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(event) {
    var state;
    state = event.data.slice(1);
    console.log(event.data);
    switch(event.data[0]) {
      case 'a':
        document.getElementById('ang').innerHTML = state;
        break;
      case 'o':
        document.getElementById('pitch').innerHTML = state;
        break;
      case 'r':
        document.getElementById('roll').innerHTML = state;
        break;
      case 'd':
        document.getElementById('dist').innerHTML = state;
        break;
      default:
        document.getElementById('ang').innerHTML = "erro";
        break;
      }
  }
  function onLoad(event) {
    initWebSocket();
    initButtons();
  }
  function initButtons() {
    document.getElementById('buttonLuz').addEventListener('clickLuz', luz);
    document.getElementById('buttonSobe').addEventListener('clickSobe', sobe);
    document.getElementById('buttonDesce').addEventListener('clickDesce', desce);
    document.getElementById('buttonFrente').addEventListener('clickFrente', frente);
    document.getElementById('buttonTras').addEventListener('clickTras', tras);
    document.getElementById('buttonEsq').addEventListener('clickEsq', esq);
    document.getElementById('buttonDir').addEventListener('clickDir', dir);
  }
  function luz(){
    websocket.send('l');
  }
  function sobe(){
    websocket.send('s');
  }
  function desce(){
    websocket.send('d');
  }
  function frente(){
    websocket.send('f');
  }
  function tras(){
    websocket.send('t');
  }
  function esq(){
    websocket.send('e');
  }
  function dir(){
    websocket.send('r');
  }
</script>
</body>
</html>
)rawliteral";
