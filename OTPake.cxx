#include <bitset>
#include <sstream>
#include <sodium.h>
#include "OTPake.h"

using std::bitset;
using std::stringstream;
using std::getline;

OTPake::OTPake(string uID) {
    prime = "0xFFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA18217C32905E462E36CE3BE39E772C180E86039B2783A2EC07A28FB5C55DF06F4C52C9DE2BCBF6955817183995497CEA956AE515D2261898FA051015728E5A8AACAA68FFFFFFFFFFFFFFFF";
    generator = 2;
    salts = {"Hash1", "Hash2", "Hash3", "Hash4"};
    uniqueID = uID;
}

void OTPake::genPrivate() {
    // Calcualte bits of q where prime = rq + 1
    mpz_class q = (prime-1)/2;
    int bits = (q.get_str(2)).length()-1;
    int bytes = bits/8;

    // Generate random bytes with libsodium
    string buf(bytes, 0);
    randombytes_buf(&buf[0], bytes);

    // Convert bytes to integer
    privateKey = stringToNum(buf);
}

bool OTPake::verifyOtherEphemeral() {
    return otherEphemeral % prime == 0 ? false : true;
}

string OTPake::hexlify(string s) {
    std::string bytes = s;
    std::string hex(bytes.size()*2, 0);
    sodium_bin2hex(&hex[0], hex.size(), reinterpret_cast<const unsigned char *>(&bytes[0]), bytes.size());
    return "0x"+hex;
}

string OTPake::stringToNum(string s) {
    string tmp = "";
    for (int i = 0; i < s.size(); ++i) {
        tmp.append(bitset<8>(s[i]).to_string());
    }
    mpz_class num(tmp, 2);
    return "0x"+num.get_str(16);
}

string OTPake::hash(string s) {
    unsigned char h[crypto_hash_sha256_BYTES];
    crypto_hash_sha256(h, (const unsigned char *) s.c_str(), s.size());
    return string(reinterpret_cast<char*>(h), sizeof h);
}

vector<string> OTPake::splitString(string s) {
    vector<string> tokens;
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, ',')) {
        tokens.push_back(item);
    }
    return tokens;
}