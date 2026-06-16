$filePath = "d:\Projeler\pinoo-stuff\pinoo_sdk\package_pinoo_index.json"
$bytes = [System.IO.File]::ReadAllBytes($filePath)

$b0 = $bytes[0]
$b1 = $bytes[1]
$b2 = $bytes[2]

Write-Host "Ilk 3 byte: $b0 $b1 $b2"

if ($b0 -eq 239 -and $b1 -eq 187 -and $b2 -eq 191) {
    Write-Host "BOM BULUNDU - temizleniyor..." -ForegroundColor Red
    $noBom = $bytes[3..($bytes.Length - 1)]
    [System.IO.File]::WriteAllBytes($filePath, $noBom)
    Write-Host "BOM temizlendi. Dosya UTF-8 (BOM'suz) olarak kaydedildi." -ForegroundColor Green
} else {
    Write-Host "BOM yok." -ForegroundColor Green
}

Write-Host ""
Write-Host "ZIP dosyalari (release_output):"
Get-ChildItem "d:\Projeler\pinoo-stuff\pinoo_sdk\release_output" -Filter "*.zip" | Select-Object Name, Length
