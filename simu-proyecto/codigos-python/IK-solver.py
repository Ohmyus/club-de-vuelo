import tkinter as tk
from tkinter import ttk
import numpy as np
import matplotlib
matplotlib.use("TkAgg")  
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure

def inverse_kinematics(pitch, roll, geom): #Esta es la función principal, toma los valores de cabeceo y alabeo, y los 
    #Matrices de giro:
    L_theta = np.array([
        [np.cos(pitch), 0, np.sin(pitch)],
        [0 , 1, 0],
        [-np.sin(pitch), 0, np.cos(pitch)]
    ])

    L_phi = np.array([
        [1 , 0, 0],
        [0, np.cos(roll), -np.sin(roll)],
        [0, np.sin(roll), np.cos(roll)]
    ])

    R_bt = L_theta @ L_phi


    #Vamos con los mecanismos de barras:
    t = geom["t"]
    s = geom["s"]
    J_t = R_bt @ geom["J_b"]

    psi = np.array([0.0, 0.0])

    for i in range(2):
        l_t = geom["M_t"][:,i] - J_t[:,i]
        l = np.linalg.norm(l_t)

        if (abs((l**2+t**2-s**2)/(2*l*t)) <= 1):
            S_ang = np.acos((l**2+t**2-s**2)/(2*l*t))
        else: #Solución inválida
            S_ang = np.pi/2
            return None, None, False
        b = t/np.cos(S_ang)
        l_p = np.sqrt(l_t[0]**2 + l_t[2]**2)

        b_p = l_p*b/l
        beta = np.atan(l_t[2]/l_t[0])
        gamma_p = np.acos(t/b_p)

        psi[i] = beta-gamma_p

    return [psi, R_bt, True]

def calc_joint_positios(psi, geom, R):
    arms = np.zeros((3, 6), dtype=float)
    J_t = R @ geom["J_b"]

    for i in range(2):
        j = 3*i
        arms[:,j] = geom["M_t"][:,i]
        arms[:,j+1] = geom["M_t"][:,i] - np.array([+geom["t"]*np.cos(psi[i]), 0, +geom["t"]*np.sin(psi[i])]).T
        arms[:,j+2] = J_t[:,i]

        s_calc = np.linalg.norm(arms[:,j+1] - arms[:,j+2])

        if (s_calc - geom["s"] > 1e-3):
            return None, False

    fus_t = R @ geom["fus_b"]
    wing_t = R @ geom["wing_b"]

    return [
        [
            {"name": "Fuselage", "points": fus_t, "color": "black"},
            {"name": "Wing", "points": wing_t, "color": "black"},
            {"name": "LArm", "points": arms[:,:3], "color": "red"},
            {"name": "RArm", "points": arms[:,3:], "color": "red"},
            {"name": "Bar", "points": J_t, "color": "green"},
        ],
            True
        ]

# Main app
np.set_printoptions(precision=4, suppress=True)

#Declaración de la geometría:
geometry = {
    "M_t": np.array([#Posición del eje de los motores en ejes tierra
        [-0.6, -0.4, 0.0],
        [-0.6, 0.4, 0.0]
    ]).T,
    "J_b": np.array([#Posición de los extremos de las articulaciones en ejes cuerpo
        [-0.8, -0.4, -0.6],
        [-0.8, 0.4, -0.6]
    ]).T,
    #Geometría de ayuda para visualizar el planeador

    #Fuselaje
    "fus_b" : np.array([
        [1.0, 0.0, -0.5],
        [-1.0, 0.0, -0.5]
    ]).T,

    #Alas
    "wing_b" : np.array([
        [0.0, -0.75, -0.5],
        [0.0, 0.75, -0.5]
    ]).T,

    #Barras de las articulaciones
    "s": 0.6,
    "t": 0.2
}

class LinkageApp(tk.Tk):
    def __init__(self):
        super().__init__()

        self.valid = True

        self.title("Linkage Visualizer")

        # Matplotlib Figure
        self.fig = Figure(figsize=(9, 7))
        self.ax = self.fig.add_subplot(111, projection="3d")
        self.canvas = FigureCanvasTkAgg(self.fig, master=self)
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

        # Sliders
        self.pitch = tk.DoubleVar(value=0)
        self.roll = tk.DoubleVar(value=0)

        pitch_slider = ttk.Scale(self, from_=30*np.pi/180, to=-30*np.pi/180, orient="horizontal",
                                 variable=self.pitch, command=self.update_plot)
        roll_slider = ttk.Scale(self, from_=-30*np.pi/180, to=30*np.pi/180, orient="horizontal",
                                variable=self.roll, command=self.update_plot)

        ttk.Label(self, text="Pitch").pack()
        pitch_slider.pack(fill="x")
        ttk.Label(self, text="Roll").pack()
        roll_slider.pack(fill="x")

        # Initial plot
        self.update_plot()

    def update_plot(self, *args):
        pitch = self.pitch.get()
        roll = self.roll.get()
        motor_angles, RotationMatrix, ok1 = inverse_kinematics(pitch, roll, geometry)
        if not ok1:
            self.valid = False
            print("Glider out of limits")
            return
        joints, ok2 = calc_joint_positios(motor_angles, geometry, RotationMatrix)
        if not ok2:
            self.valid = False
            print("Glider out of limits")
            return

        self.valid = True
        self.ax.clear()
        for arm in joints:
            pts = arm["points"]
            self.ax.plot(
                pts[0,:], pts[1,:], pts[2,:],
                "-o", linewidth=2, label=arm["name"], color=arm["color"]
            )
        self.ax.set_xlim(-1, 1)
        self.ax.set_ylim(1, -1)
        self.ax.set_zlim(1, -1)
        self.ax.set_xlabel("X")
        self.ax.set_ylabel("Y")
        self.ax.set_zlabel("Z")
        self.canvas.draw()

if __name__ == "__main__":
    app = LinkageApp()
    app.mainloop()