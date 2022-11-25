# <div align=center> IOT Assignment #2 report</div>
## <div align = center> Smart Bridge</div>
## Collaborators:
- Salvatore Antonio Addimando
- Benedetta Pacilli
- Valentina Pieri

<div style="page-break-after: always;"></div>

# Index

<div style="page-break-after: always;"></div>

# FSM schema
![FSMSchema](resources/FSMschema.jpg)
<figcaption align = "center">Figure 1 - FSM schema</figcaption>

In Figure 1 it is shown the schema representation of the Finite State Machine of the program. </br> We decided to structure the state diagram in two macro-states: the first corresponding to the Smart Lightning behavior and the latter to the Monitoring of the Water Level. </br> 

## Smart Lighting
![SmartLightningSchema](resources/SmartLightningSchema.jpg)
<figcaption align = "center">Figure 3 - Smart Lightning state diagram</figcaption>

The focus of this diagram is the division in three states: Idle, Detected and Off.
This parting can be observed in the code as well, inside the SmartLightningState.h file. </br> The following part aims to the description of how we implemented the smart lightining behavior functioning in the state diagram and foremost, how the states allow a correct conduct. </br> The initial state is Idle. Idle represent the state in which nothing was detected and the water level has been reported either as normal or pre-alarm. As soon as something has been detected by the Passive InfraRed sensor (PIR) the state changes to Detected. In the Detected state a light, the La led, can be turned on if the photo sensor measures a light level below a specified threshold, THl and it can be turned off either if the light level goes beyond THl or a time, T1, has passed. T1 restarts whenever the PIR detects movement. There is another way the Idle state can be exited, when the water level is so high that the situation of the water monitoring is labeled as ALARM. In this case the state of the smart lightning is "Off": the La led is always off which means that anything that is detected by the PIR is ignored. From the Off state it is possible to return to the Idle state when the water level situation is labeled either as PRENORMAL or NORMAL.
