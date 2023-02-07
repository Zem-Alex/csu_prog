import pandas as pd
import requests
import numpy as np

pd.set_option('display.max_columns', None)

data = pd.read_csv('movies.csv', delimiter=',')
sortdata = data.sort_values(by=['rating', 'title'], ascending=False)

# print(sortdata)

top10 = sortdata.head(10)

datatop10 = top10[['title','rating', 'budget']]

print(datatop10)

# url = 'https://www.imdb.com/search/'
# r = requests.get(url)

