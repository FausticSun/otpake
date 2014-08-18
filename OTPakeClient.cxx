#include "OTPakeClient.h"

// Public
OTPakeClient::OTPakeClient(string uID, string oneTimePassword) : OTPake(uID) {
    OTP = oneTimePassword;
    genPrivate();
    genEphemeral();
}

void OTPakeClient::genSharedKey(string oEphemeral, string otherVerification) {
    otherEphemeral = oEphemeral;
    if (verifyOtherEphemeral()) {
        mpz_powm(sharedSecret.get_mpz_t(), otherEphemeral.get_mpz_t(), privateKey.get_mpz_t(), prime.get_mpz_t());
    }
    if (verifyOtherVerification(otherVerification)) {
        verification = hash(uniqueID+selfEphemeral.get_str()+otherEphemeral.get_str()+sharedSecret.get_str()+OTP+salts[2]);
    }
    genVerification();
    sharedKey = hash(uniqueID+selfEphemeral.get_str()+otherEphemeral.get_str()+sharedSecret.get_str()+OTP+salts[3]);
}

string OTPakeClient::getVerification() {
    return hexlify(verification);
}

// Protected
void OTPakeClient::genEphemeral() {
    mpz_class publicKey, hashpow;
    mpz_class hashnum(hexlify(hash(uniqueID+OTP+salts[0])));
    mpz_powm(publicKey.get_mpz_t(), generator.get_mpz_t(), privateKey.get_mpz_t(), prime.get_mpz_t());
    mpz_pow_ui(hashpow.get_mpz_t(), hashnum.get_mpz_t(), 2);
    mpz_mul(selfEphemeral.get_mpz_t(), publicKey.get_mpz_t(), hashpow.get_mpz_t());
}

bool OTPakeClient::verifyOtherVerification(string otherVerification) {
    string clientHash = hexlify(hash(uniqueID+selfEphemeral.get_str()+otherEphemeral.get_str()+sharedSecret.get_str()+OTP+salts[1]));
    vector<string> verifications = splitString(otherVerification);
    for (vector<string>::size_type i = 0; i != verifications.size(); i++) { 
        if (verifications[i] == clientHash)
            return true;
    }
    return false;
}

void OTPakeClient::genVerification() {
    verification = hash(uniqueID+selfEphemeral.get_str()+otherEphemeral.get_str()+sharedSecret.get_str()+OTP+salts[2]);
}