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
    ax.invert_xaxis()
    plt.plot(seconds_ago, water_level_data)
    fig.canvas.draw()


arduino = serial.Serial(port='COM3', baudrate=9600)

situation = 'NORMAL'
water_level_data = [0] * 30
bridge_light_status = False

seconds_ago = [i for i in range(30, 0, -1)]

use_agg('TkAgg')

layout = [
    [sg.Text("Water level graph")],
    [sg.Graph((740, 480), (0, 0), (30, 30), key='-GRAPH-')],
    [sg.Text("Situation: "), sg.Text(situation, key='-SITUATION-')],
     [sg.Text("Bridge light status: "), sg.Text(
         'on' if bridge_light_status else 'off', key='-BRIDGE_LIGHT_STATUS-')]
]

window = sg.Window('Smart Bridge Data', layout,
                   finalize=True, element_justification='center')

graph = window['-GRAPH-']
plt.ioff()
fig = plt.figure(1)
ax1 = plt.subplot(111)
pack_figure(graph, fig)

last_time_plotted = datetime.datetime.now().timestamp()

while True:
    line = arduino.readline().decode('ascii').strip()

    if line.startswith('s'):
        situation = "NORMAL" if line[2:] == '0' else "PRE-ALARM" if line[2:
                                                                         ] == '1' else "ALARM" if line[2:] == '2' else "UNKNOWN"
        window['-SITUATION-'].update(situation)
    elif line.startswith('w'):
        if(datetime.datetime.now().timestamp() - last_time_plotted > 1):
            water_level_data.append(int(line[2:]))
            water_level_data.pop(0)
            plot_figure(1, 30)
            last_time_plotted = datetime.datetime.now().timestamp()
    elif line.startswith('b'):
        bridge_light_status = True if line[2:] == '1' else False
        window['-BRIDGE_LIGHT_STATUS-'].update(bridge_light_status)

    event, values = window.read(timeout=0)

    if event == sg.WIN_CLOSED or event == 'Exit':
        break

window.close()
