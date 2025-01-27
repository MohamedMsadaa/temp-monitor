# temp-monitor
Small project to monitor temperature and visualize system status

# Temp Monitor Project

This project implements a temperature monitoring system with a hardware abstraction layer (HAL). The system is designed to monitor temperature readings from sensors, control LEDs based on temperature values, and provide a management interface via a `TempManager` class.

## Table of Contents

- [Dependencies](#dependencies)
- [Getting Started](#getting-started)
- [Build Instructions](#build-instructions)
- [Editor Setup](#editor-setup)
- [License](#license)

## Dependencies

### System Requirements

- **Operating System:** macOS, Linux, or Windows (with CMake support)
- **C++ Standard:** C++17
- **Compiler:** Clang/Clang++ (or GCC)

### Required Tools

1. **CMake**: For building the project and managing dependencies.
   - Install via [CMake Download](https://cmake.org/download/).
   
2. **Compiler**: The project uses C++17. Ensure you have a compatible compiler:
   - macOS/Linux: Clang or GCC.
   - Windows: MinGW or MSVC.
   
3. **Asciidoctor** (Optional, for generating documentation):
   - Ruby (to run Asciidoctor): 
     - Install Ruby from [ruby-lang.org](https://www.ruby-lang.org/en/documentation/installation/).
     - Install `asciidoctor` and `asciidoctor-pdf` gems:
       ```bash
       gem install asciidoctor asciidoctor-pdf
       ```

4. **PlantUML** (Optional, for generating diagrams):
   - Install PlantUML and integrate with your workflow.
   - For `asciidoctor` with diagrams:
     ```bash
     gem install asciidoctor-diagram
     ```

## Getting Started

To get a local copy of the project and start developing, follow these steps.

### Clone the Repository

```bash
git clone https://github.com/yourusername/temp-monitor.git
cd temp-monitor
```
## Build Instructions

Follow these steps to build the project:

### Prerequisites

Before you start building, make sure you have the following installed:
- **CMake** (version 3.26 or higher)
- **GCC** or **Clang** (for compiling C/C++ code)
- **Make** or **Ninja** (for build automation)
- **C++11** or later (required for some project features)

## Editor Setup

To make your development experience smoother, here are some setup instructions for popular editors:

### Visual Studio Code (VSCode)

1. **Install Extensions**:
   - **C/C++ extension** by Microsoft (for IntelliSense, debugging, and code navigation).
   - **CMake Tools extension** (for building and managing CMake projects).
   - **Asciidoctor extension** (for previewing `.adoc` files).

2. **Configure VSCode**:
   - Create a `tasks.json` file for building the project using the CMake Tools extension.
   - Configure your build tasks in `.vscode/tasks.json` (generated automatically with CMake Tools).

3. **Debugging**:
   - Add a `launch.json` file for configuring debugging with GDB (or LLDB) on your target platform.

4. **Asciidoctor Setup**:
   - Install the Asciidoctor extension or use the `asciidoctor` command-line tool to preview `.adoc` files directly within VSCode.

### Visual Studio (Windows)

1. **Install CMake**:
   - Ensure that CMake is installed and integrated with Visual Studio.
   - Set up your CMake project by opening the `CMakeLists.txt` file.

2. **Build and Debug**:
   - Use **Build > Build Solution** to compile the project.
   - Use **Debug > Start Debugging (F5)** to run the project and debug.

3. **Asciidoctor for Documentation**:
   - Use the **Asciidoctor extension** for previewing `.adoc` files.

### JetBrains CLion

1. **CMake Setup**:
   - CLion has built-in CMake support, so simply open the project folder containing `CMakeLists.txt`.

2. **Build and Run**:
   - Use **Run > Build** and **Run > Run** to build and run the project.

3. **Asciidoctor**:
   - Install the **Asciidoctor plugin** from the plugin repository to preview `.adoc` documentation.
