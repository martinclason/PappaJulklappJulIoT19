from PIL import Image
import qrcode

qr_img = qrcode.make('http://192.168.4.1')
qr_img.save("url.png");

im = Image.open("url.png")
pxls = im.load()

scale = 1
downscale = 10
padding = 40

uppercorner = ((0,25), (0,25))

uppercorner_text = ""

pixel_counter = 0

for y in range(padding + uppercorner[1][0], padding + downscale*uppercorner[1][1],
              downscale):
    for _ in range(0,scale):
        for x in range(padding + uppercorner[0][0], padding +
                       downscale*uppercorner[0][1], downscale):
            v = pxls[x,y]
            if pixel_counter % 8 == 0:
                print("B", end="")
            if v == 255:
                print(scale*"0", end="")
            else:
                print(scale*"1", end="")
            pixel_counter += 1
            if pixel_counter % 8 == 0:
                print(", ", end="")
        missing_zeros = 8 - pixel_counter % 8
        print(missing_zeros*"0"+",\n", end="")
        pixel_counter += missing_zeros
        #print("")



