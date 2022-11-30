# ASSIGNMENT 2 - 2022/2023
# Salvatore Antonio Addimando 0000970539 - salvatore.addimando@studio.unibo.it
# Benedetta Pacilli 0000975296 - benedetta.pacilli@studio.unibo.it
# Valentina Pieri 0000974789 - valentina.pieri5@studio.unibo.it

import serial
import PySimpleGUI as sg
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib import use as use_agg
import math
import datetime


def pack_figure(graph, figure):
    canvas = FigureCanvasTkAgg(figure, graph.Widget)
    plot_widget = canvas.get_tk_widget()
    plot_widget.pack(side='top', fill='both', expand=1)
    return plot_widget


def plot_figure(index, theta):
    fig = plt.figure(index)
    ax = plt.gca()
    ax.cla()
    ax.set_title("30s water level")
    ax.set_xlabel("Seconds ago")
    ax.set_ylabel("Water level (m)")
    ax.set_xscale('linear')
    ax.grid()
    ax.set_ylim(0, 100)
    ax.set_xlim(29, 0)
    plt.plot(seconds_ago, water_level_data)
    fig.canvas.draw()


arduino = serial.Serial(port='COM3', baudrate=9600)

situation = 'NORMAL'
valve_state = 'CLOSED'
water_level_data = [0] * 30
bridge_light_status = False

seconds_ago = [i for i in range(29, -1, -1)]

use_agg('TkAgg')

layout = [
    [sg.Text("Water level graph")],
    [sg.Graph((800, 480), (29, 0), (0, 100), key='-GRAPH-')],
    [sg.Text("Situation: "), sg.Text(situation, key='-SITUATION-'), sg.Text("Bridge light status: "), sg.Text(
        'on' if bridge_light_status else 'off', key='-BRIDGE_LIGHT_STATUS-')],
    [sg.Text("Valve state: "), sg.Text(valve_state, key='-VALVE_STATE-'),
     sg.Button("SWITCH", key='-SWITCH-BUTTON-'), sg.Slider(range=(0, 180), orientation='h', size=(20, 15), key='-SLIDER-')]
]

window = sg.Window('Smart Bridge Data', layout,
                   finalize=True, element_justification='center')

graph = window['-GRAPH-']
plt.ioff()
fig = plt.figure(1)
pack_figure(graph, fig)

last_time_plotted = datetime.datetime.now().timestamp()

while True:
    event, values = window.read(timeout=0)

    line = arduino.readline().decode('ascii').strip()

    if line.startswith('s'):
        situation = "NORMAL" if line[2:] == '0' else "PRE-ALARM" if line[2:
                                                                         ] == '1' else "ALARM" if line[2:] == '2' else "UNKNOWN"
        window['-SITUATION-'].update(situation)
    elif line.startswith('v'):
        if(line[2:] == '0'):
            valve_state = 'CLOSED'
            window['-SWITCH-BUTTON-'].update(disabled=True)
            window['-SLIDER-'].update(disabled=True)
        elif(line[2:] == '1'):
            valve_state = 'AUTO'
            window['-SWITCH-BUTTON-'].update(disabled=False)
            window['-SLIDER-'].update(disabled=True)
        elif(line[2:] == '2'):
            valve_state = 'MANUAL'
            window['-SWITCH-BUTTON-'].update(disabled=False)
            window['-SLIDER-'].update(disabled=False)
            arduino.write(bytes(f"v {values['-SLIDER-']}", 'ascii'))
        else:
            valve_state = 'UNKNOWN'

        window['-VALVE_STATE-'].update(valve_state)
    elif line.startswith('w'):
        if(datetime.datetime.now().timestamp() - last_time_plotted > 1):
            water_level_data.append(int(line[2:]))
            water_level_data.pop(0)
            plot_figure(1, 30)
            last_time_plotted = datetime.datetime.now().timestamp()
    elif line.startswith('b'):
        bridge_light_status = True if line[2:] == '1' else False
        window['-BRIDGE_LIGHT_STATUS-'].update(bridge_light_status)

    if event == sg.WIN_CLOSED or event == 'Exit':
        break
    elif event == '-SWITCH-BUTTON-':
        if valve_state != 'CLOSED' and valve_state != 'UNKNOWN':
            arduino.write(bytes("s", 'ascii'))

window.close()
