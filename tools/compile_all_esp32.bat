@echo off
setlocal enabledelayedexpansion

set FQBN=pinoo:esp32:pinoo_esp32:JTAGAdapter=default,PSRAM=disabled,PartitionScheme=default,CPUFreq=240,FlashMode=qio,FlashFreq=80,FlashSize=4M,UploadSpeed=921600,LoopCore=1,EventsCore=1,DebugLevel=none,EraseFlash=none,ZigbeeMode=default
set EXAMPLES_DIR=d:\Projeler\pinoo-stuff\pinoo_sdk\examples\Pinoo_ESP32
set PASS=0
set FAIL=0
set FAIL_LIST=

echo ========================================
echo Pinoo ESP32 - Batch Compile Test
echo ========================================
echo.

for /D %%E in ("%EXAMPLES_DIR%\*") do (
    set SKETCH_NAME=%%~nxE
    set SKETCH=%%E\%%~nxE.ino
    
    echo [Testing] !SKETCH_NAME!...
    arduino-cli compile --fqbn "%FQBN%" "!SKETCH!" >nul 2>&1
    
    if !ERRORLEVEL! == 0 (
        echo   [PASS] !SKETCH_NAME!
        set /A PASS=!PASS!+1
    ) else (
        echo   [FAIL] !SKETCH_NAME!
        set /A FAIL=!FAIL!+1
        set FAIL_LIST=!FAIL_LIST! !SKETCH_NAME!
    )
)

echo.
echo ========================================
echo Results: !PASS! PASS, !FAIL! FAIL
echo ========================================
if not "!FAIL_LIST!" == "" (
    echo Failed examples:
    for %%F in (!FAIL_LIST!) do echo   - %%F
)
