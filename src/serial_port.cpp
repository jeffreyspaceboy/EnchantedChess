#include "../inc/serial_port.hpp"

SerialPort::SerialPort(const char *comPort) {
  this->port_open = 0;
  this->handle = CreateFileA(comPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

  if (this->handle == INVALID_HANDLE_VALUE) {
    printf("[ERROR]: Could not open serial port.\r\n");
    return;
  }

  this->dcb_params.DCBlength = sizeof(this->dcb_params);

  // Get the current state
  if (!GetCommState(this->handle, &this->dcb_params)) {
    printf("[ERROR]: Could not get current serial parameters.\r\n");
    return;
  }

  // Set the parameters
  this->dcb_params.BaudRate = CBR_115200;
  this->dcb_params.ByteSize = 8;
  this->dcb_params.StopBits = ONESTOPBIT;
  this->dcb_params.Parity = NOPARITY;

  // Apply the settings
  if (!SetCommState(this->handle, &this->dcb_params)) {
    printf("[ERROR]: Could not set serial parameters.\r\n");
    return;
  }

  COMMTIMEOUTS timeouts = {0};
  timeouts.ReadIntervalTimeout = 50;
  timeouts.ReadTotalTimeoutConstant = 50;
  timeouts.ReadTotalTimeoutMultiplier = 10;
  timeouts.WriteTotalTimeoutConstant = 50;
  timeouts.WriteTotalTimeoutMultiplier = 10;

  // Set the timeouts
  if (!SetCommTimeouts(this->handle, &timeouts)) {
    printf("[ERROR]: Could not set timeouts.\r\n");
    return;
  }
  this->port_open = 1;
  return;
}

SerialPort::~SerialPort() {
  CloseHandle(this->handle);
  this->port_open = 0;
  return;
}

int SerialPort::write(const char *data) {
  if (this->port_open == 0) {
    printf("[ERROR]: Serial port is not open. Serial write failed.\r\n");
    return ERROR; 
  }
  DWORD bytesWritten;
  if (!WriteFile(this->handle, data, strlen(data), &bytesWritten, NULL)) {
    printf("[ERROR]: Could not write to serial port.\r\n");
    return ERROR;
  }
  return SUCCESS;
}

int SerialPort::read(char *buffer, DWORD bufferSize) {
  if (this->port_open == 0) {
    printf("[ERROR]: Serial port is not open. Serial read failed.\r\n");
    return ERROR;
  }
  DWORD bytesRead;
  if (!ReadFile(this->handle, buffer, bufferSize, &bytesRead, NULL)) {
    printf("[ERROR]: Could not read from serial port.\r\n");
    return ERROR;
  }
  buffer[bytesRead] = '\0'; // Null-terminate the string
  return SUCCESS;
}