import requests

def print_headers(url):
    try:
        response = requests.get(url)
        print(f"Headers for {url}:")
        for key, value in response.headers.items():
            print(f"{key}")
        print("\n")
    except requests.RequestException as e:
        print(f"Error: {e}")

# Пример использования для трех различных сайтов
print_headers("https://vk.com")
print_headers("https://youtube.com")
print_headers("https://ya.ru")