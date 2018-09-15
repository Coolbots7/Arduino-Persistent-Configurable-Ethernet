#include <EEPROM.h>
#include <SPI.h>
#include <Ethernet.h>
#include "Arduino.h"
#include "ConfigurableEthernet.h"


ConfigurableEthernet::ConfigurableEthernet() {
  uint8_t mac[6];
  MACAddress MAC = GetMACFromEEPROM();
  memcpy(mac, &MAC, 6);
  Ethernet.begin(mac,
                 GetIPAddressFromEEPROM(),
                 GetDNSFromEEPROM(),
                 GetGatewayFromEEPROM(),
                 GetSubnetMaskFromEEPROM());

}

void ConfigurableEthernet::ResetEthernetDefaults() {
  SetMACAddress(DefaultMAC);
  SetIPAddress(DefaultIP);
  SetDNS(DefaultDNS);
  SetGateway(DefaultGateway);
  SetSubnetMask(DefaultSubnet);
}

MACAddress ConfigurableEthernet::GetMACFromEEPROM() {
  MACAddress MAC;
  EEPROM.get(EEPROM_Address_MAC, MAC);
  return MAC;
}

MACAddress ConfigurableEthernet::GetMAC() {
  uint8_t mac[6];
  Ethernet.MACAddress(mac);
  return MACAddress(mac);
}

void ConfigurableEthernet::SetMACAddress(MACAddress MAC) {
  EEPROM.put(EEPROM_Address_MAC, MAC);
  //Ethernet.setMACAddress(&MAC);
}

IPAddress ConfigurableEthernet::GetIPAddressFromEEPROM() {
  IPAddress IP;
  EEPROM.get(EEPROM_Address_IP, IP);
  return IPAddress();
}

IPAddress ConfigurableEthernet::GetIPAddress() {
  return Ethernet.localIP();
}

void ConfigurableEthernet::SetIPAddress(IPAddress IP) {
  EEPROM.put(EEPROM_Address_IP, IP);
  Ethernet.setLocalIP(IP);
}

IPAddress ConfigurableEthernet::GetDNSFromEEPROM() {
  IPAddress DNS;
  EEPROM.get(EEPROM_Address_DNS, DNS);
  return DNS;
}

IPAddress ConfigurableEthernet::GetDNS() {
  return Ethernet.dnsServerIP();
}

void ConfigurableEthernet::SetDNS(IPAddress DNS) {
  EEPROM.put(EEPROM_Address_DNS, DNS);
  Ethernet.setDnsServerIP(DNS);
}

IPAddress ConfigurableEthernet::GetGatewayFromEEPROM() {
  IPAddress Gateway;
  EEPROM.get(EEPROM_Address_Gateway, Gateway);
  return Gateway;
}

IPAddress ConfigurableEthernet::GetGateway() {
  return Ethernet.gatewayIP();
}

void ConfigurableEthernet::SetGateway(IPAddress Gateway) {
  EEPROM.put(EEPROM_Address_Gateway, Gateway);
  Ethernet.setGatewayIP(Gateway);
}

IPAddress ConfigurableEthernet::GetSubnetMaskFromEEPROM() {
  IPAddress Subnet;
  EEPROM.get(EEPROM_Address_Subnet, Subnet);
  return Subnet;
}

IPAddress ConfigurableEthernet::GetSubnetMask() {
  return Ethernet.subnetMask();
}

void ConfigurableEthernet::SetSubnetMask(IPAddress Subnet) {
  EEPROM.put(EEPROM_Address_Subnet, Subnet);
  Ethernet.setSubnetMask(Subnet);
}
