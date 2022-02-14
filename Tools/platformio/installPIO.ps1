#platformio installer can't handle non asci chars in username - so convert username to 8.3 format
$object = New-Object -ComObject Scripting.FileSystemObject
$output = $object.GetFolder($env:USERPROFILE)
$env:USERPROFILE = $output.ShortPath

Write-Output "download platformio install script"
Invoke-WebRequest "https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py" -o:get-platformio.py
Write-Output "run platformio install script"
python .\get-platformio.py

$target=$env:USERPROFILE + "\.platformio\penv\Scripts"

$found=0
$path = [Environment]::GetEnvironmentVariable("Path", [EnvironmentVariableTarget]::User)
$path.split(";") | ForEach {
    if ($_ -ieq $target) {
      $found = 1
    } 
 }
 
if ($found -eq 0) {
  Write-Output "adding platformio to path"
  [Environment]::SetEnvironmentVariable(
    "Path", $path + ";" + $target, 
    [EnvironmentVariableTarget]::User)  
}
    
