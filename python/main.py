import serial

arduino = serial.Serial(port='COM3', baudrate=9600)

situation = NORMAL
waterLevel = 0
bridgeLightStatus = False


while True:
    situation = arduino.readline().decode('ascii')
    waterLevel = arduino.readline().decode('ascii')
    bridgeLightStatus = True if arduino.readline().decode('ascii') == 'True' else False

    print(situation, waterLevel, bridgeLightStatus)
