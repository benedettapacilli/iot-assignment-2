# <div align=center> IOT Assignment #2 report</div>
## <div align = center> Smart Bridge</div>
## Collaborators:
- Salvatore Antonio Addimando - 0000970539 - salvatore.addimando@studio.unibo.it
- Benedetta Pacilli - 0000975296 - benedetta.pacilli@studio.unibo.it
- Valentina Pieri, 0000974789 - valentina.pieri5@studio.unibo.it

P.S. The assignment was developed up to the third level of difficulty.

<div style="page-break-after: always;"></div>

# Index

- [1. FSM schema](#fsm-schema)
	- [1.1 Smart Lighting](#smart-lighting)
	- [1.2 Water Level Monitoring](#water-level-monitoring)
- [2. Circuit schema](#circuit-schema)
- [3. Task-based architecture](#task-based-architecture)
	- [3.1 Smart Lighting task](#smart-lighting-task)
	- [3.2 Polling task](#polling-task)
	- [3.3 Valve Behavior task](#valve-behavior-task)
- [4. Instructions](#instructions)
	- [4.1 Dependencies](#dependencies)
	- [4.2 Execution instructions](#execution-instructions)

<div style="page-break-after: always;"></div>

# FSM schema
![FSMSchema](resources/FSMschema.jpg)
<figcaption align = "center">Figure 1 - FSM schema</figcaption>

In Figure 1 it is shown the schema representation of the Finite State Machine of the program.</br> We decided to structure the state diagram in two macro-states: the first corresponding to the Smart Lighting behavior and the latter to the Monitoring of the Water Level.</br>

<div style="page-break-after: always;"></div>

## Smart Lighting
![SmartLightingSchema](resources/SmartLightingSchema.jpg)
<figcaption align = "center">Figure 2 - Smart Lighting state diagram</figcaption>

The focus of the diagram in Figure 2 is the division in three states: "Idle", "Detected" and "Off".
This parting can be observed in the code as well, inside the SmartLightingState.h file.</br> The following part aims to the description of how we implemented the smart lighting behavior functioning in the state diagram and foremost, how the states allow a correct conduct.</br> The initial state is Idle. Idle represent the state in which nothing was detected and the water level has been reported either as normal or pre-alarm. As soon as something has been detected by the Passive InfraRed sensor (PIR) the state changes to Detected. In the Detected state a light, the La led, can be turned on if the photo sensor measures a light level below a specified threshold, THl, and it can be turned off either if the light level goes beyond THl or a time, T1, has passed. T1 restarts whenever the PIR detects movement. There is another way the Idle state can be exited, when the water level is so high that the situation of the water monitoring is labeled as "ALARM". In this case the state of the smart lighting is Off: the La led is always off which means that anything that is detected by the PIR is ignored. From the Off state, it is possible to return to the Idle state when the water level situation is labeled either as "PRENORMAL" or "NORMAL".

<div style="page-break-after: always;"></div>

## Water Level Monitoring

![WaterLevelMonitoringSchema](resources/WaterLevelMonitoringSchema.jpg)

<figcaption align = "center">Figure 3 - Water Level Monitoring state diagram</figcaption>

Figure 3 shows how the monitoring behavior was modelled. The water level monitoring was conceptually split in three diagrams.</br> Firstly, the polling action was defined through its dedicated schema, thus showing how its functioning is loosely coupled with the rest and continuously goes on in the background. At the beginning, the water level is set to zero and later changed, according to the polling results. Water polling is done every PEnormal/PEprealarm/PEalarm seconds based on how high the water level is.</br> The central part of the image shows, through three states, what happens in each of the three possible situations: NORMAL, PREALARM and ALARM. The water level starts off as normal, in which case the Lb led, a green light, is turned on and the Lc led, a red light, is kept off. If the measured water level exceeds the WL1 threshold but not the WL2 one, the state changes to preAlarm. In this second case, Lb is still on, Lc starts blinking and a Liquid Crystal Display (LCD) is turned on so to warn on the current water level. In case the water level goes beyond the WL2 threshold, the alarm state is entered, Lb goes off while Lc is fully turned on and the LCD shows, not only the water level, but also the opening degree of a valve which only opens in the alarm situation.</br> The third and final part of the diagram is a schema regarding the valve functioning.  Originally, the valve is closed and it is kept closed when the situation is either a normal or a preAlarm one. If there is an alarm situation, the valve is opened and it automatically and linearly opens according to the water level. While the valve is in automatic mode, its control can be taken using a button and a potentiometer; this way the opening can be ad large as desired.  Repressing the button allows returning to automatic mode.

<div style="page-break-after: always;"></div>

# Circuit schema
![CircuitSchema](resources/CircuitSchema.png)
<figcaption align = "center">Figure 4 - Circuit graphic schema</figcaption>

![MinimalCircuitSchema](resources/MinimalSchema.png)
<figcaption align = "center">Figure 5 - Circuit minimal schema</figcaption>

Figures 4 and 5 showcase the circuit designed used in the project.

<div style="page-break-after: always;"></div>

# Task based architecture

The tasks identified are the following:
- ## Smart Lighting task:
This task is represented by the SmartLightingTask.h and SmartLightingTask.cpp files, and it consists of the La led, the Light Sensor and the PIR. It simulates a bridge in which, in case someone pass (is detected by the PIR), a green light turns on, depending on the intensity of the light level measured. The task is deactivated when the water level situation is labeled as "ALARM", this is possible thanks to the Situation.h and Situation.cpp files.
- ## Polling task:
This task is depicted by the PollingTask.h and PollingTask.cpp files. It represents the action of continuous water level monitoring and measuring. According to the water level, the situation is labeled as "NORMAL"/"PREALARM"/"ALARM" which allows an exchange of information, between the tasks. In fact, the whole program functioning is based on how high/low the current water level is.
- ## Valve Behavior task:
The files representing this task are the ValveBehaviorTask.h and the ValveBehaviorTask.cpp and together they simulate the valve functioning; in particular, how the valve automatically opens if the water situation is labeled as "ALARM" and the switch between automatic and manual mode.

<div style="page-break-after: always;"></div>

# Instructions
This last chapter aims to provide guidance on how to properly run the program by providing instructions on the libraries to installed and the steps to be taken to be able to correctly and concurrently run both the python and Arduino part of the program.

## Dependencies
In order to run the program, there are some libraries that have to be installed.

### Arduino libraries
- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
- [TimerOne](https://github.com/PaulStoffregen/TimerOne)
### Python libraries
Run the specified commands according to the O.S. you are using:
- On Ubuntu:
```
sudo apt install python3 && sudo apt install python3-pip && pip3 install pysimplegui && pip3 install matplotlib && pip3 install pyserial
```
- On Windows:
```
pip3 install pysimplegui ; pip3 install matplotlib ; pip3 install pyserial
```

## Execution instructions

1. Open project folder (the one containing src and pc directories) in vscode using PlatformIO extension
2. Edit the config file platformio.ini according to the location of the Arduino libraries on your machine
3. Plug the Arduino board via USB
4. Build and Upload the code through the PlatformIO extension
5. Unplug the Arduino board
6. Start the python script by running the following command:
```python3 src/pc/main.py```
7. Plug the Arduino board via USB once again