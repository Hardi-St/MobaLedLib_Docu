# Steps to create a new beta release for MobaLedLib

## Prerequisites
- MobaLedLib library files have been modified or new files are added
- changes don't break compatibility with current version - otherwise consider creating a new major release 

## Steps

### 1. Repository Setup
- Check out (or update) the **beta** branch: <https://github.com/Hardi-St/MobaLedLib/tree/beta>

### 2. Code Files
- Merge changes into `Prog_Generator_MobaLedLib.xlsm`. **!!! NEVER just copy a changed xlsm into the git beta folder !!!**
- Merge changes into `Pattern_Configurator.xlsm`. **!!! NEVER just copy a changed xlsm into the git beta folder !!!**
- Merge changes of other files into the beta branch.
- Add new files to the beta branch.

### 3. Prog_Generator_MobaLedLib Configuration
- Open `Prog_Generator_MobaLedLib.xlsm`.
- Open `M00_RevisionHistory` and update the revision history.
- Open `M02_Public` and increase the `Test_Suffix` variable.
- Open `M01_Gen_Release_Version` and run the macro `Gen_Release_Version`.
- Verify that the **Start** sheet shows the correct version with the `Test_Suffix`.
- Save and close.

### 4. Edit libraries.properties
- Change the `version` attribute to match the version and `Test_Suffix` (e.g., `version=3.5.0-h`).

### 5. Commit Changes to the Beta Branch
- During commit, use a diff tool (e.g., BeyondCompare) to review the code changes.
- Provide a clear commit message—at minimum, use the text from the revision history.

### 6. Test the New Beta
- Navigate to the folder containing the existing MobaLedLib installation.
- Open `Prog_Generator_MobaLedLib`, select **Options > Update > "Installiere Korrektorversion"**.
- At the dialog *"Soll die Korrektorversion installiert werden"*, **press and hold the CTRL (STRG) key** while clicking the **Ja** button.
- The "Beta Test Installation" dialog opens. If the URL is incorrect, change it to: <https://github.com/Hardi-St/MobaLedLib/archive/refs/heads/beta.zip>
- Wait for the update to complete.
- When `Prog_Generator_MobaLedLib` opens, import settings from the previous version.
- Select a test configuration sheet and install it for all three platforms: **Arduino, ESP32, and PICO**.
- Change the build tool to **PlatformIO** and repeat the installation for all three platforms.
- Verify the simulator: Press and hold **Shift** while clicking **"zum Arduino schicken"**.

### 7. Upload the Beta to MobaLedLib Docu Repository
- Check out the **master** branch of <https://github.com/Hardi-St/MobaLedLib_Docu>.
- Download the beta zip: <https://github.com/Hardi-St/MobaLedLib/archive/refs/heads/beta.zip>
- Use 7-Zip to open the archive (do not extract).
- Rename the root folder inside the zip from `beta` to `master`.
- Rename the actual zip file from `MobaLedLib-beta.zip` to `MobaLedLib-master.zip`.
- Copy the zip to the `MobaLedLib_Docu.git\Betatest` folder, overwriting the existing file.
- Commit changes to the **master** branch of the Docu repository:
  - Use a diff tool to review changes again.
  - Use the release string for the commit message (e.g., "Release 3.5.0H").

### 8. Final Installation Verification
- Return to the existing MobaLedLib installation folder.
- Open `Prog_Generator_MobaLedLib`, select **Options > Update > "Installiere Korrektorversion"**.
- At the dialog *"Soll die Korrektorversion installiert werden"*, click **Ja** (**without** holding CTRL) to run a default beta update.
- Wait for completion and import settings.
- Repeat the platform installation tests (Arduino, ESP32, PICO) for both standard and PlatformIO builds.
- Re-verify the simulator using **Shift + "zum Arduino schicken"**.

### 9. Publish Release Info in Forum
- Navigate to the [MLL Releases Forum](https://forum.mobaledlib.de/viewforum.php?f=117).
- Create a new topic: `MobaLedLib Korrekturversion [Version String]` (e.g., "MobaLedLib Korrekturversion 3.5.0H").
- Describe changes, new features, and bugfixes in German (and English if possible).

### 10. Feedback Loop
- If feedback is positive: Release is successful.
- If errors are reported: Address the issues and publish a new beta.
