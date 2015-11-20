param(
[string]$conf = $(throw "conf is required.")
)

$root = "$PSScriptRoot\..\"

Write-Host -foregroundcolor "Yellow" "Building gtest.."
$buildCmd = "C:\Program Files (x86)\MSBuild\14.0\bin\msbuild.exe"
$buildArgs = @(
	  "$root\src\external\googletest\googletest\msvc\gtest-md.sln",
	  "/l:C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll",
	  "/p:Configuration=$Env:CONFIGURATION")