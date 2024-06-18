#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "image.h"
#include "ColorFilter.h"
#include "BlurFilter.h"
#include "EdgeDetector.h"

int main() {

    // Load the input images
    const char* dimorphosInputImagePath = "./Images/dimorphos.png";
    int dimorphosWidth, dimorphosHeight, dimorphosChannels;
    unsigned char* dimorphosData = stbi_load(dimorphosInputImagePath, &dimorphosWidth, &dimorphosHeight, &dimorphosChannels, 0);
    Image dimorphosImg(dimorphosData, dimorphosWidth, dimorphosHeight, dimorphosChannels);

    const char* gracehopperInputImagePath = "./Images/gracehopper.png";
    int gracehopperWidth, gracehopperHeight, gracehopperChannels;
    unsigned char* gracehopperData = stbi_load(gracehopperInputImagePath, &gracehopperWidth, &gracehopperHeight, &gracehopperChannels, 0);
    Image gracehopperImg(gracehopperData, gracehopperWidth, gracehopperHeight, gracehopperChannels);

    const char* stinkbugInputImagePath = "./Images/stinkbug.png";
    int stinkbugWidth, stinkbugHeight, stinkbugChannels;
    unsigned char* stinkbugData = stbi_load(stinkbugInputImagePath, &stinkbugWidth, &stinkbugHeight, &stinkbugChannels, 0);
    Image stinkbugImg(stinkbugData, stinkbugWidth, stinkbugHeight, stinkbugChannels);

    const char* tienshanInputImagePath = "./Images/tienshan.png";
    int tienshanWidth, tienshanHeight, tienshanChannels;
    unsigned char* tienshanData = stbi_load(tienshanInputImagePath, &tienshanWidth, &tienshanHeight, &tienshanChannels, 0);
    Image tienshanImg(tienshanData, tienshanWidth, tienshanHeight, tienshanChannels);

    const char* vhAnatomySp15InputImagePath = "./Images/vh_anatomy_sp15.png";
    int vhAnatomySp15Width, vhAnatomySp15Height, vhAnatomySp15Channels;
    unsigned char* vhAnatomyDataSp15 = stbi_load(vhAnatomySp15InputImagePath, &vhAnatomySp15Width, &vhAnatomySp15Height, &vhAnatomySp15Channels, 0);
    Image vhAnatomySp15Img(vhAnatomyDataSp15, vhAnatomySp15Width, vhAnatomySp15Height, vhAnatomySp15Channels);
    vhAnatomySp15Img.displayImageInfo();

    const char* vhAnatomyInputImagePath = "./Images/vh_anatomy.png";
    int vhAnatomyWidth, vhAnatomyHeight, vhAnatomyChannels;
    unsigned char* vhAnatomyData = stbi_load(vhAnatomyInputImagePath, &vhAnatomyWidth, &vhAnatomyHeight, &vhAnatomyChannels, 0);
    Image vhAnatomyImg(vhAnatomyData, vhAnatomyWidth, vhAnatomyHeight, vhAnatomyChannels);

    const char* vhCtInputImagePath = "./Images/vh_ct.png";
    int vhCtWidth, vhCtHeight, vhCtChannels;
    unsigned char* vhCtData = stbi_load(vhCtInputImagePath, &vhCtWidth, &vhCtHeight, &vhCtChannels, 0);
    Image vhCtImg(vhCtData, vhCtWidth, vhCtHeight, vhCtChannels);

// |-- 1-grayscale
// |   |-- gracehopper.png
// |   \-- tienshan.png

    // 1.1 gracehopper
    const char* gracehopperOutputImagePath = "./Output/1-grayscale/gracehopper.png";
    Image gracehopperGrayImg = ColorFilter::toGrayscale(gracehopperImg);
    stbi_write_png(gracehopperOutputImagePath, gracehopperWidth, gracehopperHeight, 1, gracehopperGrayImg.getImageData(), gracehopperGrayImg.getWidth()* gracehopperGrayImg.getChannels());

    // 1.2 tienshan
    const char* tienshanOutputImagePath = "./Output/1-grayscale/tienshan.png";
    Image tienshanGrayImg = ColorFilter::toGrayscale(tienshanImg);
    stbi_write_png(tienshanOutputImagePath, tienshanWidth, tienshanHeight, 1, tienshanGrayImg.getImageData(), tienshanGrayImg.getWidth()* tienshanGrayImg.getChannels());


// |-- 2-brightness
// |   |-- gracehopper_minus100.png   # minus 100 from each channel
// |   |-- gracehopper_plus100.png    # plus 100 to each channel
// |   |-- stinkbug_minus50.png       # minus 50 from each channel
// |   |-- stinkbug_plus50.png        # plus 50 to each channel

    // 2.1 gracehopper_minus100
    const char* gracehopperMinus100OutputImagePath = "./Output/2-brightness/gracehopper_minus100.png";
    int gracehopperMinus100Brightness = -100; // Adjust brightness by -100
    Image gracehopperMinus100AdjustedImg = ColorFilter::adjustBrightness(gracehopperImg, gracehopperMinus100Brightness);
    gracehopperMinus100AdjustedImg.displayImageInfo();
    stbi_write_png(gracehopperMinus100OutputImagePath, gracehopperMinus100AdjustedImg.getWidth(), gracehopperMinus100AdjustedImg.getHeight(), gracehopperMinus100AdjustedImg.getChannels(), gracehopperMinus100AdjustedImg.getImageData(), gracehopperMinus100AdjustedImg.getWidth() * gracehopperMinus100AdjustedImg.getChannels());

    // 2.2 gracehopper_plus100
    const char* gracehopperPlus100OutputImagePath = "./Output/2-brightness/gracehopper_plus100.png";
    int gracehopperPlus100Brightness = +100; // Adjust brightness by +100
    Image gracehopperPlus100AdjustedImg = ColorFilter::adjustBrightness(gracehopperImg, gracehopperPlus100Brightness);
    gracehopperPlus100AdjustedImg.displayImageInfo();
    stbi_write_png(gracehopperPlus100OutputImagePath, gracehopperPlus100AdjustedImg.getWidth(), gracehopperPlus100AdjustedImg.getHeight(), gracehopperPlus100AdjustedImg.getChannels(), gracehopperPlus100AdjustedImg.getImageData(), gracehopperPlus100AdjustedImg.getWidth() * gracehopperPlus100AdjustedImg.getChannels());

    // 2.3 stinkbug_minus50
    const char* stinkbugMinus50OutputImagePath = "./Output/2-brightness/stinkbug_minus50.png";
    int stinkbugMinus50Brightness = -50; // Adjust brightness by -50
    Image stinkbugMinus50AdjustedImg = ColorFilter::adjustBrightness(stinkbugImg, stinkbugMinus50Brightness);
    stinkbugMinus50AdjustedImg.displayImageInfo();
    stbi_write_png(stinkbugMinus50OutputImagePath, stinkbugMinus50AdjustedImg.getWidth(), stinkbugMinus50AdjustedImg.getHeight(), stinkbugMinus50AdjustedImg.getChannels(), stinkbugMinus50AdjustedImg.getImageData(), stinkbugMinus50AdjustedImg.getWidth() * stinkbugMinus50AdjustedImg.getChannels());

    // 2.4 stinkbug_plus50
    const char* stinkbugPlus50OutputImagePath = "./Output/2-brightness/stinkbug_plus50.png";
    int stinkbugPlus50Brightness = -50; // Adjust brightness by -50
    Image stinkbugPlus50AdjustedImg = ColorFilter::adjustBrightness(stinkbugImg, stinkbugPlus50Brightness);
    stinkbugPlus50AdjustedImg.displayImageInfo();
    stbi_write_png(stinkbugPlus50OutputImagePath, stinkbugPlus50AdjustedImg.getWidth(), stinkbugPlus50AdjustedImg.getHeight(), stinkbugPlus50AdjustedImg.getChannels(), stinkbugPlus50AdjustedImg.getImageData(), stinkbugPlus50AdjustedImg.getWidth() * stinkbugPlus50AdjustedImg.getChannels());

// |-- 3-histogram
// |   |-- vh_anatomy_HSL.png         # equalise histogram of L channel
// |   |-- vh_anatomy_HSV.png         # equalise histogram of V channel
// |   |-- vh_ct.png                  # equalise histogram of grayscale image    

    // 3.1 vh_anatomy_HSL.png
    const char* vhAnatomyOutputImagePath_HSL = "./Output/3-histogram/vh_anatomy_HSL.png";
    Image equalizedImg_HSL = ColorFilter::histogramEqualization(vhAnatomyImg, "HSL");
    equalizedImg_HSL.displayImageInfo();
    stbi_write_png(vhAnatomyOutputImagePath_HSL, equalizedImg_HSL.getWidth(), equalizedImg_HSL.getHeight(), equalizedImg_HSL.getChannels(), equalizedImg_HSL.getImageData(), equalizedImg_HSL.getWidth() * equalizedImg_HSL.getChannels());

    // 3.2 vh_anatomy_HSV.png
    const char* vhAnatomyOutputImagePath_HSV = "./Output/3-histogram/vh_anatomy_HSV.png";
    Image equalizedImg_HSV = ColorFilter::histogramEqualization(vhAnatomyImg, "HSV");
    equalizedImg_HSV.displayImageInfo();
    stbi_write_png(vhAnatomyOutputImagePath_HSV, equalizedImg_HSV.getWidth(), equalizedImg_HSV.getHeight(), equalizedImg_HSV.getChannels(), equalizedImg_HSV.getImageData(), equalizedImg_HSV.getWidth() * equalizedImg_HSV.getChannels());

    // 3.3 vh_ct.png
    const char* vhCtOutputImagePath = "./Output/3-histogram/vh_ct.png";
    vhCtImg.displayImageInfo();
    Image equalizedImg_vhCt = ColorFilter::histogramEqualization(vhCtImg, "RGB");
    equalizedImg_vhCt.displayImageInfo();
    stbi_write_png(vhCtOutputImagePath, equalizedImg_vhCt.getWidth(), equalizedImg_vhCt.getHeight(), equalizedImg_vhCt.getChannels(), equalizedImg_vhCt.getImageData(), equalizedImg_vhCt.getWidth() * equalizedImg_vhCt.getChannels());

// |-- 4-threshold
// |   |-- stinkbug_80.png            # threshold grayscale at 80
// |   |-- tienshan_HSL_127.png       # threshold L channel at 127
// |   |-- tienshan_HSV_127.png       # threshold V channel at 127
// |   |-- vh_ct_80.png               # threshold grayscale at 80

    // 4.1 stinkbug_80.png
    const char* stinkbugOutputImagePath_80 = "./Output/4-threshold/stinkbug_80.png";
    unsigned char threshold_80 = 80; // Apply threshold filter with threshold value of 80
    Image thresholdedImg_80 = ColorFilter::thresholdImage(stinkbugImg, threshold_80, "RGB");
    thresholdedImg_80.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_80, thresholdedImg_80.getWidth(), thresholdedImg_80.getHeight(), thresholdedImg_80.getChannels(), thresholdedImg_80.getImageData(), thresholdedImg_80.getWidth() * thresholdedImg_80.getChannels());

    // 4.2 tienshan_HSL_127.png
    const char* tienshanOutputImagePath_HSL_127 = "./Output/4-threshold/tienshan_HSL_127.png";
    unsigned char threshold_HSL_127 = 127; // Apply threshold filter with threshold value of 127
    Image thresholdedImg_HSL_127 = ColorFilter::thresholdImage(tienshanImg, threshold_HSL_127, "HSL");
    thresholdedImg_HSL_127.displayImageInfo();
    stbi_write_png(tienshanOutputImagePath_HSL_127, thresholdedImg_HSL_127.getWidth(), thresholdedImg_HSL_127.getHeight(), thresholdedImg_HSL_127.getChannels(), thresholdedImg_HSL_127.getImageData(), thresholdedImg_HSL_127.getWidth() * thresholdedImg_HSL_127.getChannels());

    // 4.3 tienshan_HSV_127.png
    const char* tienshanOutputImagePath_HSV_127 = "./Output/4-threshold/tienshan_HSV_127.png";
    unsigned char threshold_HSV_127 = 127; // Apply threshold filter with threshold value of 127
    Image thresholdedImg_HSV_127 = ColorFilter::thresholdImage(tienshanImg, threshold_HSV_127, "HSV");
    thresholdedImg_HSV_127.displayImageInfo();
    stbi_write_png(tienshanOutputImagePath_HSV_127, thresholdedImg_HSV_127.getWidth(), thresholdedImg_HSV_127.getHeight(), thresholdedImg_HSV_127.getChannels(), thresholdedImg_HSV_127.getImageData(),thresholdedImg_HSV_127.getWidth() * thresholdedImg_HSV_127.getChannels());

    // 4.4 vh_ct_80.png
    const char* vhCtOutputImagePath_80 = "./Output/4-threshold/vh_ct_80.png";
    unsigned char threshold_vhCt_80 = 80; // Apply threshold filter with threshold value of 80
    Image thresholdedImg_vhCt_80 = ColorFilter::thresholdImage(vhCtImg, threshold_vhCt_80, "RGB");
    thresholdedImg_vhCt_80.displayImageInfo();
    stbi_write_png(vhCtOutputImagePath_80, thresholdedImg_vhCt_80.getWidth(), thresholdedImg_vhCt_80.getHeight(), thresholdedImg_vhCt_80.getChannels(), thresholdedImg_vhCt_80.getImageData(), thresholdedImg_vhCt_80.getWidth() * thresholdedImg_vhCt_80.getChannels());

// |-- 5-saltandpepper
// |   |-- gracehopper_10.png         # 10% salt and pepper noise
// |   |-- gracehopper_25.png         # 25% salt and pepper noise
// |   |-- stinkbug_10.png            # 10% salt and pepper noise
// |   |-- stinkbug_40.png            # 40% salt and pepper noise

    // 5.1 gracehopper_10.png
    const char* gracehopperOutputImagePath_10 = "./Output/5-saltandpepper/gracehopper_10.png";
    float noisePercent_10 = 0.10; // Add noise to 10% of pixels
    Image noisyImg_gracehopper_10 = ColorFilter::addSaltAndPepperNoise(gracehopperImg, noisePercent_10);
    noisyImg_gracehopper_10.displayImageInfo();
    stbi_write_png(gracehopperOutputImagePath_10, noisyImg_gracehopper_10.getWidth(), noisyImg_gracehopper_10.getHeight(), noisyImg_gracehopper_10.getChannels(), noisyImg_gracehopper_10.getImageData(), noisyImg_gracehopper_10.getWidth() * noisyImg_gracehopper_10.getChannels());

    // 5.2 gracehopper_25.png
    const char* gracehopperOutputImagePath_25 = "./Output/5-saltandpepper/gracehopper_25.png";
    float noisePercent_25 = 0.25; // Add noise to 25% of pixels
    Image noisyImg_gracehopper_25 = ColorFilter::addSaltAndPepperNoise(gracehopperImg, noisePercent_25);
    noisyImg_gracehopper_25.displayImageInfo();
    stbi_write_png(gracehopperOutputImagePath_25, noisyImg_gracehopper_25.getWidth(), noisyImg_gracehopper_25.getHeight(), noisyImg_gracehopper_25.getChannels(), noisyImg_gracehopper_25.getImageData(), noisyImg_gracehopper_25.getWidth() * noisyImg_gracehopper_25.getChannels());

    // 5.3 stinkbug_10.png
    const char* stinkbugOutputImagePath_10 = "./Output/5-saltandpepper/stinkbug_10.png";
    float noisePercent_stinkbug_10 = 0.10; // Add noise to 10% of pixels
    Image noisyImg_stinkbug_10 = ColorFilter::addSaltAndPepperNoise(stinkbugImg, noisePercent_stinkbug_10);
    noisyImg_stinkbug_10.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_10, noisyImg_stinkbug_10.getWidth(), noisyImg_stinkbug_10.getHeight(), noisyImg_stinkbug_10.getChannels(), noisyImg_stinkbug_10.getImageData(), noisyImg_stinkbug_10.getWidth() * noisyImg_stinkbug_10.getChannels());

    // // 5.4 stinkbug_40.png
    const char* stinkbugOutputImagePath_40 = "./Output/5-saltandpepper/stinkbug_40.png";
    float noisePercent_stinkbug_40 = 0.40; // Add noise to 40% of pixels
    Image noisyImg_stinkbug_40 = ColorFilter::addSaltAndPepperNoise(stinkbugImg, 0.40);
    noisyImg_stinkbug_40.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_40, noisyImg_stinkbug_40.getWidth(), noisyImg_stinkbug_40.getHeight(), noisyImg_stinkbug_40.getChannels(), noisyImg_stinkbug_40.getImageData(), noisyImg_stinkbug_40.getWidth()* noisyImg_stinkbug_40.getWidth());

//     |-- 6-blur
// |   |-- box
// |   |   |-- stinkbug_3x3.png       # 3x3 box filter
// |   |   |-- stinkbug_5x5.png       # 5x5 box filter
// |   |   |-- tienshan_3x3.png       
// |   |   |-- tienshan_5x5.png
// |   |   |-- vh_anatomy_sp15_3x3.png
// |   |   `-- vh_anatomy_sp15_5x5.png
// |   |-- gaussian
// |   |   |-- stinkbug_3x3.png       # 3x3 gaussian filter
// |   |   |-- stinkbug_5x5.png       # 5x5 gaussian filter
// |   |   |-- tienshan_3x3.png
// |   |   |-- tienshan_5x5.png
// |   |   |-- vh_anatomy_sp15_3x3.png
// |   |   `-- vh_anatomy_sp15_5x5.png
// |   |-- median
// |       |-- stinkbug_3x3.png       # 3x3 median filter
// |       |-- stinkbug_5x5.png       # 5x5 median filter
// |       |-- tienshan_3x3.png
// |       |-- tienshan_5x5.png
// |       |-- vh_anatomy_sp15_3x3.png
// |       `-- vh_anatomy_sp15_5x5.png

    // 6.1.1 stinkbug_3x3.png
    const char* stinkbugOutputImagePath_box_3x3 = "./Output/6-blur/box/stinkbug_3x3.png";
    Image blurredImg_stinkbug_box_3x3 = BlurFilter::boxBlur(stinkbugImg, 3);
    blurredImg_stinkbug_box_3x3.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_box_3x3, blurredImg_stinkbug_box_3x3.getWidth(), blurredImg_stinkbug_box_3x3.getHeight(), blurredImg_stinkbug_box_3x3.getChannels(), blurredImg_stinkbug_box_3x3.getImageData(), blurredImg_stinkbug_box_3x3.getWidth() * blurredImg_stinkbug_box_3x3.getChannels());

    // 6.1.2 stinkbug_5x5.png
    const char* stinkbugOutputImagePath_box_5x5 = "./Output/6-blur/box/stinkbug_5x5.png";
    Image blurredImg_stinkbug_box_5x5 = BlurFilter::boxBlur(stinkbugImg, 5);
    blurredImg_stinkbug_box_5x5.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_box_5x5, blurredImg_stinkbug_box_5x5.getWidth(), blurredImg_stinkbug_box_5x5.getHeight(), blurredImg_stinkbug_box_5x5.getChannels(), blurredImg_stinkbug_box_5x5.getImageData(), blurredImg_stinkbug_box_5x5.getWidth() * blurredImg_stinkbug_box_5x5.getChannels());

    // 6.1.3 tienshan_3x3.png
    const char* tienshanOutputImagePath_box_3x3 = "./Output/6-blur/box/tienshan_3x3.png";
    tienshanImg.displayImageInfo();
    Image blurredImg_tienshan_box_3x3 = BlurFilter::boxBlur(tienshanImg, 3);
    blurredImg_tienshan_box_3x3.displayImageInfo();
    stbi_write_png(tienshanOutputImagePath_box_3x3, blurredImg_tienshan_box_3x3.getWidth(), blurredImg_tienshan_box_3x3.getHeight(), blurredImg_tienshan_box_3x3.getChannels(), blurredImg_tienshan_box_3x3.getImageData(), blurredImg_tienshan_box_3x3.getWidth() * blurredImg_tienshan_box_3x3.getChannels());

    // 6.1.4 tienshan_5x5.png
    const char* tienshanOutputImagePath_box_5x5 = "./Output/6-blur/box/tienshan_5x5.png";
    Image blurredImg_tienshan_box_5x5 = BlurFilter::boxBlur(tienshanImg, 5);
    blurredImg_tienshan_box_5x5.displayImageInfo();
    stbi_write_png(tienshanOutputImagePath_box_5x5, blurredImg_tienshan_box_5x5.getWidth(), blurredImg_tienshan_box_5x5.getHeight(), blurredImg_tienshan_box_5x5.getChannels(), blurredImg_tienshan_box_5x5.getImageData(), blurredImg_tienshan_box_5x5.getWidth() * blurredImg_tienshan_box_5x5.getChannels());

    // 6.1.5 vh_anatomy_sp15_3x3.png
    const char* vh_anatomyOutputImagePath_box_3x3 = "./Output/6-blur/box/vh_anatomy_sp15_3x3.png";
    Image blurredImg_vhAnatomy_box_3x3 = BlurFilter::boxBlur(vhAnatomySp15Img, 3);
    blurredImg_vhAnatomy_box_3x3.displayImageInfo();
    stbi_write_png(vh_anatomyOutputImagePath_box_3x3, blurredImg_vhAnatomy_box_3x3.getWidth(), blurredImg_vhAnatomy_box_3x3.getHeight(), blurredImg_vhAnatomy_box_3x3.getChannels(), blurredImg_vhAnatomy_box_3x3.getImageData(),  blurredImg_vhAnatomy_box_3x3.getWidth() * blurredImg_vhAnatomy_box_3x3.getChannels());

    // 6.1.6 vh_anatomy_sp15_5x5.png
    const char* vhAnatomyOutputImagePath_box_5x5 = "./Output/6-blur/box/vh_anatomy_sp15_5x5.png";
    Image blurredImg_vhAnatomy_box_5x5 = BlurFilter::boxBlur(vhAnatomySp15Img, 5);
    blurredImg_vhAnatomy_box_5x5.displayImageInfo();
    stbi_write_png(vhAnatomyOutputImagePath_box_5x5, blurredImg_vhAnatomy_box_5x5.getWidth(), blurredImg_vhAnatomy_box_5x5.getHeight(), blurredImg_vhAnatomy_box_5x5.getChannels(), blurredImg_vhAnatomy_box_5x5.getImageData(), blurredImg_vhAnatomy_box_5x5.getWidth() * blurredImg_vhAnatomy_box_5x5.getChannels());

    // 6.2.1 stinkbug_3x3.png
    const char* stinkbugOutputImagePath_gaussian_3x3 = "./Output/6-blur/gaussian/stinkbug_3x3.png";
    Image blurredImg_stinkbug_gaussian_3x3 = BlurFilter::gaussianBlur(stinkbugImg, 3, 1.0);
    blurredImg_stinkbug_gaussian_3x3.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_gaussian_3x3, blurredImg_stinkbug_gaussian_3x3.getWidth(), blurredImg_stinkbug_gaussian_3x3.getHeight(), blurredImg_stinkbug_gaussian_3x3.getChannels(), blurredImg_stinkbug_gaussian_3x3.getImageData(), blurredImg_stinkbug_box_3x3.getWidth() * blurredImg_stinkbug_box_3x3.getChannels());

    // 6.2.2 stinkbug_5x5.png
    const char* stinkbugOutputImagePath_gaussian_5x5 = "./Output/6-blur/gaussian/stinkbug_5x5.png";
    Image blurredImg_stinkbug_gaussian_5x5 = BlurFilter::gaussianBlur(stinkbugImg, 5, 2.0);
    blurredImg_stinkbug_gaussian_5x5.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_gaussian_5x5, blurredImg_stinkbug_gaussian_5x5.getWidth(), blurredImg_stinkbug_gaussian_5x5.getHeight(), blurredImg_stinkbug_gaussian_5x5.getChannels(), blurredImg_stinkbug_gaussian_5x5.getImageData(), blurredImg_stinkbug_gaussian_5x5.getWidth() * blurredImg_stinkbug_gaussian_5x5.getChannels());
    
    // 6.2.3 tienshan_3x3.png
    const char* tienshanOutputImagePath_gaussian_3x3 = "./Output/6-blur/gaussian/tienshan_3x3.png";
    Image blurredImg_tienshan_gaussian_3x3 = BlurFilter::gaussianBlur(tienshanImg, 3, 2.0);
    blurredImg_tienshan_gaussian_3x3.displayImageInfo();
    stbi_write_png(tienshanOutputImagePath_gaussian_3x3, blurredImg_tienshan_gaussian_3x3.getWidth(), blurredImg_tienshan_gaussian_3x3.getHeight(), blurredImg_tienshan_gaussian_3x3.getChannels(), blurredImg_tienshan_gaussian_3x3.getImageData(), blurredImg_tienshan_box_3x3.getWidth() * blurredImg_tienshan_box_3x3.getChannels());
    
    // 6.2.4 tienshan_5x5.png
    const char* tienshanOutputImagePath_gaussian_5x5 = "./Output/6-blur/gaussian/tienshan_5x5.png";
    Image blurredImg_tienshan_gaussian_5x5 = BlurFilter::gaussianBlur(tienshanImg, 5, 2.0);
    blurredImg_tienshan_gaussian_5x5.displayImageInfo();
    stbi_write_png(tienshanOutputImagePath_gaussian_5x5, blurredImg_tienshan_gaussian_5x5.getWidth(), blurredImg_tienshan_gaussian_5x5.getHeight(), blurredImg_tienshan_gaussian_5x5.getChannels(), blurredImg_tienshan_gaussian_5x5.getImageData(), blurredImg_tienshan_box_5x5.getWidth() * blurredImg_tienshan_box_5x5.getChannels());

    // 6.2.5 vh_anatomy_sp15_3x3.png
    const char* vhAnatomyOutputImagePath_gaussian_3x3 = "./Output/6-blur/gaussian/vh_anatomy_sp15_3x3.png";
    Image blurredImg_vhAnatomy_gaussian_3x3 = BlurFilter::gaussianBlur(vhAnatomySp15Img, 3, 1.0);
    blurredImg_vhAnatomy_gaussian_3x3.displayImageInfo();
    stbi_write_png(vhAnatomyOutputImagePath_gaussian_3x3, blurredImg_vhAnatomy_gaussian_3x3.getWidth(), blurredImg_vhAnatomy_gaussian_3x3.getHeight(), blurredImg_vhAnatomy_gaussian_3x3.getChannels(), blurredImg_vhAnatomy_gaussian_3x3.getImageData(), blurredImg_vhAnatomy_box_3x3.getWidth() * blurredImg_vhAnatomy_box_3x3.getChannels());

    // 6.2.6 vh_anatomy_sp15_5x5.png
    const char* vhAnatomyOutputImagePath_gaussian_5x5 = "./Output/6-blur/gaussian/vh_anatomy_sp15_5x5.png";
    Image blurredImg_vhAnatomy_gaussian_5x5 = BlurFilter::gaussianBlur(vhAnatomySp15Img, 5, 2.0);
    blurredImg_vhAnatomy_gaussian_5x5.displayImageInfo();
    stbi_write_png(vhAnatomyOutputImagePath_gaussian_5x5, blurredImg_vhAnatomy_gaussian_5x5.getWidth(), blurredImg_vhAnatomy_gaussian_5x5.getHeight(), blurredImg_vhAnatomy_gaussian_5x5.getChannels(), blurredImg_vhAnatomy_gaussian_5x5.getImageData(), blurredImg_vhAnatomy_box_5x5.getWidth() * blurredImg_vhAnatomy_box_5x5.getChannels());
    
    // 6.3.1 stinkbug_3x3.png
    const char* stinkbugOutputImagePath_median_3x3 = "./Output/6-blur/median/stinkbug_3x3.png";
    Image blurredImg_stinkbug_median_3x3 = BlurFilter::medianBlur(stinkbugImg, 3);
    blurredImg_stinkbug_median_3x3.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_median_3x3, blurredImg_stinkbug_median_3x3.getWidth(), blurredImg_stinkbug_median_3x3.getHeight(), blurredImg_stinkbug_median_3x3.getChannels(), blurredImg_stinkbug_median_3x3.getImageData(), blurredImg_stinkbug_box_3x3.getWidth() * blurredImg_stinkbug_box_3x3.getChannels());

    // 6.3.2 stinkbug_5x5.png
    const char* stinkbugOutputImagePath_median_5x5 = "./Output/6-blur/median/stinkbug_5x5.png";
    Image blurredImg_stinkbug_median_5x5 = BlurFilter::medianBlur(stinkbugImg, 5);
    blurredImg_stinkbug_median_5x5.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_median_5x5, blurredImg_stinkbug_median_5x5.getWidth(), blurredImg_stinkbug_median_5x5.getHeight(), blurredImg_stinkbug_median_5x5.getChannels(), blurredImg_stinkbug_median_5x5.getImageData(), blurredImg_stinkbug_box_5x5.getWidth() * blurredImg_stinkbug_box_5x5.getChannels());

    // 6.3.3 tienshan_3x3.png
    const char* tienshanOutputImagePath_median_3x3 = "./Output/6-blur/median/tienshan_3x3.png";
    Image blurredImg_tienshan_median_3x3 = BlurFilter::medianBlur(tienshanImg, 3);
    blurredImg_tienshan_median_3x3.displayImageInfo();
    stbi_write_png(tienshanOutputImagePath_median_3x3, blurredImg_tienshan_median_3x3.getWidth(), blurredImg_tienshan_median_3x3.getHeight(), blurredImg_tienshan_median_3x3.getChannels(), blurredImg_tienshan_median_3x3.getImageData(), blurredImg_tienshan_box_3x3.getWidth() * blurredImg_tienshan_box_3x3.getChannels());
    
    // 6.3.4 tienshan_5x5.png
    const char* tienshanOutputImagePath_median_5x5 = "./Output/6-blur/median/tienshan_5x5.png";
    Image blurredImg_tienshan_median_5x5 = BlurFilter::medianBlur(tienshanImg, 5);
    blurredImg_tienshan_median_5x5.displayImageInfo();
    stbi_write_png(tienshanOutputImagePath_median_5x5, blurredImg_tienshan_median_5x5.getWidth(), blurredImg_tienshan_median_5x5.getHeight(), blurredImg_tienshan_median_5x5.getChannels(), blurredImg_tienshan_median_5x5.getImageData(), blurredImg_tienshan_box_5x5.getWidth() * blurredImg_tienshan_box_5x5.getChannels());

    // 6.3.5 vh_anatomy_sp15_3x3.png
    const char* vhAnatomyOutputImagePath_median_3x3 = "./Output/6-blur/median/vh_anatomy_sp15_3x3.png";
    Image blurredImg_vhAnatomy_median_3x3 = BlurFilter::medianBlur(vhAnatomySp15Img, 3);
    blurredImg_vhAnatomy_median_3x3.displayImageInfo();
    stbi_write_png(vhAnatomyOutputImagePath_median_3x3, blurredImg_vhAnatomy_median_3x3.getWidth(), blurredImg_vhAnatomy_median_3x3.getHeight(), blurredImg_vhAnatomy_median_3x3.getChannels(), blurredImg_vhAnatomy_median_3x3.getImageData(), vhAnatomyWidth * vhAnatomyChannels);

    // 6.3.6 vh_anatomy_sp15_5x5.png
    const char* vhAnatomyOutputImagePath_median_5x5 = "./Output/6-blur/median/vh_anatomy_sp15_5x5.png";
    Image blurredImg_vhAnatomy_median_5x5 = BlurFilter::medianBlur(vhAnatomySp15Img, 5);
    blurredImg_vhAnatomy_median_5x5.displayImageInfo();
    stbi_write_png(vhAnatomyOutputImagePath_median_5x5, blurredImg_vhAnatomy_median_5x5.getWidth(), blurredImg_vhAnatomy_median_5x5.getHeight(), blurredImg_vhAnatomy_median_5x5.getChannels(), blurredImg_vhAnatomy_median_5x5.getImageData(), vhAnatomyWidth * vhAnatomyChannels);

//     |-- 7-edgedetection
// |   |-- prewitt
// |   |   |-- dimorphos.png
// |   |   |-- gracehopper.png
// |   |   |-- stinkbug.png
// |   |   |-- tienshan.png
// |   |   |-- vh_anatomy.png
// |   |   |-- vh_ct.png
// |   |-- robertscross
// |   |   |-- dimorphos.png
// |   |   |-- gracehopper.png
// |   |   |-- stinkbug.png
// |   |   |-- tienshan.png
// |   |   |-- vh_anatomy.png
// |   |   |-- vh_ct.png
// |   |-- scharr
// |   |   |-- dimorphos.png
// |   |   |-- gracehopper.png
// |   |   |-- stinkbug.png
// |   |   |-- tienshan.png
// |   |   |-- vh_anatomy.png
// |   |   |-- vh_ct.png
// |   |-- sobel
// |       |-- dimorphos.png
// |       |-- gracehopper.png
// |       |-- stinkbug.png
// |       |-- tienshan.png
// |       |-- vh_anatomy.png
// |       |-- vh_ct.png

    // 7.1.1 dimorphos.png
    const char* dimorphosOutputImagePath_prewitt = "./Output/7-edgedetection/prewitt/dimorphos.png";
    dimorphosImg.displayImageInfo();
    Image prewittImg_dimorphos = EdgeDetector::applyPrewitt(dimorphosImg);
    prewittImg_dimorphos.displayImageInfo();
    stbi_write_png(dimorphosOutputImagePath_prewitt, prewittImg_dimorphos.getWidth(), prewittImg_dimorphos.getHeight(), prewittImg_dimorphos.getChannels(), prewittImg_dimorphos.getImageData(), prewittImg_dimorphos.getWidth() * prewittImg_dimorphos.getChannels());

    // 7.1.2 gracehopper.png
    const char* gracehopperOutputImagePath_prewitt = "./Output/7-edgedetection/prewitt/gracehopper.png";
    Image prewittImg_gracehopper = EdgeDetector::applyPrewitt(gracehopperImg);
    prewittImg_gracehopper.displayImageInfo();
    stbi_write_png(gracehopperOutputImagePath_prewitt, prewittImg_gracehopper.getWidth(), prewittImg_gracehopper.getHeight(), prewittImg_gracehopper.getChannels(), prewittImg_gracehopper.getImageData(), prewittImg_gracehopper.getWidth() * prewittImg_gracehopper.getChannels());

    // 7.1.3 stinkbug.png
    const char* stinkbugOutputImagePath_prewitt = "./Output/7-edgedetection/prewitt/stinkbug.png";
    Image prewittImg_stinkbug = EdgeDetector::applyPrewitt(stinkbugImg);
    prewittImg_stinkbug.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_prewitt, prewittImg_stinkbug.getWidth(), prewittImg_stinkbug.getHeight(), prewittImg_stinkbug.getChannels(), prewittImg_stinkbug.getImageData(), prewittImg_stinkbug.getWidth() * prewittImg_stinkbug.getChannels());

    // 7.1.4 tienshan.png
    const char* tienshanOutputImagePath_prewitt = "./Output/7-edgedetection/prewitt/tienshan.png";
    Image prewittImg_tienshan = EdgeDetector::applyPrewitt(tienshanImg);
    prewittImg_tienshan.displayImageInfo();
    stbi_write_png(tienshanOutputImagePath_prewitt, prewittImg_tienshan.getWidth(), prewittImg_tienshan.getHeight(), prewittImg_tienshan.getChannels(), prewittImg_tienshan.getImageData(), prewittImg_tienshan.getWidth() * prewittImg_tienshan.getChannels());

    // 7.1.5 vh_anatomy.png
    const char* vhAnatomyOutputImagePath_prewitt = "./Output/7-edgedetection/prewitt/vh_anatomy.png";
    Image prewittImg_vhAnatomy = EdgeDetector::applyPrewitt(vhAnatomyImg);
    prewittImg_vhAnatomy.displayImageInfo();
    stbi_write_png(vhAnatomyOutputImagePath_prewitt, prewittImg_vhAnatomy.getWidth(), prewittImg_vhAnatomy.getHeight(), prewittImg_vhAnatomy.getChannels(), prewittImg_vhAnatomy.getImageData(), vhAnatomyWidth);

    // 7.1.6 vh_ct.png
    const char* vhCtOutputImagePath_prewitt = "./Output/7-edgedetection/prewitt/vh_ct.png";
    Image prewittImg_vhCt = EdgeDetector::applyPrewitt(vhCtImg);
    prewittImg_vhCt.displayImageInfo();
    stbi_write_png(vhCtOutputImagePath_prewitt, prewittImg_vhCt.getWidth(), prewittImg_vhCt.getHeight(), prewittImg_vhCt.getChannels(), prewittImg_vhCt.getImageData(), vhCtWidth * vhCtChannels);


    // 7.2.1 dimorphos.png
    const char* dimorphosOutputImagePath_robertscross = "./Output/7-edgedetection/robertscross/dimorphos.png";
    Image robertsCrossImg_dimorphos = EdgeDetector::applyRobertsCross(dimorphosImg);
    robertsCrossImg_dimorphos.displayImageInfo();
    stbi_write_png(dimorphosOutputImagePath_robertscross, robertsCrossImg_dimorphos.getWidth(), robertsCrossImg_dimorphos.getHeight(), robertsCrossImg_dimorphos.getChannels(), robertsCrossImg_dimorphos.getImageData(), robertsCrossImg_dimorphos.getWidth() * robertsCrossImg_dimorphos.getChannels());

    // 7.2.2 gracehopper.png
    const char* gracehopperOutputImagePath_robertscross = "./Output/7-edgedetection/robertscross/gracehopper.png";
    Image robertsCrossImg_gracehopper = EdgeDetector::applyRobertsCross(gracehopperImg);
    robertsCrossImg_gracehopper.displayImageInfo();
    stbi_write_png(gracehopperOutputImagePath_robertscross, robertsCrossImg_gracehopper.getWidth(), robertsCrossImg_gracehopper.getHeight(), robertsCrossImg_gracehopper.getChannels(), robertsCrossImg_gracehopper.getImageData(), robertsCrossImg_gracehopper.getWidth() * robertsCrossImg_gracehopper.getChannels());


    // 7.2.3 stinkbug.png
    const char* stinkbugOutputImagePath_robertscross = "./Output/7-edgedetection/robertscross/stinkbug.png";
    Image robertsCrossImg_stinkbug = EdgeDetector::applyRobertsCross(stinkbugImg);
    robertsCrossImg_stinkbug.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_robertscross, robertsCrossImg_stinkbug.getWidth(), robertsCrossImg_stinkbug.getHeight(), robertsCrossImg_stinkbug.getChannels(), robertsCrossImg_stinkbug.getImageData(), robertsCrossImg_stinkbug.getWidth() * robertsCrossImg_stinkbug.getChannels());


    // 7.2.4 tienshan.png
    const char* tienshanOutputImagePath_robertscross = "./Output/7-edgedetection/robertscross/tienshan.png";
    Image robertsCrossImg_tienshan = EdgeDetector::applyRobertsCross(tienshanImg);
    robertsCrossImg_tienshan.displayImageInfo();
    stbi_write_png(tienshanOutputImagePath_robertscross, robertsCrossImg_tienshan.getWidth(), robertsCrossImg_tienshan.getHeight(), robertsCrossImg_tienshan.getChannels(), robertsCrossImg_tienshan.getImageData(), robertsCrossImg_tienshan.getWidth() * robertsCrossImg_tienshan.getChannels());


    // 7.2.5 vh_anatomy.png
    const char* vhAnatomyOutputImagePath_robertscross = "./Output/7-edgedetection/robertscross/vh_anatomy.png";
    Image robertsCrossImg_vhAnatomy = EdgeDetector::applyRobertsCross(vhAnatomyImg);
    robertsCrossImg_vhAnatomy.displayImageInfo();
    stbi_write_png(vhAnatomyOutputImagePath_robertscross, robertsCrossImg_vhAnatomy.getWidth(), robertsCrossImg_vhAnatomy.getHeight(), robertsCrossImg_vhAnatomy.getChannels(), robertsCrossImg_vhAnatomy.getImageData(), robertsCrossImg_vhAnatomy.getWidth() * robertsCrossImg_vhAnatomy.getChannels());


    // 7.2.6 vh_ct.png
    const char* vhCtOutputImagePath_robertscross = "./Output/7-edgedetection/robertscross/vh_ct.png";
    Image robertsCrossImg_vhCt = EdgeDetector::applyRobertsCross(vhCtImg);
    robertsCrossImg_vhCt.displayImageInfo();
    stbi_write_png(vhCtOutputImagePath_robertscross, robertsCrossImg_vhCt.getWidth(), robertsCrossImg_vhCt.getHeight(), robertsCrossImg_vhCt.getChannels(), robertsCrossImg_vhCt.getImageData(), robertsCrossImg_vhCt.getWidth() * robertsCrossImg_vhCt.getChannels());

    // 7.3.1 dimorphos.png
    const char* dimorphosOutputImagePath_scharr = "./Output/7-edgedetection/scharr/dimorphos.png";
    Image scharrImg_dimorphos = EdgeDetector::applyScharr(dimorphosImg);
    scharrImg_dimorphos.displayImageInfo();
    stbi_write_png(dimorphosOutputImagePath_scharr, scharrImg_dimorphos.getWidth(), scharrImg_dimorphos.getHeight(), scharrImg_dimorphos.getChannels(), scharrImg_dimorphos.getImageData(), scharrImg_dimorphos.getWidth() * scharrImg_dimorphos.getChannels());


    // 7.3.2 gracehopper.png
    const char* gracehopperOutputImagePath_scharr = "./Output/7-edgedetection/scharr/gracehopper.png";
    Image scharrImg_gracehopper = EdgeDetector::applyScharr(gracehopperImg);
    scharrImg_gracehopper.displayImageInfo();
    stbi_write_png(gracehopperOutputImagePath_scharr, scharrImg_gracehopper.getWidth(), scharrImg_gracehopper.getHeight(), scharrImg_gracehopper.getChannels(), scharrImg_gracehopper.getImageData(), scharrImg_gracehopper.getWidth() * scharrImg_gracehopper.getChannels());


    // 7.3.3 stinkbug.png
    const char* stinkbugOutputImagePath_scharr = "./Output/7-edgedetection/scharr/stinkbug.png";
    Image scharrImg_stinkbug = EdgeDetector::applyScharr(stinkbugImg);
    scharrImg_stinkbug.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_scharr, scharrImg_stinkbug.getWidth(), scharrImg_stinkbug.getHeight(), scharrImg_stinkbug.getChannels(), scharrImg_stinkbug.getImageData(), scharrImg_stinkbug.getWidth() * scharrImg_stinkbug.getChannels());


    // 7.3.4 tienshan.png
    const char* tienshanOutputImagePath_scharr = "./Output/7-edgedetection/scharr/tienshan.png";
    Image scharrImg_tienshan = EdgeDetector::applyScharr(tienshanImg);
    scharrImg_tienshan.displayImageInfo();
    stbi_write_png(tienshanOutputImagePath_scharr, scharrImg_tienshan.getWidth(), scharrImg_tienshan.getHeight(), scharrImg_tienshan.getChannels(), scharrImg_tienshan.getImageData(), scharrImg_tienshan.getWidth() * scharrImg_tienshan.getChannels());

    // 7.3.5 vh_anatomy.png
    const char* vhAnatomyOutputImagePath_scharr = "./Output/7-edgedetection/scharr/vh_anatomy.png";
    Image scharrImg_vhAnatomy = EdgeDetector::applyScharr(vhAnatomyImg);
    scharrImg_vhAnatomy.displayImageInfo();
    stbi_write_png(vhAnatomyOutputImagePath_scharr, scharrImg_vhAnatomy.getWidth(), scharrImg_vhAnatomy.getHeight(), scharrImg_vhAnatomy.getChannels(), scharrImg_vhAnatomy.getImageData(), scharrImg_vhAnatomy.getWidth() * scharrImg_vhAnatomy.getChannels());
    

    // 7.3.6 vh_ct.png
    const char* vhCtOutputImagePath_scharr = "./Output/7-edgedetection/scharr/vh_ct.png";
    Image scharrImg_vhCt = EdgeDetector::applyScharr(vhCtImg);
    scharrImg_vhCt.displayImageInfo();
    stbi_write_png(vhCtOutputImagePath_scharr, scharrImg_vhCt.getWidth(), scharrImg_vhCt.getHeight(), scharrImg_vhCt.getChannels(), scharrImg_vhCt.getImageData(), scharrImg_vhCt.getWidth() * scharrImg_vhCt.getChannels());

    // 7.4.1 dimorphos.png
    const char* dimorphosOutputImagePath_sobel = "./Output/7-edgedetection/sobel/dimorphos.png";
    Image sobelImg_dimorphos = EdgeDetector::applySobel(dimorphosImg);
    sobelImg_dimorphos.displayImageInfo();
    stbi_write_png(dimorphosOutputImagePath_sobel, sobelImg_dimorphos.getWidth(), sobelImg_dimorphos.getHeight(), sobelImg_dimorphos.getChannels(), sobelImg_dimorphos.getImageData(), sobelImg_dimorphos.getWidth() * sobelImg_dimorphos.getChannels());


    // 7.4.2 gracehopper.png
    const char* gracehopperOutputImagePath_sobel = "./Output/7-edgedetection/sobel/gracehopper.png";
    Image sobelImg_gracehopper = EdgeDetector::applySobel(gracehopperImg);
    sobelImg_gracehopper.displayImageInfo();
    stbi_write_png(gracehopperOutputImagePath_sobel, sobelImg_gracehopper.getWidth(), sobelImg_gracehopper.getHeight(), sobelImg_gracehopper.getChannels(), sobelImg_gracehopper.getImageData(), sobelImg_gracehopper.getWidth() * sobelImg_gracehopper.getChannels());


    // 7.4.3 stinkbug.png
    const char* stinkbugOutputImagePath_sobel = "./Output/7-edgedetection/sobel/stinkbug.png";
    Image sobelImg_stinkbug = EdgeDetector::applySobel(stinkbugImg);
    sobelImg_stinkbug.displayImageInfo();
    stbi_write_png(stinkbugOutputImagePath_sobel, sobelImg_stinkbug.getWidth(), sobelImg_stinkbug.getHeight(), sobelImg_stinkbug.getChannels(), sobelImg_stinkbug.getImageData(), sobelImg_stinkbug.getWidth() * sobelImg_stinkbug.getChannels());


    // 7.4.4 tienshan.png
    const char* tienshanOutputImagePath_sobel = "./Output/7-edgedetection/sobel/tienshan.png";
    Image sobelImg_tienshan = EdgeDetector::applySobel(tienshanImg);
    sobelImg_tienshan.displayImageInfo();
    stbi_write_png(tienshanOutputImagePath_sobel, sobelImg_tienshan.getWidth(), sobelImg_tienshan.getHeight(), sobelImg_tienshan.getChannels(), sobelImg_tienshan.getImageData(), sobelImg_tienshan.getWidth() * sobelImg_tienshan.getChannels());


    // 7.4.5 vh_anatomy.png
    const char* vhAnatomyOutputImagePath_sobel = "./Output/7-edgedetection/sobel/vh_anatomy.png";
    Image sobelImg_vhAnatomy = EdgeDetector::applySobel(vhAnatomyImg);
    sobelImg_vhAnatomy.displayImageInfo();
    stbi_write_png(vhAnatomyOutputImagePath_sobel, sobelImg_vhAnatomy.getWidth(), sobelImg_vhAnatomy.getHeight(), sobelImg_vhAnatomy.getChannels(), sobelImg_vhAnatomy.getImageData(), sobelImg_vhAnatomy.getWidth() * sobelImg_vhAnatomy.getChannels());


    // 7.4.6 vh_ct.png
    const char* vhCtOutputImagePath_sobel = "./Output/7-edgedetection/sobel/vh_ct.png";
    Image sobelImg_vhCt = EdgeDetector::applySobel(vhCtImg);
    sobelImg_vhCt.displayImageInfo();
    stbi_write_png(vhCtOutputImagePath_sobel, sobelImg_vhCt.getWidth(), sobelImg_vhCt.getHeight(), sobelImg_vhCt.getChannels(), sobelImg_vhCt.getImageData(), sobelImg_vhCt.getWidth() * sobelImg_vhCt.getChannels());

    return 0;
}

// g++-13 src/outputs_2D_filters.cpp src/image.cpp src/ColorFilter.cpp src/BlurFilter.cpp src/EdgeDetector.cpp -o outputs_2D_filters && ./outputs_2D_filters