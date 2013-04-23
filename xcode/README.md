Any questions should be asked to walidvb@gmail.com

Instructions:
    Plug the cam
    Press enter when the chessboard is in view to start scanning
    Use the mouse to select the darkest area of the surface, and then the brightest(do it either before scanning stops or once the white image has been displayed and captured)
    Press r for new scan
    Press v to switch to video
    Press o to switch image
    Press c to toggle original/compensated image
    Press f to toggle fullscreen
    Press d to toggle the GUI

Architecture:
    RDCApp          : contains the main, sets the GUI up, and requests an image to be compensated
    Controller      : contains the logic, and holds the instances of Sensor, RDC, and some methods to bring RDC attributes up to the GUI
    Sensor          : can either be a camera, or a media
    RDC             : the algorithm itself, processes and updates an image
    Timer           : the timer
    Renderer_A      : abstract class used for rendering(only used for the scanning, further rendering is done by the external caller)
    Image           : encapsulator of cv::Mat
    Homo            : internal class handling the homography
    ColorCalibrator : handles the color calibration. completely unused for the moment, color calib logic is not yet implemented
    CalibController :
    CameraCalibrator: computes the calibration parameters to correct lens distortion. Implemented but not integrated in the program. Current method is based on showing the camera multiple physical prints of a chessboard, which isn't possible for now.

Further comments:
    Resource path should be changed in the following files: RDC.cpp, RDCApp.cpp
    Chessboard size can be changed in Homo.cpp