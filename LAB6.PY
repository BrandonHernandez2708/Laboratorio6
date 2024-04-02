import serial
import tkinter as tk

class ArduinoInterface:
    def __init__(self, port='COM3', baud_rate=9600):
        try:
            self.ser = serial.Serial(port, baud_rate, timeout=1)
        except serial.SerialException as e:
            print("Error al conectar con el puerto serial:", e)

    def enviar_comando(self, comando):
        try:
            self.ser.write(comando.encode())
        except serial.SerialException as e:
            print("Error al enviar el comando:", e)

    def obtener_estado(self):
        try:
            self.ser.write(b'S')
            return self.ser.readline().decode().strip()
        except serial.SerialException as e:
            print("Error al obtener el estado:", e)

class LEDButtonApp:
    def __init__(self, master, arduino):
        self.master = master
        self.arduino = arduino
        self.create_widgets()
        self.actualizar_estado()

    def create_widgets(self):
        self.shapes = []
        self.buttons = []
        for i in range(4):
            shape = tk.Canvas(self.master, width=40, height=40, bg='gray')
            shape.grid(row=i, column=2, padx=10, pady=5)
            self.shapes.append(shape)

        for i, grupo in enumerate(['A', 'B', 'C', 'D']):
            button = tk.Button(self.master, text=f"Encender Grupo {grupo}",
                               command=lambda g=grupo: self.arduino.enviar_comando(g))
            button.grid(row=i, column=0, padx=10, pady=5)
            self.buttons.append(button)

        for i, grupo in enumerate(['a', 'b', 'c', 'd']):
            button = tk.Button(self.master, text=f"Apagar grupo {grupo}",
                               command=lambda g=grupo: self.arduino.enviar_comando(g))
            button.grid(row=i, column=1, padx=10, pady=5)
            self.buttons.append(button)

    def actualizar_estado(self):
        try:
            estado = self.arduino.obtener_estado()
            if estado is not None:  # Verificar si se obtuvo un estado válido
                for i, val in enumerate(estado):
                    color = 'red' if val == '1' else 'green'
                    self.shapes[i].delete("LED")
                    self.shapes[i].create_oval(5, 5, 35, 35, fill=color, outline=color, tags="LED")
                    grupo = chr(ord('A') + i)
                    if val == '0':
                        self.buttons[i].config(bg='green')
                        print(f"LED del Grupo {grupo} apagado por medio del botón del Grupo {grupo}.")
                    else:
                        self.buttons[i].config(bg='SystemButtonFace')
                        print(f"LED del Grupo {grupo} encendido por medio del botón del Grupo {grupo}.")
        except Exception as e:
            print(f"Error al obtener el estado del Arduino: {e}")
        if self.arduino is not None:
            self.master.after(100, self.actualizar_estado)

def main():
    arduino = ArduinoInterface()
    if hasattr(arduino, 'ser') and arduino.ser.is_open:
        root = tk.Tk()
        root.title("Control de LEDs y Botones")
        app = LEDButtonApp(root, arduino)
        root.mainloop()
    else:
        print("No se pudo establecer la conexión con el Arduino.")

if __name__ == "__main__":
    main()
