# Sudoku

This is a Sudoku game built using the Qt framework. Experience classic Sudoku with a modern twist! Built with Qt, this game offers a clean interface, real-time error detection, and a solution finder to assist with tricky puzzles. User-entered values are highlighted in blue, while mistakes are marked in red for easy correction. Dive into the fun!

![sudoku-capture](https://github.com/user-attachments/assets/d84cd4e1-eaa5-4d06-8819-82425320005c)

## Key Features

- **Standard Sudoku Gameplay:** Enjoy classic Sudoku with a clean and intuitive interface.
- **Solution Finder:** Get possible solutions for any field, making it easier to solve complex puzzles.
- **User-Friendly Interface:** Built with the Qt framework for a smooth and responsive experience.
- **Visual Feedback:**
  - **Selected Fields:** Highlighted in yellow for easy identification.
  - **User-Entered Values:** Displayed in blue, differentiating them from pre-filled values.
  - **Pre-Filled Values:** Displayed in black and are immutable, ensuring they cannot be accidentally altered.
  - **Error Detection:** Incorrectly filled fields are highlighted in red, helping users easily identify and correct mistakes.

## Missing Features
- **Temporary Locking:** A feature to lock values temporarily, allowing users to mark potential solutions without committing to them.
- **Hints:** An option to provide hints for solving the puzzle.

## Building the Qt Application from Source

To build and run the **Sudoku** application from source, the best solution would be to open the application in [Qt Creator](https://www.qt.io/), then compile it to your liking. But if you want to do it manually, here are the steps you need to follow: 

1. **Clone the Repository:**
   - Ensure you have Git installed on your system.
   - Open your terminal or command prompt and navigate to the directory where you want to clone the repository.
   - Run the following command:
     ```
     git clone https://github.com/ali-begic/sudoku
     ```
   - Navigate into the cloned directory:
     ```
     cd sudoku
     ```

2. **Install Qt Dependencies:**
   - Ensure you have the necessary Qt libraries, compilers, and build tools installed. Refer to the official Qt documentation for platform-specific instructions:
     - [Qt Documentation for Windows](https://doc.qt.io/qt-6/windows-deployment.html)
     - [Qt Documentation for macOS](https://doc.qt.io/qt-6/macos-deployment.html)
     - [Qt Documentation for Linux](https://doc.qt.io/qt-6/linux-deployment.html)

3. **Configure and Build:**
   - Create a build directory and navigate into it:
     ```
     mkdir build
     cd build
     ```
   - Run `qmake` to generate the Makefile from the `.pro` file:
     ```
     qmake ../src/sudoku.pro
     ```
   - Compile the application:
      - On Windows with MSVC:
        ```
        nmake
        ```
      - On Windows with MinGW:
        ```
        mingw32-make
        ```
      - On macOS and Linux:
        ```
        make
        ```

4. **Run Your Application:**
   - After a successful build, the executable will be located in the build directory.
   - On Windows, you can find the executable in the release or debug directory depending on your build configuration.
   - Run the application:
     ```
     ./sudoku
     ```

## Using `windeployqt` for Windows Deployment

To deploy the **Grades** application on Windows, you can use the `windeployqt` tool. This tool automatically copies the necessary Qt runtime files (DLLs, plugins, etc.) to your application's deployment folder, making it easier to distribute the application.

### Steps to Use `windeployqt`:

1. **Build Your Application:**
   - Ensure that your application is fully built using the steps above.

2. **Open the Correct Command Prompt:**
   - Open the "Developer Command Prompt for VS 2022" or the "Qt MinGW" command prompt, depending on the compiler you used.

3. **Navigate to the Build Directory:**
   - Use the command prompt to navigate to the directory where your application’s executable is located:
     ```bash
     cd .../sudoku/build/release
     ```

4. **Run `windeployqt`:**
   - Run the following command to deploy your application:
     ```bash
     windeployqt sudoku.exe
     ```

5. **Test the Deployed Application:**
   - After running `windeployqt`, test the application by running the executable in its deployment directory to ensure all dependencies are correctly deployed.

6. **Distribute the Application:**
   - You can now package the deployed files (including the executable and all copied DLLs and plugins) into a ZIP file, installer, or other distribution formats for distribution.

## Contributing

Contributions are welcome! If you find a bug, have a feature request, or want to improve the code, feel free to open an issue or submit a pull request.

## License

This project is licensed under the Apache-2.0 license - see the [LICENSE](LICENSE) file for details.

## Additional Notes

- Ensure that you have the correct version of Qt and associated build tools for your platform.
- If you encounter issues, check the Qt and compiler documentation or seek assistance on community forums.
- If the application still does not work properly, try running it as an administrator.

Thank you for your interest in the **Sudoku** application!
