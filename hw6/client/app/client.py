import requests
import time

def main():
    while True:
        try:
            r = requests.get('http://localhost:5000')
            print(r.text)
            break
        except:
            continue

if __name__ == "__main__":
    main()