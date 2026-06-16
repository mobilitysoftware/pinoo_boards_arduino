# =============================================================================
# Pinoo SDK - Birlesik Index Olusturucu
# =============================================================================
# package_pinoo_index.json + package_esp32_index.template.json'u birlestirir.
# Sonuc: tek URL'den hem AVR hem ESP32 kartlar kurulabilir.
# =============================================================================

$ErrorActionPreference = "Stop"
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path

Write-Host ""
Write-Host "======================================================" -ForegroundColor Cyan
Write-Host "  Pinoo Index Birlestirici" -ForegroundColor Cyan
Write-Host "======================================================" -ForegroundColor Cyan

# --- Dosyalari oku ---
$pinooIndexPath = Join-Path $ScriptDir "package_pinoo_index.json"
$esp32TemplatePath = Join-Path $ScriptDir "package_esp32_index.template.json"

if (-not (Test-Path $pinooIndexPath)) {
    Write-Error "HATA: package_pinoo_index.json bulunamadi!"
    exit 1
}
if (-not (Test-Path $esp32TemplatePath)) {
    Write-Error "HATA: package_esp32_index.template.json bulunamadi!"
    exit 1
}

$pinooIndex = Get-Content $pinooIndexPath -Raw -Encoding UTF8 | ConvertFrom-Json
$esp32Template = Get-Content $esp32TemplatePath -Raw -Encoding UTF8 | ConvertFrom-Json

Write-Host "[OK] Dosyalar okundu." -ForegroundColor Green

# --- ESP32 tool listesini al ---
$esp32Package = $esp32Template.packages | Where-Object { $_.name -eq "esp32" }
if (-not $esp32Package) {
    Write-Error "HATA: ESP32 paketi template'de bulunamadi!"
    exit 1
}

$esp32Tools = $esp32Package.tools
Write-Host "[OK] ESP32 tool sayisi: $($esp32Tools.Count)" -ForegroundColor Green

# --- Birlesik yapiya ekle ---
# packages dizisine esp32 packager'i ekle (sadece tools, platform yok)
$esp32Entry = [PSCustomObject]@{
    name        = "esp32"
    maintainer  = "Espressif Systems"
    websiteURL  = "https://github.com/espressif/arduino-esp32"
    email       = "hristo@espressif.com"
    help        = [PSCustomObject]@{ online = "https://esp32.com" }
    platforms   = @()
    tools       = $esp32Tools
}

# Mevcut pinoo paketine ek olarak esp32 paketini ekle
$combinedPackages = @($pinooIndex.packages) + @($esp32Entry)
$combinedIndex = [PSCustomObject]@{
    packages = $combinedPackages
}

# --- JSON'a cevir ve kaydet ---
$outputPath = Join-Path $ScriptDir "package_pinoo_index.json"
$json = $combinedIndex | ConvertTo-Json -Depth 20

# BOM'suz UTF-8 olarak kaydet (kritik!)
$utf8NoBom = New-Object System.Text.UTF8Encoding $false
[System.IO.File]::WriteAllText($outputPath, $json, $utf8NoBom)

Write-Host "[OK] Birlesik index olusturuldu: $outputPath" -ForegroundColor Green
Write-Host "     Boyut: $((Get-Item $outputPath).Length) byte" -ForegroundColor Gray

Write-Host ""
Write-Host "======================================================" -ForegroundColor Cyan
Write-Host "  TAMAMLANDI!" -ForegroundColor Green
Write-Host "======================================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Simdi: package_pinoo_index.json'u commit'le ve push'la." -ForegroundColor Yellow
Write-Host "Ardindan Arduino IDE'de Board Manager'i yenile." -ForegroundColor Yellow
Write-Host ""
