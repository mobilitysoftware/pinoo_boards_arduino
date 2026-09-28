# =============================================================================
# Pinoo SDK - Release Paketi Oluşturucu
# =============================================================================
# Kullanım: .\create_release.ps1 [-Version "1.0.0"] [-GithubUser "kullaniciadi"] [-GithubRepo "pinoo_sdk"]
#
# Ne yapar?
#   1. hardware/avr/1.0.0/ klasörünü pinoo-avr-<version>.zip olarak paketler
#   2. hardware/esp32/1.0.0/ klasörünü pinoo-esp32-<version>.zip olarak paketler
#   3. Her ZIP için SHA-256 checksum ve byte boyutu hesaplar
#   4. package_pinoo_index.json dosyasındaki PLACEHOLDER değerlerini gerçek değerlerle doldurur
# =============================================================================

param(
    [string]$Version    = "1.0.3",
    [string]$GithubUser = "mobilitysoftware",
    [string]$GithubRepo = "pinoo_sdk"
)

$ErrorActionPreference = "Stop"
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path

Write-Host ""
Write-Host "======================================================" -ForegroundColor Cyan
Write-Host "  Pinoo SDK Release Paketi Olusturucu v$Version" -ForegroundColor Cyan
Write-Host "======================================================" -ForegroundColor Cyan
Write-Host ""

# --- Çıkış klasörü ---
$OutputDir = Join-Path $ScriptDir "release_output"
if (Test-Path $OutputDir) {
    Remove-Item $OutputDir -Recurse -Force
}
New-Item -ItemType Directory -Path $OutputDir | Out-Null
Write-Host "[OK] Cikis klasoru olusturuldu: $OutputDir" -ForegroundColor Green

# =============================================================================
# Yardımcı Fonksiyonlar
# =============================================================================

function New-PinooZip {
    param(
        [string]$SourceDir,
        [string]$ZipName,
        [string]$InternalFolderName
    )

    $ZipPath = Join-Path $OutputDir $ZipName

    # Geçici klasör oluştur (ZIP içindeki klasör adı önemli!)
    $TempDir = Join-Path $OutputDir "temp_$InternalFolderName"
    $TempInner = Join-Path $TempDir $InternalFolderName

    New-Item -ItemType Directory -Path $TempInner | Out-Null
    Copy-Item -Path "$SourceDir\*" -Destination $TempInner -Recurse

    # ZIP oluştur
    Compress-Archive -Path "$TempInner" -DestinationPath $ZipPath -Force

    # Temizle
    Remove-Item $TempDir -Recurse -Force

    return $ZipPath
}

function Get-FileChecksum {
    param([string]$FilePath)
    $hash = (Get-FileHash -Path $FilePath -Algorithm SHA256).Hash
    return "SHA-256:$hash"
}

function Get-FileSize {
    param([string]$FilePath)
    return (Get-Item $FilePath).Length
}

# =============================================================================
# 1. AVR Paketi
# =============================================================================
Write-Host ""
Write-Host "[1/4] AVR paketi hazirlaniyor..." -ForegroundColor Yellow

$AvrSourceDir = Join-Path $ScriptDir "hardware\avr\$Version"
if (-not (Test-Path $AvrSourceDir)) {
    Write-Error "HATA: AVR kaynak klasoru bulunamadi: $AvrSourceDir"
    exit 1
}

$AvrZipName  = "pinoo-avr-$Version.zip"
$AvrZipPath  = New-PinooZip -SourceDir $AvrSourceDir -ZipName $AvrZipName -InternalFolderName "pinoo-avr-$Version"

$AvrChecksum = Get-FileChecksum -FilePath $AvrZipPath
$AvrSize     = Get-FileSize -FilePath $AvrZipPath
$AvrUrl      = "https://github.com/$GithubUser/$GithubRepo/releases/download/v$Version/$AvrZipName"

Write-Host "  ZIP     : $AvrZipPath" -ForegroundColor Gray
Write-Host "  Checksum: $AvrChecksum" -ForegroundColor Gray
Write-Host "  Boyut   : $AvrSize byte" -ForegroundColor Gray
Write-Host "  URL     : $AvrUrl" -ForegroundColor Gray
Write-Host "[OK] AVR paketi olusturuldu." -ForegroundColor Green

# =============================================================================
# 2. ESP32 Paketi
# =============================================================================
Write-Host ""
Write-Host "[2/5] ESP32 paketi hazirlaniyor..." -ForegroundColor Yellow

$Esp32SourceDir = Join-Path $ScriptDir "hardware\esp32\$Version"
if (-not (Test-Path $Esp32SourceDir)) {
    Write-Error "HATA: ESP32 kaynak klasoru bulunamadi: $Esp32SourceDir"
    exit 1
}

$Esp32ZipName  = "pinoo-esp32-$Version.zip"
$Esp32ZipPath  = New-PinooZip -SourceDir $Esp32SourceDir -ZipName $Esp32ZipName -InternalFolderName "pinoo-esp32-$Version"

$Esp32Checksum = Get-FileChecksum -FilePath $Esp32ZipPath
$Esp32Size     = Get-FileSize -FilePath $Esp32ZipPath
$Esp32Url      = "https://github.com/$GithubUser/$GithubRepo/releases/download/v$Version/$Esp32ZipName"

Write-Host "  ZIP     : $Esp32ZipPath" -ForegroundColor Gray
Write-Host "  Checksum: $Esp32Checksum" -ForegroundColor Gray
Write-Host "  Boyut   : $Esp32Size byte" -ForegroundColor Gray
Write-Host "  URL     : $Esp32Url" -ForegroundColor Gray
Write-Host "[OK] ESP32 paketi olusturuldu." -ForegroundColor Green

# =============================================================================
# 3. ESP8266 Paketi
# =============================================================================
Write-Host ""
Write-Host "[3/5] ESP8266 paketi hazirlaniyor..." -ForegroundColor Yellow

$Esp8266SourceDir = Join-Path $ScriptDir "hardware\esp8266\$Version"
if (-not (Test-Path $Esp8266SourceDir)) {
    Write-Error "HATA: ESP8266 kaynak klasoru bulunamadi: $Esp8266SourceDir"
    exit 1
}

$Esp8266ZipName  = "pinoo-esp8266-$Version.zip"
$Esp8266ZipPath  = New-PinooZip -SourceDir $Esp8266SourceDir -ZipName $Esp8266ZipName -InternalFolderName "pinoo-esp8266-$Version"

$Esp8266Checksum = Get-FileChecksum -FilePath $Esp8266ZipPath
$Esp8266Size     = Get-FileSize -FilePath $Esp8266ZipPath
$Esp8266Url      = "https://github.com/$GithubUser/$GithubRepo/releases/download/v$Version/$Esp8266ZipName"

Write-Host "  ZIP     : $Esp8266ZipPath" -ForegroundColor Gray
Write-Host "  Checksum: $Esp8266Checksum" -ForegroundColor Gray
Write-Host "  Boyut   : $Esp8266Size byte" -ForegroundColor Gray
Write-Host "  URL     : $Esp8266Url" -ForegroundColor Gray
Write-Host "[OK] ESP8266 paketi olusturuldu." -ForegroundColor Green

# =============================================================================
# 4. package_pinoo_index.json güncelle
# =============================================================================
Write-Host ""
Write-Host "[4/5] package_pinoo_index.json guncelleniyor..." -ForegroundColor Yellow

$IndexTemplatePath = Join-Path $ScriptDir "package_pinoo_index.json"
if (-not (Test-Path $IndexTemplatePath)) {
    Write-Error "HATA: package_pinoo_index.json bulunamadi!"
    exit 1
}

$json = Get-Content $IndexTemplatePath -Raw -Encoding UTF8 | ConvertFrom-Json
$pinooPkg = $json.packages | Where-Object { $_.name -eq "pinoo" }

$avrPlat = $pinooPkg.platforms | Where-Object { $_.architecture -eq "avr" }
if ($avrPlat) {
    $avrPlat.url = $AvrUrl
    $avrPlat.archiveFileName = $AvrZipName
    $avrPlat.checksum = $AvrChecksum
    $avrPlat.size = "$AvrSize"
}

$esp32Plat = $pinooPkg.platforms | Where-Object { $_.architecture -eq "esp32" }
if ($esp32Plat) {
    $esp32Plat.url = $Esp32Url
    $esp32Plat.archiveFileName = $Esp32ZipName
    $esp32Plat.checksum = $Esp32Checksum
    $esp32Plat.size = "$Esp32Size"
}

$esp8266Plat = $pinooPkg.platforms | Where-Object { $_.architecture -eq "esp8266" }
if ($esp8266Plat) {
    $esp8266Plat.url = $Esp8266Url
    $esp8266Plat.archiveFileName = $Esp8266ZipName
    $esp8266Plat.checksum = $Esp8266Checksum
    $esp8266Plat.size = "$Esp8266Size"
}

# Çıkış JSON'ı yaz
$OutputIndexPath = Join-Path $OutputDir "package_pinoo_index.json"
$utf8NoBom = New-Object System.Text.UTF8Encoding $false
[System.IO.File]::WriteAllText($OutputIndexPath, ($json | ConvertTo-Json -Depth 100), $utf8NoBom)

Write-Host "[OK] JSON guncellendi: $OutputIndexPath" -ForegroundColor Green

# =============================================================================
# 5. Özet
# =============================================================================
Write-Host ""
Write-Host "======================================================" -ForegroundColor Cyan
Write-Host "  TAMAMLANDI!" -ForegroundColor Green
Write-Host "======================================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Olusturulan dosyalar:" -ForegroundColor White
Write-Host "  $OutputDir\" -ForegroundColor Gray
Write-Host "  |-- $AvrZipName" -ForegroundColor Gray
Write-Host "  |-- $Esp32ZipName" -ForegroundColor Gray
Write-Host "  |-- $Esp8266ZipName" -ForegroundColor Gray
Write-Host "  \-- package_pinoo_index.json" -ForegroundColor Gray
Write-Host ""
Write-Host "Sonraki adimlar:" -ForegroundColor White
Write-Host "  1. GitHub uzerinde repoyu public yap" -ForegroundColor Yellow
Write-Host "  2. v$Version etiketi ile bir GitHub Release olustur" -ForegroundColor Yellow
Write-Host "  3. release_output icerisindeki ZIP dosyalarini Release ekle" -ForegroundColor Yellow
Write-Host "  4. release_output/package_pinoo_index.json icerigini" -ForegroundColor Yellow
Write-Host "     repo kok dizinindeki package_pinoo_index.json dosyasina kopyala ve commit yap" -ForegroundColor Yellow
Write-Host ""
Write-Host "  Arduino IDE Ek Kart Yoneticisi URL:" -ForegroundColor White
Write-Host "  https://raw.githubusercontent.com/$GithubUser/$GithubRepo/main/package_pinoo_index.json" -ForegroundColor Cyan
Write-Host ""

