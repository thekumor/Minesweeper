:: ==================================================
::	Wrapper around a powershell script.
:: ==================================================

@ECHO OFF

powershell -ExecutionPolicy Bypass -File scripts/build.ps1
PAUSE