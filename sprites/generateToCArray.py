from PIL import Image
import numpy as np

def rgba2rgb( rgba, background=(255,255,255)):


    rgb = [0,0,0]
    r, g, b, a = rgba[0], rgba[1], rgba[2], rgba[3]

    a = np.asarray( a, dtype='int' ) / 255.0

    R, G, B = background

    rgb[0] = r * a + (1.0 - a) * R
    rgb[1] = g * a + (1.0 - a) * G
    rgb[2] = b * a + (1.0 - a) * B

    return rgb

def compress_pixel(r, g, b):
    # Compress RGBA values into a special 8-bit format
    compressed_value = (( int(r)>> 5) << 5) | ((int(g) >> 5) << 2) | (int(b) >> 5)
    return compressed_value

def png_to_c_array(filename, output_file):
    # Open the PNG file
    img = Image.open(filename)
    #img = img.convert('RGB')
    # Get image dimensions
    width, height = img.size
    print(width)
    print(height)
    # Get pixel data as a flat list of RGBA values
    # Generate C-style array string
    array_string = "{\n"
    for i in range(height):
        array_string += "{"
        for j in range(width):
            coordinate = [j,i]
            
            
            pixel = np.array(img.getpixel(coordinate))
            ret = rgba2rgb(pixel)
            #print (ret)
            compr = compress_pixel(ret[0],ret[1],ret[2])
            array_string += str(compr)
            array_string += ","
        array_string = array_string[:-1]
        array_string += "},\n"
    array_string += "};\n"

    # Write the generated array string to the output file
    with open(output_file, "w") as f:
        f.write("#ifndef " + filename[:-4] + "sprite_h \n#define " + filename[:-4] + "sprite_h\nstatic unsigned char " + filename[:-4] + "_pixel_data[32][32] = " + array_string + "\n #endif")

# Usage example
input_filename = "caster.png"
output_filename = "caster.h"
png_to_c_array(input_filename, output_filename)
print(f"Pixel data written to {output_filename}")

input_filename = "defender.png"
output_filename = "defender.h"
png_to_c_array(input_filename, output_filename)
print(f"Pixel data written to {output_filename}")

input_filename = "guard.png"
output_filename = "guard.h"
png_to_c_array(input_filename, output_filename)
print(f"Pixel data written to {output_filename}")

input_filename = "medic.png"
output_filename = "medic.h"
png_to_c_array(input_filename, output_filename)
print(f"Pixel data written to {output_filename}")

input_filename = "sniper.png"
output_filename = "sniper.h"
png_to_c_array(input_filename, output_filename)
print(f"Pixel data written to {output_filename}")

input_filename = "specialist.png"
output_filename = "specialist.h"
png_to_c_array(input_filename, output_filename)
print(f"Pixel data written to {output_filename}")

input_filename = "supporter.png"
output_filename = "supporter.h"
png_to_c_array(input_filename, output_filename)
print(f"Pixel data written to {output_filename}")

input_filename = "vanguard.png"
output_filename = "vanguard.h"
png_to_c_array(input_filename, output_filename)
print(f"Pixel data written to {output_filename}")
