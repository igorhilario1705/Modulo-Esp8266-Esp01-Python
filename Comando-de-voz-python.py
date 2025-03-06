import requests
import speech_recognition as sr

# IP esp01
ESP_IP = "http://192.168.0.48"

def ouvir_comando():
    recognizer = sr.Recognizer()
    with sr.Microphone() as source:
        recognizer.adjust_for_ambient_noise(source)
        print("Aguardando...")

        try:
            comando = recognizer.recognize_google(recognizer.listen(source, timeout=10), language="pt-BR").lower()
            if "ligar" in comando:
                requests.get(f"{ESP_IP}/toggle")
                print("Relé LIGADO!")
                
            elif "desligar" in comando:
                requests.get(f"{ESP_IP}/toggle")
                print("Relé DESLIGADO!")
                
            else:
                print("Comando não reconhecido.")
                
        except (sr.UnknownValueError, sr.WaitTimeoutError):
            print("Nenhum comando detectado.")

while True:
    ouvir_comando()

