#ifndef SERIAL_PORT_HPP
#define SERIAL_PORT_HPP

#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <unistd.h>

#define MAX_COMPORT_LEN 32

#ifndef ERROR
#define ERROR 1
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

class SerialPort{
  private: 
    int port_open;
    HANDLE handle;
    DCB dcb_params;
    COMMTIMEOUTS timeouts;
  public:
    SerialPort(const char *comPort);
    ~SerialPort();

    int write(const char *data);
    int read(char *buffer, DWORD bufferSize);
};

#endif // SERIAL_PORT_HPP