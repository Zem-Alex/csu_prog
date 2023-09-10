import urllib.request
import json

with urllib.request.urlopen("https://ipinfo.io/json") as url:
 data = json.load(url)

for key, value in data.items():
 print(f"{key}:{value}")