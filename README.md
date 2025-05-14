# SimpleMenu-SDUpdater
**[` 日本語 `](README_jp.md)**

## 1. Introduction

This program is a simple launcher for M5Stack devices (Cardputer, Core2, CoreS3) that lists applications (`.bin` files) stored on a microSD card, allowing you to select and run them.
It utilizes the M5StackUpdater library to launch the selected application.

**Original Program Author:** @shikarunochi

**Modified by:** NoRi

## 2. Supported Devices

*   M5Stack Cardputer / Cardputer v1.1
*   M5Stack Core2 / Core2 for AWS / Core2 v1.1
*   M5Stack CoreS3 / CoreS3-SE

## 3. What You Need

*   One of the M5Stack devices listed above
*   A microSD card
*   Application files for M5Stack (in `.bin` format) that you want to run

## 4. How to Use

### 4.1. Preparing the Program

1.  Copy the `.bin` files of the applications you want to run to the **root directory** (the top-level folder) of your microSD card.
    *   Example: `myapp.bin`, `game.bin`, etc.

### 4.2. Launching the Launcher

1.  Flash this `SimpleMenu-SDUpdater` program (compiled from `SimpleMenu-SDUpdater\src\main.cpp`) to your M5Stack device.
2.  When you power on the device, the launcher will start automatically.

### 4.3. Selecting and Running Applications

A list of `.bin` files found in the root directory of the microSD card will be displayed alphabetically on the screen.

*   **For M5Stack Cardputer:**
    *   **Move cursor up:** `;` key (semicolon key, with an up arrow printed on it)
    *   **Move cursor down:** `.` key (period key, with a down arrow printed on it)
    *   **Execute:** `Enter` key

*   **For M5Stack Core2 / CoreS3:**
    *   **Move cursor up:** `BtnA` (the leftmost button)
    *   **Move cursor down:** `BtnC` (the rightmost button)
    *   **Execute:** **Long press** `BtnB` (the middle button)

The selected application will be highlighted in green. Choose the application you want to run and execute it using the operations described above.

### 4.4. After Running an Application

The selected application will be loaded and will start running.
When the application finishes or the device is reset, the device will typically restart, and this launcher will usually start again (depending on the specifications of the selected application).

## 5. About the Screen Display

*   **File List:** Displays the names of the `.bin` files on the microSD card.
*   **Selected File:** The file name currently under the cursor is displayed in **green**. Other file names are displayed in white.
*   **File Name Length:** If a file name exceeds the screen width, it will be truncated.
    *   Cardputer: Up to approximately 20 characters
    *   Core2/CoreS3: Up to approximately 26 characters
*   **Help Message (Core2/CoreS3 only):** A simple operation guide (`up`, `select`, `down`) is displayed in yellow at the bottom of the screen.

## 6. Important Notes

*   Always place `.bin` files in the **root directory** of the microSD card. Files in subfolders will not be recognized.
*   The file extension must be `.bin` (case-insensitive).
*   There is a limit to the number of files that can be displayed on the screen at one time. If the file list is long, you can scroll by moving the cursor to select files.
*   If the microSD card is not inserted correctly or cannot be recognized, the file list will not be displayed (or an empty list will be shown).
*   Using multibyte characters (like Japanese) in file names may cause garbled text. It is recommended to use alphanumeric file names.

## 7. For Developers (Key Configuration Values in Code)

You can customize some behaviors by changing the following defined values in the source code `SimpleMenu-SDUpdater\src\main.cpp`.

*   `dispfileCount`: The maximum number of files displayed on one screen (actually, `dispfileCount + 1` files will be displayed).
    *   Cardputer: `7` (actually displays 8 files)
    *   Core2/CoreS3: `12` (actually displays 13 files)
*   `N_COLS`: The maximum number of columns (approximate characters) for displaying file names. File names exceeding this will be truncated.
    *   Cardputer: `20`
    *   Core2/CoreS3: `26`

## 8. Link

[SimpleMenu-SDUpdater](https://github.com/NoRi-230401/SimpleMenu-SDUpdater)

[SDUpdater-AppTemplate-v2](https://github.com/NoRi-230401/SDUpdater-AppTemplate-v2)

[CardputerSimpleLauncher@shikarunochi](https://github.com/shikarunochi/CardputerSimpleLaucher)

[M5Stack-SD-Updater@tobozo](https://github.com/tobozo/M5Stack-SD-Updater)

