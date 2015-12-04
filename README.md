#################################### Project Introduction #############################################
This repo is half of the complete Simple Oscope project. The second half (the GUI portion) is located
at https://github.com/apolcyn/capstone_gui. This portion is the PSoC Creator project that controls the
PSoC. It functions as the interface to the physical world by taking in and outputting waveforms. The
following instructions assumes you have the latest version of PSoC Creator installed. You can download
the program at http://www.cypress.com/products/psoc-creator-integrated-design-environment-ide.

################################ Instructions for beginners ###########################################
After downloading/forking this repo and installing PSoC Creator, open the Simple_Oscope.cyprj file by
double clicking it in File Explorer or, in PSoC Creator, going to File -> Open -> Project/Workspace and
selecting Simple_Oscope.cyprj.

Once open the project files will populate on the left side in the Window Explorer, and there will be a
lot of files. Fortunately, most of the important information is kept within only a few of these files.
Most of the files are auto-generated and don't need to be manually configured. Here we will give a
basic breakdown of the most important files.

################################### File Descriptions #################################################
** TopDesign.cysch **
This file shows all of the hardware and software modules implemented in the project. It is great for
getting a visual idea of how everything is connected. For this project, the three main portions are
separated so that the purpose of each module is clear. The sections include:
UART Module        - Controls UART communication. Currently set to communicate through the USB port.
Waveform Generator - Outputs a user-defined waveform through the output pin.
Oscilloscope       - Reads waveform data and sends it out through UART in packets called frames.

** Simple_Oscope.cydwr **
Contains the pin-mapping for the project. The correct PSoC must be selected in the Device Selector
under the Project drop-down menu so that the appropriate available pins are shown.

** main.h **
This is the header file that contains all of the required definitions for main.c. Unless you absolutely
know what you are doing, it is advised that you only alter the default values or the DEBUG_OUTPUT
definition. However, keep in mind the default values must be kept within their respective valid range.
Reference the Packet Format document and respective datasheets for valid ranges.

** main.c **
This file runs the whole show. The main() function really only has two jobs: synchronize the PSoC with
the GUI and execute commands. The synchronization is self-explanatory, but the commands are a bit
involved. Simply put, the GUI tells the PSoC how to configure the Oscilloscope and Waveform Generator
modules and the PSoC sends the GUI Oscope data (when it is enabled). This file and functions that it
calls are well-documented so that you may be able to follow along and make changes if you wish.

############################### Thank you for your interest! ##########################################
