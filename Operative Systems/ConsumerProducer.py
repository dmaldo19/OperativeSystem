import random
import msvcrt
import time
import os

BUFFER_SIZE = 20

# Clase para el buffer circular
class CircularBuffer:
    def __init__(self):
        self.data = [0] * BUFFER_SIZE
        self.head = 0
        self.tail = 0

# Función para imprimir el estado del buffer
def imprimir_buffer(buffer):
    print("Estado del Buffer:")
    print()
    for i in range(BUFFER_SIZE):
        if buffer.data[i] != 0:
            print(f"[{i+1}] => {buffer.data[i]}")
        else:
            print(f"[{i+1}] => Vacío")


if __name__ == "__main__":
    # Inicialización del buffer
    buffer = CircularBuffer()

    # Inicialización de variables de productor y consumidor
    productor_trabajando = False
    consumidor_trabajando = False
    funcionar_programa = True
    bufferLleno = False
    imprimir_buffer(buffer)
    while funcionar_programa:
        os.system("cls")
        # Chequeo si se presiona la tecla ESC para terminar el programa
        if msvcrt.kbhit() and msvcrt.getch() == b'\x1b':
            break
        trabajador = random.randint(0,1)
        if trabajador == 0:
            productor_trabajando = True
            consumidor_trabajando = False
        else:
            productor_trabajando = False
            consumidor_trabajando = True
        # Productor
        if productor_trabajando:
            producir = random.randint(4, 7)  # Genera un número aleatorio entre 4 y 7
            contador = 0

            if not bufferLleno:
                for _ in range(producir):
                    os.system("cls")
                    print(f"El productor está produciendo {producir - contador} elementos.")
                    print("El consumidor esta dormido.")
                    print("Productor trabajando...")
                    buffer.data[buffer.head] = random.randint(1, 99)  # Genera un número aleatorio entre 0 y 99
                    if buffer.data[(buffer.head + 1) % BUFFER_SIZE] == 0: 
                        buffer.head = (buffer.head + 1) % BUFFER_SIZE
                    else:
                        buffer.head = (buffer.head + 1) % BUFFER_SIZE
                        os.system("cls")
                        print("El productor esta intentando producir.")
                        print(f"El consumidor está dormido.")
                        print("Contenedor lleno...")
                        bufferLleno = True
                        imprimir_buffer(buffer)
                        time.sleep(producir - contador)
                        break
                    imprimir_buffer(buffer)
                    if msvcrt.kbhit() and msvcrt.getch() == b'\x1b':
                        funcionar_programa = False
                        break
                    contador+=1
                    time.sleep(0.5)
                print("El productor ha terminado de producir.")

            else:
                print("El buffer está lleno. El productor está esperando(Durmiendo).")
                print("El consumidor esta dormido.")
                print("Intentando entrar el productor")
                imprimir_buffer(buffer)
                if msvcrt.kbhit() and msvcrt.getch() == b'\x1b':
                    funcionar_programa = False
                    break
                time.sleep(producir)
            

        # Consumidor
        if consumidor_trabajando:
            consumir = random.randint(4, 7)  # Genera un número aleatorio entre 4 y 7
            contador = 0
            if buffer.tail != buffer.head or bufferLleno: 
                for _ in range(consumir):
                    os.system("cls")
                    print("El productor esta dormido.")
                    print(f"El consumidor está consumiendo {consumir - contador} elementos.")
                    print("Consumidor trabajando...")
                    if buffer.data[buffer.tail] == 0:
                        os.system("cls")
                        print("El productor esta dormido.")
                        print(f"El consumidor está intentando consumir.")
                        print("Contenedor vacio...")
                        imprimir_buffer(buffer)
                        time.sleep(consumir - contador)
                        break
                    buffer.data[buffer.tail] = 0
                    buffer.tail = (buffer.tail + 1) % BUFFER_SIZE
                    imprimir_buffer(buffer)
                    if msvcrt.kbhit() and msvcrt.getch() == b'\x1b':
                        funcionar_programa = False
                        imprimir_buffer(buffer)
                        break
                    contador += 1
                    time.sleep(0.5)
                print("El consumidor ha terminado de consumir.")
                bufferLleno = False
            else:
                print("El productor esta dormido.")
                print("El buffer está vacío. El consumidor está esperando(Durmiendo).")
                print("Intentando entrar el consumidor")
                imprimir_buffer(buffer)
                if msvcrt.kbhit() and msvcrt.getch() == b'\x1b':
                    funcionar_programa = False
                    break
                time.sleep(consumir)
    print("Simulador productor consumidor finalizado...")