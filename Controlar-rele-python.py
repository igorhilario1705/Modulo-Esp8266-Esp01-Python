import requests
import tkinter as tk

ip_esp01 = "http://192.168.0.48"

root = tk.Tk()
root.title("Controle do módulo Relé ESP-01")

status_label = tk.Label(root, text="Clique no botão.", font=("Arial", 12))
status_label.pack(pady=10)

toggle_button = tk.Button(root, text="Ligar/Desligar", font=("Arial", 10),
                          command=lambda: status_label.config(fg="green") 
                          
                          if requests.get(f"{ip_esp01}/toggle").status_code == 200
                          
                          else status_label.config(text="Erro ao acionar!", fg="red"))

toggle_button.pack(pady=10)

root.mainloop()