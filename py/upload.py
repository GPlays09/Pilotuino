import serial, serial.tools.list_ports
import time
import sys, os

run_cmd = "hardware\\tools\\bin\\avrdude -Chardware\\tools\\etc\\avrdude.conf -v -patmega32u4 -cavr109 -P{port1} -b57600 -D -Uflash:w:{file1}:i"

def find_port():
    search_start = time.time()
    rn = time.time()
    
    while rn - search_start < 10.0:
        ports = serial.tools.list_ports.comports()

        for port, desc, hwid in sorted(ports):
            if "VID:PID=2341:0036" in hwid:  # Leonardo bootloader
                return [port, 1]
            elif "VID:PID=2341:8036" in hwid:  # Leonardo
                return [port, 2]
        rn = time.time()
    
    return [0, 0]

print("Looking for any suitable devices")
ret = find_port()

if ret[1] == 0:
    print("Device not found")
elif ret[1] == 1:
    os.system(run_cmd.format(port1=ret[0], file1=sys.argv[1]))
elif ret[1] == 2:
    print("Force resetting Leonardo")
    serial.Serial(ret[0], baudrate=1200)
    time.sleep(1)
    ret1 = find_port()

    if ret1[1] == 0:
        print("Device not found")
    elif ret1[1] == 1:
        os.system(run_cmd.format(port1=ret1[0], file1=sys.argv[1]))
    else:
        print("Missed upload window")
