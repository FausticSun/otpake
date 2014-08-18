#ifndef _OTPAKECLIENT_H
#define _OTPAKECLIENT_H

#include "OTPake.h"

class OTPakeClient : public OTPake {
    protected:
        string verification;
        bool verifyOtherVerification(string otherVerification);
        void genEphemeral();
        void genVerification();
    public:
        OTPakeClient(string uniqueID, string OTP);
        void genSharedKey(string otherEphemeral, string otherVerification);
        string getVerification();
};

#endif