void loop()
{  
  OSC_Decode();
  // is configuration portal requested?
  if ((digitalRead(TRIGGER_PIN) == LOW) || (initialConfig))
  {
    WifiPortal();
  }
}
