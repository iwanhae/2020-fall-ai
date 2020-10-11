import os
import json
from matplotlib import pyplot as plt

if not os.path.isdir('./tmp'):
    os.mkdir("./tmp")
if not os.path.isdir('./tmpout'):
    os.mkdir("./tmpout")

tmp_dir = os.listdir("./tmp")
tmp_dir.sort()
img_dir = []
for fname in tmp_dir:
    data = []
    print(fname)
    with open("./tmp/" + fname, "r") as f:
        data = json.load(f)
    plt.title(fname)
    plt.scatter([0], [0], c="red")
    plt.scatter([0, 1, 1], [1, 0, 1], c="green")
    for i in range(len(data) - 1):
        plt.plot(data[0], data[i + 1])
    plt.savefig("./tmpout/" + fname + ".png")
    img_dir.append("./tmpout/" + fname + ".png")
    plt.close()
import imageio

images = []
for filename in img_dir:
    images.append(imageio.imread(filename))
imageio.mimsave('./movie.gif', images)