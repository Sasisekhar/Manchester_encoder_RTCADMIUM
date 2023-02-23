import matplotlib.pyplot as plt
import serial

# serial port parameters
PORT = 'COM5'
BAUDRATE = 115200

tblk_list = []
outblk_list = []
tdin_list = []
outdin_list = []

with serial.Serial(PORT, BAUDRATE, timeout=1) as ser:
    for i in range(0,200):
        line = ser.readline()
        # debug
        # print(line)
        if len(line.decode("utf-8").split(";")) != 5:
            continue
        t,atomic_id,atomic_name,port_name,val = line.decode("utf-8").split(";")
        if (atomic_name=="blinky" and port_name=="out"):
            # print(line)
            tblk_list.append(float(t))
            outblk_list.append(int(val.split(" ")[-1]))
        elif (atomic_name=="digitalInput" and port_name=="out" and int(val)==0):
            # print(line)
            tdin_list.append(float(t))
            outdin_list.append(int(val))
            tblk = tblk_list
outblk = outblk_list
tdin = tdin_list
outdin = outdin_list

plt.figure(figsize=(15,5))
plt.step(tblk[5:],outblk[5:],label='output')
plt.plot(tdin[0:],outdin[0:],'r*',label='input')
plt.title('Blinky Output')
plt.xlabel('time (s)')
plt.ylabel('value')
plt.legend()
plt.grid(True)