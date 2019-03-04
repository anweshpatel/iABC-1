# iABC-1
Codes and materials for iABC course

Refer to the pdfs made available

To run the server, start the ./restfulserver/app.py using python 3

```
  #For those using virtualenv
  python app.py
  
  #For those have both Python2 and 3 without virtualenv
  python3 app.py
```

In the arduino ```.ino``` files, replace ```< ... >``` tokens with suitable values

## Try LED on/off from browser

### 1. Start the server

Use the method stated above

### 2. Flash the ESP8266 with the BasicHttpClient_Get code using arduino IDE

Change the tokens as mentioned before

### 3. Try to open a browser on your computer and hit the url

To turn on, replace 7 by any number greater than 0

  http://localhost:8080/iot?reqtype=update&led=7

Then try

  http://localhost:8080/iot?reqtype=update&led=0

### ----------------------------------------

*** Always have a serial monitor open in arduino to analyse the program ***
