void WifiPortal()
{
     Serial.println("Configuration portal requested");
     digitalWrite(PIN_LED, LOW); // turn the LED on by making the voltage LOW to tell us we are in configuration mode.
    //Local intialization. Once its business is done, there is no need to keep it around

    // Extra parameters to be configured
    // After connecting, parameter.getValue() will get you the configured value
    // Format: <ID> <Placeholder text> <default value> <length> <custom HTML> <label placement>

    // Thingspeak API Key - this is a straight forward string parameter
    WiFiManagerParameter p_thingspeakApiKey("thingspeakapikey", "Thingspeak API Key", thingspeakApiKey, 17);

    // DHT-22 sensor present or not - bool parameter visualized using checkbox, so couple of things to note
    // - value is always 'T' for true. When the HTML form is submitted this is the value that will be 
    //   sent as a parameter. When unchecked, nothing will be sent by the HTML standard.
    // - customhtml must be 'type="checkbox"' for obvious reasons. When the default is checked
    //   append 'checked' too
    // - labelplacement parameter is WFM_LABEL_AFTER for checkboxes as label has to be placed after the input field

    char customhtml[24] = "type=\"checkbox\"";
    if (sensorDht22)
    {
      strcat(customhtml, " checked");
    }
    WiFiManagerParameter p_sensorDht22("sensordht22", "DHT-22 Sensor", "T", 2, customhtml, WFM_LABEL_AFTER);

    // I2C SCL and SDA parameters are integers so we need to convert them to char array but
    // no other special considerations
    char convertedValue[3];
    sprintf(convertedValue, "%d", pinSda);
    WiFiManagerParameter p_pinSda("pinsda", "I2C SDA pin", convertedValue, 3);
    sprintf(convertedValue, "%d", pinScl);
    WiFiManagerParameter p_pinScl("pinscl", "I2C SCL pin", convertedValue, 3);

    // Just a quick hint
    WiFiManagerParameter p_hint("<small>*Hint: if you want to reuse the currently active WiFi credentials, leave SSID and Password fields empty</small>");
    
    // Initialize WiFIManager
    WiFiManager wifiManager;
    
    //add all parameters here
    
    wifiManager.addParameter(&p_hint);
    wifiManager.addParameter(&p_thingspeakApiKey);
    wifiManager.addParameter(&p_sensorDht22);
    wifiManager.addParameter(&p_pinSda);
    wifiManager.addParameter(&p_pinScl);  

    // Sets timeout in seconds until configuration portal gets turned off.
    // If not specified device will remain in configuration mode until
    // switched off via webserver or device is restarted.
    // wifiManager.setConfigPortalTimeout(600);

    // It starts an access point 
    // and goes into a blocking loop awaiting configuration.
    // Once the user leaves the portal with the exit button
    // processing will continue
    if (!wifiManager.startConfigPortal())
    {
      Serial.println("Not connected to WiFi but continuing anyway.");
    }
    else
    {
      // If you get here you have connected to the WiFi
      Serial.println("Connected...yeey :)");
    }


    // Getting posted form values and overriding local variables parameters
    // Config file is written regardless the connection state
    strcpy(thingspeakApiKey, p_thingspeakApiKey.getValue());
    sensorDht22 = (strncmp(p_sensorDht22.getValue(), "T", 1) == 0);
    pinSda = atoi(p_pinSda.getValue());
    pinScl = atoi(p_pinScl.getValue());
    // Writing JSON config file to flash for next boot
    writeConfigFile();

    
    digitalWrite(PIN_LED, HIGH); // Turn LED off as we are not in configuration mode.

    ESP.reset(); // This is a bit crude. For some unknown reason webserver can only be started once per boot up 
    // so resetting the device allows to go back into config mode again when it reboots.
}
