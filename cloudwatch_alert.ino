#include <SPI.h>
#include <Ethernet.h>

// イーサネットシールドのMacアドレス
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x49, 0xDB };

// 接続サーバ
char server[] = "example.com";

// 接続ポート
int port = 3000;

// 何秒おきにアクセスするか
int loopSecond = 60;

// 自身にふられるIPアドレス
IPAddress ip( 192, 168, 0, 177 );
EthernetClient client;

int pin = 4;
void setup() {
  serialOut();
  pinMode( 4, OUTPUT );
  pinMode( 5, OUTPUT );
  pinMode( 6, OUTPUT );
  pinMode( 7, OUTPUT );
  pinMode( 8, OUTPUT );
  pinMode( 9, OUTPUT );
}

int count = 0;
bool cloudWatchError = false;
void loop() {
  digitalWrite( 4, LOW );
  digitalWrite( 5, LOW );
  digitalWrite( 6, LOW );
  digitalWrite( 7, LOW );
  digitalWrite( 8, LOW );
  digitalWrite( 9, LOW );
  if ( count > 10 * loopSecond && connection() ) {
    String text = access();
    cloudWatchError = hasError( text );
    disconnection();

    count = 0;
  }
  
  if ( cloudWatchError ) {
    Serial.println( "cloudWatchState" );
    digitalWrite( pin, HIGH );
    pin++;
    if ( pin == 10 ) pin = 4;
  }
  count++;
  delay( 100 );
}

void serialOut () {
  Serial.begin( 9600 );
  while ( !Serial );
}

bool hasError ( String text ) {
  if ( text.startsWith( "HTTP/1.1 200 OK" ) ) return false;
  return true;
}

bool connection () {
  if ( Ethernet.begin( mac ) == 0 ) {
    Ethernet.begin( mac, ip );
  }

  Serial.println( "connecting..." );

  int state = client.connect( server, 3000 );
  if ( state ) {
    Serial.println( "connected" );
    return true;
  } else {
    Serial.println( "connection failed [" + String( state ) + "]" );
    delay( 1000 );
    return connection();
  }
}

String access () {
  String str;
  client.println( "GET / HTTP/1.1" );
  client.println( "Host: " + String( server ) + ":" + String( port ) );
  client.println( "Connection: close" );
  client.println();
  while ( !client.available() );
  while ( !client.connected() );
  while ( client.available() ) {
    char c = client.read();
    str.concat( c );
  }
  client.flush();
  return str;
}

void disconnection () {
  if ( !client.connected() ) {
    Serial.println();
    Serial.println( "disconnecting." );
    client.stop();
  }
}

