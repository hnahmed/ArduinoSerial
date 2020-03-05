#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void setup() {
  USART_Init(MYUBRR);
  USART_Transmit('0');
  // put your setup code here, to run once:
  //Serial.begin(9600);
}

unsigned char status = '1';
void loop() {

  if(RXC0){
    status=USART_Receive();
    USART_Transmit(status);
  }
  /*if(Serial.available()>0){
    status = Serial.read();
    Serial.print(status - '0');
  }*/
}

void USART_Init( unsigned int ubrr)
{
  //Set baud rate
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  //Enable rx and tx
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  //Set frame format
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data)
{
  while( !( UCSR0A & (1<<UDRE0)) )
    ;
  //put data into buffer
  UDR0 = data;
}

unsigned char USART_Receive( void )
{
  //wait for data to be received
  while( !(UCSR0A & (1<<RXC0)) )
    ;

  //Get and return received data from buffer
  return UDR0;
}
