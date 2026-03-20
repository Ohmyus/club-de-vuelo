import numpy as np
import tkinter as tk


class SimulatorDashboard:
    def __init__(self, root):
        self.root = root
        self.root.title("Simulador-GUI")
        self.root.geometry("500x300")
        # Initialize the UI components
        self.build_ui()

    def build_ui(self):
        # --- LABELS (Text) ---
        # A static title spanning two columns
        self.state_label = tk.Label(self.root, text="Estado", font=("Helvetica", 16, "bold"))
        self.state_label.grid(row=0, column=0, columnspan=2, pady=10)

        self.telem_label = tk.Label(self.root, text="Telemetría:")
        self.telem_label.grid(row=2, column=1, sticky="w", padx=5)

        self.telem_info = tk.Label(self.root, text="No recibiendo")
        self.telem_info.grid(row=2, column=2, sticky="w", padx=5)

        self.calc_label = tk.Label(self.root, text="Cálculos:")
        self.calc_label.grid(row=4, column=1, sticky="w", padx=5)

        self.calc_info = tk.Label(self.root, text="Sin Resultado")
        self.calc_info.grid(row=4, column=2, sticky="w", padx=5)

        self.control_label = tk.Label(self.root, text="Control", font=("Helvetica", 16, "bold"))
        self.control_label.grid(row=0, column=8, columnspan=2, pady=10)

        # --- BUTTONS ---
        # Standard button linking to a class method
        self.auto_btn = tk.Button(self.root, text="Activar Movimiento Automático", command=self.start_sim, width=25)
        self.auto_btn.grid(row=4, column=8, pady=20)

        self.man_btn = tk.Button(self.root, text="Activar Movimiento Manual", command=self.manual_control, width=25)
        self.man_btn.grid(row=6, column=8, pady=20)

        # Emergency Stop button with custom colors
        self.stop_btn = tk.Button(self.root, text="E-STOP", bg="red", fg="white", command=self.emergency_stop, width=15)
        self.stop_btn.grid(row=2, column=8, pady=20)

    # Button callback methods
    def start_sim(self):
        print("Simulator Started")

    def emergency_stop(self):
        print("E-STOP TRIGGERED")

    def manual_control(self):
        print("Activated Manual Control")

if __name__ == "__main__":
    root = tk.Tk()
    app = SimulatorDashboard(root)
    root.mainloop() # This is the infinite loop that keeps the window open
