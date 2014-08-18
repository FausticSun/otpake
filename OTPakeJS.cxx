#include <emscripten/bind.h>
#include "OTPakeClient.h"
#include "OTPake.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(OTPake) {
    class_<OTPake>("OTPake")
        .function("getSelfEphemeral", &OTPake::getSelfEphemeral)
        .function("getSharedKey", &OTPake::getSharedKey)
        .function("getPrime", &OTPake::getPrime)
        .function("getGenerator", &OTPake::getGenerator)
        .function("getPrivateKey", &OTPake::getPrivateKey)
        .function("getOtherEphemeral", &OTPake::getOtherEphemeral)
        .function("getSharedSecret", &OTPake::getSharedSecret)
        .function("getOTP", &OTPake::getOTP)
        .function("getUniqueID", &OTPake::getUniqueID)
    ;
    class_<OTPakeClient, base<OTPake>>("OTPakeClient")
        .constructor<std::string, std::string>()
        .function("genSharedKey", &OTPakeClient::genSharedKey)
        .function("getVerification", &OTPakeClient::getVerification)
    ;
}