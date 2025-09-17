param(
    [Parameter(Mandatory = $true)]
    [string]
    $Path,
    [Parameter(Mandatory = $false)]
    [switch]
    $Force
)

New-Item -Path $Path -ItemType Directory -Force:$Force -ErrorAction SilentlyContinue | Out-Null
