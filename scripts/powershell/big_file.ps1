param([string]$FileName)
if (-not (Test-Path $FileName)) { "File does not exist"; exit }
$size=(Get-Item $FileName).Length
if ($size -gt 1048576){"Too large"} else {"OK"}
