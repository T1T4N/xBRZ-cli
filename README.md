# xBRZ-cli
A command line application that uses the [xBRZ filter](https://sourceforge.net/projects/xbrz/files/xBRZ/) to scale images

xBRZ: "Scale by rules" is a high quality image upscaling filter by Zenju.
Currently it has the best output from all available filters and it's speed matches (and sometime surpasses) that of hqx.

This application uses the awesome library [CImg](http://cimg.eu/) to read and write images.

The application was developed after stumbling across [node-xbrz](https://github.com/kentaromiura/node-xbrz), and realizing that Zenju, the original author, forgot to upload the source for the ScalerTest.

#### Usage
The command accepts three arguments: ```xbrz-cli inputFile scaleFactor outputFile```

#### Building
This was built and tested on MacOSX, but there should be no trouble building for other platforms since the **CImg** library is very portable.

CImg depends on [libpng](http://www.libpng.org/pub/png/libpng.html) to be able to process PNG files.

Fastest way to install it on MacOSX: ```brew install libpng```

If you want fork & modify the code and use the graphical display features of CImg, you will also need X11.

The default header, lib locations and linker flags for libpng and X11 have already been added to the XCode project.

#### Any comments and pull requests if bugs are found are welcome
