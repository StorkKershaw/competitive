param(
    [Parameter(Mandatory = $true)]
    [string]
    $Path,
    [Parameter(Mandatory = $true)]
    [string]
    $Destination,
    [Parameter(Mandatory = $false)]
    [switch]
    $Recurse,
    [Parameter(Mandatory = $false)]
    [switch]
    $Force
)

Copy-Item -Path $Path -Destination $Destination -Recurse:$Recurse -Force:$Force | Out-Null
