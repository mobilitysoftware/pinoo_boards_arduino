# PowerShell script to synchronize the Pinoo SDK library files and external dependencies into the hardware platform folders.
# This prevents code duplication in Git while providing a self-contained board package installation.

$ErrorActionPreference = "Stop"

# Define Paths
$SrcDir = Join-Path $PSScriptRoot "src"
$ExamplesDir = Join-Path $PSScriptRoot "examples"
$PropsFile = Join-Path $PSScriptRoot "library.properties"
$KeywordsFile = Join-Path $PSScriptRoot "keywords.txt"

# External Library Sources
$ExtLibsSrcDir = Join-Path $PSScriptRoot "pinoostudiodan_cekilen_libraries/libraries"
$ExtLibs = @("Adafruit_NeoPixel", "IRremote", "LiquidCrystal_I2C", "Adafruit_PWM_Servo_Driver_Library", "Adafruit_BusIO")

$Version = "1.0.2"

# Platform Destinations
$Destinations = @(
    (Join-Path $PSScriptRoot "hardware/avr/$Version/libraries"),
    (Join-Path $PSScriptRoot "hardware/esp32/$Version/libraries")
)

# Function to copy files recursively and sync external dependencies
function Sync-LibrariesForPlatform {
    param (
        [string]$LibrariesDest
    )
    
    # 1. Sync the core Pinoo SDK Library
    $PinooDest = Join-Path $LibrariesDest "Pinoo"
    if (Test-Path $PinooDest) {
        Write-Host "Cleaning existing files in $PinooDest..." -ForegroundColor Gray
        Remove-Item -Path $PinooDest -Recurse -Force
    }
    $null = New-Item -ItemType Directory -Path $PinooDest -Force
    
    Write-Host "Syncing Pinoo SDK src/ to $PinooDest/src..." -ForegroundColor Gray
    Copy-Item -Path $SrcDir -Destination $PinooDest -Recurse -Force
    
    Write-Host "Syncing Pinoo SDK examples/ to $PinooDest/examples..." -ForegroundColor Gray
    Copy-Item -Path $ExamplesDir -Destination $PinooDest -Recurse -Force
    
    Write-Host "Syncing Pinoo SDK library.properties to $PinooDest..." -ForegroundColor Gray
    Copy-Item -Path $PropsFile -Destination $PinooDest -Force
    
    Write-Host "Syncing Pinoo SDK keywords.txt to $PinooDest..." -ForegroundColor Gray
    Copy-Item -Path $KeywordsFile -Destination $PinooDest -Force
    
    # 2. Sync External Dependencies (Adafruit_NeoPixel, IRremote, LiquidCrystal_I2C)
    foreach ($LibName in $ExtLibs) {
        $LibSrc = Join-Path $ExtLibsSrcDir $LibName
        $LibDest = Join-Path $LibrariesDest $LibName
        
        if (Test-Path $LibSrc) {
            if (Test-Path $LibDest) {
                Write-Host "Cleaning existing files in $LibDest..." -ForegroundColor Gray
                Remove-Item -Path $LibDest -Recurse -Force
            }
            $null = New-Item -ItemType Directory -Path $LibDest -Force
            
            Write-Host "Syncing external library $LibName to $LibDest..." -ForegroundColor Gray
            Copy-Item -Path "$LibSrc/*" -Destination $LibDest -Recurse -Force
        } else {
            Write-Warning "Source external library not found: $LibSrc"
        }
    }
}

# Execute sync for all destinations
foreach ($LibDest in $Destinations) {
    Write-Host "==========================================" -ForegroundColor Cyan
    Write-Host "Syncing all libraries to platform destination:" -ForegroundColor Cyan
    Write-Host "$LibDest" -ForegroundColor White
    Sync-LibrariesForPlatform -LibrariesDest $LibDest
}

# Copy to IDE directories for live testing
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "Deploying to active IDE folders..." -ForegroundColor Cyan

# 1. AppData packages directory (for Arduino IDE 2.x)
$AppDataHardware = "C:\Users\SemihNoir\AppData\Local\Arduino15\packages\pinoo\hardware"
if (Test-Path "C:\Users\SemihNoir\AppData\Local\Arduino15") {
    Write-Host "Syncing to AppData (IDE 2.x): $AppDataHardware" -ForegroundColor Gray
    if (Test-Path $AppDataHardware) { Remove-Item -Path $AppDataHardware -Recurse -Force }
    $null = New-Item -ItemType Directory -Path $AppDataHardware -Force
    Copy-Item -Path "$PSScriptRoot/hardware/*" -Destination $AppDataHardware -Recurse -Force
}

Write-Host "==========================================" -ForegroundColor Green
Write-Host "Synchronization and deployment completed successfully!" -ForegroundColor Green
