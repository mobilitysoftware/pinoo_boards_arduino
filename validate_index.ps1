$filePath = "d:\Projeler\pinoo-stuff\pinoo_sdk\package_pinoo_index.json"
$bytes = [System.IO.File]::ReadAllBytes($filePath)

$b0 = $bytes[0]
$b1 = $bytes[1]
$b2 = $bytes[2]

# BOM kontrolu
if ($b0 -eq 239 -and $b1 -eq 187 -and $b2 -eq 191) {
    Write-Host "UYARI: BOM bulundu!" -ForegroundColor Red
} else {
    Write-Host "BOM yok - temiz UTF-8" -ForegroundColor Green
}

# JSON parse kontrolu
try {
    $json = Get-Content $filePath -Raw | ConvertFrom-Json
    $packageCount = $json.packages.Count
    Write-Host "JSON gecerli - $packageCount paket var" -ForegroundColor Green

    foreach ($pkg in $json.packages) {
        $platformCount = $pkg.platforms.Count
        $toolCount = $pkg.tools.Count
        Write-Host "  Paket: '$($pkg.name)' -> $platformCount platform, $toolCount tool" -ForegroundColor Cyan
        foreach ($plat in $pkg.platforms) {
            Write-Host "    Platform: $($plat.name) [$($plat.architecture)] v$($plat.version)" -ForegroundColor Gray
            Write-Host "      Board sayisi: $($plat.boards.Count)" -ForegroundColor Gray
            Write-Host "      ToolsDep sayisi: $($plat.toolsDependencies.Count)" -ForegroundColor Gray
        }
    }
} catch {
    Write-Host "HATA: JSON parse edilemedi: $_" -ForegroundColor Red
}
