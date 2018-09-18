#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>

#define EEPROM_Address_MAC 0 //MAC Address 6 bytes (EEPROM Address 0-5)
#define EEPROM_Address_IP 6  //IP Address 4 bytes (EEPROM Address 6-9)
#define EEPROM_Address_DNS 10  //DNS IP Address 4 bytes (EEPROM Address 10-13)
#define EEPROM_Address_Gateway 14  //Gateway IP Address 4 bytes (EEPROM Address 14-17)
#define EEPROM_Address_Subnet 18 //Subnet Mask 4 bytes (EEPROM Address 18-21)


static const uint8_t DefaultMAC[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
static const uint8_t DefaultIP[] = {192, 168, 2, 177};
static const uint8_t DefaultDNS[] = {192, 168, 2, 1};
static const uint8_t DefaultGateway[] = {192, 168, 2, 1};
static const uint8_t DefaultSubnet[] = {255, 255, 255, 0};

class MACAddress {
  public:
    MACAddress() {
      _address.dword = 0;
    }
    MACAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet, uint8_t fifth_octet, uint8_t sixth_octet) {
      _address.bytes[0] = first_octet;
      _address.bytes[1] = second_octet;
      _address.bytes[2] = third_octet;
      _address.bytes[3] = fourth_octet;
      _address.bytes[4] = fifth_octet;
      _address.bytes[5] = sixth_octet;
    }
    MACAddress(uint64_t address) {
      _address.dword = address;
    }
    MACAddress(const uint8_t *address) {
      memcpy(_address.bytes, address, 6);
    }

    //    bool fromString(const char *address);
    //    bool fromString(const String &address) {
    //      return fromString(address.c_str());
    //    }


    String toString() const
    {
      char szRet[24];
      sprintf(szRet, "%02X-%02X-%02X-%02X-%02X-%02X", _address.bytes[0], _address.bytes[1], _address.bytes[2], _address.bytes[3], _address.bytes[4], _address.bytes[5]);
      return String(szRet);
    }

    //    static bool isValid(const String& arg);
    //    static bool isValid(const char* arg);

  private:
    union {
      uint8_t bytes[6];
      uint64_t dword;
    } _address;

};

class ConfigurableEthernet {

  public:
    ConfigurableEthernet();
	
	void begin(HardwareSerial &s);

    void ResetEthernetDefaults(HardwareSerial &s);

    MACAddress GetMAC();
    IPAddress GetIPAddress();
    IPAddress GetDNS();
    IPAddress GetGateway();
    IPAddress GetSubnetMask();

    MACAddress GetMACFromEEPROM();
    void GetIPAddressFromEEPROM(uint8_t*);
    void GetDNSFromEEPROM(uint8_t*);
    void GetGatewayFromEEPROM(uint8_t*);
    void GetSubnetMaskFromEEPROM(uint8_t*);

    void SetMACAddress(MACAddress);
    void SetIPAddress(uint8_t*);
    void SetDNS(uint8_t*);
    void SetGateway(uint8_t*);
    void SetSubnetMask(uint8_t*);

  private:
	Print* serial;
	void putByteArrayInEEPROM(int, uint8_t*, int);
	void getByteArrayFromEEPROM(int, uint8_t*, int);
	void printIPAddress(IPAddress);

};
