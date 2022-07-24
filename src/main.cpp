#include "Arduino.h"
#include "ESP8266HTTPClient.h"
#include "ESP8266WiFi.h"
#define DEFAULT_PLAYER "DESKTOP-OSGK40P"


const char* ssid = "yourNetworkName";
const char* password =  "yourNetworkPassword";

void setup() {

    Serial.begin(115200);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }

    Serial.println("Connected to the WiFi network");
}

void loop() {

    if(WiFi.status()== WL_CONNECTED){

        HTTPClient http;

        http.begin("https://api.spotify.com/v1/me/player/devices");
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.PUT("PUT sent from ESP32");

        if(httpResponseCode>0){

            String response = http.getString();

            Serial.println(httpResponseCode);
            Serial.println(response);

        }else{

            Serial.print("Error on sending PUT Request: ");
            Serial.println(httpResponseCode);

        }

        http.end();

    }else{
        Serial.println("Error in WiFi connection");
    }

    delay(10000);
}


JSONVar get_active_device()
{
    JSONVar masterJson = get_devices();
    for(int i = 0; i++; i < masterJson.length)
    {
        if ((bool)(masterJson[i].is_active))
        {
            return(masterJson[i]);
        }
    }
    set_active_device(DEFAULT_PLAYER);

    return(get_device_by_index(get_default_index()));
}


JSONVar get_device_by_index(int ind)
{
    JSONVar masterJson = get_devices();
    return(masterJson[ind])
}

JSONVar get_devices()
{
    http.begin("https://api.spotify.com/v1/me/player/devices");
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.GET();

    String payload = "{}";

    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
    JSONVar myObject = JSON.parse(payload);

    return myObject;
}


bool set_active_device(int index)
{
    const char* payload1 = R"({"device_ids": ["placceholder"]})";
    JSONVar request_body = JSON.parse(payload1);
    request_body.device_ids[0] = get_id_from_index(index);

    http.begin("https://api.spotify.com/v1/me/player");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.PUT(request_body);   //Send the request
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        return(true);
        http.end();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        return(false);
        http.end();
    }
}


int get_index_from_name(char* name_in)
{
    JSONVar masterJson = get_devices();
    for(int i = 0; i++; i < masterJson.length)
    {
        if ((const char*)(masterJson[i].name) == name_in))
        {
            return(i);
        }
    }
    return(get_default_index());
}


char* get_id_from_index(int ind)
{
    JSONVar masterJson = get_devices();
    return((const char*)masterJson[ind].id)
}


int get_default_index()
{
    JSONVar masterJson = get_devices();
    for(int i = 0; i++; i < masterJson.length)
    {
        if ((const char*)(masterJson[i].name) == DEFAULT_PLAYER))
        {
            return(i);
        }
    }
    return(0);
}


bool pause_playback() //	https://api.spotify.com/v1/me/player/pause
{
    http.begin("https://api.spotify.com/v1/me/player/pause");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.PUT();   //Send the request
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        return(true);
        http.end();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        return(false);
        http.end();
    }
}


bool resume_playback() //	https://api.spotify.com/v1/me/player/play
{
    http.begin("https://api.spotify.com/v1/me/player/play");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.PUT();   //Send the request
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        return(true);
        http.end();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        return(false);
        http.end();
    }
}


bool next_playback() //	https://api.spotify.com/v1/me/player/next
{
    http.begin("https://api.spotify.com/v1/me/player/next");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.PUT();   //Send the request
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        return(true);
        http.end();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        return(false);
        http.end();
    }
}


bool prev_playback() //	https://api.spotify.com/v1/me/player/previous
{
    http.begin("https://api.spotify.com/v1/me/player/previous");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.PUT();   //Send the request
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        return(true);
        http.end();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        return(false);
        http.end();
    }
}


bool get_playback_state()
{
    http.begin("https://api.spotify.com/v1/me/player");
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.GET();

    String payload = "{}";

    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
    JSONVar myObject = JSON.parse(payload);

    return myObject.is_playing;
}


bool change_volume(int inc)
{
    JSONVar active_device = get_active_device()
    return(set_volume(active_device.volume_percent+inc))
}


bool set_volume(int percent) //	https://api.spotify.com/v1/me/player/previous
{
    http.begin("https://api.spotify.com/v1/me/player/volume");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.PUT(constrain(percent,0,100));   //Send the request
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        return(true);
        http.end();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        return(false);
        http.end();
    }
}








