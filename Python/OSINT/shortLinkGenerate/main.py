import requests

# Замените YOUR_API_KEY на ваш ключ API от bit.ly
API_KEY = '38b02ce08a39c7d1c0019c159ebf70689ceed0fe'
LONG_URL = 'https://example.com' # Замените на вашу длинную ссылку

# URL для создания короткой ссылки через API bit.ly
url = 'https://api-ssl.bitly.com/v4/shorten'

# Заголовки для запроса (необходимо указать ключ API)
headers = {
    'Authorization': f'Bearer {API_KEY}',
    'Content-Type': 'application/json',
}

# Данные для запроса
data = {
'long_url': LONG_URL,
'domain': 'bit.ly', # Можете выбрать другой домен, если нужно
}

# Отправляем POST-запрос к API bit.ly
response = requests.post(url, headers=headers, json=data)

if response.status_code == 200:
# Извлекаем короткую ссылку из ответа
    short_url = response.json().get('link')
    print(f'Короткая ссылка: {short_url}')
else:
    print(f'Не удалось создать короткую ссылку. Код статуса: {response.status_code}')