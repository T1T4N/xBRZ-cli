# xBRZ-cli
A command line application that uses the [xBRZ filter](https://sourceforge.net/projects/xbrz/files/xBRZ/) to [scale](https://en.wikipedia.org/wiki/Pixel-art_scaling_algorithms) images.

> xBRZ: "Scale by rules" is a high quality image upscaling filter by Zenju.

Currently it has the best output from all available filters and it's speed matches (and sometime surpasses) that of hqx.

This application uses the awesome library [CImg](http://cimg.eu/) to read and write images.

The project was developed after stumbling across [node-xbrz](https://github.com/kentaromiura/node-xbrz).

![Original image](http://i.imgur.com/dhgI53H.png "Original image")
![sxBRZ x2](http://i.imgur.com/TZLKAmm.png "sxBRZ x2")
![sxBRZ x3](http://i.imgur.com/wYJKREk.png "sxBRZ x3")

#### Usage
The command accepts three arguments: ```xbrz-cli inputFile scaleFactor outputFile```

#### Building
This was built and tested on macOS, but there should be no trouble building for other platforms since the **CImg** library is very portable.

CImg depends on [libpng](http://www.libpng.org/pub/png/libpng.html) to be able to process PNG files.

Fastest way to install it on macOS: ```brew install libpng```

X11 is needed for the (optional) graphical display features of CImg.

The default header, lib locations and linker flags for libpng are already added to the XCode project.

#### Any comments and pull requests if bugs are found are welcome

## License

xBRZ is released under the [GNU General Public License version 3.0 (GPLv3)](https://github.com/T1T4N/xBRZ-cli/blob/master/LICENSE.txt).
