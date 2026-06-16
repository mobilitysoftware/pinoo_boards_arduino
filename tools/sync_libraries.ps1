<#
.SYNOPSIS
    Syncs Pinoo ESP32 SDK changes to the installed Arduino packages.

.DESCRIPTION
    Copies modified source files and hardware libraries from the local SDK 
    to the arduino-cli installed package directory so that builds pick up
    the latest changes.

    Run this after making any changes to:
      - src/  (Pinoo module source files)
      - hardware/esp32/1.0.0/libraries/  (bundled platform libraries)
      - hardware/esp32/1.0.0/boards.txt
      - hardware/esp32/1.0.0/platform.txt

.EXAMPLE
    .\tools\sync_libraries.ps1
#>

$sdkRoot     = Split-Path $PSScriptRoot -Parent
$installedPkg = "C:\Users\$env:USERNAME\AppData\Local\Arduino15\packages\pinoo\hardware\esp32\1.0.0"

Write-Host "=== Pinoo ESP32 SDK Sync ===" -ForegroundColor Cyan
Write-Host "SDK      : $sdkRoot"
Write-Host "Installed: $installedPkg"
Write-Host ""

# --- 1. Sync Pinoo module source files (src/) ---
Write-Host "[1/4] Syncing src/ -> installed Pinoo library..." -ForegroundColor Yellow
$srcDir = Join-Path $sdkRoot "src"
$dstLib = Join-Path $installedPkg "libraries\Pinoo\src"
Copy-Item "$srcDir\*" $dstLib -Recurse -Force
Write-Host "      Done." -ForegroundColor Green

# --- 2. Sync boards.txt ---
Write-Host "[2/4] Syncing boards.txt..." -ForegroundColor Yellow
Copy-Item (Join-Path $sdkRoot "hardware\esp32\1.0.0\boards.txt") $installedPkg -Force
Write-Host "      Done." -ForegroundColor Green

# --- 3. Sync hardware bundled libraries ---
Write-Host "[3/4] Syncing hardware libraries..." -ForegroundColor Yellow
$hwLibs = Join-Path $sdkRoot "hardware\esp32\1.0.0\libraries"
$dstLibs = Join-Path $installedPkg "libraries"
Get-ChildItem $hwLibs -Directory | ForEach-Object {
    $libName = $_.Name
    $srcLib  = $_.FullName
    $dstLib2 = Join-Path $dstLibs $libName
    Copy-Item $srcLib $dstLib2 -Recurse -Force
    Write-Host "      $libName" -ForegroundColor DarkGray
}
Write-Host "      Done." -ForegroundColor Green

# --- 4. Sync partition CSVs ---
Write-Host "[4/5] Syncing partition CSV files..." -ForegroundColor Yellow
$srcParts = Join-Path $sdkRoot "hardware\esp32\1.0.0\tools\partitions"
$dstParts = Join-Path $installedPkg "tools\partitions"
if (Test-Path $srcParts) {
    New-Item -ItemType Directory -Force -Path $dstParts | Out-Null
    Copy-Item "$srcParts\*.csv" $dstParts -Force
    Copy-Item "$srcParts\*.bin" $dstParts -Force -ErrorAction SilentlyContinue
    Write-Host "      Done." -ForegroundColor Green
} else {
    Write-Host "      Skipped (no tools/partitions folder in SDK)." -ForegroundColor DarkGray
}

# --- 5. Sync build tools (gen_esp32part.exe, espota.exe, etc.) ---
Write-Host "[5/5] Syncing build tools (gen_esp32part, espota, etc.)..." -ForegroundColor Yellow
$srcTools = Join-Path $sdkRoot "hardware\esp32\1.0.0\tools"
$dstTools = Join-Path $installedPkg "tools"
New-Item -ItemType Directory -Force -Path $dstTools | Out-Null
Get-ChildItem $srcTools -File | ForEach-Object {
    Copy-Item $_.FullName (Join-Path $dstTools $_.Name) -Force
    Write-Host "      $($_.Name)" -ForegroundColor DarkGray
}
Write-Host "      Done." -ForegroundColor Green

Write-Host ""
Write-Host "=== Sync complete! ===" -ForegroundColor Cyan
