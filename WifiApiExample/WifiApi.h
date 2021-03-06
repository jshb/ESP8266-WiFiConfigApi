
#ifndef WifiApi_h
#define WifiApi_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

class WifiApi {
  public:
    WifiApi();
    
    boolean autoConnect();
    boolean autoConnect(char const *apName, char const *apPassword = NULL);
    
    void handleClient();  // Must be called in the main loop of the application?

    void onFailedReconnect( void (*func)(void) );
    void onConfigChange( void (*func)(void) );

    void resetSettings();

  private:
    std::unique_ptr<DNSServer>        dnsServer;
    std::unique_ptr<ESP8266WebServer> server;
    
    const char* _apName = "no-net";
    const char* _apPassword = NULL;
    String _ssid = "";
    String _pass = "";
    unsigned long _accessPointTimeout = 0;
    unsigned long _connectTimeout = 0;

    void (*_fnFailedReconnect)(void) = NULL;
    void (*_fnConfigChange)(void) = NULL;

    int status = WL_IDLE_STATUS;
    unsigned long _accessPointStart = 0;
    boolean _ap_wifi_config_provided = false;
    
    const byte DNS_PORT = 53;
    
    boolean _debug = true;
    


    int connectWifi(String ssid, String pass);
    uint8_t waitForConnectResult();
    

    boolean awaitSetupViaAccessPoint(char const *apName, char const *apPassword = NULL);
    void startAccessPoint();

    void startApi();
    void apiHandleConfig();
    
    void saveConfig();
    

    template <typename Generic>
    void DEBUG_WM(Generic text);
    
};

#endif
