# ==================================================
#	Script that clears all the unnecessary files in
#	the project's directory.
# ==================================================

# Sets which files are to be kept.
$Whitelist = ".git","src","scripts","vs2022-old","clear.bat","generate.bat","CMakeLists.txt",".gitignore"

# Gets the current directory's structure.
$Files = Get-ChildItem

# Iterates through the files.
foreach ($File in $Files) {
	$Name = $File.Name
	Write-Output "Checking $($Name)"

	$FileIsGood = 0
	# Checks if file's name is whitelisted.
	foreach ($WhitelistedName in $Whitelist) {
		if ($Name -eq $WhitelistedName) {
			$FileIsGood = 1
			break
		}
	}

	# File marked to removal.
	if ($FileIsGood -eq 0) {
		Write-Output "$($Name) is to be removed."
		Remove-Item $File -Recurse 
	}

	# Line break
	Write-Output ""
}