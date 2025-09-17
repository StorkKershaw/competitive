param(
    [Parameter(Mandatory = $true)]
    [string]
    $Path,
    [Parameter(Mandatory = $false)]
    [switch]
    $Recurse,
    [Parameter(Mandatory = $false)]
    [switch]
    $Force
)

Remove-Item -Path $Path -Force:$Force -Recurse:$Recurse -ErrorAction SilentlyContinue | Out-Null
