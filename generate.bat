:: ==================================================
::	Wrapper around a powershell script.
:: ==================================================

@ECHO OFF

powershell -ExecutionPolicy Bypass -File scripts/generate.ps1
PAUSE