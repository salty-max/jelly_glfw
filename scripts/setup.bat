@echo off
setlocal

:: Enable debug logging
set DEBUG_LOG=debug.log
echo Initializing setup... > %DEBUG_LOG%

:: Clean existing deps folder
echo Cleaning existing deps folder...
if exist deps (
    rmdir /S /Q deps >> %DEBUG_LOG% 2>&1
)

mkdir deps >> %DEBUG_LOG% 2>&1
mkdir deps\include >> %DEBUG_LOG% 2>&1
mkdir deps\include\glad >> %DEBUG_LOG% 2>&1
mkdir deps\include\KHR >> %DEBUG_LOG% 2>&1
mkdir deps\include\GLFW >> %DEBUG_LOG% 2>&1
mkdir deps\imgui >> %DEBUG_LOG% 2>&1
mkdir deps\lib >> %DEBUG_LOG% 2>&1

:: Clean existing build folder
echo Cleaning existing build folder...
if exist build (
    rmdir /S /Q build >> %DEBUG_LOG% 2>&1
)

:: Ensure Python is installed
echo Checking Python installation...
python --version >> %DEBUG_LOG% 2>&1
if %errorlevel% neq 0 (
    echo Python not found. Installing Python...
    powershell -Command "Invoke-WebRequest -Uri 'https://www.python.org/ftp/python/3.11.5/python-3.11.5-amd64.exe' -OutFile 'python-installer.exe'"
    python-installer.exe /quiet InstallAllUsers=1 PrependPath=1 Include_test=0
    del python-installer.exe
    python --version >> %DEBUG_LOG% 2>&1
    if %errorlevel% neq 0 (
        echo Error: Python installation failed! Check debug.log for details.
        pause
        exit /b 1
    )
)

:: Ensure Pip is installed
echo Checking Pip installation...
pip --version >> %DEBUG_LOG% 2>&1
if %errorlevel% neq 0 (
    echo Pip not found. Installing Pip...
    python -m ensurepip --upgrade >> %DEBUG_LOG% 2>&1
    python -m pip install --upgrade pip >> %DEBUG_LOG% 2>&1
    pip --version >> %DEBUG_LOG% 2>&1
    if %errorlevel% neq 0 (
        echo Error: Pip installation failed! Check debug.log for details.
        pause
        exit /b 1
    )
)

:: Install Python dependencies
echo Installing required Python modules...
pip install --quiet jinja2 >> %DEBUG_LOG% 2>&1

:: Download and build Glad
echo Cloning Glad repository...
git clone https://github.com/Dav1dde/glad.git deps\glad >> %DEBUG_LOG% 2>&1
cd deps\glad

:: Generate Glad files
echo Generating Glad files...
python -m glad --api=gl:core=4.6 --out-path=glad_build >> %DEBUG_LOG% 2>&1
if %errorlevel% neq 0 (
    echo Error: Glad generation failed! Check debug.log for details.
    pause
    exit /b 1
)
cd glad_build

:: Copy generated Glad files
echo Copying generated Glad files...
copy include\glad\gl.h ..\..\include\glad\gl.h
copy include\KHR\khrplatform.h ..\..\include\KHR\khrplatform.h
copy src\gl.c ..\..\lib\gl.c
cd ..\..\..

:: Verify Glad setup
if not exist deps\include\glad\gl.h (
    echo Error: Glad header generation failed! Check debug.log for details.
    pause
    exit /b 1
)
if not exist deps\lib\gl.c (
    echo Error: Glad source generation failed! Check debug.log for details.
    pause
    exit /b 1
)

:: Clone GLFW repository
echo Cloning GLFW repository...
git clone https://github.com/glfw/glfw.git deps\glfw >> %DEBUG_LOG% 2>&1

:: Build GLFW
echo Building GLFW...
cd deps\glfw
cmake -S . -B build -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF >> %DEBUG_LOG% 2>&1
cmake --build build --config Release >> %DEBUG_LOG% 2>&1
cd ../..

if not exist deps\glfw\build\src\libglfw3.a (
    echo Error: GLFW build failed! Check debug.log for details.
    pause
    exit /b 1
)

:: Copy GLFW headers
echo Copying GLFW headers...
robocopy deps\glfw\include\GLFW deps\include\GLFW /E >> %DEBUG_LOG% 2>&1
if not exist deps\include\GLFW\glfw3.h (
    echo Error: GLFW header copy failed! Check debug.log for details.
    pause
    exit /b 1
)

:: Copy GLFW library
echo Copying GLFW library...
copy /Y deps\glfw\build\src\libglfw3.a deps\lib\libglfw3.a >> %DEBUG_LOG% 2>&1
if not exist deps\lib\libglfw3.a (
    echo Error: GLFW library copy failed! Check debug.log for details.
    pause
    exit /b 1
)

:: Clone Dear ImGui repository
echo Cloning Dear ImGui repository...
git clone https://github.com/ocornut/imgui.git deps\imgui >> %DEBUG_LOG% 2>&1
if not exist deps\imgui\imgui.cpp (
    echo Error: Failed to clone Dear ImGui repository!
    pause
    exit /b 1
)

:: Verify Dear ImGui setup
if not exist deps\imgui\imgui.cpp (
    echo Error: Dear ImGui setup failed!
    pause
    exit /b 1
)

:: Download stb_image.h
echo Downloading stb_image.h...
curl -L https://raw.githubusercontent.com/nothings/stb/master/stb_image.h -o deps\include\stb_image.h
if not exist deps\include\stb_image.h (
    echo Error: Failed to download stb_image.h!
    pause
    exit /b 1
)

:: Cleanup
echo Cleaning up build files...
rmdir /S /Q deps\glad >> %DEBUG_LOG% 2>&1
rmdir /S /Q deps\glfw >> %DEBUG_LOG% 2>&1

:: CMake
echo Checking CMake installation...
cmake --version >> %DEBUG_LOG% 2>&1 && cmake --version
if %errorlevel% neq 0 (
    echo Error: CMake is not installed or not in PATH! Check debug.log for details.
    pause
    exit /b 1
)

:: Generate build files
echo Generating build files...
cmake -S . -B build -G "MinGW Makefiles" >> %DEBUG_LOG% 2>&1

:: Build project
echo Building project...
cmake --build build >> %DEBUG_LOG% 2>&1

:: Verify build
if not exist build\bin\sandbox.exe (
    echo Error: Build failed! Check debug.log for details.
    pause
    exit /b 1
)

echo Setup complete!
pause
