$repoPath = "d:\Projeler\pinoo-stuff\pinoo_boards_arduino"
if (Test-Path $repoPath) {
    Write-Host "pinoo_boards_arduino BULUNDU" -ForegroundColor Green
    Get-ChildItem $repoPath | Select-Object Name, LastWriteTime
} else {
    Write-Host "pinoo_boards_arduino bulunamadi" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "Mevcut release_output ZIP checksumlari:"
$zipDir = "d:\Projeler\pinoo-stuff\pinoo_sdk\release_output"
Get-ChildItem $zipDir -Filter "*.zip" | ForEach-Object {
    $hash = (Get-FileHash -Path $_.FullName -Algorithm SHA256).Hash
    $size = $_.Length
    $name = $_.Name
    Write-Host "$name : SHA-256:$hash ($size byte)"
}
