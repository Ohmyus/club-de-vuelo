import tkinter as tk
from tkinter import ttk

root=tk.Tk()
root.title("Controlador Simu")
root.geometry("1280x720")

notebook = ttk.Notebook(root)
notebook.grid(column=0, row=0, sticky="nsew")

root.columnconfigure(0, weight=1)
root.rowconfigure(0, weight=1)

overview_tab = ttk.Frame(notebook)
overview_tab.columnconfigure(0, weight=1)
overview_tab.rowconfigure(0, weight=5)
overview_tab.columnconfigure(1, weight=5)
overview_tab.columnconfigure(2, weight=2)
overview_tab.rowconfigure(1, weight=1)

vert_tab = ttk.Frame(overview_tab, borderwidth=3, relief="ridge", padding=10)
vert_tab.grid(column=0, row=0, rowspan=2, sticky="nsew")
placeholder_text = ttk.Label(vert_tab, text="Vertical\nTab\nMenu")
placeholder_text.grid(row=0, column=0)

visualizer_frame = ttk.Frame(overview_tab, borderwidth=3, relief="ridge", padding=10)
visualizer_frame.grid(column=1, row=0, sticky="nsew")
vis_dummy = ttk.Label(visualizer_frame, text="Dummy Visualizer")
vis_dummy.grid(row=0, column=0)

diagnostics_frame = ttk.Frame(overview_tab, borderwidth=3, relief="ridge", padding=10)
diagnostics_frame.grid(column=2, row=0, sticky="nsew")
diagnostics1_dummy = ttk.Label(diagnostics_frame, text="E-Stop state")
diagnostics2_dummy = ttk.Label(diagnostics_frame, text="MCU Diagnostics")
diagnostics3_dummy = ttk.Label(diagnostics_frame, text="Simulator Readyness")
diagnostics4_dummy = ttk.Label(diagnostics_frame, text="Condor 3 Diagnostics")
diagnostics1_dummy.grid(row=0, column=0, sticky="w")
diagnostics2_dummy.grid(row=1, column=0, sticky="w")
diagnostics3_dummy.grid(row=2, column=0, sticky="w")
diagnostics4_dummy.grid(row=3, column=0, sticky="w")

terminal_frame = ttk.Frame(overview_tab, borderwidth=3, relief="ridge", padding=10)
terminal_frame.grid(row=1, columnspan=2, column=1, sticky="nsew")
terminal_dummy = ttk.Label(terminal_frame, text="Terminal Text")
terminal_dummy.grid(row=0, column=0)

control_tab = ttk.Frame(notebook)

notebook.add(overview_tab, text="Overview")
notebook.add(control_tab, text="Control")

root.mainloop()
