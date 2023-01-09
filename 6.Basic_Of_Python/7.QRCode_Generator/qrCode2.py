import qrcode

qr = qrcode.QRCode(
    version=None,
    error_correction=qrcode.constants.ERROR_CORRECT_H,
    box_size=10,
    border=4,
)

qr.add_data('https://www.linkedin.com/in/matheus-belchior-ramires/')
qr.make(fit=True)
img = qr.make_image(fill_color="black", back_color="white")
type(img)  # qrcode.image.pil.PilImage
img.save("qr2.png")