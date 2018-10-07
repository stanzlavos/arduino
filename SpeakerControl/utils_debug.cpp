#include "utils_debug.h"

#ifdef DEBUG_TELNET

WiFiServer  TelnetServer(23);
WiFiClient  Telnet;

void setup_telnet(void)
{
    T_PRINTLN("Setting up telnet...");
    TelnetServer.begin();
    TelnetServer.setNoDelay(true);
}

void handle_telnet(void)
{
    if (TelnetServer.hasClient())
    {
        // client is connected
        T_PRINTLN("Telnet client connected !!!");
        if (!Telnet || !Telnet.connected())
        {
            if (Telnet)
                Telnet.stop();                 // client disconnected
            Telnet = TelnetServer.available(); // ready for new client
        }
        else
        {
            TelnetServer.available().stop(); // have client, block new connection
        }
    }
}

#endif // DEBUG_TELNET
