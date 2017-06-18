@echo off
pushd tools\premake
premake5 vs2013
python slnPchFixer.py "..\.." "RavenScript"
popd