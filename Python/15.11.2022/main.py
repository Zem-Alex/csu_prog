from bs4 import BeautifulSoup
import requests

page = requests.get("https://3dnews.ru").text
bsobj = BeautifulSoup(page, "lxml")

articles = bsobj.find_all("span", {"class":"left_label inl_bl"})
for article in articles:
    a = article.findChild("a")
    print(a["title"])