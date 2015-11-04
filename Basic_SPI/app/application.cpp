#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <SmingCore/SPI.h>

/* Basic_SPI Master Code for talking with generic SPI Slaves, such as Arduino, etc. */
/* https://github.com/evanmj/ */

//TODO: Add pins and connection information.

//Define timer
Timer procTimer;

//Create SPI object using default of SPI_ID_HSPI which is the "User" SPI.
SPIClass spi(SPI_ID_HSPI);

String MyData = "Hello from ESP8266";
String ReturnData;

String ScratchData;

void SendData()
{
	ScratchData = MyData;  // Buffer my data into scratch space for code clarity.
	Serial.println("Sending Data of size: " + String(sizeof(ScratchData) * 8) + "bits. String Content: " + ScratchData);
	spi.transfer(reinterpret_cast<uint8_t*>(&ScratchData[0]), sizeof(ScratchData) * 8);  // Feed pointer to our data.  This Sends data out to slave via the SPI_FLASH_CO register.  uint8_t count is in bits not bytes!
	ReturnData = ScratchData;  // spi.transfer dumped the slave's response in our ScrachData memory location.  Buffer it back.
	Serial.println("Return Data from Slave: " + String(ReturnData));
}

void init()
{
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true); // Enable debug output to serial
	Serial.println("\r\n=== SPI EXAMPLE STARTED ===");
	Serial.println("\r\n===     STARTING SPI    ===");
	spi.begin();
	procTimer.initializeMs(1000, SendData).start(); // Start cyclic timer to send our test data.
}

