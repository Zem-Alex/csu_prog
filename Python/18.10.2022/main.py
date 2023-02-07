import sqlite3
from sqlite3 import Error

con = sqlite3.connect('1.db')
cur = con.cursor()
cur.execute("CREATE TABLE student(name, average score)")

res = cur.execute("SELECT name FROM sqlite_master")
print(res.fetchall())



























'''app = FastAPI()


@app.get("/")
def read_root():
    return {"Hello": "World"}


@app.get("/items/{item_id}")
def read_item(item_id: int, q: Union[str, None] = None):
    return {"item_id": item_id, "q": q}'''


