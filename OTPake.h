#ifndef _OTPAKE_H
#define _OTPAKE_H

#include <string>
#include <vector>
#include <gmp.h>
#include <gmpxx.h>

using std::string;
using std::vector;

class OTPake {
    protected:
        mpz_class prime;
        mpz_class generator;
        mpz_class privateKey;
        mpz_class selfEphemeral;
        mpz_class otherEphemeral;
        mpz_class sharedSecret;
        string OTP;
        string sharedKey;
        string uniqueID;
        vector<string> salts;
        void genPrivate();
        bool verifyOtherEphemeral();
        // Utility functions
        string hexlify(string s);
        string stringToNum(string s);
        string hash(string s);
        vector<string> splitString(string s);
    public:
        OTPake(string uniqueID);
        // string getSelfEphemeral(){return selfEphemeral.get_str(16);};
        // string getSharedKey(){return sharedKey;};

        // For testing purposes
        string getPrime(){return "0x"+prime.get_str(16);};
        string getGenerator(){return "0x"+generator.get_str(16);};
        string getPrivateKey(){return "0x"+privateKey.get_str(16);};
        string getSelfEphemeral(){return "0x"+selfEphemeral.get_str(16);};
        string getOtherEphemeral(){return "0x"+otherEphemeral.get_str(16);};
        string getSharedSecret(){return "0x"+sharedSecret.get_str(16);};
        string getOTP(){return OTP;};
        string getSharedKey(){return hexlify(sharedKey);};
        string getUniqueID(){return uniqueID;};
};

#endif