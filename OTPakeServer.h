#ifndef _OTPAKESERVER_H
#define _OTPAKESERVER_H

#include "OTPake.h"

class OTPakeServer : public OTPake {
    protected:
        vector<string> OTPs;
        vector<mpz_class> sharedSecrets;
        vector<string> verifications;
        bool verifyOtherVerification(string otherVerification);
        void genEphemeral();
        void genSharedSecret();
        void genVerification();
    public:
        OTPakeServer(string uniqueID, string otherEphemeral, string OTPs);
        OTPakeServer(string pv, string sE, string oE,
                        string uID, string vs, string otpss,
                        string sss, string k, string otpo, string ss);
        void genSharedKey(string otherVerification);
        string getVerifications();
        string getOTPs();
        string getSharedSecrets();
};

#endif