This package contains the golden simulator and test cases for ECE 449, Spring 2013.
Please unzip this package first before continuing.

-- Version 3.0 Jan.11, 2013
   Updated for Spring 2013

-- Version 2.0 Jan.5, 2012
   Updated for Spring 2012

-- Version 1.1 Feb.8, 2011
   Updated for Project 3/4

-----------------------------------------------------------------------------------
Here is the list of files:

- README.txt: this file

- EasyVL.exe: golden simulator for Windows

- EasyVL: golden simulator for compatible linux systems

- lfsr10.evl, s15850.evl, counter.evl, counter.evl.sim_in:
      test cases for the first four projects

- bonus/cpu8.evl, bonus/cpu8.program, bonus/tris_lut_assign.evl,
  bonus/tris_lut_assign.evl.rom:
      test cases for the bonus project

- other files: golden outputs

-----------------------------------------------------------------------------------
To run the golden simulator on Windows, you need to start a terminal window first.
This can be done by first clicking Run... from the Start menu to bring up the Run
dialog box and then starting the program 'cmd' from there. From within the terminal
window, please first type the disk label to switch to the disk you have extracted
the package to and then use the 'cd' command to change your current directory to
where you have upzipped the package. For example, if you have extracted the package
to d:\golden, you can type the following two commands:

d:
cd \golden

Then you can run the golden simulator as:

EasyVL

and follow the instructions.

-----------------------------------------------------------------------------------
To run the golden simulator on compatible linux systems, please refer to your system
menu or search online to bring up a terminal window (also known as a shell). Then
you can use the 'cd' command to change your current directory to where you have
extracted the package, e.g.,

cd /home/user/golden

You may need the following command to flag EasyVL as an executable:

chmod +x EasyVL

Then you can run the golden simulator as:

./EasyVL

and follow the instructions.

-----------------------------------------------------------------------------------
Please contact Prof. Jia Wang if you have any question.
