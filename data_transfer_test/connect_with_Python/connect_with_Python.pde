import processing.net.*;

int port = 10001; // 適当なポート番号を設定

Server server;
byte[] byteBuffer = new byte[3];

void setup() {
  server = new Server(this, port);
  println("server address: " + server.ip()); // IPアドレスを出力
}

void draw() {
  Client client = server.available();
  if (client !=null) {
    int byteCount = client.readBytes(byteBuffer);
    String printString = new String(byteBuffer);
    if (byteCount > 0) {
      println(byteBuffer); // Pythonからのメッセージを出力
    } 
  } 
}
