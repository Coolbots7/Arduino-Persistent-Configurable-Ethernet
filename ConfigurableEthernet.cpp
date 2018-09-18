#include <EEPROM.h>
#include <SPI.h>
#include <Ethernet.h>
#include "Arduino.h"
#include "ConfigurableEthernet.h"


ConfigurableEthernet::ConfigurableEthernet() {

}

void ConfigurableEthernet::begin(HardwareSerial &s) {
	serial = &s;
	
	uint8_t mac[6];
	MACAddress MAC = GetMACFromEEPROM();
	memcpy(mac, &MAC, 6);
  
	uint8_t IP[4];
	uint8_t DNS[4];
	uint8_t Gateway[4];
	uint8_t Subnet[4];
	
	GetIPAddressFromEEPROM(IP);
	GetDNSFromEEPROM(DNS);
	GetGatewayFromEEPROM(Gateway);
	GetSubnetMaskFromEEPROM(Subnet);
	
	Ethernet.begin(mac, IP, DNS, Gateway, Subnet);

}

void ConfigurableEthernet::ResetEthernetDefaults(HardwareSerial &s) {
	serial = &s;
	
	
	Ethernet.begin(DefaultMAC, DefaultIP, DefaultDNS, DefaultGateway, DefaultSubnet);

	SetMACAddress(DefaultMAC);
	SetIPAddress(DefaultIP);
	SetDNS(DefaultDNS);
	SetGateway(DefaultGateway);
	SetSubnetMask(DefaultSubnet);
}


// MAC Address
MACAddress ConfigurableEthernet::GetMACFromEEPROM() {
  MACAddress MAC;
  EEPROM.get(EEPROM_Address_MAC, MAC);
  
  serial->print("Got MAC from EEPROM: ");
  serial->println(MAC.toString());  
  
  return MAC;
}

MACAddress ConfigurableEthernet::GetMAC() {
  uint8_t mac[6];
  Ethernet.MACAddress(mac);
  MACAddress MAC(mac);
  
  serial->print("Got MAC: ");
  serial->println(MAC.toString());  
  
  return MAC;
}

void ConfigurableEthernet::SetMACAddress(MACAddress MAC) {
  EEPROM.put(EEPROM_Address_MAC, MAC);
  
  uint8_t mac[6];
  memcpy(mac, &MAC, 6);  
  Ethernet.setMACAddress(mac);
  
  serial->print("Set MAC Address to: ");
  serial->println(MAC.toString());
}


// IP Address
void ConfigurableEthernet::GetIPAddressFromEEPROM(uint8_t* IP) {
	getByteArrayFromEEPROM(EEPROM_Address_IP, IP, 4);

	serial->print("Got IP Address from EEPROM: ");
	serial->print(IP[0]);
	serial->print(".");
	serial->print(IP[1]);
	serial->print(".");
	serial->print(IP[2]);
	serial->print(".");
	serial->print(IP[3]);
	serial->println();
}

IPAddress ConfigurableEthernet::GetIPAddress() {
	IPAddress ip = Ethernet.localIP();

	serial->print("Got IP: ");
	printIPAddress(ip);
	serial->println(); 

	return ip;
}

void ConfigurableEthernet::SetIPAddress(uint8_t* IP) {
	putByteArrayInEEPROM(EEPROM_Address_IP, IP, 4);
	Ethernet.setLocalIP(IP);
  
	serial->print("Set IP Address to: ");
	serial->print(IP[0]);
	serial->print(".");
	serial->print(IP[1]);
	serial->print(".");
	serial->print(IP[2]);
	serial->print(".");
	serial->print(IP[3]);
	serial->println();
}


// DNS Address
void ConfigurableEthernet::GetDNSFromEEPROM(uint8_t* DNS) {
	getByteArrayFromEEPROM(EEPROM_Address_DNS, DNS, 4);

	serial->print("Got DNS Address from EEPROM: ");
	serial->print(DNS[0]);
	serial->print(".");
	serial->print(DNS[1]);
	serial->print(".");
	serial->print(DNS[2]);
	serial->print(".");
	serial->print(DNS[3]);
	serial->println();
}

IPAddress ConfigurableEthernet::GetDNS() {
  IPAddress DNS = Ethernet.dnsServerIP();
  
  serial->print("Got DNS: ");
  printIPAddress(DNS);
  serial->println(); 
  
  return DNS;
}

void ConfigurableEthernet::SetDNS(uint8_t* DNS) {
	putByteArrayInEEPROM(EEPROM_Address_DNS, DNS, 4);
	Ethernet.setDnsServerIP(DNS);
  
	serial->print("Set DNS Address to: ");
	serial->print(DNS[0]);
	serial->print(".");
	serial->print(DNS[1]);
	serial->print(".");
	serial->print(DNS[2]);
	serial->print(".");
	serial->print(DNS[3]);
	serial->println();
}


// Gateway Address
void ConfigurableEthernet::GetGatewayFromEEPROM(uint8_t* Gateway) {
	getByteArrayFromEEPROM(EEPROM_Address_Gateway, Gateway, 4);
  
	serial->print("Got Gateway from EEPROM: ");
	serial->print(Gateway[0]);
	serial->print(".");
	serial->print(Gateway[1]);
	serial->print(".");
	serial->print(Gateway[2]);
	serial->print(".");
	serial->print(Gateway[3]);
	serial->println();
}

IPAddress ConfigurableEthernet::GetGateway() {
  IPAddress Gateway = Ethernet.gatewayIP();
  
  serial->print("Got Gateway: ");
  printIPAddress(Gateway);
  serial->println(); 
  
  return Gateway;
}

void ConfigurableEthernet::SetGateway(uint8_t* Gateway) {
	putByteArrayInEEPROM(EEPROM_Address_Gateway, Gateway, 4);
	Ethernet.setGatewayIP(Gateway);

	serial->print("Set Gateway Address to: ");
	serial->print(Gateway[0]);
	serial->print(".");
	serial->print(Gateway[1]);
	serial->print(".");
	serial->print(Gateway[2]);
	serial->print(".");
	serial->print(Gateway[3]);
	serial->println();
}


// EEPROM Address
void ConfigurableEthernet::GetSubnetMaskFromEEPROM(uint8_t* Subnet) {
	getByteArrayFromEEPROM(EEPROM_Address_Subnet, Subnet, 4);

	serial->print("Got Subnet from EEPROM: ");
	serial->print(Subnet[0]);
	serial->print(".");
	serial->print(Subnet[1]);
	serial->print(".");
	serial->print(Subnet[2]);
	serial->print(".");
	serial->print(Subnet[3]);
	serial->println();
}

IPAddress ConfigurableEthernet::GetSubnetMask() {
  IPAddress Subnet = Ethernet.subnetMask();
  
  serial->print("Got Subnet Mask: ");
  printIPAddress(Subnet);
  serial->println(); 
  
  return Subnet;
}

void ConfigurableEthernet::SetSubnetMask(uint8_t* Subnet) {
	putByteArrayInEEPROM(EEPROM_Address_Subnet, Subnet, 4);
	Ethernet.setSubnetMask(Subnet);

	serial->print("Set Subnet Address to: ");
	serial->print(Subnet[0]);
	serial->print(".");
	serial->print(Subnet[1]);
	serial->print(".");
	serial->print(Subnet[2]);
	serial->print(".");
	serial->print(Subnet[3]);
	serial->println();
}

void ConfigurableEthernet::getByteArrayFromEEPROM(int StartAddress, uint8_t* array, int size) {
	for(int i=0;i<size;i++) {
		EEPROM.get(StartAddress+i, array[i]);
	}
}

void ConfigurableEthernet::putByteArrayInEEPROM(int StartAddress, uint8_t* array, int size) {
	for(int i=0;i<size;i++) {
		EEPROM.put(StartAddress+i, array[i]);
	}
}



void ConfigurableEthernet::printIPAddress(IPAddress ip) {	
  serial->print(ip[0]);
  serial->print(".");
  serial->print(ip[1]);
  serial->print(".");
  serial->print(ip[2]);
  serial->print(".");
  serial->print(ip[3]);
}