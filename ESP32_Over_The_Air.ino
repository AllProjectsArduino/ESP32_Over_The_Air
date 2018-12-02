#include <ArduinoOTA.h> //lib do ArduinoOTA 

const char* ssid = "RedeWifi"; //nome da rede
const char* password = "12345678"; //senha da rede

void setup(){
  //inicia serial com 115200 bits por segundo
  Serial.begin(115200);

  Serial.println("Booting");

  //define wifi como station (estação)
  WiFi.mode(WIFI_STA);

  //inicializa wifi
  WiFi.begin(ssid, password);

  //enquanto o wifi não for conectado aguarda
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    //caso falha da conexão, reinicia esp
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // A porta fica default como 3232
  ArduinoOTA.setPort(3232);

  // Define o hostname (opcional)
  ArduinoOTA.setHostname("myesp32");

  // Define a senha (opcional)
  ArduinoOTA.setPassword("password123");

  // É possível definir uma criptografia hash md5 para a senha usando a função "setPasswordHash"
  // Exemplo de MD5 para senha "admin" = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  //define o que será executado quando o ArduinoOTA iniciar
  ArduinoOTA.onStart( startOTA ); //startOTA é uma função criada para simplificar o código

  //define o que será executado quando o ArduinoOTA terminar
  ArduinoOTA.onEnd( endOTA ); //endOTA é uma função criada para simplificar o código

  //define o que será executado quando o ArduinoOTA estiver gravando
  ArduinoOTA.onProgress( progressOTA ); //progressOTA é uma função criada para simplificar o código

  //define o que será executado quando o ArduinoOTA encontrar um erro
  ArduinoOTA.onError( errorOTA );//errorOTA é uma função criada para simplificar o código

  //inicializa ArduinoOTA
  ArduinoOTA.begin();

  //exibe pronto e o ip utilizado pelo ESP
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

//funções de exibição dos estágios de upload (start, progress, end e error) do ArduinoOTA
void startOTA()
{
  String type;

  //caso a atualização esteja sendo gravada na memória flash externa, então informa "flash"
  if (ArduinoOTA.getCommand() == U_FLASH)
    type = "flash";
  else  //caso a atualização seja feita pela memória interna (file system), então informa "filesystem"
    type = "filesystem"; // U_SPIFFS

  //exibe mensagem junto ao tipo de gravação
  Serial.println("Start updating " + type);
}

//exibe mensagem
void endOTA()
{
  Serial.println("\nEnd");
}

//exibe progresso em porcentagem
void progressOTA(unsigned int progress, unsigned int total)
{
  Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
}

//caso aconteça algum erro, exibe especificamente o tipo do erro
void errorOTA(ota_error_t error)
{
  Serial.printf("Error[%u]: ", error);

  if (error == OTA_AUTH_ERROR)
    Serial.println("Auth Failed");
  else if (error == OTA_BEGIN_ERROR)
    Serial.println("Begin Failed");
  else if (error == OTA_CONNECT_ERROR)
    Serial.println("Connect Failed");
  else if (error == OTA_RECEIVE_ERROR)
    Serial.println("Receive Failed");
  else if (error == OTA_END_ERROR)
    Serial.println("End Failed");
}

void loop()
{
  //Handle é descritor que referencia variáveis no bloco de memória
  //Ele é usado como um "guia" para que o ESP possa se comunicar com o computador pela rede
  ArduinoOTA.handle();
}
