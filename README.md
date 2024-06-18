
# Team Huffman: Advanced Image & 3D Data Processing Tool

Team Huffman has developed a cutting-edge, C++-based application designed for sophisticated image and 3D data volume processing. It integrates a range of filters, projections, and slicing techniques to provide users with the capabilities to enhance, analyse, and transform both 2D images and 3D data volumes.

## Features

- **2D Image Processing**: Apply colour correction, brightness adjustments, histogram equalisation, thresholding, noise addition, and various blurring and edge detection techniques.
- **3D Data Volume Manipulation**: Includes Gaussian and median filters, orthographic projections (MIP, MinIP, AIP), and slicing through volumes to reveal internal structures.

### Possible Future Capabilities: 
- **Advanced Machine Learning Filters**: Future modifications will incorporate deep learning-based enhancements for denoising and super-resolution.
- **Parallel Processing & OMP Threading**: As we were restricted in not using parallel processing techniques, future adjustments would incorporate these for faster running times and handling larger data volumes efficiently.
- **Graphical User Interface (GUI)**: A more intuitive GUI would also aid in the application being more user-friendly and gear it for wider deployment.
- **Expanded Testing Framework**: Expanding our testing framework to include comprehensive automated tests will help us maintain code quality and performance.

## Getting Started
### Prerequisites

- C++ Compiler (C++17 or later recommended)
- No external libraries required, thanks to the use of standard libraries and custom implementations.

### Installation

1. Clone the repository:
```bash
git clone https://github.com/ese-msc-2023/advanced-programming-group-huffman.git
```

2. Navigate to the src directory:
```bash
cd src
```

3. Run the compiled code to use the interface:
```
./userinterface
```
Or you can compile and run directly the source code for the user interface:

```bash
g++ -std=c++17 src/userInterface.cpp src/Volume.cpp src/Projection.cpp src/ThreeDFilter.cpp src/Slice.cpp src/Image.cpp src/ColorFilter.cpp src/BlurFilter.cpp src/EdgeDetector.cpp -o src/userinterface && ./src/userinterface
```

## Usage

Upon launching, Visionary prompts the user to select between 2D image processing and 3D data volume manipulation. Users can then choose from the available filters or projections and specify any necessary parameters. The application processes the input data accordingly and outputs the result to a specified file. Here are some use cases for both 2D images and 3D volumes as examples:

### User Interface
The program functions with a simple and easy-to-use text-based interface which prompts user input at each step.

#### Example: 2D Image Processing  
1. First, the UI prompts the user to write the path of the input file:
```bash
Please enter the path to the input file: 
```
2. Then, write the path to the output file:
```bash
Please enter the path to save the output file: 
```
3. Choose between 2D and 3D processing mode:
```bash
Please select 1.2D 2.3D
```
4. For this 2D example, we would have written '1', which displays this list for 2D images:
```bash
Select a filter to apply to the image:
1. Grayscale
2. Adjust Brightness
3. Histogram Equalization
4. Thresholding
5. Salt and Pepper Noise
6. Image Blur  # Combined option for all blurs
7. Edge Detection
Enter your choice (1-7): 
```
5. We can choose to modify the brightness here by writing 2, and then input the adjustment value:
```bash
Enter brightness change value (-255 to 255):
```
6. Following the brightness adjustment, the UI will prompt for the name of the image to be saved, and then save the image at the specified path:
```bash
Please enter the file name you want to save with '.png' (for example: yourFileName.png)
```
```bash
Image saved successfully: [path/yourFileName.png]
```
7. There is now an option to continue applying more filters, or to quit the program:
```bash
Do you want to apply another filter? (yes/no):
```
8. For example, if yes is picked, then the initial filter menu would be redisplayed:
```bash
Select a filter to apply to the image:
1. Grayscale
2. Adjust Brightness
3. Histogram Equalization
4. Thresholding
5. Salt and Pepper Noise
6. Image Blur  # Combined option for all blurs
7. Edge Detection
Enter your choice (1-7): 
```
9. We can continue modifying the image by applying a blur filter and choosing 6, which displays the blur options menu:
```bash
Select type of blur to apply:
1. Box Blur
2. Gaussian Blur
3. Median Blur
Enter your choice (1-3):
```
10. Selecting any would prompt the user to enter the kernel size, but we will pick Gaussian Blur as option 2 in this case:
```bash
Enter kernel size (must be odd number):
```
11. As Gaussian Blur is chosen, a further sigma value is required:
```bash
Enter sigma value:
```
12. Following this, the selected blur filter will be applied and the user will be prompted again for the output image's name, and save the image again :
```bash
Please enter the file name you want to save with '.png' (for example: yourFileName.png)
```
```bash
Image saved successfully: [path/yourFileName.png]
```
13. The program will ask the user if they want to process more data, and selecting 'no' will exit.
```bash
Do you want to process another data? (yes/no)
```

Concluding this example, the image would be saved after a brightness filter and a gaussian blur filter with a specified kernel size and sigma have been applied. 

#### Example: 3D Data Volume Processing
1. First, the UI prompts the user to write the path of the input file:
```bash
Please enter the path to the input file: 
```
2. Then, write the path to the output file:
```bash
Please enter the path to save the output file: 
```
3. Choose between 2D and 3D processing mode:
```bash
Please select 1.2D 2.3D
```
4. For this 2D example, we would have written '2', which displays this list for 3D data volumes:
```bash
Please select the 3D filter: 1. Gaussian 2. Median 3. None
```
5. After selecting Median Blur, the program will prompt for the kernel size, and also notify when the blurring filter is applied.
```bash
Please enter the kernel size (3 or 5):
```
```bash
Applied 3D Median Blur with kernel size [kernel size]
```
6. The program will then prompt for any orthographic projections to be performed on the volume data:
```bash
Please select the projection method: 1. Maximum 2. Minimum 3. Average 4. None
```
7. In this case we select none and proceed to the slicing menu:
```bash
Select whether to slice: 1. Yes 2. No
```
8. If yes, the user will be prompted for the slicing ranges:
```bash
Please select the xz slice range:
```
```bash
Please select yz slice range:
```
9. The program will notify the user of success in saving the sliced data afterwards:
```bash
X-Z slice saved successfully.
Y-Z slice saved successfully.
```
10. Following this, the program will ask the user for any further files to be processed:
```bash
Do you want to process another data? (yes/no)
```

To conclude this example, the program will have applied a Median Blur filter with the specified kernel size and slicing ranges and saved the data at the specified output path.

## Testing 
Robust testing frameworks were developed to test each filter output independently. The tests for the filters are located in the 'test' directory. To run the tests, follow these instructions: 
```bash
1.  Open a terminal or command line interface.
```
```bash
2.  Navigate to the test folder.  You can do this by using the cd test command to enter the test directory.
```
```bash
3.  Execute the corresponding test executable.  For example, if you want to test the 2D filters, type . /2DSimpleFilter_test and press Enter to run the test program.
```
```bash
4.  The program will execute the respective tests and display the results in the terminal.
````
By following these steps, you can easily conduct testing and view the results.


## Contributing

We welcome contributions, including bug fixes, new features, and documentation improvements. Please reach out for any questions or suggestions. 

## License

This project is licensed under the MIT License - see the `LICENSE.txt` file for details.

## Acknowledgements

- An amazing team composed of:
  - Yuheng Chen (yuheng.chen23@imperial.ac.uk)
  - Francois Crespin (francois.crespin23@imperial.ac.uk)
  - Yixuan Jiang (yixuan.jiang23@imperial.ac.uk)
  - Atys Panier (atys.panier23@imperial.ac.uk)
  - Walid Sheikh (walid.sheikh23@imperial.ac.uk)
  - Xuan Zhan (xuan.zhan23@imperial.ac.uk)

- Our sincere thanks to the teaching staff in the Advanced Programming module for their guidance and support.

## References
Please see 'References.md'

