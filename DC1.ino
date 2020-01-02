#define MY_DEBUG 
#define MY_RADIO_RF24

#include <MySensors.h>
#include <Bounce2.h>
MyMessage msg(1,V_STATUS);
MyMessage msg1(2,V_STATUS);
MyMessage msg2(3,V_STATUS);
MyMessage msg4(3,V_STATUS);

Bounce debouncer = Bounce(); 
int oldValue = 0;
bool state = false;

Bounce debouncer1 = Bounce(); 
int oldValue1 = 0;
bool state1 = false;

Bounce debouncer2 = Bounce(); 
int oldValue2 = 0;
bool state2 = false;

Bounce debouncer3 = Bounce(); 
int oldValue3 = 0;
bool state3 = false;

void setup() {
  pinMode(7, INPUT_PULLUP);
  debouncer.attach(7);
  debouncer.interval(5);

  pinMode(4, INPUT_PULLUP);
  debouncer1.attach(4);
  debouncer1.interval(5);

  pinMode(3, INPUT_PULLUP);
  debouncer2.attach(3);
  debouncer2.interval(5);
  
  pinMode(2, INPUT_PULLUP);
  debouncer3.attach(2);
  debouncer3.interval(5);

  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A5, OUTPUT);

  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  analogWrite(5, HIGH);

  analogWrite(4, HIGH);
  analogWrite(3, HIGH);
}

void presentation()  {
  sendSketchInfo("斐讯DC1", "1.0");
  present(1, S_LIGHT);
  present(2, S_LIGHT);
  present(3, S_LIGHT);
  present(4, S_LIGHT);
  
  send(msg4.set(true));
  send(msg.set(true));
  send(msg1.set(true));
  send(msg2.set(true));
}

void loop() {
  debouncer.update();
  int value = debouncer.read();
  if (value != oldValue && value==0) {
    state = state?false:true;
    send(msg4.set(state)); 
  }
  oldValue = value;

  debouncer1.update();
  int value1 = debouncer1.read();
  if (value1 != oldValue1 && value1==0) {
    state1 = state1?false:true;
    digitalWrite(5, state1?HIGH:LOW);
    send(msg.set(state1)); 
  }
  oldValue1 = value1;

  debouncer2.update();
  int value2 = debouncer2.read();
  if (value2 != oldValue2 && value2==0) {
    state2 = state2?false:true;
    digitalWrite(6, state2?HIGH:LOW);
    send(msg1.set(state2)); 
  }
  oldValue2 = value2;

  debouncer3.update();
  int value3 = debouncer3.read();
  if (value3 != oldValue3 && value3==0) {
    state3 = state3?false:true;
    analogWrite(5, state3?HIGH:LOW);
    send(msg2.set(state3)); 
  }
  oldValue3 = value3;
} 

void receive(const MyMessage &message) {
  if (message.isAck()) {
     Serial.println("This is an ack from gateway");
  }

  if (message.type == V_STATUS && message.sensor==1) {
     state1 = message.getBool();
     digitalWrite(7, state1?HIGH:LOW);
     send(msg.set(state1));
     return;
   }

  if (message.type == V_STATUS && message.sensor==2) {
     state2 = message.getBool();
     digitalWrite(6, state2?HIGH:LOW);
     send(msg1.set(state2));
     return;
   }

  if (message.type == V_STATUS && message.sensor==3) {
     state3 = message.getBool();
     digitalWrite(5, state3?HIGH:LOW);
     send(msg2.set(state3));
     return;
   } 
}
