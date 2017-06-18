import re
import os
import sys

print('Fixing precompiled headers...')

solutionPath = sys.argv[1]
solutionName = '{0}.sln'.format(sys.argv[2])

projectsList = []
with open(os.path.join(solutionPath, solutionName), "r") as solutionFile:
	solutionText = solutionFile.read()

	pattern = "Project\(\"{.*}\"\) = \".*\", \"(.*)\", \"{.*}\""
	for match in re.finditer(pattern, solutionText):
		projPath = os.path.join(solutionPath, match.group(1))
		projectsList.append(projPath)

for project in projectsList:
	f = open(project, "r")
	projectContent = f.read()
	f.close()

	lenOld = len(projectContent)
	projectContent = projectContent.replace("<PrecompiledHeader>Use</PrecompiledHeader>", "<PrecompiledHeader>Create</PrecompiledHeader>")
	projectContent = projectContent.replace("<CharacterSet>Unicode</CharacterSet>", "<CharacterSet>Not Set</CharacterSet>")

	if (lenOld != len(projectContent)):
		f = open(project, "w")
		f.write(projectContent)
		f.close()

		print('Fixed {0}.'.format(project))

print('Done.')
