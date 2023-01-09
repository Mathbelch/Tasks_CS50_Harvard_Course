import os
import qrcode

img = qrcode.make("https://www.linkedin.com/in/matheus-belchior-ramires/")
type(img)
img.save("qr.png","PNG")