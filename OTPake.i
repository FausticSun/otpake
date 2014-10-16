%module OTPake
%include "std_string.i"
%include "std_vector.i"

%{
    #include "OTPake.h"
    #include "OTPakeClient.h"
    #include "OTPakeServer.h"
%}

%include "OTPake.h"
%include "OTPakeClient.h"
%include "OTPakeServer.h"

%extend OTPakeServer {
    %pythoncode %{
    def __reduce__(self):
       return (self.__class__,(
            self.getPrivateKey(),
            self.getSelfEphemeral(),
            self.getOtherEphemeral(),
            self.getUniqueID(),
            self.getVerifications(),
            self.getOTPs(),
            self.getSharedSecrets(),

            self.getSharedKey(),
            self.getOTP(),
            self.getSharedSecret()
       ))
    %}
}

