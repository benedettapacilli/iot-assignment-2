import serial

arduino = serial.Serial(port='COM3', baudrate=9600)

situation = 0
waterLevel = 0
bridgeLightStatus = False


while True:
    line = arduino.readline().decode('ascii').strip()

    if line.startswith('s'):
        situation = line[2:]
    elif line.startswith('w'):
        waterLevel = int(line[2:])
    elif line.startswith('b'):
        bridgeLightStatus = bool(int(line[2:]))

    print(situation, waterLevel, bridgeLightStatus)