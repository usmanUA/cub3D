import subprocess
import glob
import sys

# maps path
maps_path = 'maps/' + sys.argv[1] + '/*'

for map_file in glob.iglob(maps_path):
    subprocess.run(["./cub3d", map_file])

