#include <iostream>
#include "OTPakeClient.h"
#include "OTPakeServer.h"

using namespace std;

int main() {
    string clientID = "FausticSun";
    string serverID = "www.fs.com";
    string uniqueID = clientID + serverID;
    string OTP = "111111";
    string OTPs = "111111,222222,333333,444444,555555,666666";
    OTPakeClient client(uniqueID, OTP);
    OTPakeServer server(uniqueID, client.getSelfEphemeral(), OTPs);
    client.genSharedKey(server.getSelfEphemeral(), server.getVerifications());
    server.genSharedKey(client.getVerification());
    cout << (client.getSharedKey() == server.getSharedKey() ? "WIN" : "LOSE") << endl;
    cout << client.getPrime() << endl;
    cout << client.getGenerator() << endl;
    cout << client.getPrivateKey() << endl;
    cout << client.getSelfEphemeral() << endl;
    cout << client.getOtherEphemeral() << endl;
    cout << client.getSharedSecret() << endl;
    cout << server.getSharedSecrets() << endl;
}