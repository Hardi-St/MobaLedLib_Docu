These are the steps to create a new beta release for MobaLedLib

Prerequisites:
- we have changed or new MobaLedLib library files

Steps:

1.) Check out or use already checked out branch https://github.com/Hardi-St/MobaLedLib/tree/beta

2.) Code files
- merge changes into Prog_Generator_MobaLedLib.xlsm. !!! never just copy a changed xlsm into the git beta folder !!!
- merge changes into Pattern_Configurator.xlsm.      !!! never just copy a changed xlsm into the git beta folder !!!
- merge changes of other files into the beta branch

3.) Prog_Generator_MobaLedLib
- open Prog_Generator_MobaLedLib.xlsm
- open M00_RevisionHistory and update the revision history
- open M02_Public and increase the Test_Suffix variable
- open M01_Gen_Release_Version and run the macro Gen_Release_Version
- verify that the "Start" sheet shows the correct version with the Test_Suffix  
- save and close

4.) libraries.properties
- change version attribute to match version and Test_Suffix, e.g. version=3.5.0-h

5.) commit changes to the beta branch
- while commit use a diff tool (e.g. BeyondCompare) to review the code changes
- fill the commit message with a good short description - at least the text used in revision history

6.) test the new beta
- change to the folder containing the existing MobaLedLib installation
- open Prog_Generator_MobaLedLib, select options/update/ "Installiere Korrektorversion"
- at the dialog "Soll die Korrektorversion installiert werden" press and hold the STRG (CTRL) key while clicking "Ja" Button
- the dialog "Beta Test Installation" opens, if not already correct change the URL to https://github.com/Hardi-St/MobaLedLib/archive/refs/heads/beta.zip
- wait for the update to complete
- Prog_Generator_MobaLedLib opens, import the settings from the previous version
- select a sheet with test configuration and install it for all three platforms, Arduino, ESP32 and PICO
- change build tool to platformio, repeat installation for all three platforms, Arduino, ESP32 and PICO
- verify the simulator: Press and hold the "Shift" key while clicking "zum Arduino schicken"

7.) upload the beta to MobaLedLib Docu repository
- Check out or use already checked out master branch of https://github.com/Hardi-St/MobaLedLib_Docu
- download the file https://github.com/Hardi-St/MobaLedLib/archive/refs/heads/beta.zip
- use 7zip (or other tool) to view the archive (no need to extract files)
- rename the root folder from "beta" to "master"
- close the zip
- rename to zip file from MobaLedLib-beta.zip to MobaLedLib-master.zip
- copy the zip to MobaLedLib_Docu.git\Betatest folder, overwriting the existing file
- commit changes to the master branch of MobaLedLib Docu repository
  - while commit use a diff tool (e.g. BeyondCompare) to AGAIN review the changes
  - use the release string for the commit message, e.g. "Release 3.5.0H"
  
8.) Again change to the folder containing the existing MobaLedLib installation
- open Prog_Generator_MobaLedLib, select options/update/ "Installiere Korrektorversion" 
- at the dialog "Soll die Korrektorversion installiert werden" press "Ja" - without "STRG/CTRL" key - to run a default beta update
- wait for the update to complete
- Prog_Generator_MobaLedLib opens, import the settings from the previous version
- select a sheet with test configuration and install it for all three platforms, Arduino, ESP32 and PICO
- change build tool to platformio, repeat installation for all three platforms, Arduino, ESP32 and PICO
- verify the simulator: Press and hold the "Shift" key while clicking "zum Arduino schicken"

9.) Publish release info in forum
- open forum Software -> MobaLedLib Software -> MLL Releases: https://forum.mobaledlib.de/viewforum.php?f=117
- create a new topic named "MobaLedLib Korrekturversion " + version string, e.g. "MobaLedLib Korrekturversion 3.5.0H"
- describe changes, new features, bufixes etc., at least in german, best also in english

10.) wait for feedback
- if you receive good feedback -> be happy
- if you receive error or problem message -> handle the problems and publish a next beta fixing the issues













