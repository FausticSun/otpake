#include "OTPakeServer.h"

// Public
OTPakeServer::OTPakeServer(string uID, string oEphemeral, string oneTimePasswords) : OTPake(uID) {
    otherEphemeral = oEphemeral;
    OTPs = splitString(oneTimePasswords);
    if (verifyOtherEphemeral()) {
        genPrivate();
        genEphemeral();
        genSharedSecret();
        genVerification();
    }
}

OTPakeServer::OTPakeServer(string pv, string sE, string oE,
                            string uID, string vs, string otpss,
                            string ss) : OTPake(uID) {
    privateKey = pv;
    selfEphemeral = sE;
    otherEphemeral = oE;
    verifications = splitString(vs);
    OTPs = splitString(otpss);
    vector<string> preSS = splitString(ss);
    for(vector<string>::size_type i = 0; i != preSS.size(); i++) {
        sharedSecrets.push_back(mpz_class(preSS[i]));
    }
}

void OTPakeServer::genSharedKey(string otherVerification) {
    if (verifyOtherVerification(otherVerification)) {
        sharedKey = hash(uniqueID+otherEphemeral.get_str()+selfEphemeral.get_str()+sharedSecret.get_str()+OTP+salts[3]);
    }
}

string OTPakeServer::getVerifications() {
    string s = "";
    for(vector<string>::size_type i = 0; i != verifications.size(); i++) {
        s.append(hexlify(verifications[i]));
        s.append(",");
    }
    return s;
}

string OTPakeServer::getOTPs() {
    string s = "";
    for(vector<string>::size_type i = 0; i != OTPs.size(); i++) {
        s.append(OTPs[i]);
        s.append(",");
    }
    return s;
}

string OTPakeServer::getSharedSecrets() {
    string s = "";
    for(vector<string>::size_type i = 0; i != sharedSecrets.size(); i++) {
        s.append("0x"+sharedSecrets[i].get_str(16));
        s.append(",");
    }
    return s;
}

// Protected
bool OTPakeServer::verifyOtherVerification(string otherVerification) {
    for(vector<string>::size_type i = 0; i != sharedSecrets.size(); i++) {
        if (otherVerification == hexlify(hash(uniqueID+otherEphemeral.get_str()+selfEphemeral.get_str()+sharedSecrets[i].get_str()+OTPs[i]+salts[2]))) {
            sharedSecret = sharedSecrets[i];
            OTP = OTPs[i];
            return true;
        }
    }
    return false;
}

void OTPakeServer::genEphemeral() {
    mpz_powm(selfEphemeral.get_mpz_t(), generator.get_mpz_t(), privateKey.get_mpz_t(), prime.get_mpz_t());
}

void OTPakeServer::genSharedSecret() {
    mpz_class hashpow;
    for (vector<string>::size_type i = 0; i != OTPs.size(); i++) {
        mpz_class buf;
        mpz_class hashnum(hexlify(hash(uniqueID+OTPs[i]+salts[0])));
        mpz_pow_ui(hashpow.get_mpz_t(), hashnum.get_mpz_t(), 2);
        mpz_class pub = otherEphemeral / hashpow;
        mpz_powm(buf.get_mpz_t(), pub.get_mpz_t(), privateKey.get_mpz_t(), prime.get_mpz_t());
        sharedSecrets.push_back(buf);
    }
}

void OTPakeServer::genVerification() {
    for (vector<string>::size_type i = 0; i != sharedSecrets.size(); i++) {
       verifications.push_back(hash(uniqueID+otherEphemeral.get_str()+selfEphemeral.get_str()+sharedSecrets[i].get_str()+OTPs[i]+salts[1]));
    }
}