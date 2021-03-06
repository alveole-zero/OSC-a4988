int packetSize;
char incomingPacket[255];

void toggle1(OSCMessage &msg)
//This function is called by OSC_Decode() depending on msg.dispatch()
{
  if(msg.isFloat(0))
  {
    if (DEBUG_LEVEL >=1 ) Serial.println("Float received");
    float val = msg.getFloat(0);
    Serial.print("button1 = ");
    Serial.print(val);
    Serial.println("");
    if(val == 1.0)
    {
      digitalWrite(MS1_PIN,HIGH);
    }
    else
    {
      digitalWrite(MS1_PIN,LOW);
    }
  }
}

void toggle2(OSCMessage &msg)
//This function is called by OSC_Decode() depending on msg.dispatch()
{
  if(msg.isFloat(0))
  {
    if (DEBUG_LEVEL >=1 ) Serial.println("Float received");
    float val = msg.getFloat(0);
    Serial.print("button1 = ");
    Serial.print(val);
    Serial.println("");
    if(val == 1.0)
    {
      digitalWrite(MS2_PIN,HIGH);
    }
    else
    {
      digitalWrite(MS2_PIN,LOW);
    }
  }
}

void toggle3(OSCMessage &msg)
//This function is called by OSC_Decode() depending on msg.dispatch()
{
  if(msg.isFloat(0))
  {
    if (DEBUG_LEVEL >=1 ) Serial.println("Float received");
    float val = msg.getFloat(0);
    Serial.print("button1 = ");
    Serial.print(val);
    Serial.println("");
    if(val == 1.0)
    {
      digitalWrite(MS3_PIN,HIGH);
    }
    else
    {
      digitalWrite(MS3_PIN,LOW);
    }
  }
}


void slider1(OSCMessage &msg)
{
  float pipi;
  int stepstogo=0;
  pipi = msg.getFloat(0);
  Serial.print("stepstogo=");
  stepstogo = pipi;//*stepsPerRevolution;
  Serial.print(stepstogo);
  for(int i=0;i<stepstogo;i++)
  {
    digitalWrite(STEP_PIN,HIGH);
    delay(attente);
    digitalWrite(STEP_PIN,LOW);
    delay(attente);    
  }
  Serial.println(" Done");
}

void slider2(OSCMessage &msg)
{
  float pipi;
  pipi = msg.getFloat(0);
  Serial.print("slider2=");
  Serial.println(pipi);  
  attente = pipi;
}

void slider3(OSCMessage &msg)
{
  float pipi;
  pipi = msg.getFloat(0);
  Serial.print("slider3=");
  Serial.println(pipi);  
}

void slider4(OSCMessage &msg)
{
  float pipi;
  pipi = msg.getFloat(0);
  Serial.print("slider4=");
  Serial.println(pipi);  
}

void OSC_Decode()
{
//Read UDP Frame and parse OSC
  packetSize = Udp.parsePacket();
  if (packetSize)
  {
    if (DEBUG_LEVEL >= 1) Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    OSCMessage msg;
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    if (DEBUG_LEVEL >= 1) Serial.print("UDP packet contents: ");
    for(int i=0;i<len;i++)
    {
      msg.fill(incomingPacket[i]);
      if (DEBUG_LEVEL >= 1) Serial.print(incomingPacket[i]);
    }
    if (DEBUG_LEVEL >= 1) Serial.println(" ");

//Dispatch OSC messages to actions (modify code bellow)
    msg.dispatch("/oscControl/slider1 ", slider1);
    msg.dispatch("/oscControl/slider2", slider2);
    msg.dispatch("/oscControl/slider3", slider3);
    msg.dispatch("/oscControl/slider4", slider4);
    msg.dispatch("/oscControl/toggle1", toggle1);
    msg.dispatch("/oscControl/toggle2", toggle2);
    msg.dispatch("/oscControl/toggle3", toggle3);
    if (DEBUG_LEVEL >= 1) Serial.println(" ");
  }
}
